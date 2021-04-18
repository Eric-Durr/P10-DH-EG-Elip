
#include "s_box.h"

#ifndef AES_128_H__
#define AES_128_H__
class AES_128
{
    byte_grid_t
        inp_block_,
        input_key_;
    std::vector<byte_grid_t> round_key_;

    // tools
    const std::vector<uint32_t> RC =
        {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
         0x20000000, 0x40000000, 0x80000000, 0x1B000000, 0x36000000};
    const byte_grid_t MIX_GRID = {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}};

public:
    AES_128(const byte_grid_t &block, const byte_grid_t &input_key);
    ~AES_128(void){};
    byte_grid_t generate(const bool &snitch = false);
    byte_grid_t round(const byte_grid_t &grid, const byte_grid_t &round_key);
    const byte_grid_t &round_key(const int &pos) const { return this->round_key_[pos]; }

    byte_grid_t add_round_key(const byte_grid_t &grid, const byte_grid_t &key);
    byte_grid_t subs_bytes(const byte_grid_t &grid);
    byte_grid_t shift_rows(const byte_grid_t &grid);
    byte_grid_t mix_column(const byte_grid_t &grid);

    std::string grid_to_s(const byte_grid_t &grid) const;

private:
    void generate_round_keys(void);
    uint32_t gen_word(const uint8_t k_0, const uint8_t k_1,
                      const uint8_t k_2, const uint8_t k_3);

    std::vector<uint8_t> gen_col(const uint32_t word);
    byte_grid_t cols_to_byte(const std::vector<uint32_t> word);

    uint32_t cls_word(const uint32_t rw);
    uint32_t sub_word(const uint32_t sw);
    uint8_t hig_4_bits(const uint8_t &byte) const { return (byte & 0xf0) >> 4; };
    uint8_t low_4_bits(const uint8_t &byte) const { return (byte & 0x0f); };
};

#endif /* AES_128_H__ */
