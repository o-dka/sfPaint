// std libs
 #include <iostream>
// project libs
#include "utils/general.hpp"
#include "tools/Tool.hpp" 
#include "tools/Pipet.hpp"
#include "tools/Fill.hpp"

// 3rd party libs
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "utils/imfilebrowser.h"

enum class CurTool {PEN = 1, PIPET = 2,FILL = 3};



int main() { 
  
  int size  = 1;

  CurTool cur_tool;
  Tool* cursor = new Tool;
  
  sf::Image pasted_garbo;
  sf::Texture bckgrnd;
  sf::Sprite bckgrnd_sprt;
  static sf::Vector2f bkc (350.0f,650.0f); 

  sf::RectangleShape bckgrnd_box(bkc);
  sf::RenderWindow window(
      sf::VideoMode(1280, 720),                       
      "Paint clone",      
      sf::Style::Default
  );

  window.setVerticalSyncEnabled(true);
  fileOpen("Untitled.png",bckgrnd,bckgrnd_sprt);


  
  

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
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) { 
        window.setSize(sf::Vector2u(event.size.width,event.size.height));
      }
      if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::Button(sf::Mouse::Left)) {
        sf::Vector2f cursor_pos = cursor->getPos(window);
       while (
            bckgrnd_box.getLocalBounds().contains(cursor_pos)
            && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)  
            && !ImGui::IsAnyItemHovered() 
           ) {   
          cursor->posm.push_back(cursor_pos);
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());
    {
      ImGui::Begin("Brush Controls");
      ImGui::SliderInt3("Color",cursor->colors,0,255);
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
          fileSave(bckgrnd);
        }
        if (ImGui::MenuItem("Open")) {
          filebrowser.Open();
          if (filebrowser.HasSelected()) {
            std::string selected_file = filebrowser.GetSelected().string();
            if ( fileOpen(selected_file,bckgrnd,bckgrnd_sprt)) {
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
          cur_tool = CurTool::PEN ;
        }
        if (ImGui::MenuItem("Fill bucket")) {
          cur_tool = CurTool::FILL ;
        }
        
        if (ImGui::MenuItem("Cut/Copy/Paste/Pipet")) { 
          cur_tool = CurTool::PIPET;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
   
    // Application operations 
    //  What fucns to use? 
    sf::Sprite in_s;
    switch (cur_tool)
    {
    case CurTool::PEN:
      in_s = cursor->getSprite();
      copyToTex(bckgrnd,in_s,bckgrnd_sprt,size,cursor->posm);
      break;
    case CurTool::FILL:
      FloodFill(bckgrnd_sprt,bckgrnd,,{cursor->colors[0],cursor->colors[1],cursor->colors[2],255},{cursor->getPos().x,cursor->getPos().y});
      break;
    case CurTool::PIPET: 
      pasted_garbo = copyPixels();
      pastePixels();
      pasted_garbo = cutPixels();
      setColorFromPos();
      break;
    }
      
     
  
    // canvas resize
    bckgrnd_box.setSize(bkc);
    bckgrnd_sprt.setTextureRect(sf::IntRect(0, 0, int(bkc.x),int(bkc.y)));

    // drawing on the screen
    window.clear();
    window.draw(bckgrnd_box);
    window.draw(bckgrnd_sprt);
    
    
    if (bckgrnd_box.getLocalBounds().contains(cursor->getPos(window))
        && !ImGui::IsWindowHovered(ImGuiHoveredFlags_None)  
        && !ImGui::IsAnyItemHovered()) {
      cursor->Render(window);
    }
    filebrowser.Display();
    ImGui::SFML::Render(window);
    window.display();
  }
  }
  ImGui::SFML::Shutdown();
  return 0;
}
