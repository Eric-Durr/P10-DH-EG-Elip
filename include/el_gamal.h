
#include <iostream>
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
