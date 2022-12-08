#include "pack_packer.h"
#include "pack_state.h"
#include "pack_util.h"
#include <WinSock2.h>

Packer::Packer(size_t buf_size)
	:_packBuffer(buf_size),
	_freeStateList(nullptr) {

}

Packer::~Packer() {

}

//PackState* Packer::_getFreeState(PackBuffer* pb) {
//	PackState* state = _freeStateList;
//	if (state == nullptr) {
//		state = new PackState(this);
//	} else {
//		_freeStateList = state->next;
//	}
//
//	state->fieldnum = 0;
//	state->packBuffer = pb;
//	return state;
//}
//
//void Packer::_freeState(PackState* state) {
//	state->next = _freeStateList;
//	_freeStateList = state;
//}

void Packer::clear() {
	_packBuffer.reset();
}


void Packer::_packUint(uint64_t n) {
	if (n <= 0x7F) {
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

void Packer::_packField(size_t* field) {
	if (*field > 0) {
		_packUint((uint64_t)(*field));
		*field = 1;
	}
}

void Packer::packUint(size_t *field, uint64_t n) {
	if (n != 0) {
		_packField(field);
		_packUint(n);
	} else if (*field > 0) {
		*field += 1;
	}
}
