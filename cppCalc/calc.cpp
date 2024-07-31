#include <string>
#include <cmath>
#include "calc.hpp"

void Calculator::resizeMemory(){
    if(memSize >= memCapacity){ //increase
        memCapacity *= 2;
        double* ansTemp = new double[memCapacity];
        std::string* expTemp = new std::string[memCapacity];
        for(int i = 0; i < memSize; i++){
            ansTemp[i] = answerMemory[i];
            expTemp[i] = expMemory[i];
        }
        delete[] answerMemory;
        delete[] expMemory;
        answerMemory = ansTemp;
        expMemory = expTemp;
    }
    else{ //decrease
        if (memSize <= 2){
            if (memCapacity > 2) {
                memCapacity = 2;
                double* ansTemp = new double[memCapacity];
                std::string* expTemp = new std::string[memCapacity];
                for (int i = 0; i < memSize; i++) {
                    ansTemp[i] = answerMemory[i];
                    expTemp[i] = expMemory[i];
                }
                delete[] answerMemory;
                delete[] expMemory;
                answerMemory = ansTemp;
                expMemory = expTemp;
            }
        }
        else {
            while (memSize < (memCapacity / 2)) {
                memCapacity /= 2;
                double* ansTemp = new double[memCapacity];
                std::string* expTemp = new std::string[memCapacity];
                for (int i = 0; i < memSize; i++) {
                    ansTemp[i] = answerMemory[i];
                    expTemp[i] = expMemory[i];
                }
                delete[] answerMemory;
                delete[] expMemory;
                answerMemory = ansTemp;
                expMemory = expTemp;
            }
        }
        
    }
}
void Calculator::addToMemory(std::string expression, double answer){
    resizeMemory();
    expMemory[memSize] = expression;
    answerMemory[memSize] = answer;
    memSize++;
}
void Calculator::saveToMemory(double a, char op, double b, double answer){
    std::string exp = std::to_string(a) + op + std::to_string(b) + '=';
    addToMemory(exp,answer);
}
void Calculator::saveToMemory(double a, char op, double answer){
    std::string exp = std::to_string(a) + op + '=';
    addToMemory(exp,answer);
}
void Calculator::saveToMemory(std::string op, double a, double answer){
    std::string exp = op + std::to_string(a) + '=';
    addToMemory(exp,answer);
}
std::string Calculator::viewMemory(){
    std::string output = "";
    for(int i = 0; i < memSize; i++){
        output += (std::to_string(i) + ": " + expMemory[i] + std::to_string(answerMemory[i]) + "\n");
    }
    return output;
}
double Calculator::add(double a, double b){
    return a + b;
}
double Calculator::sub(double a, double b){
    return a - b;
}
double Calculator::div(double a, double b){
    return a / b;
}
double Calculator::mul(double a, double b){
    return a * b;
}
double Calculator::abs(double a){
    return std::abs(a);
}
double Calculator::mod(double a, double b){
    return std::remainder(a,b);
}
double Calculator::exp(double a, double b){
    return std::pow(a,b);
}
double Calculator::fact(double a){
    return mul(a,tgamma(a));
}
Calculator::Calculator(int memorySize){
    memCapacity = memorySize;
    memSize = 0;
    answerMemory = new double[memCapacity];
    expMemory = new std::string[memCapacity];
}
Calculator::~Calculator(){
    delete[] answerMemory;
    delete[] expMemory;
}
void Calculator::process(double a, char op, double b){
    double answer;
    switch(op){
        case '+':{
            answer = add(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '-':{
            answer = sub(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '*':{
            answer = mul(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '/':{
            if(b == 0){
                throw("Error: Division by zero!");
            }
            answer = div(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '%':{
            if(b == 0){
                throw("Error: Division by zero!");
            }
            answer = mod(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '^':{
            answer = exp(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '!':{
            if(b != 0){
                throw("Error: Factorials take one arguement");
            }
            answer = fact(a);
            saveToMemory(a,op,answer);
            break;
        }
        case 'a':{
            if(b != 0){
                throw("Error: Absolute value take one arguement");
            }
            answer = abs(a);
            saveToMemory("abs",a,answer);
            break;
        }
        default:{
            throw("Operator not supported");
            break;
        }
    }
}
double Calculator::lastAnswer() {
    return answerMemory[memSize];
}
std::string Calculator::lastExpression() {
    return expMemory[memSize];
}