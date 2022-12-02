#include <macro.hpp>
#include <cstring>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

Macro::Macro() {

    string _name = "My Macro";
    strcpy(name, _name.c_str());
    this->loop = false;
    this->delay = 0;
    this->rec_play_delay = 20;


    
}

Macro::Macro(const Macro &copy){

    string _name = copy.name;
    this->loop = copy.loop;
    this->delay = copy.delay;
    this->rec_play_delay = copy.rec_play_delay;


}

Macro::Macro(Json::Value loader){

    this->Load(loader);

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
void Macro::setMovePos(int index, Click newClick){

    this->movePos[index] = &newClick;

}

Click Macro::getMovePos(int index){

    return *(this->movePos[index]);

}

void Macro::play(){

    MOUSEINPUT input;

    bool status = false;
    for (int i = 0; i < (int)this->movePos.size(); i++){
        Sleep(this->rec_play_delay);
        
        status = SetCursorPos(this->movePos[i]->getX(), this->movePos[i]->getY());

        mouse_event(this->movePos[i]->getInput().dwFlags, 0, 0, this->movePos[i]->getInput().mouseData, 0);
        // ZeroMemory(&input, sizeof(INPUT));      
        // input = this->movePos[i]->getInput();
        
        // UINT sent = SendInput(1, &input, sizeof(INPUT));

        // if (!sent){
        //     cout << "SendInput Failed" << endl;
        //     return false;
        // }
            
        if(GetAsyncKeyState(VK_ESCAPE)){ // Escape will throw exception and in turn destroy object 

            cout << "User Interruption" << endl;

        } 
    }

}

    // SetCapture(GetCapture());
    // WNDPROC Wndproc;

    // LRESULT Wndproc(HWND hWin,
    //                 UINT uMsg,
    //                 WPARAM wParam,
    //                 LPARAM lParam) {
        

void Macro::record(){

    // SDL_CaptureMouse(SDL_TRUE);
    // SDL_Event event;

    // int button;
    // vector<Click>::iterator index;

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

        SDL_Log("size : %d", this->movePos.size());

    }
}

void Macro::Load(Json::Value &in){

    int size = in["movePos"].size();

    this->movePos.reserve(size);

    for (int i = 0; i < size; i++){

        this->movePos.push_back(new Click);
        this->movePos[i]->setX(in["movePos"][i]["x"].asInt());
        this->movePos[i]->setY(in["movePos"][i]["y"].asInt());

    }
}

Json::Value Macro::Save(Json::Value &out){

    Json::Reader read;
    Json::Value root;
    int size = this->movePos.size();

    string json = "{"; // start of object

    json.append("\"movePos\" :"); // start of variables in obj

    for (int i = 0; i < size; i++){ // number of elements in vector movePos
        
        string add = "{ \"x\" : " + to_string(this->movePos[i]->getX()) + 
                      ", \"y\" : " + to_string(this->movePos[i]->getY()) +
                      "},";
        json.append(add);

    }

    json.append("},"); // end of object

    read.parse(json, root, false);
    out.append(root);

    return root;
}