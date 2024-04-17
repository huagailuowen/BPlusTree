#include<bits/stdc++.h>
#include <cstdlib>
#include <iostream>

#include "./src/BPlusTree.hpp"
using namespace std;

BPlusTree<int, int,4, 4>A("datafile","treefile",true);
map<int,int>mp;

bool pd()
{
    vector<int>v1,v2;
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
    A.printconfig();
//    srand(time(0));
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
    A.print_tree();
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
            mp[x]=y;
        }
        else if(tp==1||tp==3&&!flag){
            // goto K;
            if(mp.size()<500){flag=true;goto K;}
            int x=rand()%5000;
            // std::cerr<<T<<"remove\n";
            A.remove(x);
            mp.erase(x);
        }
        else{
            // goto K;
            int x=rand()%5000;
            auto it=mp.find(x);
            int res=-1;
            A.search(x,res);
            // std::cerr<<T<<"search\n";
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
        if(!A.checktree()){
            getchar();
            return 0;
        }
        if(!pd()){
            cout<<"error"<<endl;
            return 0;
        }
        // A.print_buffer();
        // getchar();
        // A.print_tree();
        // std::cerr<<"-------------------"<<endl;
    }    
    return 0;
}

/*
--------
tree:  29
num:  2
isLeaf:  1
32765 
55 21 --------
--------
tree:  21
num:  2
isLeaf:  0
88 
7 20 --------
--------
tree:  7
num:  3
isLeaf:  0
33 56 
2 14 25 --------
--------
tree:  20
num:  4
isLeaf:  0
129 145 164 
6 12 19 27 --------
--------
tree:  2
num:  3
isLeaf:  0
6 16 
0 10 16 --------
--------
tree:  14
num:  2
isLeaf:  0
48 
1 24 --------
--------
tree:  25
num:  4
isLeaf:  0
66 73 80 
9 29 13 17 --------
--------
tree:  6
num:  4
isLeaf:  0
95 101 111 
3 22 28 11 --------
--------
tree:  12
num:  2
isLeaf:  0
135 
4 18 --------
--------
tree:  19
num:  2
isLeaf:  0
151 
5 23 --------
--------
tree:  27
num:  3
isLeaf:  0
170 180 
8 26 15 --------
--------
tree:  0
num:  2
isLeaf:  1
2 
0 15 --------
--------
data:  0
num:  2
0 2 
7 105 
next:  15
prev:  -1
--------
--------
data:  15
num:  3
3 4 6 
90 34 8 
next:  20
prev:  0
--------
--------
tree:  10
num:  3
isLeaf:  1
10 13 
20 46 1 --------
--------
data:  20
num:  2
9 10 
160 124 
next:  46
prev:  15
--------
--------
data:  46
num:  3
11 12 13 
6 126 193 
next:  1
prev:  20
--------
--------
data:  1
num:  2
14 16 
5 120 
next:  34
prev:  46
--------
--------
tree:  16
num:  4
isLeaf:  1
20 24 29 
34 41 19 32 --------
--------
data:  34
num:  2
17 20 
129 161 
next:  41
prev:  1
--------
--------
data:  41
num:  3
22 23 24 
50 116 139 
next:  19
prev:  34
--------
--------
data:  19
num:  3
25 28 29 
189 28 31 
next:  32
prev:  41
--------
--------
data:  32
num:  4
30 31 32 33 
45 19 34 125 
next:  4
prev:  19
--------
--------
tree:  1
num:  4
isLeaf:  1
35 38 45 
4 57 54 24 --------
--------
data:  4
num:  2
34 35 
11 75 
next:  57
prev:  32
--------
--------
data:  57
num:  3
36 37 38 
189 28 68 
next:  54
prev:  4
--------
--------
data:  54
num:  4
39 43 44 45 
109 125 2 40 
next:  24
prev:  57
--------
--------
data:  24
num:  2
46 48 
127 111 
next:  16
prev:  54
--------
--------
tree:  24
num:  3
isLeaf:  1
51 53 
16 27 58 --------
--------
data:  16
num:  3
49 50 51 
142 183 63 
next:  27
prev:  24
--------
--------
data:  27
num:  2
52 53 
15 156 
next:  58
prev:  16
--------
--------
data:  58
num:  3
54 55 56 
58 94 148 
next:  18
prev:  27
--------
--------
tree:  9
num:  2
isLeaf:  1
62 
18 30 --------
--------
data:  18
num:  3
57 59 60 
172 96 9 
next:  30
prev:  58
--------
--------
data:  30
num:  2
63 66 
125 74 
next:  55
prev:  18
--------
--------
tree:  29
num:  2
isLeaf:  1
32765 
55 21 --------
--------
data:  55
num:  3
67 68 69 
62 180 103 
next:  21
prev:  30
--------
--------
data:  21
num:  2
71 73 
159 53 
next:  33
prev:  55
--------
--------
tree:  13
num:  2
isLeaf:  1
77 
33 50 --------
--------
data:  33
num:  2
75 77 
168 165 
next:  50
prev:  21
--------
--------
data:  50
num:  2
78 79 
58 106 
next:  9
prev:  33
--------
--------
tree:  17
num:  2
isLeaf:  1
85 
9 37 --------
--------
data:  9
num:  4
81 83 84 85 
177 39 114 139 
next:  37
prev:  50
--------
--------
data:  37
num:  2
87 88 
149 128 
next:  3
prev:  9
--------
--------
tree:  3
num:  2
isLeaf:  1
91 
3 42 --------
--------
data:  3
num:  2
89 90 
13 182 
next:  42
prev:  37
--------
--------
data:  42
num:  4
92 93 94 95 
132 157 12 179 
next:  14
prev:  3
--------
--------
tree:  22
num:  2
isLeaf:  1
97 
14 52 --------
--------
data:  14
num:  2
96 97 
47 189 
next:  52
prev:  42
--------
--------
data:  52
num:  3
99 100 101 
148 119 16 
next:  31
prev:  14
--------
--------
tree:  28
num:  2
isLeaf:  1
107 
31 53 --------
--------
data:  31
num:  3
103 106 107 
165 34 107 
next:  53
prev:  52
--------
--------
data:  53
num:  2
108 110 
187 194 
next:  7
prev:  31
--------
--------
tree:  11
num:  4
isLeaf:  1
115 119 124 
7 23 13 40 --------
--------
data:  7
num:  2
113 115 
15 89 
next:  23
prev:  53
--------
--------
data:  23
num:  2
116 118 
7 82 
next:  13
prev:  7
--------
--------
data:  13
num:  3
120 121 122 
126 69 102 
next:  40
prev:  23
--------
--------
data:  40
num:  3
126 127 129 
88 60 22 
next:  2
prev:  13
--------
--------
tree:  4
num:  2
isLeaf:  1
133 
2 5 --------
--------
data:  2
num:  3
130 132 133 
191 174 13 
next:  5
prev:  40
--------
--------
data:  5
num:  2
134 135 
100 53 
next:  38
prev:  2
--------
--------
tree:  18
num:  3
isLeaf:  1
138 141 
38 25 29 --------
--------
data:  38
num:  3
136 137 138 
180 4 117 
next:  25
prev:  5
--------
--------
data:  25
num:  3
139 140 141 
88 160 112 
next:  29
prev:  38
--------
--------
data:  29
num:  3
143 144 145 
36 165 72 
next:  10
prev:  25
--------
--------
tree:  5
num:  2
isLeaf:  1
147 
10 48 --------
--------
data:  10
num:  2
146 147 
156 4 
next:  48
prev:  29
--------
--------
data:  48
num:  2
148 150 
191 124 
next:  12
prev:  10
--------
--------
tree:  23
num:  3
isLeaf:  1
155 159 
12 45 47 --------
--------
data:  12
num:  2
154 155 
82 165 
next:  45
prev:  48
--------
--------
data:  45
num:  2
156 159 
158 112 
next:  47
prev:  12
--------
--------
data:  47
num:  3
160 162 164 
19 193 147 
next:  17
prev:  45
--------
--------
tree:  8
num:  2
isLeaf:  1
168 
17 22 --------
--------
data:  17
num:  3
166 167 168 
83 166 38 
next:  22
prev:  47
--------
--------
data:  22
num:  2
169 170 
140 38 
next:  56
prev:  17
--------
--------
tree:  26
num:  3
isLeaf:  1
173 177 
56 36 51 --------
--------
data:  56
num:  3
171 172 173 
65 114 187 
next:  36
prev:  22
--------
--------
data:  36
num:  2
174 175 
135 159 
next:  51
prev:  56
--------
--------
data:  51
num:  3
178 179 180 
8 150 158 
next:  8
prev:  36
--------
--------
tree:  15
num:  4
isLeaf:  1
183 191 195 
8 28 11 39 --------
--------
data:  8
num:  3
181 182 183 
113 72 61 
next:  28
prev:  51
--------
--------
data:  28
num:  4
187 188 190 191 
82 37 28 64 
next:  11
prev:  8
--------
--------
data:  11
num:  3
192 193 195 
154 112 55 
next:  39
prev:  28
--------
--------
data:  39
num:  2
198 199 
141 194 
next:  -1
prev:  11
--------


*/