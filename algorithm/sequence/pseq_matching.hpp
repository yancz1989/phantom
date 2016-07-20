/*
* @Author: yancz1989
* @Date:   2016-07-17 09:11:45
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-18 11:33:10
*/

#ifndef PHANTOM_SEQUENCE_MATCHING_H
#define PHANTOM_SEQUENCE_MATCHING_H

#include <cstdio>
#include <cstring>

#define LL long long

template<typename key_type>
class RabinKarp{
public:
	RabinKarp() : low('a'){};
	LL hash(key_type* seq, int l, LL base){
		LL v = 0;
		for(int i = 0; i < l; ++i)
			v = v * base + seq[i] - low;
		return v;
	}

	LL pow(LL x, int e){
		LL v = 1, b = x;
		while(e > 0){
			if((e & 1) == 1)
				v = v * b;
			b = b * b;
			e = e >> 1;
		}
		return v;
	}

	// tmpl, tmplate to match, seq source string.
	vector<int> index(key_type* seq, key_type* tmpl, int lstr, int ltmpl){
		vector<int> indexes(0);
		int base = 26;
		LL v = hash(tmpl, ltmpl, base), s = hash(seq, ltmpl - 1, base), mod = pow(base, ltmpl);
		for(int i = ltmpl - 1; i < lstr; ++i){
			s = s * base % mod + seq[i] - low;
			if(s == v)
				indexes.push_back(i);
		}
		return indexes;
	}

	vector<LL> all_keys(key_type* seq, int lstr, int ltmpl, LL base){
		vector<LL> keys;
		int cnt = 0;
		LL v = hash(seq, ltmpl - 1, base), mod = pow(base, ltmpl);
		key_type* trunk = new key_type[mod];
		memset(trunk, 0, mod);
		for(int i = ltmpl - 1; i < lstr; ++i){
			v = v * base % mod + seq[i] - low;
			trunk[v] = 1;
		}
		for(int i = 0; i < mod; ++i)
			if(trunk[i] == 1)
				keys.push_back(i);
		return keys;
	}
private:
	key_type low;
};

template<typename key_type>
class KMP{
public:
	vector<int> index(key_type* seq, key_type* tmpl, int lstr, int ltmpl){
		int *next = new int[ltmpl], j = 0, i = 0;
		vector<int> indexes;
		build_next(tmpl, ltmpl, next);
		while(i < lstr){
			if(tmpl[j] == seq[i]){
				++j, ++i;
				if(j == ltmpl){
					indexes.push_back(i - j);
					j = next[j - 1];
				}
			} else {
				if(j != 0)
					j = next[j - 1];
				else
					i = i + 1;
			}
		}
		delete next;
		return indexes;
	}

	void build_next(key_type* tmpl, int ltmpl, int* next){
		int i = 1, j = 0;
		next[0] = 0;
		while(i < ltmpl){
			if(tmpl[i] == tmpl[j])
				next[i++] = ++j;
			else{
				if(j != 0)
					j = next[j - 1];
				else
					next[i++] = 0;
			}
		}
	}
};

#endif