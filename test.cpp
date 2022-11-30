#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main(){

    while(true){
        if(HIBYTE(GetAsyncKeyState(VK_LBUTTON))){
            cout << "down" << endl;
        }
        if(!GetAsyncKeyState(VK_LBUTTON)){
            cout << "up" << endl;
        }
        if(GetAsyncKeyState(VK_SPACE)){
            cout << "click" << endl;
            break;
        }
    }
    return 0;
}