#ifndef TARGET_H
#define TARGET_H
#include <vector>
#include <QPair>
#include <QtMath>
class target
{
public:
    target(int a);
    target() {
        Radius_ = 0;
    }
    void generatePas();
    void setR(int aR);
    int getR() const {
        return Radius_;
    }
    int getHits() const;
    void ClearAmount() {
        amount_ =0 ;
    }
    int getShoots() const;
    bool shoot(int x , int y);
    std::vector<QPair<double,double>> points_;
    std::vector<QPair<int,int>> hitsCoor_;
private:
    double Radius_;
    int amount_ = 0;
};

#endif // TARGET_H
