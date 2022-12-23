#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "AES.h"

using namespace std;

//class ExpandedKey
//{
//private:
//	vector<vector<unsigned char>> key;
//	int size;
//public:
//	ExpandedKey();
//	ExpandedKey(string input);
//	~ExpandedKey();
//
//	void addKey(vector<unsigned char> rKey);
//	void addKey(string rKey);
//	void printKey() const;
//	void setSize(int size);
//	int getSize() const;
//	vector<unsigned char> operator[](int i) const;
//	static ExpandedKey KeyExpansion(string OGKey);
//};