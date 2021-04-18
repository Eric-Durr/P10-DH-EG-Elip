
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdint.h>
#include "s_box.h"

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

  if (argc < 4)
  {
    std::cout << "ERROR: missing input arguments\n";
    std::cout << "USAGE: " << argv[0] << "<hex_IV_grid_string> <hex_key_grid_string> <hex_input_grid_string_1> <hex_input_grid_string_2> ... [trace]\n";
    return 1;
  }
  if (std::string{argv[2]}.size() != 32)
  {
    std::cout << "ERROR: wrong IV string , must contain 16 hex numbers\n";
    std::cout << "USAGE: " << argv[0] << " <hex_IV_grid_string>  <hex_key_grid_string> <hex_input_grid_string_1> <hex_input_grid_string_2> ...  [trace]\n";
    return 2;
  }
  if (std::string{argv[3]}.size() != 32)
  {
    std::cout << "ERROR: wrong Key string , must contain 16 hex numbers\n";
    std::cout << "USAGE: " << argv[0] << " <hex_IV_grid_string>  <hex_key_grid_string> <hex_input_grid_string_1> <hex_input_grid_string_2> ...  [trace]\n";
    return 2;
  }
  for (int i = 3; i < (argc - 1); ++i)
  {

    if (std::string{argv[i]}.size() != 32)
    {
      std::cout << "ERROR: wrong input string , must contain 16 hex numbers\n";
      std::cout << "USAGE: " << argv[0] << "<hex_IV_grid_string>  <hex_key_grid_string> <hex_input_grid_string_1> <hex_input_grid_string_2> ... [trace]\n";
      return 3;
    }
  }

  /* CASES */

  return 0;
}

void print_grid(const byte_grid_t &grid)
{

  for (auto row : grid)
  {
    for (auto element : row)
      std::cout << std::hex << static_cast<int>(element);
    std::cout << "\n";
  }
}

byte_grid_t parse_grid(const std::string &input)
{
  byte_grid_t output = {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}};
  int c = 0;
  int r = 0;
  int pos = 0;
  for (int i = 1; i <= 16 && pos < 32; ++i)
  {

    output[c][r] = static_cast<uint8_t>(std::stoi(input.substr(pos, 2), 0, 16));
    if (((i % 4) == 0) && (i != 0))
      r++;
    c++;
    pos += 2;

    if (((i % 4) == 0))
      c = 0;
  }

  return output;
}