// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBXPACK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBXPACK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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