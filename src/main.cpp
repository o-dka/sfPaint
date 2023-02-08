
#include "brush.hpp"
// #include "penTool.hpp"
// #include "lineTool.hpp"
// #include "rectangleTool.hpp"
// #include "cutPasteTool.hpp"
// #include "fillTool.hpp"
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
        filename.replace(8, 1, std::to_string(x + 1));
    }
}

float bkc_x = 200;
float bkc_y = 350;

int main() {
    Brush *pen = new Brush();
    sf::Vector2i mousepos;
    // sf::RectangleShape brush;
    sf::Texture bckgrnd;
    sf::RectangleShape bckgrnd_box(sf::Vector2f(bkc_x, bkc_y));
    sf::Sprite bckgrnd_sprt;
    if (!bckgrnd.loadFromFile("build/Untitled.png")) {
        return 1;
    }
    bckgrnd_sprt.setTexture(bckgrnd);
    sf::RenderWindow window(sf::VideoMode(1280, 720),
                            "Crappy paint clone , has only one brush");
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
                if (ImGui::MenuItem("Save")) {
                    // a save button that saves, wow!
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
            if (ImGui::BeginMenu("Other")) {
                // Program info and stuff
                ImGui::MenuItem("Help");
                ImGui::MenuItem("About");
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::Begin("Brush Controls");
        ImGui::SliderInt("Red", &colors[0], 0, 255);
        ImGui::SliderInt("Green", &colors[1], 0, 255);
        ImGui::SliderInt("Blue", &colors[2], 0, 255);
        ImGui::SliderInt("Aplha", &colors[3], 1, 255);
        ImGui::SliderInt("Size", pen->size(), 1, 100);
        ImGui::End();
        ImGui::Begin("Brush type");
        ImGui::Button("Line");
        ImGui::Button("Brush");
        ImGui::Button("Rectangle tool");
        ImGui::Button("Fill tool");
        ImGui::End();
        ImGui::Begin("Canvas Controls");
        ImGui::SliderFloat(" :X", &bkc_x, 1.f, 1280.f);
        ImGui::SliderFloat(" :Y", &bkc_y, 1.f, 720.f);
        ImGui::End();
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // drawing things
            pen->draw();
        }
        bckgrnd_box.setSize(sf::Vector2f(bkc_x, bkc_y));
        bckgrnd_sprt.setTextureRect(sf::IntRect(0, 0, int(bkc_x), int(bkc_y)));
        window.clear();
        window.draw(bckgrnd_box);
        window.draw(bckgrnd_sprt);
        if ((float(mousepos.x) < bckgrnd_box.getSize().x) &&
            (float(mousepos.y) < bckgrnd_box.getSize().y)) {
            // Brush things :P
            pen.setPosition(sf::Vector2f(mousepos) + sf::Vector2f(10.f, 1.f));
            pen.setFillColor(
                sf::Color(colors[0], colors[1], colors[2], colors[3]));
            brush.setSize(sf::Vector2f(float(pen.size()), float(pen.size())));
            window.draw(brush);
        }
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
