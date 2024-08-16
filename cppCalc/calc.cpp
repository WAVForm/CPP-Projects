#include <string>
#include <cmath>
#include <vector>
#include <exception>
#include "calc.hpp"

#include <iostream>

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
void Calculator::saveToMemory(std::string expression, double answer) {
    std::string exp = expression + '=';
    addToMemory(exp, answer);
}
std::string Calculator::viewMemory(){
    std::string output = "";
    for(int i = 0; i < memSize; i++){
        output += (std::to_string(i) + ": " + expMemory[i] + std::to_string(answerMemory[i]) + "\n");
    }
    return output;
}
void Calculator::printMemory() {
    std::cout << "Memory: " << std::endl << viewMemory() << std::endl;
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
    return std::fmod(a,b);
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
double  Calculator::process(double a, char op, double b){
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
                throw(std::invalid_argument("Error: Division by zero!"));
            }
            answer = div(a,b);
            saveToMemory(a,op,b,answer);
            break;
        }
        case '%':{
            if(b == 0){
                throw(std::invalid_argument("Error: Division by zero!"));
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
                throw(std::invalid_argument("Error: Factorials take one arguement"));
            }
            answer = fact(a);
            saveToMemory(a, op, answer);
            break;
        }
        case 'a':{
            if(b != 0){
                throw(std::invalid_argument("Error: Absolute value take one arguement"));
            }
            answer = abs(a);
            saveToMemory("abs~",a,answer);
            break;
        }
        default:{
            throw(std::invalid_argument("Operator not supported"));
            break;
        }
    }
    return answer;
}
double Calculator::lastAnswer() {
    return answerMemory[memSize];
}
std::string Calculator::lastExpression() {
    return expMemory[memSize];
}
bool Calculator::validExpression(std::string expression){
    int parans = 0;
    bool hasNums = false;
    for(char c : expression){
        if(c == '('){
            parans++;
            continue;
        }
        else if(c == ')'){
            parans--;
            continue;
        }
        else if(c >= '0' && c <= '9' || c == '.' || c == ' '){
            hasNums = true;
            continue;
        }
        else if(containsOperator(c) == true){
            //seperate so that every char doesn't get processed
            continue;
        }
        else{
            return false;
        }
    }
    if(parans == 0 && hasNums == true){
        return true;
    }
    else{
        return false;
    }
}

bool Calculator::containsOperator(char c){
    bool opFound = false;
    for(int i = 0; i < opsCount; i++){
        if(c == ops[i]){
            opFound = true;
            break;
        }
    }
    return opFound;
}

bool Calculator::containsOperator(std::string expression){
    bool opFound = false;
    for(char c : expression){
        if(containsOperator(c) == false){
            continue;
        }
        else{
            opFound = true;
            break;
        }
    }
    return opFound;
}

void Calculator::preprocessExpression(std::string &expression){
    //erase spaces
    while(expression.find(' ') != std::string::npos){
        expression.erase(expression.find(' '), 1);
    }
}

bool Calculator::containsParans(std::string nestedExpression){
    if (nestedExpression.find('(') != std::string::npos|| nestedExpression.find(')') != std::string::npos) {
        return true;
    }
    return false;
}

double Calculator::convertToDouble(std::string expression){
    //this function should only recieve numbers as strings. Convert them to doubles and return them
    double returned;
    try {
        returned = std::stod(expression);
    }
    catch (...) {
        throw(std::invalid_argument("Attempted to perform an operation on an operator. Check your expression"));
    }
    return returned;
}

double Calculator::processExpression(std::string expression){
    if(validExpression(expression) == false){
        //cannot have spaces...
        throw(std::invalid_argument("Not valid expression!"));
    }
    preprocessExpression(expression);
    //fill list with expressions and the operators seperating them
    std::string buffer;
    std::vector<std::string> expressions;
    for(int i = 0; i < expression.length(); i++){
        if(containsOperator(expression[i]) == true){
            if (buffer != "") {
                expressions.push_back(buffer);
            }
            buffer = "";
            std::string temp;
            temp += expression[i];
            expressions.push_back(temp);
        }
        else{
            buffer += expression[i];
            if(i == (expression.length()-1)){
                expressions.push_back(buffer);
                buffer = "";
            }
        }
    }

    if(expressions.size() <= 3){
        if(expressions.size() == 3){
            //there is a left, operator, and right only
            double answer;
            while(validExpression(expressions[0]) == false || validExpression(expressions[2]) == false){
                //sub expression not valid, but left and right together are. Must mean they are nested so remove parans as necessary
                if(validExpression(expressions[0]) == false){
                    expressions[0].erase(expressions[0].begin());
                }
                if(validExpression(expressions[2]) == false){
                    expressions[0].erase(expressions[2].end());
                }
            }
            double left;
            double right;
            if (expressions[0].length() != 1) {
                left = processExpression(expressions[0]);
            }
            else {
                left = convertToDouble(expressions[0]);
            }
            if (expressions[2].length() != 1) {
                right = processExpression(expressions[2]);
            }
            else {
                right = convertToDouble(expressions[2]);
            }
            answer = process(left, expressions[1][0], right);
            saveToMemory(expression, answer);
            return answer;
        }
        else if(expressions.size() == 2){
            //there is either left or right with an operator, or left and right with no operator
            if (expressions[1] == "!") {
                double num = convertToDouble(expressions[0]);
                double answer = process(num, '!', 0);
                saveToMemory(expression, answer);
                return answer;
            }
            else {
                throw(std::invalid_argument("Invalid expression, either no operator, or an operator without both operands"));
            }
        }
        else if(expressions.size() == 1){
            //there is either left, operator, or right
            //if it's not an operator return the value
            //else, throw invalid expressions
            if(containsOperator(expressions[0])){
                throw(std::invalid_argument("Operator found at expression size of 1"));
            }
            else{
                double answer = convertToDouble(expressions[0]);
                saveToMemory(expression, answer);
                return answer;
            }
        }
    }
    else{
        std::string buffer = expressions[0];
        std::vector<std::string> exps;
        int i = 0;
        while(i < expressions.size()){
            if(containsOperator(buffer) == true && buffer.length() == 1){
                exps.push_back(buffer);
                buffer = "";
            }
            else if (containsOperator(expressions[i + 1]) == true && expressions[i + 1].length() == 1 && containsParans(buffer) == false) {
                exps.push_back(buffer);
                buffer = "";
            }
            if (i + 1 < expressions.size()) {
                buffer += expressions[++i];
            }
            else {
                break;
            }
            if(validExpression(buffer) == true){
                //delete first and last parans

                exps.push_back(buffer);
                buffer = "";
                if (i + 1 < expressions.size()) {
                    buffer += expressions[++i];
                }
                else {
                    break;
                }
                
            } 
        }
        
        //process by PEMDAS
        //P's
        for (int p = 0; p < exps.size(); p++) {
            if (containsParans(exps[p])) {
                exps[p].erase(exps[p].begin());
                exps[p].erase(exps[p].end() - 1);
                double returned;
                returned = processExpression(exps[p]);
                exps[p] = std::to_string(returned); //process the expression and place it back as a string
            }
        }
        for (int o = 0; o < opsCount; o++) {
            std::string currentOp;
            currentOp += ops[o];
            for (int i = 0; i < exps.size(); i++) {
                //mul AND div
                //add AND sub
                if (exps[i] == currentOp || (exps[i] == "*" && currentOp == "/") || (exps[i] == "/" && currentOp == "*") || (exps[i] == "+" && currentOp == "-") || (exps[i] == "-" && currentOp == "+")) {
                    if (currentOp == "!") {
                        double num = convertToDouble(exps[i - 1]);
                        exps[i] = std::to_string(process(num, ops[o], 0)); //place result into where op is
                        exps.erase(exps.begin() + (i - 1)); //delete num
                    }
                    else {
                        if (i + 1 >= exps.size()) {
                            throw(std::invalid_argument("Attempting to access and operand that does not exist, check your expression"));
                        }
                        double left = convertToDouble(exps[i - 1]);
                        double right = convertToDouble(exps[i + 1]);
                        exps[i] = std::to_string(process(left, exps[i][0], right)); //place result into where op is
                        exps.erase(exps.begin() + (i - 1)); //delete left
                        exps.erase(exps.begin() + i); //delete right (since left was deleted, node moved to the left by one value)
                    }
                }
            }
        }
        double answer = convertToDouble(exps[0]);
        saveToMemory(expression, answer);
        return answer;
    }
}