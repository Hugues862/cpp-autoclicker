#ifndef MOVE_MOUSE_HPP_
    #define MOVE_MOUSE_HPP_

    #include <point.hpp>
    #include <string>
    #include <json/json.h>
    #include <fstream>

    using namespace std;

    /**
     * @brief Object with control over the cursor's movement
     * 
     */
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
            
            /**
             * @brief Set the Point object in the movePos vector at a specific index
             * 
             * @param index Index of the vector
             * @param newPoint New assigned Point
             */
            void setMovePos(int index, Point newPoint);

            /**
             * @brief Get the Point object in the movePos vector at a specific index
             * 
             * @param index Index of the vector
             * @return Point object
             */
            Point getMovePos(int index);

            /**
             * @brief Replays the movement of the mouse registered in the vector movePos
             * 
             * @return true if replay was successful,
             * @return false if function is interrupted by the user
             */
            bool play();

            /**
             * @brief Loads an moveMouse object from a Json file
             * 
             * @param in Json file containing the object to load
             */
            void Load(Json::Value &in); // Load data from in stream //! https://stackoverflow.com/questions/11365456/saving-and-loading-data-to-a-file-c-beginner
            
            /**
             * @brief Appends object Data as Json to a Json file
             * 
             * @param out Json file that will get updated
             * @return Json::Value with the data of the object
             */
            Json::Value Save(Json::Value &out); // Save data with out stream //! https://stackoverflow.com/questions/32205981/reading-json-files-in-c

    };

#endif /* !MOVE_MOUSE_HPP_ */