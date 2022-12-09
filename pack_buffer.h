#ifndef pack_buffer_h__
#define pack_buffer_h__

#include "libxpack.h"

class PackBuffer {
public:
	PackBuffer(size_t buf_size);
	~PackBuffer();

	void setBuf(uint8_t* data, size_t size);

	void write(uint8_t* data, size_t size);
	size_t size() { return _size; }
	void reset();
	uint8_t* data(size_t* size);
	void drop(size_t n);

	void read(uint8_t* data, size_t size);
	void pick(uint8_t* data, size_t size);

private:
	void _checkSize(size_t size);
	uint8_t* _buf;
	size_t _size;
	size_t _cap;
	size_t _offset;
};

#endif // pack_buffer_h__
