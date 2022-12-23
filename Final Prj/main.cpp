#include <iostream>
#include "dos.h"
#include "rsa_keygen.h"
#include "ExpandedKey.h"
#include "State.h"
using namespace std;

int main()
{
	/*auto test = AES::encrypt("theblockbreakers", "2b7e151628aed2a6abf7158809cf4f3c");

	AES::printState(test[0]);*/

	cout << AES::toString(AES::toState("the block breakers"));

	return 0;
}
