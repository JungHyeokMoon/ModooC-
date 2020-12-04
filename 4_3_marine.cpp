#include <iostream>
#include <string.h>
class Marine{
    static int total_marine_num;
    int hp;
    int coordi_x, coordi_y;
    bool is_dead;
    char * name;
    const int default_damage;
    public:
        Marine();
        Marine(int x, int y);
        Marine(int x, int y, const char * marine_name);
        Marine(int x, int y, int default_damage);
        ~Marine(); //char * name�� �Ҹ��� ȣ���ϱ� ���ؼ� �ۼ�
        int Attack() const; //��� ����Լ� => �ٸ������� ���� �ٲ��� �ʴ� �Լ������� �� �ִ�. �б⸸ ����. ����Լ������� �Լ�ȣ���� ����Լ��� ȣ���� �����ϴ�.
        Marine& Be_Attacked(int damage_earn);
        void Show_Status();
        void Move(int x, int y);
        static void Show_Total_Marine();
};
int Marine::total_marine_num=0;
void Marine::Show_Total_Marine(){
    std::cout<<"��ü ���� �� : "<<total_marine_num<<std::endl;
}
Marine::~Marine(){
    std::cout<<name<<"�� �Ҹ��� ȣ��!"<<std::endl;
    total_marine_num--;
    if(name!=NULL)
        delete[] name;
}
Marine::Marine():hp(50),coordi_x(0),coordi_y(0),is_dead(false),default_damage(5),name(NULL){total_marine_num++;}

Marine::Marine(int x, int y):hp(50),coordi_x(x),coordi_y(y),is_dead(false),default_damage(5),name(NULL){total_marine_num++;}
Marine::Marine(int x, int y, int default_damage): hp(50), coordi_x(x),coordi_y(y),default_damage(default_damage),is_dead(false),name(NULL){total_marine_num++;}
Marine::Marine(int x, int y, const char * marine_name):hp(50),coordi_x(x),coordi_y(y),default_damage(5),is_dead(false){
    total_marine_num++;
    name=new char[strlen(marine_name)+1];
    strcpy(name,marine_name);
}
void Marine::Move(int x, int y){
    coordi_x=x;
    coordi_y=y;
}
int Marine::Attack() const{
    return default_damage;
}
Marine& Marine::Be_Attacked(int damage_earn){
    hp-=damage_earn;
    if(hp<=0)is_dead=true;

    return *this;
}
void Marine::Show_Status(){
    std::cout << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << coordi_x << " , " << coordi_y << " ) "
                << std::endl;
    std::cout << " HP : " << hp << std::endl;
    std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;
}

int main(){
    // Marine marine1(2,3);
    // Marine marine2(3,5);

    // marine1.Show_Status();
    // marine2.Show_Status();

    // std::cout<<std::endl<<"???? 1?? ????2?? ????"<<std::endl;
    // marine2.Be_Attacked(marine1.Attack());

    // marine1.Show_Status();
    // marine2.Show_Status();
    Marine * marines[100];
    marines[0]=new Marine(2,3,"Marine 2");
    marines[1]=new Marine(3,5,"Marine 1");

    marines[0]->Show_Status();
    marines[1]->Show_Status();
    std::cout<<std::endl<<"����1�� ����2�� �����մϴ�."<<std::endl;
    marines[1]->Be_Attacked(marines[0]->Attack()).Be_Attacked(marines[0]->Attack());

    marines[0]->Show_Status();
    marines[1]->Show_Status();

    delete marines[0];
    delete marines[1];
    return 0;
}