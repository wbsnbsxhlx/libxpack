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

	LIBXPACK_API packer_t xpack_create(size_t buf_size);
	LIBXPACK_API void xpack_destroy(packer_t* packerId);

	LIBXPACK_API void* xpack_pack_get_data(packer_t packerId, size_t* size);
	LIBXPACK_API void xpack_pack_clear(packer_t packerId);
	LIBXPACK_API void xpack_pack_int(packer_t packerId, int64_t n);
	LIBXPACK_API void xpack_pack_uint(packer_t packerId, uint64_t n);
	LIBXPACK_API void xpack_pack_float(packer_t packerId, double n);
	LIBXPACK_API void xpack_pack_raw(packer_t packerId, void* data, size_t size);

	LIBXPACK_API void xpack_unpack_init(packer_t packerId, void* data, size_t size);
	LIBXPACK_API uint64_t xpack_unpack_uint(packer_t packerId);
	LIBXPACK_API uint64_t xpack_unpack_int(packer_t packerId);
	LIBXPACK_API void xpack_unpack_raw(packer_t packerId, void** data, size_t* size);
	LIBXPACK_API double xpack_unpack_float(packer_t packerId);
}

#endif // libxpack_h__