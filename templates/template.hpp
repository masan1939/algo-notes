// ============================================================
// 算法模板库 template.hpp
// 用法：比赛时把这些函数粘进自己的代码里，按需删减
// 编译：g++ -std=c++17 -O2 -Wall
// ============================================================
#pragma once
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 0. 竞赛常用 IO 加速（main 第一行调用）
// ============================================================
inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// ============================================================
// 1. 二分：4 种写法（★ 最常错，闭卷能写才算会）
// ============================================================
// L1. 找最后一个满足 check(x) 为 true 的位置（check 单调：前真后假）
template <class F>
int lastTrue(int lo, int hi, F check) {
    if (!check(lo)) return lo - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;   // 上取整，避免死循环
        if (check(mid)) lo = mid; else hi = mid - 1;
    }
    return lo;
}

// L2. 找第一个满足 check(x) 为 true 的位置（check 单调：前假后真）
template <class F>
int firstTrue(int lo, int hi, F check) {
    if (!check(hi)) return hi + 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;       // 下取整
        if (check(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// L3. 浮点二分（求 f(x) 的零点 / 极值，err 为精度）
template <class F>
double binarySearchReal(double lo, double hi, F check, double err = 1e-7) {
    for (int it = 0; it < 100; ++it) {      // 固定迭代次数更稳
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid; else lo = mid;
    }
    return (lo + hi) / 2;
}

// L4. 答案二分：最低可行答案（最小化最大值 / 最大化最小值）
//    例如：求最小的船载重，使得 maxDays 天内运完
template <class F>
long long binaryAnswer(long long lo, long long hi, F ok) {
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}

// 数组版：lower_bound / upper_bound（C++ 自带，优先用）
// lower_bound(v.begin(), v.end(), x)  第一个 >= x
// upper_bound(v.begin(), v.end(), x)  第一个 >  x
// 手写版（无自带容器时用）
int lowerBoundVec(const vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size();          // [0, n)
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

// ============================================================
// 2. 前缀和与差分
// ============================================================
// 一维前缀和，下标从 1 开始，pre[0] = 0
vector<long long> prefix1d(const vector<long long>& a) {
    int n = (int)a.size() - 1;
    vector<long long> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];
    return pre;
}
// 区间和 [l, r]：pre[r] - pre[l - 1]

// 二维前缀和，下标从 1 开始
vector<vector<long long>> prefix2d(const vector<vector<long long>>& a) {
    int n = (int)a.size() - 1, m = n ? (int)a[0].size() - 1 : 0;
    vector<vector<long long>> pre(n + 1, vector<long long>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    return pre;
}
// 矩形和 (x1,y1)-(x2,y2)：pre[x2][y2]-pre[x1-1][y2]-pre[x2][y1-1]+pre[x1-1][y1-1]

// 差分：区间加 c，最后还原；下标从 1 开始
vector<long long> diff1d(const vector<long long>& a) {  // 返回差分数组
    int n = (int)a.size() - 1;
    vector<long long> d(n + 2, 0);
    for (int i = 1; i <= n; ++i) d[i] = a[i] - a[i - 1];
    return d;
}
void rangeAdd(vector<long long>& d, int l, int r, long long c) {
    d[l] += c; d[r + 1] -= c;
}

// ============================================================
// 3. 排序与去重
// ============================================================
template <class T>
void sortUnique(vector<T>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}
// 坐标离散化：把值映射到 1..k
template <class T>
vector<int> compress(const vector<T>& v) {
    vector<T> u(v);
    sortUnique(u);
    vector<int> r(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        r[i] = int(lower_bound(u.begin(), u.end(), v[i]) - u.begin()) + 1;
    return r;
}

// ============================================================
// 4. 最大公约数 / 快速幂 / 质数筛
// ============================================================
long long gcdll(long long a, long long b) { return b ? gcdll(b, a % b) : a; }
long long lcmll(long long a, long long b) { return a / gcdll(a, b) * b; }

long long qpow(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

// 线性筛：返回 1..n 中所有质数
vector<int> linearSieve(int n) {
    vector<int> primes;
    vector<bool> isComposite(n + 1, false);
    for (int i = 2; i <= n; ++i) {
        if (!isComposite[i]) primes.push_back(i);
        for (int p : primes) {
            if ((long long)i * p > n) break;
            isComposite[i * p] = true;
            if (i % p == 0) break;
        }
    }
    return primes;
}

// 欧拉函数（单个数）
long long phi(long long n) {
    long long r = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            r = r / p * (p - 1);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) r = r / n * (n - 1);
    return r;
}

// 扩展 gcd：ax + by = gcd(a,b)
long long exgcd(long long a, long long b, long long& x, long long& y) {
    if (!b) { x = 1; y = 0; return a; }
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// ============================================================
// 5. 并查集
// ============================================================
struct DSU {
    vector<int> p, sz;
    explicit DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }   // 路径压缩
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);                                // 按大小合并
        p[b] = a; sz[a] += sz[b];
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};

// ============================================================
// 6. 树状数组（单点改、区间查 / 区间改、单点查）
// ============================================================
struct Fenwick {
    int n;
    vector<long long> t;
    explicit Fenwick(int n = 0) : n(n), t(n + 1, 0) {}
    void add(int i, long long v) { for (; i <= n; i += i & -i) t[i] += v; }
    long long sum(int i) const { long long s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
    long long rangeSum(int l, int r) const { return sum(r) - sum(l - 1); }
};
// 区间加 + 单点查：用差分数组建两个树状数组（套路见 P3374 / P3368）

// ============================================================
// 7. 线段树（区间加 + 区间求和，懒标记）
// ============================================================
struct SegTree {
    int n;
    vector<long long> sum, lazy;
    explicit SegTree(int n = 0) : n(n), sum(4 * n + 4, 0), lazy(4 * n + 4, 0) {}
    void build(const vector<long long>& a, int o, int l, int r) {
        if (l == r) { sum[o] = a[l]; return; }
        int m = (l + r) / 2;
        build(a, o * 2, l, m); build(a, o * 2 + 1, m + 1, r);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
    void push(int o, int l, int r) {
        if (!lazy[o]) return;
        int m = (l + r) / 2;
        sum[o * 2] += lazy[o] * (m - l + 1);
        sum[o * 2 + 1] += lazy[o] * (r - m);
        lazy[o * 2] += lazy[o];
        lazy[o * 2 + 1] += lazy[o];
        lazy[o] = 0;
    }
    void add(int o, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) { sum[o] += v * (r - l + 1); lazy[o] += v; return; }
        push(o, l, r);
        int m = (l + r) / 2;
        if (ql <= m) add(o * 2, l, m, ql, qr, v);
        if (qr > m) add(o * 2 + 1, m + 1, r, ql, qr, v);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
    long long query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return sum[o];
        push(o, l, r);
        int m = (l + r) / 2;
        long long s = 0;
        if (ql <= m) s += query(o * 2, l, m, ql, qr);
        if (qr > m) s += query(o * 2 + 1, m + 1, r, ql, qr);
        return s;
    }
};

// ============================================================
// 8. 图：存图与最短路
// ============================================================
struct Edge { int to; long long w; };
using Graph = vector<vector<Edge>>;

// 邻接表加边（无向图调用两次）
inline void addEdge(Graph& g, int u, int v, long long w = 1) {
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}

// Dijkstra（堆优化）
vector<long long> dijkstra(const Graph& g, int s) {
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(g.size(), INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (dist != d[u]) continue;                 // 过期节点
        for (auto& e : g[u]) {
            if (d[u] + e.w < d[e.to]) {
                d[e.to] = d[u] + e.w;
                pq.push({d[e.to], e.to});
            }
        }
    }
    return d;
}

// Floyd
const long long INFLL = LLONG_MAX / 4;
void floyd(vector<vector<long long>>& d) {
    int n = (int)d.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) {
            if (d[i][k] == INFLL) continue;
            for (int j = 0; j < n; ++j)
                if (d[k][j] != INFLL) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
}

// 拓扑排序（Kahn），返回拓扑序；有环返回空
vector<int> topoSort(const Graph& g) {
    int n = (int)g.size();
    vector<int> deg(n, 0);
    for (int u = 0; u < n; ++u)
        for (auto& e : g[u]) ++deg[e.to];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (!deg[i]) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (auto& e : g[u]) if (--deg[e.to] == 0) q.push(e.to);
    }
    return (int)order.size() == n ? order : vector<int>{};
}

// Kruskal
struct DSUEdge { int u, v; long long w; };
long long kruskal(int n, vector<DSUEdge> edges) {   // 返回最小生成树总权值
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a.w < b.w; });
    DSU dsu(n);
    long long total = 0;
    int cnt = 0;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) { total += e.w; if (++cnt == n - 1) break; }
    }
    return cnt == n - 1 ? total : -1;               // -1 表示不连通
}

// ============================================================
// 9. 搜索：DFS / BFS
// ============================================================
// 网格 BFS 最短路（1 表示可走）
int bfsGrid(vector<vector<int>>& g, pair<int, int> s, pair<int, int> t) {
    int n = (int)g.size(), m = n ? (int)g[0].size() : 0;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    dist[s.first][s.second] = 0;
    q.push(s);
    const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == t.first && y == t.second) return dist[x][y];
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (g[nx][ny] != 1 || dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    return -1;
}

// 全排列 / 组合（递归）
void dfsPermutation(int n, vector<int>& path, vector<bool>& used) {
    if ((int)path.size() == n) {
        // 处理 path
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (used[i]) continue;
        used[i] = true; path.push_back(i);
        dfsPermutation(n, path, used);
        path.pop_back(); used[i] = false;
    }
}

// ============================================================
// 10. 动态规划
// ============================================================
// 0/1 背包
long long knapsack01(const vector<int>& w, const vector<long long>& v, int W) {
    vector<long long> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); ++i)
        for (int j = W; j >= w[i]; --j)          // ★ 倒序！否则变成完全背包
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}

// 完全背包
long long knapsackComplete(const vector<int>& w, const vector<long long>& v, int W) {
    vector<long long> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); ++i)
        for (int j = w[i]; j <= W; ++j)          // ★ 正序
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}

// 最长上升子序列 LIS（O(n log n)）
int lis(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);   // 严格上升
        if (it == tails.end()) tails.push_back(x); else *it = x;
    }
    return (int)tails.size();
}

// 最长公共子序列 LCS
int lcs(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = (a[i - 1] == b[j - 1]) ? dp[i - 1][j - 1] + 1
                                              : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}

// 最大子段和
long long maxSubarray(const vector<long long>& a) {
    long long best = a.empty() ? 0 : a[0], cur = best;
    for (size_t i = 1; i < a.size(); ++i) {
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

// ============================================================
// 11. 字符串
// ============================================================
// KMP：next 数组（next[i] = 前缀 s[0..i] 的最长相等前后缀长度）
vector<int> kmpNext(const string& s) {
    int n = (int)s.size();
    vector<int> nxt(n, 0);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) ++j;
        nxt[i] = j;
    }
    return nxt;
}
// KMP 匹配：返回 s 中 pattern 所有出现的起点
vector<int> kmpMatch(const string& s, const string& p) {
    vector<int> nxt = kmpNext(p), res;
    for (int i = 0, j = 0; i < (int)s.size(); ++i) {
        while (j && s[i] != p[j]) j = nxt[j - 1];
        if (s[i] == p[j]) ++j;
        if (j == (int)p.size()) { res.push_back(i - j + 1); j = nxt[j - 1]; }
    }
    return res;
}

// 字符串哈希（双模数）
struct StrHash {
    static const int M1 = 1000000007, M2 = 1000000009, B = 131;
    vector<int> h1, h2;
    explicit StrHash(const string& s) : h1(s.size() + 1, 0), h2(s.size() + 1, 0) {
        for (size_t i = 0; i < s.size(); ++i) {
            h1[i + 1] = ((long long)h1[i] * B + s[i]) % M1;
            h2[i + 1] = ((long long)h2[i] * B + s[i]) % M2;
        }
    }
    // [l, r] 的哈希（0-based，返回 pair）
    pair<int, int> get(int l, int r) const {
        static vector<long long> p1, p2;
        if (p1.empty()) {
            int n = (int)h1.size();
            p1.assign(n, 1); p2.assign(n, 1);
            for (int i = 1; i < n; ++i) {
                p1[i] = p1[i - 1] * B % M1;
                p2[i] = p2[i - 1] * B % M2;
            }
        }
        int len = r - l + 1;
        int a = (h1[r + 1] - (long long)h1[l] * p1[len]) % M1; if (a < 0) a += M1;
        int b = (h2[r + 1] - (long long)h2[l] * p2[len]) % M2; if (b < 0) b += M2;
        return {a, b};
    }
};

// ============================================================
// 12. 位运算与常用技巧
// ============================================================
// lowbit：最低位的 1
inline int lowbit(int x) { return x & -x; }
// 统计 1 的个数
inline int popcount64(unsigned long long x) { return __builtin_popcountll(x); }
// 枚举子集：for (int s = mask; s; s = (s - 1) & mask)
// 高精度比较 / 组合数：见 C++17 的 std::gcd 与组合数模板（P3792）

// 组合数（预处理阶乘，模 mod）
struct Comb {
    vector<long long> fac, ifac;
    long long mod;
    explicit Comb(int n, long long m) : fac(n + 1), ifac(n + 1), mod(m) {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = modPow(fac[n], mod - 2);
        for (int i = n; i > 0; --i) ifac[i - 1] = ifac[i] * i % mod;
    }
    long long modPow(long long a, long long e) const {
        long long r = 1;
        a %= mod;
        while (e) { if (e & 1) r = r * a % mod; a = a * a % mod; e >>= 1; }
        return r;
    }
    long long C(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
    }
};

// ============================================================
// 13. 常用常量
// ============================================================
const long long INF = 0x3f3f3f3f3f3f3f3fLL;   // 1.06e18
const int INFi = 0x3f3f3f3f;                    // 1.06e9
// 蓝桥杯常见注意：结果可能超 int，用 long long；
// 多组输入记得清空容器；输出末尾不带空格。
