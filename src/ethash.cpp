#include "../include/ethash.h"
#include "../include/types.h"
#include "../include/keccak.h"

#include <iostream>
#include <cstring>

using namespace std;

namespace ethash{
	hash_512 element_wise_xor(hash_512 h1, hash_512 h2){
        hash_512 h3;
        for(int i=0; i<HASH_BYTES; ++i){
            h3.bytes[i] = h1.bytes[i] ^ h2.bytes[i];
        }
        return h3;
    }

    union hash_512* mkcache(uint64_t cache_size, hash_256 seed){
        uint64_t n = cache_size / HASH_BYTES;
        hash_512* output = new hash_512[cache_size/64];
        keccak512(output[0].words64, seed.bytes, sizeof(hash_256));
        for(int i=1; i<cache_size/64; ++i){
            keccak512(output[i].words64, output[i-1].bytes, 64);
        }

        for(int i=0; i<CACHE_ROUNDS; ++i){
            for(int j=0; j<n; ++j){
                uint64_t v = output[j].words64[0] % n;
                keccak512(output[j].words64, element_wise_xor(output[(j-1+n)%n], output[v]).bytes, 64);
            }
        }
        return output;
    }

    void get_seedhash(hash_256* seed, uint64_t block){
        memset(seed, 0, sizeof(hash_256));
        if(block < EPOCH_LENGTH) {
            return;
        }
        for(int i=0; i<block/EPOCH_LENGTH;++i){
            keccak256(seed->words64, seed->bytes, sizeof(hash_256));
        }
    }
}

void print_seed(hash_256 seed){
    cout <<"seed:";
    for(int i=0;i<sizeof(hash_256);++i){
        cout << hex << (int) seed.bytes[i];
    }
    cout << "\n";
}

void print_cache(hash_512* cache, uint64_t cache_size){
    cout << "cache:\n";
    for(int j=0;j<cache_size/sizeof(hash_512);++j) {
        for(int i=0;i<sizeof(hash_512);++i){
            cout << hex << (int) cache[j].bytes[i];
        }
    }
    cout << "\n";
}

int main(){
    hash_256 h256 = {0x53617665};
    hash_512* h;
    hash_256 s;
    ethash::get_seedhash(&s, 0);
    print_seed(s);
    ethash::get_seedhash(&s, 1);
    print_seed(s);
    hash_256 seed;
    ethash::get_seedhash(&seed, 1);
    h = ethash::mkcache(1024/8, seed);
    print_cache(h, 1024/8);
    

    return 0;
}



