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

            Click(Click& copy){
                
                this->setX(copy.getX());
                this->setY(copy.getY());

                this->event.dwFlags = copy.getInput().dwFlags;
                this->event.mouseData = copy.getInput().mouseData;

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

            // void Load(Json::Value &in){

            //     int size = in["movePos"].size();

            //     this->movePos.reserve(size);

            //     for (int i = 0; i < size; i++){

            //         this->movePos.push_back(new Click);
            //         this->movePos[i]->setX(in["movePos"][i]["x"].asInt());
            //         this->movePos[i]->setY(in["movePos"][i]["y"].asInt());

            //     }
            // }

            // Json::Value Save(Json::Value &out){

            //     Json::Reader read;
            //     Json::Value root;

            //     string json = "{"; // start of object

            //     json.append("\"pos\" :"); // start of obj in class

            //     string add = "{ \"x\" : " + to_string(this->getX()) + 
            //                 ", \"y\" : " + to_string(this->getY()) +
            //                 "},";
            //     json.append(add);

            //     json.append("\"mouseEvent\" :"); // start of obj in class

            //     string add = "{ \"flags\" : " + to_string(this->getX()) + 
            //                 ", \"y\" : " + to_string(this->getY()) +
            //                 "},";
            //     json.append(add);


            //     json.append("},"); // end of object

            //     read.parse(json, root, false);
            //     out.append(root);

            //     return root;
            // }

    };

#endif /* !CLICK_HPP */