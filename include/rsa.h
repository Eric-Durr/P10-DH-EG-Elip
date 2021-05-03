
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>

const std::vector<std::string> alphabet =
    {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
     "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

unsigned pos_in_aplh(const std::string &character)
{
  int i = 0;
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

int block_sz(const int &n)
{
  int j = 1;
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

std::vector<int> encode(std::string msg, const int &block_sz)
{
  std::vector<int> blocks;
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

  // divide message into block sizes:
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

  for (int i = 0; i < divided_msg.size(); ++i)
  {
    int block = 0;
    for (int j = block_sz - 1, k = 0; j >= 0; --j, ++k)
    {
      block += pos_in_aplh(std::string{divided_msg[i][k]}) * std::pow(alphabet.size(), j);
    }
    blocks.push_back(block);
  }
  return blocks;
}

/**
 * @brief Checks the program command line input. If the input is the desired returns 0
 * and the main program can proceed.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int filter(int argc, char *argv[])
{

  if (argc < 5)
  {
    std::cout << "ERROR: missing input arguments\n";
    std::cout << "USAGE: " << argv[0] << "<plain text> <p> <q> <d>\n";
    return 1;
  }

  /* CASES */

  return 0;
}

bool is_prime(int p)
{
  if (p == 0 || p == 1)
    return false;
  for (int i = 2; i < p; ++i)
    if (p % i == 0)
      return false;
  return true;
}

int f_exp(int x, int y, int mod)
{
  int res = 1;
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

bool le_pe_test(const int &num, int tries = 1)
{
  std::srand(time(NULL));
  int a = 2 + (rand() % (num - 1));
  int e = (num - 1) / 2;

  while (tries > 0)
  {

    // calculating final value using formula
    int result = ((int)(pow(a, e))) % num;

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

int ext_gcd(int a, int b, int &x, int &y)
{
  if (a == 0) // When base is 0, the only expected result is the module
  {
    x = 0, y = 1;
    return b;
  }
  // When base case isn't trigered, the recursive function keeps calling

  int x1, y1;
  int gcd = ext_gcd(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

unsigned mod_mult_inv(int num, int mod)
{
  int x, y;
  unsigned g = ext_gcd(num, mod, x, y);
  return (g != 1) ? 0 : (x % mod + mod) % mod;
}

std::vector<int> cipher(std::vector<int> blocks, const int &e, const int &n)
{
  std::vector<int> c_blocks;
  for (unsigned i = 0; i < blocks.size(); ++i)
  {
    c_blocks.push_back(f_exp(blocks[i], e, n));
  }
  return c_blocks;
}