// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include <string>
#include "stack.h"
#include <map>;
#include <set>;


class TPostfix {
	std::string infix;
	std::string postfix;
	const double PI = acos(-1);// ~=3.14159
	std::set<std::string> var;
public:
	TPostfix(const std::string& s = "");

	void ToPostfix();
	double calculated(const std::map<std::string, double>& vars = {}) const;
	std::string GetPostfix() const;
	std::string GetInfix() const { return infix; }
	std::set<std::string> Getvar() const { return var; }
};