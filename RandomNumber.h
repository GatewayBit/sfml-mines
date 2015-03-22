/* 
 * File:   RandomNumber.h
 * Author: cujo
 *
 * Created on March 14, 2015, 2:30 PM
 */

#ifndef RANDOMNUMBER_H
#define	RANDOMNUMBER_H
#include <stdlib.h>
#include <time.h>

class RandomNumber 
{
public:
    RandomNumber();
    virtual ~RandomNumber();
    
    int GetNumber();
    int NewNumber(int start);
    int NewNumber(int start, int end);
    
private:
    int _number;
    
    int _startingNum;
    int _endingNum;
    
    
};

#endif	/* RANDOMNUMBER_H */

