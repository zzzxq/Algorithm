/*************************************************************************
	> File Name: FenwickTree.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Sat 05 Feb 2022 02:55:46 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

//解决单点修改，区间修改(差分数组)，区间查询

#define lowbit(x) (x & (-x))

class FenwickTree {
public:
    FenwickTree(int size) : n(size), arr(size + 1) {}
    void add(int i, int x) {
        while (i <= n) {
            arr[i] += x;
            i += lowbit(i);
        }
        return;
    }

    long long query(int i) {
        long long sum = 0;
        while (i > 0) {
            sum += arr[i];
            i -= lowbit(i);
        }
        return sum;
    }

    long long get_sum(int l, int r) {
        long long sum = 0;
        for (int i = l; i <= r; i++) sum += query(i);
        return sum;
    }
private:
    int n;
    vector<long long> arr;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> num(n + 1, 0);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    FenwickTree tree(n);
    for (int i = n; i >= 1; i--) {
        num[i] -= num[i - 1];
        tree.add(i, num[i]);
    }
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d", &a);
        if (a == 1) {
            scanf("%d%d%d", &b, &c, &d);
            if (b > c) continue;
            tree.add(b, d);
            tree.add(c + 1, -d);
        } else {
            scanf("%d%d", &b, &c);
            if (b > c) 
                printf("0\n");
            else
                printf("%lld\n", tree.get_sum(b, c));
        }
    }
    return 0;


}

