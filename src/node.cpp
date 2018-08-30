
#include <iostream>
#include "node.hpp"
//#include "point2d.hpp"


Node::Node():Point2D(){
	id = 0;
}

Node::Node(double x, double y, long val):Point2D(x, y){
	id = val;
}

long Node::GetID() {
	return id;
}

void Node::SetID(long x){
	id = x;
}

