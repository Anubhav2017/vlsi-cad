#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


struct clause{

	vector<int> vars;
	int n_remaining;
	vector<int> remaining_vars;
	bool value;

	clause(){
		n_remaining=0;
		value=0;
	}

	bool return_value(){
		return value;
	}


	void add(int x){

		vars.push_back(x);
		remaining_vars.push_back(x);
		n_remaining++;
	}

	bool exist(int var){

		vector<int>::iterator iter;
		iter=find(vars.begin(),vars.end(),var);

		if(iter != vars.end()){
			return true;
		}

		iter=find(vars.begin(),vars.end(),-var);
		if(iter != vars.end()){
			return true;
		}

		return false;
	}

	bool var_sign(int var){

		vector<int>::iterator iter;
		iter=find(vars.begin(),vars.end(),var);

		if(iter != vars.end()){
			return true;
		}

		iter=find(vars.begin(),vars.end(),-var);
		if(iter != vars.end()){
			return false;
		}

	}

	bool unit_clause(){
		if(n_remaining==1 && !value){
			return true;
		}
		else return 0;
	}

	void assign(int x, bool val){
		vector<int>::iterator iter;

		iter=find(remaining_vars.begin(),remaining_vars.end(),x);

		if(iter != remaining_vars.end()){
			int el=*iter;
			remaining_vars.erase(iter);
			n_remaining--;
			if(!value && el>0){
				value=val;
			}
			else if(!value && el<0){
				value=val^1;
			}

		}
	}

	int assign_unit(vector<bool> &vars,vector<bool> &assigned_vars){
		int el=remaining_vars[0];
		if(el>0){
			int index=el-1;
			vars[index]=1;
			assigned_vars[index]=1;
			value=1;
			return el;

		}
		else{
			int index=abs(el)-1;
			vars[index]=0;
			value=1;
			assigned_vars[index]=1;
			return abs(el);
		}
	}

	void reset(){
		remaining_vars.clear();
		remaining_vars=vars;
		value=0;
	}


};

void solve1(vector<clause> clauses, vector<bool> &vars, vector<bool> &assigned_vars){

	int n=clauses.size();
}

void assign1(vector<clause> &clauses,int var, bool value){
	for(int i=0;i<clauses.size();i++){
		clauses[i].assign(var,value);
	}
}

void check_for_unit_and_assign(vector<clause> &clauses, vector<bool> &vars, vector<bool> &assigned_vars,bool& found){
	for(int i=0;i<clauses.size();i++){

		if(clauses[i].unit_clause()){

			found=1;
			int var=clauses[i].assign_unit(vars,assigned_vars);
			bool value=vars[var-1];
			assign1(clauses,var,value);

		}
	}
}

bool check_for_sat(vector<clause> clauses){
    
    bool ans=clauses[0].return_value();
    
    for(int i=1;i<clauses.size();i++){
        
        ans=ans*clauses[i].return_value();
    }
    return ans;
} 

bool check_for_pure_and_assign(vector<clause> &clauses,vector<bool> &vars, vector<bool> &assigned_vars, int index){


	vector<bool> var_values(0);

	for(int i=0;i<clauses.size();i++){

		if(clauses[i].exist(index+1) && !clauses[i].return_value()){
			var_values.push_back(clauses[i].var_sign(index+1));
		}
	}

	if(var_values.size()>0){

		bool val=var_values[0];

		for(int i=0;i<var_values.size();i++){
			if(var_values[i] != val)return false;
		}

		assign1(clauses,index+1,val);
		vars[index]=val;
		assigned_vars[index]=1;


	}



}

int main(){
	
	int n;  //number of clauses
	cin>>n;

	int m;
	cin>>m; //nunumber of variables

	vector<clause> clauses(n);
	vector<bool> vars(m);
	vector<bool> assigned_vars(m);

	for(int i=0;i<n;i++){
		int x;
		cin>>x;

		while( x!= 0){
			clauses[i].add(x);
			cin>>x;
		}
	}

	bool found=1;
	bool sat=0; 

	while(found && !sat){
		found=0;
		check_for_unit_and_assign(clauses,vars,assigned_vars,found);
		sat=check_for_sat(clauses);
	}
	
	

	if(!sat){

		/*vector<clause> clauses2(0);
		for(int i=0;i<n;i++){
			if(!clauses[i].return_value()){
				clauses2.push_back(clauses[i]);
			}
		}
		int n2=clauses2.size();*/

/*		vector<bool> vars2=vars;
		vector<bool> assigned_vars2=assigned_vars;*/

		for(int i=0;i<m;i++){
			if(assigned_vars[i]==0){

				bool pure=check_for_pure(clauses,i);

			}
		}

	    
	}

}