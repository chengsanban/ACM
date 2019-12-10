//����ĳ����������֮��ĳ������


//�ܽ�
//���ö��ֲ����ҳ�ĳ��k���ֵ�λ�ã�Ȼ���ٷֱ���ǰ���������ܵĸ���
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int i = binaryFind(data,0,data.size(),k);
        if( i == -1) return 0;
        int sum = 1;
        for(int j = i - 1; j >= 0; j--){
            if(data[j] == k) sum++;
            else break;
        }
        for(int j = i + 1; j < data.size(); j++){
            if(data[j] == k) sum++;
            else break;
        }
        return sum;
    }
     
    int binaryFind(vector<int> &data, int begin, int end ,int k){
        if(begin >= end) return -1;
        int mid = (begin + end) / 2;
        if(data[mid] == k) return mid;
        int res = -1;
        if((res = binaryFind(data,begin,mid,k)) != -1) return res;
        if((res = binaryFind(data,mid + 1, end,k) != -1)) return res;
        return -1;
    }
};