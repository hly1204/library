---
title: ST-Trees
documentation_of: ../st_tree_node_base.hpp
---

## ST-Trees

The code of my ST-Trees is a modified version of the original ST-Trees.

ST-Trees is vertex based.

The trick of using CRTP is learned from someone's beautiful Top Tree implementation, but I no longer remember who I have learned from.

**WARNINGS**: The order is somehow **reversed**, I store the root of the path as the left most node of the auxiliary tree. In Tarjan and Werneck's paper it should be stored as the right most node.

## APIs

- `x->update()`: Once node `x`'s information is set, `x->update()` should be called.
- `x->expose()`: After calling `x->expose()`, `x` become the root of the auxiliary tree (or shadow tree in Tarjan and Werneck's paper). So we could use the information of `x`, it will represent the information from `x->root()` to `x`. But calling `x->root()` will change the structure of the tree, so we must access the information of `x` right after `x->expose()`. If we want to get `x->root()`, it should be called before `x->expose()`.
- `x->evert()`: Make `x` the root of the tree. If we want the information of the path from `x` to `y`, we could use `x->evert(), y->expose()` and then access the information of `y`.
- `x->root()`: Get the root of `x` of the tree.
- `x->parent()`: Helper function to get the parent of `x`.
- `x->link(y)`: Link `x` and `y`. This will make `y` become the parent of `x`.
- `x->cut()`: Cut the edge between `x` and `x->parent()`.
- `x->cut(y)`: Cut the edge between `x` and `y`. Either `x` is the parent of `y` or `y` is the parent of `x`.
- `x->select(k)`: Call `x->expose()` before using `x->select(k)`. `x->select(0)` equals `x->root()`.
- `x->jump(k)`: Call `x->expose()` before using `x->jump(k)`. `x->jump(0)` equals `x`, `x->jump(1)` equals `x->parent()`.
