#include <iostream>
#include <string.h>

class PhotonCannon{
    int hp, shield;
    int coord_x, coord_y;
    int damage;

    public:
        PhotonCannon(int x, int y);
        PhotonCannon(const PhotonCannon& pc);

        void Show_Status();
};
PhotonCannon::PhotonCannon(int x, int y){
    std::cout<<"생성자 호출!"<<std::endl;
    hp=shield=100;
    coord_x=x;
    coord_y=y;
    damage=20;
}
PhotonCannon::PhotonCannon(const PhotonCannon& pc){
    std::cout<<"복사 생성자 호출!"<<std::endl;
    hp=pc.hp;
    shield=pc.shield;
    coord_x=pc.coord_x;
    coord_y=pc.coord_y;
    damage=pc.damage;
}

void PhotonCannon::Show_Status(){
    std::cout << "Photon Cannon " << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
                << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

int main(){
    PhotonCannon pc1(3,3);
    PhotonCannon pc2(pc1);
    //복사생성자 호출 바로 윗문장과 동일하게 작동한다. 복사생성자호출
    PhotonCannon pc3=pc2;

    //PhotonCannon pc3;
    //pc3=pc2; 이문장은 바로윗문장과는 다른문장
    //대입연산자가 실행됨

    pc1.Show_Status();
    pc2.Show_Status();

    return 0;

}