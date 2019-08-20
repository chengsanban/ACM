//����ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ��СԪ�ص�min����
//��������ջһ�������ݣ�һ������Сֵ
#include<cassert>
class Solution {
public:
    stack<int> m_data, m_min;
    //pushʱ��push����С�ڵ�ǰ����С���ݵĶѶ��Ŵ���
//������pop����ʱ������ջ��ԭ��ֻҪû��ջ������Сֵ����Сֵһ��ջ��Ԫ��	
    void push(int value) 
    {
        m_data.push(value);
        if(m_min.size() == 0 || m_min.top() >= value)
            m_min.push(value);
    }
    void pop() 
    {
        assert(m_data.size() >0 && m_min.size() > 0);
        if(m_data.top()==m_min.top())
             m_min.pop();
        m_data.pop();
    }
    int top() {
        assert(m_data.size() > 0 && m_min.size() > 0);
        return m_data.top();
    }
    int min() {
        assert(m_data.size() > 0 && m_min.size() > 0);
        return m_min.top();
    }
};
