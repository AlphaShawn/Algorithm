# Algorithm & DataStucture

## Introduction

This repository contains implemtation of some algorithm and data structure.

Most of the code is written in C++ class style. And try to create functional and complete modules which can be used in future coding easily.

## Implemented
* String
	* KMP
* Number theory
	* Miller_Rabin
	* Eular_Prime_Select
	* Josephus Problem
	* Euclid's Algorithm  greatest common divisor(gcd)
	* Extended Euclid's Algorithm (Ax + By = gcd(A, B))
	* Euler's totient function
	* Modular Linear System
* heap, heap_template, support customize compare function and data.
* Trie tree
* leftist Tree, basic heap opertion, quick merge, use it solve OJ problem(HDU-1512)
* Union set, path compression and weighted tree
* Quick-sort, randomized pivot, two ways of partition
* quick_power, data type:integer, using muliply mod avoid overflow
* DP
	* LCS， space compresion(version 1), reconstruct seq(version 2)
* graph
	* Shortest Path(single source)
		* SPFA
		* Dijkstra, normal version, heap version
	* Minimum spanning tree
		* Kruskal
		* Prim
	* Floyd
	* Tarjan
* network flow
	* Ford-Fulkerson
	* MPLA (sap-shortest augmenting path)
	* Dinic (Successive shortest augmenting path algo)

## TODO
* skip list 
* big number 
* Aho-Corasick automaton (AC automaton)
* Matrix data structure, support +, -, *, power
* Fibonacci heap
* Johnson's algorithm
* graph
	* Minimum spanning tree
		* Prim  using heap or more advanced data structure
	* Tarjan test  poj2762  p421
* network flow
	

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
[poj-1861](http://poj.org/problem?id=1861)| graph/kruskal_poj1861 | kruskal or prim
[poj-1135](http://poj.org/problem?id=1135)| graph/poj-1135.cpp | dijkstra or SPFA
[poj-3616](http://poj.org/problem?id=3615)| graph/poh-3615 | Floyd
[poj-3268](http://poj.org/problem?id=3268)| graph/poh-3268 | SPFA

## Math

OJ-Problem ID | Dir | Description
--------------|-----|------------
[hihocoder](http://hihocoder.com/contest/hiho92/problem/1)| number_theory/Miller_Rabin.cpp | Miller–Rabin_primality_test - [WIKI](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
[hihocoder](http://hihocoder.com/contest/hiho93/problem/1) | number_theory/Rular_prime_select.cpp | Eular prime select
[hihocoder](http://hihocoder.com/contest/hiho94/problem/1?sid=773738) | number_theory/Josephus.cpp | mod and recurrence
[hihocoder](http://hihocoder.com/contest/hiho95/problem/1) | | Extended Euclid's Algorithm 
[hihocoder](http://hihocoder.com/contest/hiho96/problem/1) | /number_theory/Euler's_totient_function.cpp| Euler's totient function
[hihocoder](http://hihocoder.com/contest/hiho97/problem/1) | /number_theory/modular_linear_system.cpp | 线性同余方程组

## Data structure

OJ-Problem ID | Dir | Description
--------------|-----|------------
[HDU-1512](http://acm.hdu.edu.cn/showproblem.php?pid=1512)| /leftist_tree/OJ-hdu1512.cpp| leftist tree + union set
[hihocoder-1078](http://hihocoder.com/problemset/problem/1078) | | segment tree + lazy update
[hihocoder-1014](http://hihocoder.com/problemset/problem/1014) | /TrieTree/trie.cpp | simple trie tree

## Network flow
OJ-Problem ID | Dir | Description
--------------|-----|------------
[POJ-3281](http://poj.org/problem?id=3281)|/network_flow/ford_fulkerson.cpp| split node

##Secching
OJ-Problem ID | Dir | Description
--------------|-----|------------
[hihocoder](http://hihocoder.com/contest/hiho98/problem/1) | | 24点