#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>

#include "State.h"
#include "ExpandedKey.h"

using namespace std;

class AES;

class ExpandedKey
{
private:
	vector<vector<unsigned char>> key;
	int size;
	int round;
public:
	ExpandedKey();
	ExpandedKey(string input);
	~ExpandedKey();

	void addKey(vector<unsigned char> rKey);
	void addKey(string rKey);
	void printKey() const;
	void setSize(int size);
	int getSize() const;
	int getRound() const;
	vector<unsigned char> operator[](int i) const;
	static ExpandedKey KeyExpansion(string OGKey);
};

class AES
{
private:
	static unsigned int rcon[256];
	static unsigned int multiplication_by_2[256];
	static unsigned int multiplication_by_3[256];
	static unsigned int multiplication_by_9[256];
	static unsigned int multiplication_by_11[256];
	static unsigned int multiplication_by_13[256];
	static unsigned int multiplication_by_14[256];

	static State prefixEn;
	static State prefixDe;

public:
	ExpandedKey key;

	AES();
	~AES();

	static unsigned int sbox_en[256];
	static unsigned int sbox_de[256];

	// Bytewise
	static bool getBitFrom(char byte, int loca);
	static vector<unsigned char> RotWord(vector<unsigned char> bytes);
	static vector<unsigned char> RotWordInverse(vector<unsigned char> bytes);
	static vector<unsigned char> SubWord(vector<unsigned char> bytes);
	static vector<unsigned char> SubWordInverse(vector<unsigned char> bytes);
	static vector<unsigned char> rCon(int val);
	static vector<unsigned char> XOR(vector<unsigned char> bytes1, vector<unsigned char> bytes2);

	// Statewise
	static State toState(string input);
	static string toString(State input);
	static void printState(State state);

	// Encrypt
	static State subState(State state);
	static State shiftRow(State state);
	static State mixColomnEn(State state);
	static State addRoundKey(State state, ExpandedKey k, int kIndex);
	static vector<State> encrypt(string plaintext, string key);

	// Decrypt
	static State subStateInverse(State state);
	static State shiftRowInverse(State state);
	static State mixColomnDe(State state);
	static string decrypt(vector<State> cipher, string key);
};


