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
    int num;
    while (in >> num) root = build(root, num);
    in.close();
    NLR_traverse(root, out);
    out.close();
    return 0;
}