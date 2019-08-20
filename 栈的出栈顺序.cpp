//���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�Ϊ��ջ�ĵ���˳��
//����ѹ��ջ���������־�����ȡ���������1,2,3,4,5��ĳջ��ѹ��˳������4��5,3,2,1�Ǹ�ѹջ���ж�Ӧ��һ��
//�������У���4,3,5,1,2�Ͳ������Ǹ�ѹջ���еĵ������С� 
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> st;
        int len1 = pushV.size();
        int len2 = popV.size();
        if(len1 != len2 || 0 == len1)
            return false;
        int j = 0;
        for(int i = 0;i < len1;++i) {
            st.push(pushV[i]);
            for(;j < len1;++j) {
                if(!st.empty() && popV[j] == st.top()) 
                    st.pop();
                else
                    break;
            }
        }
        return st.empty();
    }
};
