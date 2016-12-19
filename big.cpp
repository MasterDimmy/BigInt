/******************************************************************
GNU FREE LICENSE

**=============================**
||                             ||
|| 25.02.2007 - 18.02.2009     ||
||                             ||
|| Edel Dmitry's Big Int class ||
||                             ||
||            v1.7.2           ||
||                             ||
**=============================**

NOTE:   (big) A / B returns [A/B];
	no float numeric format


methods:
--------
reverse()
bool empty()
clear()
push_back(..)
push_front(..)
pop_back(..)
pop_front(..)
front()
back()
empty()
size() // без знака!
c_str()

norm() // deletes 0 in the begining

operations:
-----------
+, *, /, %, [], ++ , --, += , -=
<, ==, <=, >, >=, *= , /= , %= , >>= , <<=


History of changes:
-------------------
25.02.08 - created & main parts
28.02.08 - pop & push added (queue)
03.03.08 - +,- added
04.03.08 - norm() , devide , /, % ,  sign added
	       mistakes
19.11.08 - ~big() bug fixed
	       versions
20.11.08 - delete bug fixed
		   big(string a)
22.11.08 - *=, /= , %= , >>= , <<= added
20.03.08 - speed up optimizing
	  	   rude mistakes fix up
22.05.08 - unary - added
22.08.08 - fast suply , devide by 10 added
         - fast % by 1,2,4,8 added
26.08.08 - suply error fixed
         - fast errors fixed
		 - deviding speed up
23.01.09 - deviding redone
		 - [] operator set to rvalue
13.02.09 - reverse method added
18.02.09 - converted to class with private members

*************************************************************/

#include "big.h"

void logit(char *a)
{	
	OutputDebugStringA(a);	
	char fname[1024], fin[1024];	
	GetModuleFileName(0,fin,1024);	
	sprintf(fname,"%s.log",fin);	
	FILE *f = fopen(fname,"a");	
	if (!f) {		
		printf("Can\'t write to file %s!",fname);	
		ExitProcess(0);	
	}	
	fprintf(f,"%s\n",a);	
	fclose(f);	
}

//*************************************************************************************************

void big::reverse() {
	std::reverse(data.begin(),data.end());
}

void big :: norm()
{
while (front()==0) pop_front();
if (!size()) sign = 1;
}


big::big(int a)
{
 sign = a>=0 ? 1 : -1;
 a = abs(a);
 while (a>0)
 {
  push_front(a%10);
  a/=10;
 }
 norm();
 temp = NULL;
}


big::big(const char* a)
{
 int sz = strlen(a);
 if (sz==0) return;
 sign = (a[0]=='-' ? -1 : 1);
 char j = sign>0 ? 0 : 1;
 for (int i=0;i<sz-j;i++)
  push_back(a[i+j]-'0');
 norm();
 temp = NULL;
}


const char* big :: c_str() {
	if (empty()) return "0";

	int k = size();
	char j = sign>0 ? 0 : 1;

	if (temp) delete temp;
	temp = new char[k+j+1];

	temp[0] = sign>0 ? '0' : '-';
	for (int i=0;i<k;i++)
		temp[i+j] = data[i] + '0';
	temp[k+j] = '\0';

	return temp;
}


big big :: operator *= (big a)
{
 big &t = *this;
 if (t==0)
	 return 0; 
 t = t * a;
 return t;
}


big big :: operator /= (big a)
{
 big &t = *this;
 if (t==0)
	 return 0; 
 t = t / a;
 return t;
}


big big :: operator %= (big a)
{
 big &t = *this;
 if (t==0)
	 return 0; 
 t = t % a;
 return t;
}


big big :: operator >>= (int a)
{
 big &t = *this;
 t = t >> a;
 return t;
}


big big :: operator <<= (int a)
{
 big &t = *this;
 t = t << a;
 return t;
}


big big :: operator << (int a)
{
 big ret = *this;
 if (!a) return ret;

 for (int i=0;i<a;i++)
	 ret = ret*2;
 return ret;
}


big big :: operator >> (int a)
{
 big ret = *this;
 if (!a) return ret;
 for (int i=0;i<a;i++)
	 ret = ret / 2;
 return ret;
}


big big :: operator += (big a)
{
 big &t = *this;
 if (!a.size()) return t;

 t = t + a;
 return t;
}


big big :: operator -= (big a)
{
 big &t = *this;
 if (!a.size()) return t;
 t = t - a;
 return t;
}


big big :: operator ++ (int a)
{
 big t = *this;
 return t + (a==0 ? 1 : a);
}


big big :: operator -- (int a)
{
 big t = *this;
 return t - (a==0 ? 1 : a);
}


big & big :: operator = (big a)
{
	if (!a.size()) {
		data.clear();
		return *this;
	};

	sign = a.sign;
	data.assign(a.begin(),a.end());
	return *this;
}


big big :: operator - (big a)
{
	big ret = *this;
	if (!a.size()) return ret;

	if (sign>0 && a.sign<0)
	{
		a.sign = 1;
		ret = ret + a;	
		return ret;
	}

	if (sign<0 && a.sign>0)
	{
		a.sign = ret.sign = 1;
		ret = ret + a;	
		ret.sign = -1;
		return ret;
	}

	if (sign<0 && a.sign<0)
	{
		a.sign = ret.sign = 1;
		ret = a - ret;
		return ret;
	}

	if (ret<a)
 	{
		big q = ret;
		ret = a;
		a = q;
		ret.sign = -1;
	}
	
	int a1 = ret.size()-1;
	int a2 = a.size()-1;

	char p = 0;

	while (a2>=0 || p>0) {
	char d2 = a2>=0 ? a[a2] : 0;
	char d = ret.data[a1] - d2 - p;
	p = d<0 ? 1 : 0;
	ret.data[a1] = d>=0 ? d : 10+d;
	a2--;
	a1--;
	}
	
	ret.norm();

	return ret;
}


bool big :: operator == (big a)
{
 if (sign!=a.sign) return false;
 if (size()!=a.size()) return false;

 for (int i=0;i<size();i++)
	 if (data[i]!=a.data[i])
		 return false;

 return true;
}


bool big :: operator < (big a)
{
 bool ret = true;

 if (sign<a.sign) return ret;
 if (sign>a.sign) return !ret;

 if (sign<0) ret = !ret;

 int t = size();
 int t2 = a.size();

 if (t!=t2)
  return t < t2;

 for (int i=0;i<t;i++)
  if (data[i]>a.data[i])
   return !ret;
  else
   if (data[i]<a.data[i])
    return ret;
   else
	continue;

 return !ret;
}


bool big :: operator <= (big a)
{
 return (*this)<a || (*this)==a;
}


bool big :: operator != (big a)
{
 big &t = *this;
 return !(t==a);
}


bool big :: operator > (big a)
{
 big &t = *this;
 return !(t<a) && t!=a;
}


bool big :: operator >= (big a)
{
 norm();
 big &t = *this;
 return t>a || t==a;
}

        
tdevide* big::devide(big a)  // -------------------- DEVIDE -------------------------------
{
 if (!devide_ret.devider.empty() && !a.size()) {
	 bool ok = true;
	 if (devide_ret.devider.size()==a.size())
	 for (int i=0;i<devide_ret.devider.size();i++)
		 if (devide_ret.devider[i]!=a.data[i]) {
			 ok = false;
			 break;
		 }
	 if (ok) return &devide_ret;
 }

 if (!a.size()) devide_ret.devider.assign(a.data.begin(),a.data.end());

 if (a==0)
 {
  big t = *this;
  printf("Dividing %s by 0!\n",t.c_str());
  devide_ret.a[0] = devide_ret.b[0] = '0';
  devide_ret.a[1] = devide_ret.a[1] = '\0';
  return &devide_ret;
 }

 big t = *this;

 char sgn = 1;
 char c1 = t.sign;
 char c2 = a.sign;

 if (t.sign!=a.sign)
 	sgn = -1;

 t.sign = a.sign = 1;

 big reta = 0;
 big retb = 0;
 big retm = 0;

 if (t.size()-a.size()-1>0) {
	 int st = t.size()-a.size()-1;
	 reta = 1;
	 for (int i=0;i<st;i++)
		 reta.push_back(0);
 }

 do {
	reta = reta + retb;

	retb = 1;
	while ((reta + (retb*2)) * a <= t) 
		retb = retb * 2;

 } while ((reta+retb)*a <= t);
 
 if (sgn<0)
 {
	t.sign = c1;
	a.sign = c2;
	reta.sign = -1;
 }

 retb = t - reta * a;
 big a1 = a>=0 ? a : (a * (-1));

 while (retb<0)
 {
  	reta = reta + (reta < 0 ? -1 : 1);
	retb = retb + a1;
 }


 devide_ret.a = (char*)reta.c_str();
 devide_ret.b = (char*)retb.c_str();

 return &devide_ret;                                               
}


big big :: operator / (big a)   // ------------------------ / -----------------------
{
 big ret = *this;
 if (ret==0)
	 return 0; 
 if (ret<a)
	 return 0;
 if (ret==a)
	 return 1;

 // fast devide by 10
 if (a.size()>1 && ret.size()>1)
 while ((a.back()==0) && (ret.data.back()==0)) {
  a.pop_back();
  ret.data.pop_back();
 }

 if (ret==a) {
	return 1;
 }

 if (a==1) {
	 return ret;
 }

 return ret.devide(a)->a.c_str();
}


big big :: operator % (big a)  // ------------------------- % -------------------------
{
 if (*this==a)
	return 0;
 if (*this==1)
	 return a;

 //fast solving
 if (a==1)
	 return 0;
 if (a==10)
	 return back() % 10;
 if (a==2)
	 return (back() & 0x1);

 return devide(a)->b.c_str();
};


big big::operator * (int a)
{
	big ret = *this;
	if (!a) {
		ret.clear();
		ret = 0;
		return ret;
	}

	if (ret==0)
		return 0;
	if (ret==1)
		return a;

	while ((a%10)==0) {
		a = (int) (a / 10);
		ret.push_back(0);
	}

	char asign = a>=0 ? 1 : -1;

	if (size()<=0) return ret;
	
 	int s = 0;
	int a1 = ret.size()-1;

	while (a1>=0 || s>0) 
	{
		int d1 = a1>=0 ? ret.data[a1]*a : 0;	
		s += d1;
        	if (a1<0) ret.data.push_front(0);
		int k = a1>=0 ? a1 : 0;
		ret.data[k] = s % 10;
		s /= 10;
	    a1--;
	}
	
	ret.sign = sign * asign;
	ret.norm();
	
	return ret;
}


big big::operator * (big a)
{
	big ret = *this;
	if (!size() || !a.size()) return 0;
	if (ret==0)
		return 0;
	if (ret==1)
		return a;

	int a1 = size()-1;
	int p = 0;

	// fast suply on 10
	while (a.back()==0) {
		a.pop_back();
		ret.data.push_back(0);
		a1++;
	}

	big ret2 = 0;

	while (a1>=0)
	{
		big sp = a * ret.data[a1];

		for (int i=0;i<p;i++) 
			sp.push_back(0);

		ret2 = ret2 + sp;	
		p++;
		a1--;
	}

	ret2.sign = sign * a.sign;
	ret2.norm();

	return ret2;
}


char& big::operator[] (int k)
{
 if (k<0 || k>size()) {
  printf("Error in operator [%d]\n",k);  
  char c = 0xFF;
  return c;
 }
 return data[k];
}


big big::operator + (big a)
{
	big ret = *this;
	if (!a.size()) return ret;
	if (ret==0) {
		ret = a;
		return ret;
	}

	if (ret.sign<0 && a.sign>0) {
		ret.sign = 1;
		return (a-ret);
	}
		
	if (ret.sign>0 && a.sign<0) {
		a.sign = 1;
		return (ret-a);
	}

 	char sgn = sign;

	int s = 0;
	int a1 = ret.size()-1; // *this
	int a2 = a.size()-1; //a

	while (a1>=0 || a2>=0 || s>0)
	{
		int d1 = a1>=0 ? ret.data[a1] : 0;
		int d2 = a2>=0 ? a[a2] : 0;
		
		s += d1 + d2;

		if (a1<0) ret.data.push_front(0); 
		int k = a1>=0 ? a1 : 0;
		ret.data[k] = s%10;

		s/=10;
		a1--;
		a2--;
	}

	ret.sign = sgn;
	ret.norm();

	return ret;
}


// -----------------------------------------------------------------


