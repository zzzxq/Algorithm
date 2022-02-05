# Algorithm
线段树
使用场景1、对于一段区间的修改，对于一段区间的求和(树状数组也可)
结构
struct node {
  int l, r;
  int val, lazy;
}tree[maxn * 4];

如何通过数组 建树 build(int ind, int l, int r);
如何修改一段区间的值 change(int ind, int l, int r, int z)
如何通过lazy修改孩子的值  spread(int ind)
如何求一段区间的和  get_sum(int ind, int l, int r)


使用场景2、修改某个值，求某段区间的最值
struct node {
  int l, r;
  int maxn;
}tree[maxn * 4];

build(int ind, int l, int r);
change(int ind, int pos, int c);
get_max(int ind, int l, int r);


数组数组 FenwickTree

首先,树状数组是为了解决前缀和中，修改区间某个值后，前缀和需要全部修改的问题，将时间复杂度从O(n)->O(logn)

线段树 > 树状数组
1.外观上树状数组比较简洁，常数复杂度低，空间复杂度低。

2.可以用树状数组解决的问题，线段树均可解决，但可以用线段树解决的，树状数组不一定可以解决。

3.常见的三种查询方法实现方式（给a加b，查询a到b的区间）

树状数组的核心思想:
1、lowbit(x) = (x & (-x))
lowbit(i)的本质是求i的二进制下最后一个1的位置，例如lowbit(1) = 1, lowbit(2) = 10 lowbit(3) = 1, lowbit(4) = 100

C1 = A1
C2 = A1+A2
C3 = A3
C4 = A1+A2+A3+A4
C5 = A5
C6 = A5+A6
C7 = A7



例如要求前7位的和
S[7] = S[6] + C[7]
     = S[4] + C[6] + C[7]
     = C[4] + C[6] + C[7]
理解本质
7 = (111)2, 7 - lowbit(7) 等于 110   6 - lowbit(6) = 100,  4 - lowbit(4) = 0

修改的本质
i + lowbit(i) 一定包含i
因此修改了 C[i], 一定要接着修改 C[i + lowbit(i)]

知识点：如何使用差分数组实现区间修改？
维护另一个树状数组
a[n] = n * sigmod(n, C) - sigmod(n, (i - 1) * C);
维护一个C，一个 (i - 1) * C

当然用线段树也通用











