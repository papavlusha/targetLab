#include "target.h"
#include <QPainter>
#include <algorithm>

target::target(int a) {
  setR(a);
}
void target::setR(int aR) {
    Radius_ = aR;
}

bool target::shoot(int x , int y) {
    amount_++;
    if ((x <= 0) && (y <= 0) && (x*x+y*y <= Radius_*Radius_)) {
        hitsCoor_.push_back(QPair<int,int>(x,y));
        return true;
    }
    if((x >= 0) && (y >= 0) && (x*x+y*y <= Radius_*Radius_) && ((y/Radius_)*5 >= (((x/Radius_)*5-1))*((x/Radius_)*5-1))) {
        hitsCoor_.push_back(QPair<int,int>(x,y));
        return true;
    }
    return false;
}

int target::getHits() const {
    return hitsCoor_.size();
}

int target::getShoots() const {
    return amount_;
}

void target::generatePas() {
    points_.clear();
    double x;
    double y = 0;
    double step = 0.025;
        points_.push_back(QPair<double,double>(0,Radius_));
    for (x = 0; x * x + y * y <= (5) * (5) ; x += step) { //генерирую параболу так , чтобы при любом R>0 мишень выглядила одинаково
        y = (x-1)*(x-1);
        if( x * x + y * y > (5) * (5)) {
            y = sqrt(25 - x*x) + step;
        }
        points_.push_back(QPair<double,double>(Radius_/5*x,Radius_/5*y));//тогда имеем мишень относительно R=5 как и нарисованно в варианте
    }
    for (double x = points_[points_.size()-1].first/Radius_*5 ; x >=0;x-=0.05) {
        if(x<0) {
              points_.push_back(QPair<double,double>(0,Radius_));
        }
        y = sqrt(25-x*x);
        points_.push_back(QPair<double,double>(Radius_/5*x,Radius_/5*y));
    }
}
