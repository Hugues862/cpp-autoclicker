#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "macro.hpp"
#include <string> 


class Windows {
    
    
    public:

        vector<Macro*> macros;

        bool display_edit_module_window = false;
        int selected_macro = 0;


        Windows() {
            
        };


        int demo_window() {
            

            ImGui::ShowDemoWindow();

            return 0;
        };

        int main_window() {
            const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
            
            ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 0, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_FirstUseEver);

            ImGui::Begin("Autoclicker");                          // Create a window called "Hello, world!" and append into it.

            



            if (ImGui::Button("New")) {

                macros.push_back(new Macro);
            };

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

            ImGui::BeginChild("ListMacros", ImVec2(0, 0), true, window_flags);
            
            ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH
             | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_PadOuterX;


            if (ImGui::BeginTable("Macros", 2, flags))
            {

                vector<Macro*>::iterator it;

                int row = 0;
                for (it = macros.begin(); it != macros.end(); it++)
                {
                    int color_modifier = 0;
                    ImGui::TableNextRow();
                    //COL 1
                    ImGui::TableNextColumn();
                    ImGui::Text("%d |", row); ImGui::SameLine();
                    ImGui::PushID(row);
                    ImGui::InputText("##title", (*it)->name, 64);
                    ImGui::PopID();

                    //COL 2
                    ImGui::TableNextColumn();
                    
                    //EDIT BTN
                    //Color Yellow
                    color_modifier = 1;
                    ImGui::PushID(color_modifier);
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
                    ImGui::PopID();
                    ImGui::PushID(row);
                    if (ImGui::Button("EDIT")) {
                        display_edit_module_window = true;
                        selected_macro = row;
                    };
                    ImGui::PopID();
                    ImGui::PopStyleColor(2);
                    ImGui::SameLine();

                    //DUPLICATE BTN
                    ImGui::PushID(row);
                    if (ImGui::Button("DUPLICATE")) {
                        std::cout << "DUPE " << row << std::endl;
                    };
                    ImGui::PopID();
                    ImGui::SameLine();


                    //DELETE BTN
                    //Color Red
                    color_modifier = 0;
                    ImGui::PushID(color_modifier);
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
                    ImGui::PopID();
                    ImGui::PushID(row);
                    if (ImGui::Button("DELETE")) {
                        macros.erase(it);
                    };
                    ImGui::PopID();
                    ImGui::PopStyleColor(2);

                    row++;
                    // 
                }
                ImGui::EndTable();
            
            };

            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::End();
            return 0;
        };


        int edit_module_window() {
            if (display_edit_module_window) {
                ImGui::Begin("New Click Module", &display_edit_module_window);
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    display_edit_module_window = false;
                ImGui::End();
            }

            return 0;
        };

};
