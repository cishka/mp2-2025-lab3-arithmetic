#include <gtest.h>
#include "stack.h"

// Конструкторы
TEST(StackTest, DefaultConstructorCreatesEmptyStack) {
    Stack<int> s;
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, ConstructorWithPositiveSizeCreatesEmptyStack) {
    Stack<int> s(10);
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, ConstructorWithZeroSizeThrowsException) {
    ASSERT_ANY_THROW(Stack<int>(0));
}

TEST(StackTest, ConstructorWithNegativeSizeThrowsException) {
    ASSERT_ANY_THROW(Stack<int>(-5));
}

// Основные операции
TEST(StackTest, PushIncreasesSize) {
    Stack<int> s;
    s.Push(42);
    EXPECT_EQ(s.Getsize(), 1);
}

TEST(StackTest, TopReturnsLastPushedValue) {
    Stack<int> s;
    s.Push(42);
    EXPECT_EQ(s.Top(), 42);
}

TEST(StackTest, PopReturnsLastPushedValue) {
    Stack<int> s;
    s.Push(42);
    EXPECT_EQ(s.Pop(), 42);
}

TEST(StackTest, PopDecreasesSize) {
    Stack<int> s;
    s.Push(42);
    s.Pop();
    EXPECT_TRUE(s.isEmpty());
}

// Проверка на пустоту
TEST(StackTest, IsEmptyTrueForNewStack) {
    Stack<int> s;
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, IsEmptyFalseAfterPush) {
    Stack<int> s;
    s.Push(1);
    EXPECT_FALSE(s.isEmpty());
}

TEST(StackTest, IsEmptyTrueAfterPushPop) {
    Stack<int> s;
    s.Push(1);
    s.Pop();
    EXPECT_TRUE(s.isEmpty());
}

// Исключения
TEST(StackTest, TopOnEmptyStackThrowsException) {
    Stack<int> s;
    ASSERT_ANY_THROW(s.Top());
}

TEST(StackTest, PopOnEmptyStackThrowsException) {
    Stack<int> s;
    ASSERT_ANY_THROW(s.Pop());
}

// Перевыделение памяти
TEST(StackTest, PushBeyondCapacityResizesStack) {
    Stack<int> s(2);
    s.Push(1);
    s.Push(2);
    s.Push(3); // Должно вызвать resize
    EXPECT_EQ(s.Getsize(), 3);
}

// Очистка стека (нужен метод Clear, добавим его в класс)
TEST(StackTest, ClearEmptiesStack) {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Clear();
    EXPECT_TRUE(s.isEmpty());
}

TEST(StackTest, ClearResetsSize) {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Clear();
    EXPECT_EQ(s.Getsize(), 0);
}

// Проверка isFull
TEST(StackTest, IsFullTrueWhenCapacityReached) {
    Stack<int> s(2);
    s.Push(1);
    s.Push(2);
    EXPECT_TRUE(s.isFull());
}

TEST(StackTest, IsFullFalseAfterResize) {
    Stack<int> s(2);
    s.Push(1);
    s.Push(2);
    s.Push(3); // Вызывает resize
    EXPECT_FALSE(s.isFull());
}