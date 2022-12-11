#include "pack_packer.h"
#include "pack_util.h"
#include <WinSock2.h>
#include <assert.h>

const uint64_t m3 = 0x00ff00ff00ff00ff;
const uint64_t m4 = 0x0000ffff0000ffff;

uint64_t reverseUint(uint64_t n) {
	n = n >> 8 & m3 | (n&m3) << 8;
	n = n >> 16 & m4 | (n&m4) << 16;
	return n >> 32 | n << 32;
}

Packer::Packer(size_t buf_size)
	:_packBuffer(buf_size),
	_unpackBuffer(0){

}

Packer::~Packer() {

}

void Packer::clear() {
	_packBuffer.reset();
}

uint8_t* Packer::getData(size_t* size) {
	return _packBuffer.data(size);
}

void Packer::packRaw(void* data, size_t size) {
	packUint(size);
	_packBuffer.write((uint8_t*)data, size);
}

void Packer::packUint(uint64_t n) {
	if (n <= 0x7f) {
		uint8_t nn = uint8_t(n);
		_packBuffer.write(&nn, 1);
		return;
	}

	uint8_t buf[9];

	uint64_t nn = htonll(n);
	memcpy(buf + 1, &nn, 8);
	int bc = leadingZeros64(n) >> 3;
	buf[bc] = uint8_t(bc - 8);
	_packBuffer.write(buf + bc, 9 - bc);
}

void Packer::packInt(int64_t n) {
	uint64_t x;
	if (n < 0) {
		x = (uint64_t)(~n << 1) | 1;
	} else {
		x = (uint64_t)(n << 1);
	}

	packUint(x);
}

void Packer::packFloat(double n) {
	packUint(reverseUint(*((uint64_t*)&n)));
}

void Packer::unpackInit(void* data, size_t size) {
	_unpackBuffer.setBuf((uint8_t*)data, size);
}

uint64_t Packer::unpackUint() {
	uint8_t b;
	_unpackBuffer.read(&b, 1);
	if (b <= 0x7f) {
		return b;
	}

	size_t n = -((int8_t)b);
	assert(n <= 8);

	uint64_t ret = 0;
	for (int i = 0; i < n; i++) {
		_unpackBuffer.read(&b, 1);
		ret = ret << 8 | b;
	}
	return ret;
}

int64_t Packer::unpackInt() {
	uint64_t ret = unpackUint();
	if (ret & 1 != 0) {
		return ~(int64_t)(ret >> 1);
	}
	return ret >> 1;
}

double Packer::unpackFloat() {
	uint64_t n = reverseUint(unpackUint());
	double d = *((double *)&n);

	return *((double *)&n);
}

void Packer::unpackRaw(void** data, size_t* size) {
	*size = unpackUint();
	*data = _unpackBuffer.data(nullptr);
	_unpackBuffer.drop(*size);
}