
#include <iostream>
#include <iostream>
#include <string>

/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

bool is_prime(int p)
{
  if (p == 0 || p == 1)
    return false;
  for (int i = 2; i < p; ++i)
    if (p % i == 0)
      return false;
  return true;
}

int filter(int argc, char *argv[])
{

  if (argc < 6)
  {
    std::cout << "ERROR: missing input arguments\n";
    std::cout << "USAGE: " << argv[0] << "<prime number> <a integer> <k secret> <x secret> <message number>\n";
    return 1;
  }

  /* CASES */

  return 0;
}

unsigned f_exp(unsigned x, unsigned y, unsigned mod)
{
  unsigned res = 1;
  x %= mod; // updating x
  if (x == 0)
    return 0;

  while (y > 0)
  {
    // multiply x with res when y is odd
    if (y & 1)
      res = (res * x) % mod;
    // y = y/2
    y >>= 1;
    // Change x to x^2
    x = (x * x) % mod;
  }
  return res;
}

int gcdExtended(int a, int b, int &x, int &y)
{
  if (a == 0)
  {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int gcd = gcdExtended(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return gcd;
}

unsigned mod_mult_inv(unsigned num, unsigned mod)
{
  for (unsigned x = 1; x < mod; x++)
    if (((num % mod) * (x % mod)) % mod == 1)
      return x;
  return 0;
}
