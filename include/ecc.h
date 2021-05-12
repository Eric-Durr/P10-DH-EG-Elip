/**
 * @file ecc.h
 * @author Eric Dürr (eric.durr.20@ull.edu.es)
 * @brief Elliptic curve criptography main program common functions
 * @version 0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <math.h>
const long y_pow = 2;
const long x_pow = 3;
const std::string args = " <p> <a> <b> <G> <db> <da> <msg> ";

// Command line input filtering function
int filter(int argc, char *argv[])
{
  if (argc < 8)
  {
    std::cout << "ERROR: wrong number of arguments\n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 1;
  }
  if (std::string{argv[4]}.front() != '[' || std::string{argv[4]}.back() != ']')
  {
    std::cout << "ERROR: given: " + std::string{argv[4]} + ", G must match euclidean space point format, such as [X,Y]\n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[1], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[1]} + ", p must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[2], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[2]} + ", a must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[3], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[3]} + ", b must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[5], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[5]} + ", da must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[6], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[6]} + ", db must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  if (!std::regex_match(argv[7], std::regex("[0-9]+")))
  {
    std::cout << "ERROR: given: " + std::string{argv[6]} + ", msg must be an integer number \n";
    std::cout << "USAGE:" + std::string{argv[0]} + args + "\n";
    return 2;
  }

  return 0;
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

std::pair<long, long> parse_point(const std::string &str)
{
  int pos = 0;
  for (pos = 0; str[pos] != ','; pos++)
    ;
  return std::pair<long, long>{std::stoi(str.substr(1, pos - 1)), std::stoi(str.substr(pos + 1, str.size() - 2))};
}

std::vector<std::pair<long, long>> extract_points(const long &p, const long &a, const long &b)
{
  std::vector<std::pair<long, long>> all_on_x;
  std::vector<std::pair<long, long>> all_on_y;
  std::vector<std::pair<long, long>> common;
  for (long i = 0; i < p; ++i)
  {
    // pushing x points values
    long cb_x = std::pow(i, x_pow);
    all_on_x.push_back(std::pair<long, long>{i, ((cb_x + a * i + b) % p)});
    // pushing y points values
    long sq_y = std::pow(i, y_pow);
    all_on_y.push_back(std::pair<long, long>{sq_y % p, i});
  }

  for (auto x_element : all_on_x)
  {
    for (auto y_element : all_on_y)
    {
      if (x_element.second == y_element.first)
        common.push_back(std::pair<long, long>{x_element.first, y_element.second});
    }
  }
  return common;
}

long great_strict_pow(const long &m)
{
  if (m == 1 || m == 0)
    return 2;
  long i = 0;
  while (1)
  {
    long current = std::pow(2, i);
    if (current > m)
      return current;

    ++i;
  }
}

std::pair<long, long> msg_2_point(const long &m, const long &h, const long M, const std::vector<std::pair<long, long>> &all_points)
{
  std::vector<std::pair<long, long>> available_points;
  long j = 0;
  bool found = false;
  while (!found) // iterate over j
  {

    long x = m * h + j; // Generate current x value

    for (auto point : all_points) // Check if x is a generated point from the curve
    {
      if (point.first == x) // When a match on x is found, the while will stop
      {
        available_points.push_back(point);
        found = true;
      }
    }
    ++j;
  }
  std::pair<long, long> msg_as_point = available_points.front();
  for (auto point : available_points) // Check for the lowest value of Y
    if (point.second <= msg_as_point.second)
      msg_as_point = point;

  return msg_as_point;
}

long first_set_bit(const long &n)
{
  int i;
  for (i = (sizeof(int) * 8) - 1; i >= 0; --i)
  {
    if (((1 << i) & n))
      return i;
  }
  return 0;
}

unsigned int to_positive_mod(int a, unsigned int m)
{
  while (a < 0)
  {
    a += m;
  }
  return a % m;
}

int ext_euclidian_alg(int a, int b, int *t, int *s)
{
  // Base Case
  if (a == 0)
  {
    *t = 0, *s = 1;
    return b;
  }

  int temp_t;
  int temp_s;
  int gcd = ext_euclidian_alg(b % a, a, &temp_t, &temp_s);

  *t = temp_s - (b / a) * temp_t;
  *s = temp_t;

  return gcd;
}

long inv_mod(long num, long p)
{
  int t, s;
  int gcd = ext_euclidian_alg(num, p, &t, &s);

  if (gcd == 1)
  {
    return to_positive_mod(t, p);
  }
  return 0;
}

std::pair<long, long> add_points(std::pair<long, long> p1, std::pair<long, long> p2, long &a, long &p)
{
  int temp = to_positive_mod(p2.first - p1.first, p);
  int slope = to_positive_mod((p2.second - p1.second) * inv_mod(temp, p), p);
  long rx = to_positive_mod((pow(slope, 2) - p1.first - p2.first), p);
  long ry = to_positive_mod((slope * (p1.first - rx) - p1.second), p);
  return std::pair<long, long>{rx, ry};
}

std::pair<long, long> double_point(std::pair<long, long> p1, long &a, long &p)
{

  int slope = (3 * pow(p1.first, 2) + a) * inv_mod(2 * p1.second, p);
  long rx = to_positive_mod(pow(slope, 2) - 2 * p1.first, p);
  long ry = to_positive_mod(slope * (p1.first - rx) - p1.second, p);
  return std::pair<long, long>{rx, ry};
}

std::pair<long, long> pubkey(long d,
                             std::pair<long, long> base,
                             long &a,
                             long &p)
{
  int i = 0;
  std::pair<long, long> pubkey = base;

  for (i = first_set_bit(d) - 1; i >= 0; --i)
  {
    pubkey = double_point(pubkey, a, p);

    if ((1 << i) & d) // if the bit at index 'i' is 1 then point addition
      pubkey = add_points(pubkey, base, a, p);
  }

  return pubkey;
}

std::pair<long, long> shkey(long d,
                            std::pair<long, long> point,
                            long &a,
                            long &p)
{

  return pubkey(d, point, a, p);
}