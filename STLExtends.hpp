#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
using std::map;
using std::ostream;
using std::vector;
using std::lower_bound;
using std::cerr;

inline ostream& LOG(){
    time_t t;
    time(&t);
    return cerr<<asctime(localtime(&t));
}

template <class T>
unsigned int getIndex(const T a[],int n,const T& value) {
    int index =lower_bound(a,a+n,value) -a;
    if(index<n && a[index]==value){
        return index;
    }
    return -1;
}

template <class K,class V>
ostream& operator << (ostream& out,const map<K,V>& m){
	for(typename map<K,V>::const_iterator it=m.begin();it!=m.end();++it){
		out<<" "<<it->first<<":"<<it->second<<" ";
	}
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

template<class T,class B>
T operator + (const T& a,const B& b){ 
	T ret = a;	
	ret += b;	
	return ret;	
}
template<class T,class B>
T operator - (const T& a,const B& b){ 
	T ret = a;	
	ret -= b;	
	return ret;	
}
template<class T,class B>
T operator * (const T& a,const B& b){ 
	T ret = a;	
	ret *= b;	
	return ret;	
}
template<class T,class B>
T operator / (const T& a,const B& b){ 
	T ret = a;	
	ret /= b;	
	return ret;	
}



