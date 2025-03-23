# Graph Explorer (C++)

A command-line C++ program for building, visualizing, and traversing directed graphs using adjacency lists. Supports dynamic edge addition/removal and includes implementations of depth-first search (DFS) and breadth-first search (BFS).

## Overview

This project demonstrates core graph algorithms using fundamental data structures implemented from scratch:
- Adjacency List via custom `LinkedList`
- Stack (`DynamicIntStack`) for DFS
- Queue for BFS

The program reads edges from an input file, validates them, builds the graph, and allows user interaction through a console menu.

## Features

- Parse and validate graph edges from a file
- Prevent duplicate or invalid edges
- Build graph using adjacency lists
- Display the full graph structure
- Add or remove edges interactively
- Perform DFS and BFS from a user-defined start node

## Input Format

The input file should contain one edge per line in the format:

<from_node> <to_node>
- Only non-negative integers are valid
- Invalid or duplicate edges will be reported but not processed

Example:
0 1 1 2 2 0
