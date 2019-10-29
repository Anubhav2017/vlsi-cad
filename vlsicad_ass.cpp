#include<iostream>
#include<vector>

using namespace std;


struct clause{

	vector<int> vars;

	void add(int x){

		vars.push_back(x);
	}


};


int main(){
	
	int n;  //number of clauses
	cin>>n;

	int m;
	cin>>m; //nunumber of variables



	for(int i=0;i<n;i++){
		int x;
		cin>>x;

		while( x!= 0){
			clauses[i].add(x);
			cin>>x;
		}
	}

	
}