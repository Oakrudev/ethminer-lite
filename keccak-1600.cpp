/* Ethminer-lite: Keccak f[1600]
*/
#include <iostream>
#include "keccak.h"

using namespace std;

Keccak::Keccak() {
}

uint64_t* Keccak::keccak_1600(uint64_t* message) {
	for (int i = 0; i < ROUNDS; ++i) {
		cout << "." << "\n";
	}
	return 0;
}

uint64_t*  Keccak::round(uint64_t* message) {
	cout << "-" << "\n";
	return 0;
}


int main() {
	Keccak k = Keccak();
	k.keccak_1600(NULL);
	return 0;
}