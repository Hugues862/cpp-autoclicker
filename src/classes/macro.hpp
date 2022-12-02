#ifndef MACRO_HPP_
    #define MACRO_HPP_

    #include <click.hpp>
    #include <string>
    #include <json/json.h>
    #include <fstream>
    #include <imgui.h>

    using namespace std;

    /**
     * @brief Object with control over the cursor's movement
     * 
     */
    class Macro{

        public:
            char name[64];
            bool loop;
            int delay;
            int rec_play_delay;

            vector<Click*> movePos; // Store the movement of the mouse

            /**
             * @brief Creates object while registering every mouse event in a time frame
             * 
             */
            Macro();

            Macro(const Macro &copy);

            /**
             * @brief Load a Macro object from a Json file
             * 
             * @param loader Json value of the object
             */
            Macro(Json::Value loader);

            /**
             * @brief Destroy the Macro object
             * 
             */
            ~Macro();
            
            void clearVector();

            /**
             * @brief Set the Click object in the movePos vector at a specific index
             * 
             * @param index Index of the vector
             * @param newClick New assigned Click
             */
            void setMovePos(int index, Click newClick);

            /**
             * @brief Get the Click object in the movePos vector at a specific index
             * 
             * @param index Index of the vector
             * @return Click object
             */
            Click getMovePos(int index);

            /**
             * @brief Replays the movement of the mouse registered in the vector movePos
             * 
             * @return true if replay was successful,
             * @return false if function is interrupted by the user or fails
             */
            void play();

            /**
             * @brief Loads an Macro object from a Json file
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

            void record();

    };

#endif /* !MACRO_HPP_ */