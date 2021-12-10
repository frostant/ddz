#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++) 
using namespace std;
typedef unsigned long long ul;
const ul hashBase=137;
const ul hashMod =1222827239;

struct node {
    int a,x,cards[20];
    void tyrs(){
        int ser,card[20]; 
        cout<<a<<endl; 
        rep(i,0,19) cout<<card[i]<<" ";
        cout<<endl;  
        rep(i,0,19) cout<<cards[i]<<" ";
        cout<<endl;  
        cout<<ser<<endl; 
    }
}uu;
// void test()
int main (){
    uu.tyrs(); 
    map<ul,int> mp;
    if(mp[12422]) cout<<"sg"<<endl; 
    if(!mp[12422]) cout<<"EG"<<endl;
    return 0; 
}