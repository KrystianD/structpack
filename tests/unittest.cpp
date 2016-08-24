#include <gtest/gtest.h>

#include "../structpack.h"

#define ASSERT_EQ_ARRAY(a1,a2,len) \
	{ for (int i = 0; i < len; i++) { ASSERT_EQ((uint8_t)a2[i], (uint8_t)a1[i]); } }

uint8_t buf[100];

TEST(structpack, test1)
{
	int r = StructPack::pack(buf, 100, "L", 123);

	ASSERT_EQ(r, 4);
	ASSERT_EQ_ARRAY(buf, "\x7b\x00\x00\x00", r);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
