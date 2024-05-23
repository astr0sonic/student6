#include "volume.h"
#include <algorithm>

using namespace std;

int getMaxVolume(int a, int b, int c, int n, int* t) {
	int i = 0, j = n - 1, m = 0;
	for (j = 0; j + a < n; j++) {
		int k = min(t[j], t[j + a]);
		if (k > m && k <= c) {
			i = j;
			m = k;
		}
	}
	j = i + a;
	if (j >= n)
		j = n - 1;
	while (i < j) {
		int k = (j - i) * min(t[i], t[j]);
		if (k > m && min(t[i], t[j]) <= c)
			m = k;
		if (t[i] == min(t[i], t[j]))
			i++;
		else
			j--;
	}
	return b * m;
}
