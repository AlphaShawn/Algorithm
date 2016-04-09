# Algorithm & DataStucture

## Introduction

This repository contains implemtation of some algorithm and data structure.

Most of the code is written in C++ class style. And try to create functional and complete modules which can be used in future coding easily.

## Implemented
* String
	* KMP
* Number theory
	* Miller_Rabin
* heap, heap_template, support customize compare function and data.
* leftist Tree, basic heap opertion, quick merge, use it solve OJ problem(HDU-1512)
* Union set, path compression and weighted tree
* Quick-sort, randomized pivot, two ways of partition
* quick_power, data type:integer, using muliply mod avoid overflow
* DP
	* LCS， space compresion
* graph
	* SPFA
	* Dijkstra, normal version, heap version
	* Minimum spanning tree
		* Kruskal
		* Prim

## TODO
* skip list
* Matrix data structure, support +, -, *, power
* graph
	* SPFA  - test
	* Dijkstra - test ZOJ1298  P137
	* Minimum spanning tree   ZOJ 1542  P102
		* Prim  test
	* Floyd
	* Tarjan
* network flow
* DP
	* LCS， reconstruct seq

# OnlineJudge Catalog

## String
OJ-Problem ID | Dir | Description
--------------|-----|------------
[Lintcode-158](http://www.lintcode.com/zh-cn/problem/two-strings-are-anagrams/)|  | sort string
[Lintcode-55](http://www.lintcode.com/zh-cn/problem/compare-strings/)|  | sort string
[Lintcode-13](http://www.lintcode.com/zh-cn/problem/strstr/)| /string/KMP.cpp | using kmp do string matching
[Lintcode-171](http://www.lintcode.com/zh-cn/problem/anagrams/) | | sorting and hashing


## DP

## Graph
OJ-Problem ID | Dir | Description
--------------|-----|------------
[poj-1861](http://poj.org/problem?id=1861)| graph/kruskal_poj1861 | kruskal

## Math

OJ-Problem ID | Dir | Description
--------------|-----|------------
[hihocoder](http://hihocoder.com/contest/hiho92/problem/1)| number_theory/Miller_Rabin.cpp | Miller–Rabin_primality_test - [WIKI](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)

## Data structure

OJ-Problem ID | Dir | Description
--------------|-----|------------
[HDU-1512](http://acm.hdu.edu.cn/showproblem.php?pid=1512)| /leftist_tree/OJ-hdu1512.cpp| leftist tree + union set
[hihocoder-1078](http://hihocoder.com/problemset/problem/1078) | | segment tree + lazy update