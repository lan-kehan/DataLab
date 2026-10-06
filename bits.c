/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  // x xor y = ~x y + ~y x = ~ ( ~(~x y) ~(~y x) )
	return ~(~(~x & y) & ~(x & ~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return ~ (x + ~0) & (x >> 31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcc = src << 3;
  int dstt = dst << 3;
  int srcMask = 255 << srcc;
  int srcByte = x & srcMask;
  int dstByte = ((srcByte >> srcc) & 0xFF) << dstt;
  int dstMask = ~(255 << dstt);

  return (x & dstMask) + dstByte;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int aShift = x >> n ;
  int y = 1 << 31;
  int mask = ~((y >> n) << 1);
  return aShift & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int left = x << 4;
  int right = x >> 4;
  int mask = 240 + (240 << 8) + (240 << 16) + (240 << 24);
  return (left & mask) + (right & (~mask));
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = ((x + 1) ^ x) | x;
  int z = (y + 1) ^ y;
  return z & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int x1 = x ^ (x >> 16);
  int x2 = x1 ^ (x1 >> 8);
  int x3 = x2 ^ (x2 >> 4);
  int x4 = x3 ^ (x3 >> 2);
  int x5 = x4 ^ (x4 >> 1);

  return ~x5 & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int k = n & 31;
  int ck = (~k + 1) & 31;
  int right = x >> k;
  int left = x << ck;
  int mask = ~0 << ck; //  n 1, 32 - n 0
  return (left & mask) + (right & ~mask);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  // if n bit is 100001, x >> n + 1
  // if n bit is 0, x >> n
  // if n bit is 100000, x >> n + 1 if x >> n & 1 else x >> n

  int nbitis1 = (x << 1 >> n) & 1;
  int nbitis1andother0 = nbitis1 & !(x & ~(~0 << n >> 1));
  int nplus1bitis1 = (x >> n) & 1;

  return ((x >> n) + ((nbitis1andother0 & nplus1bitis1) | (nbitis1 & !(nbitis1andother0)))) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int xSign = (x >> 31) & 1;
  int ySign = (y >> 31) & 1;
  int diff = y + (~x) + 1; // y - x
  int diffSign = (diff >> 31) & 1;
  // if positive overflow, diff >> 1, add 0, ySign is 0, x Sign is 1, diffSign is 1
  // if negative overflow, diff >> 1, add 1, ySign is 1, x Sign is 0, diffSign is 0;
  // if no overflow, diff >> 1, no need to reverse sign bit;

  // TO ensure toward first, 
  // if diff has half, if x > y, + 1
  // which is y - x < 0, diffSign is 1 but not overflow or diffSign is 0 but overflow
  int diffHalf = diff & 1;
  int overflow = (xSign ^ ySign) & (diffSign ^ ySign);
  int greater = diffSign ^ overflow;
  int halfDiff = ((diff >> 1) ^ (overflow << 31)) + (greater & diffHalf);
  
  return x + halfDiff;  
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  // i.e. a >= x and x >= b, i.e. !(a < x) and !(x < b);
  int xSign = (x >> 31) & 1;
  int aSign = (a >> 31) & 1;
  int adiff = a + (~x) + 1; // y - x
  int adiffSign = (adiff >> 31) & 1;  
  int aoverflow = (xSign ^ aSign) & (adiffSign ^ aSign);
  int agreater = adiffSign ^ aoverflow; // x > a

  int bSign = (b >> 31) & 1;
  int bdiff = x + (~b) + 1; // x - b
  int bdiffSign = (bdiff >> 31) & 1;
  int boverflow = (bSign ^ xSign) & (bdiffSign ^ xSign);
  int bgreater = !(bdiffSign ^ boverflow); // x > b

  int xisa = !(adiff);
  int xisb = !(bdiff);

  return xisa | xisb | (agreater ^ bgreater);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int y = x << 2;
  int signx = (x >> 31) & 1;
  int notoverflow0 = !(((y >> 2) + ~x) + 1);
  int z = y + x;
  int signz = (z >> 31) & 1;
  int notoverflow1 = !(signz ^ signx);
  int notoverflow = notoverflow0 & notoverflow1;
  int tmp = (notoverflow << 31 >> 31);

  return (z & tmp) + (((1 << 31) ^ (!signx << 31 >> 31)) & ~tmp);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int tmin = 1 << 31;
    int tmax = ~tmin;

    int xsign = x >> 31;
    int ysign = y >> 31;
    int sumxy = x + y;
    int sumsign = sumxy >> 31;

    int overflow = ~(xsign ^ ysign) & (xsign ^ sumsign);
    int sumneg = sumsign ^ overflow;
    int sumpos = ~sumneg;

    int negz = ~z + 1;
    int sumlow = sumxy & tmax;

    // greater: sumxy >  INT_MAX - z
    int maxz = tmax + negz;
    int maxzsign = maxz >> 31;
    int maxdiff = (maxz & tmax) + (~sumlow) + 1;
    int lowgreater = maxdiff >> 31;

    // if sum is positive and (sumsign is 1 and maxzsign is 0 or sumsign == maxzsign and lowbits sum greater)
    int greater = sumpos & ((sumsign & !maxzsign) | (~(sumsign ^ maxzsign) & lowgreater));

    // less x + y < INT_MIN - z
    int minz = tmin + negz;
    int minzsign = minz >> 31;
    int mindiff = sumlow + (~(minz & tmax)) + 1;
    int lowless = mindiff >> 31;

    int minzero = (!minz) << 31 >> 31;

    /// if sum is neg and (min is zero or (sumsign is 0 and minzsign is 1) or samesign but lowbits sum less)
    int less = sumneg & (minzero | (~sumsign & minzsign) | (~(sumsign ^ minzsign) & lowless));

    return (greater & 1) + less;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 255;
  unsigned sig = uf & 0x7FFFFF;
  unsigned shift = 1;
  unsigned rest;
  unsigned half;

  if (exp == 255) {
    return uf;
  }
  if (exp) {
    sig = sig | 0x800000;
  } else {
    exp = 1;
  }

  sig = sig + (sig << 1);
  if (sig >= 0x2000000) {
    shift = 2;
    exp = exp + 1;
  }
  rest = sig & ((1 << shift) - 1);
  half = 1 << (shift - 1);
  sig = sig >> shift;
  if (rest > half || (rest == half && (sig & 1))) {
    sig = sig + 1;
  }
  if (sig >= 0x1000000) {
    sig = sig >> 1;
    exp = exp + 1;
  }
  if (exp >= 255) {
    return sign | 0x7F800000;
  }
  if (sig < 0x800000) {
    exp = 0;
  }
  return sign | (exp << 23) | (sig & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 255;
  unsigned shift;
  unsigned unit;
  unsigned mask;
  unsigned rest;
  unsigned half;
  unsigned rounded;


  if (exp >= 150) {
    return uf;
  }
  if (exp < 126) {
    return sign;
  }
  if (exp == 126) {
    if (uf & 0x7FFFFF) {
      return sign | 0x3F800000;
    }
    return sign;
  }
  shift = 150 - exp;
  unit = 1 << shift;
  mask = unit - 1;
  rest = uf & mask;
  half = unit >> 1;
  rounded = uf & ~mask;
  if (rest > half || (rest == half && ((uf >> shift) & 1))) {
    rounded = rounded + unit;
  }
  return rounded;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = x & 0x80000000;
  unsigned mag = x;
  unsigned scan;
  unsigned exp = 0;
  unsigned sig;
  unsigned shift;
  unsigned rest;
  unsigned half;

  if (!x) {
    return 0;
  }
  if (sign) {
    mag = ~mag + 1;
  }
  scan = mag;
  while (scan >> 1) {
    scan = scan >> 1;
    exp = exp + 1;
  }
  if (exp <= 23) {
    sig = mag << (23 - exp);
  } else {
    shift = exp - 23;
    sig = mag >> shift;
    rest = mag & ((1 << shift) - 1);
    half = 1 << (shift - 1);
    if (rest > half || (rest == half && (sig & 1))) {
      sig = sig + 1;
    }
  }
  return sign | (((exp + 126) << 23) + sig);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  // 2 bits sum -> 4 bits sum ...
  int mask16 = 255 + (255 << 8);
  int mask8 = 255 +  (255 << 16);
  int half4 = 15 | (15 << 8);
  int half2 = 51 | (51 << 8);
  int half1 = 85 | (85 << 8);
  int mask4 = half4 | (half4 << 16);
  int mask2 = half2 | (half2 << 16);
  int mask1 = half1 | (half1 << 16);

  int x1 = (x & mask1) + ((x >> 1) & mask1);
  int x2 = (x1 & mask2) + ((x1 >> 2) & mask2);
  int x3 = (x2 & mask4) + ((x2 >> 4) & mask4);
  int x4 = (x3 & mask8) + ((x3 >> 8) & mask8);

  return (x4 & mask16) + ((x4 >> 16) & mask16);
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  // reverse 16,16, 8,8,8,8 ...
  int mask16 = 255 + (255 << 8);
  int mask8 = 255 +  (255 << 16);
  int mask4 = 15 + (15 << 8);
  mask4 = mask4 + (mask4 << 16);
  int mask2 = 51 + (51 << 8);
  mask2 = mask2 + (mask2 << 16);
  int mask1 = 85 + (85 << 8);
  mask1 = mask1 + (mask1 << 16);

  int x1 = ((x & mask16) << 16) + (x >> 16 & mask16);
  int x2 = ((x1 & mask8) << 8) + (x1 >> 8 & mask8);
  int x3 = ((x2 & mask4) << 4) + (x2 >> 4 & mask4);
  int x4 = ((x3 & mask2) << 2) + (x3 >> 2 & mask2);

  return ((x4 & mask1) << 1) + (x4 >> 1 & mask1);
}
