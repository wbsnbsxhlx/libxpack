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

	void packStructEnd();
	void packField(size_t* field);
	void packInt(size_t *field, bool sendZero, int64_t n);
	void packUint(size_t *field, bool sendZero, uint64_t n);
	void packRaw(size_t *field, bool sendZero, void* data, size_t size);

	void unpackInit(void* data, size_t size);

	size_t unpackPickField();
	size_t unpackField();
	uint64_t unpackUint(size_t *field);
	int64_t unpackInt(size_t *field);
	void unpackRaw(size_t *field, void** data, size_t* size);
private:

	void _packUint(uint64_t n);
	void _packInt(int64_t n);
	uint64_t _unpackUint();
	int64_t _unpackInt();
	PackBuffer _packBuffer;
	PackBuffer _unpackBuffer;
};

#endif // pack_packer_h__
