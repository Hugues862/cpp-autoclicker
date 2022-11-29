#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "macro.hpp"
#include <string> 


class Windows {
    
    
    public:

        vector<Macro*> macros;
        bool show_new_click_module_window = false;

        Windows() {
            
        };


        int demo_window() {
            

            ImGui::ShowDemoWindow();

            return 0;
        };

        int main_window() {
            const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
            
            ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 0, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

            ImGui::Begin("Autoclicker");                          // Create a window called "Hello, world!" and append into it.

            



            if (ImGui::Button("New")) {
                show_new_click_module_window = true;

                macros.push_back(new Macro);
            };

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

            ImGui::BeginChild("ListMacros", ImVec2(0, 0), true, window_flags);
            
            ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH
             | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_PadOuterX;


            if (ImGui::BeginTable("Macros", 2, flags))
            {



                for (int row = 0; row < (int)macros.size(); row++)
                {
                    ImGui::TableNextRow();
                    //COL 1
                    ImGui::TableNextColumn();
                    ImGui::Text("%d |", row); ImGui::SameLine();
                    ImGui::Text(" %s", macros[row]->name); ImGui::SameLine();

                    //COL 2
                    ImGui::TableNextColumn();
                    if (ImGui::Button("EDIT")) {
                        std::cout << "EDIT" << std::endl;
                    }; ImGui::SameLine();
                    if (ImGui::Button("DUPLICATE")) {
                        std::cout << "DUPE" << std::endl;
                    };
                    if (ImGui::Button("DELETE")) {
                        std::cout << "DELETE" << std::endl;
                    };

                        
                    // 
                }
                ImGui::EndTable();
            
            };

            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::End();
            return 0;
        };


        int new_click_module_window() {
            if (show_new_click_module_window) {
                ImGui::Begin("New Click Module", &show_new_click_module_window);
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_new_click_module_window = false;
                ImGui::End();
            }

            return 0;
        };

};
