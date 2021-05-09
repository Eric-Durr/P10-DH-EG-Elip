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

const std::string args = " <p> <a> <b> <G> <db> <da> <trace>";

// Command line input filtering function
int filter(int argc, char *argv[])
{
  if (argc < 7)
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

  return 0;
}