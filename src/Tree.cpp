#include "Tree.h"
#include <queue>
#include <iostream>

using namespace std;

// ============================================================
// BST Implementation (adapted to Student A's Resource::getID())
// ============================================================

BST::BST() : root(nullptr) {}

BST::~BST() {
    destroyRec(root);
}

void BST::destroyRec(TreeNode* node) {
    if (node == nullptr) return;
    destroyRec(node->left);
    destroyRec(node->right);
    delete node;
}

TreeNode* BST::insertRec(TreeNode* node, const Resource& r) {
    if (node == nullptr) {
        return new TreeNode(r);
    }
    if (r.getID() < node->data.getID()) {
        node->left = insertRec(node->left, r);
    } else if (r.getID() > node->data.getID()) {
        node->right = insertRec(node->right, r);
    }
    return node;
}

void BST::insert(const Resource& r) {
    root = insertRec(root, r);
}

TreeNode* BST::searchRec(TreeNode* node, const string& id) const {
    if (node == nullptr || node->data.getID() == id) {
        return node;
    }
    if (id < node->data.getID()) {
        return searchRec(node->left, id);
    }
    return searchRec(node->right, id);
}

bool BST::search(const string& id) const {
    return searchRec(root, id) != nullptr;
}

TreeNode* BST::findMin(TreeNode* node) const {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* BST::removeRec(TreeNode* node, const string& id) {
    if (node == nullptr) return nullptr;

    if (id < node->data.getID()) {
        node->left = removeRec(node->left, id);
    } else if (id > node->data.getID()) {
        node->right = removeRec(node->right, id);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            TreeNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeRec(node->right, successor->data.getID());
        }
    }
    return node;
}

void BST::remove(const string& id) {
    root = removeRec(root, id);
}

void BST::inorderRec(TreeNode* node) const {
    if (node == nullptr) return;
    inorderRec(node->left);
    node->data.display();
    inorderRec(node->right);
}

void BST::inorder() const {
    cout << "\n--- Inorder Traversal (Sorted by Resource ID) ---\n";
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }
    inorderRec(root);
}

void BST::preorderRec(TreeNode* node) const {
    if (node == nullptr) return;
    node->data.display();
    preorderRec(node->left);
    preorderRec(node->right);
}

void BST::preorder() const {
    cout << "\n--- Preorder Traversal ---\n";
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }
    preorderRec(root);
}

void BST::postorderRec(TreeNode* node) const {
    if (node == nullptr) return;
    postorderRec(node->left);
    postorderRec(node->right);
    node->data.display();
}

void BST::postorder() const {
    cout << "\n--- Postorder Traversal ---\n";
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }
    postorderRec(root);
}

void BST::levelOrder() const {
    cout << "\n--- Level-Order Traversal ---\n";
    if (root == nullptr) {
        cout << "Tree is empty.\n";
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        current->data.display();
        if (current->left)  q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

bool BST::isEmpty() const {
    return root == nullptr;
}

// ============================================================
// Category Tree
// ============================================================

CategoryTree::CategoryTree() {
    root = new CategoryNode("CAMPUS");
}

CategoryTree::~CategoryTree() {
    destroyRec(root);
}

void CategoryTree::destroyRec(CategoryNode* node) {
    if (node == nullptr) return;
    for (CategoryNode* child : node->children) {
        destroyRec(child);
    }
    delete node;
}

void CategoryTree::buildDefaultHierarchy() {
    for (CategoryNode* child : root->children) {
        destroyRec(child);
    }
    root->children.clear();

    CategoryNode* academic = new CategoryNode("Academic");
    academic->children.push_back(new CategoryNode("Laboratories"));
    academic->children.push_back(new CategoryNode("Lecture Rooms"));
    academic->children.push_back(new CategoryNode("Computer Labs"));

    CategoryNode* services = new CategoryNode("Services");
    services->children.push_back(new CategoryNode("Library"));
    services->children.push_back(new CategoryNode("Offices"));
    services->children.push_back(new CategoryNode("Meeting Rooms"));

    CategoryNode* recreation = new CategoryNode("Recreation");
    recreation->children.push_back(new CategoryNode("Sports Facilities"));

    root->children.push_back(academic);
    root->children.push_back(services);
    root->children.push_back(recreation);
}

void CategoryTree::displayRec(CategoryNode* node, int depth) const {
    if (node == nullptr) return;
    for (int i = 0; i < depth; ++i) cout << "    ";
    if (depth == 0) cout << node->name << endl;
    else cout << "|-- " << node->name << endl;
    for (CategoryNode* child : node->children) {
        displayRec(child, depth + 1);
    }
}

void CategoryTree::display() const {
    cout << "\n========== Campus Category Hierarchy ==========\n";
    displayRec(root, 0);
    cout << "==============================================\n";
}

CategoryNode* CategoryTree::findNode(CategoryNode* node, const string& name) const {
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;
    for (CategoryNode* child : node->children) {
        CategoryNode* found = findNode(child, name);
        if (found != nullptr) return found;
    }
    return nullptr;
}

bool CategoryTree::addCategory(const string& parentName, const string& newCategory) {
    CategoryNode* parent = findNode(root, parentName);
    if (parent == nullptr) {
        cout << "Error: Parent category \"" << parentName << "\" not found.\n";
        return false;
    }
    for (CategoryNode* child : parent->children) {
        if (child->name == newCategory) {
            cout << "Category already exists under this parent.\n";
            return false;
        }
    }
    parent->children.push_back(new CategoryNode(newCategory));
    cout << "Category \"" << newCategory << "\" added under \"" << parentName << "\".\n";
    return true;
}

bool CategoryTree::exists(const string& name) const {
    return findNode(root, name) != nullptr;
}
