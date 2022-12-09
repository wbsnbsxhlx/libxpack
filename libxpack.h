// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBXPACK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBXPACK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef libxpack_h__
#define libxpack_h__

#ifdef LIBXPACK_EXPORTS
#define LIBXPACK_API __declspec(dllexport)
#else
#define LIBXPACK_API __declspec(dllimport)
#endif

#include <stdint.h>

extern "C" {
	typedef int32_t packer_t;

	const int INVALID_PACKER = -1;

	LIBXPACK_API packer_t pack_create(size_t buf_size);
	LIBXPACK_API void pack_destroy(packer_t* packerId);

	LIBXPACK_API void pack_pack_struct_end(packer_t packerId);
	LIBXPACK_API void* pack_get_data(packer_t packerId, size_t* size);
	LIBXPACK_API void pack_pack_field(packer_t packerId, size_t* field);
	LIBXPACK_API void pack_pack_int(packer_t packerId, size_t* field, bool sendZero, uint64_t n);
	LIBXPACK_API void pack_pack_uint(packer_t packerId, size_t* field, bool sendZero, uint64_t n);
	LIBXPACK_API void pack_pack_raw(packer_t packerId, size_t* field, bool sendZero, void* data, size_t size);

	LIBXPACK_API void pack_unpack_init(packer_t packerId, void* data, size_t size);
	LIBXPACK_API size_t pack_unpack_field(packer_t packerId);
	LIBXPACK_API uint64_t pack_unpack_uint(packer_t packerId, size_t* field);
	LIBXPACK_API uint64_t pack_unpack_int(packer_t packerId, size_t* field);
	LIBXPACK_API void pack_unpack_raw(packer_t packerId, size_t* field, void** data, size_t* size);
}

#endif // libxpack_h__