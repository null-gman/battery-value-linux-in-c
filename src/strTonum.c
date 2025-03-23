#include <stdio.h>
#include <string.h>
#include "strToNum.h"



static LLINT power(int num , size_t repet){
    //2^2
    long long int res = 1;
    for (size_t i = 0; i < repet; ++i) {
        res = res * num;
    }
    return res;
}

static int charToNum(char acsii)
{
    switch (acsii)
    {
        case '0':
          return 0;
        case '1':
          return 1;
        case '2':
          return 2;
        case '3':
          return 3;
        case '4':
          return 4;
        case '5':
          return 5;
        case '6':
          return 6;
        case '7':
          return 7;
        case '8':
          return 8;
        case '9':
          return 9;
        default :
          return 10; //for error code
    }
}


LLINT stringToNum(const char * stringNum)
{
    LLINT res = 0;
    //123
    size_t stringNumLen = strlen(stringNum) ;
    size_t powerOrder = stringNumLen;
    for (size_t i = 0; i < stringNumLen  ; ++i) {
        powerOrder--;
        res += charToNum(stringNum[i]) * power(10,powerOrder);

    }

    return res;
}
