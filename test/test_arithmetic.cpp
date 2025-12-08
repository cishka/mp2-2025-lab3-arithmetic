#include <gtest.h>
#include "arithmetic.h"

// Базовые выражения
TEST(ArithmeticTest, SimpleAdditionToPostfix) {
    TPostfix expr("2+3");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "2 3 + ");
}

TEST(ArithmeticTest, SimpleAdditionCalculation) {
    TPostfix expr("2+3");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 5.0);
}

TEST(ArithmeticTest, SimpleSubtractionToPostfix) {
    TPostfix expr("5-2");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "5 2 - ");
}

TEST(ArithmeticTest, SimpleSubtractionCalculation) {
    TPostfix expr("5-2");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 3.0);
}

// Приоритет операций
TEST(ArithmeticTest, MultiplicationBeforeAdditionToPostfix) {
    TPostfix expr("2+3*4");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "2 3 4 * + ");
}

TEST(ArithmeticTest, MultiplicationBeforeAdditionCalculation) {
    TPostfix expr("2+3*4");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 14.0);
}

// Скобки
TEST(ArithmeticTest, ParenthesesChangePriorityToPostfix) {
    TPostfix expr("(2+3)*4");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "2 3 + 4 * ");
}

TEST(ArithmeticTest, ParenthesesChangePriorityCalculation) {
    TPostfix expr("(2+3)*4");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 20.0);
}

// Функции
TEST(ArithmeticTest, SinFunctionToPostfix) {
    TPostfix expr("sin(30)");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "30 sin ");
}

TEST(ArithmeticTest, SinFunctionCalculation) {
    TPostfix expr("sin(30)");
    expr.ToPostfix();
    EXPECT_NEAR(expr.calculated(), 0.5, 1e-9);
}

TEST(ArithmeticTest, CosFunctionToPostfix) {
    TPostfix expr("cos(60)");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "60 cos ");
}

TEST(ArithmeticTest, CosFunctionCalculation) {
    TPostfix expr("cos(60)");
    expr.ToPostfix();
    EXPECT_NEAR(expr.calculated(), 0.5, 1e-9);
}

// Степень
TEST(ArithmeticTest, PowerToPostfix) {
    TPostfix expr("2^3");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "2 3 ^ ");
}

TEST(ArithmeticTest, PowerCalculation) {
    TPostfix expr("2^3");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 8.0);
}

// Комплексные выражения
TEST(ArithmeticTest, ComplexExpressionToPostfix) {
    TPostfix expr("sin(30)+cos(60)*2");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "30 sin 60 cos 2 * + ");
}

TEST(ArithmeticTest, ComplexExpressionCalculation) {
    TPostfix expr("sin(30)+cos(60)*2");
    expr.ToPostfix();
    EXPECT_NEAR(expr.calculated(), 1.5, 1e-9);
}

// Исключения
TEST(ArithmeticTest, DivisionByZeroThrowsException) {
    TPostfix expr("5/0");
    expr.ToPostfix();
    ASSERT_ANY_THROW(expr.calculated());
}

TEST(ArithmeticTest, InvalidSymbolThrowsException) {
    TPostfix expr("2#3");
    ASSERT_ANY_THROW(expr.ToPostfix());
}

TEST(ArithmeticTest, UnmatchedParenthesisThrowsException) {
    TPostfix expr("(2+3");
    ASSERT_ANY_THROW(expr.ToPostfix());
}

TEST(ArithmeticTest, ExtraClosingParenthesisThrowsException) {
    TPostfix expr("2+3)");
    ASSERT_ANY_THROW(expr.ToPostfix());
}

TEST(ArithmeticTest, InvalidFunctionNameThrowsException) {
    TPostfix expr("foo(2)");
    ASSERT_ANY_THROW(expr.ToPostfix());
}

TEST(ArithmeticTest, InvalidNumberFormatThrowsException) {
    TPostfix expr("2..3");
    ASSERT_ANY_THROW(expr.ToPostfix());
}

TEST(ArithmeticTest, EmptyExpressionThrowsException) {
    TPostfix expr("");
    expr.ToPostfix();
    ASSERT_ANY_THROW(expr.calculated());
}

// Пробелы
TEST(ArithmeticTest, SpacesAreIgnoredInPostfix) {
    TPostfix expr(" 2 + 3 ");
    expr.ToPostfix();
    EXPECT_EQ(expr.GetPostfix(), "2 3 + ");
}

TEST(ArithmeticTest, SpacesAreIgnoredInCalculation) {
    TPostfix expr(" 2 + 3 ");
    expr.ToPostfix();
    EXPECT_DOUBLE_EQ(expr.calculated(), 5.0);
}

// GetInfix
TEST(ArithmeticTest, GetInfixReturnsOriginalString) {
    TPostfix expr("2+3*4");
    EXPECT_EQ(expr.GetInfix(), "2+3*4");
}