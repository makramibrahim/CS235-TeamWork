/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Makram Ibrahim
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include "infix.h"
using namespace std;
const string space = " ";

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Check if the input is operator
 *****************************************************/
bool operat(const char & op)
{
   //int highPriority;
  
   if(op == '*' || op == '/' || op == '+' || op == '-' || op == '^') 

    return 1;
  else 
    return 0;
}

bool operand(const char op)
{
   // check if the input is operand
    if(op >= '0' && op <= '9') return 1;
    if(op >= 'a' && op <= 'z') return 1;
    if(op >= 'A' && op <= 'Z') return 1;
    return 0;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Add weight to the operator
 *****************************************************/
int wOperator(const char op)
{
    int highOp = 0;
    switch(op)
    {
    case '+':
    case '-':
        highOp = 1;
        break;
    case '*':
    case '/':
        highOp = 2;
        break;
    case '^':
        highOp = 3;
        break;
    }
    return highOp;
}


/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation '5 + 2' into postifx '5 2 +'
 *****************************************************/
bool highOp(const char a, const char b)
{  
    int highA = wOperator(a);
    int highB = wOperator(b);
    if(a >= b) return 1;
    return 0;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation '5 + 2' into postifx '5 2 +'
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
  
   Stack<char> stack;
   string postfix = "";
    
    // keep looping until infix equation is empty
  for (int i = 0; i < infix.length(); i++) 

      if ((infix[i] == '('))
    
    {
      stack.push(infix[i]);
    }
    else if (infix[i] == ')')
    {
      while (stack.top() != '(')
      {
        postfix += stack.top();
        stack.pop();
      }
      stack.pop();
    }
    else if (operand(infix[i]))
    {
      postfix.append(space + infix[i]);
    }
    else if (operat(infix[i]))
    {
      while(!stack.empty() && !highOp(infix[i], stack.top()))
      {
        postfix += stack.top();
        stack.pop();
      }
      stack.push(infix[i]);
    }

    while (!stack.empty())
    {
      postfix.append(space + stack.top());
      stack.pop();
    }

  
   return postfix;
}


/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}


/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix '5 2 +' to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly = postfix;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
