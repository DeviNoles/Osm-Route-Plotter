
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "way.hpp"

Way::Way(){
   HwyType = false; 
   ids.clear();
}

Way::Way(bool value, vector<long>& vec){
   HwyType = value; 
   ids.clear();
   for(auto itr = vec.begin(); itr!=vec.end(); itr++)
      ids.push_back(*itr);
}
      
bool Way::GetType() {
   return HwyType;
}

vector<long> Way::GetIds() {
   return ids;
}

void Way::SetType(bool b) {
   HwyType = b;
}

void Way::SetIds(vector<long> vec) {
   ids = vec;
}



