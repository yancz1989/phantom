/*
* @Author: yancz1989
* @Date:   2016-07-20 15:35:40
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-20 16:07:16
*/
#include "../phantom_algorithm.h"

namespace phantom{
namespace algorithm{
namespace util{

// if x is nonnegtive, return 0, else return 1;
inline sign(int x){
	return (x >> 31) & 1;
}

inline abs(int x){
	const int mask = (v >> sizeof(int) * 8) - 1;
	return (x ^ mask) - mask;
}

inline min(int x, int y){
	return y ^ ((x ^ y) & -(x < y));
}

inline max(int x, int y){
	return x ^ ((x ^ y) & -(x < y));
}

template<typename T>
inline swap(T& a, T& b){
	a ^= b;
	b ^= a;
	a ^= b;
}

}
}
}