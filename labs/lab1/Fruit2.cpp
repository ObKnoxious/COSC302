// Lab 1, COSC302
// By Knox Crichton
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>

using namespace std;


struct Fruit{
	string name;
	float quant;
	float cost;
	Fruit(string f, float q, float c){
		name = f;
		quant = q;
		cost = c;
	}
	Fruit(){
		name = "NOT SET!";
		quant = -1.0;
		cost = -1.0;
	}
	bool operator <(const Fruit& f) const{
		//return lexicographical_compare(name.c_str(), name.c_str()+int(strlen(name.c_str())), f.name.c_str(), f.name.c_str()+strlen(name.c_str()));
		return this->name < f.name;
	}
	bool operator <=(const Fruit& f) const{
		if(name == f.name){
			return true;
		}else{
		return lexicographical_compare(name.c_str(), name.c_str()+int(strlen(name.c_str())), f.name.c_str(), f.name.c_str()+strlen(name.c_str()));
		}
	}
	bool operator ==(const Fruit& f) const{
		//if(name == f.name){
			//return true;
		//}else{
			//return false;
		//}
		return(name == f.name);
	}
	void operator +=(const Fruit& f){
		//if(name == f.name){
		//cout << "Adding " << quant << " and " << f.quant;	
		this->quant+=f.quant;
		//cout << " got " << quant << "\n";
		//}else{
			//cerr << "Looks like you are trying to add differnet fruits...\n";
		//}
	}
};

struct Node{
	struct Fruit data;
	struct Node* next;
	Node(){
		data = Fruit();
		next = NULL;
	}
	//struct Node* prev;
};
int main(int argc, char* argv[]){
	//cout << "DOES ANYTHING WORK???\n";
	//cout << (string(argv[1]) == "-inorder");
	//cout << (string(argv[1]) == "-inorder" || string(argv[1]) == "-sortall" || string(argv[1]) == "-sortone");
	if(argc == 3 && (string(argv[1]) == "-inorder" || string(argv[1]) == "-sortall" || string(argv[1]) == "-sortone")){
		if(string(argv[1]) == "-inorder"){
			//cout << "inorder detected\n";
			ifstream f;
			f.open(argv[2]);
			string line;
			struct Node* head = new Node();
			string fr;
			float p, q;
			while(f >> fr >> q >> p){
				Fruit inF = Fruit(fr, q, p);
				Node* n = new Node();
				Node* l = head;
				n->data = inF;
				while(l->next != NULL){
					//cout << "inside the while\n";
					l=l->next;
				}
				l->next=n;
						//n->prev=l;
			}
			float tc;
			struct Node* ptr = head->next;
			while(ptr != NULL){
				float uc = ptr->data.quant * ptr->data.cost;
				tc+=uc;
				cout << fixed << showpoint << setprecision(2) << setw(20) << setfill('.') <<  left <<  ptr->data.name << setfill(' ') <<  setw(6) << right << ptr->data.quant <<  " x " << setw(4)  <<  ptr->data.cost << " = " <<  setw(7) << right <<  uc << "  : " <<  setw(8) << right << tc << "\n";
				ptr=ptr->next;
			}
			while(head->next){
				Node* t = head->next;
				head->next=head->next->next;
				delete(t);

			}
			delete head;
			f.close();
			return 0;
		}else if(string(argv[1]) == "-sortall"){
			ifstream fin;
			fin.open(argv[2]);
			string line;
			struct Node* head = new Node();
			string fr;
			float p, q;
			while(fin >> fr >> q >> p){
				Fruit inF = Fruit(fr, q, p);
				Node* n = new Node();
				Node* l = head;
				n->data = inF;
				while(l->next && l->next->data <= inF){
					l=l->next;
				}
							n->next=l->next;
				l->next=n;
			}
			float tc;
			struct Node* ptr;
			ptr = head->next;
			while(ptr != NULL){
				float uc = ptr->data.quant * ptr->data.cost;
				tc+=uc;
				cout << fixed << showpoint << setprecision(2) << setw(20) << setfill('.') <<  left <<  ptr->data.name << setfill(' ') <<  setw(6) << right << ptr->data.quant <<  " x " << setw(4)  <<  ptr->data.cost << " = " <<  setw(7) << right <<  uc << "  : " <<  setw(8) << right << tc << "\n";
				ptr=ptr->next;
			}
			while(head->next){
				Node* t = head->next;
				head->next=head->next->next;
				delete(t);

			}
			delete head;
			fin.close();
			return 0;
		}else if(string(argv[1]) == "-sortone"){
			ifstream fin;
			fin.open(argv[2]);
			string line;
			struct Node* head = new Node();
			string fr;
			float p, q;
			while(fin >> fr >> q >> p){
				Fruit inF = Fruit(fr, q, p);
				Node* n = new Node();
				Node* l = head;
				n->data = inF;
				while(l->next && l->next->data <= inF){
					l=l->next;
				}
				if(l->data == inF){
					//cout << "Detecting that " << l->data.name << " in the list is equal too " << inF.name << " adding " << l->data.quant << " and " << inF.quant << "\n";
					l->data += inF;
					continue;
				}
				n->next=l->next;
				l->next=n;
			}
			float tc;
			struct Node* ptr;
			ptr = head->next;
			while(ptr != NULL){
				float uc = ptr->data.quant * ptr->data.cost;
				tc+=uc;
				cout << fixed << showpoint << setprecision(2) << setw(20) << setfill('.') <<  left <<  ptr->data.name << setfill(' ') <<  setw(6) << right << ptr->data.quant <<  " x " << setw(4)  <<  ptr->data.cost << " = " <<  setw(7) << right <<  uc << "  : " <<  setw(8) << right << tc << "\n";
				ptr=ptr->next;
			}
			while(head->next){
				Node* t = head->next;
				head->next=head->next->next;
				delete(t);

			}
			delete head;

			fin.close();
			return 0;
		}
	}else{
		cerr << "usage: ./sfruit2 -inorder|sortall|sortone file.txt";
		return 1;
	}
}

