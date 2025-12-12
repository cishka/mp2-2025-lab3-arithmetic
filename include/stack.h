// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, !
// - получение количества элементов в стеке
// - очистка стека!
// при вставке в полный стек должна перевыдел€тьс€ пам€ть

#include<iostream>
#include <stdexcept>
#include <new>

template<typename T>
class Stack {
private:
	T* mem;
	int size;
	int top;
	void resize() {
		size_t newsize = (size == 0) ? 8 : size * 2;
		T* newmem = new (std::nothrow) T[newsize];
		if (!newmem) throw std::bad_alloc();
		for (size_t i = 0; i < size; ++i) {
			newmem[i] = mem[i];
		}
		delete[] mem;
		mem = newmem;
		size = newsize;
	}
public:
	Stack(): size(8), top(0) {
		mem = new(std::nothrow) T[8];
		if (!mem) throw std::bad_alloc();
	}		// создает стек с начальной емкостью 8

	explicit Stack(int sz) : size(sz), top(0) {     //создает стек заданной емкости
		if (sz <= 0) throw std::invalid_argument("the stack size must be positive");
		mem = new T[sz];
		if (!mem) throw std::bad_alloc();
	}

	~Stack() {
		delete[] mem;
		mem = nullptr;
	}

	bool isFull() const {
		return top == size;
	}

	bool isEmpty() const {
		return top == 0;
	}

	void Push(const T& val) {
		if (isFull()) resize();
		mem[top++] = val;
	}
	T Pop() {
		if (isEmpty()) throw std::out_of_range("stack is empty");
		return mem[--top];
	}
	T Top() const {
		if (isEmpty()) throw std::out_of_range("stack is empty");
		return mem[top - 1];
	}
	void Clear() { top = 0; }
	int Getsize() const {return top;}
};
