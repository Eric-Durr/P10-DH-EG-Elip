
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>

const std::vector<std::string> alphabet =
    {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
     "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param argc 
 * @param argv 
 * @return long 
 */

long filter(long argc, char *argv[])
{

  if (argc < 4)
  {
    std::cout << "ERROR: missing input arguments\n";
    std::cout << "USAGE: " << argv[0] << "<p> <q> <d>\n";
    return 1;
  }

  /* CASES */

  return 0;
}

unsigned pos_in_aplh(const std::string &character)
{
  long i = 0;
  for (auto element : alphabet)
  {
    if (character == element)
      return i;
    ++i;
  }
  return -1;
}

void to_upper(std::string &str)
{
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return toupper(c); });
}

long block_sz(const long &n)
{
  long j = 1;
  while (1)
  {
    if (std::pow(alphabet.size(), j) > n)
    {
      --j;
      break;
    }
    ++j;
  }
  return j;
}

std::vector<long> encode(std::string msg, const long &block_sz)
{
  std::vector<long> blocks;
  std::vector<std::string> divided_msg;

  // clean message spaces
  std::string clean_msg = "";
  for (auto element : msg)
  {
    if (element != ' ')
    {
      clean_msg += element;
    }
  }
  msg = clean_msg;

  // divide message longo block sizes:
  while (!msg.empty())
  {
    divided_msg.push_back(msg.substr(0, block_sz));
    msg.erase(0, block_sz);

    if (msg.size() < block_sz)
    {
      divided_msg.push_back(msg);
      break;
    }
  }

  // Fill uncompleted blocks
  if (divided_msg.back().size() < block_sz)
  {
    for (unsigned i = divided_msg.back().size(); i < block_sz; ++i)
    {
      divided_msg.back() += "X";
    }
  }

  for (unsigned i = 0; i < divided_msg.size(); ++i)
  {
    long block = 0;
    for (long j = block_sz - 1, k = 0; j >= 0; --j, ++k)
    {
      block += pos_in_aplh(std::string{divided_msg[i][k]}) * std::pow(alphabet.size(), j);
    }
    blocks.push_back(block);
  }
  return blocks;
}

bool is_prime(long p)
{
  if (p == 0 || p == 1)
    return false;
  for (long i = 2; i < p; ++i)
    if (p % i == 0)
      return false;
  return true;
}

long f_exp(long x, long y, long mod)
{
  long res = 1;
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

bool le_pe_test(const long &num, long tries = 1)
{
  std::srand(time(NULL));
  long a = 2 + (rand() % (num - 1));
  long e = (num - 1) / 2;

  while (tries > 0)
  {

    // calculating final value using formula
    long result = ((long)(pow(a, e))) % num;

    //if not equal, try for different base
    if ((result % num) == 1 || (result % num) == (num - 1))
    {
      a = 2 + (rand() % (num - 1));
      tries -= 1;
    }

    // else return negative
    else
      return false;
  }

  // return positive after attempting
  return true;
}

long gcd(long a, long b)
{
  long temp;
  while (1)
  {
    temp = a % b;
    if (temp == 0)
      return b;
    a = b;
    b = temp;
  }
}

long ext_gcd(long a, long b, long &x, long &y)
{
  if (a == 0) // When base is 0, the only expected result is the module
  {
    x = 0, y = 1;
    return b;
  }
  // When base case isn't trigered, the recursive function keeps calling

  long x1, y1;
  long gcd = ext_gcd(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

unsigned mod_mult_inv(long num, long mod)
{
  long x, y;
  unsigned g = ext_gcd(num, mod, x, y);
  return (g != 1) ? 0 : (x % mod + mod) % mod;
}

std::vector<long> cipher(std::vector<long> blocks, const long &e, const long &n)
{
  std::vector<long> c_blocks;
  for (unsigned i = 0; i < blocks.size(); ++i)
  {
    c_blocks.push_back(f_exp(blocks[i], e, n));
  }
  return c_blocks;
}