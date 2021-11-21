#pragma once

#ifndef math_algo_h
#define math_algo_h

namespace math_algo
{

long int factorial(long int n){
    if (n == 0) return 1;
    long int returnVal = 1;
    for (int i = 1; i <= n; i++){
        returnVal = returnVal * i;
    }
    return returnVal;
}

}
#endif