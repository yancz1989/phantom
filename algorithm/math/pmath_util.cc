/* 
* @Author: yancz1989
* @Date:   2016-01-08 15:46:57
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-08 15:51:38
*/
#include "pmath.h"

bool multi_cmp(int i, int j) {
	double mul = MULTIP(0, i, j);
	return mul > eps ? true : (mul > -eps ? (DISTP(i, 0) > DISTP(j, 0) ? true : false) : false);
}