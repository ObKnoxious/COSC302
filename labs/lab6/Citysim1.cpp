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
				time_table.at(i).at(j) = distance_table.at(i).at(j)/60;
			}else{
				time_table.at(i).at(j) = distance_table.at(i).at(j)/570;
			}
		}
	}

}



int main(int argc, char *argv[]){
	if((argc != 2) || (std::string(argv[1]) != "-graphinfo")){
		std::cerr << "usage: ./Citysim1 -graphinfo\n";
		return 1;
	}
	std::vector<city> c;
	read_cityinfo("city_list.txt", c);
	costtable ct(c);
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


	return 0;
}
