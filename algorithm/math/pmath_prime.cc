/*
* @Author: yancz1989
* @Date:   2016-07-15 10:33:00
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-15 10:34:08
*/

vector<int> all_primes(int range){
	char *bitmap = new char[range];
	vector<int> primes(0);
	int tmp;
	memset(bitmap, 0, sizeof(bitmap));
	for(i = 2; i < RANGE; ++i){
		if(!bitmap[i]){
			for(int k = i; k < RANGE; k = k + i)
				bitmap[k] = 1;
			primes.push_back(i);
		}
	}
	delete bitmap;
	return primes;
}

bool is_prime(long long num, vector<int> primes){
	long long r = sqrt(num);
	bool flag = false;
	for(int i = 0; primes[i] < r; ++i){
		if(num % primes[i] == 0){
			flag = true;
			break;
		}
	}
	return flag;
}

// from x radix to y radix
long long radixX2Y(long long num, int from, int to, long long module = 0x7FFFFFFFFFFFFFFF){
	long long v = 0;
	while(num > 0){
		v = (v * to + num % from) % module;
		num /= from;
	}
	return v;
}