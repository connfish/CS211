#include <stdio.h>
#include <stdlib.h>

int stringToInt(const char *str) 
{
    int result = 0;
    int i = 0;


    if (str[0] == '-') 
    {
        i = 1;
    }

    while (str[i] != '\0') 
    {
        if (str[i] >= '0' && str[i] <= '9') 
        {
            result = result * 10 + (str[i] - '0');
        } 
        else 
        {
            fprintf(stderr, "Error: Invalid input. Please provide a valid integer.\n");
            exit(1);
        }
        i++;
    }
    if (str[0] == '-') 
    {
        result = -result;
    }

    return result;
}


int isPerfect(int n)
{
    if (n == 1) return 0; 

    int sum = 1;
    for (int i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            if (i * i != n)
                sum = sum + i + n / i;
            else
                sum = sum + i;
        }
    }
    return sum == n; 
}


int power(int base, int exp) 
{
    int result = 1;
    while (exp > 0) 
    {
        result *= base;
        exp--;
    }
    return result;
}


int findMersennePrime(int perfectNumber) {
    for (int p = 2; p <= 20; p++) 
    { 
        int powM = power(2, p) - 1;
        int candidate = power(2, p - 1) * powM;

        if (candidate == perfectNumber) 
            return powM;
    }
    return -1;
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

   
    int number = stringToInt(argv[1]);

   
    if (isPerfect(number)) 
    {
        int mersennePrime = findMersennePrime(number);
        printf("%d\n", mersennePrime);
    } 
    else 
    {
        printf("-1\n");
    }

    return 0;
}