// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <set>
#include<map>
#include<stdexcept>

using namespace std;

	map<string, int> prior = {
		{"+",1},{"-",1},{"*",2},{"/",2},{"^",4},
		{"sin",5},{"cos",5},{"ln",5},{"exp",5}
	};

	set<string> func = { "sin","cos","ln","exp" };

	TPostfix::TPostfix(const string& s): infix(s), postfix(""){}

	void TPostfix::ToPostfix() {
		var.clear();
		Stack<string> op;
		stringstream out;
		size_t i = 0;
		int pos = 1;

		while (i < infix.length()) {
			char c = infix[i];

			if (isspace(c)) { i++; pos++; continue; }

			if (isdigit(c) || c == '.') {
				string num = "";
				size_t startpos = pos;

				while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
					num += infix[i++];
					pos++;
				}

				if (num.empty() || num == ".") {
					throw runtime_error("error in format number in pos " + to_string(startpos));
				}

				if (num.find("..") != string::npos) {
					throw runtime_error("error in format number in pos " + to_string(startpos));
				}
				try {
					stod(num);
				}
				catch (...) {
					throw runtime_error("error in format number in pos " + to_string(startpos));
				}

				out << num << " ";
				continue;
			}


			if (isalpha(c)) {
				string name;
				while (i < infix.length() && isalpha(infix[i])) {
					name += infix[i];
					i++;
					pos++;
				}


				if (i < infix.length() && infix[i] == '(') {
					if (func.count(name)) {
						op.Push(name);
						op.Push("(");
						i++; pos++;
					}
					else {
						throw runtime_error("uxknow func' " + name + "' at position " + to_string(pos - name.length()));
					}
				}
				else {
					if (func.count(name)) throw runtime_error("func ' " + name + "' must be follow by ( pos" + to_string(pos - name.length()));
					out << name << " ";
					var.insert(name);
				}
				continue;

			}
			if (c == '(') {
				op.Push("(");
				i++, pos++;
				continue;
			}

			if (c == ')') {
				while (!op.isEmpty() && op.Top() != "(") out << op.Pop() << " ";

				if (op.isEmpty()) throw runtime_error("extra ')' " + to_string(pos));

				op.Pop();

				if (!op.isEmpty() && func.count(op.Top())) out << op.Pop() << " ";

				i++; pos++;
				continue;
			}
			if(c=='+'||c=='-'||c=='*'||c=='/' || c=='^'){
				string op_str(1, c);
				int prio = prior[op_str];
				bool right_assoc = (c == '^');

				while (!op.isEmpty() && op.Top() != "(" && (prior[op.Top()] > prio || (prior[op.Top()] == prio && !right_assoc))) {
					out << op.Pop() << " ";
				}
				op.Push(op_str);
				i++; pos++;
				continue;
			}

			throw runtime_error(" nedopustim simvol " + string(1, c) + "(pos " + to_string(pos) + ")");
		}

		while (!op.isEmpty()) {
			if (op.Top() == "(") throw runtime_error("ne hvataet )");
			out << op.Pop() << " ";
		}

		postfix = out.str();
	}

	double TPostfix::calculated(const std::map<std::string, double>& vars) const {
		Stack<double> st;
		stringstream ss(postfix);
		string tok;

		while (ss >> tok) {
			if (tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "^") {
				double b = st.Pop();
				double a = st.Pop();

				if (tok == "+") st.Push(a + b);
				else if (tok == "-") st.Push(a - b);
				else if (tok == "*") st.Push(a * b);
				else if (tok == "/") { 
					if (b == 0.0) throw runtime_error("div on 0");
					st.Push(a / b);
				}
				else if (tok == "^") st.Push(pow(a, b));
			}

			else if (func.count(tok)) {
				double x = st.Pop();

				if (tok == "sin") st.Push(sin(x*PI/180.0));
				else if (tok == "cos") st.Push(cos(x*PI/180.0));
				else if (tok == "ln") st.Push(log(x));
				else if (tok == "exp") st.Push(exp(x));
			}
			else {
				double vall;
				try {
					vall = stod(tok);
				}
				catch (const std::invalid_argument&) {
					auto it = vars.find(tok);
					if (it == vars.end()) throw std::runtime_error("no value provided for var: " + tok);
					vall = it->second;
				}
				st.Push(vall);
			}
		}
		if (st.Getsize() != 1) throw std::runtime_error("invalid expression");
		return st.Pop();
	}

	string TPostfix::GetPostfix() const { return postfix; }
