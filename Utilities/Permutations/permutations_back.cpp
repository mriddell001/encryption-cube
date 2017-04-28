/*
 * C++ Program to Generate All Permutations using BackTracking
 * Author: Manish Bhojasia
 * Source: http://www.sanfoundry.com/cpp-program-generate-permutations-using-backtracking/
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

/* swap values at two pointers */
void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* print permutations of string */
void permute(char *a, int i, int n)
{
    int j;
    if (i == n)
        cout<<a<<endl;
    else
    {
        for (j = i; j <= n; j++)
        {
            swap((a + i), (a + j));
            permute(a, i + 1, n);
            swap((a+i), (a + j));
       }
   }
}

/* Main*/
int main()
{
    char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv";
    permute(a, 0, 48);
    return 0;
}
