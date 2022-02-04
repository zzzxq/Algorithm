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
