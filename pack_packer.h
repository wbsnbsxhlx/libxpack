#ifndef pack_packer_h__
#define pack_packer_h__

#include "libxpack.h"
#include "pack_buffer.h"

class PackState;
class Packer {
public:
	Packer(size_t buf_size);
	~Packer();

	void clear();

	void packUint(size_t *field, uint64_t n);
private:
	//PackState* _getFreeState(PackBuffer* pb);
	//void _freeState(PackState* state);

	void _packUint(uint64_t n);
	void _packInt(int64_t n);
	void _packField(size_t* field);

	PackBuffer _packBuffer;

	PackState* _freeStateList;
};

#endif // pack_packer_h__
