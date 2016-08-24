#ifndef __STRUCTPACK_H__
#define __STRUCTPACK_H__

#include <stdint.h>
#include <stdarg.h>

class StructPack {
	uint8_t* buffer;
	uint32_t pos, maxLen;

	const char* format;
	va_list arg;

public:
	StructPack(const char* format, va_list inArg);
	StructPack(const char* format, va_list inArg, void* buffer, uint32_t maxLen);
	~StructPack();

	int doPack();
	int doUnpack();

	static int pack(void* buffer, uint32_t maxLen, const char* format, ...);
	static int unpack(const void* buffer, uint32_t maxLen, const char* format, ...);

private:
	void pack_uint8(uint8_t val);
	void pack_uint32(uint32_t val);
	void pack_float(float val);
	void pack_string(const char* str, int len, int width);
	void emit(uint8_t byte);

	void unpack_uint8(uint8_t* val);
	void unpack_uint32(uint32_t* val);
	void unpack_float(float* val);
	void unpack_string(char* str, int len, int width);
	uint8_t fetch();
};

#endif
