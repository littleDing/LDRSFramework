#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "STLExtends.hpp"
#include "Vector.h"
#include <algorithm>
using namespace std;
struct RelationShip {
    bool followed;
    short at;
    short retweet;
    short comment;
};
ostream& operator << (ostream& out,const RelationShip& r){
    
    return out;
}

struct User{
	map<int,RelationShip> sns;
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

void logRecordLoaded(int& cnt){
    cnt++;
    if(cnt%1000000==0){
        LOG()<<cnt<<" record loaded"<<endl;
    }
}

class Solver {
    vector<User> users;
    vector<int> ids;
    int tranID(const int& origin){
        return lower_bound(ids.begin(),ids.end(),origin)-ids.begin();
    }
public:
    void loadIDs(const char *file="../data/track1/user_id.txt"){
		LOG()<<__FUNCTION__<<" begins"<<endl;
        int cnt=0,id,n=2000000;
		ifstream fin;	fin.open(file);
        //fin>>n;
        ids.resize(n);
		while(fin>>id){
			ids.push_back(id);
            logRecordLoaded(cnt);
        }
        users.resize(ids.size());
		LOG()<<__FUNCTION__<<" ends"<<endl;
    }
    void loadSNS(const char *file="../data/track1/user_sns.txt"){
		LOG()<<__FUNCTION__<<" begins"<<endl;
        int cnt=0;
		ifstream fin;	fin.open(file);
		int a,b;
		while(fin>>a>>b){
            a=tranID(a); b=tranID(b);
			users[a].sns[b].followed=true;
            cnt++;
            logRecordLoaded(cnt);
        }
		LOG()<<__FUNCTION__<<" ends"<<endl;
	}
    void loadAction(const char *file="../data/track1/user_action.txt"){
		LOG()<<__FUNCTION__<<" begins"<<endl;
		ifstream fin;	fin.open(file);
		int a,b,cnt=0;
		while(fin>>a>>b){
            a=tranID(a); b=tranID(b);
            fin>>users[a].sns[b].at;
            fin>>users[a].sns[b].retweet;
            fin>>users[a].sns[b].comment;
            logRecordLoaded(cnt);
		}
		LOG()<<__FUNCTION__<<" ends"<<endl;
	}
    void loadAll(){
        loadIDs();
        loadSNS();
        loadAction();
    }
}solver;


int main(){
	LOG()<<__FUNCTION__<<" begins"<<endl;
    
    solver.loadAll();
    
	LOG()<<__FUNCTION__<<" ends"<<endl;
	return 0;
}
