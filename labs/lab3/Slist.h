#ifndef SLIST_H
#define SLIST_H
#include <iostream>
#include <string.h>
#include <vector>
// include header file(s) needed

// qsort_r3: randomly chosen pivot, 3-way partition {<},{=},{>}



class data{
	public:
		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);
		data(){};
		data(string fn, string ln, string nm);
		bool operator <(const data& d) const{
			if(this->lname == d.lname){
				if(this->fname == d.fname){
					return this->num < d.num;
				}
				return this->fname < d.fname;
			}
			return lname < d.lname;
		};

	private:
		string fname;
		string lname;
		string num;
};
data::data(string fn, string ln, string nm){
	fname = fn;
	lname = ln;
	num = nm;
};
istream & operator>>(istream &in, data &r){
	in >> r.fname >> r.lname >> r.num;
	//in >> r.lname;
	//in >> r.num;
	return in;
}


ostream & operator<<(ostream &out, const data &r){
	out << r.lname <<", " << r.fname;
	int l = 24 - (r.fname.length() + r.lname.length() +2);
	for (int i = 0; i < l; i++){
		out << " ";
	}
	out << r.num << "\n";
	return out;
}


void printlist(vector<data> v){
	for(int i =0; i < v.size(); i++){
		cout << v.at(i);
	}
};
// template <typename T>
template <class T>
class slist {
	private:
		struct node {
			node() { data = T(); next = NULL; }
			node(const data &d){
				T = d;
				next = NULL;
			}
			//operator <(const node& n) const{

			// add node(const T &key) { write this }
			// add overloaded operator< code

			T data;
			node *next;
		};

		// add class sptr { write this for node data }

	public:
		class iterator {
			public:
				iterator() { p = NULL; }
				T & operator*() { return p->data; }
				iterator & operator++() { p = p->next; return *this; }
				bool operator!=(const iterator & rhs) const { return p != rhs.p; }

			private:
				iterator(node *n_p) { p = n_p; }
				node *p;

				friend class slist<T>;
		};

	public:
		slist();
		~slist();

		void push_back(const T &);
		void sort(const string &);

		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(NULL); }

	private:
		node *head;
		node *tail;
};

template <typename T>
slist<T>::slist() {
	head = new node();
	tail = head;
}

template <typename T>
slist<T>::~slist() {
	while (head->next != NULL) {
		node *p = head->next;
		head->next = p->next;
		delete p;
	}
	delete head;

	head = NULL;
	tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
	tail->next = new node(din);
	tail = tail->next;
}

template <typename T>
void slist<T>::sort(const string &algname) {
	// determine number of list elements
	// set up smart pointer array called Ap
	// if quicksort, apply std::sort(...)
	// if mergesort, apply std::stable_sort(...)
	// if qsort_r3, apply qsort_r3(...)
	// use sorted Ap array to relink list 
}

#endif // SLIST_H
