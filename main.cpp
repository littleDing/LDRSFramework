#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
template <class K,class V>
ostream& operator << (ostream& out,const map<K,V>& m){
	//out<<"{"<<endl;
	for(typename map<K,V>::const_iterator it=m.begin();it!=m.end();++it){
		out<<" "<<it->first<<":"<<it->second<<" ";
	}
	//out<<"}";
	return out;
}
template <class V>
ostream& operator << (ostream& out,const vector<V> v){
	out<<"<";
	for(int i=0;i<v.size();i++){
		if(i==0)	out<<v[i];
		else out<<","<<v[i];
	}
	out<<">";
	return out;
}
template <class K,class V>
V findMax(const map<K,V>& m){
	V ret;
	for(typename map<K,V>::const_iterator it=m.begin();it!=m.end();++it){
		ret=max(ret,it->second);
	}
	return ret;
}
template <class T>
bool cmp(const T& a,const T& b){
	return a>b;
}
template <class K,class V>
vector<V> findMax(const map<K,V>& m,int cnt){
	vector<V> ret;
	for(typename map<K,V>::const_iterator it=m.begin();it!=m.end();++it){
		ret.push_back(it->second);
	}
	sort(ret.begin(),ret.end(),cmp);
	return ret;
}

struct VectorItem{
	int key;
	double value;
};
bool operator < (const VectorItem& a,const VectorItem& b){
	return a.key < b.key;
}

class Vector:public map<int,double> {
public:
	Vector& operator /= (const double& c){
		for(map<int,double>::iterator it=this->begin();it!=this->end();++it){
			it->second/=c;
		}
		return *this;
	}
	Vector& operator += (const Vector& c){
		for(map<int,double>::const_iterator it=c.begin();it!=c.end();++it){
			(*this)[it->first]+=it->second;
		}
		return *this;
	}
	Vector& operator -= (const Vector& c){
		return *this;
	}
	Vector& operator *= (const Vector& c){
		return *this;
	}
};


Vector operator + (const Vector& a,const Vector& b){ 
	Vector ret = a;	
	ret += b;	
	return a;	
}
Vector operator / (const Vector& a,const double& b){ 
	Vector ret = a;	
	ret /= b;	
	return a;	
}

struct User{
	vector<int> sns;
	Vector scores;
};
ostream& operator << (ostream& out,const User u){
	//out<<"{";
	//out<<"sns=";
	out<<u.sns<<" ";
	//out<<"scores="
	out<<u.scores;
	//out<<"}";
	return out;
}

class UpdatorExample{
public:
	void operator()(map<int,User>& users,int user){
		Vector newScore ;
		for(int i=0;i<users.size();i++){
			newScore += users[i].scores;
		}
		newScore /= users.size();
		newScore = ( users[user].scores + newScore )/2;
		users[user].scores=newScore;
	}	
};

template <class Updator=UpdatorExample>
class Framework{
	Updator updator;
public:
	map<int,User> users; 
	void loadSNS(const char *file="../data/track1/user_sns.txt"){
		cerr<<__FUNCTION__<<" begins"<<endl;
		ifstream fin;	fin.open(file);
		int a,b;
		while(fin>>a>>b){
			users[a].sns.push_back(b);
		}
		cerr<<__FUNCTION__<<" ends"<<endl;
	}
	void solve(){
		cerr<<__FUNCTION__<<" begins"<<endl;
		for(map<int,User>::iterator it=users.begin();it!=users.end();it++){
			User& u =it->second;
			u.scores[it->first]=1;
		}
		for(int i=0;i<5;i++){
			for(int j=0;j<users.size();j++){
				updator(users,j);
			}
		}
		cerr<<__FUNCTION__<<" ends"<<endl;
	}
	void output(){
		cerr<<__FUNCTION__<<" begins"<<endl;
		for(map<int,User>::iterator it=users.begin();it!=users.end();it++){
			User& u =it->second;
			//vector<double> score
			cout<<u<<endl;
		}
		cerr<<__FUNCTION__<<" ends"<<endl;
	}
};

Framework<> framework;

int main(){
	framework.loadSNS();
	framework.solve();	
	framework.output();

	cerr<<"finished!"<<endl;
	return 0;
}
