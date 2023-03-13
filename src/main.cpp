#include "brush.hpp"
// #include "lineTool.hpp"
// #include "rectangleTool.hpp"
// #include "cutPasteTool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <experimental/filesystem>
#include <string>
namespace fs = std::experimental::filesystem;

void file_save(sf::Texture &t) {
    std::string filename = "Unnamed_0.png";
    for (int x = 0;; x++) {
        if (fs::exists(filename) == false) {
            t.copyToImage().saveToFile(filename);
            break;
        }
        else 
            filename.replace(8, 1, std::to_string(x + 1));
    }
}
bool is_within_canvas(sf::Vector2i pointr_pos,sf::RectangleShape canvas){
    return
        float(pointr_pos.x) < canvas.getSize().x &&
        float(pointr_pos.y) < canvas.getSize().y ;
   
}
float bkc_x = 200.f;
float bkc_y = 350.f;

int main() { 
    sf::Texture bckgrnd;
    sf::RectangleShape bckgrnd_box(sf::Vector2f(bkc_x, bkc_y));
    sf::Sprite bckgrnd_sprt;
    if (!bckgrnd.loadFromFile("build/Untitled.png")) {
        return 1;
    }
    bckgrnd_sprt.setTexture(bckgrnd);
    // sf::ContextSettings settings;
    // settings.antialiasingLevel = zz;
    sf::RenderWindow window(sf::VideoMode(1280, 720),                  //
                            "Crappy paint clone , has only one brush" //
                            // sf::Style::Default,                        //
                            // settings                                   //
    );
    window.setFramerateLimit(120);
    Brush *pen = new Brush(window); // Brush set
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
                if (ImGui::MenuItem("Save")) {
                    file_save(bckgrnd);
                }
                if (ImGui::MenuItem("Open")){
                    // bckgrnd = file_open();
                }
                if (ImGui::MenuItem("Quit")) {
                    // a quit button!
                    window.close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Brush Type")){
                if (ImGui::MenuItem("Pen")) {
                    // delete pen;
                    /* Pen change code */
                }
                if (ImGui::MenuItem("Line")) { /*Line change code */}
                if (ImGui::MenuItem("Rectangle")) { /*Rectangle change code */}
                if (ImGui::MenuItem("Cut/Copy/Paste")) { /*Cut/Copy/Paste change code */}
                ImGui::EndMenu();
            }
                if (ImGui::BeginMenu("Other")) {
                    // Program info and stuff
                    ImGui::MenuItem("Help");
                    ImGui::MenuItem("About");
                    ImGui::EndMenu();
                }
            ImGui::EndMainMenuBar();
        }
        ImGui::Begin("Brush Controls");
        ImGui::SliderInt("Red", &pen->color[0], 0, 255);
        ImGui::SliderInt("Green", &pen->color[1], 0, 255);
        ImGui::SliderInt("Blue", &pen->color[2], 0, 255);
        ImGui::SliderInt("Aplha", &pen->color[3], 1, 255);
        ImGui::SliderInt("Size",&pen->size, 1, 100);
        ImGui::End();
        ImGui::Begin("Canvas Controls");
        ImGui::SliderFloat(" :X", &bkc_x, 1.f, 1280.f);
        ImGui::SliderFloat(" :Y", &bkc_y, 1.f, 720.f);
        ImGui::End();
        // canvas body resize and texture set
        bckgrnd_box.setSize(sf::Vector2f(bkc_x, bkc_y));
        bckgrnd_sprt.setTextureRect(sf::IntRect(0, 0, int(bkc_x), int(bkc_y)));
        // painting!
        if (is_within_canvas(pen->sf::Mouse::getPosition(), bckgrnd_box)) {
            pen->paint(bckgrnd_box, bckgrnd, bckgrnd_sprt);
            pen->pointer_draw(bckgrnd_box);
        }
        // drawing on the screen
        window.clear();
        window.draw(bckgrnd_box);
        window.draw(bckgrnd_sprt);
        if (is_within_canvas(pen->sf::Mouse::getPosition(),bckgrnd_box)){
            window.draw(*pen);
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}