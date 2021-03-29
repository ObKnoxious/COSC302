#include <string.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <stack>
#include <limits>
#include <algorithm> 
class city{
	private:
		std::string name;
		std::string type;
		int zone;
		float lat;
		float lon;
		int popu;
		const static float rp =	M_PI/180;
	public:
		std::string getName(){
			return name;
		}
		std::string getType(){
			return type;
		}
		int getZone(){
			return zone;
		}
		float getLat(){
			return lat;
		}
		float getLon(){
			return lon;
		}
		float getLatRad(){
			return lat*rp;
		}
		float getLonRad(){
			return lon*rp;
		}
		int getPopu(){
			return popu;
		}

		friend std::istream & operator >> (std::istream &, city &);
		friend std::ostream & operator << (std:: ostream &, city &);
};

std::istream & operator >> (std::istream &in, city &c){
	in  >> c.zone >> c.name >> c.type >> c.lat >> c.lon >> c.popu;
	return in;
}

std::ostream & operator << (std::ostream &out, city &c){
	out << std::setw(18) << std::setfill(' ') << std::left << c.name << std::setw(12) << std::left << c.type << c.zone << std::setw(11) << std::right << c.popu << std::setw(8) << std::right << std::fixed << std::setprecision(2) <<  c.lat << std::setw(8) << std::right << std::fixed << std::setprecision(2) << c.lon << '\n';
	return out;
}


void read_cityinfo(std::string fname, std::vector<city> &v){
	std::fstream fin;
	fin.open(fname.c_str());
	city c;
	std::string l;
	while(std::getline(fin, l)){
		if(l[0] != '#'){
			std::stringstream ss(l);
			ss >> c;
			v.push_back(c);

		}
	}
	for(unsigned int i=1; i<v.size(); i++){
		if(v.at(i).getName() == v.at(i-1).getName()){
			v.erase(v.begin() + i);
		}
	}
	
}

float haversine(float a1, float o1, float a2, float o2){
	float d1 = o2-o1;
	float d2 = a2-a1;
	float f = pow(sin(d2/2.0), 2.0)+ cos(a1)*cos(a2)* pow(sin(d1/2.0), 2.0);
	f = 2.0 * asin(sqrt(f));
	f = f * 3982.0;
	f = 10.0*round(f/10.0);
	//std::cout<<f;
	return f;
}

class costtable{
	private:
		std::vector<std::vector<float> > distance_table;
		std::vector<std::vector<float> > time_table;
	public:
		costtable(){}
		costtable(std::vector<city> &);
		std::vector<std::vector<float> > getDt(){
			return distance_table;
		}
		std::vector<std::vector<float> > getTt(){
			return time_table;
		}

};

costtable::costtable(std::vector<city> &c){
	distance_table.resize(c.size());
	for(unsigned int i=0; i < distance_table.size(); i++){
		distance_table.at(i).resize(c.size());
	}
	for(unsigned int i =0; i < distance_table.size(); i++){
		for(unsigned int j=0; j < distance_table.size(); j++){
			if(i == j){
				continue;
			}
			distance_table.at(i).at(j) = haversine(c.at(i).getLatRad(), c.at(i).getLonRad(), c.at(j).getLatRad(), c.at(j).getLonRad());
		}
	}
	time_table.resize(distance_table.size());
	//std::cerr << time_table.size() << " size\n";
	for(unsigned int i=0; i < time_table.size(); i++){
		time_table.at(i).resize(distance_table.at(i).size());
	}
	for(unsigned int i=0; i < time_table.size(); i++){
		for(unsigned int j=0; j < time_table.size(); j++){
			if(i == j){
				continue;
			}
			//if(c.at(i).getZone() == c.at(j).getZone()){
				//time_table.at(i).at(j) = distance_table.at(i).at(j)/60;
			if(c.at(j).getType() == "REGIONAL" && c.at(i).getType() == "REGIONAL"){
				//std::cerr << "i " << i << "j " << j << '\n';
				time_table.at(i).at(j) = distance_table.at(i).at(j)/60;
			}else{
				//std::cerr << "i " << i << "j " << j << '\n';
				time_table.at(i).at(j) = distance_table.at(i).at(j)/570;
			}
		}
	}

}

//void create_citygraph(std::vector<city> c, costtable ct){
	//std::ofstream fout("city_graph.txt");
	//fout << "CITY GRAPH:\n";
	//for(unsigned int i =1; i< c.size(); i++){
		//fout << std::setw(3) << std::right << i-1 << " " << c.at(i).getName() << '\n';
		//for(unsigned j =1; j<i; j++){
			//fout << j << " " << c.at(j).getName() << '\n';
		//}
		//fout << '\n';
	//}
	//fout.close();
//}

void create_citygraph(std::vector<city> c, costtable ct, std::vector<std::vector<bool> > &a){
	//for(unsigned int i=0; i<a.size(); i++){
		//a.at(i).resize(a.size(), false);
	//}
	a.assign(c.size(), std::vector<bool>(c.size(), false));	
	for(unsigned int i=0; i<c.size(); i++){
		for(unsigned int j=0; j<c.size(); j++){
			if(i == j){
				continue;
			}
			if(c.at(i).getZone() == c.at(j).getZone()){
					//std::cerr << c.at(i).getName() << " type: " << c.at(i).getType()<< c.at(j).getName() << " type: " << c.at(j).getType()<< '\n';	
				if(c.at(i).getType() == c.at(j).getType()){
				//std::cerr << c.at(i).getZone() << '\n';
					//std::cerr << "Adjacent!\n\n";
					a.at(i).at(j) = true;
					a.at(j).at(i) = true;
				}//else{
					//if(c.at(i).getType() == "REGIONAL"){
						//std::vector<int> g;
						//for(unsigned int k=0; k<c.size(); k++){
							//if(c.at(k).getZone() == c.at(i).getZone() && c.at(k).getType() == "GATEWAY"){
								////std::cerr <<"Adding gateway\n";
								//g.push_back(k);
							//}
						//}
						//int gw;
						//if(g.size() == 1){
							//gw=g.at(0);
						//}else{
							//gw=g.at(0);
							//for(unsigned int l=0; l<g.size(); l++){
								//if(ct.getDt().at(i).at(l) < ct.getDt().at(i).at(gw)){
									//gw = l;
								//}
							//}
						//}
						//a.at(i).at(gw) == true;
						//a.at(gw).at(i) == true;
						
					//}
				//}
			}

		}
	}
	
	for(unsigned int i=0; i<c.size(); i++){
		if(c.at(i).getType() == "REGIONAL"){
			int gw =-1;
			int gwd=24902;
			for(unsigned int j=0; j<c.size(); j++){
				if(c.at(i).getZone() == c.at(j).getZone() && c.at(j).getType() == "GATEWAY"){
					if(ct.getDt().at(i).at(j) < gwd){
						//std::cout << "Setting gateway for " << c.at(i).getName() << "... " << c.at(j).getName() << '\n';
						gw=j;
						gwd=ct.getDt().at(i).at(j);
					}
				}
			}
			a.at(i).at(gw) = true;
			a.at(gw).at(i) = true;
		}
	}

	for(unsigned int i=0;i<c.size(); i++){
		if(c.at(i).getType() == "GATEWAY"){
			for(unsigned int j=0; j<c.size(); j++){
				if(c.at(j).getType() == "GATEWAY" && ct.getDt().at(i).at(j) < 5200 && i != j){
					if(c.at(i).getName() == "Santiago_CL" && c.at(j).getName() == "New_York_NY"){
						continue;
					}
					if(c.at(j).getName() == "Santiago_CL" && c.at(i).getName() == "New_York_NY"){
						continue;
					}
					a.at(i).at(j) = true;
					a.at(j).at(i) = true;
				}
			}
		}
	}


	std::ofstream fout("city_graph.txt");
	fout << "CITY GRAPH:\n\n";
	for(unsigned int i=1; i<a.size(); i++){
		fout << std::setw(3) <<std::right<< i-1 << " " << c.at(i).getName() << '\n';
		for(unsigned int j=1; j<a.size(); j++){
			if(a.at(i).at(j)){
				fout <<std::setw(6) << std::right << j-1 << " " << std::setw(20) << std::left << c.at(j).getName() << std::setw(4) << std::right << ct.getDt().at(i).at(j) << ".0 miles  " << std::setw(4) << std::right <<  std::setprecision(1) << std::fixed<< ct.getTt().at(i).at(j) << std::setprecision(0) << std::fixed << " hours" << '\n';
			}
		}
		if(i != a.size()-1){
			fout<< '\n';
		}
	}
	fout.close();
				
	//for(unsigned int i=0; i<a.at(1).size();i++){

	//std::cout << a.at(1).at(i)<< '\n';
	//}



}


typedef enum {WHITE, BLACK} vcolor_t;
void dijkstra_route(int source, int sink, std::vector<city> c, std::vector<std::vector<bool> > a, costtable ct){
	std::vector<float> vdist;
	std::vector<int> vlink;
	std::vector<float> vtim;
	vtim.assign(c.size()-1,0);
	vdist.assign(c.size()-1,std::numeric_limits<float>::infinity());
	vlink.assign(c.size()-1, -1);
	std::vector<vcolor_t> vcolor;
	vcolor.assign(c.size()-1, WHITE);
	vdist.at(source) =0;
	vlink.at(source) = source;
	//vector<int> aj;
	//for(int i=0; i<c.size(); i++){
		//if(a.at(source).at(i)){
			//aj.push_back(i);
		//}
	//}
	//for(unsigned int i=0; i<a.at(1).size();i++){

	//std::cout << a.at(1).at(i)<< '\n';
	//}
	std::vector<std::vector<int> > aj;
	aj.resize(c.size());
	for(unsigned int i=1; i<c.size(); i++){
		for(unsigned int j=1; j<c.size(); j++){
			if(a.at(i).at(j)){
				//std::cout << i << " " <<  j << '\n';
				aj.at(i-1).push_back(j-1);
				aj.at(j-1).push_back(i-1);
			}
		}
	}
	for(unsigned int i=0; i<aj.size(); i++){
		std::sort(aj.at(i).begin(), aj.at(i).end());
		aj.at(i).erase(std::unique(aj.at(i).begin(), aj.at(i).end()), aj.at(i).end());	
	}

	//for(unsigned int i=0; i<aj.at(10).size(); i++){
		//std::cout << aj.at(10).at(i);
	//}
	while(true){
		int next_i =-1;
		float mdist = std::numeric_limits<float>::max();
		//Line 279!
		for(unsigned int i=0; i<(unsigned int)vcolor.size(); i++){
			//std::cout<< i <<'\n';
			if(vcolor.at(i) == WHITE && mdist > vdist.at(i)){
				next_i = i;
				mdist = vdist.at(i);
			}
		}

		int i = next_i;
		if(i == -1){
			//std::cerr << "-1\n";
			return;
		}
		//std::cerr << i <<'\n';
		vcolor.at(i) = BLACK;

		if(i == sink){
			break;
		}

		for(unsigned int k=0; k<aj.at(i).size(); k++){
			int j = aj.at(i).at(k);
			float wij = ct.getDt().at(i+1).at(j+1);
			float wit = ct.getTt().at(i+1).at(j+1);
			//std::cerr << i << ' ' << j << ' ' << wij << '\n';
			if(vcolor.at(j) == WHITE){
				if(vdist.at(j) > vdist.at(i) + wij){
					vdist.at(j) = vdist.at(i) + wij;
					vtim.at(j) = vtim.at(j) + wit;
					vlink.at(j) = i;
				}
			}
		}
	}

	if(vdist.at(sink) == std::numeric_limits<float>::infinity()){
		std::cout << "No route\n";
		return;
	}

	std::stack<int> s;

	for(int i = sink; i != source; i=vlink.at(i)){
		s.push(i);
	}
	s.push(source);
	//std:: cout << c.at(source);
	int td =0;
	float tt =0.0;
	while(!s.empty()){
		int i = s.top();
		s.pop();
		std::cout <<std::setw(7) << std::right << std::setprecision(1) << std::fixed << vdist.at(i) << " miles  " 
			<<  std::setw(4) << std::right <<  std::setprecision(1) << std::fixed<< vtim.at(i)+tt  << std::setprecision(0) << std::fixed << " hours :" << std::setw(3) << i << ' ' 
			<< std::setw(19) << std::left << c.at(i+1).getName()
			<< std::setprecision(1) << std::fixed << std::setw(6) << std::right <<  vdist.at(i)-td << " miles  "
			<< std::setw(4) << std::right << vtim.at(i) << " hours" << '\n';
		td=vdist.at(i);
		tt+=vtim.at(i);
	}
	std::cout << '\n';


}

void dijkstra_time(int source, int sink, std::vector<city> c, std::vector<std::vector<bool> > a, costtable ct){
	std::vector<float> vdist;
	std::vector<int> vlink;
	std::vector<float> vtim;
	vtim.assign(c.size()-1,0);
	vdist.assign(c.size()-1,std::numeric_limits<float>::infinity());
	vlink.assign(c.size()-1, -1);
	std::vector<vcolor_t> vcolor;
	vcolor.assign(c.size()-1, WHITE);
	vdist.at(source) =0;
	vlink.at(source) = source;
	//vector<int> aj;
	//for(int i=0; i<c.size(); i++){
		//if(a.at(source).at(i)){
			//aj.push_back(i);
		//}
	//}
	//for(unsigned int i=0; i<a.at(1).size();i++){

	//std::cout << a.at(1).at(i)<< '\n';
	//}
	std::vector<std::vector<int> > aj;
	aj.resize(c.size());
	for(unsigned int i=1; i<c.size(); i++){
		for(unsigned int j=1; j<c.size(); j++){
			if(a.at(i).at(j)){
				//std::cout << i << " " <<  j << '\n';
				aj.at(i-1).push_back(j-1);
				aj.at(j-1).push_back(i-1);
			}
		}
	}
	for(unsigned int i=0; i<aj.size(); i++){
		std::sort(aj.at(i).begin(), aj.at(i).end());
		aj.at(i).erase(std::unique(aj.at(i).begin(), aj.at(i).end()), aj.at(i).end());	
	}

	//for(unsigned int i=0; i<aj.at(10).size(); i++){
		//std::cout << aj.at(10).at(i);
	//}
	while(true){
		int next_i =-1;
		float mdist = std::numeric_limits<float>::max();
		//Line 279!
		for(unsigned int i=0; i<(unsigned int)vcolor.size(); i++){
			//std::cout<< i <<'\n';
			if(vcolor.at(i) == WHITE && mdist > vdist.at(i)){
				next_i = i;
				mdist = vdist.at(i);
			}
		}

		int i = next_i;
		if(i == -1){
			//std::cerr << "-1\n";
			return;
		}
		//std::cerr << i <<'\n';
		vcolor.at(i) = BLACK;

		if(i == sink){
			break;
		}

		for(unsigned int k=0; k<aj.at(i).size(); k++){
			int j = aj.at(i).at(k);
			float wij = ct.getTt().at(i+1).at(j+1);
			float wit = ct.getDt().at(i+1).at(j+1);
			//std::cerr << i << ' ' << j << ' ' << wij << '\n';
			if(vcolor.at(j) == WHITE){
				if(vdist.at(j) > vdist.at(i) + wij){
					vdist.at(j) = vdist.at(i) + wij;
					vtim.at(j) = vtim.at(j) + wit;
					vlink.at(j) = i;
				}
			}
		}
	}

	if(vdist.at(sink) == std::numeric_limits<float>::infinity()){
		std::cout << "No route\n";
		return;
	}

	std::stack<int> s;

	for(int i = sink; i != source; i=vlink.at(i)){
		s.push(i);
	}
	s.push(source);
	//std:: cout << c.at(source);
	int td =0;
	float tt =0.0;
	while(!s.empty()){
		int i = s.top();
		s.pop();
		std::cout <<std::setw(7) << std::right << std::setprecision(1) << std::fixed << vtim.at(i) << " miles  " 
			<<  std::setw(4) << std::right <<  std::setprecision(1) << std::fixed<< vdist.at(i)  << std::setprecision(0) << std::fixed << " hours :" << std::setw(3) << i << ' ' 
			<< std::setw(19) << std::left << c.at(i+1).getName()
			<< std::setprecision(1) << std::fixed << std::setw(6) << std::right <<  vtim.at(i) << " miles  "
			<< std::setw(4) << std::right << (vdist.at(i))-tt << " hours" << '\n';
		td=vtim.at(i);
		tt=vdist.at(i);
	}
	std::cout << '\n';


}
void distance(std::string c1, std::string c2, std::vector<city> c, costtable ct){
	//vector<float> vdist;
	//vector<int> vlink;

	
	for(unsigned int i=0; i<c.size(); i++){
		if(c1 == c.at(i).getName()){
			for(unsigned int j=0; j<c.size(); j++){
				if(c2 == c.at(j).getName()){
					std::cout << c1 << " to " << c2 << " " << ct.getDt().at(i).at(j) << '\n';
				}
			}
		}
	}
}



int main(int argc, char *argv[]){
	//if((argc !=2) || (std::string(argv[1]) != "-graphinfo") || (std::string(argv[1]) != "-time") || (std::string(argv[1]) != "-distance")){
		//return 1;
	//}
	if(argc !=2){
		std::cerr << "usage: ./Citysim1 -distance|time|graphinfo\n";
	}
	std::vector<city> c;
	read_cityinfo("city_list.txt", c);
	costtable ct(c);
	//City Graph
	std::vector<std::vector<bool> > a;
	create_citygraph(c, ct, a);	
	//Distance
	if(std::string(argv[1]) == "-distance"){
		while(true){
			std::cout << "Enter> ";
			std::string c1, c2;
			int source, sink;
			std::cin >> c1 >> c2;
			//std::cerr << c1 << ' ' << c2;
			for(unsigned int i=0; i<c.size();i++){
				if(c1 == c.at(i).getName()){
					source = i-1;
				}
				if(c2 == c.at(i).getName()){
					sink = i-1;
				}
			}
			//std::cerr << source << " " << sink;
			dijkstra_route(source, sink, c, a, ct);
			//dijkstra_route(23, 21, c, a, ct);
		}
	//Time
	}else if(std::string(argv[1]) == "-time"){
		while(true){
			std::cout << "Enter> ";
			std::string c1, c2;
			int source, sink;
			std::cin >> c1 >> c2;
			//std::cerr << c1 << ' ' << c2;
			for(unsigned int i=0; i<c.size();i++){
				if(c1 == c.at(i).getName()){
					source = i-1;
				}
				if(c2 == c.at(i).getName()){
					sink = i-1;
				}
			}
			//std::cerr << source << " " << sink;
			dijkstra_time(source, sink, c, a, ct);
			//dijkstra_route(23, 21, c, a, ct);
		}
	
	//Graphinfo
	}else if(std::string(argv[1]) == "-graphinfo"){
		//City Info
		std::ofstream info("city_info.txt");
		info << "CITY INFO (N=" << c.size()-1 << "):\n\n";
		for(unsigned int i =1; i<c.size(); i++){
			info << std::setw(3) << std::right << i-1 << " " << c.at(i);
		}
		info.close();
		//Distance Table
		std::ofstream dis("city_distancetable.txt");
		dis << "DISTANCE TABLE:\n";
		for(unsigned int i =1; i<c.size(); i++){	
			for(unsigned int j=1; j<i; j++){
				std::string o = c.at(i).getName() + " to " + c.at(j).getName() + " ";
				std::ostringstream tv;
				tv << ct.getDt().at(i).at(j);
				std::string tvs(tv.str());
				std::string d = tvs + ".0 miles";
				dis << std:: setw(3) << std::setfill(' ') << std::right << i-1 << " " << std::setw(38) << std::setfill('.') << std::left << o << std::setw(13) << std::setfill(' ') << std::right << d<< '\n';
			
			}
			dis << '\n';
		}
		dis.close();
		//Time Table
		std::ofstream tim("city_timetable.txt");
		tim << "TIME TABLE:\n";
		for(unsigned int i =1; i<c.size(); i++){
			for(unsigned int j=1; j<i; j++){
				std::string o = c.at(i).getName() + " to " + c.at(j).getName() + " ";
				std::ostringstream tv;
				float tvf = ct.getTt().at(i).at(j);
				tvf = round(10 * tvf)/10;
				if(tvf-(int)tvf ==0){
					tv << tvf << ".0";
				}else {
					tv << tvf;
				}
				std::string tvs(tv.str());
				std::string d = tvs + " hours";
				tim << std:: setw(3) << std::setfill(' ') << std::right << i-1 << " " << std::setw(38) << std::setfill('.') << std::left << o << std::setw(11) << std::setfill(' ') << std::right << d<< '\n';
			
			}
			tim <<'\n';
		}
		tim.close();
	}else{
		std::cerr << "usage: ./Citysim1 -distance|time|graphinfo\n";
	
	}
	return 0;
}
