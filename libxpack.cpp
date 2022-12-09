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

LIBXPACK_API void* pack_get_data(packer_t packerId, size_t* size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return nullptr; }

	return packer->getData(size);
}

LIBXPACK_API void pack_pack_struct_end(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packStructEnd();
}

LIBXPACK_API void pack_pack_field(packer_t packerId, size_t* field) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packField(field);
}

LIBXPACK_API void pack_pack_uint(packer_t packerId, size_t* field, bool sendZero, uint64_t n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packUint(field, sendZero, n);
}

LIBXPACK_API void pack_pack_int(packer_t packerId, size_t* field, bool sendZero, uint64_t n) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packInt(field, sendZero, n);
}

LIBXPACK_API void pack_pack_raw(packer_t packerId, size_t* field, bool sendZero, void* data, size_t size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->packRaw(field, sendZero, data, size);
}

LIBXPACK_API size_t pack_unpack_pick_field(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackPickField();
}

LIBXPACK_API size_t pack_unpack_field(packer_t packerId) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackField();
}

LIBXPACK_API void pack_unpack_init(packer_t packerId, void* data, size_t size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->unpackInit(data, size);
}

LIBXPACK_API uint64_t pack_unpack_uint(packer_t packerId, size_t* field) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackUint(field);
}

LIBXPACK_API uint64_t pack_unpack_int(packer_t packerId, size_t* field) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return 0; }

	return packer->unpackInt(field);
}

LIBXPACK_API void pack_unpack_raw(packer_t packerId, size_t* field, void** data, size_t* size) {
	Packer* packer = PackerManager::getInstance()->getPacker(packerId);
	if (packer == nullptr) { pack_log_error("packer is null:%d", packerId); return; }

	packer->unpackRaw(field, data, size);
}
