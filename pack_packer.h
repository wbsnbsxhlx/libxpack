#ifndef pack_packer_h__
#define pack_packer_h__

#include "libxpack.h"
#include "pack_buffer.h"

class Packer {
public:
	Packer(size_t buf_size);
	~Packer();

	void clear();

	uint8_t* getData(size_t* size);

	void packInt(int64_t n);
	void packFloat(double n);
	void packUint(uint64_t n);
	void packRaw(void* data, size_t size);

	void unpackInit(void* data, size_t size);

	uint64_t unpackUint();
	int64_t unpackInt();
	double unpackFloat();
	void unpackRaw(void** data, size_t* size);
private:

	PackBuffer _packBuffer;
	PackBuffer _unpackBuffer;
};

#endif // pack_packer_h__
