#include "src/testBPlusTree.hpp"
#include "./src/Mystring.hpp"
// #include "./src/vector.hpp"
#include <iostream>
#include <string>
#include <cstring>
int TIME=0;
unsigned long long hashh(const Mystring &s){
    unsigned long long res=0;
    for(int i=0;s.c[i];i++){
        res=res*131+(unsigned long long)s.c[i];
    }
    return res;
}

    const int MAXblocknum=3000;
    const int blocklength=3000;

    using namespace std;
    int main()
    {
        // const Mystring a("const323233");
        // Mystring b(a);
        // a.c[1]='8';
        // cout<<a.tostr()<<' '<<b.tostr()<<'\n';
        // std::cerr<<"start\n";
        sjtu::BPlusTree<sjtu::pair<unsigned long long, int>, int, 50, 50>A("bptfile",false);
        int T;cin>>T;
        // cout<<T<<'\n';
        while(T--){
            string s;string a;int b;
            cin>>s;
            if(s=="insert"){
                cin>>a>>b;
                // cout<<a<<b;
                A.insert(sjtu::make_pair(hashh(Mystring(a)),b), b);
            }
            if(s=="delete"){
                cin>>a>>b;
                A.remove(sjtu::make_pair(hashh(Mystring(a)), b));
            }
            if(s=="find"){
                cin>>a;//cout<<"|||";
                sjtu::vector<int>v;
                A.searchall(sjtu::make_pair(hashh(Mystring(a)), 0), sjtu::make_pair(hashh(Mystring(a)), 1000000),v);
                if(v.empty())cout<<"null";
                else{
                    for(int i=0;i<v.size();i++)
                        cout<<v[i]<<(i+1==v.size()?"":" ");
                }
                cout<<'\n';
            }
        }
            // int res;
            // A.search(sjtu::make_pair(Mystring(string("CppPrimer")), 2012), res);
            // cout<<res<<'\n';
            // A.printconfig();
            // vector<int>v;
            // A.searchall(sjtu::make_pair(Mystring("Dune"), 0), sjtu::make_pair(Mystring("Dune"), 1000000),v);
                
        // for(int i=1;i<=1000;i++){
        //     A.insert(rand()%100, i);

        // }
        // vector<int >v=A.find(6);
        // // cout<<v.size();
        // for(auto u:v){
        //     cout<<u<<'\n';
        // }
        // A.del(6,137);
        // A.del(6,137);
        // A.del( 6,207);
        // A.del( 6,740);
        // A.del( 6,887);
        // // cerr<<"4444";
        // v=A.find(6); v 
        // // cout<<v.size();
        // for(auto u:v){
        //     cout<<u<<'\n';
        // }
        
        return 0;
    }
    /*
    4
    insert FlowersForAlgernon 1966
    insert CppPrimer 2012
    insert Dune 2021
    insert CppPrimer 2001
    find CppPrimer
    find Java
    delete CppPrimer 2012
    find CppPrimer
    */


    // #include<bits/stdc++.h>
    // #include "utity.hpp"
    // int main() {
    //     BPlusTree <int,int,50,50,100> tree("datafile","treefile",true);
    //     for(int i=1;i<=50;i++){
    //         tree.insert(i,i);
    //     }
        
        
    //     int res;
    //     tree.search(1,res);

    //     std::cout<<res<<std::endl;

    //     tree.search(2,res);
    //     std::cout<<res<<std::endl;
    //     tree.search(3,res);
    //     std::cout<<res<<std::endl;
    //     tree.search(4,res);
    //     std::cout<<res<<std::endl;
    //     tree.search(5,res);
    //     std::cout<<res<<std::endl;
    //     res=-1;
    //     tree.remove(1);
    //     tree.search(1,res);
    //     std::cout<<res<<std::endl;
    //     // tree.printconfig();//灵异事件？？？
    //     std::cout<<"-------------------\n";
    //     res=-1;
    //     tree.remove(5);
    //     tree.search(5,res);
    //     std::cout<<res<<std::endl;
    //     // tree.printconfig();
    //     std::cout<<"-------------------\n";

    //     res=-1;
    //     tree.search(45,res);
    //     std::cout<<res<<std::endl;
    //     res=-1;
    //     tree.remove(5);
    //     tree.search(5,res);
    //     std::cout<<res<<std::endl;
    //     tree.printconfig();
    //     std::cout<<"-------------------\n";
        
    //     // res=-1;
    //     // tree.search(-2,res);
    //     // tree.printconfig();
    //     // std::cout<<res<<std::endl;

    //     for(int i=1;i<=49;i++){
    //         tree.remove(i);
    //     }
    //     for(int i=1;i<=49;i++){
    //         tree.insert(i,i+1);
    //     }
        
    //     tree.search(50, res);
    //     std::cout<<res<<std::endl;
    //     tree.search(30, res);
    //     std::cout<<res<<std::endl;
    //     tree.search(40, res);
    //     std::cout<<res<<std::endl;
        
    //     tree.printconfig();
    //     return 0;
    // }