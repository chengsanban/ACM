//һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж����������� 
class Solution { 

public: 

    int jumpFloor(int number) { 

        int a[number+1]; 

        int i; 

        a[1]=1; 

        a[2]=2; 

        for(i=3;i<=number;i++) 

        { 

            a[i]=a[i-1]+a[i-2]; 

        } 

        return a[number]; 

    } 

}; 
//һֻ����һ�ο�������1��̨�ף�Ҳ��������2��������Ҳ��������n���������������һ��n����̨���ܹ��ж����������� 
class Solution {
public:
    int jumpFloorII(int number) {
return  1<<--number;
    }
};