#include <bits/stdc++.h>
#include "template.hpp"

int main() {
    std::vector<int> a{1, 3, 5, 7};
    std::cout << lowerBoundVec(a, 4) << "\n";           // 2
    std::cout << lastTrue(1, 10, [](int x){ return x <= 7; }) << "\n";  // 7
    std::cout << firstTrue(1, 10, [](int x){ return x >= 4; }) << "\n"; // 4
    std::cout << binaryAnswer(1, 100, [](long long x){ return x * x >= 50; }) << "\n"; // 8

    long long x, y;
    std::cout << exgcd(30, 18, x, y) << "\n";           // 6
    std::cout << qpow(2, 10, 1000) << "\n";             // 24
    std::cout << lis({3, 1, 4, 1, 5}) << "\n";           // 3
    std::cout << lcs("abcde", "ace") << "\n";            // 3
    std::cout << knapsack01({1,2,3}, {1,2,3}, 5) << "\n"; // 6
    std::cout << maxSubarray({-2, 1, -3, 4, -1, 2, 1, -5, 4}) << "\n"; // 6
    std::cout << kmpMatch("abcabc", "abc").size() << "\n"; // 2
    std::cout << lowbit(12) << "\n";                     // 4

    DSU d(5);
    std::cout << d.unite(1, 2) << d.unite(2, 3) << d.same(1, 3) << "\n"; // 111

    Fenwick f(5);
    for (int i = 1; i <= 5; ++i) f.add(i, i);
    std::cout << f.rangeSum(2, 4) << "\n";               // 9

    SegTree st(5);
    std::vector<long long> v(6, 0);
    for (int i = 1; i <= 5; ++i) v[i] = i;
    st.build(v, 1, 1, 5);
    st.add(1, 1, 5, 2, 3, 10);
    std::cout << st.query(1, 1, 5, 1, 5) << "\n";        // 15 + 20 = 35

    std::string s = "abcab";
    std::cout << (kmpNext(s)[4]) << "\n";                // 2
    StrHash h("abcab");
    std::cout << (h.get(0, 1) == h.get(3, 4)) << "\n";   // 1

    Comb c(10, 1000000007);
    std::cout << c.C(5, 2) << "\n";                      // 10
    std::cout << "ALL OK\n";
    return 0;
}
