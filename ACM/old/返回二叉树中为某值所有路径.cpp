//����һ�Ŷ�������һ����������ӡ���������н��ֵ�ĺ�Ϊ��������������·����
//·������Ϊ�����ĸ���㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·����


//���ͣ�ͨ���ݹ�Ѹ����������εݼ���ֱ������һ����ʣ������ͬ�Ľڵ�ֵ���Ҵ˽ڵ���Ҷ��
class Solution {
public:
    void GetPath(TreeNode* root,int expectNumber,vector<int> &path,vector<vector<int>> &Ret)
    {
        if(root==NULL||root->val>expectNumber)//�ջ��߽ڵ����Ѿ�����Ԥ������pass
            return;
        path.push_back(root->val);
		//��ǰ�ڵ�ֵ��Ԥ������ͬ��ΪҶ�ӽڵ㣬��������·�������ҵ�����ǰֵ��������һ��
        if(root->val==expectNumber&&root->right==NULL&&root->left==NULL)
        {
            Ret.push_back(path);
            path.pop_back();
        }
		//�����ݹ�
        else
        {
        	GetPath(root->left,expectNumber-root->val,path,Ret);   
       	    GetPath(root->right,expectNumber-root->val,path,Ret);
            path.pop_back();
        }
    }
    
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) 
    {
		vector<vector<int>> Ret;
        vector<int> path;
        if(root==NULL)
            return Ret;
        GetPath(root,expectNumber,path,Ret);
        return Ret;
    }
};