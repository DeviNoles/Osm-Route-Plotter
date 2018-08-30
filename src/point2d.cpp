
//HPP Given to Students
//Students must make CPP file; Part of ABET

#include <iostream>
#include "point2d.hpp"

Point2D::Point2D(){
	lat = 0;
	lon = 0;

}

Point2D::Point2D(double lt, double lo){
	lat =lt;
	lon = lo;
}

double Point2D::GetLat(){
    return lat;
}

double Point2D::GetLon(){
    return lon;
}

void Point2D::SetLat(double x){
	lat=x;
}

void Point2D::SetLon(double x){
	lon=x;
}


