#include <cstring>
#include <iostream>
//#include <string>
#include "Parser.h"

#include <string>
using namespace std;

void Parser::DeterminationOfPriority(string nextSymbol) //в ифе не верные условия, проверить все.
{
	/*struct priority_1
	{
		char plus {'+'};
		int priority{ 1 };
	};*/

	/*
	 (5.0+2.0^3.0-(4.0-(2.0+3.0)*2.0)-1.0)
	*/
	string inStack = m_symbolStack.Get(); // символ из вершины стека символов
	if (
		inStack == nextSymbol || // такая же операция

		strchr(inStack.c_str(), '*') != nullptr && strchr(nextSymbol.c_str(), '+') != nullptr ||
		strchr(inStack.c_str(), '*') != nullptr && strchr(nextSymbol.c_str(), '-') != nullptr ||
		strchr(inStack.c_str(), '/') != nullptr && strchr(nextSymbol.c_str(), '+') != nullptr ||
		strchr(inStack.c_str(), '/') != nullptr && strchr(nextSymbol.c_str(), '-') != nullptr ||
		strchr(inStack.c_str(), '^') != nullptr && strchr(nextSymbol.c_str(), '+') != nullptr ||
		strchr(inStack.c_str(), '^') != nullptr && strchr(nextSymbol.c_str(), '-') != nullptr ||

		strchr(inStack.c_str(), '+') != nullptr && strchr(nextSymbol.c_str(), '-') != nullptr ||
		strchr(inStack.c_str(), '-') != nullptr && strchr(nextSymbol.c_str(), '+') != nullptr ||

		strchr(inStack.c_str(), '*') != nullptr && strchr(nextSymbol.c_str(), '/') != nullptr ||
		strchr(inStack.c_str(), '*') != nullptr && strchr(nextSymbol.c_str(), '^') != nullptr ||
		strchr(inStack.c_str(), '/') != nullptr && strchr(nextSymbol.c_str(), '*') != nullptr ||
		strchr(inStack.c_str(), '/') != nullptr && strchr(nextSymbol.c_str(), '^') != nullptr ||
		strchr(inStack.c_str(), '^') != nullptr && strchr(nextSymbol.c_str(), '/') != nullptr ||
		strchr(inStack.c_str(), '^') != nullptr && strchr(nextSymbol.c_str(), '*') != nullptr

		/*inStack == '*' && nextSymbol == '+'
		inStack == '*' && nextSymbol == '-'
		inStack == '/' && nextSymbol == '+'
		inStack == '/' && nextSymbol == '-'
		inStack == '^' && nextSymbol == '+'
		inStack == '^' && nextSymbol == '-'

		inStack == '+' && nextSymbol == '-'
		inStack == '-' && nextSymbol == '+'

		inStack == '*' && nextSymbol == '/'
		inStack == '*' && nextSymbol == '^'
		inStack == '/' && nextSymbol == '*'
		inStack == '/' && nextSymbol == '^'
		inStack == '^' && nextSymbol == '/'
		inStack == '^' && nextSymbol == '*'
		*/
		)
	{
		m_priority = false;
	}
	else
		m_priority = true;

	// ASCII
	// + 43
	// - 45

	// * 42
	// / 47
	// ^ 94

	// ( 40
	// ) 41
}

void Parser::PushOutAndAction()
{
	int elemsInNumbers = m_numbersStack.GetCount(); // ТЕСТ
	string oper = m_symbolStack.Pop(); // оператор в выражении
	string second_expressionEl = to_string(m_numbersStack.Pop()); // 2 элемент выражения
	elemsInNumbers = m_numbersStack.GetCount(); // ТЕСТ
	string first_expressionEl = to_string(m_numbersStack.Pop()); // 1 элемент выражения
	elemsInNumbers = m_numbersStack.GetCount(); // ТЕСТ
	double result{ 0 };
	if (oper == "+")
		result = atof(first_expressionEl.c_str()) + atof(second_expressionEl.c_str()); // 5+8 не дает 13 !
	if (oper == "-")
		result = atof(first_expressionEl.c_str()) - atof(second_expressionEl.c_str());
	if (oper == "*")
		result = atof(first_expressionEl.c_str()) * atof(second_expressionEl.c_str());
	if (oper == "/")
		result = atof(first_expressionEl.c_str()) / atof(second_expressionEl.c_str());
	if (oper == "^")
	{
		double temp = atof(second_expressionEl.c_str());
		result = 1;
		while (temp)
		{
			result = result * atof(first_expressionEl.c_str());
			temp--;
		}
		elemsInNumbers = m_numbersStack.GetCount(); // ТЕСТ
	}
	//result = atoi(&first_expressionEl) - atoi(&second_expressionEl);

	//int elemsInNumbers = m_numbersStack.GetCount(); 
	elemsInNumbers = m_numbersStack.GetCount(); // ТЕСТ
	int elemsInSymbols = m_symbolStack.GetCount(); // ТЕСТ

	double top = m_numbersStack.Get();// ТЕСТ
	string strTop = m_symbolStack.Get();// ТЕСТ
	m_numbersStack.Push(result);
}

void Parser::ExpressionTraversal(string str)
{
	//Stack<char> m_symbolStack;
	//m_symbolStack
	string s;
	//int len = strlen(str);
	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '(':
			m_symbolStack.Push(&str[i]);
			break;
		case ')':
			s = m_symbolStack.Pop();
			if (atoi(s.c_str()) == -1)
			{
				cout << "\nПропущена открывающая скобка в позиции ";
				cout << i;
				return;
			}
			if (str[i] == ')' && s != "(")
			{
				cout << "\nНекорректная закрывающая скобка в позиции ";
				cout << i;
				return;
			}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			m_numbersStack.Push(str[i]);
			break;
		case '+':
			DeterminationOfPriority(&str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(&str[i]);
			}
			else
			{
				// выталкивание чисел и обработка выражения, закидка результатат в стек.
				PushOutAndAction();
			}
			break;
		case '-':
			DeterminationOfPriority(&str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(&str[i]);
			}
			else
			{
				while (m_priority == false) // пока m_priority выталкиваем выражения о проводим операции
				{
					// выталкивание чисел и обработка выражения, закидка результатата в стек.
					PushOutAndAction();
					DeterminationOfPriority(&str[i]); // и проверяем можем ли сделать вставку.
					if (m_priority == true)
						m_symbolStack.Push(&str[i]);
				}
			}
			break;
		case '*':
			DeterminationOfPriority(&str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(&str[i]);
			}
			else
			{
				// выталкивание чисел и обработка выражения, закидка результатат в стек.
				PushOutAndAction();
			}
			break;
		case '/':
			DeterminationOfPriority(&str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(&str[i]);
			}
			else
			{
				// выталкивание чисел и обработка выражения, закидка результатат в стек.
				PushOutAndAction();
			}
			break;
		case '^':
			DeterminationOfPriority(&str[i]);
			if (m_priority == true)
			{
				m_symbolStack.Push(&str[i]);
			}
			else
			{
				// выталкивание чисел и обработка выражения, закидка результатат в стек.
				PushOutAndAction();
			}
			break;
		}
	}
	if (!m_symbolStack.IsEmpty())
	{
		cout << "\nОтсутствует закрывающая скобка в конце выражения!";
		return;
	}
	cout << "\nСкобки расставлены верно!";
}