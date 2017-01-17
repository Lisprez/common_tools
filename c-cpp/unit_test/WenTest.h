#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>

#define TEST_CASE(NAME)																	\
    extern void TEST_CASE_FUNCTION_##NAME(void);										\
    class TEST_CASE_CLASS_##NAME														\
    {																					\
    public:																				\
        TEST_CASE_CLASS_##NAME()														\
        {																				\
            std::cout << std::setw(100) << std::left << #NAME;							\
            TEST_CASE_FUNCTION_##NAME();												\
        }																				\
    } TEST_CASE_INSTANCE_##NAME;														\
    void TEST_CASE_FUNCTION_##NAME(void)

#define TEST_ASSERT(CONDITION) do {														\
	if (!(CONDITION)) {																	\
		std::cout << std::right << std::setw(10) << "[";								\
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),						\
			FOREGROUND_INTENSITY|FOREGROUND_RED);										\
		std::cout << "Failed";															\
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),						\
			FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);		\
		std::cout << "]" << std::endl;													\
	} else {																			\
		std::cout << std::right << std::setw(10) << "[";								\
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),						\
			FOREGROUND_INTENSITY|FOREGROUND_GREEN);										\
		std::cout << "Passed";															\
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),						\
			FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);		\
		std::cout << "]" << std::endl;													\
	}																					\
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),							\
		FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);			\
} while (0)

#define TEST_PRINT(MESSAGE) do {														\
	std::cout << (MESSAGE) << std::endl;												\
} while (0)