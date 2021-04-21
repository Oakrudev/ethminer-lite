/* Ethminer-lite: Keccak f[1600]
 *
 * implementation of https://keccak.team/keccak_specs_summary.html
*/
#include <iostream>
#include "keccak.h"

using namespace std;

/*Rotate bits to the left by s. Note ethash uses little-endian.*/
uint64_t rot(uint64_t b, uint8_t s) {
	return (b << s)|(b >> (64 - s));
}

Keccak::Keccak(uint64_t* A) {
	states = (uint64_t*) calloc(STATE_SIZE, 64);
	for (int i = 0; i < STATE_SIZE; ++i) {
		states[i] = A[i];
	}
}

uint64_t* Keccak::keccak_1600() {
	for (int i = 0; i < ROUNDS; ++i) {
		round(i);
	}
	return states;
}

void  Keccak::round(int ri) {
	/* theta step */
	uint64_t C[5] = {0};
	uint64_t D[5] = {0};
	uint64_t B[25] = {0};
	for (int x = 0; x < 5; ++x) {
		C[x] = states[5*0+x] ^ states[5*1+x] ^ states[5*2+x] ^ states[5*3+x] ^ states[5*4+x];
		D[x] = C[(x >=1 ? x-1 : 0)%5] ^ rot(C[(x+1)%5], 1);
		for (int y = 0; y < 5; ++y)
			states[5*y + x] = states[5*y + x] ^ D[x];
	}
	/* rho and pi step*/
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			B[y+5*((2*x+3*y)%5)] = rot(states[y*5+x], r[y*5+x]);
		}
	}

	/* chi step*/
	for (int x = 0; x < 5; ++x) {
		for (int y = 0; y < 5; ++y) {
			states[y*5+x] = B[y*5+x] ^ ((~B[y*5+(x+1)%5]) & B[y*5+(x+2)%5]);
		}
	}
	/* iota step*/
	states[0] = states[0] ^ RC[ri];
}


int main() {
	uint64_t a[25] = {0};
	Keccak k = Keccak(a);
	uint64_t* s = k.keccak_1600();
	for (int i=0; i < STATE_SIZE; ++i) {
		cout << hex << s[i] << " ";
		if (( i+1) % 5 == 0) {
			cout << "\n";
		}
	}
	return 0;
}
