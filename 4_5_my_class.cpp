#include <iostream>
#include <algorithm>
#include <vector>
class MyString{
    char * string_content;
    int string_length;
    int memory_capacity;

    public:
        MyString(char c);
        MyString(const char * source);
        MyString(const MyString& source);
        ~MyString();

        int length() const;
        int capacity() const;

        //string.h의 strlen 를 만든 것
        int strlen(const char * source);

        void print() const ;
        void println() const;
        void reserve(int size);
        MyString & assign(const char * source);
        MyString & assign(const MyString & source);
        
        char at(int i) const;

        MyString & insert(int loc, const MyString & source);
        MyString & insert(int loc, const char * str);
        MyString & insert(int loc, char c);

        MyString & erase(int loc, int num);
        
        int find(int find_from, const MyString & source) const;
        int find(int find_from, const char * source) const;
        int find(int find_from, char c) const;
        
        int compare(const MyString& source);
        int compare(const char * source);
        int compare(char c);
};
int MyString::compare(const MyString & source){
    
    int compare_length=std::min(string_length,source.string_length);
    for(int i=0; i<compare_length; i++){
        if(string_content[i]>source.string_content[i])return 1;
        else if(string_content[i]<source.string_content[i])return -1;
    }

    //반복문을 다 돌았는데 return이 안됐고 길이가 같은경우 비교의결과는 같음
    if(string_length==source.string_length)return 0;
    
    //문자열 abc, abcd가 있다면 abcd가 더 큰 것
    return string_length<source.string_length ? -1: 1;
    return 0;
}
int MyString::compare(const char * source){
    MyString temp(source);
    return compare(temp);
}
int MyString::compare(char c){
    MyString temp(c);
    return compare(temp);
}
//우선 0번 인덱스부터 매칭하는거 있는지 찾기
int MyString::find(int find_from, const MyString & source) const{
    if(find_from>=string_length) return -1;
    int source_length=source.string_length;

    //실패함수만들기
    int * failure=new int[source_length];
    for(int i=0; i<source_length; i++){
        failure[i]=0;
    }

    int j=0;
    for(int i=1; i<source_length; i++){
        while(j>0 && source.string_content[i]!=source.string_content[j])j=failure[j-1];
        if(source.string_content[i]==source.string_content[j])failure[i]=++j;
    }
    
    j=0;
    for(int i=find_from; i<string_length; i++){
        while(j>0 && string_content[i]!=source.string_content[j])j=failure[j-1];
        if(string_content[i]==source.string_content[j])
            j++;
        
        if(j==source_length){
            delete []failure;
            return i-source_length+1;
        }
    }
    //못찾았을경우
    return -1;
}
int MyString::find(int find_from, const char * source) const{
    MyString temp(source);
    return find(find_from,temp);
}
int MyString::find(int find_from, char c) const{
    MyString temp(c);
    return find(find_from,temp);
}
MyString & MyString::erase(int loc, int num){
    if(loc<0 || loc>string_length || num<0)return * this;
    if(loc+num>string_length){
        string_length=loc;
        return *this;
    }
    for(int i=loc+num; i<string_length; i++)
        string_content[i-num]=string_content[i];
    string_length-=num;
    return *this;
}
MyString & MyString::insert(int loc, const MyString & source){
    if(loc<0 || loc>source.string_length)return * this;
    if(loc+source.string_length>memory_capacity){
        //새롭게 동적할당
        //빈번한 동적할당을 막기 위해서
        if(memory_capacity*2>string_length+source.string_length)
            memory_capacity*=2;
        else
            memory_capacity=string_length+source.string_length;

        char * prev_string_content=string_content;
        string_content=new char[memory_capacity];
        int i=0;
        for(i=0; i<loc; i++)
            string_content[i]=prev_string_content[i];
        
        for(int j=0; j!=source.string_length; j++)
            string_content[i+j]=source.string_content[j];
        
        for(; i<string_length; i++)
            string_content[i+source.string_length]=prev_string_content[i];

        delete[]prev_string_content;
        string_length=string_length+source.string_length;
        return *this;
    }

    //초과하지 않는경우 그냥 뒤로 밀어주고 삽입하면된다.
    for(int i=string_length-1; i>=loc ; i--)
        string_content[i+source.string_length]=string_content[i];
    
    for(int i=0; i<source.string_length; i++)
        string_content[loc+i]=source.string_content[i];

    string_length=string_length+source.string_length;
    return *this;
}
//기존에 있던 함수 활용
MyString & MyString::insert(int loc, const char * source){
    MyString temp(source);
    return insert(loc,temp);
}
MyString & MyString::insert(int loc, char c){
    MyString temp(c);
    return insert(loc,temp);
}
//할당할 문자열의 크기를 미리 예약해두는 함수
void MyString::reserve(int size){
    if(size>memory_capacity){
        //가르키게 하고
        char * prev_string_content=string_content;
        //새로할당받아서
        string_content=new char[size];
        memory_capacity=size;
        //옮긴다.
        for(int i=0; i!=string_length; i++)
            string_content[i]=prev_string_content[i];

        
        //이전 string_content를 delete
        delete[] prev_string_content;
    }
}
//인덱스 위치에 있는 글자 return 
char MyString::at(int i) const{
    if(i<0 || i>=string_length)return 0;
    return string_content[i];
}
//memory_capacity 반환
int MyString::capacity()const {return memory_capacity;}

MyString& MyString::assign(const char * source){
    MyString temp(source);
    return assign(temp);
    // int source_length=strlen(source);
    // if(source_length>memory_capacity){
    //     delete[] string_content;
    //     string_content=new char[source_length];
    //     memory_capacity=source_length;
    // }
    // for(int i=0; i!=source_length; i++)
    //     string_content[i]=source[i];
    // string_length=source_length;
    // return * this;
}

MyString& MyString::assign(const MyString & source){
    if(source.string_length>memory_capacity){
        delete[] string_content;
        string_content=new char[source.string_length];
        memory_capacity=source.string_length;
    }
    for(int i=0; i!=source.string_length; i++)
        string_content[i]=source.string_content[i];
    
    string_length=source.string_length;

    return * this;
}
MyString::MyString(const MyString & source){
    string_length=source.string_length;
    memory_capacity=string_length;
    string_content=new char[string_length];
    for(int i=0; i!=string_length ;i++)
        string_content[i]=source.string_content[i];
}
MyString::MyString(char c){
    string_length=1;
    string_content=new char[string_length];
    string_content[0]=c;
    memory_capacity=1;
}
int MyString::length() const{
    return string_length;
}
int MyString::strlen(const char * source){
    int len=0;
    while(source[len]){
        len++;
    }
    return len;
}
MyString::MyString(const char * source){
    string_length=strlen(source);
    string_content=new char[string_length];
    memory_capacity=string_length;
    for(int i=0; i!=string_length; i++)
        string_content[i]=source[i];
}
void MyString::print() const{
    for(int i=0; i!=string_length; i++)
        std::cout<<string_content[i];
}
void MyString::println() const{
    print();
    std::cout<<std::endl;
}
MyString::~MyString(){
    print();
    std::cout<<"의 소멸자 호출"<<std::endl;
    if(string_content)delete[] string_content;
}
int main() {
    MyString s1("asdfg");
    std::cout<<"찾은 인덱스: "<<s1.find(1,'f')<<std::endl;

    return 0;
}