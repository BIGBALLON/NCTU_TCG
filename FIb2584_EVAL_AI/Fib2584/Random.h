#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <ctime>

class Random
{
private:
	struct RanCtx 
	{ 
		unsigned long long a;
		unsigned long long b;
		unsigned long long c;
		unsigned long long d;
	};

public:
	Random();
	Random(unsigned long long seed);
	~Random();
	unsigned long long get_rand_num();

private:
	inline unsigned long long rotate_rand_num(unsigned long long x, int k) {
		return (x << k) | (x >> (64 - k));
	}
	void random_init(unsigned long long seed);
	unsigned long long random_value();

private:
	RanCtx ranctx_;
};

#endif
