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
