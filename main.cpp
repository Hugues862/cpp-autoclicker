#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include "guis.hpp"

// const int WIN_WIDTH = 800, WIN_HEIGHT = 600;

int main(int argv, char** args){

    Gui gui;
    


    return 0;
}
    // if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    // {
    //     printf("Error: %s\n", SDL_GetError());
    //     return -1;
    // }

    // Setup window
    // SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    // SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    // if (NULL == window){
    //     std::cout << "Couldn't create the window" << std::endl << SDL_GetError() << std::endl;
    //     return 1;
    // }  

    // // Setup SDL_Renderer instance
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    // if (renderer == NULL)
    // {
    //     SDL_Log("Error creating SDL_Renderer!");
    //     return 0;
    // }

    // // SDL Renderer info for debugging
    // SDL_RendererInfo info;
    // SDL_GetRendererInfo(renderer, &info);
    // SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    // //ImGui::StyleColorsLight();

    // // Setup Platform/Renderer backends
    // ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    // ImGui_ImplSDLRenderer_Init(renderer);

    // bool show_demo_window = true;
    // bool show_another_window = false;
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // // Main loop
    // bool done = false;
    // while (!done)
    // {
    //     // Poll and handle events (inputs, window resize, etc.)
    //     // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    //     // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    //     // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    //     // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event))
    //     {
    //         ImGui_ImplSDL2_ProcessEvent(&event);
    //         if (event.type == SDL_QUIT)
    //             done = true;
    //         if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
    //             done = true;
    //     }

    //     // Start the Dear ImGui frame
    //     ImGui_ImplSDLRenderer_NewFrame();
    //     ImGui_ImplSDL2_NewFrame();
    //     ImGui::NewFrame();

    //     // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    //     if (show_demo_window)
    //         ImGui::ShowDemoWindow(&show_demo_window);

    //     // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    //     {
    //         static float f = 0.0f;
    //         static int counter = 0;

    //         ImGui::Begin("Main");                          // Create a window called "Hello, world!" and append into it.

    //         ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //         ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //         ImGui::Checkbox("Another Window", &show_another_window);

    //         ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //         ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //         if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    //             counter++;
    //         ImGui::SameLine();
    //         ImGui::Text("counter = %d", counter);

    //         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //         ImGui::End();
    //     }

    //     // 3. Show another simple window.
    //     // if (show_another_window)
    //     // {
    //     //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    //     //     ImGui::Text("Hello from another window!");
    //     //     if (ImGui::Button("Close Me"))
    //     //         show_another_window = false;
    //     //     ImGui::End();
    //     // }

    //     // Rendering
    //     ImGui::Render();
    //     SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    //     SDL_RenderClear(renderer);
    //     ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    //     SDL_RenderPresent(renderer);
    // }
    // Cleanup
    // ImGui_ImplSDLRenderer_Shutdown();
    // ImGui_ImplSDL2_Shutdown();
    // ImGui::DestroyContext();

    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();


