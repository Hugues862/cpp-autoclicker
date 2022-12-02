#include <SDL.h>
#include <iostream>
#include "windows.hpp"
#include <cstring>
#include "macro.hpp"
#include <vector>
#include "click.hpp"
#include <json/value.h>
#include <fstream>

/**
 * @brief The Gui class is used to control all the GUIs, also it inits the SDL as well as ImGui
 **/
class Gui {
    public:
        bool DEBUG;
        bool main_loop_alive = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        //SDL COMPONENTS
        SDL_WindowFlags window_flags;
        SDL_Window* window;
        SDL_Renderer* renderer;

        Windows windows;

        //Gui constructor, inits SDL and ImGui
        Gui(bool DEBUG = false) {
            
            this->DEBUG = DEBUG;
            

            initial_SDL();
            initial_ImGui();

            //Font Configuration
            ImFontConfig font_config;
            font_config.OversampleH = 1;
            font_config.OversampleV = 1;

            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontFromFileTTF("src/imgui/misc/fonts/Roboto-Medium.ttf", 18.0f, &font_config);
            // io.Fonts->AddFontDefault();
            
            // Disables .ini file
            io.IniFilename = NULL;
            io.LogFilename = NULL;

            main_loop();
            
        }

        int initial_SDL() {

            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
            {
                printf("Error: %s\n", SDL_GetError());
                return 0;
            }

            // Setup window
            window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
            window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 900, window_flags);
            if (NULL == window){
                std::cout << "Couldn't create the window" << std::endl << SDL_GetError() << std::endl;
                return 0;
            }  

            // Setup SDL_Renderer instance
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            if (renderer == NULL)
            {
                SDL_Log("Error creating SDL_Renderer!");
                return 0;
            }

            // SDL Renderer info for debugging
            if (DEBUG) {
                SDL_RendererInfo info;
                SDL_GetRendererInfo(renderer, &info);
                SDL_Log("Current SDL_Renderer: %s", info.name);
            }

            return 0;
        }

        int initial_ImGui() {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            // Setup Dear ImGui style, light mode also available
            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
            ImGui_ImplSDLRenderer_Init(renderer);


            return 0;
        }

        int rendering() {
            ImGui::Render();
            SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
            SDL_RenderClear(renderer);
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderer);

            return 0;
        }

        
        int main_loop() {
            //Load Macros from JSON
            Json::Reader reader;
            Json::Value root;

            std::ifstream file_input("saveFile/data.json");
            reader.parse(file_input, root);

            int sizeRoot = root["macros"].size();
            // windows.macros.reserve(sizeRoot);

            for (int i = 0; i < sizeRoot; i++){
                SDL_Log("Macro %d", i);
                windows.macros.push_back(new Macro);
                windows.macros.back()->Load(root["macros"][i]);
            }

            while(main_loop_alive){
                
                //Close Event, if the user clicks the X button or alt f4, etc...
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    ImGui_ImplSDL2_ProcessEvent(&event);
                    if (event.type == SDL_QUIT)
                        main_loop_alive = false;
                    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                        main_loop_alive = false;
                }


                ImGui_ImplSDLRenderer_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();

                //WINDOWS
                if (this->DEBUG == true) {
                    ImGui::ShowDemoWindow();
                    
                }

                

                windows.main_window();
                windows.edit_module_window();
                windows.history_window();

                rendering();
            }
            
            std::ofstream file_id;
            file_id.open("saveFile/data.json");

            Json::Value saveTmp = windows.Save();
            //populate 'value_obj' with the objects, arrays etc.

            Json::StyledWriter styledWriter;
            file_id << styledWriter.write(saveTmp);

            file_id.close();
            return 0;

        }

        ~Gui() {
            // Cleanup
            ImGui_ImplSDLRenderer_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
};