//��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
//����һ����������������һ����ת�������ת�������СԪ�ء�
//��������{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת�����������СֵΪ1��
// NOTE������������Ԫ�ض�����0���������СΪ0���뷵��0��
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size()==0){
            return 0;
        }
        int min = rotateArray[0];
        for(int i=1;i<rotateArray.size();i++){
            if(rotateArray[i]<min){
                min = rotateArray[i];
                break;
            }
        }
        return min;
    }
};
