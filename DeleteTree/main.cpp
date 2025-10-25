#include <fstream>
using namespace std;

struct node
{
    int data;
    node* left;
    node* right;
};

node* build(node* root, int num)
{
    if (root == nullptr)
    {
        root = new node();
        root->data = num;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    if (num < root->data)
    {
        root->left = build(root->left, num);
        return root;
    }
    if (num > root->data)
    {
        root->right = build(root->right, num);
        return root;
    }
    return root;
}

node* deleteKey(node* root, int key)
{
    if (root == nullptr) return nullptr;
    if (key > root->data)
    {
        root->right = deleteKey(root->right, key);
        return root;
    }
    if (key < root->data)
    {
        root->left = deleteKey(root->left, key);
        return root;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        delete root;
        return nullptr;
    }
    if (root->left == nullptr && root->right != nullptr)
    {
        node* newRoot = root->right;
        delete root;
        return newRoot;
    }
    if (root->left != nullptr && root->right == nullptr)
    {
        node* newRoot = root->left;
        delete root;
        return newRoot;
    }
    node* temp = root->right;
    while (temp->left != nullptr) temp = temp->left;
    int largerKey = temp->data;
    root->data = largerKey;
    root->right = deleteKey(root->right, largerKey);
    return root;
}

void NLR_traverse(node* root, ofstream& out)
{
    if (root == nullptr) return;
    out << root->data << '\n';
    NLR_traverse(root->left, out);
    NLR_traverse(root->right, out);
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    node* root = nullptr;
    int key, num;
    in >> key;
    while (in >> num) root = build(root, num);
    in.close();
    root = deleteKey(root, key);
    NLR_traverse(root, out);
    out.close();
    return 0;
}