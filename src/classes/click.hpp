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

                if (GetAsyncKeyState(VK_LBUTTON)){
                    left = true;
                    event.mi.dwFlags += MOUSEEVENTF_LEFTDOWN;
                }

                else if (!GetAsyncKeyState(VK_LBUTTON)){
                    left = false;
                    event.mi.dwFlags += MOUSEEVENTF_LEFTUP;
                }

                if (GetAsyncKeyState(VK_RBUTTON)){
                    right = true;
                    event.mi.dwFlags += MOUSEEVENTF_RIGHTDOWN;
                }

                else if (!GetAsyncKeyState(VK_RBUTTON)){
                    right = false;
                    event.mi.dwFlags += MOUSEEVENTF_RIGHTUP;
                }

                if (GetAsyncKeyState(VK_MBUTTON)){
                    mid = true;
                    event.mi.dwFlags += MOUSEEVENTF_MIDDLEDOWN;
                }

                else if (!GetAsyncKeyState(VK_MBUTTON)){
                    mid = false;
                    event.mi.dwFlags += MOUSEEVENTF_MIDDLEUP;
                }

                if (GetAsyncKeyState(VK_XBUTTON1)){
                    x1 = true;
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON1;
                }

                else if (!GetAsyncKeyState(VK_XBUTTON1)){
                    x1 = false;
                    event.mi.dwFlags += MOUSEEVENTF_XUP;
                    event.mi.mouseData += XBUTTON1;
                }

                if (GetAsyncKeyState(VK_XBUTTON2)){
                    x2 = true;
                    event.mi.dwFlags += MOUSEEVENTF_XDOWN;
                    event.mi.mouseData += XBUTTON2;
                }

                else if (!GetAsyncKeyState(VK_XBUTTON2)){
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