#pragma once
#include "STLExtends.hpp"
using namespace std;

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
