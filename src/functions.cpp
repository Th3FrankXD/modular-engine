#include <functions.h>
#include <iostream>

void func1(int var) {
    std::cout << "func1 " << var << std::endl;
}

int func2(void) {
    std::cout << "func2" << std::endl;
    return 2;
}

float func3(int var1, float var2) {
    std::cout << "func3 " << var1 << " " << var2 << std::endl;
    return 4.2;
}

std::vector<int> func4(std::vector<int> vec1) {
    std::cout << "func4" << std::endl;
    std::vector<int> vec2;
    for (int i: vec1) {
        vec2.push_back(i*2);
    }
    return vec2;
}

void func5() {
    std::cout << "func5" << std::endl;
}