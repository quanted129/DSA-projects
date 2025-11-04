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

int minDepthToLeaf(node* root)
{
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    int leftDepth = (root->left != nullptr) ? minDepthToLeaf(root->left) : 2147483647;
    int rightDepth = (root->right != nullptr) ? minDepthToLeaf(root->right) : 2147483647;
    return ((leftDepth < rightDepth) ? leftDepth : rightDepth) + 1;
}

int lengthOfShortestPath(node* root)
{
    if (root == nullptr) return 0;
    return minDepthToLeaf(root->left) + minDepthToLeaf(root->right) + 1;
}

long long minPathSum(node* root, long long sum)
{
    if (root == nullptr) return 9223372036854775807;
    if (root->left == nullptr && root->right == nullptr) return sum + root->data;
    long long leftSum = minPathSum(root->left, sum + root->data);
    long long rightSum = minPathSum(root->right, sum + root->data);
    return (leftSum < rightSum) ? leftSum : rightSum;
}

long long sumOfShortestPath(node* root)
{
    if (root == nullptr) return 0;
    long long leftSum = minPathSum(root->left, 0);
    long long rightSum = minPathSum(root->right, 0);
    return leftSum + rightSum + root->data;
}

node* findNode(node* root, int target)
{
    if (root == nullptr) return nullptr;
    if (root->data == target) return root;
    if (target < root->data) return findNode(root->left, target);
    return findNode(root->right, target);
}

node* findCentralElement(node* semipathRoot, int leftDepth, int rightDepth)
{
    int center = (leftDepth + rightDepth + 1) >> 1;
    if (center < leftDepth)
    {
        node* current = semipathRoot->left;
        int steps = leftDepth - center - 1;
        for (int i = 0; i < steps; i++)
        {
            if (current->left != nullptr && minDepthToLeaf(current->left) == minDepthToLeaf(current) - 1)
            {
                current = current->left;
            }
            else if (current->right != nullptr && minDepthToLeaf(current->right) == minDepthToLeaf(current) - 1)
            {
                current = current->right;
            }
            else
            {
                if (current->left != nullptr)
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }
        }
        return current;
    }
    if (center == leftDepth) return semipathRoot;
    node* current = semipathRoot->right;
    int steps = center - leftDepth - 1;
    for (int i = 0; i < steps; i++)
    {
        if (current->left != nullptr && minDepthToLeaf(current->left) == minDepthToLeaf(current) - 1)
        {
            current = current->left;
        }
        else if (current->right != nullptr && minDepthToLeaf(current->right) == minDepthToLeaf(current) - 1)
        {
            current = current->right;
        }
        else
        {
            if (current->left != nullptr)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
    }
    return current;
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
    ofstream out("out.txt");
    int num, minLength = 2147483647;
    vector<node*> forks;
    node* root = nullptr;
    while (in >> num) root = build(root, num);
    in.close();
    findForks(root, forks);
    if (forks.empty())
    {
        NLR_traverse(root, out);
        return 0;
    }
    vector<node*> candidates;
    for (int i = 0; i < forks.size(); i++)
    {
        int length = lengthOfShortestPath(forks[i]);
        if (length < minLength)
        {
            minLength = length;
            candidates.clear();
            candidates.push_back(forks[i]);
        }
        else if (minLength == length) candidates.push_back(forks[i]);
    }
    if (!(minLength & 1))
    {
        NLR_traverse(root, out);
        return 0;
    }
    long long minSum = 9223372036854775807;
    node* semipathRoot;
    for (int i = 0; i < candidates.size(); i++)
    {
        long long sum = sumOfShortestPath(candidates[i]);
        if (sum < minSum)
        {
            semipathRoot = candidates[i];
            minSum = sum;
        }
        if (minSum == sum && candidates[i]->data < semipathRoot->data) semipathRoot = candidates[i];
    }
    int leftDepth = minDepthToLeaf(semipathRoot->left);
    int rightDepth = minDepthToLeaf(semipathRoot->right);
    node* nodeToDelete = findCentralElement(semipathRoot, leftDepth, rightDepth);
    NLR_traverse(deleteNode(root, nodeToDelete), out);
    out.close();
    return 0;
}