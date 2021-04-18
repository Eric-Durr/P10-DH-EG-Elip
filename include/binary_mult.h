
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>

#pragma once

/**
 * @brief Adds two uint8_t values which expresses a byte from the LFSR, the result is returned
 * 
 * @param a 
 * @param b 
 * @return uint8_t 
 */

uint8_t byte_add(const uint8_t &a, const uint8_t &b)
{
  return a ^ b;
}

/**
 * @brief Prints the bits in the command line from the uint8_t byte value.
 * The number to print is given as argument.
 * 
 * @param a 
 */

void byte_print(uint8_t a)
{
  int i = 8;
  while (i--)
    putchar((a >> i & 1) + '0');
}

/*!
 * @brief Compact GF(2^8) multiplication function for AES
 *
 * @returns the 8 bits of the resultant multiplication between the given numbers.
 * */
uint8_t gf2n_multiply(uint8_t a, uint8_t b)
{
  uint8_t p = 0;
  uint8_t carry;
  int i;
  for (i = 0; i < 8; i++)
  {
    if (b & 1)
      p ^= a;
    carry = a & 0x80;
    a = a << 1;
    if (carry)
      a ^= 0x1b;
    b = b >> 1;
  }
  return p;
}
