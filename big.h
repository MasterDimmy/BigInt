/*
	GNU FREE LICENSE
*/
#pragma once

#ifndef BIG_H
#define BIG_H

/*
	for Edel's BigInt 1.7.2 & higher
*/

#include <Windows.h>

#include <cstdio>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

#define abs(a) ((a)>0?(a):-(a));
void logit(char *);


struct tdevide {
	string a; // div  /
	string b; // qout %
	deque <char> devider;
	tdevide() {};
	~tdevide() {}
};

class big {
private:
	// inner
	deque <char> data;
	char sign; // = 1 if >= 0 
	// =-1 if <  0

	char *temp;

public:
	// constructor & destrutor
	big() { 
		sign=1; 
		temp=NULL; 
	};
	big(int a);
	big(const big &a) {
		sign = a.sign;
		data.assign(a.data.begin(),a.data.end());
		temp = NULL;
	};
	big(const char * a);
	~big() { 
		data.clear(); 
		if (temp) delete temp;
		temp = NULL;
	};

	// methods
	const char* c_str();
	int size() { return data.size(); };
	deque <char> :: iterator begin() { return data.begin(); };
	deque <char> :: iterator end() { return data.end(); };

	bool empty() { return size() ? 0 : 1; };
	void clear() { data.clear(); sign=1; };
	void push_back(int k) { data.push_back(k); };
	void push_front(int k) { data.push_front(k); };
	void pop_back() { data.pop_back(); };
	void pop_front() { data.pop_front(); };
	char front() { return empty() ? -1 : data[0]; };
	char back() { return empty() ? -1 : data.back(); };
	void reverse();	// переворачивает

	tdevide devide_ret;
	tdevide* devide(big a);
	void norm();	// normilize

	// operators
	// unary
	big operator - () {
		big ret = *this;
		ret.sign = -ret.sign;
		return ret;
	}
	big operator !() {
		if (*this==0)
			return 1;
		else
			return 0;
		return *this;
	}

    //binary
	big operator + (big a);
	friend big operator + (int a,big b) {
		return b + (big)a;
	}
	big operator - (big a);
	friend big operator - (int a,big b) {
		return (big)a - b;
	}
	big operator * (big a);
	friend big operator * (int a,big b) {
		return b * (big)a;
	}
	big operator * (int a);
	big operator / (big a);
	friend big operator / (int a,big b) {
		return (big)a / b;
	}
	big operator % (big a);
	friend big operator % (int a,big b) {
		return (big)a % b;
	}
	big operator ++ (int a);
	big operator -- (int a);
	big operator << (int a);
	big operator >> (int a);
	big operator += (big a);
	big operator -= (big a);
	big operator *= (big a);
	big operator /= (big a);
	big operator %= (big a);
	big operator >>= (int a);
	big operator <<= (int a);


	big & operator = (big a);
	char& operator[] (int k);

	bool operator < (big a);  //main
	bool operator == (big a); //main
	bool operator <= (big a);
	bool operator != (big a);
	bool operator > (big a);
	bool operator >= (big a);
};


#endif
