/*
* @Author: yancz1989
* @Date:   2016-07-15 10:33:00
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-15 10:34:08
*/
#ifndef PHANTOM_MATH_H
#define PHANTOM_MATH_H

namespace phantom{
namespace algorithm{
namespace math{
#define DIF(i, j, idx) (point[(i << 1) | idx] - point[(j << 1) | idx])
#define MULTIP(s, i, j) MULTI(DIF(i, s, 0), DIF(j, s, 0), DIF(i, s, 1), DIF(j, s, 1))
#define DISTP(i, j) DIST(point[i << 1], point[j << 1], point[(i << 1) + 1], point[(j << 1) + 1])
#define DIST(x1, x2, y1, y2) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define MULTI(x1, x2, y1, y2) (x1 * y2 - x2 * y1)
#define MAXN 10000
#define SWAP_DOUBLE(a, b) (a = a + b, b = a - b, a = a - b)
bool multi_cmp(int i, int j);
}
}
}

#endif