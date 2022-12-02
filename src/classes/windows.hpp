#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "macro.hpp"
#include <string> 
#include <thread>
#include <time.h>

class Windows {
    
    
    public:

        // Vectors
        // Stores the macros
        vector<Macro*> macros;
        // Stores the macros execution history
        vector<Macro*> macros_history;

        // Display or not certain windows
        bool display_edit_module_window = false;
        bool display_history_window = true;


        int selected_macro = 0;


        Windows() {
            
        };

        /**
         * @brief Display the main window
         */
        int main_window() {
            // Main window setup
            const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 0, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(600, 900), ImGuiCond_FirstUseEver);
            ImGui::Begin("Autoclicker");                          // Create a window called "Hello, world!" and append into it.


            // New Macro Button
            if (ImGui::Button("New")) {
                macros.push_back(new Macro);
            };

            //Preparing the list of macros
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ListMacros", ImVec2(0, 0), true, window_flags);
            
            ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH
             | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_PadOuterX;

            if (ImGui::BeginTable("Macros", 2, flags))
            {

                vector<Macro*>::iterator it;

                int row = 0;
                for (it = macros.begin(); it != macros.end(); )
                {
                    int color_modifier = 0;
                    ImGui::TableNextRow();
                    //COL 1
                    ImGui::TableNextColumn();
                    ImGui::Text("%d |", row); ImGui::SameLine();
                    ImGui::PushID(row);
                    //When name modified, update the macro name
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
                    //When button clicked, display the edit window
                    if (ImGui::Button("EDIT")) {
                        display_edit_module_window = true;
                        selected_macro = row;
                    };

                    ImGui::PopID();
                    ImGui::PopStyleColor(2);
                    ImGui::SameLine();

                    // RECORD BUTTON
                    ImGui::PushID(row);
                    if (ImGui::Button("RECORD")) {
                        //
                        //Horrible to do, hate threading in C++
                        //Create a lambda function that takes in an iterator it and executes the record function of the macro
                        //Create a new thread from the lambda function
                        //This is non optional or te program crash, ImGui doesn't like when nothing is displayed for a long time
                        auto lmRec = [](vector<Macro*>::iterator it){(*it)->record();};
                        std::thread thread_obj(std::ref(lmRec), it);
                        //Detach the thread so it doesn't wait for the end of the program
                        thread_obj.detach();

                    };

                    ImGui::PopID();
                    ImGui::SameLine();

                    // PLAY BUTTON
                    ImGui::PushID(row);
                    if (ImGui::Button("PLAY")) {
                        
                        if ((*it)->movePos.size() != 0) {

                            //Same as comment above ^^
                            auto lmPlay = [](vector<Macro*>::iterator it){(*it)->play();};
                            std::thread thread_obj(std::ref(lmPlay), it);
                            thread_obj.detach();
                            macros_history.emplace(macros_history.begin(), (*it));
                        }

                    };

                    ImGui::PopID();
                    ImGui::SameLine();

                    //DUPLICATE BTN
                    //Could not make it work in time unfortunately
                    //
                    // ImGui::PushID(row);
                    // if (ImGui::Button("DUPLICATE")) {
                        
                    //     Macro* newMacro = new Macro(*(*it));
                    //     macros.emplace_back(newMacro);

                    //     // std::cout << "DUPE " << row << std::endl;
                    // };
                    // ImGui::PopID();
                    // ImGui::SameLine();


                    //DELETE BTN
                    //Color Red
                    color_modifier = 0;
                    ImGui::PushID(row);
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(color_modifier / 7.0f, 0.7f, 0.7f));
                    //Remove macro from vector when DELETE button clicked
                    if (ImGui::Button("DELETE")) {
                        macros.erase(it);
                    };
                    ImGui::PopID();
                    ImGui::PopStyleColor(2);

                    ++row;

                    if (it != macros.end()){
                        ++it;
                    }
                    
                    // 
                }
                ImGui::EndTable();
            
            };

            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::End();
            return 0;
        };


        /**
         * @brief Display the edit module window
         */
        int edit_module_window() {
            if (display_edit_module_window) {
                const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 600, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(400, 900), ImGuiCond_FirstUseEver);
                ImGui::Begin("Edit Macro", &display_edit_module_window);
                ImGui::Text("Macro ID: %d", selected_macro);
                ImGui::Text("Macro Name: %s", macros[selected_macro]->name);
                // if (ImGui::Button("New")) {
                //     macros[selected_macro]->movePos.push_back(new Click);
                // };
                ImGui::Separator();
                // ImGui::PushID("record");
                // if (ImGui::Button("RECORD")) {
                    
                //     Macro* it = macros[selected_macro];
                //     auto lmRec = [](Macro* it){ it->record();};
                //     std::thread thread_obj(std::ref(lmRec), it);
                //     thread_obj.detach();
                // };
                // ImGui::PopID();
                // ImGui::SameLine();


               
                
                //Loop, display input
                ImGui::InputInt("Loop : ", &macros[selected_macro]->loop);
                //If loop is -1, display infinite loop
                if (macros[selected_macro]->loop == -1) {
                    ImGui::SameLine();
                    ImGui::Text("Repeat Indefinitely");
                }
                //If user try to set loop less than -1, block him
                if (macros[selected_macro]->loop < -1) {
                    macros[selected_macro]->loop = -1;
                }

                //Delay
                ImGui::InputInt("Delay (ms) : ", &macros[selected_macro]->delay);


                ImGui::Separator();

                //List of Clicks
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

                ImGui::BeginChild("ListClicks", ImVec2(0, 0), true, window_flags);
                
                ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH
                | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_PadOuterX;

                //List of clicks
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
                        strcpy(_x, std::to_string((*it)->getX()).c_str());
                        strcpy(_y, std::to_string((*it)->getY()).c_str());

                        ImGui::PushID(row);
                        ImGui::InputText("x", _x, 64, ImGuiInputTextFlags_CharsDecimal);
                        ImGui::InputText("y", _y, 64, ImGuiInputTextFlags_CharsDecimal);
                        ImGui::PopID();
                        (*it)->setX(atoi(_x));
                        (*it)->setY(atoi(_y));


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

        
        int history_window() {
            if (display_history_window) {
                const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 1000, main_viewport->WorkPos.y + 0), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(200, 900), ImGuiCond_FirstUseEver);
                ImGui::Begin("Macro History", &display_history_window);
                
                

                // int row = 0;

                // fetch history from vector
                for (int i = 0; i < (int)macros_history.size(); i ++){
                    ImGui::Text("%d | ", i);ImGui::SameLine();
                    ImGui::Text("%s", macros_history[i]->name);
                    // row++
                };
                ImGui::End();
                return 0;

            };
            return 0;
        };

        /**
         * @brief Uses Json Value to export all data from previous session
         * 
         * @return Json::Value 
         */
        Json::Value Save(){

            Json::Reader read;
            Json::Value root;

            string json = "{\"macros\":[";
            string add;

            for (int i = 0; i < (int)macros.size(); i++){

                add = macros[i]->Save();
                json.append(add);

            }
            json.pop_back();

            json.append("]}");
            
            SDL_Log("%s", json.c_str());
            bool v = read.parse(json.c_str(), root, false);
            if (!v) {
                SDL_Log("Error parsing json");
            }
            return root;
        }

        //Cleanup
        ~Windows () {
            //Delete all macros
            for (int i = 0; i < (int)macros.size(); i++) {
                delete macros[i];
            }
            //Delete all macros history
            for (int i = 0; i < (int)macros_history.size(); i++) {
                delete macros_history[i];
            }
        };
};
