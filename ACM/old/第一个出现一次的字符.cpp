//��Ŀ����һ���ַ����е�һ������һ�ε��ַ�


//���һ
//һ�α����������
//��������СΪ26��hash������һ����СΪ256��hash��Ҳ���ԣ����ַ�Ϊhash��ļ�ֵ
//ֵΪ��Ӧ���ַ����ִ���
//һ��vector<pair<char,int> >����Ÿ�char��һ�γ��ֵ�λ��
//����ÿ���ַ�ʱ���ж�hash�����ַ��Ƿ�Ϊ0��Ϊ������ַ���һ�γ��֣������ַ���
//��λ��push��vector�С�����Ϊ0���߸ü�ֵ��Ӧ��ֵ��һ
//������֮�󣬿�����vector����pair<char,int>�е�charΪ��ֵ��hash�в鿴��ֵ�Ƿ�Ϊ1����
//��1���򷵻�pair<char,int> �е�int��Ϊ��һ��ֻ����һ���ַ��ĳ���λ��


//����
//����ʹ�ù�ϣ����һ��ͳ�Ƹ������ڶ����ǰ�������ҵ���һ���ַ�����Ϊ1�ļ�λ����
 
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        if(str.empty()) return -1;
        int countsA[26] = {0};
        int countsB[26] = {0};
        vector<pair<char,int> > comeoutOrder;
        pair<char,int> pairIt;
        for(int i = 0;i<str.size();i++){
            if(str[i] >= 'A' && str[i] <= 'Z'){
                if(countsA[str[i]-'A'] == 0){
                    countsA[str[i]-'A']++;
                    pairIt.first = str[i];
                    pairIt.second = i;
                    comeoutOrder.push_back(pairIt);
                }
                else countsA[str[i]-'A']++;
            }
            else if(str[i] >= 'a' && str[i] <= 'z'){
                if(countsB[str[i]-'a'] == 0){
                    countsB[str[i]-'a']++;
                    pairIt.first = str[i];
                    pairIt.second = i;
                    comeoutOrder.push_back(pairIt);
                }
                else countsB[str[i]-'a']++;
            }
            else return -1;
        }
        for(int i = 0;i<comeoutOrder.size();i++){
            if(comeoutOrder[i].first >= 'A' && comeoutOrder[i].first <= 'Z')
                {
                if(countsA[comeoutOrder[i].first-'A'] == 1) return comeoutOrder[i].second;
            }
            else {
                if(countsB[comeoutOrder[i].first-'a'] == 1) return comeoutOrder[i].second;
            }
        }
         
        return -1;
    }
};
