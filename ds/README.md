# 数据结构手写实现（30 个）

每个文件独立可编译：

```bash
g++ -std=c++17 01_dynamic_array.cpp -o 01 && ./01
```

> 原则：**先手写，再看答案**。写完在下面表格打勾，并记一次踩过的坑。

## 进度表

| # | 状态 | 类别 | 结构 / 算法 | 文件 | 易错点 |
|---|---|---|---|---|---|
| 01 | ☐ | 线性 | 动态数组 | `01_dynamic_array.cpp` | |
| 02 | ☐ | 线性 | 单链表 | `02_singly_linked_list.cpp` | |
| 03 | ☐ | 线性 | 双链表 | `03_doubly_linked_list.cpp` | |
| 04 | ☐ | 线性 | 循环链表 | `04_circular_linked_list.cpp` | |
| 05 | ☐ | 栈 | 顺序栈 | `05_array_stack.cpp` | |
| 06 | ☐ | 栈 | 链栈 | `06_linked_stack.cpp` | |
| 07 | ☐ | 栈 | 括号匹配 | `07_bracket_match.cpp` | |
| 08 | ☐ | 队列 | 循环队列 | `08_circular_queue.cpp` | |
| 09 | ☐ | 队列 | 链队列 | `09_linked_queue.cpp` | |
| 10 | ☐ | 队列 | BFS 队列模板 | `10_bfs_template.cpp` | |
| 11 | ☐ | 串 | 字符串哈希 | `11_string_hash.cpp` | |
| 12 | ☐ | 串 | KMP | `12_kmp.cpp` | |
| 13 | ☐ | 树 | 递归三序遍历 | `13_tree_recursive.cpp` | |
| 14 | ☐ | 树 | 非递归中序遍历 | `14_tree_inorder_stack.cpp` | |
| 15 | ☐ | 树 | 层序遍历 | `15_tree_level_order.cpp` | |
| 16 | ☐ | 树 | 由遍历重建树 | `16_tree_rebuild.cpp` | |
| 17 | ☐ | 树 | BST 插入/查找/删除 | `17_bst.cpp` | |
| 18 | ☐ | 树 | 二分查找 4 种写法 | `18_binary_search.cpp` | |
| 19 | ☐ | 树 | 堆 / 优先队列 | `19_heap.cpp` | |
| 20 | ☐ | 树 | 树状数组 | `20_fenwick.cpp` | |
| 21 | ☐ | 树 | 线段树（区间加+求和） | `21_segment_tree.cpp` | |
| 22 | ☐ | 图 | 邻接矩阵存图 | `22_adj_matrix.cpp` | |
| 23 | ☐ | 图 | 邻接表存图 | `23_adj_list.cpp` | |
| 24 | ☐ | 图 | 图 DFS 遍历 | `24_graph_dfs.cpp` | |
| 25 | ☐ | 图 | 图 BFS 遍历 | `25_graph_bfs.cpp` | |
| 26 | ☐ | 图 | 拓扑排序 | `26_topo_sort.cpp` | |
| 27 | ☐ | 图 | 并查集 | `27_dsu.cpp` | |
| 28 | ☐ | 图 | Dijkstra 堆优化 | `28_dijkstra.cpp` | |
| 29 | ☐ | 图 | Floyd 最短路 | `29_floyd.cpp` | |
| 30 | ☐ | 图 | Kruskal 最小生成树 | `30_kruskal.cpp` | |

## 完成统计

| 类别 | 数量 | 完成 |
|---|---|---|
| 线性 | 4 | /4 |
| 栈 | 3 | /3 |
| 队列 | 3 | /3 |
| 串 | 2 | /2 |
| 树 | 9 | /9 |
| 图 | 8 | /8 |
| **合计** | **30** | **/30** |

## 约定

- 每个文件包含：结构定义 + 核心操作 + 一个 `main()` 自测
- 不自测不算完成（"能跑" ≠ "正确"）
- 每个文件顶部注释记录：日期、用时、卡住的地方
