/**
 * @file elip.cpp
 * @author Eric Dürr (eric.durr.20@ull.edu.es)
 * @brief Elliptic curve criptography based on ElGamal and Diffie-Hellman algorithms.
 *          -> The Elyptic curve type is: Y^2=X^3+aX+b
 * @version 0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/ecc.h"

#include <iostream>
int main(int argc, char *argv[])
{
     if (int flag = filter(argc, argv) != 0)
     {
          return flag;
     }
     return 0;
}