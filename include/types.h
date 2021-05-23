#pragma once

#include <stdint.h>

union hash_256 {
	uint64_t words64[4];
	uint8_t  bytes[32];
	char     str[32];
};

union hash_512 {
	uint64_t words64[8];
	uint8_t  bytes[64];
	char     str[64];
};
