// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <string>
#include "stack.h"

class TPostfix {
	std::string infix;
	std::string postfix;
	const double PI = acos(-1);// ~=3.14159
public:
	TPostfix(const std::string& s = "");

	void ToPostfix();
	double calculated() const;
	std::string GetPostfix() const;
	std::string GetInfix() const { return infix; }
};