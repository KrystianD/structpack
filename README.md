# structpack
Simple C++ serialization library (with Python struct.pack-like interface)

[![Build Status](https://travis-ci.org/KrystianD/structpack.svg?branch=master)](https://travis-ci.org/KrystianD/structpack)

# Example
```c++
uint8_t buf[100];

uint32_t a = 34678, c = 1234;
uint8_t b = 45;
int r = StructPack::pack(buf, 100, "LBL6s", a, b, c, "test", 4);
```
`buf` now contains:
```
\x76\x87\x00\x00\x2d\xd2\x04\x00\x00test\x00\x00
```
