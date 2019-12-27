#include <iostream>
#include "fs.hpp"
using namespace std;

#define APP "tux"
#ifndef DEBUG
#define DEBUG
#endif

int main(int argc, char *argv[])
{
    string data = file_get_contents("dat");
    cout << data.length() << endl;
    cout << "[" << data << "]" << endl;
    return 0;
}
