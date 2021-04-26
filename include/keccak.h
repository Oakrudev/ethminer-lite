#pragma once

#include <cstdint>

using namespace std;

const uint8_t STATE_SIZE = 25;
const uint8_t ROUNDS = 24;
const uint8_t WIDTH = 64;

/*Round constants*/
static const uint64_t RC[24] = {
	0x0000000000000001, 0x0000000000008082, 0x800000000000808a, 0x8000000080008000,
	0x000000000000808b, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
	0x000000000000008a, 0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
	0x000000008000808b, 0x800000000000008b, 0x8000000000008089, 0x8000000000008003,
	0x8000000000008002, 0x8000000000000080, 0x000000000000800a, 0x800000008000000a,
	0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

/*Rotation Offsets indexed by (y*5+x)*/
static const uint8_t r[25] = {
	0, 1, 62, 28, 27,
	36, 44, 6, 55, 20,
	3, 10, 43, 25, 39,
	41, 45, 15, 21, 8,
	18, 2, 61, 56, 14
};

class Keccak {
private:
	uint64_t* states;
	bool logging = false;
	void round(int r);

public:
	Keccak();
	~Keccak();
	uint64_t* keccak_1600();
	uint64_t* get_state();
	void clear_state();
	void enable_logging();
};

static void keccak(uint64_t* hash, size_t obits, uint8_t* idata, size_t ibits);
void keccak224(uint64_t* hash, uint8_t* data, size_t ibytes);
void keccak256(uint64_t* hash, uint8_t* data, size_t ibytes);
void keccak384(uint64_t* hash, uint8_t* data, size_t ibytes);
void keccak512(uint64_t* hash, uint8_t* data, size_t ibytes);
