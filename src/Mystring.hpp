
#ifndef Mystring_HPP
#define Mystring_HPP
#include <string>
using std::string;

struct Mystring{
// #ifdef DEBUG
// private:
// #endif
    char c[65];int l=0;
public:
    Mystring()
    {c[0]='\0';l=0;}
    Mystring(string s){
        for(int i=0;i<s.size();i++)
            c[i]=s[i];
        l=s.size()+1;
        c[s.size()]='\0';
    }
    string tostr()
    {
        string s;
        for(int i=0;i<l;i++)
            s+=c[i];
        return s;
    }
    bool operator<(const Mystring &b)const
    {
        for(int i=0;i<std::max(l,b.l);i++){
            if(c[i]!=b.c[i])
                return c[i]<b.c[i];
        }
        return 0;
    }
    bool operator==(const Mystring &b)const
    {
        if(b.l!=l)return 0;
        for(int i=0;i<l;i++){
            if(c[i]!=b.c[i])
                return 0;
        }
        return 1;
    }
    bool operator>(const Mystring &b)const
    {
        return b<(*this);
    }
    bool operator>=(const Mystring &b)const
    {
        return !((*this)<b);
    }
    bool operator<=(const Mystring &b)const
    {
        return !((*this)>b);
    }
    bool operator!=(const Mystring &b)const
    {
        return !((*this)==b);
    }

};
#endif