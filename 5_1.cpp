#include <iostream>
#include <cstring>
#include <cstdlib>
class Complex{
    double real,img;
    //내부적으로만 사용되고 밖에서는 사용할 필요없는 함수
    int find_i(const char * str,int end) const;
    double get_numbers(const char * str, int from, int to) const;
    public:
        Complex(double real, double img):real(real),img(img){}
        Complex(const Complex & c){real=c.real; img=c.img;}
        Complex(const char * str);
        //사칙 연산의 경우 반드시 값을 리턴
        //Complex a = b + c + b;
        //아마도 위 문장을 쓴 사람 입장에서는 결과적으로 a = 2 * b + c; 를 의도하였을 것입니다.

        // 하지만, 실제로 처리되는 것을 보자면, (b.plus(c)).plus(b) 가 되는데, b.plus(c) 를 하면서 b 에는 (b + c) 가 들어가고, 
        //거기에 다시 plus(b) 를 하게 된다면 값 자체만 보자면 (b + c) + (b + c) 가 되서 (왜냐하면 현재 b 에는 b + c 가 들어가 있으니까) a = 2 * b + 2 * c 가 되기 때문입니다. 
        //이러한 문제를 막기 위해서는 반드시 사칙 연산의 경우 반드시 값을 리턴해야 만 합니다.
        Complex operator+(const Complex& c) const;
        //(부호) (실수부) (부호) i (허수부)
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
        return ; //원래 생성자는 return을 사용하지 않지만, 그 뒤에 코드를진행시키지 않기 위해 사용할 수 도 있다.
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
    strncpy(temp,str+from, to-from+1); //str+from은 str로부터 from 떨어진곳부터 복사를 하기 위해서 
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

//     // //i의 인덱스찾기
//     // int pos_i=find_i(str,end);

//     // //실수부만 존재할경우
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
//대입연산 이후 다른 연산을 수행하지 않기 때문에 레퍼런스를 리턴한다.
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