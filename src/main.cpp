#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

float bkc_x = 100;
float bkc_y = 100;
int brush_size = 2;
int colors[3] = {0, 120, 0};
int main() {
    sf::Vector2i mousepos;
    sf::RectangleShape brush;
    sf::Texture bckgrnd;
    sf::RectangleShape bckgrnd_box(sf::Vector2f(bkc_x, bkc_y));
    sf::Sprite bckgrnd_sprt;
    if (!bckgrnd.loadFromFile("build/Untitled.png")) {
        return 1;
    }
    bckgrnd_sprt.setTexture(bckgrnd);

    sf::RenderWindow window(
                        sf::VideoMode(1280, 720),
                        "Crappy paint clone , has only one brush"
                        );
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        // Create a Menu bar
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                // File interaction
                if (ImGui::MenuItem("Save") ){ /* something about saving an image and stuff*/}
                if(ImGui::MenuItem("Quit")){ //a quit button!
                    window.close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Other")){
                // Program info and stuff
                ImGui::MenuItem("Help");
                ImGui::MenuItem("About");
                ImGui::EndMenu();
            } ImGui::EndMainMenuBar();
        }
        ImGui::Begin("Brush Controls");
        ImGui::SliderInt("Red", &colors[0], 0, 255);
        ImGui::SliderInt("Green", &colors[1], 0, 255);
        ImGui::SliderInt("Blue", &colors[2], 0, 255);
        ImGui::SliderInt("Size", &brush_size, 1, 100);
        ImGui::End();
        
        ImGui::Begin("Canvas Controls");
        ImGui::SliderFloat(" :X", &bkc_x, 1.f, 1280.f);
        ImGui::SliderFloat(" :Y", &bkc_y, 1.f, 720.f);
        ImGui::End();
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            // drawing things
            int  pixel_arr_sz=(brush_size * brush_size) * 4 ;

            sf::Uint8 pixels[pixel_arr_sz];
            for (int i = 0; i != pixel_arr_sz; i++) {
                pixels[i] = brush.getFillColor().r;
                pixels[i + 1] = brush.getFillColor().g;
                pixels[i + 2] = brush.getFillColor().b;
                if (brush.getFillColor().r > 0)
                    pixels[i + 3] = brush.getFillColor().r;
                if (brush.getFillColor().g  > 0  )
                    pixels[i + 3] = brush.getFillColor().g;
                if(brush.getFillColor().b > 0)
                    pixels[i + 3] = brush.getFillColor().b;
            }
            
            if ((float(mousepos.x) < bckgrnd_box.getSize().x) &&
                (float(mousepos.y) < bckgrnd_box.getSize().y)) {
                bckgrnd.update(pixels,               //
                               unsigned(brush_size), //
                               unsigned(brush_size), //
                               unsigned(mousepos.x) + 1,
                               unsigned(mousepos.y) + 10);
                bckgrnd_sprt.setTexture(bckgrnd);
            }
        }
        bckgrnd_box.setSize(sf::Vector2f(bkc_x, bkc_y));
        bckgrnd_sprt.setTextureRect(sf::IntRect(0, 0, int(bkc_x), int(bkc_y)));
        window.clear();
        window.draw(bckgrnd_box);
        window.draw(bckgrnd_sprt);
        if ((float(mousepos.x) < bckgrnd_box.getSize().x) &&
            (float(mousepos.y) < bckgrnd_box.getSize().y)) {
            // Brush things :P
            brush.setPosition(sf::Vector2f(mousepos) + sf::Vector2f(10.f, 1.f));
            brush.setFillColor(sf::Color(colors[0], colors[1], colors[2]));
            brush.setSize(sf::Vector2f(float(brush_size), float(brush_size)));
            window.draw(brush);
        }
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
