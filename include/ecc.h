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
const std::string args = " <p> <a> <b> <G> <db> <da> <msg> <eg/dh> [trace]";

// Command line input filtering function
int filter(int argc, char *argv[])
{
  if (argc < 9)
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

long inv_mod(long num, long p)
{
  num = num % p;
  for (long x = 1; x < p; x++)
    if ((num * x) % p == 1)
      return x;

  return 0;
}

long neg_inv_mod(long num, long p)
{
  while (num < 0)
    num += p;
  return num % p;
}

bool equal_points(std::pair<long, long> p1, std::pair<long, long> p2)
{
  return (p1.first == p2.first) && (p1.second == p2.second);
}

std::pair<long, long> add_points(std::pair<long, long> p1, std::pair<long, long> p2, long &a, long &p)
{
  long num, den, lambda;
  bool use_negative = false;

  if (equal_points(p1, p2))
  {
    num = (3 * std::pow(p1.first, 2)) + a;
    den = 2 * p1.second;
  }
  else
  {
    num = p2.second - p1.second;
    den = p2.first - p1.first;
  }

  if (num * den < 0)
    use_negative = true;

  num = std::abs(num);
  den = std::abs(den);

  lambda = ((num % p) * inv_mod(den, p)) % p;
  if (use_negative)
    lambda = (neg_inv_mod(-1, p) % p) * lambda % p;

  long rx = std::pow(lambda, 2) - p1.first - p2.first;
  long ry = lambda * (p1.first - rx) - p1.second;

  if (rx < 0)
    rx = neg_inv_mod(rx, p);
  else
    rx = rx % p;

  if (ry < 0)
    ry = neg_inv_mod(ry, p);
  else
    ry = ry % p;

  return std::pair<long, long>{rx, ry};
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

std::pair<long, long> dh_pubkey(long d,
                                std::pair<long, long> base,
                                long &a,
                                long &p)
{
  if (d == 1)
    return base;
  else
  {
    std::pair<long, long> result = add_points(base, base, a, p);
    int counter = d - 2;
    while (counter > 0)
    {
      result = add_points(base, result, a, p);
      counter--;
    }

    return result;
  }
}

std::pair<long, long> eg_pubkey() {}