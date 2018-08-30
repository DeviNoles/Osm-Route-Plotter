//HPP Given to Students
//Students must make CPP file; Part of ABET

#ifndef POINT2D_H
#define POINT2D_H

class Point2D 
{
	public:
    	Point2D();
    	Point2D(double, double);
    	double GetLat();
    	double GetLon();
    	void SetLat(double x);
    	void SetLon(double x);
	private:
    	double lat;
    	double lon;
};

#endif