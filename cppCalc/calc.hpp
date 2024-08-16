#include <string>

class Calculator{
    private:
        const static int opsCount = 7;
        char ops[opsCount] = {'!','^','*','/','%','+','-'}; //all operators, in order of operations
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
        void saveToMemory(std::string expression, double answer);
        std::string viewMemory();
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
        Calculator(int memorySize = 2);
        ~Calculator();
        void printMemory();
        double lastAnswer();
        std::string lastExpression();

        double process(double a, char op, double b);
        
        double processExpression(std::string expression);
        bool validExpression(std::string expression);
        void preprocessExpression(std::string &expression);
        double convertToDouble(std::string expression);

        bool containsOperator(char c);
        bool containsOperator(std::string expression);
        bool containsParans(std::string nestedExpression);
};