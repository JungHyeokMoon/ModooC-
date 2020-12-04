#include <iostream>
#include <string.h>

class PhotoCannon{
    int hp,shield;
    int coordi_x, coordi_y;
    int damage;
    
    char * name;

    public:
        PhotoCannon(int x, int y);
        PhotoCannon(int x, int y,const char * cannon_name);
        PhotoCannon(const PhotoCannon & pc);
        ~PhotoCannon();
        void Show_Status();
};

PhotoCannon::PhotoCannon(int x, int y){
    hp=shield=100;
    coordi_x=x;
    coordi_y=y;
    damage=50;
    name=NULL;
}
PhotoCannon::~PhotoCannon(){
    if(name)delete[]name;
}
PhotoCannon::PhotoCannon(int x, int y, const char * cannon_name){
    hp=shield=100;
    coordi_x=x;
    coordi_y=y;
    damage=50;
    name=new char[strlen(cannon_name)+1];
    strcpy(name,cannon_name);
}

PhotoCannon::PhotoCannon(const PhotoCannon & pc){
    std::cout << "복사 생성자 호출! " << std::endl;
    hp=pc.hp;
    shield=pc.shield;
    coordi_x=pc.coordi_x;
    coordi_y=pc.coordi_y;
    damage=pc.damage;

    name=new char[strlen(pc.name)+1];
    strcpy(name,pc.name);
}
void PhotoCannon::Show_Status(){
     std::cout << "Photon Cannon :: " << name << std::endl;
    std::cout << " Location : ( " << coordi_x << " , " << coordi_y << " ) "
                << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

int main(){
    PhotoCannon pc1(3,3,"Cannon");
    PhotoCannon pc2=pc1;

    pc1.Show_Status();
    pc2.Show_Status();

    return 0;
}