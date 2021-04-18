#include <sstream>

#include "../include/aes.h"
#include "../include/binary_mult.h"

AES_128::AES_128(const byte_grid_t &block, const byte_grid_t &input_key)
{
  this->inp_block_ = block;
  this->input_key_ = input_key;
  generate_round_keys();
}

/*!
 * @brief generates encripted block by aplying the AES instruction 
   round key -> +9 rounds -> out
 * */
byte_grid_t AES_128::generate(const bool &snitch)
{
  byte_grid_t output;
  //  init round (add round key)
  output = this->add_round_key(this->inp_block_, this->input_key_);
  if (snitch)
  {
    std::cout << "LAP 0:\n";
    std::cout << "R0 (Subclave =" << this->grid_to_s(this->input_key_)
              << ") = " << this->grid_to_s(output) << "\n";
  }

  // 9 rounds of the secuence sub bytes -> shift rows -> mix columns -> ad round key
  for (int i = 0; i < 9; ++i)
  {
    output = this->round(output, this->round_key_[i + 1]);
    if (snitch)
    {
      std::cout << "LAP " << i + 1 << ":\n";
      std::cout << "R" << i + 1 << " (Subclave =" << this->grid_to_s(this->round_key_[i + 1])
                << ") = " << this->grid_to_s(output) << "\n";
    }
  }
  // Last sub byte -> shift rows -> add round key
  output = this->add_round_key(this->shift_rows(this->subs_bytes(output)), this->round_key_[10]);
  if (snitch)
  {
    std::cout << "LAP " << 10 << ":\n";
    std::cout << "R10 (Subclave =" << this->grid_to_s(this->round_key_[10])
              << ") = " << this->grid_to_s(output) << "\n";
    std::cout << "Bloque de texto cifrado: " << this->grid_to_s(output) << "\n";
  }
  return output;
}

/*!
 * @brief generates only one round of the AES sequence of instructions
 *
 * 1. sub_bytes
 * 2. shift_row
 * 3. mix_column
 * 4. add_round_key
 * 
 * @returns modified grid
 * */
byte_grid_t AES_128::round(const byte_grid_t &grid, const byte_grid_t &round_key)
{
  return this->add_round_key(this->mix_column(this->shift_rows(this->subs_bytes(grid))), round_key);
}

/*!
 * @brief prints a grid in a linear secuence of hex numbers
 *
 * @returns the output string generated from the grid.
 * */
std::string AES_128::grid_to_s(const byte_grid_t &grid) const
{
  std::ostringstream out;

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
      out << std::hex << static_cast<int>(grid[j][i]) << " ";
  }
  return std::string{out.str()};
}

/*!
 * @brief Private method that applies the substitution according to the defined S_BOX  
 * for AES 
 * 
 * It usses the private methods low_4_bits(const uint8_t& byte) and hig_4_bits(const uint8_t& byte)
 * to generate the eexpected output value.  
 * 
 * @returns substituted bytes grid
 * */
byte_grid_t AES_128::subs_bytes(const byte_grid_t &grid)
{
  byte_grid_t out = {{}, {}, {}, {}};
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      out[i].push_back(S_BOX[hig_4_bits(grid[i][j])][low_4_bits(grid[i][j])]);

  return out;
}

/*!
 * @brief Private method that applies the row shifting to the given grid (which comes from sub_bytes())
 * 
 * The method shifts N times the current row elements, N refers to the actual row number
 * 
 * ```
 *  [n1 n5 n9  n13] << x0        [n1  n5  n9  n13]
 *  [n2 n6 n10 n14] << x1   -->  [n6  n10 n14 n2 ] 
 *  [n3 n7 n11 n15] << x2        [n11 n15 n3  n7 ]
 *  [n4 n8 n12 n16] << x3        [n16  n4 n8  n12] 
 * ```
 * 
 * @returns shifted bytes grid
 * */
byte_grid_t AES_128::shift_rows(const byte_grid_t &grid)
{
  return byte_grid_t{{grid[0][0], grid[0][1], grid[0][2], grid[0][3]},
                     {grid[1][1], grid[1][2], grid[1][3], grid[1][0]},
                     {grid[2][2], grid[2][3], grid[2][0], grid[2][1]},
                     {grid[3][3], grid[3][0], grid[3][1], grid[3][2]}};
}

/*!
 * @brief Private method that the second part of the permutation to the current block
 * 
 * The method multiplies each column with a base column to create the output block
 * 
 * ```
 *  [02 03 01 01] [c1]   [c'1]
 *  [01 02 03 01] [c2] = [c'2] 
 *  [01 01 02 03] [c3]   [c'3]
 *  [03 01 01 02] [c4]   [c'4] 
 * ```
 * 
 * @returns mixed column bytes grid
 * */
byte_grid_t AES_128::mix_column(const byte_grid_t &grid)
{
  byte_grid_t out = {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}};
  for (int i = 0; i < 4; ++i)
  {

    out[0][i] = gf2n_multiply(0x02, grid[0][i]) ^ gf2n_multiply(0x03, grid[1][i]) ^ grid[2][i] ^ grid[3][i];
    out[1][i] = grid[0][i] ^ gf2n_multiply(0x02, grid[1][i]) ^ gf2n_multiply(0x03, grid[2][i]) ^ grid[3][i];
    out[2][i] = grid[0][i] ^ grid[1][i] ^ gf2n_multiply(0x02, grid[2][i]) ^ gf2n_multiply(0x03, grid[3][i]);
    out[3][i] = gf2n_multiply(0x03, grid[0][i]) ^ grid[1][i] ^ grid[2][i] ^ gf2n_multiply(0x02, grid[3][i]);
  }

  return out;
}

/*!
 * @brief Private method that adds the key to the given grid 
 *
 * It usses byte_add(uint8_t A, uint8_t B) function of bitwise XOR to each byte 
 * of both elements
 * 
 * @returns add round key grid
 * */
byte_grid_t AES_128::add_round_key(const byte_grid_t &grid, const byte_grid_t &key)
{
  byte_grid_t out;
  for (int i = 0; i < 4; ++i)
  {
    std::vector<uint8_t> aux_line;
    for (int j = 0; j < 4; ++j)
      aux_line.push_back(byte_add(grid[i][j], key[i][j]));
    out.push_back(aux_line);
  }

  return out;
}

/*!
 * @brief Private method that expands the original key  
 *
 * Generates all the 10 round keys expected to use in each round, round_keys_ 
 * attribute is modified to contain all the keys (inlcuding the original)
 * 
 * */

void AES_128::generate_round_keys(void)
{
  std::vector<uint32_t> words;
  words.resize(44);

  // first 4 words are the original key
  for (int i = 0; i < 4; ++i)
  {
    words[i] = this->gen_word(this->input_key_[0][i], this->input_key_[1][i],
                              this->input_key_[2][i], this->input_key_[3][i]);
  }

  // expansion for next 10 keys (40 words)
  for (int i = 4; i < 44; ++i)
  {
    uint32_t temp = words[i - 1];
    if ((i % 4) == 0)
    {
      words[i] = words[i - 4] ^ sub_word(cls_word(temp)) ^ this->RC[(i / 4) - 1];
    }
    else
    {
      words[i] = words[i - 4] ^ temp;
    }
  }

  // Copy into attribute ordering the words into bytes
  for (int i = 0; i < 11; ++i)
  {
    std::vector<uint32_t> this_set = {words[i * 4],
                                      words[i * 4 + 1],
                                      words[i * 4 + 2],
                                      words[i * 4 + 3]};

    this->round_key_.push_back(cols_to_byte(this_set));
  }
}

/*!
 * 
 * @brief generates a word from 4 key bytes
 * 
 * This method uses the bitwise operators to arrange the
 * 4 bytes into one 32b word
 * 
 * */

uint32_t AES_128::gen_word(const uint8_t k_0, const uint8_t k_1,
                           const uint8_t k_2, const uint8_t k_3)
{
  uint32_t result = 0x00000000;
  uint32_t current;
  current = static_cast<uint32_t>(k_0);

  current <<= 24;
  result |= current;
  current = static_cast<uint32_t>(k_1);
  current <<= 16;
  result |= current;
  current = static_cast<uint32_t>(k_2);
  current <<= 8;
  result |= current;
  current = static_cast<uint32_t>(k_3);
  result |= current;

  return result;
}

/*!
 * 
 * @brief generates 4 bytes from one column
 * 
 * This method uses the bitwise operators to split into
 * 4 bytes the given word.
 * 
 * */

std::vector<uint8_t> AES_128::gen_col(const uint32_t word)
{
  return std::vector<uint8_t>{
      static_cast<uint8_t>((word & 0xff000000) >> 24),
      static_cast<uint8_t>((word & 0x00ff0000) >> 16),
      static_cast<uint8_t>((word & 0x0000ff00) >> 8),
      static_cast<uint8_t>(word & 0x000000ff)};
}

/*!
 * 
 * @brief takes a vector of 4 words to order them into a grid
 * 
 * */
byte_grid_t AES_128::cols_to_byte(const std::vector<uint32_t> words)
{
  return {
      {gen_col(words[0])[0], gen_col(words[1])[0], gen_col(words[2])[0], gen_col(words[3])[0]},
      {gen_col(words[0])[1], gen_col(words[1])[1], gen_col(words[2])[1], gen_col(words[3])[1]},
      {gen_col(words[0])[2], gen_col(words[1])[2], gen_col(words[2])[2], gen_col(words[3])[2]},
      {gen_col(words[0])[3], gen_col(words[1])[3], gen_col(words[2])[3], gen_col(words[3])[3]},
  };
}

/*!
 * 
 * @brief Cyclic left shift the given word which will be rotated
 * 
 * */

uint32_t AES_128::cls_word(const uint32_t rw)
{
  uint32_t high = rw << 8;
  uint32_t low = rw >> 24;
  return high | low;
}

/*!
 * 
 * @brief Applies the substitution with the s-box to the given word.
 * 
 * */
uint32_t AES_128::sub_word(const uint32_t sw)
{
  // 32b word to 8b words vector
  std::vector<uint8_t> word = gen_col(sw);

  std::vector<uint8_t> out = {};

  // substitution stored into out
  for (int j = 0; j < 4; ++j)
    out.push_back(S_BOX[hig_4_bits(word[j])][low_4_bits(word[j])]);

  // std::cout << std::hex << gen_word(out[0], out[1], out[2], out[3]) << "\n";

  // out as 32b word.
  return gen_word(out[0], out[1], out[2], out[3]);
}
