#include "pack_packer.h"
#include "pack_util.h"
#include <WinSock2.h>
#include <assert.h>

Packer::Packer(size_t buf_size)
	:_packBuffer(buf_size),
	_unpackBuffer(0){

}

Packer::~Packer() {

}

void Packer::clear() {
	_packBuffer.reset();
}


void Packer::_packUint(uint64_t n) {
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

void Packer::_packInt(int64_t n) {
	uint64_t x;
	if (n < 0) {
		x = (uint64_t)(~n << 1) | 1;
	} else {
		x = (uint64_t)(n << 1);
	}

	_packUint(x);
}

uint64_t Packer::_unpackUint() {
	uint8_t b;
	_unpackBuffer.read(&b, 1);
	if (b <= 0x7f){
		return b;
	}

	size_t n = -((int8_t)b);
	assert(n <= 8);

	uint64_t ret = 0;
	for (int i = 0; i < n; i++){
		_unpackBuffer.read(&b, 1);
		ret = ret << 8 | b;
	}
	return ret;
}

int64_t Packer::_unpackInt() {
	uint64_t ret = _unpackUint();
	if (ret&1 != 0){
		return ~(int64_t)(ret >> 1);
	}
	return ret >> 1;
}

uint8_t* Packer::getData(size_t* size) {
	return _packBuffer.data(size);
}

void Packer::packStructEnd() {
	_packUint(0);
}

void Packer::packField(size_t* field) {
	if (field != nullptr && *field > 0) {
		_packUint((uint64_t)(*field));
		*field = 1;
	}
}

void Packer::packRaw(size_t *field, bool sendZero, void* data, size_t size) {
	if (size > 0 || sendZero) {
		packField(field);
		_packUint(size);
		_packBuffer.write((uint8_t*)data, size);
	} else if (field != nullptr && *field > 0) {
		*field += 1;
	}
}

void Packer::packUint(size_t *field, bool sendZero, uint64_t n) {
	if (n != 0 || sendZero) {
		packField(field);
		_packUint(n);
	} else if (field != nullptr && *field > 0) {
		*field += 1;
	}
}

void Packer::packInt(size_t *field, bool sendZero, int64_t n) {
	if (n != 0 || sendZero) {
		packField(field);
		_packInt(n);
	} else if (field != nullptr && *field > 0) {
		*field += 1;
	}
}

void Packer::unpackInit(void* data, size_t size) {
	_unpackBuffer.setBuf((uint8_t*)data, size);
}

size_t Packer::unpackField() {
	uint8_t ret;
	_unpackBuffer.read(&ret, 1);
	return ret;
}

size_t Packer::unpackPickField() {
	uint8_t ret;
	_unpackBuffer.pick(&ret, 1);
	return ret;
}

uint64_t Packer::unpackUint(size_t *field) {
	if (field == nullptr){
		return _unpackUint();
	}
	uint8_t delta;
	_unpackBuffer.pick(&delta, 1);
	if (*field != delta){
		*field += 1;
		return 0;
	}
	_unpackBuffer.drop(1);
	return _unpackUint();
}

int64_t Packer::unpackInt(size_t *field) {
	uint8_t delta;
	_unpackBuffer.pick(&delta, 1);
	if (*field != delta) {
		*field += 1;
		return 0;
	}

	_unpackBuffer.drop(1);
	return _unpackInt();
}

void Packer::unpackRaw(size_t *field, void** data, size_t* size) {
	uint8_t delta;
	_unpackBuffer.pick(&delta, 1);
	if (*field != delta) {
		*field += 1;
		*data = nullptr;
		*size = 0;
		return;
	}

	_unpackBuffer.drop(1);

	*size = _unpackUint();
	*data = _unpackBuffer.data(nullptr);
	_unpackBuffer.drop(*size);
}