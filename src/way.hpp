
#ifndef WAY_H
#define WAY_H

#include <vector>

using namespace std;

class Way
{
   public:
      Way();
      Way(bool, vector<long>&);

      bool GetType();
      vector<long> GetIds();
      
      void SetType(bool b);
      void SetIds(vector<long> vec);

   private:
      vector<long> ids;
      bool HwyType;
      //If HwyType is true, it must be drawn

};

#endif