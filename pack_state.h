// #ifndef pack_state_h__
// #define pack_state_h__
// 
// #include "libxpack.h"
// #include "pack_packer.h"
// #include "pack_buffer.h"
// 
// class PackState {
// public:
// 	PackState(Packer* packer);
// 	~PackState();
// 
// 	void packUint(uint64_t n);
// 	void packInt(int64_t n);
// 	void packField(int field);
// 	void reset();
// 
// 	PackState* next;
// 
// 	PackBuffer* packBuffer;
// 	int fieldnum;
// private:
// 	Packer* _packer;
// 	uint8_t _buf[9];
// };
// 
// #endif // pack_state_h__
