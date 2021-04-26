#include <gtest/gtest.h>
#include "keccak.h"
#include "gmock/gmock.h"

using testing::ElementsAreArray;

TEST(KeccakF1600Test, BasicAssertions) {
	Keccak k = Keccak();
	// prints states matrix in each round. Remove to disable logging.
	k.enable_logging();
	uint64_t expected[25] = {
        0xF1258F7940E1DDE7, 0x84D5CCF933C0478A, 0xD598261EA65AA9EE, 0xBD1547306F80494D,
        0x8B284E056253D057, 0xFF97A42D7F8E6FD4, 0x90FEE5A0A44647C4, 0x8C5BDA0CD6192E76,
        0xAD30A6F71B19059C, 0x30935AB7D08FFC64, 0xEB5AA93F2317D635, 0xA9A6E6260D712103,
        0x81A57C16DBCF555F, 0x43B831CD0347C826, 0x01F22F1A11A5569F, 0x05E5635A21D9AE61,
        0x64BEFEF28CC970F2, 0x613670957BC46611, 0xB87C5A554FD00ECB, 0x8C3EE88A1CCF32C8,
        0x940C7922AE3A2614, 0x1841F924A2C509E4, 0x16F53526E70465C2, 0x75F644E97F30A13B,
        0xEAF1FF7B5CECA249,
    };
	uint64_t* s = k.keccak_1600();
	// No point to test the sponge functions if this fails.
	ASSERT_THAT(expected, ElementsAreArray(s, 25));
}

TEST(Keccak256TestShort, BasicAssertions) {
	uint64_t* hash = NULL;
	size_t hash_size = 256;
	uint8_t* data = (uint8_t*) "deadbeef";
	size_t size = 8;
	uint64_t expected[4] = {
		0x9F24C52E0FCD1AC6,
		0x96D00405C3BD5ADC,
		0x558C48936919AC5A,
		0xB3718FCB7D70F93F
	};
	hash = keccak256(data, size);
	EXPECT_THAT(expected, ElementsAreArray(hash, hash_size/64));
}

TEST(Keccak256TestLong, BasicAssertions) {
	uint64_t* hash = NULL;
	size_t hash_size = 256;
	uint8_t* data = (uint8_t*) "qbWbUWhkXqfxFcdHAgJuIUFzjPRpumgvfAUCbgBFqvrSoCpFqOxHSaDlKTCgtCqwBXtHMIUzMJvWYEjxgAGLqxecZxooBEiCJJrM";
	size_t size = 100;
	uint64_t expected[4] = {
		0x7cbf802f5e954702,
		0xded95b0eaaaaf7c2,
		0xbed78e4f49e25977,
		0x8a665c4ae83410e4
	};
	hash = keccak256(data, size);
	EXPECT_THAT(expected, ElementsAreArray(hash, hash_size/64));
}

TEST(Keccak512TestShort, BasicAssertions) {
	uint64_t* hash = NULL;
	size_t hash_size = 512;
	uint8_t* data = (uint8_t*) "deadbeef";
	size_t size = 8;
	uint64_t expected[8] = {
		0x99505637a3c27670,
		0x05db9e43ed1461d2,
		0x449412efda50f0b1,
		0x54b35cb16fdb4051,
		0xa46ab350336a5e30,
		0x8635b3245404ff6a,
		0x5e8ec463a167c8c4,
		0xde4f76b95cb90eac
	};
	hash = keccak512(data, size);
	EXPECT_THAT(expected, ElementsAreArray(hash, hash_size/64));
}

TEST(Keccak512TestLong, BasicAssertions) {
	uint64_t* hash = NULL;
	size_t hash_size = 512;
	uint8_t* data = (uint8_t*) "qbWbUWhkXqfxFcdHAgJuIUFzjPRpumgvfAUCbgBFqvrSoCpFqOxHSaDlKTCgtCqwBXtHMIUzMJvWYEjxgAGLqxecZxooBEiCJJrM";
	size_t size = 100;
	uint64_t expected[8] = {
		0x31fc1141110593ad,
		0xd4960eaa4cca5301,
		0x8d094c7982a4c427,
		0xfea5debb8a2f4dd6,
		0xb4985c5428c0eff3,
		0xda969fce3cdce754,
		0x7e2256addb92ef8e,
		0x9c752e7e82457d2f
	};
	hash = keccak512(data, size);
	EXPECT_THAT(expected, ElementsAreArray(hash, hash_size/64));
}
