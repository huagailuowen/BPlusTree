#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#define DEBUG
template <class key_t,class val_t,int M,int L>
class BPlusTree {
#ifdef DEBUG
public:
#endif 
    class dataNode{
    public:
        int id=0;
        int num;
        key_t keys[L+1];
        val_t values[L+1];
        int next;
        int prev;
        dataNode() {
            num=0;
            next = -1;
            prev = -1;
        }    
        #ifdef DEBUG
        void print()
        {
            std::cerr<<"--------\n";
            std::cerr<<"data:  "<<id<<std::endl;
            std::cerr<<"num:  "<<num<<std::endl;
            for(int i=0;i<num;i++){
                std::cerr<<keys[i]<<" ";
            }
            std::cerr<<std::endl;
            for(int i=0;i<num;i++){
                std::cerr<<values[i]<<" ";
            }
            std::cerr<<std::endl;
            std::cerr<<"next:  "<<next<<std::endl;
            std::cerr<<"prev:  "<<prev<<std::endl;
            std::cerr<<"--------\n";
        }
        #endif
    };
    class innerTreeNode {
    public:
        int id = 0;
        key_t keys[M+1];
        int children[M+1];
        bool isLeaf;
        int num;
        innerTreeNode(bool isLeafNode=false) {
            isLeaf = isLeafNode;
            num = 0;
        }
        #ifdef DEBUG
        void print()
        {
            std::cout<<"--------\n";
            std::cout<<"tree:  "<<id<<std::endl;
            std::cout<<"num:  "<<num<<std::endl;
            std::cout<<"isLeaf:  "<<isLeaf<<std::endl;
            for(int i=0;i<num-1;i++){
                std::cout<<keys[i]<<" ";
            }
            std::cout<<std::endl;
            for(int i=0;i<num;i++){
                std::cout<<children[i]<<" ";
            }
            std::cout<<"--------\n";
            
            
        }
        #endif
    };
    
    class config{
    public:
        int root;
        int datahead;
        int dataend;
        int vacantdatablock=-1;
        int vacanttreeblock=-1;
        //空间回收子系统
        int datacnt=0;
        int treecnt=0;
        config(){
            root = 0;
            datahead = 0;
            dataend = 0;
            datacnt=0;
            treecnt=0;
            vacantdatablock=-1;
            vacanttreeblock=-1;
        }
    };
private:
#ifdef DEBUG
public:
#endif 
    std::string datafile;
    std::string treefile;
    std::fstream file;
    static const int buffersize=5;
    innerTreeNode treebuffer[buffersize];
    dataNode databuffer[buffersize];
    //缓存系统
    std::map<int,int > father;


    std::map<int,int>test;
    std::map<int,int>testm;
    
public:
    #ifdef DEBUG
    void printconfig(){
        config Config;
        getconfig(Config);
        std::cout<<"root: "<<Config.root<<std::endl;
        std::cout<<"datahead: "<<Config.datahead<<std::endl;
        std::cout<<"dataend: "<<Config.dataend<<std::endl;
        std::cout<<"datacnt: "<<Config.datacnt<<std::endl;
        std::cout<<"treecnt: "<<Config.treecnt<<std::endl;
    }
    #endif
    void getallelement(std::vector<key_t>&key,std::vector<val_t>&value){
        key.clear();
        value.clear();
        config Config;
        getconfig(Config);
        dataNode datanw;
        getdatafile(datanw,Config.datahead);
        while(datanw.id!=Config.dataend){
            for(int i=0;i<datanw.num;i++){
                key.push_back(datanw.keys[i]);
                value.push_back(datanw.values[i]);
            }
            getdatafile(datanw,datanw.next);
        }
        for(int i=0;i<datanw.num;i++){
            key.push_back(datanw.keys[i]);
            value.push_back(datanw.values[i]);
        }

    }
    #ifdef DEBUG
    bool checktree()
    {
        //遍历树
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        dataNode datanw;
        int st[5000],h=0,t=0;
        st[0]=Config.root;
        int las=Config.datahead;
        bool flag=false;
        int mm=-1,MM=100000000;
        test[Config.root]=100000000;
        testm[Config.root]=-1;

        while(h<=t){
            int u=st[h++];
            gettreefile(nw,u);
            if(testm[u]>test[u]){
                std::cout<<"__error in tree structure1"<<std::endl;
                return false;
            }
            if(nw.num>1&&nw.keys[0]<testm[u]){
                std::cout<<"__error in tree structure3"<<std::endl;
                return false;
            }
            if(nw.num>1&&nw.keys[nw.num-2]>test[u]){
                std::cout<<"__error in tree structure2"<<std::endl;
                //!!!!!!
                nw.print();

                return false;
            }

            for(int i=0;i<nw.num;i++){
                if(i+2<nw.num&&nw.keys[i]>nw.keys[i+1]){
                    std::cout<<"__error in tree structur4"<<std::endl;
                    return false;
                }
                if(!nw.isLeaf){
                    st[++t]=nw.children[i];
                    test[nw.children[i]]=(i+1==nw.num)?test[nw.id]:nw.keys[i];
                    testm[nw.children[i]]=(i==0)?testm[nw.id]:nw.keys[i-1];
                }else{
                    if(!flag){
                        if(nw.children[i]!=las){
                            std::cout<<"error in tree structure"<<std::endl;
                            return false;
                        }else {
                            flag=true;
                            continue;
                        }
                    }
                    getdatafile(datanw,las);
                    if(datanw.next!=nw.children[i]){
                        std::cout<<"error in tree structrue"<<std::endl;
                        return false;
                    }
                    las=nw.children[i];
                    getdatafile(datanw,las);
                    mm=(i==0)?testm[nw.id]:nw.keys[i-1];
                    MM=(i+1==nw.num)?test[nw.id]:nw.keys[i];
                    for(int j=0;j<datanw.num;j++){
                        if(j+1<datanw.num&&datanw.keys[j]>datanw.keys[j+1]){
                            datanw.print();
                            std::cerr<<"__error in tree structur5"<<std::endl;
                            return false;
                        }
                        if(datanw.keys[j]<mm){
                            datanw.print();
                            std::cout<<"__error in tree structure6"<<std::endl;
                            return false;
                        }
                        if(datanw.keys[j]>MM){
                            std::cout<<"__error in tree structure7"<<std::endl;
                            return false;
                        }
                        
                    }
                }
            }
            
        }
        if(las!=Config.dataend){
            std::cout<<"error in tree structure"<<std::endl;
            return false;
        }
        return true;
    }
    void print_tree()
    {
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        dataNode datanw;
        int st[5000],h=0,t=0;
        st[0]=Config.root;
        int las=Config.datahead;
        bool flag=false;
        test[Config.root]=100000000;
        testm[Config.root]=-1;
        while(h<=t){
            int u=st[h++];
            gettreefile(nw,u);
            nw.print();
            for(int i=0;i<nw.num;i++){
                if(!nw.isLeaf){
                    st[++t]=nw.children[i];
                }else{
                    getdatafile(datanw,nw.children[i]);
                    datanw.print();
                }
            }
            
        }
    }
    #endif
    BPlusTree(std::string datafile,std::string treefile,bool isnew=false):datafile(datafile),treefile(treefile){
        for(int i=0;i<buffersize;i++){
            treebuffer[i].id=-1;
            databuffer[i].id=-1;
        }
        file.open(treefile, std::ios::app);
        if (isnew||file.tellp()==0){
            //建立第一个节点，存储空 
            file.close();   
            file.open(treefile, std::ios::out);
            config head;
            file.write(reinterpret_cast<char *>(&head), sizeof(config));
            innerTreeNode headtreenode(true);
            headtreenode.num=1;
            headtreenode.children[0]=0;
            file.write(reinterpret_cast<char *>(&headtreenode), sizeof(innerTreeNode));
            file.close();


            file.open(datafile, std::ios::out);
            dataNode headdatanode;
            headdatanode.num=0;
            file.write(reinterpret_cast<char *>(&headdatanode), sizeof(dataNode));
            
        }
        file.close();
    }
    ~BPlusTree(){

        for(int i=0;i<buffersize;i++){
            if(treebuffer[i].id!=-1){
                settreefile(treebuffer[i],treebuffer[i].id);
            }
            if(databuffer[i].id!=-1){
                setdatafile(databuffer[i],databuffer[i].id);
            }
        }
        #ifdef DEBUG
        print_tree();
        #endif
    }
    //空间池

    //可以扩展缓存优化
    void getconfig(config &head){
        file.open(treefile, std::ios::in | std::ios::out);
        file.read(reinterpret_cast<char *>(&head), sizeof(config));
        file.close();
    }
    void setconfig(config &head){
        file.open(treefile, std::ios::in | std::ios::out);
        file.write(reinterpret_cast<char *>(&head), sizeof(config));
        file.close();
    }
    void checkfilesize(int pos,bool is_tree)
    {
        // file.seekp(std::ios::beg);
        // file.open(is_tree?treefile:datafile, std::ios::in | std::ios::out);
        int fsize = file.tellp();
        file.seekp(0,std::ios::end);
        // std::cerr<<file.tellp()<<std::endl;
        fsize = (int)file.tellp() - fsize;
        size_t blocksize=is_tree?sizeof(innerTreeNode):sizeof(dataNode);
        // std::cerr<<(is_tree?"tree":"data")<<fsize<<" "<<pos<<" "<<blocksize<<std::endl;
        // getchar();
        if(fsize<sizeof(config)*is_tree+pos*blocksize){
            int times=(sizeof(config)*is_tree+(pos+1)*blocksize-fsize-1)/blocksize;
            for(int i=0;i<times;i++){
                if(is_tree){
                    innerTreeNode tmp;
                    file.write(reinterpret_cast<char *>(&tmp), blocksize);
                }else{
                    dataNode tmp;
                    file.write(reinterpret_cast<char *>(&tmp), blocksize);
                }
            }
        }
        // file.close();
    }
    void gettreefile(innerTreeNode &node,int pos){
        file.open(treefile, std::ios::in | std::ios::out);
        checkfilesize(pos,true);
        file.seekg(sizeof(config)+pos*sizeof(innerTreeNode),std::ios::beg);
        file.read(reinterpret_cast<char *>(&node), sizeof(innerTreeNode));
        file.close();
    }
    void settreefile(innerTreeNode &node,int pos){
        file.open(treefile, std::ios::in | std::ios::out);
        checkfilesize(pos,true);
        file.seekp(sizeof(config)+pos*sizeof(innerTreeNode),std::ios::beg);
        file.write(reinterpret_cast<char *>(&node), sizeof(innerTreeNode));
        file.close();
    }
    void buffergettreefile(innerTreeNode &node,int pos){
        //没有绑定同步设置，只是一个存档！！！
        for(int i=0;i<buffersize;i++){
            if(treebuffer[i].id==pos){
                node=treebuffer[i];
                return;
            }
        }
        settreefile(treebuffer[0],treebuffer[0].id);
        for(int i=0;i<buffersize-1;i++){
            treebuffer[i]=treebuffer[i+1];
        }
        gettreefile(node,pos);
        treebuffer[buffersize-1]=node;    
    }
    void buffersettreefile(innerTreeNode &node,int pos){
        for(int i=0;i<buffersize;i++){
            if(treebuffer[i].id==pos){
                treebuffer[i]=node;
                return;
            }
        }
        if(treebuffer[0].id!=-1){
            settreefile(treebuffer[0],treebuffer[0].id);
        }
        for(int i=0;i<buffersize;i++){
            treebuffer[i]=treebuffer[i+1];
        }
        treebuffer[buffersize-1]=node;
    }
    void getdatafile(dataNode &node,int pos){
        file.open(datafile, std::ios::in | std::ios::out);
        checkfilesize(pos,false);
        file.seekg(pos*sizeof(dataNode),std::ios::beg);
        file.read(reinterpret_cast<char *>(&node), sizeof(dataNode));
        file.close();
    }
    void setdatafile(dataNode &node,int pos){
        file.open(datafile, std::ios::in | std::ios::out);
        checkfilesize(pos,false);
        file.seekp(pos*sizeof(dataNode),std::ios::beg);
        file.write(reinterpret_cast<char *>(&node), sizeof(dataNode));
        file.close();
    }
    void buffergetdatafile(dataNode &node,int pos){
        for(int i=0;i<buffersize;i++){
            if(databuffer[i].id==pos){
                node=databuffer[i];
                return;
            }
        }
        setdatafile(databuffer[0],databuffer[0].id);
        for(int i=0;i<buffersize-1;i++){
            databuffer[i]=databuffer[i+1];
        }
        getdatafile(node,pos);
        databuffer[buffersize-1]=node;    
    }
    void buffersetdatafile(dataNode &node,int pos){
        for(int i=0;i<buffersize;i++){
            if(databuffer[i].id==pos){
                databuffer[i]=node;
                return;
            }
        }
        if(databuffer[0].id!=-1){
            setdatafile(databuffer[0],databuffer[0].id);
        }
        for(int i=0;i<buffersize;i++){
            databuffer[i]=databuffer[i+1];
        }
        databuffer[buffersize-1]=node;
    }
    bool search(const key_t &key, val_t &value) {
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        gettreefile(nw,Config.root);
        int depth=0;
        while (!nw.isLeaf) {
            int i = 0;
            while (i < nw.num-1 && key > nw.keys[i]) {
                i++;
            }
            gettreefile(nw,nw.children[i]);
            depth++;
            
            // if(key==33){
            //     std::cout<<nw.num<<" ||"<<std::endl;
            //     std::cout<<nw.children[0]<<" --"<<std::endl;
            //     std::cout<<nw.keys[0]<<""<<std::endl;

            //     std::cout<<nw.children[1]<<" --"<<std::endl;
            // }
        }
        int i = 0;
        while (i < nw.num-1 && key > nw.keys[i]) {
            i++;
        }
        depth++;
        // std::cout<<"depth: "<<depth<<std::endl;
        dataNode datanw;
        getdatafile(datanw,nw.children[i]);
        int j = 0;
        while (j < datanw.num && key > datanw.keys[j]) {
            j++;
        }
        if(j<datanw.num&&key==datanw.keys[j]){
            value = datanw.values[j];
            return true;
        }
        return false;

    }
    void searchall(const key_t &lower_bound,const key_t upper_bound,std::vector<val_t> &value)
    {
        value.clear();
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        gettreefile(nw,Config.root);
        while (!nw.isLeaf) {
            int i = 0;
            while (i < nw.num-1 && lower_bound > nw.keys[i]) {
                i++;
            }
            gettreefile(nw,nw.children[i]);
        }
        int i = 0;
        while (i < nw.num-1 && lower_bound > nw.keys[i]) {
            i++;
        }
        dataNode datanw;
        getdatafile(datanw,nw.children[i]);
        int j = 0;
        while (j < datanw.num && lower_bound > datanw.keys[j]) {
            j++;
        }
        while(datanw.id!=Config.dataend){
            for(int k=j;k<datanw.num;k++){
                if(datanw.keys[k]>upper_bound){
                    return;
                }
                value.push_back(datanw.values[k]);
            }
            getdatafile(datanw,datanw.next);
            j=0;
        }

        for(int k=j;k<datanw.num;k++){
            if(datanw.keys[k]>upper_bound){
                return;
            }
            value.push_back(datanw.values[k]);
        }
    }
    // 插入关键字
    void insert(const key_t &key,const val_t &value) {
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        gettreefile(nw,Config.root);
        father[nw.id]=-1;
        while (!nw.isLeaf) {
            int i = 0;
            while (i < nw.num-1 && key > nw.keys[i]) {
                i++;
            }
            father[nw.children[i]]=nw.id;
            gettreefile(nw,nw.children[i]);
        }
        int i = 0;
        while (i < nw.num-1 && key > nw.keys[i]) {
            i++;
        }
        int place=nw.children[i];
        dataNode datanw;
        getdatafile(datanw,nw.children[i]);
        
        
        int j = 0;
        while (j < datanw.num && key > datanw.keys[j]) {
            j++;
        }
        
        for(int k=datanw.num;k>j;k--){
            datanw.keys[k]=datanw.keys[k-1];
            datanw.values[k]=datanw.values[k-1];
        }
        datanw.keys[j]=key;
        datanw.values[j]=value;
        datanw.num++;
        if(datanw.num<=L){
            setdatafile(datanw,datanw.id);
            return;
        }
        dataNode newdatanw;
        newdatanw.id=++Config.datacnt;
        //可以加入内存回收策略
        for(int i=((L+1)>>1);i<datanw.num;i++){
            newdatanw.keys[i-((L+1)>>1)]=datanw.keys[i];
            newdatanw.values[i-((L+1)>>1)]=datanw.values[i];
            newdatanw.num++;
        }
        datanw.num=(L+1)>>1;
        newdatanw.next=datanw.next;
        datanw.next=newdatanw.id;
        newdatanw.prev=datanw.id;
        setdatafile(datanw,datanw.id);
        setdatafile(newdatanw,newdatanw.id);
        if(datanw.id!=Config.dataend){
            dataNode nextdatanw;
            getdatafile(nextdatanw,newdatanw.next);
            nextdatanw.prev=newdatanw.id;
            setdatafile(nextdatanw,nextdatanw.id);
        }else{
            Config.dataend=newdatanw.id;
        }
        
        //data部分完成
        //开始更新树
        bool flag=false;
        int childid=newdatanw.id;
        key_t splitkey=datanw.keys[((L+1)>>1)-1];
        //叶子层
        while(!flag){
            int k;
            for(k=nw.num;k>1&&nw.children[k-1]!=place;k--){
                nw.keys[k-1]=nw.keys[k-2];
                nw.children[k]=nw.children[k-1];
            }
            nw.keys[k-1]=splitkey;
            nw.children[k]=childid;
            nw.num++;
            if(nw.num<=M){
                
                settreefile(nw,nw.id);
                flag=true;
                break;
            }
            innerTreeNode newnw(nw.isLeaf);
            newnw.id=++Config.treecnt;
            for(int i=((M+1)>>1);i<nw.num;i++){
                newnw.keys[i-((M+1)>>1)]=nw.keys[i];
                newnw.children[i-((M+1)>>1)]=nw.children[i];
                newnw.num++;
            }
            nw.num=(M+1)>>1;


            //可加入内存回收策略
            //如果是新建的空间必须先写入，否则文件大小、读写头出问题
            settreefile(newnw,newnw.id);
            innerTreeNode parent(false);
            if(father[nw.id]==-1){
                parent.id=++Config.treecnt;
                Config.root=parent.id;
                //可加入内存回收策略
                parent.num=1;
                parent.children[0]=nw.id;
                father[parent.id]=-1;
                //如果是新建的空间必须先写入，否则文件大小、读写头出问题
                settreefile(parent,parent.id);
            }else{
                gettreefile(parent,father[nw.id]);
            }
            settreefile(nw,nw.id);
            settreefile(newnw,newnw.id);
            place=nw.id;
            childid=newnw.id;
            splitkey=nw.keys[((M+1)>>1)-1];
            nw=parent;//位置要对
        }
        setconfig(Config);
    }

    // 删除关键字
    void remove(const key_t &key) {
        
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        gettreefile(nw,Config.root);
        father[nw.id]=-1;
        while (!nw.isLeaf) {
            int i = 0;
            while (i < nw.num-1 && key > nw.keys[i]) {
                i++;
            }
            father[nw.children[i]]=nw.id;
            gettreefile(nw,nw.children[i]);
        }
        int i = 0;
        while (i < nw.num-1 && key > nw.keys[i]) {
            i++;
        }
        dataNode datanw;
        getdatafile(datanw,nw.children[i]);
        
        
        int j = 0;
        while (j < datanw.num && key > datanw.keys[j]) {
            j++;
        }
        if(j>=datanw.num||key!=datanw.keys[j]){
            return;
        }
        for(int k=j;k<datanw.num-1;k++){
            datanw.keys[k]=datanw.keys[k+1];
            datanw.values[k]=datanw.values[k+1];
        }
        datanw.num--;
        if(datanw.num>=(L>>1)){
            setdatafile(datanw,datanw.id);
            return;
        }
        //借用节点
        int place=i;
        if(place>0){
            dataNode prevdatanw;
            getdatafile(prevdatanw,datanw.prev);
            assert(datanw.prev==prevdatanw.id);
            assert(nw.children[place-1]==prevdatanw.id);
            if(prevdatanw.num>(L>>1)){
                for(int i=datanw.num;i>0;i--){
                    datanw.keys[i]=datanw.keys[i-1];
                    datanw.values[i]=datanw.values[i-1];
                }
                datanw.keys[0]=prevdatanw.keys[prevdatanw.num-1];
                datanw.values[0]=prevdatanw.values[prevdatanw.num-1];
                datanw.num++;
                prevdatanw.num--;
                setdatafile(datanw,datanw.id);
                setdatafile(prevdatanw,prevdatanw.id);
                nw.keys[place-1]=prevdatanw.keys[prevdatanw.num-1];
                settreefile(nw,nw.id);
                return;
            }
        }
        if(place<nw.num-1){
            dataNode nextdatanw;
            getdatafile(nextdatanw,datanw.next);
            assert(datanw.next==nextdatanw.id);
            assert(nw.children[place+1]==nextdatanw.id);
            if(nextdatanw.num>(L>>1)){
                datanw.keys[datanw.num]=nextdatanw.keys[0];
                datanw.values[datanw.num]=nextdatanw.values[0];
                datanw.num++;
                nextdatanw.num--;
                for(int i=0;i<nextdatanw.num;i++){
                    nextdatanw.keys[i]=nextdatanw.keys[i+1];
                    nextdatanw.values[i]=nextdatanw.values[i+1];
                }
                setdatafile(datanw,datanw.id);
                setdatafile(nextdatanw,nextdatanw.id);
                nw.keys[place]=datanw.keys[datanw.num-1];
                settreefile(nw,nw.id);
                return;
            }
        }
        
        int removeid;
        if(place>0){
            dataNode prevdatanw;
            getdatafile(prevdatanw,datanw.prev);
            for(int i=0;i<datanw.num;i++){
                prevdatanw.keys[prevdatanw.num+i]=datanw.keys[i];
                prevdatanw.values[prevdatanw.num+i]=datanw.values[i];
            }
            prevdatanw.num+=datanw.num;
            prevdatanw.next=datanw.next;
            if(datanw.id!=Config.dataend){
                dataNode nextdatanw;
                getdatafile(nextdatanw,datanw.next);
                nextdatanw.prev=prevdatanw.id;
                setdatafile(nextdatanw,nextdatanw.id);
            }else{
                Config.dataend=prevdatanw.id;
            }
            setdatafile(prevdatanw,prevdatanw.id);
            removeid=place;
        }else if(place<nw.num-1){
            dataNode nextdatanw;
            getdatafile(nextdatanw,datanw.next);
            for(int i=0;i<nextdatanw.num;i++){
                datanw.keys[datanw.num+i]=nextdatanw.keys[i];
                datanw.values[datanw.num+i]=nextdatanw.values[i];
            }
            datanw.num+=nextdatanw.num;
            datanw.next=nextdatanw.next;
            // assert(datanw.id!=Config.dataend);
            if(nextdatanw.id!=Config.dataend){
                dataNode nextnextdatanw;
                getdatafile(nextnextdatanw,nextdatanw.next);
                nextnextdatanw.prev=datanw.id;
                setdatafile(nextnextdatanw,nextnextdatanw.id);
            }else{
                Config.dataend=datanw.id;
            }
            setdatafile(datanw,datanw.id);
            removeid=place+1;
        }else{
            //不可能(除非删光了)
            setdatafile(datanw, datanw.id);
            setconfig(Config);
            return;
        }
        
        while(true){
            //不断向上合并直到不用再合并
            nw.keys[removeid-1]=nw.keys[removeid];//之前错了removeid是一个下标
            for(int i=removeid;i<nw.num-1;i++){
                nw.keys[i]=nw.keys[i+1];
                nw.children[i]=nw.children[i+1];
            }
            nw.num--;
            if(nw.num>=(M>>1)||father[nw.id]==-1){
                settreefile(nw,nw.id);
                break;
            }
            innerTreeNode parent;
            gettreefile(parent,father[nw.id]);
            assert(parent.id==father[nw.id]);
            for(place=0;place<parent.num&&parent.children[place]!=nw.id;place++);
            //借用节点
            if(place>0){
                innerTreeNode prevnw;
                gettreefile(prevnw,parent.children[place-1]);
                if(prevnw.num>(M>>1)){
                    for(int i=nw.num;i>0;i--){
                        nw.keys[i]=nw.keys[i-1];
                        nw.children[i]=nw.children[i-1];
                    }
                    nw.keys[0]=parent.keys[place-1];

                    nw.children[0]=prevnw.children[prevnw.num-1];
                    prevnw.num--;
                    parent.keys[place-1]=prevnw.keys[prevnw.num-1];

                    nw.num++;
                    settreefile(nw,nw.id);
                    settreefile(prevnw,prevnw.id);
                    settreefile(parent,parent.id);
                    break;
                }
            }
            if(place<parent.num-1){
                innerTreeNode nextnw;
                gettreefile(nextnw,parent.children[place+1]);
                if(nextnw.num>(M>>1)){

                    //bug take me a year!!!!!!!! nw.num-1
                    nw.keys[nw.num-1]=parent.keys[place];
                    nw.children[nw.num]=nextnw.children[0];
                    parent.keys[place]=nextnw.keys[0];
                    for(int i=0;i<nextnw.num-1;i++){
                        nextnw.keys[i]=nextnw.keys[i+1];
                        nextnw.children[i]=nextnw.children[i+1];
                    }
                    nextnw.num--;
                    nw.num++;
                    settreefile(nw,nw.id);
                    settreefile(nextnw,nextnw.id);
                    settreefile(parent,parent.id);
                    break;
                }

            }
            //合并
            if(place>0){
                innerTreeNode prevnw;
                gettreefile(prevnw,parent.children[place-1]);
                prevnw.keys[prevnw.num-1]=parent.keys[place-1];
                for(int i=0;i<nw.num;i++){
                    prevnw.keys[prevnw.num+i]=nw.keys[i];
                    prevnw.children[prevnw.num+i]=nw.children[i];
                }
                prevnw.num+=nw.num;
                settreefile(prevnw,prevnw.id);
                removeid=place;
                nw=parent;
            }else if(place<parent.num-1){
                innerTreeNode nextnw;
                gettreefile(nextnw,parent.children[place+1]);
                nw.keys[nw.num-1]=parent.keys[place];
                for(int i=0;i<nextnw.num;i++){
                    nw.keys[nw.num+i]=nextnw.keys[i];
                    nw.children[nw.num+i]=nextnw.children[i];
                }
                nw.num+=nextnw.num;
                settreefile(nw,nw.id);
                removeid=place+1;
                nw=parent;
            }else{
                //不可能(除非删光了)
                settreefile(nw, nw.id);
                break;
            }
        }

        setconfig(Config);
    }

    

    // 查找关键字
    
};

