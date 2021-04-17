#include "../include/aes_simulator.h"
#include "../include/aes.h"

int main(int argc, char *argv[])
{
  int flag = filter(argc, argv);
  if (flag != 0)
  {
    return flag;
  }

  std::cout << "--- Encriptado AES de 128 b --- \n";
  std::cout << "\n Bloque de texto plano origen: \n\n";
  print_grid(parse_grid(argv[2]));

  // Cypherer object instance with plain text and key once parsed into byte_grid_object
  AES_128 my_aes_obj(parse_grid(argv[2]), parse_grid(argv[1]));

  // Result grid operation by generating AES
  //// Trace is printed by passing boolean value which depends on the command line input
  byte_grid_t result;
  result = my_aes_obj.generate((argc == 4) && (std::string{argv[3]} == "trace"));

  // Result block print in the terminal
  std::cout << "\n\n Bloque encriptado resultante: \n";
  print_grid(result);

  return 0;
}