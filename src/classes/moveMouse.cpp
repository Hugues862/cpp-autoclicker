#include <moveMouse.hpp>

moveMouse::moveMouse(){

    // SDL_CaptureMouse(SDL_TRUE);
    SDL_Event event;

    cout << "Begin Capture of cursor movement." << endl;

    while(true){

        if (SDL_PollEvent(&event)){ // Stops creation of object
            
            if(SDLK_ESCAPE == event.key.keysym.sym){ // Escape will throw exception and in turn destroy object

                throw exception{};

            }

            else if(SDLK_SPACE == event.key.keysym.sym){ // Space will stop registering mouse movement and confirm creation of object
                
                // SDL_CaptureMouse(SDL_FALSE);
                cout << "End Capture of cursor movement." << endl;
                break;

            }

        }

        this->movePos.reserve(this->movePos.size() + 1); // Allocate space to avoid exception
        this->movePos.push_back(new Point); // Add pointer to new Point object with current global coordinates of cursor

    }

}

moveMouse::moveMouse(Json::Value loader){

    this->Load(loader);

}

moveMouse::~moveMouse(){

    for (int i = 0; i < this->movePos.size(); i++){

        delete this->movePos[i]; // Delete every Point object movePos is pointing to
    
    }

    this->movePos.clear();

}

void moveMouse::Load(Json::Value &in){

    int size = in["movePos"].size();

    this->movePos.reserve(size);

    for (int i = 0; i < size; i++){

        this->movePos.push_back(new Point);
        this->movePos[i]->setX(in["movePos"][i]["x"].asInt());
        this->movePos[i]->setY(in["movePos"][i]["y"].asInt());

    }
}

Json::Value moveMouse::Save(Json::Value &out){

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

    bool parseSuccess = read.parse(json, root, false);
    out.append(root);

    return root;
}