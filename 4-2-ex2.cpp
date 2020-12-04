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
            std::cout<<"좌표는 "<<x<<", "<<y<<"입니다. "<<std::endl;
        }
        
};
class Geometry{
    // 점 100개를 보관하는 배열
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
            std::cout<<"추가된 점의 좌표"<<point.x<<", "<<point.y<<"입니다."<<std::endl;
        }
        // 모든 점들 간의 거리를 출력하는 함수 입니다.
        void PrintDistance(){
            for(int i=0; i<pointCount; i++){
                int hx=pointArray[i]->x;
                int hy=pointArray[i]->y;
                std::cout<<i<<"번째 점의 좌표"<<hx<<", "<<hy<<": ";
                for(int j=0; j<pointCount; j++){
                    if(i==j)continue;
                    int tx=pointArray[j]->x;
                    int ty=pointArray[j]->y;
                    double d=sqrt(pow(hx-tx,2)+pow(hy-ty,2));
                    std::cout<<"("<<tx<<", "<<ty<<") 간의 거리"<<d<<" ,";
                }
                std::cout<<std::endl;
            }
        }
        // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
        // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
        // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
        // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
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

    //delete하고 나서 점들사이의 거리를 출력을 하면 쓰레기 값이 나오는것을 알 수 있다.
    // g.PrintDistance();
    return 0;
}