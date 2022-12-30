#include "sha.h"
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;

SHA::SHA() : mBlockLen(0), mBitLen(0) {
	mState[0] = 0x6a09e667;
	mState[1] = 0xbb67ae85;
	mState[2] = 0x3c6ef372;
	mState[3] = 0xa54ff53a;
	mState[4] = 0x510e527f;
	mState[5] = 0x9b05688c;
	mState[6] = 0x1f83d9ab;
	mState[7] = 0x5be0cd19;
}

void SHA::update(const uint8_t* data, size_t length) {
	for (size_t i = 0; i < length; i++) {
		mData[mBlockLen++] = data[i];
		if (mBlockLen == 64) {
			transform();

			// End of the block
			mBitLen += 512;
			mBlockLen = 0;
		}
	}
}

void SHA::update(const string& data) {
	update(reinterpret_cast<const uint8_t*> (data.c_str()), data.size());
}

uint8_t* SHA::digest() {
	uint8_t* hash = new uint8_t[32];

	pad();
	revert(hash);

	return hash;
}

uint32_t SHA::rotr(uint32_t x, uint32_t n) {
	return (x >> n) | (x << (32 - n));
}

uint32_t SHA::choose(uint32_t e, uint32_t f, uint32_t g) {
	return (e & f) ^ (~e & g);
}

uint32_t SHA::majority(uint32_t a, uint32_t b, uint32_t c) {
	return (a & (b | c)) | (b & c);
}

uint32_t SHA::sig0(uint32_t x) {
	return SHA::rotr(x, 7) ^ SHA::rotr(x, 18) ^ (x >> 3);
}

uint32_t SHA::sig1(uint32_t x) {
	return SHA::rotr(x, 17) ^ SHA::rotr(x, 19) ^ (x >> 10);
}

void SHA::transform() {
	uint32_t maj, xorA, ch, xorE, sum, newA, newE, m[64];
	uint32_t state[8];

	for (uint8_t i = 0, j = 0; i < 16; i++, j += 4) { // Split data in 32 bit blocks for the 16 first words
		m[i] = (mData[j] << 24) | (mData[j + 1] << 16) | (mData[j + 2] << 8) | (mData[j + 3]);
	}

	for (uint8_t k = 16; k < 64; k++) { // Remaining 48 blocks
		m[k] = SHA::sig1(m[k - 2]) + m[k - 7] + SHA::sig0(m[k - 15]) + m[k - 16];
	}

	for (uint8_t i = 0; i < 8; i++) {
		state[i] = mState[i];
	}

	for (uint8_t i = 0; i < 64; i++) {
		maj = SHA::majority(state[0], state[1], state[2]);
		xorA = SHA::rotr(state[0], 2) ^ SHA::rotr(state[0], 13) ^ SHA::rotr(state[0], 22);

		ch = choose(state[4], state[5], state[6]);

		xorE = SHA::rotr(state[4], 6) ^ SHA::rotr(state[4], 11) ^ SHA::rotr(state[4], 25);

		sum = m[i] + K[i] + state[7] + ch + xorE;
		newA = xorA + maj + sum;
		newE = state[3] + sum;

		state[7] = state[6];
		state[6] = state[5];
		state[5] = state[4];
		state[4] = newE;
		state[3] = state[2];
		state[2] = state[1];
		state[1] = state[0];
		state[0] = newA;
	}

	for (uint8_t i = 0; i < 8; i++) {
		mState[i] += state[i];
	}
}

void SHA::pad() {

	uint64_t i = mBlockLen;
	uint8_t end = mBlockLen < 56 ? 56 : 64;

	mData[i++] = 0x80; // Append a bit 1
	while (i < end) {
		mData[i++] = 0x00; // Pad with zeros
	}

	if (mBlockLen >= 56) {
		transform();
		memset(mData, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	mBitLen += mBlockLen * 8;
	mData[63] = mBitLen;
	mData[62] = mBitLen >> 8;
	mData[61] = mBitLen >> 16;
	mData[60] = mBitLen >> 24;
	mData[59] = mBitLen >> 32;
	mData[58] = mBitLen >> 40;
	mData[57] = mBitLen >> 48;
	mData[56] = mBitLen >> 56;
	transform();
}

void SHA::revert(uint8_t* hash) {
	// SHA uses big endian byte ordering
	// Revert all bytes
	for (uint8_t i = 0; i < 4; i++) {
		for (uint8_t j = 0; j < 8; j++) {
			hash[i + (j * 4)] = (mState[j] >> (24 - i * 8)) & 0x000000ff;
		}
	}
}

string SHA::toString(const uint8_t* digest) {
	stringstream s;
	s << setfill('0') << hex;

	for (uint8_t i = 0; i < 32; i++) {
		s << setw(2) << (unsigned int)digest[i];
	}

	return s.str();
}