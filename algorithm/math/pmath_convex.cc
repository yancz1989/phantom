/* 
* @Author: yancz1989
* @Date:   2015-11-21 16:23:46
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-08 16:07:39
*/

#include "computing_geometry.h"
double eps = 1e-8, *point;
int convex_hull[MAXN], idxs[MAXN], n;

int graham_convex_hull() {
  int k, top = 2;
  double lower = 10000000.0;
  for (int i = 0; i < n; ++i) {
    idxs[i] = i;
    if (lower > point[(i << 1) + 1]) {
      lower = point[(i << 1) + 1];
      k = i;
    }
  }
  idxs[n] = 0;
  if(k != 0) {SWAP_DOUBLE(point[k << 1], point[0]), SWAP_DOUBLE(point[(k << 1) + 1], point[1]);}
  sort(idxs + 1, idxs + n, multi_cmp);
  convex_hull[1] = idxs[1]; convex_hull[0] = 0; convex_hull[2] = idxs[2];
  for(int i = 3; i < n + 1; ++i){
    while(top >= 1 && MULTIP(convex_hull[top - 1], convex_hull[top], idxs[i]) < 0) --top;
    convex_hull[++top] = idxs[i];
  }
  return top;
}

double rotating_calipers(int top) {
  int anti = 1;
  double l = -1;
  for (int i = 0; i < top; ++i) {
    while (MULTIP(convex_hull[i], convex_hull[i + 1], convex_hull[anti + 1]) >
            MULTIP(convex_hull[i], convex_hull[i + 1], convex_hull[anti]))
      anti = (anti + 1) % top;
    l = MAX(l, MAX(DISTP(convex_hull[i], convex_hull[anti]), DISTP(convex_hull[i + 1], convex_hull[anti + 1])));
  }
  return l;
}