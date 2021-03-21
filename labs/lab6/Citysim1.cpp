#include <string.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
class city{
	private:
		std::string name;
		std::string type;
		int zone;
		float lat;
		float lon;
		int popu;

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
		int getPopu(){
			return popu;
		}

		friend std::istream & operator >> (std::istream &, city &);
		friend std::ostream & operator << (std:: ostream &, city &);
};

std::istream & operator >> (std::istream &in, city &c){
	in  >> c.zone >> c.name >> c.lat >> c.lon >> c.popu;
	return in;
}

std::ostream & operator << (std::ostream &out, city &c){
	out << c.name;
	return out;
}


void read_cityinfo(std::string fname, std::vector<city> &v){
	std::fstream fin;
	fin.open(fname.c_str());
	city c;
	std::string l;
	while(std::getline(fin, l)){
		if(l[0] == '#'){
			continue;
		}
		std::stringstream ss(l);
		ss >> c;
		v.push_back(c);
	}
	
}

int main(int argc, char *argv[]){
	std::vector<city> c;
	read_cityinfo("city_list.txt", c);
	//for(unsigned int i=0; i<c.size(); i++){
		//std::cout << c.at(i);
	//}

	return 0;
}
