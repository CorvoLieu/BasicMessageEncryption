#include "State.h"

State::State()
{
	for (int i = 0; i < 4; i++)
	{
		vector<unsigned char> temp{ 0,0,0,0 };
		data.push_back(temp);
	}
}

State::State(const State& obj)
{
	this->data = obj.data;
}

State::State(vector<vector<unsigned char>> data)
{
	this->data = data;
}

State::~State()
{
}

State State::operator=(const State& obj)
{
	this->data = obj.data;
	return *this;
}

vector<unsigned char> State::operator[](int val) const
{
	return data[val];
}

vector<unsigned char>& State::operator[](int val)
{
	return data[val];
}

vector<unsigned char> State::getRow(int val) const
{
	vector<unsigned char> result;

	for (int i = 0; i < 4; i++)
	{
		result.push_back(data[i][val]);
	}

	return result;
}

void State::setRow(vector<unsigned char> newData, int val)
{
	for (int i = 0; i < 4; i++)
	{
		data[i][val] = newData[i];
	}
}
