#include "max_value.h"
#include <algorithm>

using namespace std;

double calculateMaxValue(double* a, int n) {
    double mn = a[0], mx = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > 0) {
            mx = max({ mx + a[i], mx * a[i], mx / a[i] });
            mn = min({ mn - a[i], mn * a[i], mn / a[i] });
        }
        else if (a[i] < 0) {
            double maxtmp = mx;
            mx = max({ mx - a[i], mn * a[i], mn / a[i] });
            mn = min({ mn + a[i], maxtmp * a[i], maxtmp / a[i] });
        }
        else {
            mn = min(0., mn);
            mx = max(0., mx);
        }
    }
    return mx;
}