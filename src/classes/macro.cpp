#include <macro.hpp>
#include <cstring>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

Macro::Macro() {

    string _name = "My Macro";
    strcpy(this->name, _name.c_str());
    this->loop = 0;
    this->delay = 0;
    this->rec_play_delay = 20;
    
}


Macro::Macro(const Macro& copy){
    // char *copyof = "Copy of";
    strcpy(this->name, copy.name);
    this->loop = copy.loop;
    this->delay = copy.delay;
    this->rec_play_delay = copy.rec_play_delay;


    for (int i = 0; i < (int)copy.movePos.size(); i++){

        Click *newClick = new Click((*copy.movePos[i]));
        this->movePos.push_back(newClick);
        
    }

    // SDL_Log("THIS");
    // SDL_Log("name : %s", this->name);
    // SDL_Log("loop : %d", this->loop);
    // SDL_Log("delay : %d", this->delay);
    // SDL_Log("rec_play_delay : %d", this->rec_play_delay);
    
    // SDL_Log("posx: %d", this->movePos[1]->getX());
    // SDL_Log("posy : %d", this->movePos[1]->getY());
    // // SDL_Log("FLAGS : %d", this->movePos[1]->getY());
    
    // SDL_Log("COPY");
    // SDL_Log("name : %s", copy.name);
    // SDL_Log("loop : %d", copy.loop);
    // SDL_Log("delay : %d", copy.delay);
    // SDL_Log("rec_play_delay : %d", copy.rec_play_delay);

    // SDL_Log("posx: %d", copy.movePos[1]->getX());
    // SDL_Log("posy : %d", copy.movePos[1]->getY());
    

}

Macro::~Macro(){
    this->clearVector();
}

void Macro::clearVector(){

    for (int i = 0; i < (int)this->movePos.size(); i++){
        delete this->movePos[i]; // Delete every Click object movePos is pointing to
    }

    this->movePos.clear();
}

//! Revoir
// void Macro::setMovePos(int index, Click newClick){

//     this->movePos[index] = &newClick;

// }

Click Macro::getMovePos(int index){

    return *(this->movePos[index]);

}

void Macro::play(){

    for (int rpt = 0; rpt <= loop; rpt++){


        for (int i = 0; i < (int)this->movePos.size(); i++){
            Sleep(this->rec_play_delay);
            
            SetCursorPos(this->movePos[i]->getX(), this->movePos[i]->getY());

            mouse_event(this->movePos[i]->getInput().dwFlags, 0, 0, this->movePos[i]->getInput().mouseData, 0);
                
        }

        if(GetAsyncKeyState(VK_ESCAPE)){ 

            cout << "User Interruption" << endl;
            break;

        } 

        Sleep(this->delay);
    }

    while(loop == -1){

        for (int i = 0; i < (int)this->movePos.size(); i++){
            Sleep(this->rec_play_delay);
            
            SetCursorPos(this->movePos[i]->getX(), this->movePos[i]->getY());

            mouse_event(this->movePos[i]->getInput().dwFlags, 0, 0, this->movePos[i]->getInput().mouseData, 0);
                
        }

        if(GetAsyncKeyState(VK_ESCAPE)){

            cout << "User Interruption" << endl;
            break;

        } 

        Sleep(this->delay);
    }

}

void Macro::record(){

    this->clearVector();

    cout << "Begin Capture of cursor movement." << endl;

    bool leftDown = false;
    bool rightDown = false;
    bool midDown = false;

    // this->movePos.reserve(this->movePos.size() + 1); // Allocate space to avoid exception
    this->movePos.push_back(new Click); // Add first pointer to new Click object with starting global coordinates of cursor
    (*this->movePos.back()).event.dwFlags = 0;

    while(true){

        DWORD left = 0;
        DWORD right = 0;
        DWORD mid = 0;
        
        if(GetAsyncKeyState(VK_ESCAPE)){ // Escape will throw exception and in turn destroy object

            cout << "User Interruption" << endl;
            this->clearVector();
            break;

        }

        if(GetAsyncKeyState(VK_SPACE)){ // Space will stop registering mouse movement and confirm creation of object
            
            cout << "End Capture of cursor movement." << endl;
            break;

        }
        
        if (GetAsyncKeyState(VK_LBUTTON) && leftDown == false){

            leftDown = true;
            left = MOUSEEVENTF_LEFTDOWN;
        }

        else if (!GetAsyncKeyState(VK_LBUTTON) && leftDown == true){

            leftDown = false;
            left = MOUSEEVENTF_LEFTUP;
        }

        if (GetAsyncKeyState(VK_RBUTTON) && rightDown == false){

            rightDown = true;
            right = MOUSEEVENTF_RIGHTDOWN;
            
        }

        else if (!GetAsyncKeyState(VK_RBUTTON) && rightDown == true){

            rightDown = false;
            right = MOUSEEVENTF_RIGHTUP;
            
        }

        if (GetAsyncKeyState(VK_MBUTTON) && midDown == false){

            midDown = true;
            mid = MOUSEEVENTF_MIDDLEDOWN;

        }

        else if (!GetAsyncKeyState(VK_MBUTTON) && midDown == true){

            midDown = false;
            mid = MOUSEEVENTF_MIDDLEUP;
        }

        Sleep(this->rec_play_delay);

        // this->movePos.reserve(this->movePos.size() + 1); // Allocate space to avoid exception
        this->movePos.push_back(new Click); // Add pointer to new Click object with current global coordinates of cursor and mouse button state
        (*this->movePos.back()).event.dwFlags = (left | right | mid);


    }
}

void Macro::Load(Json::Value loader){
    SDL_Log("Macro::Load(Json::Value loader)");
    int size = loader["movePos"].size();

    // this->movePos.reserve(size);

    for (int i = 0; i < size; i++){
        SDL_Log("CLick i : %d", i);
        this->movePos.push_back(new Click);
        this->movePos.back()->Load(loader["movePos"][i]);

    }

    strcpy(this->name, loader["name"].asString().c_str());
    this->loop = loader["loop"].asInt();
    this->delay = loader["delay"].asInt();
    this->rec_play_delay = loader["rpDelay"].asInt();

}

string Macro::Save(){

    int size = this->movePos.size();
    string add;

    string json = "{"; // start of object

    json.append("\"name\" :"); // start of variables in obj

    add = "\""+(string)this->name + "\",";
    json.append(add);

    json.append("\"loop\" :"); // start of variables in obj
    add = to_string(this->loop)+ ",";
    json.append(add);

    json.append("\"delay\" :"); // start of variables in obj
    add = to_string(this->delay) + ",";
    json.append(add);

    json.append("\"rpDelay\" :"); // start of variables in obj
    add = to_string(this->rec_play_delay) + ",";
    json.append(add);

    json.append("\"movePos\" : ["); // start of variables in obj

    for (int i = 0; i < size; i++){ // number of elements in vector movePos
        
        json.append(this->movePos[i]->Save());

    }
    if(size){
        json.pop_back();
    }

    json.append("]");

    json.append("},"); // end of object

    return json;
}

