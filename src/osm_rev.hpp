

#ifndef OSM_REV_H
#define OSM_REV_H
#include "way.hpp"
#include "node.hpp"
#include <map>
#include <list>

using namespace std;

class Osm {
   private:
      double MinLat, MaxLat, MinLon, MaxLon;
      vector<Node> nodes;
      vector<Way> ways;
      map<long, int> index;

      
   public:
      Osm();
      Osm(const string &);
      ~Osm();

      void ParseOsmFile(const string &);
      void parseWays(const string &);
      void parseNodes(const string &);
      void parseBounds(const string &);

      //Getters
      double GetMinLat();
      double GetMaxLat();
      double GetMinLon();
      double GetMaxLon();


      vector<Node> GetNodes();
      vector<Way> GetWays();

      //gives the int-index in "nodes" for an long-id
      map<long, int> GetIndex();





};

#endif


