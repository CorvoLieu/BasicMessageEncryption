#include <iostream>
#include "dos.h"
#include "rsa_keygen.h"
using namespace std;

int main()
{
	char choice;
	cout << ((DEBUG) ? "-------------Key Generator Started-------------\n" : "");
	cout << ((DEBUG) ? "Select key size:\n1. 512 bits\n2. 1024 bits\n3. 2048 bits\n" : "");
	cout << ((DEBUG) ? "-----------------\nYou select: " : "");

	cin >> choice;
	
	int len = 0;

	if (choice == '1')
		len = 155;

	if (choice == '2')
		len = 309;

	if (choice == '3')
		len = 617;

	RSA* rsa = RSA::getInstance(len);
	cout << "Public key (E):" << rsa->getE() << "- " << Length(rsa->getE()) << " digits\n";
	cout << "Public key (N):" << rsa->getN() << "- " << Length(rsa->getN()) << " digits\n";
	cout << "Private key (D):" << rsa->getD() << "- " << Length(rsa->getD()) << " digits\n";

	return 0;
}
