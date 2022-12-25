#include <iostream>
#include "dos.h"
#include "rsa_keygen.h"
#include "ExpandedKey.h"
#include "State.h"
using namespace std;

int main()
{
	string key = "2b7e151628aed2a6abf7158809cf4f3c";
	auto test = AES::encrypt("the block breakers", key);

	cout << AES::decrypt(test, key);

	return 0;
}
