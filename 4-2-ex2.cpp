#include <iostream>
#include <cmath>
class Point{
    
    public:
        // Point()=default;
        int x,y;
        Point(){
            x=0;
            y=0;
        }
        Point(int _x, int _y){
            x=_x;
            y=_y;
            std::cout<<"��ǥ�� "<<x<<", "<<y<<"�Դϴ�. "<<std::endl;
        }
        
};
class Geometry{
    // �� 100���� �����ϴ� �迭
    Point* pointArray[100];
    int pointCount=0;
    public:
        // Geometry()=default;
        Geometry(Point **pointList,int length){
            for(int i=0; i<length; i++){
                pointArray[i]=pointList[i];
                pointCount++;
            }
        }
        Geometry(){

        }
        //
        void AddPoint(const Point &point){
            pointArray[pointCount++]=new Point(point);
            std::cout<<"�߰��� ���� ��ǥ"<<point.x<<", "<<point.y<<"�Դϴ�."<<std::endl;
        }
        // ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
        void PrintDistance(){
            for(int i=0; i<pointCount; i++){
                int hx=pointArray[i]->x;
                int hy=pointArray[i]->y;
                std::cout<<i<<"��° ���� ��ǥ"<<hx<<", "<<hy<<": ";
                for(int j=0; j<pointCount; j++){
                    if(i==j)continue;
                    int tx=pointArray[j]->x;
                    int ty=pointArray[j]->y;
                    double d=sqrt(pow(hx-tx,2)+pow(hy-ty,2));
                    std::cout<<"("<<tx<<", "<<ty<<") ���� �Ÿ�"<<d<<" ,";
                }
                std::cout<<std::endl;
            }
        }
        // ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
        // ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
        // �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
        // ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
        void PrintNumMeets(){
            
        }
};

int main(){
    Point * array[10];
    array[0]=new Point(1,7);
    array[1]=new Point(1,8);
    array[2]=new Point(45,23);
    array[3]=new Point(2,8);
    array[4]=new Point(81,6);
    array[5]=new Point(15,38);
    array[6]=new Point(16,3);
    array[7]=new Point(4,2);
    array[8]=new Point(17,27);
    array[9]=new Point(10,10);

    Geometry g(array,10);
    g.PrintDistance();

    Point p(-1,-1);
    g.AddPoint(p);
    for(int i=0; i<10; i++)
        delete array[i];

    //delete�ϰ� ���� ��������� �Ÿ��� ����� �ϸ� ������ ���� �����°��� �� �� �ִ�.
    // g.PrintDistance();
    return 0;
}