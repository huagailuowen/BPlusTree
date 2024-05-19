#include "src/BPlusTree.hpp"
// #include<bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#define DEBUG
// #define AA
#include "./src/testBPlusTree.hpp"
#include "./src/vector.hpp"
// #include "./src/save_work(right but not concurent).hpp"
using namespace std;
// #include "src/BPlusTree.hpp"
// using namespace sjtu;

BPlusTree<int, int,4, 4>A(std::string("datafile"),true);
// BPlusTree<int, int,4, 4>A("datafile",true);
map<int,int>mp;

bool pd()
{
    sjtu::vector<int>v1,v2;
    A.getallelement(v1,v2);
    if(v1.size()!=mp.size())return false;
    for(int i=0;i<v1.size();i++){
        if(mp.count(v1[i])==0)return false;
        if(mp[v1[i]]!=v2[i])return false;
    }
    return true;
}
int main()
{
    bool flag=1;
    //A.printconfig();
   srand(time(0));
    // A.file.open(A.treefile, std::ios::in | std::ios::out);
    // A.file.seekp(0, std::ios::end);
    // std::cerr<<A.file.tellp()<<endl;
    // A.file.close();
    // A.file.open(A.treefile, std::ios::in | std::ios::out);
    // A.file.seekp(0, std::ios::end);
    // std::cerr<<A.file.tellp()<<endl;
    // A.file.close();
    // A.printconfig();
    // getchar();
    
    // std::cerr<<"-------------------"<<endl;

    // // BPlusTree<int, int,4, 4>::innerTreeNode it;
    // // A.settreefile(it, 0);

    // std::cerr<<"-------------------"<<endl;
   // A.print_tree();


    // std::thread j(&BPlusTree<int, int,4, 4>::insert,&A,0,1);
    // std::thread jj(&BPlusTree<int, int,4, 4>::insert,&A,6,7);
    // std::thread jjj(&BPlusTree<int, int,4, 4>::remove,&A,6);
    // std::thread jjjj(&BPlusTree<int, int,4, 4>::remove,&A,3);
    
    // std::thread jjjjj(&BPlusTree<int, int,4, 4>::remove,&A,1);
    // std::thread jjjjjj(&BPlusTree<int, int,4, 4>::remove,&A,0);
    // std::thread jjj2(&BPlusTree<int, int,4, 4>::remove,&A,9);
    //         std::thread j1(&BPlusTree<int, int,4, 4>::insert,&A,9,1);

    // std::thread jj1(&BPlusTree<int, int,4, 4>::insert,&A,6,7);
    // std::thread jjj1(&BPlusTree<int, int,4, 4>::remove,&A,6);
    // std::thread jjjj1(&BPlusTree<int, int,4, 4>::remove,&A,3);

    // sleep(1);
    //     jjj2.join();
    // j.join();
    // jj.join();
    // jjj.join();
    // jjjj.join();
    // jjjjj.join();
    // jjjjjj.join();
    // j1.join();
    // jj1.join();
    // jjj1.join();
    // jjjj1.join();
    // A.print_tree();
    // return 0;
   int res;
   std::thread threads[100000];
    for(int T=1;T<=10000;T++){
        // A.printconfig();
        std::cerr<<T<<"\n";
        K:
        int tp=rand()%4;
        if(tp==0||tp==3&&flag){
            if(mp.size()>4500){flag=false;goto K;}
            Back:
            int x=rand()%5000;
            int y=rand()%5000;
            if(mp.count(x))goto Back;
            // std::cerr<<T<<"insert\n";
            A.insert(x,y);
            // std::cerr<<"|"<<threads[T].joinable()<<"\n";
            // threads[T]=std::thread(&BPlusTree<int, int,4, 4>::insert,&A,x,y);
            #ifdef AA
            threads[T].join();
            #endif
            // A.insert(x,y);
            // threads[T]->join();
            mp[x]=y;
        }
        else if(tp==1||tp==3&&!flag){
            // goto K;
            if(mp.size()<500){flag=true;goto K;}
            int x=rand()%5000;
            // std::cerr<<T<<"remove\n";
            std::cerr<<"|"<<threads[T].joinable()<<"\n";
            A.remove(x);
            // threads[T]=std::thread(&BPlusTree<int, int,4, 4>::remove,&A,x);

            // A.remove(x);
            // threads[T]=&j;
            // j.join();
            #ifdef AA
            threads[T].join();
            #endif
            mp.erase(x);
        }
        else{
            // goto K;
            int x=rand()%5000;
            auto it=mp.find(x);
            std::cerr<<"|"<<threads[T].joinable()<<"\n";
            // int res=-1;
            A.search(x,res);
            // threads[T]=std::thread(&BPlusTree<int, int,4, 4>::search,&A,x,std::ref(res[T]));
            #ifdef AA
            threads[T].join();
            #endif
            // threads[T]=&j;
            // j.join();

            std::cerr<<T<<"search\n";
            if(it==mp.end()){
                assert(res==-1);
            }
            else{
                if(res==-1){
                    std::cerr<<"hahahahaha";
                    return 0;
                }
                assert(res==it->second);
            }
        }
        if(T%1==0){
            cerr<<T<<':'<<tp<<' '<<mp.size()<<endl;
        }
        //if(!A.checktree()){
          //  getchar();
            //return 0;
        //}
        
        // if(!pd()){
        //     cout<<"error"<<endl;
        //     return 0;
        // }
        // A.print_buffer();
        // getchar();
        // A.print_tree();
        // std::cerr<<"-------------------"<<endl;
    }    
    // for(int i=1;i<=10000;i++){
    //     if(threads[i].joinable()){
    //         threads[i].join();
    //     }
    // }
    A.print_tree();std::cerr<<"$$";
    sleep(1);
    return 0;
}

