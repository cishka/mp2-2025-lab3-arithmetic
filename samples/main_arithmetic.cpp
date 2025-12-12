// реализация пользовательского приложения
#include"arithmetic.h"
#include <iostream>

int main() {
    std::cout << "=== ARITHMETIC EXPRESSION CALCULATOR ===\n\n";
    std::cout << "Supported operations:\n";
    std::cout << "  - Basic: +, -, *, /, ^ (power)\n";
    std::cout << "  - Functions: sin(x), cos(x), ln(x), exp(x)\n";
    std::cout << "  - Parentheses: ( )\n";
    std::cout << "  - Numbers: integers and decimals (using dot)\n\n";
    std::cout << "IMPORTANT: Arguments for sin and cos are in degrees!\n";
    std::cout << "Expression examples:\n";
    std::cout << "  2 + 3 * 4\n";
    std::cout << "  (1 + 2) * 3\n";
    std::cout << "  sin(30) + cos(60)\n";
    std::cout << "  2^3 + ln(exp(5))\n\n";

    while (true) {
        std::cout << "==========================================\n";
        std::cout << "Enter an expression (or 'exit' or 'q' to quit):\n";

        std::string input;
        std::getline(std::cin, input);

        if (input == "exit" || input == "q") {
            break;
        }

        if (input.empty()) {
            continue;
        }
        bool onlyWhitespace = true;
        for (char c : input) {
            if (!std::isspace(c)) {
                onlyWhitespace = false;
                break;
            }
        }
        if (onlyWhitespace) {
            std::cout << "ERROR: Input contains only spaces. Please enter a valid expression.\n\n";
            continue;
        }

        try {
            TPostfix calculator(input);

            calculator.ToPostfix();
            auto var_set = calculator.Getvar();
            std::map<std::string, double> values;
            for (const auto& var : var_set) {
                std::cout << "Enter value for " + var + ": ";
                double val;
                std::cin >> val;
                values[var] = val;
            }

            if (!var_set.empty()) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            double result = calculator.calculated(values);

            std::cout << "\nRESULTS:\n";
            std::cout << "  Original expression: " << calculator.GetInfix() << "\n";
            std::cout << "  Postfix notation: " << calculator.GetPostfix() << "\n";
            std::cout << "  Calculation result: " << result << "\n\n";
        }
        catch (const std::exception& e) {
            std::cout << "\nERROR: " << e.what() << "\n";
            std::cout << "Please try entering the expression again.\n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << "\nProgram terminated.\n";
    return 0;
}
