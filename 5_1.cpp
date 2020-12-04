#include <iostream>
#include <cstring>
#include <cstdlib>
class Complex{
    double real,img;
    //���������θ� ���ǰ� �ۿ����� ����� �ʿ���� �Լ�
    int find_i(const char * str,int end) const;
    double get_numbers(const char * str, int from, int to) const;
    public:
        Complex(double real, double img):real(real),img(img){}
        Complex(const Complex & c){real=c.real; img=c.img;}
        Complex(const char * str);
        //��Ģ ������ ��� �ݵ�� ���� ����
        //Complex a = b + c + b;
        //�Ƹ��� �� ������ �� ��� ���忡���� ��������� a = 2 * b + c; �� �ǵ��Ͽ��� ���Դϴ�.

        // ������, ������ ó���Ǵ� ���� ���ڸ�, (b.plus(c)).plus(b) �� �Ǵµ�, b.plus(c) �� �ϸ鼭 b ���� (b + c) �� ����, 
        //�ű⿡ �ٽ� plus(b) �� �ϰ� �ȴٸ� �� ��ü�� ���ڸ� (b + c) + (b + c) �� �Ǽ� (�ֳ��ϸ� ���� b ���� b + c �� �� �����ϱ�) a = 2 * b + 2 * c �� �Ǳ� �����Դϴ�. 
        //�̷��� ������ ���� ���ؼ��� �ݵ�� ��Ģ ������ ��� �ݵ�� ���� �����ؾ� �� �մϴ�.
        Complex operator+(const Complex& c) const;
        //(��ȣ) (�Ǽ���) (��ȣ) i (�����)
        // Complex operator+(const char* str) const;

        Complex operator-(const Complex& c) const;
        // Complex operator-(const char * str) const;

        Complex operator*(const Complex& c) const;
        // Complex operator*(const char * str) const;

        Complex operator/(const Complex& c) const;
        // Complex operator/(const char * str) const;

        Complex& operator+=(const Complex& c);
        Complex& operator-=(const Complex& c);
        Complex& operator*=(const Complex& c);
        Complex& operator/=(const Complex& c);

        Complex& operator=(const Complex & c);
        void println() { std::cout << "( " << real << " , " << img << " ) " << std::endl; }
        
        
};
Complex::Complex (const char * str){
    int begin=0, end=strlen(str);
    real=0.0;
    img=0.0;

    int pos_i=find_i(str,end);
    if(pos_i==-1){
        real=get_numbers(str,begin,end-1);
        return ; //���� �����ڴ� return�� ������� ������, �� �ڿ� �ڵ带�����Ű�� �ʱ� ���� ����� �� �� �ִ�.
    }
    real=get_numbers(str,begin,pos_i-1);
    img=get_numbers(str,pos_i+1,end-1);
    if(pos_i>=1 && str[pos_i-1]=='-')img*=-1.0;
}
int Complex::find_i(const char * str,int end) const{
    for(int i=0; i!=end;i++){
        if(str[i]=='i')
            return i;
    }
    return -1;
}
double Complex::get_numbers(const char * str, int from , int to) const {
    char * temp=new char[to-from+1];
    strncpy(temp,str+from, to-from+1); //str+from�� str�κ��� from ������������ ���縦 �ϱ� ���ؼ� 
    double ret_value=atof(temp);
    delete[] temp;
    return ret_value;
    
    // bool minus=false;
    // if(from >to) return 0;
    // if(str[from]=='-')minus=true;
    // if(str[from]=='-'|| str[from]=='+')from++;

    // double num=0.0;
    // double decimal=1.0;
    // bool integer_part=true;
    // for(int i=from ;i<=to; i++){
    //     if(isdigit(str[i]) && integer_part){
    //         num*=10.0;
    //         num+=(str[i]-'0');
    //     }
    //     else if(str[i]=='.')integer_part=false;
    //     else if(isdigit(str[i]) && !integer_part){
    //         decimal/=10.0;
    //         num+=((str[i]-'0')*decimal);
    //     }
    //     else
    //         break;
    // }

    // return minus ? (-1.0)*num : num;
    // return 0.0;
}
// Complex Complex::operator+(const char* str) const{
//     return (*this)+Complex(str);
//     // int begin=0, end=strlen(str);
//     // double str_img=0.0, str_real=0.0;

//     // //i�� �ε���ã��
//     // int pos_i=find_i(str,end);

//     // //�Ǽ��θ� �����Ұ��
//     // if(pos_i==-1){
//     //     str_real=get_numbers(str,begin,end-1);
//     //     return (*this)+Complex(str_real,str_img);
//     // }

//     // str_real=get_numbers(str,begin,pos_i-1);
//     // str_img=get_numbers(str,pos_i+1,end-1);

//     // if(pos_i>=1 && str[pos_i-1]=='-')str_img*=-1.0;
//     // return (*this)+Complex(str_real,str_img);

// }
Complex Complex::operator+(const Complex& c) const{
    return Complex(real+c.real,img+c.img);
}

Complex Complex::operator-(const Complex& c) const{
    return Complex(real-c.real, img-c.img);
}

// Complex Complex::operator-(const char * str) const{
//     return (*this)-Complex(str);
// }

Complex Complex::operator*(const Complex & c) const{
    return Complex(real*c.real-img*c.img,real*c.img+c.real*img);
}

// Complex Complex::operator*(const char * str) const{
//     return (*this)*Complex(str);
// }

Complex Complex::operator/(const Complex & c)const{
    double divide=c.real*c.real+c.img*c.img;
    return Complex((real*c.real+img*c.img)/divide,(c.real*img-real*c.img)/divide);
}

// Complex Complex::operator/(const char * str) const{
//     return (*this)/Complex(str);
// }
//���Կ��� ���� �ٸ� ������ �������� �ʱ� ������ ���۷����� �����Ѵ�.
Complex& Complex::operator=(const Complex & c){
    real=c.real;
    img=c.img;
    return *this;
}

Complex& Complex::operator+=(const Complex & c){
    return (*this)=(*this)+c;
}
Complex& Complex::operator-=(const Complex & c){
    return (*this)=(*this)-c;
}
Complex& Complex::operator/=(const Complex &c){
    return (*this)=(*this)/c;
}
Complex& Complex::operator*=(const Complex & c){
    return (*this)=(*this)*c;
}

int main() {
    Complex a(0, 0);
    a = a + "-1.1 + i3.923";
    a.println();
    a = a - "1.2 -i1.823";
    a.println();
    a = a * "2.3+i22";
    a.println();
    a = a / "-12+i55";
    a.println();

    return 0;
}