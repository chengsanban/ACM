//����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ���������������Ľ���ж������ظ���//���֡���������ǰ���������{1,2,4,7,3,5,6,8}�������������{4,7,2,1,5,3,8,6}�����ؽ������������ء�
 class Solution {
public:
    struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) {    
         
        struct TreeNode *result = createBinaryTreeHelper(pre, in, 
                                                  0, pre.size() - 1, 0, in.size() - 1);
        return result;
    }
     
    struct TreeNode* createBinaryTreeHelper(vector<int> pre, vector<int> in, 
                                            int preLeft, int preRight, int inLeft, int inRight) {
        if(preLeft > preRight) return NULL;
         
        int rootValue = pre[preLeft];
        struct TreeNode *rootNode = new TreeNode(rootValue);
         
        int index;   // ����������������е�λ��
        for(int i = inLeft; i <= inRight; ++i) {
            if(in[i] == rootValue) {
                index = i;
                break;
            }
        }
        int lenLeft = index - inLeft;
        int lenRight = inRight - index;
         
        rootNode->left = createBinaryTreeHelper(pre, in, preLeft + 1, preLeft + lenLeft, 
                                                         inLeft, index - 1);
        rootNode->right = createBinaryTreeHelper(pre, in, preRight - lenRight + 1, preRight, 
                                                         index + 1, inRight);
         
        return rootNode;
    }
};
 