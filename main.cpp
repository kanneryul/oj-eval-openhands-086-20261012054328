#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
    
    void inorderHelper(TreeNode* node, vector<int>& result) {
        if (node == nullptr) return;
        inorderHelper(node->left, result);
        result.push_back(node->val);
        inorderHelper(node->right, result);
    }
    
    void swapChildren(TreeNode* node) {
        if (node == nullptr) return;
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
    
    void markDepths(TreeNode* root, vector<vector<TreeNode*>>& depthNodes, int currentDepth) {
        if (root == nullptr) return;
        
        // Ensure the vector has enough space
        if (currentDepth >= depthNodes.size()) {
            depthNodes.resize(currentDepth + 1);
        }
        
        depthNodes[currentDepth].push_back(root);
        
        markDepths(root->left, depthNodes, currentDepth + 1);
        markDepths(root->right, depthNodes, currentDepth + 1);
    }
    
    void processSwaps(TreeNode* root, int k) {
        // First, mark all nodes with their depths
        vector<vector<TreeNode*>> depthNodes;
        markDepths(root, depthNodes, 1); // Root is at depth 1
        
        // Perform swap operation on all nodes at depth that is multiple of k
        for (int depth = k; depth < depthNodes.size(); depth += k) {
            for (TreeNode* node : depthNodes[depth]) {
                swapChildren(node);
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    
    // Create nodes
    vector<TreeNode*> nodes(n + 1);
    for (int i = 1; i <= n; i++) {
        nodes[i] = new TreeNode(i);
    }
    
    // Read children information
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        
        if (left != -1) {
            nodes[i]->left = nodes[left];
        }
        if (right != -1) {
            nodes[i]->right = nodes[right];
        }
    }
    
    int t;
    cin >> t;
    
    Solution solution;
    
    // Process each query
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        
        // Process swaps for this k
        solution.processSwaps(nodes[1], k);
        
        // Get and print inorder traversal
        vector<int> result = solution.inorderTraversal(nodes[1]);
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Clean up memory
    for (int i = 1; i <= n; i++) {
        delete nodes[i];
    }
    
    return 0;
}