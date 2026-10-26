#ifndef TREE_H
#define TREE_H

#include "Resource.h"
#include <string>
#include <vector>
#include <iostream>

// ============================================================
// BST - stores Resources ordered by Resource ID (getID())
// Adapted to work with Student A's Resource class
// ============================================================

struct TreeNode {
    Resource data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Resource& r) : data(r), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, const Resource& r);
    TreeNode* searchRec(TreeNode* node, const std::string& id) const;
    TreeNode* removeRec(TreeNode* node, const std::string& id);
    TreeNode* findMin(TreeNode* node) const;

    void inorderRec(TreeNode* node) const;
    void preorderRec(TreeNode* node) const;
    void postorderRec(TreeNode* node) const;
    void destroyRec(TreeNode* node);

public:
    BST();
    ~BST();

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const Resource& r);
    bool search(const std::string& id) const;
    void remove(const std::string& id);

    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelOrder() const;

    bool isEmpty() const;
};

// ============================================================
// Category Tree - hierarchical organisation of facilities
// ============================================================

struct CategoryNode {
    std::string name;
    std::vector<CategoryNode*> children;

    CategoryNode(const std::string& n) : name(n) {}
};

class CategoryTree {
private:
    CategoryNode* root;

    void displayRec(CategoryNode* node, int depth) const;
    void destroyRec(CategoryNode* node);
    CategoryNode* findNode(CategoryNode* node, const std::string& name) const;

public:
    CategoryTree();
    ~CategoryTree();

    CategoryTree(const CategoryTree&) = delete;
    CategoryTree& operator=(const CategoryTree&) = delete;

    void buildDefaultHierarchy();
    bool addCategory(const std::string& parentName, const std::string& newCategory);
    void display() const;
    bool exists(const std::string& name) const;
};

#endif
