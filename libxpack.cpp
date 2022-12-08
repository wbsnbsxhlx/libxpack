// libxpack.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdio.h"

#include "libxpack.h"
#include "pack_packer_manager.h"
#include "pack_log.h"
#include "pack_packer.h"


LIBXPACK_API packer_t pack_create(size_t buf_size) {
	return PackerManager::getInstance()->createPacker(buf_size);
}

LIBXPACK_API void pack_destroy(packer_t* packerId) {
	PackerManager::getInstance()->destroyPacker(*packerId);
	*packerId = INVALID_PACKER;
}

LIBXPACK_API void pack_pack_uint(packer_t packerId, size_t* field, uint64_t n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) {
		pack_log_error("packer is null:%d", packerId);
		return;
	}

	packer->packUint(field, n);
	//if (n != 0) {
	//	packer->packField(*field);
	//	packer->packUint(n);
	//	*field = 1;
	//} else {
	//	*field+=1;
	//}
}

LIBXPACK_API void pack_pack_raw(packer_t packerId, size_t field, void* data, size_t size) {

}
