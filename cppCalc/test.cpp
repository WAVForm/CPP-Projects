#include "calc.hpp"

#include <ctime>
#include <iostream>
#include <cstdlib>

int randInt(int min, int max) {
    return ((rand() % (max - min)) + (min + 1));
}

double randDouble(double min, double max) {
    double temp = (rand() / (double)RAND_MAX) * (max-min) + min;
    return temp;
}

int main(){
    srand(time(0));
    std::cout << "Testing Calculator Class..." << std::endl;
    Calculator c;
    try {
        c.process(randDouble(-10,10), '+', randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10),'-',randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try{
        c.process(randDouble(-10,10), '*', randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10), '/', randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10), '%', randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10), '^', randDouble(-10,10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10), '!', 0);
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10,10), 'a', 0);
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    std::cout << c.viewMemory() << std::endl;
    return 0;
}