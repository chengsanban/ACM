//��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ����ά�����һ���������ж��������Ƿ��и������� 

class Solution {
public:
    bool Find(vector<vector<int> > array,int target) {
              int sizeX = array.size();
        int sizeY = array[0].size();
        int i = sizeX-1;
        int j = 0;
        while (i >= 0 && j < sizeY) {
            if (target == array[i][j])
             return true;
            else if (target < array[i][j])
             i--;              
            else
                 j++;
        }
        return false;
    }
};