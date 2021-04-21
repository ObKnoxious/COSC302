//#include ... needed header files
#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//class matrix {
  //// class for storing 2D array
//};i

template <typename T> class matrix {
	   size_t Nrows, Ncols;
	   T **   data;

	   public:
	   matrix() : data(NULL) {}
	   ~matrix() {
			 if (!data)
				    return;
			 delete[] * data; // delete[] doesn't care if it's NULL
			 delete[] data;
			 data = NULL;
	   }
	   void assign(size_t _Nrows, size_t _Ncols, const T &value = T()) {
			 this->Nrows               = _Nrows;
			 this->Ncols               = _Ncols;
			 *(data = new T *[_Nrows]) = new T[_Nrows * _Ncols];
			 std::fill(*data, *data + _Nrows * _Ncols, value);
			 for (T **beg = data + 1; beg < data + _Nrows; ++beg) *beg = *(beg - 1) + _Ncols;
	   }
	   size_t   get_Nrows() const { return Nrows; }
	   size_t   get_Ncols() const { return Ncols; }
	   T *      operator[](size_t i) { return data[i]; }
	   const T *operator[](size_t i) const { return data[i]; }
};


enum direction{
	   VERT=1,
	   HORZ=2,
	   DIAG=4,
};
enum operation{
	   //NONE_OP=0,
	   DELETE=0,
	   INSERT=1,
	   MATCH=2,
};

struct diff{
	   int m;
	   int n;
	   int op;
	   diff(int a, int b, int c){m=a, n=b, op=c;}
};

//class LCS {
class LCS{
	   private:
			 std::vector<std::string> t1;
			 std::vector<std::string> t2;
			 int m;
			 int n;
			 matrix<int> cost;
			 matrix<int> link;
			 //int V;
			 //int H;
			 //int D;
			 
			 //int(LCS::*DEL)(std::string);
			 //int(LCS::*INS)(std::string);
			 //int(LCS::*SUB)(std::string, std::string);
			  
			 //int DELcost(std::string c){
				    //return(*this.*DEL)(c);
			 //}
			 //int INScost(std::string c){
				    //return(*this.*INS)(c);
			 //}
			 //int SUBcost(std::string c1, std::string c2){
				    //return (*this.*SUB)(c1,c2);
			 //}

			 int DELcost(std::string c){return 1;}
			 int INScost(std::string c){return 1;}
			 int SUBcost(std::string c1, std::string c2){return c1==c2 ? 0 :m+n;}
	   public: 
			 void t1pb(std::string i){t1.push_back(i);}
			 void t2pb(std::string i){t2.push_back(i);}
			 //void compute_alignment(std::string &, std::string &);
			 void compute_alignment();
			 void report_difference();
			 void report_difference(std::stack<diff> &, int, int);
			 void printToMatch(std::list<diff>, std::list<diff>);

};

//void LCS::compute_alignment(std::string &x, std::string &y){
void LCS::compute_alignment(){
	   //t1= "-" +x;
	   //t1.push_back("-");
	   //t1.push_back(x);
	   ////t2= "-" +y;
	   //t2.push_back("-");
	   //t2.push_back(y);
	   t1.insert(t1.begin(), "");
	   t2.insert(t2.begin(), "");
	   m = t1.size();
	   n = t2.size();
	   cost.assign(m, n);
	   link.assign(m, n);
	   cost[0][0] = 0;
	   link[0][0] = 0;

	   for(int i=1; i<m; i++){
			 cost[i][0] = cost[i-1][0] + DELcost(t1[i]);
			 link[i][0] = VERT;
	   }
	   for(int j=1; j<n; j++){
			 cost[0][j] = cost[0][j-1] + INScost(t2[j]);
			 link[0][j] = HORZ;
	   }

	   for(int i=1; i<m; i++){
			 for(int j=1; j<n; j++){
				    cost[i][j] = cost[i-1][j-1] + SUBcost(t1[i],t2[j]);
				    link[i][j] = DIAG;

				    int delcost = cost[i-1][j] + DELcost(t1[i]);
				    if(delcost < cost[i][j]){
						  cost[i][j] = delcost;
						  link[i][j] = VERT;
				    }

				    int inscost = cost[i][j-1] + INScost(t2[j]);
				    if(inscost < cost[i][j]){
						  cost[i][j] = inscost;
						  link[i][j] = HORZ;
				    }
			 }
	   }

	   std::cout << "m = " << m << '\n' << "n = " << n << '\n';
	   std::cout << "D[m][n] = " << cost[m-1][n-1] << '\n';


}

void::LCS::report_difference(){
	   std::stack<diff> tsm;
	   report_difference(tsm, t1.size()-1, t2.size()-1);
	   std::list<diff> dL;
	   std::list<diff> iL;
	   while(!tsm.empty()){
			 //std::cerr<<"b4 switch\n";
			 switch(tsm.top().op){
				   case DELETE:
					 //std::cerr<<"DELETE\n";
						 dL.push_back(tsm.top());
						 break;
				    case INSERT:
						 //std::cerr<<"INSTERT\n";
						 iL.push_back(tsm.top());
						 break;
				    //case MATCH:
				    default:
					 //std::cerr<<"MATCH\n";
						 printToMatch(dL, iL);
						 dL.clear();
						 iL.clear();
						 break;
			}
			tsm.pop();
	   }
	   //std::cerr<<"b4 if\n";
	   if(dL.size() || iL.size()){
			 printToMatch(dL, iL);
	   }
}

void::LCS::report_difference(std::stack<diff> &tsm, int m, int n){
	   if(m < 0 || n < 0){
			 return;
	   }
	   if(link[m][n] == VERT){
			 //std::cerr<<"VERT\n";
			 diff op {m, n, 0};
			 tsm.push(op);
			 report_difference(tsm, m-1, n);
	   }else if(link[m][n] == HORZ){
		 //std::cerr<<"HORZ\n";
			 diff op {m, n, 1};
			 tsm.push(op);
			 report_difference(tsm, m , n-1);
	   }else {
			 //std::cerr<<"ELSE\n";
			 diff op {m, n, 2};
			 tsm.push(op);
			 report_difference(tsm, m-1, n-1);
	   }
}

void::LCS::printToMatch(std::list<diff> dL, std::list<diff> iL){
	  //std::cerr<< "In recursize cal
	   //std::cerr<< "Print to match\n";
	   if(!iL.size() && !dL.size()){
			 return;
	   }
	   if(dL.size()){
			 dL.front().m;
			 if(dL.front().m == dL.back().m){
				    std::cout<<dL.front().n;
			 }else{
				    std::cout << dL.front().n << "," << dL.back().n;
			 }
	   }else{
			 std::cout<<iL.front().m;
			 std::cout << 'a';
	   }
	   if(dL.size()&&iL.size()){
			 std::cout << 'c';
	   }
	   if(iL.size()){
			 iL.front().n;
			 if(iL.front().n == iL.back().n){
				    std::cout << iL.front().n;
			 }else{
				    std::cout << dL.front().n << ',' << dL.back().n;
			 }
	   }
}


//int main(int argc, char *argv[])
int main(int argc, char *argv[]){
	   if(argc != 3 && argc != 4){
		   std::cerr << "usage: ./diff8 [-verbose] file1 file2";
	   }

//{
  //// check two input files are specified on command line
	   std::fstream oin;
	   oin.open(argv[argc-2]);
	   if(oin.fail()){
			 std::cerr << "usage: ./diff8 [-verbose] file1 file2";
	   }
	   std::fstream min;
	   min.open(argv[argc-1]);
	   if(min.fail()){
			 std::cerr <<"usage: ./diff8 [-verbose] file1 file2";
	   }


  //LCS lcs;  // instantiate your "LCS based diff" object
	   LCS lcs;
	   std::string line ="";
	   while(getline(oin,line)){
			 //std::cerr << "Reading in stuff \n";
			 lcs.t1pb(line);
	   }
	   while(getline(min,line)){
			 lcs.t2pb(line);
	   }
  //// read the text from file1 into the lcs.text1 buffer
  //// read the text from file2 into the lcs.text2 buffer
	   lcs.compute_alignment();
 //lcs.compute_alignment();
  //lcs.report_difference();
	   lcs.report_difference();
}
