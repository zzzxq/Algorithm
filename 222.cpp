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
    int maxx;
}edge[maxn * 4];

int arr[maxn], n, m;


void build(int ind, int l, int r) { //从下标1开始建树
    edge[ind].l = l, edge[ind].r = r;
    if (l == r) {
        edge[ind].maxx = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    edge[ind].maxx = max(edge[ind << 1].maxx, edge[ind << 1 | 1].maxx);
    return;
}
//更新区间值的代码
void change(int ind, int pos, int c) {
    if (edge[ind].l == edge[ind].r && edge[ind].l == pos) { //当前节点
        edge[ind].maxx = c; 
        return;
    }
    int mid = (edge[ind].l + edge[ind].r) >> 1;
    if (pos <= mid) change(ind << 1, pos, c);
    else if (mid + 1 <= pos) change(ind << 1 | 1, pos, c);
    edge[ind].maxx = max(edge[ind << 1].maxx, edge[ind << 1 | 1].maxx);
    return;
}


//求区间最值
int get_max(int ind, int l, int r) {
    int ans = -1;
    if (edge[ind].l >= l && edge[ind].r <= r) {
        return edge[ind].maxx;
    }
    int mid = (edge[ind].l + edge[ind].r) >> 1;
    if (l <= mid) ans = max(ans, get_max(ind << 1, l, r));
    if (mid + 1 <= r) ans = max(ans, get_max(ind << 1 | 1, l, r));
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
            scanf("%d%d", &b, &c);
            if (b > c) continue;
            change(1, b, c);
        } else {
            scanf("%d%d", &b, &c);
            if (b > c) {
                printf("-2147483648\n");
                continue;
            }
            printf("%d\n", get_max(1, b, c));
        }
    }
    return 0;
}




