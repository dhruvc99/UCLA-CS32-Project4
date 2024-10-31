// eval.cpp

#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int precedence(const char inputOp);
string removeWhitespace(string infix);
bool isValid(string infix);
string toPostfix(string infix);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    if (isValid(infix) == false)
        return 1;
    
    postfix = toPostfix(infix);
    stack<bool> myStack;
    
    for (int i = 0; i < postfix.size(); i++)
    {
        if (islower(postfix[i]))
        {
            if (trueValues.contains(postfix[i]) == true && falseValues.contains(postfix[i]) == false)
                myStack.push(true);
            else if (trueValues.contains(postfix[i]) == false && falseValues.contains(postfix[i]) == true )
                myStack.push(false);
            else if (trueValues.contains(postfix[i]) == false && falseValues.contains(postfix[i]) == false)
                return 2;
            else
                return 3;
        }
        else
        {
            if (postfix[i] == '!')
            {
                bool p = myStack.top();
                myStack.pop();
                myStack.push(!p);
                continue;
            }
            
            bool p = myStack.top();
            myStack.pop();
            
            bool q = myStack.top();
            myStack.pop();
            
            if (postfix[i] == '&')
                myStack.push(p && q);
            else if (postfix[i] == '|')
                myStack.push(p || q);
        }
    }
    
    if (myStack.size() != 1)
        return 1;
    result = myStack.top();
    
    return 0;
}

int precedence(const char inputOp)
{
    if (inputOp == '|')
        return 1;
    else if (inputOp == '&')
        return 2;
    else if (inputOp == '!')
        return 3;
    else
        return 0;
}

string removeWhitespace(string infix)
{
    string newInfix = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
            newInfix += infix[i];
    }
    return newInfix;
}

bool isValid(string infix)
{
    infix = removeWhitespace(infix);
    if (infix == "")
        return false;
    
    // check if all characters in infix are valid
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '&' || infix[i] == '|' || infix[i] == '!' || infix[i] == '(' || infix[i] == ')' || islower(infix[i]))
            continue;
        else
            return false;
    }

    stack<char> parenStack; // to check if same number of open and close parentheses match

    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '(')
            parenStack.push(infix[i]);
        if (infix [i] == ')')
        {
            if (parenStack.empty() == true)
                return false;
            else
                parenStack.pop();
        }
    }
    
    if (parenStack.empty() == false)
        return false;
    
    // checking if invalid start or end characters
    if (infix[0] == '&' || infix[infix.size() - 1] == '&' || infix[0] == '|' || infix[infix.size() - 1] == '|')
        return false;
    
    // checking coupled ordering of characters
    for (int j = 1; j < infix.size(); j++)
    {
        if (infix[j - 1] == '!' && (infix[j] == '&' || infix[j] == '|'))
            return false;
        
        if (infix[j - 1] == '(' && (infix[j] == '|' || infix[j] == '&'))
            return false;
        
        if (infix[j - 1] == ')' && infix[j] == '!')
            return false;
        
        if ((infix[j - 1] == '|' || infix[j - 1] == '&') && (infix[j] == '&' || infix[j] == '|' || infix[j] == ')'))
                return false;
        
        if (infix[j] == '|' || infix[j] == '&' || islower(infix[j]))
        {
            if (infix[j - 1] == infix[j])
                return false;
        }
    }
            
    return true;
}

string toPostfix(string infix)
{
    string postfix = "";
    infix = removeWhitespace(infix);
    
    stack<char> operatorStack;
    
    for (int i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
        default:
            postfix += infix[i];
            break;
        case '(':
            operatorStack.push(infix[i]);
            break;
        case ')':
            while (operatorStack.top() != '(')
            {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
            break;
        case '&': case '|': case '!':
            while (operatorStack.empty() == false && operatorStack.top() != '(')
            {
                if (precedence(infix[i]) <= precedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                else
                    break;
            }
            operatorStack.push(infix[i]);
            break;
        }
    }
    
    while (operatorStack.empty() == false)
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
    return postfix;
}
