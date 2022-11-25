#ifndef POINT_HPP
    #define POINT_HPP

    #include <iostream>
    #include <vector>
    #include <SDL2/SDL.h>

    using namespace std;

    /**
     * @brief Object representing a point on the screen through coordinates
     * 
     */
    class Point {

        protected:
            int x;
            int y;

        public:

            /**
              * @brief Construct a new Point object with chosen X & Y pos
              * 
              * @param newX Default X position
              * @param newY Default Y position
              */
            Point(int newX, int newY){
                this->x = newX;
                this->y = newY;
            }

            /**
             * @brief Construct a new Point object with dynamic cursor position
             * 
             */
            Point(){
                SDL_GetGlobalMouseState(&this->x, &this->y);
            }

            // Getters
            int getX(){ return this->x; }
            int getY(){ return this->y; }

            // Setters
            void setX(int newX){ this->x = newX; }
            void setY(int newY){ this->y = newY; }
    };

#endif /* !POINT_HPP */