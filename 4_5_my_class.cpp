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

        //string.h�� strlen �� ���� ��
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

    //�ݺ����� �� ���Ҵµ� return�� �ȵư� ���̰� ������� ���ǰ���� ����
    if(string_length==source.string_length)return 0;
    
    //���ڿ� abc, abcd�� �ִٸ� abcd�� �� ū ��
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
//�켱 0�� �ε������� ��Ī�ϴ°� �ִ��� ã��
int MyString::find(int find_from, const MyString & source) const{
    if(find_from>=string_length) return -1;
    int source_length=source.string_length;

    //�����Լ������
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
    //��ã�������
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
        //���Ӱ� �����Ҵ�
        //����� �����Ҵ��� ���� ���ؼ�
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

    //�ʰ����� �ʴ°�� �׳� �ڷ� �о��ְ� �����ϸ�ȴ�.
    for(int i=string_length-1; i>=loc ; i--)
        string_content[i+source.string_length]=string_content[i];
    
    for(int i=0; i<source.string_length; i++)
        string_content[loc+i]=source.string_content[i];

    string_length=string_length+source.string_length;
    return *this;
}
//������ �ִ� �Լ� Ȱ��
MyString & MyString::insert(int loc, const char * source){
    MyString temp(source);
    return insert(loc,temp);
}
MyString & MyString::insert(int loc, char c){
    MyString temp(c);
    return insert(loc,temp);
}
//�Ҵ��� ���ڿ��� ũ�⸦ �̸� �����صδ� �Լ�
void MyString::reserve(int size){
    if(size>memory_capacity){
        //����Ű�� �ϰ�
        char * prev_string_content=string_content;
        //�����Ҵ�޾Ƽ�
        string_content=new char[size];
        memory_capacity=size;
        //�ű��.
        for(int i=0; i!=string_length; i++)
            string_content[i]=prev_string_content[i];

        
        //���� string_content�� delete
        delete[] prev_string_content;
    }
}
//�ε��� ��ġ�� �ִ� ���� return 
char MyString::at(int i) const{
    if(i<0 || i>=string_length)return 0;
    return string_content[i];
}
//memory_capacity ��ȯ
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
    std::cout<<"�� �Ҹ��� ȣ��"<<std::endl;
    if(string_content)delete[] string_content;
}
int main() {
    MyString s1("asdfg");
    std::cout<<"ã�� �ε���: "<<s1.find(1,'f')<<std::endl;

    return 0;
}