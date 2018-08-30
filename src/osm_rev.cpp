#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm> 
#include <map>
#include "osm_rev.hpp"

using namespace std;

Osm::Osm(){
  MinLat=0, MaxLat=0, MinLon=0, MaxLon=0;
  nodes.clear();
  ways.clear();
  index.clear();
}

Osm::Osm(const string & s){
  ParseOsmFile(s);
}

Osm::~Osm(){
}

void Osm::ParseOsmFile(const string & s){
  parseBounds(s);
  parseWays(s);
	parseNodes(s);
}

void Osm::parseWays(const string & s){

  ifstream infile(s);
  string line; 
  bool isWay = false;
  Way newWay;
  vector<long> newids;
  ways.clear();

  if(infile.is_open()){

    while(getline(infile, line)){
      if(line.find("<way ") != string::npos){
        isWay = true;
        newWay.SetType(false);
        newids.clear();
        newWay.SetIds(newids);
      }
      if(line.find("</way>") != string::npos){
        isWay = false;
        newWay.SetIds(newids);
        ways.push_back(newWay);

      }

      if(isWay){
        int begin = line.find("<nd ref=\"");
        if(begin != string::npos){
          int end = line.find("\"/");
          string id = line.substr(begin+9, end-begin-9);
          newids.push_back(stol(id));
        }
        if(line.find("<tag k=\"highway\"") != string::npos){
          newWay.SetType(true);
        }
      }

    }//endwhile
  }//endif
  infile.close();
}

void Osm::parseNodes(const string & s){

  ifstream infile(s);
  string line, sub; 
  Node newNode;
  bool isNode = false;

  //temporary set of ALL nodes
  vector<Node> nodes2;
  nodes2.clear();


  if(infile.is_open()){
    while(getline(infile, line)){

      sub = "<node";
      if(line.find(sub) != string::npos){
        isNode=true;
      }

      int begin = line.find(" id=\"");
      if(isNode==true && begin != string::npos){
        int end = line.find("\" lat=\"");
        string id = line.substr(begin+5, end-begin-5);
        newNode.SetID(stol(id));
      } 

      begin = line.find(" lat=\"");
      if(isNode==true && begin != string::npos){
        int end = line.find("\" lon");
        string lat = line.substr(begin+6, end-begin-6);
        newNode.SetLat(stod(lat));
      } 

      begin = line.find("lon=\"");
      if(isNode==true && begin != string::npos){
        int end = line.find("\" ver");
        string lon = line.substr(begin+5, end-begin-5);
        newNode.SetLon(stod(lon));

        nodes2.push_back(newNode);
        isNode = false;
      } 
    }
  }

  //Store only those nodes which are on highways
  nodes.clear();
  index.clear();
  bool inside = false;
  int k = 0;
  for (auto itr = ways.begin(); itr!=ways.end(); itr++){
    if (itr->GetType()==true){
      vector<long> idsVec = itr->GetIds();
      for(int i= 0; i< idsVec.size(); i++)
        for (auto it = nodes2.begin(); it!=nodes2.end(); it++){
          if (it->GetID()==idsVec[i]){

            //Make sure *it is not aleady in "nodes"
            inside = false;
            for (auto it2 = nodes.begin(); it2!=nodes.end(); it2++){
              if (it2->GetID() == it->GetID()) inside = true;
            }

            //If not, push it to "nodes"
            if (inside == false){
              nodes.push_back(*it);
              index[it->GetID()]=k;
              k++;
            }
          }
        }
    }
  }
  //sort (nodes.begin(), nodes.end(), sorter); 
  infile.close();
}


void Osm::parseBounds(const string & s){
  ifstream infile(s);
  string line, sub; 
  if(infile.is_open()){
    while(getline(infile, line)){

      int begin = line.find("<bounds minlat=\"");
      if(begin != string::npos){
        int end = line.find("\" minlon=");
        string sub = line.substr(begin+16, end-begin-16);
        MinLat = stod(sub);
      }

      begin = line.find(" minlon=\"");
      if(begin != string::npos){
        int end = line.find("\" maxlat=");
        string sub = line.substr(begin+9, end-begin-9);
        MinLon = stod(sub);
      } 

      begin = line.find(" maxlat=\"");
      if(begin != string::npos){
        int end = line.find("\" maxlon=");
        string sub = line.substr(begin+9, end-begin-9);
        MaxLat = stod(sub);
      } 

      begin = line.find(" maxlon=\"");
      if(begin != string::npos){
        int end = line.find("\"/>");
        string sub = line.substr(begin+9, end-begin-9);
        MaxLon = stod(sub);
        break;
      } 
    }
  }
  infile.close();

}

//Getters
double Osm::GetMinLat(){
	return MinLat;
}

double Osm::GetMaxLat(){
	return MaxLat;
}

double Osm::GetMinLon(){
	return MinLon;
}

double Osm::GetMaxLon(){
	return MaxLon;
}

std::vector<Node> Osm::GetNodes(){
	return nodes;
}

std::vector<Way> Osm::GetWays(){
	return ways;
}

map<long, int> Osm::GetIndex(){
  return index;
}




