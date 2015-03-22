/* 
 * File:   RandomNumber.cpp
 * Author: cujo
 * 
 * Created on March 14, 2015, 2:30 PM
 */

#include "RandomNumber.h"

RandomNumber::RandomNumber() : _startingNum(0), _endingNum(0)
{
    srand(time(NULL));
}

RandomNumber::~RandomNumber() 
{
}

int RandomNumber::GetNumber()
{
    return _number;
}

int RandomNumber::NewNumber(int start)
{
    return _number = rand() % start;
}

int RandomNumber::NewNumber(int start, int end)
{
    return _number = rand() % end + start;
}


/*
 * {
    int number;
    
    srand(time(NULL));
    
    for (int i = 0; i < 25; i++)
    {
        number = rand() % 100;
        std::cout << "Number: " << number << std::endl;
    }
    
 */