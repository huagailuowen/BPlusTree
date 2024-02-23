#include <fstream>
#include <iostream>
#include <vector>
#include <map>



template <class key_t,class val_t,int M,int L,int totdatanum>
class BPlusTree {
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
    };
    
    class config{
    public:
        int root;
        int datahead;
        int dataend;
        int datacnt=0;
        int treecnt=0;
        config(){
            root = 0;
            datahead = 0;
            dataend = 0;
            datacnt=0;
            treecnt=0;
        }
    };
private:
    std::string datafile;
    std::string treefile;
    std::fstream file;
    std::map<int,int > father;
public:
    BPlusTree(std::string datafile,std::string treefile,bool isnew=false):datafile(datafile),treefile(treefile){
        if (isnew){
            //建立第一个节点，存储空    
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
            file.write(reinterpret_cast<char *>(&head), sizeof(innerTreeNode));
            file.close();
            
        }

    }
    //空间池

    //可以扩展缓存优化
    void getconfig(config &head){
        file.open(treefile, std::ios::in | std::ios::out);
        file.read(reinterpret_cast<char *>(&head), sizeof(config));
        file.close();
    }
    void setconfig(const config &head){
        file.open(treefile, std::ios::in | std::ios::out);
        file.write(reinterpret_cast<char *>(&head), sizeof(config));
        file.close();
    }
    void gettreefile(innerTreeNode &node,int pos){
        file.open(treefile, std::ios::in | std::ios::out);
        file.seekg(sizeof(config)+pos*sizeof(innerTreeNode));
        file.read(reinterpret_cast<char *>(&node), sizeof(innerTreeNode));
        file.close();
    }
    void settreefile(const innerTreeNode &node,int pos){
        file.open(treefile, std::ios::in | std::ios::out);
        file.seekp(sizeof(config)+pos*sizeof(innerTreeNode));
        file.write(reinterpret_cast<char *>(&node), sizeof(innerTreeNode));
        file.close();
    }
    void getdatafile(dataNode &node,int pos){
        file.open(datafile, std::ios::in | std::ios::out);
        file.seekg(pos*sizeof(dataNode));
        file.read(reinterpret_cast<char *>(&node), sizeof(dataNode));
        file.close();
    }
    void setdatafile(const dataNode &node,int pos){
        file.open(datafile, std::ios::in | std::ios::out);
        file.seekp(pos*sizeof(dataNode));
        file.write(reinterpret_cast<char *>(&node), sizeof(dataNode));
        file.close();
    }
    bool search(const key_t &key, val_t &value) {
        config Config;
        getconfig(Config);
        innerTreeNode nw;
        gettreefile(nw,Config.root);
        while (!nw.isLeaf) {
            int i = 0;
            while (i < nw.num-1 && key > nw.keys[i]) {
                i++;
            }
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
        if(j<datanw.num&&key==datanw.keys[j]){
            value = datanw.values[j];
            return true;
        }
        return false;

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
        if(datanw.num<L){
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
            // datanw.keys[i]=0;
        }
        datanw.num=(L+1)>>1;
        newdatanw.next=datanw.next;
        datanw.next=newdatanw.id;
        newdatanw.prev=datanw.id;
        setdatafile(datanw,datanw.id);
        setdatafile(newdatanw,newdatanw.id);
        if(newdatanw.next!=-1){
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
            if(nw.num<M){
                int k;
                for(k=nw.num;k>0&&nw.children[k-1]!=childid;k--){
                    nw.keys[k]=nw.keys[k-1];
                    nw.children[k]=nw.children[k-1];
                }
                nw.keys[k-1]=splitkey;
                nw.children[k]=childid;
                nw.num++;
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
            innerTreeNode parent(false);
            if(father[nw]==-1){
                parent.id=++Config.treecnt;
                Config.root=parent.id;
                //可加入内存回收策略
                parent.num=1;
                parent.children[0]=nw.id;
                father[parent]=-1;
            }else{
                gettreefile(parent,father[nw]);
            }
            settreefile(nw,nw.id);
            settreefile(newnw,newnw.id);
            nw=parent;
            childid=newnw.id;
            splitkey=nw.keys[((M+1)>>1)-1];
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
        for(int k=datanw.num-2;k>=j;k--){
            datanw.keys[k]=datanw.keys[k+1];
            datanw.values[k]=datanw.values[k+1];
        }
        datanw.num--;
        if(datanw.num>=(L>>1)){
            setdatafile(datanw,datanw.id);
            return;
        }
        //借用节点
        int place;
        for(place=0;place<nw.num&&nw.children[place]!=datanw.id;place++);
        if(place>0){
            dataNode prevdatanw;
            getdatafile(prevdatanw,datanw.prev);
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
        //合并
        

    }

    // 查找关键字
    
};

int main() {
    BPlusTree tree(3); // 创建一个度为3的B+树

    // 插入关键字
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);

    // 查找关键字
    bool found = tree.search(30);
    if (found) {
        std::cout << "Key 30 found in the B+ tree." << std::endl;
    } else {
        std::cout << "Key 30 not found in the B+ tree." << std::endl;
    }

    // 删除关键字
    tree.remove(30);

    return 0;
}