#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main(){

    while(true){
        if(GetKeyState(VK_ESCAPE)){
            cout << "moving" << endl;
        }
        if(GetKeyState(VK_SPACE)){
            cout << "click" << endl;
            break;
        }
    }
    return 0;
}