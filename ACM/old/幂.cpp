//����һ��double���͵ĸ�����base��int���͵�����exponent����base��exponent�η���
class Solution {
public:
    double Power(double base, int exponent) {
    int p = abs(exponent);
      double r = 1.0;
        while(p){
            if(p & 1) r *= base;
            base *= base;
            p >>= 1;
        }
        return exponent < 0 ? 1/ r : r;

    }
};