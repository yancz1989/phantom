# phantom
A library for learning, computing and connecting.

# Motivation

This library is written for a complete union of advanced algorithms which can't be found in standard library like BOOST. It uses C++ and python and will interact with BLAS and LAPACK. In the future, CUDA based parallel will merge into parallel module.

# What's In It?

 It mainly contains:

1. most data structure and algorithms used in time or memory critical applications. STL is used as you can always find it with modern compiler. In case of special need, similar structure will be implemented with needs;
	a) util module: most algorithms which can be described as supportive like bit operations, hash algorithms, binary search, and others;
	b) tree module: tree data structures including **Treap, Size Balanced Tree, SPlay Tree, Trie Tree (with failed pointer), Dance Links, Fibonacci Heap, Segment Tree, Interval Tree**;
	c) math module:
		1) computing geometry: algorithms like convex hulls, Voronoi Diagrams, and others;
		2) combinatorial: combinatorial mathematics routines;
		3) number theory: gcd, Chinese remainder problem, etc.
	d) string module: Implemented string algorithm like suffix tree.
2. design pattern demo, implementation of design patterns in "Gang of Four", with interfaces defined and usable for future use;
3. system module is implemented for support on distributed computing which contains basic common interfaces for both Windows and POSIX APIs;
4. network module provides encapsulations and interfaces for network connection and analysis.
5. sparse optimization: python packages for sparse/convex optimization with Interial Point Mehtod, ISTA, FISTA, etc.
 