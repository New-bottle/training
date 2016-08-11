#include <iostream>

int buf[1 << 8];

#define NAND(a, b) (!((a) && (b)))

bool test1(int k)
{
	bool x1, x2;
	bool fail;
	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 2);
		if (!(x1 && x2) ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 4);
		if (!(x1 && x2) ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 2);
		x2 = !!(i & 4);
		if (!(x1 && x2) ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	return false;
}

bool test2(int k)
{
	bool x1, x2, x3;
	bool fail;
	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 2);
		x3 = !!(i & 4);
		bool a = !(x1 && x2);
		bool b = !(a && x3);
		if (b ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 4);
		x3 = !!(i & 2);
		bool a = !(x1 && x2);
		bool b = !(a && x3);
		if (b ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 2);
		x2 = !!(i & 4);
		x3 = !!(i & 1);
		bool a = !(x1 && x2);
		bool b = !(a && x3);
		if (b ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	return false;
}

bool test3(int k)
{
	bool x1, x2, x3;
	bool fail;
	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 2);
		x3 = !!(i & 4);
		bool a = !(x1 && x2);
		bool b = !(x1 && x3);
		bool c = !(a && b);
		if (c ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 2);
		x3 = !!(i & 4);
		bool a = !(x1 && x2);
		bool b = !(x2 && x3);
		bool c = !(a && b);
		if (c ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	fail = false;
	for (int i = 0; i < 8; ++i) {
		x1 = !!(i & 1);
		x2 = !!(i & 2);
		x3 = !!(i & 4);
		bool a = !(x1 && x3);
		bool b = !(x2 && x3);
		bool c = !(a && b);
		if (c ^ (k >> i & 1)) {
			fail = true;
			break;
		}
	}
	if (!fail)
		return true;

	return false;
}


int main()
{
	for (int i = 0; i < 256; ++i) {
		if (test1(i))
			buf[i] = 1;
		else if (test2(i))
			buf[i] = 2;
		else if (test3(i))
			buf[i] = 3;
		std::cout << i << ' ' << buf[i] << std::endl;
	}
}
