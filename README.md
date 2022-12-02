# How to Build

-   On Windows with Visual Studio's CLI

```
set SDL2_DIR=path_to_your_sdl2_folder
cl /Zi /MD /I.. /I..\.. /I%SDL2_DIR%\include main.cpp ..\..\backends\imgui_impl_sdl.cpp ..\..\backends\imgui_impl_sdlrenderer.cpp ..\..\imgui*.cpp /FeDebug/example_sdl_sdlrenderer.exe /FoDebug/ /link /libpath:%SDL2_DIR%\lib\x86 SDL2.lib SDL2main.lib /subsystem:console
#          ^^ include paths                  ^^ source files                                                                                        ^^ output exe                        ^^ output dir  ^^ libraries
# or for 64-bit:
cl /Zi /MD /I.. /I..\.. /I%SDL2_DIR%\include main.cpp ..\..\backends\imgui_impl_sdl.cpp ..\..\backends\imgui_impl_sdlrenderer.cpp ..\..\imgui*.cpp /FeDebug/example_sdl_sdlrenderer.exe /FoDebug/ /link /libpath:%SDL2_DIR%\lib\x64 SDL2.lib SDL2main.lib /subsystem:console
```

-   On Linux and similar Unixes

```
c++ `sdl2-config --cflags` -I .. -I ../.. main.cpp ../../backends/imgui_impl_sdl.cpp ../../backends/imgui_impl_sdlrenderer.cpp ../../imgui*.cpp `sdl2-config --libs` -lGL
```

-   On Mac OS X

```
brew install sdl2
c++ `sdl2-config --cflags` -I .. -I ../.. main.cpp ../../backends/imgui_impl_sdl.cpp ../../backends/imgui_impl_sdlrenderer.cpp ../../imgui*.cpp `sdl2-config --libs` -framework OpenGl
```

# C++ Autoclicker

## Authors

-   [Yoann Chhang](https://github.com/YoannChhang)
-   [Hugues-Pacôme Stock](https://github.com/Hugues862)

---

Les commentaires technique du projet sont en anglais.

## Fonctionnalitées

-   Ajout / Suppression / Renomage Macros
-   Delai entre les Macros
-   Possibilité mettre en boucle les macros
    -   0 : 0 Répétitions
    -   n : N Répétitions
    -   -1 : Répétitions Infini
-   Enregistrement (Bouton RECORD) des mouvements et clicks de la souris (droit & gauche)
-   Historique d'éxecution des macros.
-   Interuption de l'enregistrement / Execution avec ESC ou ESPACE.
-   Sauvegarde des macros dans un fichier .json

## Build

Pour build il faut executer les commandes suivantes :

> $ make

> $ ./main

## Ouvrir le projet

> ouvrir le main.exe
