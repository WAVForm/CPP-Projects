#include <string>

class Calculator{
    private:
        double* answerMemory;
        std::string* expMemory;
        int memCapacity;
        int memSize;
        //functionality
        void resizeMemory();
        void addToMemory(std::string expression, double answer);
        void saveToMemory(double a, char op, double b, double answer);
        void saveToMemory(double a, char op, double answer);
        void saveToMemory(std::string op, double a, double answer);
        //operators
        double add(double a, double b);
        double sub(double a, double b);
        double div(double a, double b);
        double mul(double a, double b);
        double abs(double a);
        double mod(double a, double b);
        double exp(double a, double b);
        double fact(double a);
    public:
        //functionality
        Calculator(int memorySize = 2);
        ~Calculator();
        std::string viewMemory();
        double lastAnswer();
        std::string lastExpression();
        //operators
        void process(double a, char op, double b);
};