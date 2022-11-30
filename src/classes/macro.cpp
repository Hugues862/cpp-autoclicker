#include <macro.hpp>
#include <cstring>

Macro::Macro() {

    string _name = "My Macro";
    strcpy(name, _name.c_str());
    this->loop = false;
    this->delay = 0;

    
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

bool Macro::play(){

    INPUT input[this->movePos.size()] = {}; //! Not freed, possible memory leak ?
    ZeroMemory(input, sizeof(input));

    for (int i = 0; i <= (int)this->movePos.size(); i++){
        
        input[i] = this->movePos[i]->getInput();
            
        if(GetAsyncKeyState(VK_ESCAPE)){ // Escape will throw exception and in turn destroy object

            cout << "User Interruption" << endl;
            return false;

        } 
    }

    UINT sent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));

    if (sent != ARRAYSIZE(input)){
        cout << "SendInput Failed" << endl;
        return false;
    }

    return true;

}

void Macro::record(){

    // SDL_CaptureMouse(SDL_TRUE);
    // SDL_Event event;

    // int button;
    // vector<Click>::iterator index;

    this->clearVector();

    cout << "Begin Capture of cursor movement." << endl;

    this->movePos.reserve(this->movePos.size() + 1); // Allocate space to avoid exception
    this->movePos.push_back(new Click); // Add first pointer to new Click object with starting global coordinates of cursor

    while(true){

        if(GetAsyncKeyState(VK_ESCAPE)){ // Escape will throw exception and in turn destroy object

            cout << "User Interruption" << endl;
            throw exception{};

        }

        else if(GetAsyncKeyState(VK_SPACE)){ // Space will stop registering mouse movement and confirm creation of object
            
            // SDL_CaptureMouse(SDL_FALSE);
            cout << "End Capture of cursor movement." << endl;
            break;

        }

        else if(GetAsyncKeyState(WM_MOUSEMOVE)){ // Wait for Mouse Movement or Mouse Click

            this->movePos.reserve(this->movePos.size() + 1); // Allocate space to avoid exception
            this->movePos.push_back(new Click); // Add pointer to new Click object with current global coordinates of cursor and mouse button state

        }

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