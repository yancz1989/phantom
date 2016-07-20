/*
* @Author: yancz1989
* @Date:   2016-07-18 23:47:41
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-20 10:49:41
*/

#ifndef PHANTOM_SEQUENCE_PANLINDROME_H
#define PHANTOM_SEQUENCE_PANLINDROME_H

#include <string>
#include <vector>
template <typename key_type>
class Manacher{
public:
	int panlindrome(key_type* seq, int l, int& left){
		int i, w, bl = l * 2 + 3, *rad = new int[bl], r = 0, p = 0, maxl = -1;
		memset(rad, 0, sizeof(int) * bl);
		key_type *buf = new key_type[bl];
		for(i = 0, w = 2; i < l; ++i)
			buf[w++] = seq[i], buf[w++] = '#';
		buf[0] = '$', buf[1] = '#', buf[w] = 0;
		for(i = 1; i < w; ++i){
			rad[i] = r > i ? min(rad[p * 2 - i], r - i) : 1;
			while(buf[i + rad[i]] == buf[i - rad[i]]) ++rad[i];
			if(i + rad[i] > r){
				p = i;
				r = i + rad[i];
			}
			if(maxl < rad[i]){
				maxl = rad[i];
				left = (buf[i] == '#') ? (i - rad[i]) / 2 : (i - 1 - rad[i]) / 2;
			}
		}
		delete rad;
		delete buf;
		return maxl - 1;
	}
};

#endif