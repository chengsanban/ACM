//����һ����������ÿ���ڵ����нڵ�ֵ���Լ�����ָ�룬һ��ָ����һ���ڵ㣬��һ������ָ��ָ������һ���ڵ㣩�� ������

//���������ÿ���ڵ�֮��������ڵ㣬����ֵǰ�ڵ�ֵ
//Ȼ���ǰһ���ڵ�ĸ���ָ�븴�Ƹ���һ��
//����ԭ���ͱ���
//������Բο�����http://www.cnblogs.com/daniagger/archive/2012/06/19/2555321.html
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead==NULL) return NULL;
 
        RandomListNode *newHead = new RandomListNode(pHead->label);
        RandomListNode *pHead1=NULL, *pHead2=NULL;
 
        // ������ʹ�¾������֮��������
        for(pHead1=pHead,pHead2=newHead;pHead1;){
            RandomListNode* tmp = pHead1->next;
            pHead1->next = pHead2;
            pHead2->next = tmp;
 
            // next
            pHead1 = tmp;
            if(tmp) pHead2 = new RandomListNode(tmp->label);
            else pHead2 = NULL;
        }
 
        // �����������randomָ��
        for(pHead1=pHead,pHead2=newHead;pHead1;){
            if(pHead1->random) pHead2->random = pHead1->random->next;
            else pHead2->random = NULL;
 
            pHead1 = pHead2->next;
            if(pHead1) pHead2 = pHead1->next;
            else pHead2 = NULL;
        }
 
        // ���������¸������nextָ��
        for(pHead1=pHead,pHead2=newHead;pHead1;){
            pHead1->next = pHead2->next;
            if(pHead1->next) pHead2->next = pHead1->next->next;
            else pHead2->next = NULL;
 
            pHead1 = pHead1->next;
            pHead2 = pHead2->next;
        }
 
        return newHead;
    }
};
