//��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20�������磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy��
class Solution {
public:
	void replaceSpace(char *str,int length) {
	char* cur = str;
		char* tail = str + length;
		while (cur!=tail)
		{
			if (*cur == ' ')
			{
				while (tail != cur)
				{
					*(tail + 2) = *tail;
					tail--;
				}
				*cur++ = '%';
				*cur++ = '2';
				*cur = '0';
				tail = str + length + 2;
			}
			cur++;
		}
	}
};