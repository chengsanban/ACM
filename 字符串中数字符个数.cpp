/*
写出一个程序，接受一个有字母和数字以及空格组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。

输入描述:
输入一个有字母和数字以及空格组成的字符串，和一个字符。

输出描述:
输出输入字符串中含有该字符的个数。

示例1
输入
ABCDEF A
输出
1
*/


#include<iostream>
#include<string.h>
using namespace std;

int main()
{
    string s;
    char c;
    char c1;
    int count=0;
    while(cin>>s>>c)
    {
        c1 = c > 'Z' ? c - 32 : c + 32;
        
        for(int i=0;i<s.length();++i)
        {
            if(s[i] == c || s[i] == c1) ++count;
        }
        cout<<count;
    }
    return 0;
}