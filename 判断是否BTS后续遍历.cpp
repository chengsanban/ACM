//����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ��������������Yes,�������No���������������������������ֶ�������ͬ��

//��Ϊ����������������������һ���������������ǰ�沿��һ��С�ڸ�������һ�����ڸ�
//�������鵱ǰ��С�ڸ�������ȫ�����ڸ���������������ݹ����
class Solution {
public:
    bool JudgeBTS(vector<int> &sequence,int first,int end)
        {
        if(end<=first)
            return true;
        int i=first;
        for(;i<end;++i)   //�ж��Ƿ�ǰ��һ����С�ڸ�
            if(sequence[i]>sequence[end])
            break;
        for(int j=i+1;j<end;++j)//����ʣ�µĲ���һ�����ڸ���Ҫ��С��һ������
            if(sequence[j]<sequence[end])
            return false;
       return JudgeBTS(sequence,first,i-1)&&JudgeBTS(sequence,i,end-1);
        //�ݹ�
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
		if(sequence.empty())		//�յĻ����ز���
            return false;
        return JudgeBTS(sequence,0,sequence.size()-1);
    }
};