// libxpack.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdio.h"

#include "libxpack.h"
#include "pack_packer_manager.h"
#include "pack_log.h"
#include "pack_packer.h"

LIBXPACK_API packer_t xpack_create(size_t buf_size) {
	return PackerManager::getInstance()->createPacker(buf_size);
}

LIBXPACK_API void xpack_destroy(packer_t* packerId) {
	PackerManager::getInstance()->destroyPacker(*packerId);
	*packerId = INVALID_PACKER;
}

LIBXPACK_API void* xpack_pack_get_data(packer_t packerId, size_t* size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return nullptr; }

	return packer->getData(size);
}

LIBXPACK_API void xpack_pack_clear(packer_t packerId){
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->clear();
}

LIBXPACK_API void xpack_pack_uint(packer_t packerId,uint64_t n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packUint(n);
}

LIBXPACK_API void xpack_pack_int(packer_t packerId, int64_t n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packInt(n);
}

LIBXPACK_API void xpack_pack_float(packer_t packerId, double n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packFloat(n);
}

LIBXPACK_API void xpack_pack_raw(packer_t packerId, void* data, size_t size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packRaw(data, size);
}

LIBXPACK_API void xpack_unpack_init(packer_t packerId, void* data, size_t size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->unpackInit(data, size);
}

LIBXPACK_API uint64_t xpack_unpack_uint(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackUint();
}

LIBXPACK_API uint64_t xpack_unpack_int(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackInt();
}

LIBXPACK_API double xpack_unpack_float(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackFloat();
}

LIBXPACK_API void xpack_unpack_raw(packer_t packerId, void** data, size_t* size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->unpackRaw(data, size);
}
