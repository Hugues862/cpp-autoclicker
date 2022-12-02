#ifndef CLICK_HPP
    #define CLICK_HPP

    #include <windows.h>
    #include <iostream>
    #include <fstream>
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

            /**
             * @brief Copy constructor of a new Click object
             * 
             * @param copy Copied Click object
             */
            Click(Click& copy){
                
                this->setX(copy.getX());
                this->setY(copy.getY());

                this->event.dwFlags = copy.getInput().dwFlags;
                this->event.mouseData = copy.getInput().mouseData;

            }

            /**
             * @brief Destroy the Click object
             * 
             */
            ~Click(){

            }

            // Getters
            MOUSEINPUT getInput(){ return this->event; }
            int getX(){ return (int)this->pos.x; }
            int getY(){ return (int)this->pos.y; }

            // Setters
            void setInput(MOUSEINPUT newEvent){ this->event = newEvent; }
            void setX(int newX){ this->pos.x = newX; }
            void setY(int newY){ this->pos.y = newY; }

            /**
             * @brief Loads data from a Json Value to create a new Click object
             * 
             * @param loader Json data
             */
            void Load(Json::Value loader){

                
                this->setX(loader["pos"]["x"].asInt());
                this->setY(loader["pos"]["y"].asInt());

                this->event.dwFlags = loader["mouseEvent"]["flags"].asInt();
                this->event.mouseData = loader["mouseEvent"]["mData"].asInt();
                

            }   

            /**
             * @brief Outputs the object's data as string
             * 
             * @return string 
             */
            string Save(){

                string add;
                string json = "{"; // start of object

                json.append("\"pos\" :"); // start of obj in class

                add = "{ \"x\" : " + to_string(this->getX()) + 
                        ", \"y\" : " + to_string(this->getY()) +
                        "},";

                json.append(add);

                json.append("\"mouseEvent\" :"); // start of obj in class

                add = "{ \"flags\" : " + to_string(this->getInput().dwFlags) + 
                        ", \"mData\" : " + to_string(this->getInput().mouseData) +
                        "}";

                json.append(add);

                json.append("},"); // end of object

                return json;
            }

    };

#endif /* !CLICK_HPP */