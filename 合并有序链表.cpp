class Solution { 

public: 

    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) 

    { 

        if(!pHead1) 

            return pHead2; 

        if(!pHead2) 

            return pHead1; 

        ListNode* Head; 

        ListNode* p; 

        //ȡ��Сֵ��ͷ��� 

        if(pHead1->val<=pHead2->val){ 

            Head=pHead1; 

            pHead1=pHead1->next; 

        } 

        else{ 

            Head=pHead2; 

            pHead2=pHead2->next; 

        }   

        //��ʼ�����ϲ� 

        p=Head;                                                   //pΪ�ϲ��������Ĺ���ָ�� 

        while(pHead1&&pHead2){                       //����һ��������βʱ��ѭ������ 

            if(pHead1->val<=pHead2->val){          //�������1�Ľ��С������2�Ľ�� 

                p->next=pHead1;                            //ȡ���������ϲ����� 

                pHead1=pHead1->next;                 //����1����һλ 

                p=p->next;                                      //����ָ�����һλ 

            }                

            else{                                               //����ȡ����2�Ľ�� 

                p->next=pHead2; 

                pHead2=pHead2->next; 

                p=p->next; 

            }                 

        } 

        if(pHead1 == NULL)           //����1�������� 

            p->next = pHead2;         //�������2Ҳ�������ˣ���pHead2=NULL 

        if(pHead2 == NULL)            //����2�������� 

            p->next = pHead1;         ///�������1Ҳ�������ˣ���pHead1=NULL 

        return Head; 

    } 

}; 