#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "mystack.h" //use my collection
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;


//functions declaration
/**
 * Implement operations betwen two numbers
 * @param a - First parameter
 * @param b - Second parameter
 * @param symbol - The sign of operation "+-^/*"
 * @return - double result of calculation
 */
double operationsBetwenNum(double firstParam, double secondParam, char symbol){
    double res;
    if(symbol == '+'){
        res = firstParam + secondParam;
    }
    if(symbol == '-'){
        res = firstParam - secondParam;
    }
    if(symbol == '*'){
        res = firstParam * secondParam;
    }
    if(symbol == '/'){
        res = firstParam / secondParam;
    }
    if(symbol == '^'){
        res = pow(firstParam, secondParam);
    }
    return res;
}

/**
 * Use when you find variables in entered formula
 * Check if letter.
 * @param ch - Char from input formula
 * @return - true its a letter
 */
bool checkSymbolIsVariable(char ch){
    return isalpha(ch);
}

bool ascii[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0, //100
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //200
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/**
 * Return true if char is euals signs not alphabet char or digit
 * @param ch - Char from input formula
 * @return - true if it is operation sign
 */
bool isOperatorSign(char ch){
    return ascii[unsigned(ch)];
}
/**
 * Make token from string using current position of "cursor"
 * Send the current cursor position, and the line from which we select token
 * @param pos - Position of cursor in string
 * @param inputFormula - User's string
 * @return - token - or its variable or its operation sign
 */
string selectTokenFromString(int pos, string inputFormula){
    string res;
    if (isOperatorSign(inputFormula[pos])){
        res = inputFormula[pos];
    }else {
        while (!isOperatorSign(inputFormula[pos])) {
            res += inputFormula[pos];
            pos++;
            if(pos == inputFormula.length()){
                break;
            }
        }
    }
    return res;
}

/**
 * Assigns a priority to operators
 * @param ch - Operator sign
 * @return - Priority of operator
 */
int setPriorityToOperator(char ch){
    int res;
    if(ch == '+' ||ch == '-'){
        res = 0;
    }
    if(ch == '*' || ch == '/'){
        res = 1;
    }
    if(ch == '^'){
        res = 2;
    }
    if(ch == '('){
        res = -1;
    }
    return res;
}

/**
 * Retrieving end result. Calculating elements of queue
 * @param postFixNotat - Queue of operators and operands in postfix notation
 * @return - Result of user's input formula
 */
double calcResultFromPostfixNotation(Queue<string> postFixNotat){
    double res;
    Vector<string> vec;
    while(!postFixNotat.isEmpty()){
        vec.add(postFixNotat.dequeue());
    }
    for(int i = 0; i < vec.size(); i++){
        if(vec.size() == 1){
            break;
        }
        string tmp = vec[i];
        if(isOperatorSign(tmp[0]) && i >= 2){
            string tok = vec[i];
            double secondOperand = atof(vec[i-1].c_str());
            double firstOperand = atof(vec[i-2].c_str());
            double calcResult =  operationsBetwenNum(firstOperand,secondOperand,tok[0]);
            string r2 = to_string(calcResult);
            vec.set(i-2, r2);
            vec.remove(i-1);
            vec.remove(i-1);
            i = 0;
        }
    }
    return res = atof(vec[0].c_str());
}
/**
 * Replase string of user input.
 * If we have one variable appearing two or more times - function
 * replace this variable automatically.
 * @param a - String - user's formula
 */
void replaceStringIfPresentVariable(string &inputFormula){
    Map<char, string> variables;
    for(int i = 0; i < inputFormula.length(); i++){ //if we have variables - ask user to enter a number and replace string
        char ch = inputFormula[i];
        if(checkSymbolIsVariable(ch)){
            if(variables.containsKey(ch)){
                inputFormula.replace(i,1,variables.get(ch));
            }else{
                cout << inputFormula << endl; //print string
                cout << "Enter " << ch;
                string repl = getLine(" - variable:");
                inputFormula.replace(i,1,repl);
                variables.add(ch, repl);
            }
        }
    }
}
/**
 * If token is operator. Compare current token with top sign
 * in stack, if sign in stack have bigger priority then put him in
 * queue, and token put in stack
 * @param operandStack - Stack of operators
 * @param postFixNotat - Queue. Postfix notation of formula
 * @param token - Token for user's string
 */
void caterTheOperator(myStack<string>& operandStack, Queue<string>& postfixNotation, string token){
    if(operandStack.isEmpty()){ //if stack is empty then we add first sign to stack
        operandStack.push(token);
    }else if(!operandStack.isEmpty()){
        if(setPriorityToOperator(token[0])/* op1 */ <= setPriorityToOperator((operandStack.peek())[0])/* op2 */){
            //compare current token with top sign in stack if sign in stack have bigger priority then put him in
            //queue, and token put in stack
            string z = operandStack.pop();
            if(z != "("){
                postfixNotation.enqueue(z);
            }
            operandStack.push(token);
            /**
             * if in stack we have more than 1 element than comparing
             * them and push some of them to queue. in this way we have
             * allways one element in stack
             */
            if(operandStack.size() >= 2){
                if(!isOperatorSign(postfixNotation.back()[0])){
                    string firstOperand = operandStack.pop();
                    string secondOperand = operandStack.pop();
                    if(setPriorityToOperator(firstOperand[0]) <= setPriorityToOperator(secondOperand[0])){
                        if(secondOperand != "(" & firstOperand != "("){
                            postfixNotation.enqueue(secondOperand);
                            operandStack.push(firstOperand);
                        }
                    }else{
                        if(secondOperand != "(" && firstOperand != "("){
                            postfixNotation.enqueue(firstOperand);
                            operandStack.push(secondOperand);
                        }
                    }
                }
            }
        }else {
            operandStack.push(token);
        }
    }
}

/**
 * On input we have a string that write user
 * This function show to user - result
 * @param inputFormula - string of user's input
 */
void retrievingResult(string &inputFormula){
    replaceStringIfPresentVariable(inputFormula);
    myStack<string> operandStack;
    Queue<string> postfixNotation;
    for(int pos = 0; pos < inputFormula.length(); pos++){
        string token;
        token = selectTokenFromString(pos, inputFormula);
        int tokenLenght = token.length();
        if(tokenLenght > 1){
            pos += tokenLenght - 1;
        }
        //if token is number then add to queue
        if(!isOperatorSign(token[0])){
            postfixNotation.enqueue(token);
        }
        if(token == "("){
            operandStack.push(token);//add "(" to stack
        }
        if(token == ")"){
            while(operandStack.peek() != "("){
                string a = operandStack.pop();
                postfixNotation.enqueue(a);
            }
            if(operandStack.peek() == "("){
                operandStack.pop();
            }
        }
        //if token is operator sign "+-/*^"
        if(isOperatorSign(token[0]) && (token != "(" && token != ")")){
            caterTheOperator(operandStack, postfixNotation, token);
        }
    }
    //add last element in stack to queue
    while(!operandStack.isEmpty()){
        string a = operandStack.pop();
        postfixNotation.enqueue(a);
    }
    double endRes = calcResultFromPostfixNotation(postfixNotation);
    cout << "RESULT = " << endRes << endl;
}

/**
 * Check if user input have right quantity of round brackets
 * @param inputFormula - string of user's input
 */
bool checkForBrackets(string &inputFormula){
    int openB = 0;
    int closeB = 0;
    for(int i = 0; i < inputFormula.length(); i++){
        char ch = inputFormula[i];
        if(ch == '('){
            openB++;
        }
        if(ch == ')'){
            closeB++;
        }
    }
    return openB == closeB;
}

/**
 * Check if we don't have two operators after each other
 * @param inputFormula - string of user's input
 * @return - true if we hawe somethilg like that "6++7"
 */
bool checkForOperators(string &inputFormula){
    bool res;
    for(int i = 0; i < inputFormula.length(); i++){
        char ch = inputFormula[i];
        char ch2 = inputFormula[i+1];
        if((isOperatorSign(ch) && (ch != '(') && (ch != ')'))&&(isOperatorSign(ch2) && (ch2 != '(') && (ch2 != ')'))){
            res = false;
            cout << "Wrong writing operators. Your formula is invalid! ";
            break;
        }else{
            res = true;
        }
    }
    return res;
}


int main(){
    while(true){
        cout << "This is a calculator!" << " You may use variables: \"a\" \"b\" \"c\"." << endl;
        string inputFormula = getLine("Enter formula:");
        if(inputFormula == "exit"){
            break;
        }
        if(checkForBrackets(inputFormula) && checkForOperators(inputFormula)){
            retrievingResult(inputFormula);
        }else{
            checkForBrackets(inputFormula) == false ? cout << "Your brackets is invalid!" << endl : cout << "" << endl; ;
        }
    }
    return 0;
}






