#ifndef CLICK_HPP
    #define CLICK_HPP

    #include <windows.h>
    #include <iostream>
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
            // int delay;
            bool left, right, mid, x1, x2;

            /**
             * @brief Construct a new Click object with dynamic mouse event
             * 
             */
            Click(){

                event.type = MOUSE_EVENT;
                event.mi.time = 0;

                POINT pos;
                GetCursorPos(&pos);
                event.mi.dx = pos.x;
                event.mi.dx = pos.y;
                
                //! Checks for clicks

                if (HIBYTE(GetKeyState(VK_LBUTTON)) == 1){
                    left = true;
                    event.mi.dwFlags += MOUSEEVENTF_LEFTDOWN;
                }

                else if (HIBYTE(GetKeyState(VK_LBUTTON)) != 1){
                    left = false;
                    event.mi.dwFlags += MOUSEEVENTF_LEFTUP;
                }

                if (HIBYTE(GetKeyState(VK_RBUTTON)) == 1){
                    right = true;
                    event.mi.dwFlags += MOUSEEVENTF_RIGHTDOWN;
                }

                else if (HIBYTE(GetKeyState(VK_RBUTTON)) != 1){
                    right = false;
                    event.mi.dwFlags += MOUSEEVENTF_RIGHTUP;
                }

                if (HIBYTE(GetKeyState(VK_MBUTTON)) == 1){
                    mid = true;
                    event.mi.dwFlags += MOUSEEVENTF_MIDDLEDOWN;
                }

                else if (HIBYTE(GetKeyState(VK_MBUTTON)) != 1){
                    mid = false;
                    event.mi.dwFlags += MOUSEEVENTF_MIDDLEUP;
                }

                if (HIBYTE(GetKeyState(VK_XBUTTON1)) == 1){
                    x1 = true;
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON1;
                }

                else if (HIBYTE(GetKeyState(VK_XBUTTON1)) != 1){
                    x1 = false;
                    event.mi.dwFlags += MOUSEEVENTF_XUP;
                    event.mi.mouseData += XBUTTON1;
                }

                if (HIBYTE(GetKeyState(VK_XBUTTON2)) == 1){
                    x2 = true;
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON2;
                }

                else if (HIBYTE(GetKeyState(VK_XBUTTON2)) != 1){
                    x2 = false;
                    event.mi.dwFlags += MOUSEEVENTF_XUP;
                    event.mi.mouseData += XBUTTON2;
                }

            }

            // Getters
            INPUT getInput(){ return this->event; }
            int getX(){ return (int)this->event.mi.dx; }
            int getY(){ return (int)this->event.mi.dy; }

            // Setters
            void getInput(INPUT newEvent){ this->event = newEvent; }
            void setX(int newX){ this->event.mi.dx = newX; }
            void setY(int newY){ this->event.mi.dy = newY; }

            // Set clicks on and off

            void checkLeft() {

                left = !left;
                if (left){ event.mi.dwFlags += MOUSEEVENTF_LEFTDOWN; }
                else { event.mi.dwFlags -= MOUSEEVENTF_LEFTDOWN;}

            }

            void checkRight() {

                right = !right;
                if (right){ event.mi.dwFlags += MOUSEEVENTF_RIGHTDOWN; }
                else { event.mi.dwFlags -= MOUSEEVENTF_RIGHTDOWN;}

            }

            void checkMid() {

                mid = !mid;
                if (mid){ event.mi.dwFlags += MOUSEEVENTF_MIDDLEDOWN; }
                else { event.mi.dwFlags -= MOUSEEVENTF_MIDDLEDOWN;}

            }

            void checkX1() {

                x1 = !x1;
                if (x1){
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON1;
                }
                else {
                    event.mi.dwFlags -= MOUSEEVENTF_XDOWN;
                    event.mi.mouseData -= XBUTTON1;
                }

            }

            void checkX2() {

                x2 = !x2;
                if (x2){
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON2;
                }
                else {
                    event.mi.dwFlags -= MOUSEEVENTF_XDOWN;
                    event.mi.mouseData -= XBUTTON2;
                }

            }
    };

#endif /* !CLICK_HPP */