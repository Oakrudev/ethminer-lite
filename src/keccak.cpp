/* Ethminer-lite: Keccak sponge function
 *
 * implementation of https://keccak.team/keccak_specs_summary.html
*/

#include <iostream>
#include <cstring>
#include "keccak.h"

using namespace std;

uint64_t word_from_data(uint8_t* data) {
    return *((uint64_t*) data);
}

static void keccak(uint64_t* hash, size_t obits, uint8_t* idata, size_t ibytes) {
    size_t c = obits * 2;
    size_t r = 1600 - c;
    uint64_t* states = (uint64_t*) calloc(STATE_SIZE, 64);
    Keccak k (states);
    // padding - can use more memory to create new padded string.
    // Or handle the last block separately to save memory. Going
    // with the first option here.
    uint64_t blocks = (ibytes*8 + r - 1) / r;
    size_t block_bytes = r/8;
    size_t p_bytes = blocks*r/8;
    uint8_t* p = (uint8_t*) calloc(p_bytes, 1);
    memcpy(p, idata, ibytes);
    p[ibytes] = 0x01;
    p[p_bytes-1] = 0x80;


    // absorbing phase
    uint64_t iter_per_block = (r+c)/64;
    int x = 0;
    int y = 0;
    for (int i=0; i<blocks; ++i) {
        for (int j=0; j<r/64; ++j) {
            states[j] ^= *(uint64_t*) (p+(j*8)+i*block_bytes);
        }
        k.keccak_1600();
    }

    // squeezing phase
    size_t hash_length = 0;
    int i_state = 0;
    memcpy(hash, states, obits/8);
    hash_length = obits;

    // Reverse endianess to convert 64 bits to byte array
    for(int i=0;i<hash_length/64;++i) {
        hash[i] = __builtin_bswap64(hash[i]);
    }
    free(states);
    free(p);
}

void keccak224(uint64_t* hash, uint8_t* data, size_t ibytes) {
    keccak(hash, 224, data, ibytes);
}

void keccak256(uint64_t* hash, uint8_t* data, size_t ibytes) {
    keccak(hash, 256, data, ibytes);
}

void keccak384(uint64_t* hash, uint8_t* data, size_t ibytes) {
    keccak(hash, 384, data, ibytes);
}

void keccak512(uint64_t* hash, uint8_t* data, size_t ibytes) {
    keccak(hash, 512, data, ibytes);
}
