#ifndef CLICK_HPP
    #define CLICK_HPP

    #include <windows.h>
    #include <iostream>
    #include <json/json.h>
    #include <vector>
    #include <SDL.h>

    using namespace std;

    /**
     * @brief Object representing a point on the screen through coordinates
     * 
     */


    class Click {

        public:
            
            MOUSEINPUT event;
            POINT pos;
            // int delay;

            /**
             * @brief Construct a new Click object with dynamic mouse event
             * 
             */
            Click(){

                GetCursorPos(&pos);
                event.mouseData = 0;
            }

            ~Click(){

            }

            // Getters
            MOUSEINPUT getInput(){ return this->event; }
            int getX(){ return (int)this->pos.x; }
            int getY(){ return (int)this->pos.y; }

            // Setters
            void getInput(MOUSEINPUT newEvent){ this->event = newEvent; }
            void setX(int newX){ this->pos.x = newX; }
            void setY(int newY){ this->pos.y = newY; }

    };

#endif /* !CLICK_HPP */