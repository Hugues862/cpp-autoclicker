#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

class Windows {
    public:
        ImVec4 *clear_color;
        
        bool show_new_click_module_window = false;

        Windows() {
            
        };


        int demo_window() {
            

            ImGui::ShowDemoWindow();

            return 0;
        };

        int main_window() {
        

            ImGui::Begin("Autoclicker");                          // Create a window called "Hello, world!" and append into it.

            
            if (ImGui::Button("New")) {
                show_new_click_module_window = true;
            };

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        

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
