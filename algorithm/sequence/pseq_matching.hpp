/*
* @Author: yancz1989
* @Date:   2016-07-17 09:11:45
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-21 08:01:33
*/

#ifndef PHANTOM_SEQUENCE_MATCHING_H
#define PHANTOM_SEQUENCE_MATCHING_H

#include "../phantom_algorithm.h"

namespace phantom{
namespace algorithm
namespace sequence{

template<typename key_type>
class RabinKarp{
public:
  RabinKarp() : low('a'){};
  int64 hash(key_type* seq, int l, int64 base){
    int64 v = 0;
    for(int i = 0; i < l; ++i)
      v = v * base + seq[i] - low;
    return v;
  }

  int64 pow(int64 x, int e){
    int64 v = 1, b = x;
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
    int64 v = hash(tmpl, ltmpl, base), s = hash(seq, ltmpl - 1, base), mod = pow(base, ltmpl);
    for(int i = ltmpl - 1; i < lstr; ++i){
      s = s * base % mod + seq[i] - low;
      if(s == v)
        indexes.push_back(i);
    }
    return indexes;
  }

  vector<int64> all_keys(key_type* seq, int lstr, int ltmpl, int64 base){
    vector<int64> keys;
    int cnt = 0;
    int64 v = hash(seq, ltmpl - 1, base), mod = pow(base, ltmpl);
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
}
}
}

#endif