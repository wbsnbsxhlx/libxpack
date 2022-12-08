// #include "pack_state.h"
// #include "pack_util.h"
// #include <winsock2.h>
// 
// PackState::PackState(Packer* packer)
// 	:_packer(packer) {
// 
// }
// 
// PackState::~PackState() {
// 
// }
// 
// void PackState::packUint(uint64_t n) {
// 	if (n <= 0x7F){
// 		uint8_t nn = uint8_t(n);
// 		packBuffer->write(&nn, 1);
// 		return;
// 	}
// 
// 	uint64_t nn = htonll(n);
// 	memcpy(_buf + 1, &nn, 8);
// 	int bc = leadingZeros64(n) >> 3;
// 	_buf[bc] = uint8_t(bc - 8);
// 	packBuffer->write(_buf + bc, 9 - bc);
// }
// 
// void PackState::packInt(int64_t n) {
// 	uint64_t x;
// 	if (n < 0){
// 		x = (uint64_t)(~n << 1) | 1;
// 	} else {
// 		x = (uint64_t)(n << 1);
// 	}
// 	
// 	packUint(x);
// }
// 
// void PackState::packField(int field) {
// 	if (field > 0){
// 		packUint((uint64_t)(field-fieldnum));
// 		fieldnum = field;
// 	}
// }
