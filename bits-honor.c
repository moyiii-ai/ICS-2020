/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * SRS 19307130296
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
#include "bits.h"
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Max ops: 40
 *   Rating: 4
 */
int bitReverse(int x)
{
   int t1 = 85, t2 = 51, t3 = 15, t4 = 255, t5 = 255;
   t1 = t1 | (t1 << 8);
   t1 = t1 | (t1 << 16);
   t2 = t2 | (t2 << 8);
   t2 = t2 | (t2 << 16);
   t3 = t3 | (t3 << 8);
   t3 = t3 | (t3 << 16);
   t4 = t4 | (t4 << 16);
   t5 = t5 | (t5 << 8);
   x = ((x & t5) << 16) | ((x >> 16) & t5);
   x = ((x & t4) << 8) | ((x >> 8) & t4);
   x = ((x & t3) << 4) | ((x >> 4) & t3);
   x = ((x & t2) << 2) | ((x >> 2) & t2);
   x = ((x & t1) << 1) | ((x >> 1) & t1);
   return x;
}

/*
 * mod3 - calculate x mod 3 without using %.
 *   Example: mod3(100) = 1
 *            mod3(-100) = -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int mod3(int x)
{
   int t1 = 85, t2 = 51, t3 = 15, t4 = 255, t5 = 255;
   int s1, s2, op;
   int s = ~(x >> 31) + 1;
   t1 = t1 | (t1 << 8);
   t1 = t1 | (t1 << 16);
   t2 = t2 | (t2 << 8);
   t2 = t2 | (t2 << 16);
   t3 = t3 | (t3 << 8);
   t3 = t3 | (t3 << 16);
   t4 = t4 | (t4 << 16);
   t5 = t5 | (t5 << 8);

   t1 = t1 | (t1 << 16);
   s1 = x & t1, s2 = (x >> 1) & t1;
   s1 = (s1 & t1) + ((s1 >> 1) & t1);
   s1 = (s1 & t2) + ((s1 >> 2) & t2);
   s1 = (s1 & t3) + ((s1 >> 4) & t3);
   s1 = (s1 & t4) + ((s1 >> 8) & t4);
   s1 = (s1 & t5) + ((s1 >> 16) & t5);

   s2 = (s2 & t1) + ((s2 >> 1) & t1);
   s2 = (s2 & t2) + ((s2 >> 2) & t2);
   s2 = (s2 & t3) + ((s2 >> 4) & t3);
   s2 = (s2 & t4) + ((s2 >> 8) & t4);
   s2 = (s2 & t5) + ((s2 >> 16) & t5);

   s2 = (s2 << 1) + s1;

   s1 = s2 & 3;//6 bit 46 < 64
   s2 = s2 >> 2;
   s1 = s1 + (s2 & 3);
   s2 = s2 >> 2;
   s1 = s1 + (s2 & 3);
   
   s2 = s1 & 3;//4 bit 9 < 16
   s1 = s1 >> 2;
   s2 = s2 + (s1 & 3);

   s1 = s2 & 3;//3 bit 6 < 8
   s2 = s2 >> 2;
   s1 = s1 + (s2 & 3);
   
   op = !(s1 ^ 3);
   s1 = s1 + ((~(op | (op << 1))) + 1);

   return s1 + s;
}

/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *                  for floating point argument f.
 *                  Argument is passed as unsigned int, but it is to be
 *                  interpreted as the bit-level representation of a
 *                  single-precision floating point value.
 *                  Anything out of range (including NaN and infinity) should
 *                  return 0x80000000u.
 *   Legal ops: Any integer/unsigned o(1 << 23)perations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf)
{
   int y, x, z, b, b23, tx, num;
   b23 = 1 << 23;
   b = b23 - 1;

   y = uf & (1 << 31);
   if(y)  uf = uf ^ y;

   x = uf >> 23;
   z = uf & b;
   if(!x && !z)  return 0;

   x = x - 150;
   z = z + b23;
   
   num = 0, tx = z;
   while(tx >> num)  num++;
   if(num + x > 32)  return 0x80000000u;
   if(x + num < 0)  return 0;
   if(x <= 0) z = z >> (-x);
   else  z = z << x;
   if(y)  z = -z;
   return z;
}
