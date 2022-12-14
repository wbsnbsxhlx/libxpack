#include <string.h>
#include "pack_buffer.h"

PackBuffer::PackBuffer(size_t buf_size)
	:_size(0), 
	_cap(buf_size), 
	_offset(0) {
	if (buf_size != 0){
		_buf = new uint8_t[buf_size];
	} else {
		_buf = nullptr;
	}
}

PackBuffer::~PackBuffer() {
	if (_buf != nullptr){
		delete[] _buf;
		_buf = nullptr;
	}
}

void PackBuffer::setBuf(uint8_t* data, size_t size) {
	_cap = size;
	_size = size;
	_offset = 0;
	_buf = data;
}

void PackBuffer::write(uint8_t* data, size_t size) {
	_checkSize(size);
	memcpy(_buf+_size, data, size);
	_size += size;
}

void PackBuffer::_checkSize(size_t size) {
	if (_size+size > _cap){
		uint8_t *oldBuffer = _buf;
		_cap += _cap >> 1;
		_buf = new uint8_t[_cap];
		memcpy(_buf, oldBuffer, _size);

		delete[] oldBuffer;
	}
}

void PackBuffer::reset() {
	_offset = 0;
	_size = 0;
}

uint8_t* PackBuffer::data(size_t* size) {
	if (size != nullptr){
		*size = _size;
	}
	return _buf+_offset;
}

void PackBuffer::drop(size_t n) {
	_offset += n;
}

void PackBuffer::read(uint8_t* data, size_t size) {
	memcpy(data, _buf+_offset, size);
	_offset += size;
}

void PackBuffer::pick(uint8_t* data, size_t size) {
	memcpy(data, _buf + _offset, size);
}