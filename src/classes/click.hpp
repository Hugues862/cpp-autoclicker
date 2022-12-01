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
            
            INPUT event;
            POINT pos;
            // int delay;
            bool left, right, mid, x1, x2;

            /**
             * @brief Construct a new Click object with dynamic mouse event
             * 
             */
            Click(){
                left = false;
                right = false;
                mid = false;
                x1 = false;
                x2 = false;
                
                event.type = INPUT_MOUSE;
                event.mi.dwFlags = (MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP);
                event.mi.mouseData = (XBUTTON1, XBUTTON2);
                GetCursorPos(&pos);

            }

            ~Click(){

            }

            // Getters
            INPUT getInput(){ return this->event; }
            int getX(){ return (int)this->pos.x; }
            int getY(){ return (int)this->pos.y; }

            // Setters
            void getInput(INPUT newEvent){ this->event = newEvent; }
            void setX(int newX){ this->event.mi.dx = newX; }
            void setY(int newY){ this->event.mi.dy = newY; }

            // Set clicks on and off

            void checkLeft() {

                left = !left;
                if (left){
                    event.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN);
                    event.mi.mouseData = 0;
                }

                else {
                    event.mi.dwFlags = (MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP);
                    event.mi.mouseData = (XBUTTON1, XBUTTON2);
                }

            }

            void checkRight() {

                right = !right;
                if (right){
                    event.mi.dwFlags = (MOUSEEVENTF_RIGHTDOWN);
                    event.mi.mouseData = 0;
                }
                else {
                    event.mi.dwFlags = (MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP);
                    event.mi.mouseData = (XBUTTON1, XBUTTON2);
                }

            }

            void checkMid() {

                mid = !mid;
                if (mid){
                    event.mi.dwFlags = (MOUSEEVENTF_MIDDLEDOWN);
                    event.mi.mouseData = 0;
                }
                else {
                    event.mi.dwFlags = (MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP);
                    event.mi.mouseData = (XBUTTON1, XBUTTON2);
                }

            }

            void checkX1() {

                x1 = !x1;
                if (x1){
                    event.mi.dwFlags = (MOUSEEVENTF_XDOWN);
                    event.mi.mouseData = (XBUTTON1);
                }
                else {
                    event.mi.dwFlags = ((MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP));
                    event.mi.mouseData = (XBUTTON1, XBUTTON2);
                }

            }

            void checkX2() {

                x2 = !x2;
                if (x2){
                    event.mi.dwFlags = (MOUSEEVENTF_XDOWN);
                    event.mi.mouseData = (XBUTTON2);
                }
                else {
                    event.mi.dwFlags = ((MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_XUP, MOUSEEVENTF_XUP));
                    event.mi.mouseData = (XBUTTON1, XBUTTON2);
                }

            }
    };

#endif /* !CLICK_HPP */