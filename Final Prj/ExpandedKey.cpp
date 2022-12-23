//#include "ExpandedKey.h"
//
//ExpandedKey::ExpandedKey()
//{
//	size = 128;
//}
//
//ExpandedKey::ExpandedKey(string input)
//{
//	for (int i = 0; i < input.length(); i += 8)
//	{
//		vector<unsigned char> tempVec;
//		for (int j = 0; j < 8; j += 2)
//		{
//			string temp = "0x";
//			temp += input[i + j];
//			temp += input[i + j + 1];
//			tempVec.push_back(stoul(temp, nullptr, 16));
//		}
//		key.push_back(tempVec);
//	}
//	size = 128;
//}
//
//ExpandedKey::~ExpandedKey()
//{
//}
//
//ExpandedKey ExpandedKey::KeyExpansion(string OGKey)
//{
//	ExpandedKey result(OGKey);
//
//	for (int iter = 0; iter < (10.0 / 128 * result.getSize()); iter++)
//	{
//		auto newKSeed = result[iter * 4 + 3];
//		newKSeed = AES::RotWord(newKSeed);
//		newKSeed = AES::SubWord(newKSeed);
//		newKSeed = AES::XOR(newKSeed, result[iter * 4]);
//		newKSeed = AES::XOR(newKSeed, AES::rCon(iter + 1));
//
//		result.addKey(newKSeed);
//		for (int i = 1; i <= 3; i++)
//		{
//			auto temp = AES::XOR(result[iter * 4 + 3 + i], result[iter * 4 + i]);
//			result.addKey(temp);
//		}
//	}
//
//	return result;
//}
//
//void ExpandedKey::addKey(vector<unsigned char> rKey)
//{
//	key.push_back(rKey);
//}
//
//void ExpandedKey::addKey(string rKey)
//{
//	for (int i = 0; i < rKey.length(); i += 8)
//	{
//		vector<unsigned char> tempVec;
//		for (int j = 0; j < 8; j += 2)
//		{
//			string temp = "0x";
//			temp += rKey[i + j];
//			temp += rKey[i + j + 1];
//			tempVec.push_back(stoul(temp, nullptr, 16));
//		}
//		key.push_back(tempVec);
//	}
//}
//
//vector<unsigned char> ExpandedKey::operator[](int i) const
//{
//	return key[i];
//}
//
//void ExpandedKey::printKey() const
//{
//	for (int i = 0; i < key.size(); i++)
//	{
//		for (int j = 0; j < key[i].size(); j++)
//		{
//			cout << hex << (unsigned int)key[i][j] << ' ';
//		}
//		cout << '\n';
//	}
//}
//
//void ExpandedKey::setSize(int size)
//{
//	switch (size)
//	{
//	case 192: case 256:
//	{
//		this->size = size;
//	}
//	default:
//		this->size = 128;
//	}
//}
//
//int ExpandedKey::getSize() const
//{
//	return size;
//}
