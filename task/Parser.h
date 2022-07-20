#pragma once
using std::string;
#include "stack.h"

class Parser
{
	//Stack<char> m_stack; // Входящая строка для обработки.
	Stack<string> m_symbolStack; // Стек для операций и скобок.
	Stack<double> m_numbersStack; // Стек для чисел.

	bool m_priority{ false }; // Отображает можем ли мы ложить в m_symbolStack следующий символ.

	void DeterminationOfPriority(string nextSymbol); // Вычисляет можем ли мы ложить в m_symbolStack следующий символ.

	void PushOutAndAction(); // Выталкиваем 2 числа из m_numbersStack, производим действие и ложим результат в m_numbersStack

public:
	void ExpressionTraversal(string str); // Обход выражения.


};