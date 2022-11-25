#ifndef MOVE_MOUSE_HPP_
    #define MOVE_MOUSE_HPP_

    #include <point.hpp>
    #include <string>
    #include <json/json.h>
    #include <fstream>

    using namespace std;

    class moveMouse{

        protected:

            vector<Point*> movePos; // Store the movement of the mouse

        public:
            /**
             * @brief Creates object while registering every cursor position in a time frame
             * 
             */
            moveMouse();
            
            /**
             * @brief Load a moveMouse object from a Json file
             * 
             * @param loader Json value of the object
             */
            moveMouse(Json::Value loader);

            /**
             * @brief Destroy the moveMouse object
             * 
             */
            ~moveMouse();

            bool play();

            void Load(Json::Value &in); // Load data from in stream //! https://stackoverflow.com/questions/11365456/saving-and-loading-data-to-a-file-c-beginner
            Json::Value Save(Json::Value &out); // Save data with out stream //! https://stackoverflow.com/questions/32205981/reading-json-files-in-c

    };

#endif /* !MOVE_MOUSE_HPP_ */