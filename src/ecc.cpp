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
     std::cout << "--- " << (std::string{argv[8]} == "eg" ? "ElGamal" : "Diffie-Hellman") << " based elliptic encryption ---\n";
     std::cout << "Generating introduced values...\n";
     long p = std::stoi(argv[1]);
     long a = std::stoi(argv[2]);
     long b = std::stoi(argv[3]);
     std::pair<long, long> base = parse_point(argv[4]);
     long da = std::stoi(argv[5]);
     long db = std::stoi(argv[6]);
     long msg = std::stoi(argv[7]);
     std::cout
         << "p=" << p << "\n"
         << "a=" << a << "\n"
         << "b=" << b << "\n"
         << "G="
         << "(" << base.first << "," << base.second << ")\n"
         << "da=" << da << "\n"
         << "db=" << db << "\n"
         << "Plain text msg=" << msg << "\n";

     std::cout << "Generating E curve points...\n";

     std::vector<std::pair<long, long>> e_points = extract_points(p, a, b);
     std::cout << "E curve points: ";
     for (auto point : e_points)
          std::cout << "(" << point.first << "," << point.second << ") ";
     std::cout << "\n";
     std::cout << "Generating public keys for Bob and Alice...\n";
     std::pair<long, long> db_point; /* = funtion */
     std::pair<long, long> da_point; /* = funtion */
     std::cout << "dbG=(" << db_point.first << "," << db_point.second << ")\n"
               << "daG=(" << da_point.first << "," << da_point.second << ")\n";
     std::cout << "Generating private keys for Bob and Alice...\n";
     std::pair<long, long> priv_b; /* = funtion */
     std::pair<long, long> priv_a; /* = funtion */
     std::cout << "db*(daG)=(" << priv_b.first << "," << priv_b.second << ")\n"
               << "da*(dbG)=(" << priv_a.first << "," << priv_a.second << ")\n";
     std::cout << "Ciphering message...\n";
     long c_msg;
     long h;
     std::cout << "Ciphered msg=" << c_msg << "\n";
     std::cout << "h=" << h << "\n";
     std::pair<long, long> msg_point;
     std::cout << "plain text msg as point=" << msg_point.first << "," << msg_point.second << ")\n";
     std::cout << "Ciphered message and public key sent fromn Allice to Bob: \n";

     return 0;
}