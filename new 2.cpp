template <typename T>
void randperm(vector<T> &v) {
	for (int i=0; i<=(int)v.size()-1; i++){
		swap(v[rand() % (i+1)], v[i]);
	}
}