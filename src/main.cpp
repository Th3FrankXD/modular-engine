#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <functions.h>

class Script {
public:
    virtual void Update() = 0;
};

typedef void (__cdecl *SETFUNCTIONS)(std::unordered_map<std::string, void*>); 
typedef std::unordered_map<std::string, Script*(*)()> (__cdecl *GETSCRIPTS)(); 

HINSTANCE hinstLib;
SETFUNCTIONS SetFunctions;
GETSCRIPTS GetScripts;

int main() {
    hinstLib = LoadLibrary(TEXT("Script.dll"));
    if (hinstLib == NULL) {
        std::cout << "failed to load dll" << std::endl;
    }

    SetFunctions = (SETFUNCTIONS)GetProcAddress(hinstLib, "SetFunctions");
    GetScripts = (GETSCRIPTS)GetProcAddress(hinstLib, "GetScripts");

    if (SetFunctions == NULL) {
        std::cout << "failed to load init" << std::endl;
    }

    if (GetScripts == NULL) {
        std::cout << "failed to load scripts" << std::endl;
    }

    std::unordered_map<std::string, void*> funclist;
    funclist.emplace("func1", (void*)func1);
    funclist.emplace("func2", (void*)func2);
    funclist.emplace("func3", (void*)func3);
    funclist.emplace("func4", (void*)func4);
    funclist.emplace("func5", (void*)func5);

    printf("%p, %p\n", func1, &func1);

    SetFunctions(funclist);

    std::unordered_map<std::string, Script*(*)()> scripts = GetScripts();
    scripts.at("Player")()->Update();
    scripts.at("Enemy")()->Update();

    printf("%p, %p\n", func1, &func1);

    FreeLibrary(hinstLib);

    return 0;
}