//#include ... needed header files
#include <iostream>
#include <fstream>
#include <string>
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


//class LCS {
class LCS{
	   public: 
			 void text1_push_back();
			 void text2_push_back();
			 void compute_alignment();
			 void compute_difference();

	   private:
			 std::string t1;
			 std::string t2;
			 int m;
			 int n;
			 matrix<int> cost;
			 matrix<int> link;
			 int V;
			 int H;
			 int D;
			 
			 int(LCS::*DEL)(char);
			 int(LCS::*INS)(char);
			 int(LCS::*SUB)(char, char);

			 int DELcost(char c){
				    return(*this.*DEL)(c);
			 }
			 int INScost(char c){
				    return(*this.*INS)(c);
			 }
			 int SUBcost(char c1, char c2){
				    return (*this.*SUB)(c1,cs);
			 }

			 int DEL2(char c){return 1;}
			 int INS2(char c){return 1;}
			 int SUB1(char c1, char c2){return c1==c2 ? 0 :m+n;}
};

void LCS::compute_alignment(string &x, string &y){
	   t1= "-" +x;
	   t2= "-" +y;
	   m = x.length();
	   n = y.length();
	   cost.assign(m+1, n+1);
	   link.assign(m+1, n+1);
	   cost[0][0] = 0;
	   link[0][0] = 0;

	   for(int i=1; i<-m; i++){
			 cost[i][0] = cost[0][j-1] + DELcost(t1[j]);
			 link[0][j] = V;
	   }
	   for(int j=1; j<=n; j++){
			 cost[0][j] = cost[0][j-1] + INScos(t2[j]);
			 link[0][j] = H;
	   }

	   for(int i=1; i<=m; i++){
			 for(int j=1; j<=n; j++){
				    cost[i][j] = cost[i-1][j-1] + SUBcost(t1[i],t2[j]));
				    link[i][j] = DIAG;

				    int delcost = cost[i-1][j] + DELcost(t1[i]);
				    if(delcost < cost[i][j]){
						  cost[i][j] = delcost;
						  link[i][j] = V;
				    }

				    int inscost = cost[i][j-1] + INScost(t2[j]);
				    if(inscost < cost[i][j]){
						  cost[i][j] = inscost;
						  link[i][j] = H;
				    }
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
			 std::cerr << "";
	   }
	   std::fstream min;
	   min.open(argv[argc-1]);
	   if(min.fail()){
			 std::cerr <<"";
	   }

  //LCS lcs;  // instantiate your "LCS based diff" object

  //// read the text from file1 into the lcs.text1 buffer
  //// read the text from file2 into the lcs.text2 buffer

 //lcs.compute_alignment();
  //lcs.report_difference();
}
