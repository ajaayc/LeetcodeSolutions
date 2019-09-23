#include <queue>
#include <iostream>
#define COUNT 10 

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val):val(val),left(NULL),right(NULL){}
};

class BTree{
    TreeNode* root;

    void cleanTree(TreeNode* curr){
        if(curr == NULL) return;

        cleanTree(curr->left);
        cleanTree(curr->right);
        delete curr;
        curr = NULL;
    }
    
public:
    BTree():root(NULL){}

    BTree(TreeNode* root):root(root){}

    ~BTree(){
        cleanTree(root);
    }

    bool isEmpty(){
        return root == NULL;
    }

    TreeNode* getRootNode(){
        return root;
    }
    
    void insert(int val){
        TreeNode* n = new TreeNode(val);
        if(root == NULL){
            root = n;
            return;
        }

        //Get destination
        TreeNode* curr = root;
        TreeNode* prev = NULL;

        bool isRight = false;
        while(curr != NULL){
            prev = curr;

            if(val > curr->val){
                curr = curr->right;
                isRight = true;
            }
            else{
                curr = curr->left;
                isRight = false;
            }
        }
        //Target
        TreeNode*& target = (isRight ? prev->right : prev->left);
        
        target = n;
    }

    void printTreeInOrder(){
        if (this->isEmpty()) return;

        std::queue<TreeNode*> toPrint;

        toPrint.push(root);
        while(!toPrint.empty()){
            TreeNode* curr = toPrint.front();
            toPrint.pop();

            if(curr != NULL){
                std::cout << curr->val << std::endl;
                //Add left and right nodes if they're not null
                toPrint.push(curr->left);
                toPrint.push(curr->right);
            }
        }
    }

};

// Function to print binary tree in 2D  
// It does reverse inorder traversal  
void print2DUtil(TreeNode *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->val<<"\n";  
  
    // Process left child  
    print2DUtil(root->left, space);  
}  
  
// Wrapper over print2DUtil()  
void print2D(TreeNode *root)  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    //root is a NULL node
    void constructMaximumBinaryTreeHelper(TreeNode*& root,const vector<int>& nums, int lb, int rb) {
        //If lb and rb are out of order or either is out of bounds, return
        if(lb > rb || (lb < 0 || lb  >= static_cast<int>(nums.size())) || (rb < 0 || rb >= static_cast<int>(nums.size()))){
            return;
        }

        
        int maxNum = nums[lb];
        int maxIndex = lb;
        
        //Find the maximum between lb and rb inclusive
        for(int currIndex = lb; currIndex <= rb; ++currIndex){
            if(nums[currIndex] > maxNum){
                maxIndex = currIndex;
                maxNum = nums[currIndex];
            }
        }

        //Create TreeNode
        root = new TreeNode(maxNum);

        constructMaximumBinaryTreeHelper(root->left,nums,lb,maxIndex-1);
        constructMaximumBinaryTreeHelper(root->right,nums,maxIndex+1,rb);
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode* root = NULL;
        constructMaximumBinaryTreeHelper(root,nums,0,nums.size()-1);
        return root;
    }
};

int main(){
    Solution s;

    vector<int> nums = {3,2,1,6,0,5};
    TreeNode* root = s.constructMaximumBinaryTree(nums);
    
    cout << "Constructed Tree" << endl;
    print2D(root);

    //Clear memory by assigning TreeNode to a BTree
    //object so that BTree destructor will be called
    BTree b(root);
}
