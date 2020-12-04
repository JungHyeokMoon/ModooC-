#include <iostream>

class string{
    char * str;
    int len;

    public:
        string(char c, int n);
        string(const char *s);
        string(const string &s); //복사생성자
        ~string();

        void Add_String(const string & s);
        void copy_string(const string &s);
        int strlen();
        int strlen(const char * s);
        void print_string();
};
void string::print_string(){
    for(int i=0; i<len; i++)
        std::cout<<str[i];
    // std::cout<<std::endl;
}
int string::strlen(const char * s){
    int sLen=0;
    while(s[sLen]){
        sLen++;
    }
    return sLen;
}
string::string(char c, int n){
    len=n;
    str=new char[len+1];
    for(int i=0; i<len; i++)
        str[i]=c;
    str[len]='\0';
}
string::string(const string &s){
    len=s.len;
    str=new char[len+1];
    for(int i=0; i<len; i++){
        str[i]=s.str[i];
    }
    str[len]='\0';
}
int string::strlen(){
    return len;
}
string::string(const char * s){
    int sLen=strlen(s);
    std::cout<<"매개변수 s의 길이"<<sLen<<std::endl;
    len=sLen;
    str=new char[len+1];
    for(int i=0; i<len; i++){
        str[i]=s[i];
    }
    str[len]='\0';
}

string::~string(){
    print_string();
    std::cout<<"의 소멸자 호출!"<<std::endl;
    if(str)delete[] str;
}
void string::Add_String(const string & s){
    int newLen=len+s.len;
    std::cout<<"새로 만들어질 문자열의 길이"<<newLen<<std::endl;
    char * temp=new char[newLen+1];
    int idx=0;
    for(int i=0; i<len; i++)
        temp[idx++]=str[i];
    for(int i=0; i<s.len; i++)
        temp[idx++]=s.str[i];
    temp[idx]='\0';

    std::cout<<"새로 만들어진 문자열 :";
    for(int i=0; i<newLen; i++)
        std::cout<<temp[i];
    std::cout<<std::endl;
    delete[] str;
    str=temp;

    len=newLen;

}
void string::copy_string(const string &s){
    len=s.len;
    char * temp=new char[len+1];
    int idx;
    for( idx=0; idx<len; idx++)
        temp[idx]=s.str[idx];
    temp[idx]='\0';

    delete[] str;
    str=temp;
}

int main(){
    string s('c',4);
    string s2=s;
    string s3('a',3);
    string s4("abcd");
    s3.copy_string(s2);
    s4.Add_String("def");
    // s.Add_String("abc");

    return 0;
}