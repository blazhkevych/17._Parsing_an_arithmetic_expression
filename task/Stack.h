#pragma once

template<class T>
class stack
{
	int top; // Верхушка стека
	enum { EMPTY = -1, FULL = 1000 };
	T st[FULL];
public:
	stack();
	void push(T); // Добавление элемента в стек
	T pop(); // Выталкивание элемента из стека
	bool IsEmpty(); // Не пуст ли стек?
	bool IsFull(); // Не полон ли стек?
	int GetCount(); // Количество элементов в стеке
	T get(); // Просмотр элемента в вершине стека
	// Очистка стека
	void Clear();
};

template<class T>
stack<T>::stack()
{
	// Изначально стек пуст
	top = EMPTY;
}

template<class T>
bool stack<T>::IsEmpty()
{
	return top == EMPTY; //Стек пустой?
}

template<class T>
bool stack<T>::IsFull()
{
	return top == FULL - 1; //Стек полный?
}

template<class T>
int stack<T>::GetCount()
{
	return top + 1; //Подсчёт элементов в стеке
}

template<class T>
void stack<T>::push(T c)
{
	// Если в стеке есть место, то увеличиваем указатель
	// на вершину стека и вставляем новый элемент
	if (!IsFull())
		st[++top] = c;
}

template<class T>
T stack<T>::pop()
{
	// Если в стеке есть элементы, то возвращаем верхний и
	// уменьшаем указатель на вершину стека
	if (!IsEmpty())
		return st[top--];
	// Если в стеке элементов нет
	return -1;
}

template<class T>
T stack<T>::get()
{
	// Если в стеке есть элементы, то возвращаем верхний элемент
	if (!IsEmpty())
		return st[top];
	// Если в стеке элементов нет
	return -1;
}

template<class T>
void stack<T>::Clear()
{
	// Эффективная "очистка" стека 
	// (данные в массиве все еще существуют, 
	// но функции класса, ориентированные на работу с вершиной стека,
	// будут их игнорировать)
	top = EMPTY;
}