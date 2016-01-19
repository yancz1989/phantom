#ifndef ALGORITHM_GEOMETRY_UTIL_H
#define ALGORITHM_GEOMETRY_UTIL_H

namespace phantom{
namespace algorithm{
namespace computing_geometry{
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