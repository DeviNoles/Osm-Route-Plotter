
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h> 
#include <algorithm> 
#include <utility>  //pair
#include <list>

#include "way.hpp"
#include "point2d.hpp"
#include "node.hpp"
#include "matrix_rev.hpp"
#include "osm_rev.hpp"

using namespace std;

void PixelPrint(Matrix& pgm, int Xpixel, int Ypixel, int val);
void draw_line(Matrix& pgm, float x0, float y0, const float& x1, const float& y1, int color);
void PrintPath(Osm& data, Matrix& pgm, Node& begin, Node& end, double length_unit, double width_unit, list<long>*& adj);

int main(int argc, const char * argv[]) {

    string filename;
    
    long hqID, dropID, pickID;

    cin >> filename;
    cin >> hqID;
    cin >> pickID;
    cin >> dropID;

    string input = "osm/" + filename;
    Osm data(input);
    vector<Node> nodes = data.GetNodes();
    map<long, int> index = data.GetIndex();

    Node hq( nodes[index[hqID]].GetLat() , nodes[index[hqID]].GetLon() , hqID);
    Node pickup( nodes[index[pickID]].GetLat() , nodes[index[pickID]].GetLon() , pickID);
    Node dropoff( nodes[index[dropID]].GetLat() , nodes[index[dropID]].GetLon() , dropID);

	
	/////////////////////////////////////////////////////
	//CONSTRUCT A BLANK PGM OF THE CORRECT SIZE
    /////////////////////////////////////////////////////
	double raw_length = data.GetMaxLat()-data.GetMinLat();
	double raw_width = data.GetMaxLon()-data.GetMinLon();
	double length = raw_length, width = raw_width;

	if (length*10 <= 5000 && width*10 <= 5000)
		do{
			length*=10; width*=10;
		}while (length*10 <= 5000 && width*10 <= 5000);
	length = (int) length; 
	width = (int) width;
	Matrix pgm = Matrix(length, width);
	

    /////////////////////////////////////////////////////
    //DrawHighways(const Way& way)
    /////////////////////////////////////////////////////
    double length_unit = raw_length/length;
	double width_unit = raw_width/width;
    double current_lat, current_lon;
    double Xpixel=0, Ypixel=0;
    double prev_Xpixel=0, prev_Ypixel=0;

    //Iterate through all ways
    vector<Way> ways = data.GetWays();
    for (auto WaysItr = ways.begin(); WaysItr!=ways.end(); WaysItr++){

        //Select only the ways which are highways
    	if (WaysItr->GetType()==true){

    		//IDSs along the current highway
    		vector<long> ids = WaysItr->GetIds();
    		for (auto IdsItr = ids.begin(); IdsItr!=ids.end(); IdsItr++){

    			if (IdsItr != ids.begin()){
    				prev_Xpixel = Xpixel;
    				prev_Ypixel = Ypixel;
    			}

                //Find the node corresponding to the id and print the pixel
                vector<Node> nodes = data.GetNodes();
                current_lat = nodes[index[*IdsItr]].GetLat();
                current_lon = nodes[index[*IdsItr]].GetLon();
                Xpixel = ((data.GetMaxLat()-current_lat)/length_unit);
                Ypixel = ((current_lon-data.GetMinLon())/width_unit);
                PixelPrint(pgm, (int) Xpixel, (int) Ypixel, 150);

                //Draw node connections
                if (IdsItr != ids.begin()){
                    draw_line(pgm, Xpixel, Ypixel, prev_Xpixel, prev_Ypixel, 150); 
                }

    		}

    	}

    }
  
    /////////////////////////////////////////////////////
    //Print 3 Specific Larger Nodes - hq, pickup, dropoff
    /////////////////////////////////////////////////////
    //Print LARGE HQ Node
    Xpixel = (int) ((data.GetMaxLat()-hq.GetLat())/length_unit);
    Ypixel = (int) ((hq.GetLon()-data.GetMinLon())/width_unit);
    PixelPrint(pgm, Xpixel, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+2, 50);

    //Print LARGE Pickup Node
    Xpixel = (int) ((data.GetMaxLat()-pickup.GetLat())/length_unit);
    Ypixel = (int) ((pickup.GetLon()-data.GetMinLon())/width_unit);
    PixelPrint(pgm, Xpixel, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+2, 50);

    //Print LARGE Dropoff Node
    Xpixel = (int) ((data.GetMaxLat()-dropoff.GetLat())/length_unit);
    Ypixel = (int) ((dropoff.GetLon()-data.GetMinLon())/width_unit);
    PixelPrint(pgm, Xpixel, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+1, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+1, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel, 50);
    PixelPrint(pgm, Xpixel, Ypixel+2, 50);
    PixelPrint(pgm, Xpixel+2, Ypixel+2, 50);


    /////////////////////////////////////////////////////
    //Make Adjacency List
    /////////////////////////////////////////////////////
    int nSize = nodes.size();

    list<long>* adj = new list<long>[nSize];;
    for (int i=0; i< nSize; i++)
        adj[i].clear();

    for (auto itr = ways.begin(); itr!=ways.end(); itr++){
        if (itr->GetType()==true){
            vector<long> idsVec = itr->GetIds();
            for(int i= 0; i< idsVec.size(); i++){
                if (i+1<idsVec.size()){
                    adj[index[idsVec[i]]].push_back(idsVec[i+1]);
                    adj[index[idsVec[i+1]]].push_back(idsVec[i]);
                }
            }
        }
    }


    /////////////////////////////////////////////////////
    //Print Routes
    /////////////////////////////////////////////////////
    string outputfile = "images/map.pgm";
    PrintPath(data, pgm, hq, pickup, length_unit, width_unit, adj);
    PrintPath(data, pgm, pickup, dropoff, length_unit, width_unit, adj);
    PrintPath(data, pgm, dropoff, hq, length_unit, width_unit, adj);
    pgm.Save(outputfile);


	return 0;
}


void PrintPath(Osm& data, Matrix& pgm, Node& begin, Node& end, double length_unit, double width_unit, list<long>*& adj){
    /* COMPLETE PATH FINDING ALGORITHM */
}


void PixelPrint(Matrix& pgm, int Xpixel, int Ypixel, int val){
    //Print Pixel
    pgm(Xpixel+1, Ypixel+1) = val;
  
    //Print Surrounding Pixels for Greater Clarity
    //Top Row
    if (Xpixel>=1 && Ypixel>=1)
        pgm(Xpixel, Ypixel) = val;
    if (Xpixel>=1)
        pgm(Xpixel, Ypixel+1) = val;
    if (Xpixel>=1 && Ypixel+2<=pgm.NumColumns())
        pgm(Xpixel, Ypixel+2) = val;

    //Middle Row
    if (Ypixel>=1)
        pgm(Xpixel+1, Ypixel) = val;
    if (Ypixel+2<=pgm.NumColumns())
        pgm(Xpixel+1, Ypixel+2) = val;

    //Bottom Row
    if (Xpixel+2<=pgm.NumRows() && Ypixel>=1)
        pgm(Xpixel+2, Ypixel) = val;
    if (Xpixel+2<=pgm.NumRows())
        pgm(Xpixel+2, Ypixel+1) = val;
    if (Xpixel+2<=pgm.NumRows() && Ypixel+2<=pgm.NumColumns())
        pgm(Xpixel+2, Ypixel+2) = val;

}

void draw_line(Matrix& pgm, float x0, float y0, const float& x1, const float& y1, int color)
{
    float x{x1 - x0}, y{y1 - y0};
    const float max{std::max(fabs(x), fabs(y))};
    x /= max; y /= max;
    for (float n{0}; n < max; ++n)
    {
        // draw pixel at ( x0, y0 )
        x0 += x; y0 += y;
        pgm(x0+1, y0+1) = color;
    }
}






