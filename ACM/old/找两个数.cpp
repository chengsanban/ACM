//һ�����������������������֮�⣬���������ֶ����������Ρ���д�����ҳ�������ֻ����һ�ε����֡� 


//˼·
//1��������ʹż�������������ͻ�ʣ�¸ղ�ָ�����������ֵ
//2��������ͬ����ĳλ�϶���1��Ҳ��������λ��ͬ�ĵط�����Ȼ������λ�ܶ࣬�ҳ�һλ���
//3����������һλ��������������ͻ�ʣ�·ֱ����
class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int len=data.size();
        if(len< 2) return ;
        int res=data[0]^data[1];
        for(int i=2;i<len;++i)
        {
           res^=data[i];   
        }
        
        int flag=1;
         while((res & flag) == 0) flag <<= 1;
        *num1 = res;
        *num2 = res;
        
        for(int i = 0; i < len; ++ i )
        {
            if((flag & data[i]) == 0) *num2 ^= data[i];
            else *num1 ^= data[i];
        }

        
    }
};