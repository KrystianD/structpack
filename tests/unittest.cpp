#include <gtest/gtest.h>

#include "../structpack.h"

#define ASSERT_EQ_ARRAY(a1,a2,len) \
	{ for (int i = 0; i < len; i++) { ASSERT_EQ((uint8_t)a2[i], (uint8_t)a1[i]); } }

uint8_t buf[100];

TEST(structpack, test_uint32)
{
	int r = StructPack::pack(buf, 100, "L", 0xaabbccdd);

	ASSERT_EQ(r, 4);
	ASSERT_EQ_ARRAY(buf, "\xdd\xcc\xbb\xaa", r);

	uint32_t v;
	r = StructPack::unpack(buf, 100, "L", &v);

	ASSERT_EQ(r, 4);
	ASSERT_EQ(v, 0xaabbccdd);
}

TEST(structpack, test_uint8)
{
	int r = StructPack::pack(buf, 100, "B", 0xab);

	ASSERT_EQ(r, 1);
	ASSERT_EQ_ARRAY(buf, "\xab", r);

	uint8_t v;
	r = StructPack::unpack(buf, 100, "B", &v);

	ASSERT_EQ(r, 1);
	ASSERT_EQ(v, 0xab);
}

TEST(structpack, test_string)
{
	int r = StructPack::pack(buf, 100, "6s", "test", 4);

	ASSERT_EQ(r, 6);
	ASSERT_EQ_ARRAY(buf, "test\x00\x00", r);

	char buf2[100];
	r = StructPack::unpack(buf, 100, "6s", buf2, 100);

	ASSERT_EQ(r, 6);
	ASSERT_EQ_ARRAY(buf2, "test\x00\x00", 6);
}

TEST(structpack, test_array)
{
	uint8_t a[] = { 1, 2, 3, 4, 5 };
	uint32_t b[] = { 0xaabbccdd, 0x11223344 };
	float c[] = { 1.23, 2.45 };
	int r = StructPack::pack(buf, 100, "5B2L2f", a, b, c);

	ASSERT_EQ(r, 21);
	ASSERT_EQ_ARRAY(buf, "\x01\x02\x03\x04\x05\xdd\xcc\xbb\xaa\x44\x33\x22\x11\xa4\x70\x9d\x3f\xcd\xcc\x1c\x40", r);

	uint8_t a2[5];
	uint32_t b2[2];
	float c2[2];
	r = StructPack::unpack(buf, 100, "5B2L2f", a2, b2, c2);

	ASSERT_EQ(r, 21);
	ASSERT_EQ(a2[0], 1);
	ASSERT_EQ(a2[1], 2);
	ASSERT_EQ(a2[2], 3);
	ASSERT_EQ(a2[3], 4);
	ASSERT_EQ(a2[4], 5);
	ASSERT_EQ(b2[0], 0xaabbccdd);
	ASSERT_EQ(b2[1], 0x11223344);
	ASSERT_EQ(c2[0], 1.23f);
	ASSERT_EQ(c2[1], 2.45f);
}

TEST(structpack, test_combined)
{
	uint32_t a = 34678, c = 1234;
	uint8_t b = 45;
	int r = StructPack::pack(buf, 100, "LBL6s", a, b, c, "test", 4);

	ASSERT_EQ(r, 15);
	ASSERT_EQ_ARRAY(buf, "\x76\x87\x00\x00\x2d\xd2\x04\x00\x00test\x00\x00", r);

	uint32_t a2, c2;
	uint8_t b2;
	char buf2[100];

	r = StructPack::unpack(buf, 100, "LBL6s", &a2, &b2, &c2, buf2, 100);

	ASSERT_EQ(r, 15);
	ASSERT_EQ(a, a2);
	ASSERT_EQ(b, b2);
	ASSERT_EQ(c, c2);
	ASSERT_EQ_ARRAY(buf2, "test\x00\x00", 6);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
