// std libs
 #include <iostream>
// project libs
#include "utils/general.hpp"
#include "tools/Tool.hpp" 
#include "tools/Pen.hpp"
#include "tools/Copy.hpp"
#include "tools/Fill.hpp"

// 3rd party libs
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "utils/imfilebrowser.h"

enum class TOOLS {PEN = 1, CPC = 2,FILL = 3};

bool ImgUiToolBoxCheck(){
  return !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && !ImGui::IsAnyItemHovered();
}

int main() { 
  
  int size  = 1;
  int local_color[3] = {0,0,0};
  TOOLS cur_tool;
  
  sf::Image pasted_garbo;
  sf::Texture bck_t;
  sf::Sprite bck_sprt;
  static sf::Vector2f bkc (350.0f,650.0f); 

  sf::RectangleShape box(bkc);
  sf::RenderWindow window(
      sf::VideoMode(1280, 720),                       
      "Paint clone",      
      sf::Style::Default
  );
  Tool cursor(window);
  local_color [0] = cursor.colors [0];
  local_color [1] = cursor.colors [1];
  local_color [2] = cursor.colors [2];

  window.setVerticalSyncEnabled(true);
  fileOpen("Untitled.png",bck_t,bck_sprt);



  if (!ImGui::SFML::Init(window)) {
    std::abort();
  }
  // set both imgui windows 20 units away from the canvas on first launch and never again :p 
  ImGui::SetNextWindowPos(ImVec2(bkc.x + 20,10),0); 
  ImGui::FileBrowser filebrowser;
  filebrowser.SetTitle("Open file");
  filebrowser.SetTypeFilters ({ ".png" , ".jpg" , ".jpeg" });
  sf::Clock deltaClock;
  
  while (window.isOpen()) {
    sf::Vector2f cursor_pos = cursor.getPos();
    sf::Event e;
    while (window.pollEvent(e)) {
      ImGui::SFML::ProcessEvent(e);
      if (e.type == sf::Event::Closed) {
        window.close();
      }
      if (e.type == sf::Event::Resized) { 
        window.setSize(sf::Vector2u(e.size.width,e.size.height));
      }
      if (box.getLocalBounds().contains(cursor_pos) && ImgUiToolBoxCheck() ) {
        if (e.type  == e.MouseButtonPressed  ){
           if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
              auto[r,g,b,a]= cursor.getColorFromPos(bck_t);
              cursor.colors[0] = r;
              cursor.colors[1] = g;
              cursor.colors[2] = b;
          }
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
          {
              if ( cur_tool == TOOLS::PEN) {
                sf::Vector2i in_s = {e.mouseButton.x,e.mouseButton.y};
                Pen(bck_t,in_s,cursor.colors);
              }      
              if (cur_tool == TOOLS::CPC) {
                // sf::Keyboard etc.
              }
              if (cur_tool == TOOLS::FILL) {
                sf::Color target = cursor.getColorFromPos(bck_t);
                sf::Color replace = {cursor.colors[0],cursor.colors[1],cursor.colors[2],255};
                sf::Vector2u cur_pos_u(cursor.getPos().x,cursor.getPos().y);
                FloodFill(bck_sprt,bck_t,target,replace,cur_pos_u);
              }
          }
        }
       
    }

    ImGui::SFML::Update(window, deltaClock.restart());
    {
      ImGui::Begin("Brush Controls");
      ImGui::SliderInt("Red",&(local_color[0]),0,255);
      ImGui::SliderInt("Green",&(local_color[1]),0,255);
      ImGui::SliderInt("Blue",&(local_color[2]),0,255);
      ImGui::SliderInt("Size", &size, 1, 4);
      ImGui::End();
    }
    { 
      ImGui::Begin("Canvas Controls");
      ImGui::SliderFloat(" :X", &bkc.x, 1.f, 1280.f);
      ImGui::SliderFloat(" :Y", &bkc.y, 1.f, 720.f);
      ImGui::End();
    }
    // Create a Menu bar
    if (ImGui::BeginMainMenuBar()) {
      // File interaction
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Save")) {
          fileSave(bck_t);
        }
        if (ImGui::MenuItem("Open")) {
          filebrowser.Open();
          if (filebrowser.HasSelected()) {
            std::string selected_file = filebrowser.GetSelected().string();
            if ( fileOpen(selected_file,bck_t,bck_sprt)) {
              filebrowser.ClearSelected();
              filebrowser.Close();
            }
            else {
              std::printf("UNABLE TO OPEN FILE : \" %s \"",selected_file.c_str());
              filebrowser.Close();
            }
          }
        }
        if (ImGui::MenuItem("Quit")) {window.close();}
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Brush Type")) {
        if (ImGui::MenuItem("Pen")) {
          cur_tool = TOOLS::PEN ;
        }
        if (ImGui::MenuItem("Fill bucket")) {
          cur_tool = TOOLS::FILL ;
        }
        
        if (ImGui::MenuItem("Cut/Paste/Copy")) { 
          cur_tool = TOOLS::CPC;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    // canvas resize
    cursor.colors[0] = local_color [0] ;
    cursor.colors[1] = local_color [1] ;
    cursor.colors[2] = local_color [2] ;


    box.setSize(bkc);
    bck_sprt.setTextureRect(sf::IntRect(0, 0, int(bkc.x),int(bkc.y)));
    // drawing on the screen
    window.clear();
    window.draw(box);

    window.draw(bck_sprt);
    
    
    if (box.getLocalBounds().contains(cursor.getPos()) && ImgUiToolBoxCheck()) {
      cursor.Render(window);
    }
    filebrowser.Display();
    ImGui::SFML::Render(window);
    window.display();
  }
  }
  ImGui::SFML::Shutdown();
  return 0;
}
