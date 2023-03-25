#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
using std::string;
using std::stod;
#include <sstream>
#include <vector>
using std::vector;



std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
    
};

vector<string> split(string expression){
    //expression.erase(expression.find_last_not_of(" ")+1);
    vector<string> list;
    string word = "";
    for (char chr : expression+" "){
        if (chr != ' ' ){
            word += chr;
        }
        else{
            list.push_back(word);
            word.clear();
        }

    }
    return list;
};
bool isRPNValid(vector<string> expressionList){
    int stackDepth = 0;
    for(string value : expressionList){
        if(value == "+" || value == "-" || value == "*" || value == "/"){
            stackDepth -=1;
        }
        else{
            stackDepth+=1;
        }
    }
    if(stackDepth == 1){
        return true;
    }
    else{
        return false;
    }
};

double Round3dp(double value){
    return (int)(value*1000.0)/1000.0;
}

double evaluateCountdown(string expression){
    vector<string> expressionList = split(expression);
    vector<double> stack(9);

    for (int i = 0; i<expressionList.size();i++){
        string item = expressionList[i];
        if(item =="+"){
            double a = stack.back();
            stack.pop_back();
            double b = stack.back();
            stack.pop_back();
            stack.push_back(Round3dp(b+a));
        }    
        else if(item =="-"){
            double a = stack.back();
            stack.pop_back();
            double b = stack.back();
            stack.pop_back();
            stack.push_back(Round3dp(b-a));
        }
        else if(item =="*"){
            double a = stack.back();
            stack.pop_back();
            double b = stack.back();
            stack.pop_back();
            stack.push_back(Round3dp(b*a));;
        }
        else if(item =="/"){
            double a = stack.back();
            stack.pop_back();
            double b = stack.back();
            stack.pop_back();
            if (a == 0){
                throw(expression);
            }
            else{
                stack.push_back(Round3dp(b/a));
            }
        }
        else{
            stack.push_back(stod(item));

        }
    }
    
    return Round3dp(stack.back());
};
string operate(const string& expression1,const string& expression2,string& op){
    return expression1 + " " + expression2 + " " + op;
}

class RPN{
private:
    string expression;
    int value;

public:
    RPN(const string& expressionIn, const int& valueIn):expression(expressionIn), value(valueIn){}
    RPN(const RPN& rhs){
        expression = rhs.expression;
        value = rhs.value;
    }
    const std::string & getExpression() const {
        return expression;
    }
    
    int getValue() const {
        return value;
    }
    void setExpression(string& expressionIn){
        expression = expressionIn;
    }
    void setValue(int& valueIn){
        value = valueIn;
    }
};


int calculate(const int& num1, const int& num2, const string& op ){
    if(op == "+"){
        return num1 + num2;
    }
    else if(op == "-"){
        return num1 - num2;
    }
    else if(op == "*"){
        return num1 * num2;
    }
    else{
        return num1 / num2;
    }
    
}
bool operationValid(const int& num1, const int& num2, const string&op){
    if (op == "+" || op == "*"){
        return true;
    }
    else if(op == "/"){
        if(num2 == 0){
            return false;
        }
        else{
            return num1 % num2 == 0;
        }
    }
    else{
        return num1 > num2;
    }
}

void recurseCountDown(vector<RPN>& solutions ,vector<string>& operators, int& ans, RPN& currentSolution,vector<string>& allOperators){
    if(currentSolution.getValue() == ans || solutions.size()<= 1){   //if we find the value or no more values left return the solution
        return;
    }
    for(int opIndex = 0; opIndex<operators.size();opIndex++){   //loop over operators
        for(int expression1Index = 0; expression1Index < solutions.size(); ++expression1Index){  //get first operand
            int expression2Index = 0;
            if(operators[opIndex] == "+" || operators[opIndex] == "*"){// + and * are commutative so we can skip some combos
                expression2Index = expression1Index;
            }
            for(;expression2Index< solutions.size(); ++expression2Index){ //get second operand
                if(expression1Index == expression2Index || !operationValid(solutions[expression1Index].getValue(),solutions[expression2Index].getValue(),operators[opIndex])){  // cant use same operand twice
                    continue;
                }
                string newExpression = operate(solutions[expression1Index].getExpression(),solutions[expression2Index].getExpression(),operators[opIndex]);
                //cout<<newExpression<<endl;
                

                
                int value = calculate(solutions[expression1Index].getValue(),solutions[expression2Index].getValue(),operators[opIndex]);
                if(abs(ans - value) < abs(ans - currentSolution.getValue())){  //found a closer solution
                    currentSolution.setValue(value);
                    currentSolution.setExpression(newExpression);
                }
                vector<RPN> newNumberExpressions = solutions;
                newNumberExpressions[expression1Index] = RPN(newExpression,value);
                newNumberExpressions.erase(newNumberExpressions.begin() + expression2Index);
                
                vector<string> newOperators = allOperators;
                if(opIndex < 2){
                    newOperators.erase(newOperators.begin()+opIndex+2);
                }
                else{
                    newOperators.erase(newOperators.begin()+opIndex-2);
                }
            
                recurseCountDown(newNumberExpressions,newOperators,ans,currentSolution,allOperators);

            }


            
        }
    }
}


CountdownSolution solveCountdownProblem(vector<int> num, int ans){
    
    vector<string> operators{"+","*","-","/"};
    vector<string> allOperators{"+","*","-","/"};
    vector<RPN> numberExpressions;
    for(int number : num){
        numberExpressions.push_back(RPN(intToString(number),number));
    }
    RPN currentSolution = RPN("",-9999);
    
    recurseCountDown(numberExpressions,operators,ans,currentSolution,allOperators);
    
    return CountdownSolution(currentSolution.getExpression(),currentSolution.getValue());


}





#endif
