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
const int y_pow = 2;
const int x_pow = 3;
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