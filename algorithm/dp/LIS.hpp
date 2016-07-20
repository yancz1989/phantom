/*
* @Author: yancz1989
* @Date:   2016-07-16 22:06:46
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-17 00:37:03
* POJ 1631
*/

class LISSolver{
public:
	int solve(int nums[], int n){
		int *nums = new int[N], *dp = new int[N], l, r, mid, idx = 0;
		dp[0] = nums[0];
		for(int i = 1; i < n; ++i){
			if(nums[i] <= dp[0])
				dp[0] = nums[i];
			else if(nums[i] > dp[idx])
				dp[++idx] = nums[i];
			else{
				l = 0;
				r = idx;
				while(l <= r){
					mid = (l + r) >> 1;
					if(nums[i] > dp[mid] && nums[i] <= dp[mid + 1])
						break;
					else if(dp[mid] > nums[i])
						r = mid - 1;
					else
						l = mid + 1;
				}
				dp[mid + 1] = nums[i];
			}
		}
		return idx + 1;
	}
}