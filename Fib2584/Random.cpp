#include "Random.h"

Random::Random()
{
    random_init(time(NULL));
}

Random::Random(unsigned long long seed)
{
	random_init(seed);
}

Random::~Random()
{
}

unsigned long long Random::get_rand_num()
{
	return random_value();
}
 
void Random::random_init(unsigned long long seed ) 
{
    unsigned long long i;
    ranctx_.a = 0xf1ea5eed, ranctx_.b = ranctx_.c = ranctx_.d = seed;
    for (i = 0; i < 20; ++i) {
        random_value();
    }
}

unsigned long long Random::random_value() 
{
    unsigned long long e = ranctx_.a - rotate_rand_num(ranctx_.b, 7);
    ranctx_.a = ranctx_.b ^ rotate_rand_num(ranctx_.c, 13);
    ranctx_.b = ranctx_.c + rotate_rand_num(ranctx_.d, 37);
    ranctx_.c = ranctx_.d + e;
    ranctx_.d = e + ranctx_.a;
    return ranctx_.d;
}