//������������ĵ�һ������

//���
//1��ɨ������������
//2���ó����������������Ȳ�ֵ��
//3����������һ���������ĵ�һ�����������
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2) {
        if(pHead1==NULL||pHead2==NULL)
            return NULL;
        int len1=0;
        int len2=0;
        ListNode* new1=pHead1;
        ListNode* new2=pHead2;
        while(new1)
         {
         new1=new1->next;
         ++len1;
        }
        while(new2)
        {
         new2=new2->next;
         ++len2;   
        }
        int ans=abs(len1-len2);
        if(len1>len2)
        {
          	while(ans)
        	{
            	pHead1=pHead1->next;
                --ans;
        	}   
        }
        else
        {
             while(ans)
        	{
            	pHead2=pHead2->next;
                --ans;
        	}   
        }

        while(pHead1!=pHead2)
         {
            pHead1=pHead1->next;
            pHead2=pHead2->next;
        }
        
        return pHead1;
    }
};