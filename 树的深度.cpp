//����������

//˼·
//��û�������������������ֵ+1���أ��ݹ�����
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
     if(pRoot==NULL)
         return 0;
     int right=TreeDepth(pRoot->right);
     int left=TreeDepth(pRoot->left);
        
     return left>right?left+1:right+1;
    }
};