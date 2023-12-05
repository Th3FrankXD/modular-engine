
#ifdef __linux__
    #include <dlfcn.h>
#elif _WIN32
    #include <windows.h>
#endif
#include <iostream>
#include <unordered_map>
#include <string>
#include <functions.h>

class Script {
public:
    virtual void Update() = 0;
};

typedef void (__cdecl *SETFUNCTIONS)(std::unordered_map<std::string, void*>); 
typedef std::unordered_map<std::string, Script*(*)()>(__cdecl *GETSCRIPTS)();

#ifdef __linux__
    void* hinstLib;
#elif _WIN32
    HINSTANCE hinstLib;
#endif

SETFUNCTIONS SetFunctions;
GETSCRIPTS GetScripts;

int main() {
    #ifdef __linux__
        hinstLib = dlopen("bin/debug/libScript.so", RTLD_NOW);
    #elif _WIN32
        hinstLib = LoadLibrary(TEXT("Script.dll"));
    #endif

    if (hinstLib == NULL) {
        std::cout << "failed to load dll" << std::endl;
    }

    #ifdef __linux__
        SetFunctions = (SETFUNCTIONS)dlsym(hinstLib, "SetFunctions");
        GetScripts = (GETSCRIPTS)dlsym(hinstLib, "GetScripts");
    #elif _WIN32
        SetFunctions = (SETFUNCTIONS)GetProcAddress(hinstLib, "SetFunctions");
        GetScripts = (GETSCRIPTS)GetProcAddress(hinstLib, "GetScripts");
    #endif
    
    if (SetFunctions == NULL) {
        std::cout << "failed to load init" << std::endl;
    }

    if (GetScripts == NULL) {
        std::cout << "failed to load scripts" << std::endl;
    }

    std::unordered_map<std::string, void*> funclist;
    funclist.emplace("func1", (void*)&func1);
    funclist.emplace("func2", (void*)&func2);
    funclist.emplace("func3", (void*)&func3);
    funclist.emplace("func4", (void*)&func4);
    funclist.emplace("func5", (void*)&func5);
    
    SetFunctions(funclist);

    std::unordered_map<std::string, Script*(*)()> scripts = GetScripts();
    scripts.at("Player")()->Update();
    scripts.at("Enemy")()->Update();

    #ifdef __linux__
        dlclose(hinstLib);
    #elif _WIN32
        FreeLibrary(hinstLib);
    #endif

    return 0;
}