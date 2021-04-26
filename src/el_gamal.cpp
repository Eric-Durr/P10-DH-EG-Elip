#include "../include/el_gamal.h"

int main(int argc, char *argv[])
{
  int flag = filter(argc, argv);
  if (flag != 0)
  {
    return flag;
  }

  unsigned p = static_cast<unsigned>(stoi(std::string{argv[1]})),
           a = static_cast<unsigned>(stoi(std::string{argv[2]})),
           k = static_cast<unsigned>(stoi(std::string{argv[3]})),
           x = static_cast<unsigned>(stoi(std::string{argv[4]})),
           plaintxt = static_cast<unsigned>(stoi(std::string{argv[5]})),
           ciphertxt, Ka, Ya, Kb, Yb, invK, decipheredtxt;

  if (!is_prime(p))
  {
    std::cout << "p debe ser un número primo, terminando el programa\n";
    return 2;
  }

  std::cout << "\nCIFRADO DE INTERCAMBIO DE CLAVES - ELGAMAL\n";

  // Create Alice private key
  Ya = f_exp(a, k, p);
  Ka = f_exp(Ya, x, p);
  // Create Bob private key
  Yb = f_exp(a, x, p);
  Kb = f_exp(Yb, k, p);

  //message ciphering
  if (Ka == Kb)
  {
    ciphertxt = (Ka * plaintxt) % p;
  }
  else
  {
    std::cout << "Error durante la creación de las claves \n";
    return 3;
  }

  //Modular multiplicative inverse:
  invK = mod_mult_inv(Ka, p);
  decipheredtxt = (invK * Ka * plaintxt) % p;

  std::cout << "\nEntrada: p = "
            << p << ", a = "
            << a << ", k = "
            << k << ", x = "
            << x << ", m = "
            << plaintxt
            << "\nSalida: Ya="
            << Ya << ", Yb="
            << Yb << ", K="
            << Ka << ", C="
            << ciphertxt << ", K^(-1) = "
            << invK
            << ", M=" << decipheredtxt
            << "\n";
  return 0;
}
