#pragma once

#include <cstddef>
#include <stdint.h>
#include "types.h"

namespace ethash {
	const size_t WORD_BYTES = 4;                      // bytes in word
	const uint32_t DATASET_BYTES_INIT = 1073741824;   // 2^30 bytes in dataset at genesis
	const uint32_t DATASET_BYTES_GROWTH = 8388608;    // 2^23 bytes dataset growth per epoch
	const uint32_t CACHE_BYTES_INIT = 16777216;       // 2^24 bytes in cache at genesis
	const uint32_t CACHE_BYTES_GROWTH = 131072;       // 2^17 bytes cache growth per epoch
	const uint32_t CACHE_MULTIPLIER=1024;             // Size of the DAG relative to the cache
	const uint32_t EPOCH_LENGTH = 30000;              // blocks per epoch
	const size_t MIX_BYTES = 128;                     // width of mix
	const size_t HASH_BYTES = 64;                     // hash length in bytes
	const uint32_t DATASET_PARENTS = 256;             // number of parents of each dataset element
	const uint32_t CACHE_ROUNDS = 3;                  // number of rounds in cache production
	const uint32_t ACCESSES = 64;                     // number of accesses in hashimoto loop

	uint32_t get_cache_size(uint32_t block_number);
	uint32_t get_full_size(uint32_t block_number);

	hash_512* mkcache(uint64_t cache_size, hash_256 seed);

	uint32_t fnv(uint32_t v1, uint32_t v2);

	uint64_t calc_dataset_item(uint64_t* cache, uint32_t i);
	uint64_t* calc_dataset(uint32_t full_size, uint64_t* cache);

	void get_seedhash(hash_256* seed, uint64_t block);

	void hashimoto(uint64_t header, uint64_t* nonce, uint32_t full_size);

	hash_512* element_wise_xor(hash_512* h1, hash_512* h2);
}
