//
//  main.cpp
//  TestAlgorithm
//
//  Created by Channer Duan on 5/29/16.
//  Copyright © 2016 Channer Duan. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <stack>
#include <map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int size_pre = (int) preorder.size();
        int size_in = (int) inorder.size();
        if (size_pre == 0 || size_pre != size_in) {
            return NULL;
        }
        int i;
        map<int, int> inorderMap;
        for (i = 0;i < size_in;i++) {
            inorderMap[inorder.at(i)] = i;
        }
        TreeNode * pRoot = new TreeNode(preorder.at(0));
        stack<TreeNode*> nodeStack;
        stack<int> grandparentIndexStack;
        nodeStack.push(pRoot);
        grandparentIndexStack.push(size_pre);
        int grandparentIndex, parentIndex, targetIndex;
        TreeNode * pParent;
        for (i = 1;i < size_pre;i++) {
            pParent = nodeStack.top();
            grandparentIndex = grandparentIndexStack.top();
            parentIndex = inorderMap[pParent->val];
            targetIndex = inorderMap[preorder.at(i)];
            if (targetIndex < parentIndex) {
                pParent->left = new TreeNode(preorder.at(i));
                nodeStack.push(pParent->left);
                grandparentIndexStack.push(parentIndex);
            } else if (targetIndex > parentIndex) {
                while (targetIndex > grandparentIndex) {
                    nodeStack.pop();
                    pParent = nodeStack.top();
                    grandparentIndexStack.pop();
                    grandparentIndex = grandparentIndexStack.top();
                }
                nodeStack.pop();
                grandparentIndexStack.pop();
                pParent->right = new TreeNode(preorder.at(i));
                nodeStack.push(pParent->right);
                grandparentIndexStack.push(grandparentIndex);
            } else {
                return NULL;
            }
        }
        return pRoot;
    }
    
    void printTree(TreeNode* pNode, int depth) {
        if (pNode->left != NULL) printTree(pNode->left, depth+1);
        if (pNode->right != NULL) printTree(pNode->right, depth+1);
        printf(", %d(%d)", pNode->val, depth);
    }
    
    
};
int main(int argc, const char * argv[]) {
    vector<int> preorder;
    vector<int> inorder;
    preorder.push_back(1);
    preorder.push_back(2);
    preorder.push_back(3);
//    preorder.push_back(4);
    inorder.push_back(2);
    inorder.push_back(1);
    inorder.push_back(3);
//    inorder.push_back(4);
    TreeNode* pRoot = Solution().buildTree(preorder, inorder);
    Solution().printTree(pRoot, 0);
    printf("Nice to meet you again!\n");
    return 0;
}





