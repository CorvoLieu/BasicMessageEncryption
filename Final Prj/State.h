#pragma once
#include <iostream>
#include <vector>
using namespace std;

class State
{
public:
	vector<vector<unsigned char>> data;

	State();
	State(const State& obj);
	State(vector<vector<unsigned char>> data);
	~State();

	State operator=(const State& obj);
	vector<unsigned char> operator[](int val) const;
	vector<unsigned char>& operator[](int val);
	vector<unsigned char> getRow(int val) const;
	void setRow(vector<unsigned char> newData, int val);
};

