#ifndef CLICK_HPP
    #define CLICK_HPP

    #include <iostream>
    #include <vector>
    #include <SDL.h>

    using namespace std;

    /**
     * @brief Object representing a point on the screen through coordinates
     * 
     */
    class Click {

        protected:
            int x;
            int y;

            Uint32 button;

            int clicks = 1;
            int delay = 0;
            bool loop = false;

        public:

            /**
              * @brief Construct a new Click object with chosen X & Y pos
              * 
              * @param newX Default X position
              * @param newY Default Y position
              */
            Click(int newX, int newY){
                this->x = newX;
                this->y = newY;
            }

            /**
             * @brief Construct a new Click object with dynamic cursor position
             * 
             */
            Click(){
                this->button = SDL_GetGlobalMouseState(&this->x, &this->y);
            }

            // Getters
            int getX(){ return this->x; }
            int getY(){ return this->y; }
            int getClicks() { return this->clicks; }
            Uint32 getButton() { return this->button; }

            // Setters
            void setX(int newX){ this->x = newX; }
            void setY(int newY){ this->y = newY; }
            void setClicks(int num) { this->clicks = num; }
            void setButton(Uint32 chgButton) { this->button = chgButton; }
    };

#endif /* !CLICK_HPP */