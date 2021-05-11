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
#include "../include/dh-ec.h"
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
     std::pair<long, long> pub_b = (std::string{argv[8]} == "eg") ? eg_pubkey() : dh_pubkey(db, base, a, p);

     std::cout << "dbG=(" << pub_b.first << "," << pub_b.second << ")\n";
     std::pair<long, long> pub_a = (std::string{argv[8]} == "eg") ? eg_pubkey() : dh_pubkey(da, base, a, p);

     std::cout << "daG=(" << pub_a.first << "," << pub_a.second << ")\n";
     std::cout << "Generating private keys for Bob and Alice...\n";
     std::pair<long, long> priv_a; //= //mult_point(da, pub_b, a, p); /* = funtion */
     std::pair<long, long> priv_b; //= //mult_point(db, pub_a, a, p); /* = funtion */
     std::cout << db << "*(dbG)=(" << priv_b.first << "," << priv_b.second << ")\n"
               << da << "*(daG)=(" << priv_a.first << "," << priv_a.second << ")\n";
     std::cout << "Ciphering message...\n";
     long M = great_strict_pow(msg);
     long h = p / M;
     std::cout << "M=" << M << "\n";
     std::cout << "h=" << p << "/" << M << "=" << h << "\n";
     std::pair<long, long> msg_point = msg_2_point(msg, h, M, e_points);
     std::cout << "plain text msg as point: Qm=(" << msg_point.first << "," << msg_point.second << ")\n";
     std::cout << "Ciphered message and public key sent fromn Allice to Bob: \n";
     std::pair<long, long> c_msg; //= add_points(msg_point, priv_a, a, p);

     std::cout << "{(" << c_msg.first << "," << c_msg.second << ") ; (" << pub_a.first << "," << pub_a.second << ")}\n";
     return 0;
}