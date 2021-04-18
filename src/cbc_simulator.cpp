#include "../include/cbc_simulator.h"
#include "../include/aes.h"

byte_grid_t CBC_XOR(const byte_grid_t &plaintext, const byte_grid_t &element, const bool &trace = false);

int main(int argc, char *argv[])
{
  int flag = filter(argc, argv);
  if (flag != 0)
  {
    return flag;
  }

  bool trace = (std::string{argv[argc - 1]} == "trace");

  std::cout << "--- Encriptado CBC con AES de 128 b --- \n";
  std::cout << "\n Bloques de texto plano origen: \n\n";

  for (int i = 3; i < (trace ? (argc - 1) : (argc)); ++i)
    print_grid(parse_grid(argv[i]));

  //// --- CBC proccess ---

  byte_grid_t input;
  std::vector<byte_grid_t> ciph_text;

  // XOR between plaintext and corresponding element
  for (int i = 3; i < (trace ? (argc - 1) : (argc)); ++i)
  {
    if (i == 3) // First round with initialization vector (IV)
    {

      input = CBC_XOR(parse_grid(argv[i]), parse_grid(argv[1]), trace);
    }
    if (i > 3) // The rest of the rounds AES input block contains the previous Ciphertext
    {
      input = CBC_XOR(parse_grid(argv[i]), ciph_text.back(), trace);
    }

    AES_128 my_aes_obj(input, parse_grid(argv[2]));
    //// Trace is printed by passing boolean value which depends on the command line input
    ciph_text.push_back(my_aes_obj.generate(trace));
  }
  // Result grid operation by generating AES

  // Result block print in the terminal
  std::cout << "\n\nResultados del cifrado CBC:\n";
  for (unsigned i = 0; i < ciph_text.size(); ++i)
  {
    std::cout << "Bloque " << i + 1 << " de tetxo cifrado:\n";
    print_grid(ciph_text[i]);
  }
  return 0;
}

byte_grid_t CBC_XOR(const byte_grid_t &plaintext, const byte_grid_t &element, const bool &trace)
{
  byte_grid_t xored = {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}};
  for (unsigned i = 0; i < plaintext.size(); ++i)
    for (unsigned j = 0; j < plaintext.size(); ++j)
      xored[j][i] = plaintext[j][i] ^ element[j][i];
  if (trace)
  {
    std::cout << "\n\nXOR entre los bloques\n\n";
    print_grid(plaintext);
    std::cout << "\ny\n\n";
    print_grid(element);
    std::cout << "\nresulta en:\n\n";
    print_grid(xored);
    std::cout << "\n\n\n";
  }
  return xored;
}
