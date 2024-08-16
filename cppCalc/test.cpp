#include "calc.hpp"

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <exception>

int randInt(int min, int max) {
    return ((rand() % (max - min)) + (min + 1));
}

double randDouble(double min, double max) {
    double temp = (rand() / (double)RAND_MAX) * (max - min) + min;
    return temp;
}

int main() {
    srand(time(0));
    std::cout << "Testing Calculator Class..." << std::endl;
    Calculator c;
    try {
        c.process(randDouble(-10, 10), '+', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '-', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '*', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '/', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '%', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '^', randDouble(-10, 10));
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), '!', 0);
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }
    try {
        c.process(randDouble(-10, 10), 'a', 0);
    }
    catch (std::string s) {
        std::cout << s << std::endl;
    }

    /*
    
    Current Test Cases for expression tester:

    1. (7 * (6 + 2)) - (5 * (3 - 1)) Y
    2. (8 + 2) * (5 - 3) / 2 Y
    3. ((5 + 3) * (2 + 4)) - (7 * (8 - 3)) Y
    4. 12 + (3 * (4 - 1)) - (6 / 2) Y
    5. (15 / 3) + ((6 * 2) - (9 / 3)) Y
    6. (2 * (3 + 4))^2 - (5 + (6 / 2)) Y
    7. (8 + 2) * (6 - 3) / (4 + 1) + (9 - 3 * 2) Y
    8. (10 + (6 / 2)) * (4 - 1) Y
    9. (5 * (2 + 3) - (8 / 4)) + (12 / (6 - 3)) Y
    10. (7 + (5 * (2 + 3))) / (4 - 1) Y
    11. ((15 - 3) / (6 - 2)) + (10 / 2) Y
    12. ((3 + (2 * 5)) - (4 * (6 / 2))) + 7 Y

    13. 15.75 + 8.25 - 7.5 Y
    14. 7.5 * 4.2 / 3.0 Y
    15. (12.5 + 2.5) * (10.0 / 5.0) Y
    16. 4! * 2^3 Y

    17. (((5! * 3^2) / (7 - 2)) + (8.5 * 2.5)) - (15 % 4) + 10 Y
    18. ((6! / (2^3 + 1)) * (3.5 + 4.5)) % (8 - 2) - (5^2 / 3.0) + 7.2 Y
    19. (((4! * 3^2) + (7.2 / 2.4)) - (5 % 3)) * (2.5 + 1) / 3.0 Y
    20. (((7! / (2^2 + 2)) * (5 - 2.5)) + (4^2 - 3.1)) % (9 / 3) - 6.5 Y
    21. ((5! * (2^3 + 3)) / (7 - 1) + (9.0 / 3)) % 6 - (2.5 * 4) + 8 Y
    22. (((6! / (3^2 - 1)) + (7.5 - 2.5)) * (4^2 - 2.5)) % 5 - 3.8 Y
    23. (((8! / (5^2 + 3)) * 2.5) + (6.4 - (3.0 / 2))) % 7 - (4^3 / 2.5) + 9 Y
    24. ((7! * (2^2 - 1) - (5.5 / 1.1)) + (9 % 4)) / (3.0 + 1) - 2^2 Y
    25. (((5! + 2^4) * (7.5 - 2.5)) / (8 % 3)) - (4^2 / 2.0) + 11 Y
    26. (((6! / (3^3 - 1)) + (8.2 - 2.0)) * (5^2 / 5.0)) % (7 + 1) - 3.5 Y

    27. 1 Y
    28. 1+1 Y
    29. 1+ N (good cause expression is invalid
    30. 1+1+ N (good cause expression is invalid
    31. 3 + * 5 N (good cause expression is invalid 
    */

    try{
        c.processExpression("");
    }
    catch(std::invalid_argument e){
        std::cout << "Something went wrong with the expression: " << e.what() << std::endl;
    }
    c.printMemory();
    
    return 0;
}