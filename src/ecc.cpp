/**
 * @file elip.cpp
 * @author Eric Dürr (eric.durr.20@ull.edu.es)
 * @brief Elliptic curve criptography based on ElGamal and Diffie-Hellman algorithms.
 *          -> The Elyptic curve type is: Y^2=X^3+aX+b
 * @version 0.1
 * @date 2021-05-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/ecc.h"
#include <vector>

int main(int argc, char *argv[])
{
     if (int flag = filter(argc, argv) != 0)
     {
          return flag;
     }
     std::cout << "--- ElGamal and Diffie-Hellman based elliptic encryption ---\n";

     std::cout << "Generating introduced values...\n";
     long p = std::stoi(argv[1]);
     if (!is_prime(p))
     {
          std::cout << "ERROR: number p (modulo) must be a prime number,introduced p=" << p << " please retry with a prime number\n";
          return 1;
     }
     long a = std::stoi(argv[2]);
     long b = std::stoi(argv[3]);

     if (a <= 0 || a >= p)
     {
          std::cout << "ERROR: <a> must be a number between 0 and p=" << p << "  reatry with a number on the boundry\n";
          return 1;
     }
     if (b <= 0 || b >= p)
     {
          std::cout << "ERROR: <b> must be a number between 0 and p=" << p << "  reatry with a number on the boundry\n";
          return 1;
     }
     std::pair<long, long> base = parse_point(argv[4]);
     long db = std::stoi(argv[5]);
     long da = std::stoi(argv[6]);
     long msg = std::stoi(argv[7]);
     std::cout
         << "p=" << p << "\n"
         << "a=" << a << "\n"
         << "b=" << b << "\n"
         << "G="
         << "(" << base.first << "," << base.second << ")\n"
         << "db=" << da << "\n"
         << "da=" << db << "\n"
         << "Plain text msg=" << msg << "\n";
     std::cout << "\nOperating over elliptic curve:  y^2 (mod " << p << ") = x^3 + " << a << "*x + " << b << "(mod " << p << ")\n\n";
     std::cout << "Generating E curve points...\n";

     std::vector<std::pair<long, long>> e_points = extract_points(p, a, b);
     std::cout << "E curve points: ";
     for (auto point : e_points)
          std::cout << "(" << point.first << "," << point.second << ") ";
     std::cout << "\n";
     std::cout << "Generating public keys for Bob and Alice...\n";
     std::pair<long, long> pub_b = pubkey(db, base, a, p);
     std::pair<long, long> pub_a = pubkey(da, base, a, p);

     std::cout << "dbG=(" << pub_b.first << "," << pub_b.second << ")\n";
     std::cout << "daG=(" << pub_a.first << "," << pub_a.second << ")\n";

     std::cout << "Generating private keys for Bob and Alice...\n";
     std::pair<long, long> shared_a = shkey(da, pub_b, a, p);
     std::pair<long, long> shared_b = shkey(db, pub_a, a, p);

     std::cout << db << "*(" << pub_a.first << "," << pub_a.second << ") = (" << shared_b.first << "," << shared_b.second << ")\n";

     std::cout << da << "*(" << pub_b.first << "," << pub_b.second << ") = (" << shared_a.first << "," << shared_a.second << ")\n";

     std::cout << "Ciphering message process...\n";
     long M = great_strict_pow(msg);
     long h = p / M;
     std::cout << "M=" << M << "\n";
     std::cout << "h=" << p << "/" << M << "=" << h << "\n";
     std::pair<long, long> msg_point = msg_2_point(msg, h, M, e_points);
     std::cout << "plain text msg as point: Qm=(" << msg_point.first << "," << msg_point.second << ")\n";
     std::cout << "Ciphered message and public key sent from Allice to Bob: \n";
     std::pair<long, long> c_msg = add_points(msg_point, shared_a, a, p);

     std::cout << "{ Ciphered message: (" << c_msg.first << "," << c_msg.second << ") ; Public shared key: (" << pub_a.first << "," << pub_a.second << ")}\n";

     return 0;
}
