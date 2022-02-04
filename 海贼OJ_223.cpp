/*************************************************************************
	> File Name: segmentTree.cpp
	> Author: zxq
	> Mail: 1459190705@qq.com
	> Created Time: Fri 04 Feb 2022 07:38:55 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define maxn 10005

struct node {
    int l, r;
    long long val, lazy;
}edge[maxn * 4];

int arr[maxn], n, m;


void build(int ind, int l, int r) { //从下标1开始建树
    edge[ind].l = l, edge[ind].r = r;
    if (l == r) {
        edge[ind].val = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    edge[ind].val = edge[ind << 1].val + edge[ind << 1 | 1].val;
    return;
}
void spread(int ind) {
    if (edge[ind].lazy) {
        edge[ind << 1].lazy += edge[ind].lazy;
        edge[ind << 1].val += edge[ind].lazy * (edge[ind << 1].r - edge[ind << 1].l + 1);
        edge[ind << 1 | 1].lazy += edge[ind].lazy;
        edge[ind << 1 | 1].val += edge[ind].lazy * (edge[ind << 1 | 1].r - edge[ind << 1 | 1].l + 1);
        edge[ind].lazy = 0;
    }
}
//更新区间值的代码
void change(int ind, int l, int r, long long z) {
    if (edge[ind].l >= l && edge[ind].r <= r) { //当前区间包含了修改区间
        edge[ind].lazy += z; 
        edge[ind].val += z*(edge[ind].r - edge[ind].l + 1 );
        return;
    }
    spread(ind); //下沉lazy值
    int mid = (edge[ind].l + edge[ind].r) >> 1;
    if (l <= mid) change(ind << 1, l, r, z);
    if (mid + 1 <= r) change(ind << 1 | 1, l, r, z);  //这里一定是l,r，不然出错
    edge[ind].val = edge[ind << 1].val + edge[ind << 1 | 1].val;
    return;
}


//求区间和
long long get_sum(int ind, int l, int r) {
    long long ans = 0;
    if (edge[ind].l >= l && edge[ind].r <= r) {
        ans += edge[ind].val;
        return ans;
    }
    spread(ind);
    int mid = (edge[ind].l + edge[ind].r) >> 1;
    if (l <= mid) ans += get_sum(ind << 1, l, r);
    if (mid + 1 <= r) ans += get_sum(ind << 1 | 1, l, r);
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        scanf("%d", &a);
        if (a == 1) {
            scanf("%d%d%d", &b, &c, &d);
            if (b > c) continue;
            change(1, b, c, d);
        } else {
            scanf("%d%d", &b, &c);
            if (b > c) {
                printf("0\n");
                continue;
            }
            printf("%lld\n", get_sum(1, b, c));
        }
    }
    return 0;
}




