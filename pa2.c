/* Includes you should need */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ROUNDUP 0
#define ROUNDDOWN 1
#define ROUNDTOEVEN 2

/**
 * Part 1.1 
 * @brief You'll be converting a Binary string into it's unsigned decimal value.
 * @param input_string the binary string you'll be converting to decimal.
 * @return the converting decimal value (an unsigned long)
 */
unsigned long binary_to_unsigned_decimal(const char *input_string)
{
    /* Your Implementation */
   
    if (input_string == NULL) 
    {
        return 0;
    }

    int length = strlen(input_string); //length of input
    unsigned long decimal = 0;


    for (int i = 0; i <length; i++) 
    {
        
        if (input_string[i] != '0' && input_string[i] != '1') 
        {
            return 0;
        }
        if (input_string[i] == '1')
        {
            decimal = decimal + (unsigned long) (pow(2.0,length-i-1));
        }


        
    }

    return decimal;

}

/**
 * Part 1.2
 * @brief You'll be converting a binary string into it's decimal value using the signed magnitude representation
 * @param input_string, the binary string you'll be converting to decimal
 * @return the signed decimal value (a signed long type using signed magnitude)
 */
long binary_to_signed_magnitude_decimal(const char *input_string)
{
    /* Your Implementation */
    if (input_string == NULL)
        return 0;

    int length = strlen(input_string); 
    long decimal = 0;
    
    for (int i = 1; i <length; i++) 
    {
        
        if (input_string[i] != '0' && input_string[i] != '1') 
        {
            return 0;
        }
        if (input_string[i] == '1')
        {
            decimal = decimal + (long) (pow(2.0,length-i-1));
        }


        
    }
    if (input_string[0]=='1')
    {
        decimal = decimal*(-1);
    }
    return decimal;
}

/**
 * Part 1.3
 * @brief You'll be converting a binary string into it's decimal value using ones complement.
 * @param input_string, the binary string you'll be converting to decimal
 * @return the signed decimal value (a signed long type using ones complement)
 */
long binary_to_ones_complement_decimal(const char *input_string)
{
    /* Your implementation */
        
    if (input_string == NULL) 
        return 0;

    int length = strlen(input_string);
    if (length == 0) 
        return 0;

    int sign = (input_string[0] == '1') ? -1 : 1;
    long magnitude = binary_to_unsigned_decimal(input_string + 1);

    if (sign == -1) 
    {
        magnitude = (~magnitude) & ((1UL << (length - 1)) - 1);
    }
    return sign * magnitude;
}

/**
 * Part 1.4
 * @brief Convert a Binary string into it's decimal value using twos complement.
 * @param input_string: The string you're going to convert to decimal
 * @return the unsigned long using twos complement
 */
long binary_to_twos_complement_decimal(const char *input_string)
{
    /* Your implementation */
    if (input_string == NULL) 
        return 0;

    int length = strlen(input_string);
    if (length == 0) 
        return 0;

    if (input_string[0] == '0') 
    {
        return binary_to_unsigned_decimal(input_string);
    } 
    else 
    {
        
        long magnitude = binary_to_unsigned_decimal(input_string + 1);
        magnitude = (~magnitude + 1) & ((1UL << (length - 1)) - 1);
        return -magnitude;
    }
}

/**
 * part 2.1
 * @brief In this part, you'll be converting an unsigned decimal value into it's unsigned binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *unsigned_decimal_to_binary(unsigned long input, unsigned int numbits)
{
    /* Your implementation */
    char *binary = (char *)malloc(numbits + 1);
    if (!binary) 
        return NULL;
    binary[numbits] = '\0';

    for (int i = numbits - 1; i >= 0; i--) 
    {
        binary[i] = (input & 1) ? '1' : '0';
        input >>= 1;
    }
    return binary;
}

/**
 * part 2.2
 * @brief In this part, you'll be converting an unsigned decimal value into it's binary representation using signed magnitude
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_signed_magnitude(long input, unsigned int numbits)
{
    /* Your implementation */
    char *binary = (char *)malloc(numbits + 1);
    if (!binary) 
        return NULL;
    binary[numbits] = '\0';

    unsigned long value = (input < 0) ? -input : input;
    
    for (int i = numbits - 1; i > 0; i--) 
    {
        binary[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }

    binary[0] = (input < 0) ? '1' : '0';

    return binary;
}

/**
 * part 2.3
 * @brief In this part, you'll be converting an unsigned decimal value into it's ones complement binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_ones_complement(long input, unsigned int numbits)
{
    /* Your implementation */
    char *binary = (char *)malloc(numbits + 1);
    if (!binary) 
        return NULL;
    binary[numbits] = '\0';

    unsigned long value = (input < 0) ? -input : input;
    
    for (int i = numbits - 1; i > 0; i--) 
    {
        binary[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }

    binary[0] = (input < 0) ? '1' : '0';

    if (input < 0) 
    {
        for (int i = 1; i < numbits; i++) 
        {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
    }

    return binary;
}

/**
 * part 2.4
 * @brief In this part, you'll be converting an unsigned decimal value into it's two complement binary representation
 * @param input The decimal value you'll be converting to binary
 * @param numbits The the bitwidth of your converted value.
 * @return the binary string (you should be allocating the string on the heap!)
 */
char *signed_decimal_to_twos_complement(long input, unsigned int numbits)
{
    /* Your implementation*/
    char *binary = (char *)malloc(numbits + 1);
    if (!binary) 
        return NULL;
    binary[numbits] = '\0';

    unsigned long value = (input < 0) ? -input : input;
    
    for (int i = numbits - 1; i >= 0; i--) 
    {
        binary[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }

    if (input < 0) 
    {
        for (int i = 0; i < numbits; i++) 
        {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }
        for (int i = numbits - 1; i >= 0; i--) 
        {
            if (binary[i] == '0') 
            {
                binary[i] = '1';
                break;
            }
            binary[i] = '0';
        }
    }

    return binary;
}

/**
 * Part 3.1
 * @brief In this part, you'll be converting an ieee754 string with a specified number of exponent and mantissa bits into it's decimal value (always 1 sign bit).
 * @param input the ieee 754 string to convert into it's decimal value.
 * @param exp The number of exponent bits in the input string.
 * @param mantissa The number of mantissa bits in the input string.
 */
double ieee754_to_decimal(char *input, int exp, int mantissa)
{
   /* Your implementation */
   //if (input==NULL) 
    //return 0.0;

    int sign = (input[0] == '1') ? -1 : 1;
    int bias = (1 << (exp - 1)) - 1;

    int exponent = 0;
    for (int i = 1; i <= exp; i++) 
    {
        exponent = (exponent << 1) | (input[i] - '0');
    }

    double mantissa_value = 1.0;
    for (int i = 0; i < mantissa; i++) 
    {
        if (input[exp + 1 + i] == '1') 
        {
            mantissa_value += pow(2, -(i + 1));
        }
    }

    if (exponent == (1 << exp) - 1) 
    {  
        if (mantissa_value > 1.0) 
            return NAN;  
        return sign * INFINITY;  
    } 
    else if (exponent == 0) 
    {  
        mantissa_value -= 1.0;  
        return sign * mantissa_value * pow(2, 1 - bias);
    }

    int E = exponent - bias;
    return sign * mantissa_value * pow(2, E);
}


/**
 * part 3.2
 * @brief In this part, you'll be converting a decimal value, and converting it into it's ieee 754 representation given the number of exp, mantissa bits, and what rounding mode to use.
 * @param input The number you'll be converting into it's ieee 754 representation
 * @param exp_bits The number of exponent bits your representation should have.
 * @param mantissa_bits The number of mantissa bits your representation should have.
 * @param rounding_mode The rounding mode you should use: 0 to round up, 1 to round down, 2 for round to even.
 */
char *decimal_to_ieee754_binary(double input, int exp_bits, int mantissa_bits, int rounding_mode)//not working
{
   // printf("%d %d %d\n",ROUNDUP,ROUNDDOWN,ROUNDTOEVEN); //Demonstration on how to use macros
    /* Your implementation */
     
    char *result = (char *)malloc((1 + exp_bits + mantissa_bits + 1) * sizeof(char));
    if (result == NULL) 
        return NULL; 
     
    if (isnan(input)) // special cases
    {
         
        result[0] = '0';
        for (int i = 1; i <= exp_bits; i++) 
        {
            result[i] = '1';
        }
        result[exp_bits + 1] = '1';
        for (int i = exp_bits + 2; i < 1 + exp_bits + mantissa_bits; i++) 
        {
            result[i] = '0';
        }
        result[1 + exp_bits + mantissa_bits] = '\0';
        return result;
    }
     
    if (isinf(input)) 
    {
         
        result[0] = (input < 0) ? '1' : '0';
        for (int i = 1; i <= exp_bits; i++) 
        {
            result[i] = '1';
        }
        for (int i = exp_bits + 1; i < 1 + exp_bits + mantissa_bits; i++) 
        {
            result[i] = '0';
        }
        result[1 + exp_bits + mantissa_bits] = '\0';
        return result;
    }
     
    //handling for zero
    if (input == 0.0) 
    {
        result[0] = (signbit(input)) ? '1' : '0'; 
        for (int i = 1; i <= exp_bits + mantissa_bits; i++) 
        {
            result[i] = '0';
        }
        result[1 + exp_bits + mantissa_bits] = '\0';
        return result;
    }
     
    //getting the sign bit
    int sign = (input < 0) ? 1 : 0;
    result[0] = sign ? '1' : '0';
      
    double abs_val = fabs(input);
    int bias = (1 << (exp_bits - 1)) - 1;
    int E = 0;
    double normalized_val = abs_val;
     
     //Normalize value for 1 and 2
    if (normalized_val >= 2.0) 
    {
        
        while (normalized_val >= 2.0) {
            normalized_val /= 2.0;
            E++;
        }
    } 
    else if (normalized_val < 1.0) 
    {
        while (normalized_val < 1.0) 
        {
            normalized_val *= 2.0;
            E--;
        }
    }
     
     
     int exp_val = E + bias; //for exponent val
     
    
     if (exp_val <= 0) 
     {
        int shift = 1 - exp_val;
        exp_val = 0;
        normalized_val /= pow(2.0, shift);
    }
     
    if (exp_val >= (1 << exp_bits) - 1) 
    {
        result[0] = sign ? '1' : '0';
        for (int i = 1; i <= exp_bits; i++) 
        {
            result[i] = '1';
        }

        for (int i = exp_bits + 1; i < 1 + exp_bits + mantissa_bits; i++) 
        {
            result[i] = '0';
        }
        result[1 + exp_bits + mantissa_bits] = '\0';
        return result;
    }
    for (int i = exp_bits; i > 0; i--) //storing our exponent bits
    {
        result[i] = (exp_val & (1 << (exp_bits - i))) ? '1' : '0';
    }
     
    double frac = normalized_val;
    if (exp_val > 0) 
    { 
        frac -= 1.0;
    }
     
    char *mantissa = (char *)malloc((mantissa_bits + 3) * sizeof(char)); //for sticky bits
    if (mantissa == NULL) 
    {
        free(result);
        return NULL;
    } 
    for (int i = 0; i < mantissa_bits + 2; i++) 
    {
        frac *= 2.0;
        if (frac >= 1.0) 
        {
            mantissa[i] = '1';
            frac -= 1.0;
        } 
        else 
        {
            mantissa[i] = '0';
        }
    }
     
    //check for remainders
    char sticky = '0';
    if (frac > 0) 
    {
        sticky = '1';
    }
     
    // Apply the rounding
    char guard = (mantissa_bits > 0) ? mantissa[mantissa_bits - 1] : '0';
    char round = mantissa[mantissa_bits];
     
    for (int i = 0; i < mantissa_bits; i++) 
    {
        result[exp_bits + 1 + i] = mantissa[i];
    }
     
    int round_up = 0;
     
    if (rounding_mode == 0) 
    { // ROUNDUP
        round_up = (round == '1' || sticky == '1');
    } 
    else if (rounding_mode == 1) 
    { // ROUNDDOWN
        round_up = 0; 
    } 
    else if (rounding_mode == 2) 
    { // ROUNDTOEVEN
        if (round == '1') 
        {
            if (sticky == '1') 
            {
                round_up = 1; //round up
            } 
            else 
            {
                // round to even
                round_up = (guard == '1');
            }
         }
     }
     
    // rounding when needed
    if (round_up) 
    {
        int i = mantissa_bits - 1;
        while (i >= 0 && result[exp_bits + 1 + i] == '1') 
        {
            result[exp_bits + 1 + i] = '0';
            i--;
        }
         
        if (i >= 0) 
        {
            result[exp_bits + 1 + i] = '1';
        } 
        else 
        {
            i = exp_bits;
            int carry = 1;
             
            while (i > 0 && carry) 
            {
                if (result[i] == '1') 
                {
                    result[i] = '0';
                } 
                else 
                {
                    result[i] = '1';
                    carry = 0;
                }
                i--;
            }
             
             // Check for the exponent overflow
             if (carry) 
             {
                 
                for (int j = 1; j <= exp_bits; j++) 
                {
                    result[j] = '1';
                }
                for (int j = exp_bits + 1; j < 1 + exp_bits + mantissa_bits; j++) 
                {
                    result[j] = '0';
                }
            }
        }
    }
     
    
    result[1 + exp_bits + mantissa_bits] = '\0';
     
    free(mantissa); // and we are doneeeeeee
    return result;
}