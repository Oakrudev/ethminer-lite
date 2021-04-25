/* Ethminer-lite: Keccak sponge function
 *
 * implementation of https://keccak.team/keccak_specs_summary.html
*/

#include <iostream>
#include <cstring>
#include "../include/keccak.h"

#include <bitset>

using namespace std;

void print(uint8_t* d, size_t s) {
    cout << "DEBUG+++++++++++++++++\n";
    int c = 0;
    cout << "size " << s << "\nhex: \n";
    while (c < s) {
        cout << bitset<8>(*(d++)) << " ";
        c++;
        if (c % 5 == 0)
            cout << "\n";
    }
    cout << "\n";
}

uint64_t word_from_data(uint8_t* data) {
    return *((uint64_t*) data);
}

static uint64_t* keccak(size_t obits, uint8_t* idata, size_t ibytes) {
    size_t c = obits * 2;
    size_t r = 1600 - c;
    Keccak k = Keccak();
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
    //print(p, p_bytes);

    // initialization
    uint64_t* states = k.get_state();

    // absorbing phase
    uint64_t iter_per_block = (r+c)/64;
    int x = 0;
    int y = 0;
    for (int i=0; i<blocks; ++i) {
        for (int j=0; j<r/64; ++j) {
            states[j] ^= *(uint64_t*) (p+(j*8));
        }
        k.keccak_1600();
    }

    // squeezing phase
    return 0;
}

int main() {
    uint8_t* data =(uint8_t*) "0";
    keccak(256, data, 1);
}
