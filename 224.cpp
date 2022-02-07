/*************************************************************************
	> File Name: 224.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Sun 06 Feb 2022 11:45:41 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define maxn 100000

struct node {
    int l, r;
    long long sum, add, mul;
}tree[maxn * 4];

int n, m;
int arr[maxn + 5];
int mod;

void eval(int p, int add, int mul) {
    int len = tree[p].r - tree[p].l + 1;
    tree[p].sum = (tree[p].sum * mul + len * add) % mod;
    tree[p].mul = tree[p].mul * mul % mod;
    tree[p].add = (tree[p].add * mul + add) % mod;
    return;
}

void spread(int p) {
    eval(p << 1, tree[p].add, tree[p].mul);
    eval(p << 1 | 1, tree[p].add, tree[p].mul);
    tree[p].mul = 1;
    tree[p].add = 0;
    return;
}
void build(int p, int l, int r) {
    tree[p] = {l, r, 0, 0, 1};
    if (l == r) {
        tree[p].sum = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    tree[p].sum = (tree[p << 1].sum + tree[p << 1 | 1].sum) % mod;
    return;
}
void change(int p, int l, int r, int add, int mul) {
    if (tree[p].l >= l && tree[p].r <= r) {
        eval(p, add, mul);
        return;
    }
    spread(p);
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (l <= mid) change(p << 1, l, r, add, mul);
    if (mid + 1 <= r) change(p << 1 | 1, l, r, add, mul);
    tree[p].sum = (tree[p << 1].sum % mod + tree[p << 1 | 1].sum % mod) % mod;
    return;
}

int query(int p, int l, int r) {
    if (tree[p].l >= l && tree[p].r <= r) {
        return tree[p].sum;
    }
    spread(p);
    int sum = 0;
    int mid = (tree[p].l + tree[p].r) >> 1;
    if (l <= mid) sum = (sum + query(p << 1, l ,r)) % mod;
    if (mid + 1 <= r) sum = (sum + query(p << 1 | 1, l ,r)) % mod;
    return sum;
}



int main() {
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (m--) {
        int op, x, y, k;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> k;
            change(1, x, y, 0, k);
        } else if (op == 2) {
            cin >> x >> y >> k;
            change(1, x, y, k, 1);
        } else {
            cin >> x >> y;
            cout << query(1, x, y) << endl;
        }
    }
    return 0;
}
