//��Ŀ����
//����һ����������������е�����k�����

//����1����ǰ����������ż����ɾ��β��
//�ռ�С��ʱ��ȽϷ�
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        vector<int>::iterator even = array.begin();
	int size = array.size();
	while (size)
	{
		if (*even % 2 == 0)
		{
			int tmp = *even;
			even = array.erase(even);
			array.push_back(tmp);
		}
		else
			even++;
		size--;
	}
    }
};
//����2��ż����¼���������ں���
//ʱ��O��n�����ռ�O(n)
void Sloution(vector<int> &array)
{
	vector<int> v;
	vector<int>::iterator evenPtr = array.begin();
	vector<int>::iterator ptr = evenPtr;
	while (ptr!=array.end())
	{
		if (*ptr % 2 == 0)
			v.push_back(*ptr);
		else
		{
			*evenPtr = *ptr;
			evenPtr++;
		}
		ptr++;
	}
	vector<int>::iterator vPtr = v.begin();
	while (evenPtr != array.end())
	{
		*evenPtr = *vPtr;
		evenPtr++;
		vPtr++;
	}
}