#include <iostream>
#include <fstream>
#include "dos.h"
#include "rsa.h"
#include "State.h"
#include "AES.h"
#include "sha.h"
using namespace std;

void AliceSide()
{
	// Alice's doc
	string doc = "A";

	// Alice generates keypair 
	RSA* Alice = RSA::getInstance(5);
	cout << "Alice done gen key\n";

	// Alice takes from cloud
	ifstream AliceReadFile("cloud.txt");
	string B_pubkeyE, B_pubkeyN, B_title;
	while (AliceReadFile >> B_title)
	{
		if (B_title == "B-pub-key")
		{
			AliceReadFile >> B_pubkeyE >> B_pubkeyN;
			break;
		}
	}

	AliceReadFile.close();
	cout << "Alice done read\n";
	// Alice encrypts doc using AES
	string aes_key = "2b7e151628aed2a6abf7158809cf4f3c";
	auto C = AES::encrypt(doc, aes_key);

	cout << "Alice done en aes\n";
	// Alice creates signature by SHA
	SHA A_sign;
	A_sign.update(doc);
	uint8_t* digest = A_sign.digest();

	//cout << SHA::toString(digest) << '\n';
	string A_signature = SHA::toString(digest);

	delete[] digest;
	
	cout << "Alice done en sign\n";
	// Alice encrypts AES key with public keys
	BigInt en_aes_key = modulo(H2BI(aes_key), BigInt(B_pubkeyE), BigInt(B_pubkeyN));
	
	cout << "Alice done en aes\n";

	// Alice encrypts signature with private key of Alice
	BigInt en_A_sign = modulo(H2BI(A_signature), Alice->getD(), Alice->getN());

	cout << "Alice done en sign\n";
	// Alice send ciphertext, encrypted signature, encrypted AES key and public key to cloud
	ofstream AliceWriteFile("cloud.txt", ios::app);

	AliceWriteFile << "A-ciphertext ";
	for (auto i : C)
		AliceWriteFile << AES::getStrByte(i);

	AliceWriteFile << "\nA-en-aes-key " << en_aes_key << '\n'
		<< "A-en-sign " << en_A_sign << '\n'
		<< "A-pub-key " << Alice->getE() << ' ' << Alice->getN() << '\n';

	AliceWriteFile.close();

	cout << "Alice done write\n";
}

void test()
{
	cout << BI2H(BigInt("1232"));
	
}

int main()
{
	//test();
	//
	// Bob generates keypair
	RSA* Bob = RSA::getInstance(5);

	// Bob sends to cloud public key
	ofstream BobWriteFile("cloud.txt");

	BobWriteFile << "B-pub-key " << Bob->getE() << ' ' << Bob->getN() << '\n';

	BobWriteFile.close();

	cout << "Bob done write\n";

	AliceSide();
	cout << "Alice done\n";
	// Bob takes from cloud
	ifstream BobReadFile("cloud.txt");
	string c, A_en_sign, A_en_aeskey, A_title, A_pubkeyE, A_pubkeyN;

	while (BobReadFile >> A_title)
	{
		if (A_title == "A-ciphertext")
		{
			getline(BobReadFile, c);
			c.erase(c.begin());
		}

		if (A_title == "A-en-aes-key")
			BobReadFile >> A_en_aeskey;

		if (A_title == "A-en-sign")
			BobReadFile >> A_en_sign;

		if (A_title == "A-pub-key")
		{
			BobReadFile >> A_pubkeyE >> A_pubkeyN;
			break;
		}
	}

	BobReadFile.close();

	cout << "Bob done read\n";
	/* Bob gets the ciphertext and encrypted AES key, decrypt by private key*/
	BigInt A_de_aeskey = modulo(BigInt(A_en_aeskey), Bob->getD(), Bob->getN());

	cout << "Bob done de aes\n";
	/* Bob decrypt the doc*/
	cout << BI2H(A_de_aeskey);

	string m = AES::decrypt(AES::readStrByte(c), BI2H(A_de_aeskey));

	cout << "\nBob done de doc\n";
	// Bob gets (encrypted signature, public key) and decrypt to get the signature
	BigInt A_de_sign = modulo(BigInt(A_en_sign), BigInt(A_pubkeyE), BigInt(A_pubkeyN));
	cout << BI2H(A_de_sign);
	// Bob converts doc to hash signature and compare
	SHA B_sign;
	B_sign.update(m);
	uint8_t* _digest = B_sign.digest();

	string B_signature = SHA::toString(_digest);

	delete[] _digest;

	if (B_signature == BI2H(A_de_sign))
		cout << "\nDone";
	else
		cout << "\nOh no";

	return 0;
}