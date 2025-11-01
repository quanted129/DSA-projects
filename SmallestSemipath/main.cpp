#include <iostream>
#include <fstream>
#include <vector>
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
    }
    if (num > root->data)
    {
        root->right = build(root->right, num);
    }
    return root;
}

void findForks(node* root, vector<node*>& forks)
{
    if (root == nullptr) return;
    if (root->left != nullptr && root->right != nullptr) forks.push_back(root);
    findForks(root->left, forks);
    findForks(root->right, forks);
}

void NLR_traverse(node* root, ofstream& out)
{
    if (root == nullptr) return;
    out << root->data << '\n';
    NLR_traverse(root->left, out);
    NLR_traverse(root->right, out);
}

bool forkLeadsToLeaves(node* root)
{
    node* leftT = root->left;
    node* rightT = root->right;
    while (leftT->left != nullptr || leftT->right != nullptr)
    {
        if (leftT->left != nullptr && leftT->right != nullptr) return 0;
        if (leftT->left != nullptr) leftT = leftT->left;
        if (leftT->right != nullptr) leftT = leftT->right;
    }
    while (rightT->left != nullptr || rightT->right != nullptr)
    {
        if (rightT->left != nullptr && rightT->right != nullptr) return 0;
        if (rightT->left != nullptr) rightT = rightT->left;
        if (rightT->right != nullptr) rightT = rightT->right;
    }
    return 1;
}

int lengthToLeaf(node* root)
{
    if (root == nullptr) return 0;
    return lengthToLeaf(root->left) + lengthToLeaf(root->right) + 1;
}

long long sumOfChildren(node* root)
{
    if (root == nullptr) return 0;
    long long sum = 0;
    sum += root->data;
    sum += sumOfChildren(root->left);
    sum += sumOfChildren(root->right);
    return sum;
}

node* deleteNode(node* root, node* nodeToDelete)
{
    if (root == nullptr) return nullptr;
    if (nodeToDelete->data > root->data)
    {
        root->right = deleteNode(root->right, nodeToDelete);
        return root;
    }
    if (nodeToDelete->data < root->data)
    {
        root->left = deleteNode(root->left, nodeToDelete);
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
    root->right = deleteNode(root->right, temp);
    return root;
}

int main()
{
    ifstream in("in.txt");
    int num, minLength = 2147483647;
    vector<node*> forks;
    node* root = nullptr;
    while (in >> num) root = build(root, num);
    in.close();
    findForks(root, forks);
    vector<node*> leafForks;
    for (int i = 0; i < forks.size(); i++) if (forkLeadsToLeaves(forks[i])) leafForks.push_back(forks[i]);
    vector<node*> candidates;
    for (int i = 0; i < leafForks.size(); i++)
    {
        int length;
        bool newBest = 0;
        length = lengthToLeaf(leafForks[i]);
        if (length < minLength)
        {
            minLength = length;
            newBest = 1;
        }
        if (newBest) candidates.clear();
        if (minLength == length) candidates.push_back(leafForks[i]);
    }
    long long minSum = 9223372036854775807;
    node* nodeToDelete;
    for (int i = 0; i < candidates.size(); i++)
    {
        long long sum = sumOfChildren(candidates[i]);
        if (sum < minSum)
        {
            nodeToDelete = candidates[i];
            minSum = sum;
        }
        if (minSum == sum && nodeToDelete->data < candidates[i]->data) nodeToDelete = candidates[i];
    }
    ofstream out("out.txt");
    for (int i = 0; i < forks.size(); i++) out << forks[i]->data << '\n';
    out << endl;
    NLR_traverse(deleteNode(root, nodeToDelete), out);
    out.close();
}