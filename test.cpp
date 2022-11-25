#include <iostream>
#include <string>
#include <json\json.h>

using namespace std;

int main(){

    Json::Reader read;
    Json::Value root;

    string test = "{ \"main\" : 123, \"main2\" : 123, \"main4\" : 123, },";
    
    bool parseSuccess = read.parse(test, root, false);
    

    cout << root << endl;

    bool parseSucces = read.parse(test, root, false);

    cout << endl << root << endl;

    return 0;
}