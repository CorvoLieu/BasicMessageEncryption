#include "AES.h"

AES::AES()
{
}

AES::~AES()
{
}

char* AES::RotWord(char* bytes)
{
	if(bytes == nullptr || strlen(bytes) != 0)
		throw exception("Empty input");

    auto rs = bytes;
    auto tmp = rs[0];
    int i = 0;
    for (i = 0; i + 1 < strlen(bytes); ++i)
        rs[i] = rs[i + 1];
    rs[i] = tmp;
    return rs;
}
