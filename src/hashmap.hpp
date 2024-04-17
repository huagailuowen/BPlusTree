#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <iostream>
#include <cstring>
class string_hash_func
{
    static const int Mod=1e9+7,base=131;
    public:
    int operator()(std::string str)
    {
        int hash_val=0;
        for(int i=0;i<str.size();i++)
        {
            hash_val=(1ll*hash_val*base+str[i])%Mod;
        }
        return hash_val;
    }
};
template<class key_t,class value_t,int map_size,class hash_func>
class HashTable
{
    struct Node{
        key_t key;
        value_t value;
        Node *next;
        Node(){}
        Node(key_t key,value_t value):key(key),value(value),next(nullptr){}
    };
    Node *table[map_size];
    public:
    HashTable()
    {
        for(int i=0;i<map_size;i++)
        {
            table[i]=nullptr;
        }
    }
    void insert(key_t key,value_t value)
    {
        int hash_val=hash_func()(key);
        hash_val%=map_size;
        Node *new_node=new Node(key,value);
        new_node->next=table[hash_val];
        table[hash_val]=new_node;
    }
    bool search(key_t key,value_t &value)
    {
        int hash_val=hash_func()(key);
        hash_val%=map_size;
        Node *cur=table[hash_val];
        while(cur!=nullptr)
        {
            if(cur->key==key)
            {
                value=cur->value;
                return true;
            }
            cur=cur->next;
        }
        return false;
    }
    void erase(key_t key)
    {
        int hash_val=hash_func()(key);
        hash_val%=map_size;
        Node *cur=table[hash_val];
        if(cur==nullptr)return;
        if(cur->key==key)
        {
            table[hash_val]=cur->next;
            delete cur;
            return;
        }
        while(cur->next!=nullptr)
        {
            if(cur->next->key==key)
            {
                Node *delete_node=cur->next;
                cur->next=delete_node->next;
                delete delete_node;
                return;
            }
            cur=cur->next;
        }
    }
    ~HashTable()
    {
        for(int i=0;i<map_size;i++)
        {
            Node *cur=table[i];
            while(cur!=nullptr)
            {
                Node *delete_node=cur;
                cur=cur->next;
                delete delete_node;
            }
        }
    }
};

#endif