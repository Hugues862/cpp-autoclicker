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
            ImGui::SetNextWindowSize(ImVec2(600, 800), ImGuiCond_FirstUseEver);

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
                    ImGui::InputText("", (*it)->name, 64);
                    ImGui::PopID();

                    //COL 2
                    ImGui::TableNextColumn();
                    
                    //EDIT BTN
                    //Color Yellow
                    color_modifier = 1;
                    ImGui::PushID(row);
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
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
                    ImGui::PushID(row);
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
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
                const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 600, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(400, 800), ImGuiCond_FirstUseEver);
                ImGui::Begin("Edit Macro", &display_edit_module_window);
                ImGui::Text("Macro ID: %d", selected_macro);
                ImGui::Text("Macro Name: %s", macros[selected_macro]->name);
                if (ImGui::Button("New")) {
                    macros[selected_macro]->movePos.push_back(new Click(100,200));
                };
                ImGui::Separator();

                //List of Clicks
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

                ImGui::BeginChild("ListClicks", ImVec2(0, 0), true, window_flags);
                
                ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH
                | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_PadOuterX;


                if (ImGui::BeginTable("Clicks", 2, flags))
                {

                    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 200.0f); // Default to 100.0f
                    ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 100.0f); // Default to 200.0f

                    vector<Click*>::iterator it;

                    int row = 0;
                    for (it = macros[selected_macro]->movePos.begin(); it != macros[selected_macro]->movePos.end(); it++)
                    {
                        int color_modifier = 0;
                        ImGui::TableNextRow();
                        //COL 1
                        ImGui::TableNextColumn();
                        ImGui::Text("%d |", row); ImGui::SameLine();
                        
                        char _x[10];
                        char _y[10];
                        strcpy(_x, std::to_string((*it)->x).c_str());
                        strcpy(_y, std::to_string((*it)->y).c_str());

                        ImGui::PushID(row);
                        ImGui::InputText("x", _x, 64, ImGuiInputTextFlags_CharsDecimal);
                        ImGui::InputText("y", _y, 64, ImGuiInputTextFlags_CharsDecimal);
                        ImGui::PopID();
                        (*it)->x = atoi(_x);
                        (*it)->y = atoi(_y);


                        //COL 2
                        ImGui::TableNextColumn();


                        //DELETE BTN
                        //Color Red
                        color_modifier = 0;
                        ImGui::PushID(row);
                        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
                        if (ImGui::Button("DELETE")) {
                            // macros.erase(it);
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
            }

            return 0;
        };

};
