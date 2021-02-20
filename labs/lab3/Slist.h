#ifndef SLIST_H
#define SLIST_H
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
// include header file(s) needed
using namespace std;
// qsort_r3: randomly chosen pivot, 3-way partition {<},{=},{>}



// template <typename T>
template <class T>
class slist {
	private:
		struct node {
			node() { data = T(); next = NULL; }
			node(const T &d){
				data = d;
				next = NULL;
			}

			// add node(const T &key) { write this }
			// add overloaded operator< code

			T data;
			node *next;
			bool operator <(const node& n) const{
				return data < n.data;
			}
		};

		// add class sptr { write this for node data }
		class sptr {
			public:
				sptr(node * _ptr=NULL){
					ptr = _ptr;
				}

				bool operator< (const sptr &rhs) const {
					return *ptr < **rhs;
				}
				node* operator* () const {
					return ptr;
				}
			private:
				node *ptr;
		};

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
	//cout << "I'm in the sort funciton!\n";
	vector<sptr> Ap;
	node* p = head->next;
	while(p != NULL){
		//cout << "This is the while pushing into the sptr vector\n";
		Ap.push_back(p);
		p=p->next;
	}
	if(algname == "q"){

		std::sort(Ap.begin(), Ap.end());
	}else if(algname == "m"){
		std::stable_sort(Ap.begin(), Ap.end());
	}
	p = head;
	for(int i =0; i < Ap.size(); i++){
		//cout << "And this is the vector trying to put it back together\n";
		p->next = *Ap.at(i);
		p=p->next;
	}
	p->next = NULL;
	// set up smart pointer array called Ap
	// if quicksort, apply std::sort(...)
	// if mergesort, apply std::stable_sort(...)
	// if qsort_r3, apply qsort_r3(...)
	// use sorted Ap array to relink list 
}

#endif // SLIST_H
