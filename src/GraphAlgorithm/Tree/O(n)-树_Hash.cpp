// Luogu P5043
/*
 * 定义 f[u] 为以 u 为树根时的 hash 值，规定叶节点的 hash 值为 1
 * 有两种 hash 方式（seed 均为质数）：
 * 1. f[u] = size[u] * sum{size[v]} * seed ^ (rank - 1)
 *    其中 rank 为 v 在 u 的所有儿子中以 f 为关键字排序后的排名，可适当取模
 * 2. f[u] ^= f[v] * seed + size[v]
 * 我们可以通过找重心的方式来优化复杂度，一棵树的重心最多只有两个，分别比较即可
 */
