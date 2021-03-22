#include <string.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <iomanip>
class city{
	private:
		std::string name;
		std::string type;
		int zone;
		float lat;
		float lon;
		int popu;
		const static float rp =	M_PI/180;
		//const static float rp = (22/7)/180;
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
			//float pi = 22/7;
			//float rp = pi/180;
			return lat*rp;
		}
		float getLonRad(){
			//float pi = 22/7;
			//float rp = pi/180;
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
		std::vector<float> time_table;
	public:
		costtable(){}
		costtable(std::vector<city> &);
		std::vector<std::vector<float> > getDt(){
			return distance_table;
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
}

//std::ostream cityInfo(std::vector<city> c){
	//std::ostream out;
	//for(unsigned int i =0; i<c.size(); i++){
		//out << std::setw(3) << std::right << i << " ";
	//}
	//return out;
//}


int main(int argc, char *argv[]){
	std::vector<city> c;
	read_cityinfo("city_list.txt", c);
	//for(unsigned int i=0; i<c.size(); i++){
		//std::cout << c.at(i) << '\n';
	//}
	costtable ct(c);
	if(std::string(argv[1]) == "-graphinfo"){
		std::ofstream info("city_info.txt");
		info << "CITY INFO (N=" << c.size()-1 << "):\n\n";
		for(unsigned int i =1; i<c.size(); i++){
			info << std::setw(3) << std::right << i-1 << " " << c.at(i);
		}
		info.close();
		std::ofstream dis("city_distancetable.txt");
		dis << "DISTANCE TABLE:\n";
		for(unsigned int i =1; i<c.size(); i++){	
			for(unsigned int j=1; j<i; j++){
				//std::cout << " J: " << j << " " << c.at(j).getName() << " i: " << c.at(i).getName() << '\n';
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
	}
	//if(std::string(argv[1]) == "-distance"){
		//while(true){
			//std::string c1;
			//std::string c2;
			//std::cin >>c1;
			//std::cin >>c2;
			//for(unsigned int i=0; i<c.size(); i++){
				//if(c.at(i).getName() == c1){
					//for(unsigned int j=0; j<c.size(); j++){
						//if(c.at(j).getName() == c2){
							//std::cout <<"Distance "<< ct.getDt().at(i).at(j) << "\n";
							//break;
						//}
					//}
				//}
			//}		
		//}
	//}
	return 0;
}
