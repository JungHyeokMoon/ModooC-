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
    std::cout<<"������ ȣ��!"<<std::endl;
    hp=shield=100;
    coord_x=x;
    coord_y=y;
    damage=20;
}
PhotonCannon::PhotonCannon(const PhotonCannon& pc){
    std::cout<<"���� ������ ȣ��!"<<std::endl;
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
    //��������� ȣ�� �ٷ� ������� �����ϰ� �۵��Ѵ�. ���������ȣ��
    PhotonCannon pc3=pc2;

    //PhotonCannon pc3;
    //pc3=pc2; �̹����� �ٷ���������� �ٸ�����
    //���Կ����ڰ� �����

    pc1.Show_Status();
    pc2.Show_Status();

    return 0;

}