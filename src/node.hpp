#ifndef NODE_H
#define NODE_H
#include "point2d.hpp"

class Node : public Point2D
{
   public:
      Node();
      Node(double x, double y, long val);
      long GetID();
      void SetID(long x);

   private:
      long id;

};

#endif