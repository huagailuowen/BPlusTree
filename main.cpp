    // #include<bits/stdc++.h>
#include <fstream>
#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP
#include<memory>
// using namespace sjtu;
namespace sjtu {

/**
 * a container like priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
// public:
	struct Node{
		T val;
		Node *left, *right;
		Node(){left=right=nullptr;}
		Node(const T &val):val(val){left=right=nullptr;}
	};

	Node *root;
	int siz=0;
public:
	/**
	 * TODO constructors
	 */
	priority_queue() {root=nullptr;siz=0;}
	Node * queue_copy(Node *const node)
	{
		if(node == nullptr)
			return nullptr;
		Node *new_node = new Node(node->val);
		new_node->left = queue_copy(node->left);
		new_node->right = queue_copy(node->right);
		return new_node;
	}
	priority_queue(const priority_queue &other) {
		root = queue_copy(other.root);
		siz = other.siz;
	}
	/**
	 * TODO deconstructor
	 */
	void queue_delete(Node *node)
	{
		if(node == nullptr)
			return;
		queue_delete(node->left);
		queue_delete(node->right);
		delete node;
	}
	~priority_queue() {
		queue_delete(root);
	}
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other) {
		if(this == &other)
			return *this;
		queue_delete(root);
		root = queue_copy(other.root);
		siz = other.siz;
		return *this;
	}
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
		if(root == nullptr)
			;// throw container_is_empty();
		return root->val;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	Node * queue_merge(Node *first, Node *second)
	{
		if(first == nullptr)
			return second;
		if(second == nullptr)
			return first;
		if(Compare()(first->val,second->val))
			std::swap(first,second);
		// try{
		first->right = queue_merge(first->right,second);
		// }catch(...){
		// 	throw "!!";
		// }
		std::swap(first->left,first->right);
		return first;
	}
	void push(const T &e) {
		Node *new_node = new Node(e);
		if(root == nullptr)
		{
			root = new_node;
			siz++;
			return;
		}
		try{
			root =queue_merge(root,new_node);
		}catch(...){
			delete new_node;
			return;
		}
		siz++;
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
		if(root == nullptr)
			;//throw container_is_empty();
		Node *left = root->left;
		Node *right = root->right;
		Node *target=root;
		try{
			root = queue_merge(left,right);
		}catch(...){
			return;
		}
		delete target;
		siz--;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
		return siz;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
		return root == nullptr;
	}
	/**
	 * merge two priority_queues with at most O(logn) complexity.
	 * clear the other priority_queue.
	 */
	void merge(priority_queue &other) {
		try{
			root = queue_merge(root,other.root);
		}catch(...){
			return;
		}
		siz += other.siz;
		other.root = nullptr;
		other.siz = 0;
	}
};

}
namespace sjtu {
/**
 * a data container like vector
 * store data in a successive memory and support random access.
 */
template <typename T> class vector {
public:
  /**
   * TODO
   * a type for actions of the elements of a vector, and you should write
   *   a class named const_iterator with same interfaces.
   */
  /**
   * you can see RandomAccessIterator at CppReference for help.
   */

  class const_iterator;
  class iterator {
    // The following code is written for the C++ type_traits library.
    // Type traits is a C++ feature for describing certain properties of a type.
    // For instance, for an iterator, iterator::value_type is the type that the
    // iterator points to.
    // STL algorithms and containers may use these type_traits (e.g. the
    // following typedef) to work properly. In particular, without the following
    // code,
    // @code{std::sort(iter, iter1);} would not compile.
    // See these websites for more information:
    // https://en.cppreference.com/w/cpp/header/type_traits
    // About value_type:
    // https://blog.csdn.net/u014299153/article/details/72419713 About
    // iterator_category: https://en.cppreference.com/w/cpp/iteratover
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::output_iterator_tag;

  private:
    /**
     * TODO add data members
     *   just add whatever you want.
     */
    pointer ptr;
    pointer vec;

  public:
    /**
     * return a new iterator which pointer n-next elements
     * as well as operator-
     */
    iterator(pointer p, pointer vec) : ptr(p), vec(vec) {}
    iterator operator+(const int &n) const {
      // TODO
      iterator res(*this);
      res.ptr += n;
      return res;
    }
    iterator operator-(const int &n) const {
      // TODO
      iterator res(*this);
      res.ptr -= n;
      return res;
    }
    // return the distance between two iterators,
    // if these two iterators point to different vectors, ;//throw
    // invaild_iterator.
    int operator-(const iterator &rhs) const {
      // TODO
      if (vec != rhs.vec)
        ;//throw invalid_iterator();
      else
        return ptr - rhs.ptr;
    }
    iterator &operator+=(const int &n) {
      // TODO
      ptr += n;
      return *this;
    }
    iterator &operator-=(const int &n) {
      // TODO
      ptr -= n;
      return *this;
    }
    /**
     * TODO iter++
     */
    iterator operator++(int) {
      iterator res(*this);
      ptr++;
      return res;
    }
    /**
     * TODO ++iter
     */
    iterator &operator++() {
      ptr++;
      return *this;
    }
    /**
     * TODO iter--
     */
    iterator operator--(int) {
      iterator res(*this);
      ptr--;
      return res;
    }
    /**
     * TODO --iter
     */
    iterator &operator--() {
      ptr--;
      return *this;
    }
    /**
     * TODO *it
     */
    T &operator*() const { return *ptr; }
    /**
     * a operator to check whether two iterators are same (pointing to the same
     * memory address).
     */
    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }
    /**
     * some other operator for iterator.
     */
    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
  };
  /**
   * TODO
   * has same function as iterator, just for a const object.
   */
  class const_iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::output_iterator_tag;

  private:
    /*TODO*/

    const T *ptr;
    const T *vec;

  public:
    const_iterator(const pointer p, const pointer vec) : ptr(p), vec(vec) {}
    operator iterator() const { return iterator(ptr, vec); }
    const_iterator operator+(const int &n) const {
      const_iterator res(*this);
      res.ptr += n;
      return res;
    }
    const_iterator operator-(const int &n) const {
      const_iterator res(*this);
      res.ptr -= n;
      return res;
    }
    int operator-(const const_iterator &rhs) const {
      if (vec != rhs.vec)
        ;//throw invalid_iterator();
      return ptr - rhs.ptr;
    }
    const_iterator &operator+=(const int &n) {
      ptr += n;
      return *this;
    }
    const_iterator &operator-=(const int &n) {
      ptr -= n;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator res(*this);
      ptr++;
      return res;
    }
    const_iterator &operator++() {
      ptr++;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator res(*this);
      ptr--;
      return res;
    }
    const_iterator &operator--() {
      ptr--;
      return *this;
    }
    const T &operator*() const { return *ptr; }
    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }
    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
  };
  size_t max_size, current_size;
  T *begin_ptr;
  /**
   * TODO Constructs
   * At least two: default constructor, copy constructor
   */
  std::allocator<T> alloc;
  vector() : max_size(0), current_size(0), begin_ptr(nullptr) {}
  vector(size_t n)
      : max_size(n), current_size(n), begin_ptr(alloc.allocate(n)) {}
  vector(size_t n, const T &value)
      : max_size(n), current_size(n), begin_ptr(new T(n)) {
    for (size_t i = 0; i < n; i++) {
      begin_ptr[i] = value;
    }
  }
  vector(const vector &other) {
    max_size = other.max_size;
    current_size = other.current_size;
    begin_ptr =new T[max_size];
    for (size_t i = 0; i < current_size; i++) {
		begin_ptr[i]=other.begin_ptr[i];
    }
  }
  /**
   * TODO Destructor
   */
  ~vector() {
    delete [] begin_ptr;
  }
  /**
   * TODO Assignment operator
   */
  vector &operator=(const vector &other) {
    if (this == &other)
      return *this;
    delete [] begin_ptr;

    max_size = other.max_size;
    current_size = other.current_size;
	begin_ptr=new T[max_size];
    for (size_t i = 0; i < current_size; i++) {
		begin_ptr[i]=other.begin_ptr[i];
    }
    return *this;
  }
  /**
   * assigns specified element with bounds checking
   * ;//throw index_out_of_bound if pos is not in [0, size)
   */
  T &at(const size_t &pos) {
    if (pos < 0 || pos >= current_size)
      ;//throw index_out_of_bound();
    return *(begin_ptr + pos);
  }
  const T &at(const size_t &pos) const {
    if (pos < 0 || pos >= current_size)
      ;//throw index_out_of_bound();
    return *(begin_ptr + pos);
  }
  /**
   * assigns specified element with bounds checking
   * ;//throw index_out_of_bound if pos is not in [0, size)
   * !!! Pay attentions
   *   In STL this operator does not check the boundary but I want you to do.
   */
  T &operator[](const size_t &pos) {
    if (pos < 0 || pos >= current_size)
      ;//throw index_out_of_bound();
    return *(begin_ptr + pos);
  }
  const T &operator[](const size_t &pos) const {
    if (pos < 0 || pos >= current_size)
      ;//throw index_out_of_bound();
    return *(begin_ptr + pos);
  }
  /**
   * access the first element.
   * ;//throw container_is_empty if size == 0
   */
  const T &front() const {
    if (current_size == 0)
      ;//throw container_is_empty();
    return *begin_ptr;
  }
  /**
   * access the last element.
   * ;//throw container_is_empty if size == 0
   */
  const T &back() const {
    if (current_size == 0)
      ;//throw container_is_empty();
    return *(begin_ptr + current_size - 1);
  }
  /**
   * returns an iterator to the beginning.
   */
  iterator begin() { return iterator(begin_ptr, begin_ptr); }
  const_iterator cbegin() const { return const_iterator(begin_ptr, begin_ptr); }
  /**
   * returns an iterator to the end.
   */
  iterator end() { return iterator(begin_ptr + current_size, begin_ptr); }
  const_iterator cend() const {
    return const_iterator(begin_ptr + current_size, begin_ptr);
  }
  /**
   * checks whether the container is empty
   */
  bool empty() const { return current_size == 0; }
  /**
   * returns the number of elements
   */
  size_t size() const { return current_size; }
  /**
   * clears the contents
   */
  void clear() {
    // for (int i = 0; i < current_size; i++) {
    //   std::destroy_at(begin_ptr + i);
    // }
    // alloc.deallocate(begin_ptr, max_size);
    delete [] begin_ptr;
    current_size = max_size = 0;
    begin_ptr = nullptr;
  }
  /**
   * inserts value before pos
   * returns an iterator pointing to the inserted value.
   */
  void grow_capacity() {
    // if(current_size>max_size){
    // 	// std::cerr<<"!!!!!";
    // 	exit(0);
    // }
    // getchar();
    // std::cerr<<max_size<<' '<<current_size	<<std::endl;
    size_t new_max_size = (max_size == 0) ? 1 : max_size * 2;
    T *new_begin_ptr = new T[new_max_size];
    for (size_t i = 0; i < current_size; i++) {
		new_begin_ptr[i]=begin_ptr[i];
    }
	delete [] begin_ptr;
    max_size = new_max_size;
    begin_ptr = new_begin_ptr;
  }
  void shrink_capacity() {
    size_t new_max_size = max_size >> 1;
    T *new_begin_ptr = new T[new_max_size];
    for (size_t i = 0; i < current_size; i++) {
		new_begin_ptr[i]=begin_ptr[i];
    }
	delete [] begin_ptr;
    max_size = new_max_size;
    begin_ptr = new_begin_ptr;
  }
  iterator insert(iterator pos, const T &value) {
    return insert(pos - begin(), value);
  }
  /**
   * inserts value at index ind.
   * after inserting, this->at(ind) == value
   * returns an iterator pointing to the inserted value.
   * ;//throw index_out_of_bound if ind > size (in this situation ind can be size
   * because after inserting the size will increase 1.)
   */
  iterator insert(const size_t &ind, const T &value) {
    if (ind > current_size)
      ;//throw index_out_of_bound();
    if (current_size >= max_size)
      grow_capacity();
    for (size_t i = current_size; i > ind; i--) {
      begin_ptr[i] = begin_ptr[i - 1];
    }
    begin_ptr[ind] = value;
    current_size++;
    return iterator(begin_ptr + ind, begin_ptr);
  }
  /**
   * removes the element at pos.
   * return an iterator pointing to the following element.
   * If the iterator pos refers the last element, the end() iterator is
   * returned.
   */
  iterator erase(iterator pos) { return erase(pos - begin()); }
  /**
   * removes the element with index ind.
   * return an iterator pointing to the following element.
   * ;//throw index_out_of_bound if ind >= size
   */
  iterator erase(const size_t &ind) {
    if (ind >= current_size)
      ;//throw index_out_of_bound();
    for (size_t i = ind; i < current_size - 1; i++) {
      begin_ptr[i] = begin_ptr[i + 1];
    }
    current_size--;
    if (current_size <= (max_size >> 2))
      shrink_capacity();
    return iterator(begin_ptr + ind, begin_ptr);
  }
  /**
   * adds an element to the end.
   */
  void push_back(const T &value) {
    if (current_size >= max_size)
      grow_capacity();
    begin_ptr[current_size] = value;
    current_size++;
  }
  /**
   * remove the last element from the end.
   * ;//throw container_is_empty if size() == 0
   */
  void pop_back() {
    if (current_size == 0)
      ;//throw container_is_empty();
    // std::destroy_at(begin_ptr + current_size - 1);
    current_size--;
    if (current_size <= (max_size >> 2))
      shrink_capacity();
  }
};

} // namespace sjtu

#endif
#include <cassert>
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<string>
// #include <type_traits>
// #include <bits/stdc++.h>
// std::swap()
// only for std::less<T>
// #include "utility.hpp"
// #include "exceptions.hpp"
// extern map<int,int>mp;
// extern vector<int>re;
// #include <utility>
namespace sjtu {

class exception {
protected:
	const std::string variant = "";
	std::string detail = "";
public:
	exception() {}
	exception(std::string str) : detail(str) {}
	exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
	virtual std::string what() {
		return variant + " " + detail;
	}
};

class index_out_of_bound : public exception {
	/* __________________________ */
	public:
	index_out_of_bound(){}
	index_out_of_bound(std::string str) : exception(str) {}
};

class runtime_error : public exception {
	/* __________________________ */
	public:
	runtime_error(){}
	runtime_error(std::string str) : exception(str) {}
};

class invalid_iterator : public exception {
	/* __________________________ */
	public:
	invalid_iterator(){}
	invalid_iterator(std::string str) : exception(str) {}
};

class container_is_empty : public exception {
	/* __________________________ */
	public:
	container_is_empty(){}
	container_is_empty(std::string str) : exception(str) {}
};
class invalid_operator : public exception {
	/* __________________________ */
	public:
	invalid_operator(){}
	invalid_operator(std::string str) : exception(str) {}
};
}
namespace sjtu {

template<class T1, class T2>
class pair {
public:
	T1 first;
	T2 second;
	constexpr pair() : first(), second() {}
	// pair(const pair &other) = default;
	// pair(pair &&other) = default;
	pair(const T1 &x, const T2 &y) : first(x), second(y) {}
	template<class U1, class U2>
	pair(U1 &&x, U2 &&y) : first(x), second(y) {}
	template<class U1, class U2>
	pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}
	template<class U1, class U2>
	pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
    bool operator<(const pair<T1, T2> &other) const {
        return first < other.first||(first==other.first&&second<other.second);
    }
    bool operator>(const pair<T1, T2> &other) const {
        return first > other.first||(first==other.first&&second>other.second);
    }
    bool operator<=(const pair<T1, T2> &other) const {
        return first < other.first||(first==other.first&&second<=other.second);
    }
    bool operator>=(const pair<T1, T2> &other) const {
        return first > other.first||(first==other.first&&second>=other.second);
    }
    bool operator==(const pair<T1, T2> &other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const pair<T1, T2> &other) const {
        return first != other.first || second != other.second;
    }
};
template <class T1, class T2>
sjtu::pair<T1, T2> make_pair(T1&& first, T2&& second) {
    return pair<T1, T2>(std::forward<T1>(first), std::forward<T2>(second));
}
}
using namespace sjtu;

namespace sjtu {
struct iterator_base{

};
template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	
	enum Color{BLACK,RED};
    struct Node{
        Node *left,*right,*parent;
        value_type val;
        int size;
		Color color;
        Node():left(nullptr),size(0),right(nullptr),parent(nullptr){}
        Node(const value_type &val,const Color color):left(nullptr),size(1),right(nullptr),parent(nullptr),val(val),color(color){}
    };
    Node *root;
    map():root(nullptr){}
    ~map(){destruct_tree(root);}
    void destruct_tree(Node *node){
        if(node==nullptr)return;
        destruct_tree(node->left);
        destruct_tree(node->right);
        delete node;
    }
    size_t size()const
    {
        if(root==nullptr)
            return 0;
        return root->size;
    }
    bool empty()const
    {
        return size()==0;
    }
    void clear()
    {
        destruct_tree(root);
        root=nullptr;
    }
    Node * search(const Key &key)const
    {
        Node *node=root;
        while(node!=nullptr)
        {
            if(Compare()(key,node->val.first))
                node=node->left;
            else if(Compare()(node->val.first,key))
                node=node->right;
            else
                return node;
        }
        return nullptr;
    }
	const Node * constsearch(const Key &key)const
    {
        Node *node=root;
        while(node!=nullptr)
        {
            if(Compare()(key,node->val.first))
                node=node->left;
            else if(Compare()(node->val.first,key))
                node=node->right;
            else
                return node;
        }
        return nullptr;
    }
	static const Node* find_prev(const Node * node)
    {
        if(node==nullptr)
        {
//            std::cerr<<"!!!";exit(0);
            throw index_out_of_bound();//("find_prev: node is nullptr");
        }
        if(node->left!=nullptr)
        {
            node=node->left;
            while(node->right!=nullptr)
                node=node->right;
            return node;
        }
        else
        {
            while(node->parent!=nullptr&&node->parent->left==node)
                node=node->parent;
            return node->parent;
        }
    }
    static Node* find_prev(Node * node)
    {
        if(node==nullptr)
        {
//            std::cerr<<"!!!";exit(0);
            throw index_out_of_bound();//("find_prev: node is nullptr");
        }
        if(node->left!=nullptr)
        {
            node=node->left;
            while(node->right!=nullptr)
                node=node->right;
            return node;
        }
        else
        {
            while(node->parent!=nullptr&&node->parent->left==node)
                node=node->parent;
            return node->parent;
        }
    }
	static Node* find_next(Node * node)
    {
        if(node==nullptr)
        {
//			exit(0);
            throw index_out_of_bound();//("find_next: node is nullptr");
        }
        if(node->right!=nullptr)
        {
            node=node->right;
            while(node->left!=nullptr)
                node=node->left;
            return node;
        }
        else
        {
            while(node->parent!=nullptr&&node->parent->right==node)
                node=node->parent;
            return node->parent;
        }
    }
    static const Node* find_next(const Node * node)
    {
        if(node==nullptr)
        {
//			exit(0);
            throw index_out_of_bound();//("find_next: node is nullptr");
        }
        if(node->right!=nullptr)
        {
            node=node->right;
            while(node->left!=nullptr)
                node=node->left;
            return node;
        }
        else
        {
            while(node->parent!=nullptr&&node->parent->right==node)
                node=node->parent;
            return node->parent;
        }
    }


    Node* find_first_element()const
    {
        Node *node=root;
        if(node==nullptr)
            return nullptr;
        while(node->left!=nullptr)
            node=node->left;
        return node;
    }
    Node* find_last_element()const
    {
        Node *node=root;
        if(node==nullptr)
            return nullptr;
        while(node->right!=nullptr)
            node=node->right;
        return node;
    }
	
	bool is_left_(Node *node)
	{
		if(node==nullptr){
//			exit(0);
            // throw invalid_operator();("is_left: node is nullptr");

		}
		if(node->parent==nullptr){
			return false;
		}
		return node->parent->left==node;
	}
	void update(Node *node)
	{
		if(node==nullptr)
			// std::ce";exit(0);throw invalid_operator();("update: node is nullptr");
			return;
		if(node->parent==nullptr){
			root=node;
			node->color=BLACK;
//            std::cerr<<")))))";
		}
		node->size=(node->left==nullptr?0:node->left->size)+(node->right==nullptr?0:node->right->size)+1;
	}
    void rotate_left(Node *node){
		if(node==nullptr){
//			exit(0);
            //throw invalid_operator();//("rotate_left: node is nullptr");
		}
		if(node->right==nullptr){
//			exit(0);
            //throw invalid_operator();//("rotate_left: node->right is nullptr");
		}
		Node *right=node->right;
		node->right=right->left;
		if(right->left!=nullptr)
			right->left->parent=node;
		right->left=node;

		right->parent=node->parent;
		if(node->parent==nullptr)
			root=right;
		else if(node->parent->left==node)
			node->parent->left=right;
		else
			node->parent->right=right;
		node->parent=right;
		right->size=node->size;
		update(node);
	}
	void rotate_right(Node *node){
		if(node==nullptr){
//			exit(0);
            //throw invalid_operator();//("rotate_right: node is nullptr");
		}
		if(node->left==nullptr){
//			exit(0);
            //throw invalid_operator();//("rotate_right: node->left is nullptr");
		}
		Node *left=node->left;
		node->left=left->right;
		if(left->right!=nullptr)
			left->right->parent=node;
		left->right=node;
		if(node->parent==nullptr)
			root=left;
		else if(node->parent->left==node)
			node->parent->left=left;
		else
			node->parent->right=left;
		left->parent=node->parent;
		node->parent=left;
		left->size=node->size;
		update(node);
	}
	void insert_fixup(Node *node)
	{
        update_up(node);
        //siz
		insert_fixup_(node);
		update_up(node);
	}
	void insert_fixup_(Node *node)
	{
		if(node==nullptr||node->parent==nullptr||node->parent->color==BLACK)
			return;
		Node * father=node->parent,*grandfather=father->parent,*uncle; 
		//father must be exist and his color is red
		bool is_left_father=is_left_(father);
		if(is_left_father){
			uncle=father->parent->right;
			if(uncle!=nullptr&&uncle->color==RED){
				father->color=BLACK;
				uncle->color=BLACK;
				grandfather->color=RED;
				insert_fixup_(grandfather);
				return;
			}
			bool is_left=is_left_(node);
			if(is_left_(node)){
				father->color=BLACK;
				grandfather->color=RED;
				rotate_right(grandfather);
				return;
			}else{
				rotate_left(father);
				node->color=BLACK;
				grandfather->color=RED;

				rotate_right(grandfather);
				return;
			}
		}else{
			uncle=father->parent->left;
			if(uncle!=nullptr&&uncle->color==RED){
				father->color=BLACK;
				uncle->color=BLACK;
				grandfather->color=RED;
				insert_fixup_(grandfather);
				return;
			}
			bool is_left=is_left_(node);
			if(is_left_(node)){
				rotate_right(father);
				node->color=BLACK;
				grandfather->color=RED;
				rotate_left(grandfather);
				return;
			}else{
				father->color=BLACK;
				grandfather->color=RED;
				rotate_left(grandfather);
				return;
			}

			
		}
	}

    sjtu::pair<Node*,bool> insert_bykey(const value_type &val)
    {
        Node *node=root;
        Node *parent=nullptr;
		bool is_left;
        while(node!=nullptr)
        {
            parent=node;
            if(Compare()(val.first,node->val.first))
                node=node->left,is_left=true;
            else if(Compare()(node->val.first,val.first))
                node=node->right,is_left=false;
            else
                return sjtu::pair<Node*,bool>(node,false);
        }
       	node=new Node(val,RED);
        node->parent=parent;
        if(parent==nullptr)
        {
            root=node;
			node->color=BLACK;
			return sjtu::pair<Node*,bool>(node,true);
        }
        else if(is_left)
        {
            parent->left=node;
        }
        else
        {
            parent->right=node;
        }
        insert_fixup(node);
        return sjtu::pair<Node*,bool>(node,true);
    }
	void update_up(Node *node)
	{
		if(node==nullptr)
			return ;
		update(node);
		update_up(node->parent);
	}
	class iterator;
	pair<iterator,bool> insert(const value_type &val)
	{
		sjtu::pair<Node *,bool>res=insert_bykey(val);
		if(!res.second)
			return sjtu::pair<Node*,bool>(iterator(res.first,this),false);
		else
			return sjtu::pair<Node*,bool>(iterator(res.first,this),true);
	}
	// iterator insert(const value_type &val)
	// {
	// 	Node *node=insert_bykey(val);
	// 	if(node==nullptr)
	// 		return end();
	// 	else
	// 		return iterator(node);
	// }
	void erase(const Key &key)
	{
		if(root==nullptr)
			return ;
		if(root->left==nullptr&&root->right==nullptr)
		{
			if(!Compare()(root->val.first,key)&&!Compare()(key,root->val.first))
			{
				delete root;
				root=nullptr;
			}
			return ;
		}
		Node *node=root;
		while(node!=nullptr){
			// getchar();
			// std::cerr<<node->val.first<<std::endl;
			erase_fixdown(node,key);
			if(Compare()(key,node->val.first)){
				node=node->left;
				continue;
			}else if(Compare()(node->val.first,key)){
				node=node->right;
				continue;
			}
			if(node->left!=nullptr&&node->right!=nullptr){
				Node *next=find_next(node);
				node_swap(node,next);
                node=next->right;
				// std::cerr<<"JJJJ";
				continue;
			}
			if(node->left!=nullptr){
				if(node==root){
					root=node->left;
					node->left->parent=nullptr;
				}
				else if(is_left_(node)){
					node->parent->left=node->left;
					node->left->parent=node->parent;
				}else{
					node->parent->right=node->left;
					node->left->parent=node->parent;
				}
				update_up(node->left);
				delete node;
				return;
			}else if(node->right!=nullptr){
				if(node==root){
					root=node->right;
					node->right->parent=nullptr;
				}
				else if(is_left_(node)){
					node->parent->left=node->right;
					node->right->parent=node->parent;
				}else{
					node->parent->right=node->right;
					node->right->parent=node->parent;
				}
				update_up(node->right);
				delete node;
				return;
			}else{
				if(node==root){
					delete node;
					root=nullptr;
					return;
				}
				// if(node->color==BLACK)
				// 	erase_fixdown(node,key);
				if(is_left_(node))
					node->parent->left=nullptr;
				else
					node->parent->right=nullptr;
				update_up(node->parent);
                delete node;
				return;
			}
			
			
		}
        update_up(root);
	}
	void node_swap(Node *lhs,Node *rhs)
	{
		if(lhs==nullptr||rhs==nullptr){
//			exit(-1);
            //throw invalid_operator();//("node_swap: lhs or rhs is nullptr");

		}
		Node*tmpl=lhs->parent,*tmpr=rhs->parent;
		std::swap(lhs->size,rhs->size);
		std::swap(lhs->color,rhs->color);
		//or the size would be wrong
		if(tmpl==rhs){
			std::swap(lhs,rhs);
			std::swap(tmpl,tmpr);
		}
		if(tmpr==lhs){
			//lhs is the parent of rhs
			if(is_left_(rhs)){
				bool tmp=is_left_(lhs);
				rhs->parent=lhs->parent;
				lhs->parent=rhs;
				std::swap(lhs->right,rhs->right);
				lhs->left=rhs->left;
				rhs->left=lhs;
				if(lhs==root)
					root=rhs;
				else if(tmp)
					rhs->parent->left=rhs;
				else
					rhs->parent->right=rhs;

            }else{
				bool tmp=is_left_(lhs);
				rhs->parent=lhs->parent;
				lhs->parent=rhs;
				std::swap(lhs->left,rhs->left);
				lhs->right=rhs->right;
				rhs->right=lhs;
				if(lhs==root)
					root=rhs;
				else if(tmp)
					rhs->parent->left=rhs;
				else
					rhs->parent->right=rhs;
			}
            if(lhs->left)lhs->left->parent=lhs;
            if(rhs->left)rhs->left->parent=rhs;

            if(lhs->right)lhs->right->parent=lhs;
            if(rhs->right)rhs->right->parent=rhs;

            return ;
		}
		bool lp=is_left_(lhs),rp=is_left_(rhs);
		std::swap(lhs->parent,rhs->parent);
		std::swap(lhs->left,rhs->left);
		std::swap(lhs->right,rhs->right);
		if(lhs->parent==nullptr)
			root=lhs;
		else if(rp)
			lhs->parent->left=lhs;
		else
			lhs->parent->right=lhs;
		if(rhs->parent==nullptr)
			root=rhs;
		else if(lp)
			rhs->parent->left=rhs;
		else
			rhs->parent->right=rhs;
		
		if(lhs->left!=nullptr)
			lhs->left->parent=lhs;
		if(lhs->right!=nullptr)
			lhs->right->parent=lhs;
		if(rhs->left!=nullptr)
			rhs->left->parent=rhs;
		if(rhs->right!=nullptr)
			rhs->right->parent=rhs;
	}
	bool is_two_blackchild(Node* node)
	{
		if(node==nullptr){
//			exit(-1);
            //throw invalid_operator();//("is_two_blackchild: node is nullptr");

		}
		if(node->left&&node->left->color==RED)
			return false;
		if(node->right&&node->right->color==RED)
			return false;
		return true;
	
	}
	void erase_fixdown(Node *node,const Key key)
	{
		if(node==nullptr)
			return ;
		if(node->color==RED)
			return ;	
		
		// if(node->parent==nullptr)
		// {
		// 	//root
		// 	if(node->left&&node->right&&node->left->color==node->right->color&&node->left->color==BLACK)
		// 	{
		// 		node->color=RED;
		// 		node->left->color=BLACK;
		// 		node->right->color=BLACK;
		// 		return ;
		// 	}


		// 	//to do
		// }
		Node *father=node->parent;
		Node *brother=father==nullptr?nullptr:(is_left_(node)?father->right:father->left);
		//we assume that parent is red
		//and now we try to change node into red

		//if brother exist!!!!!!!
		if(is_two_blackchild(node)){
			if(!brother||is_two_blackchild(brother))
			{
				if(father)father->color=BLACK;
				if(brother)brother->color=RED;
				node->color=RED;
				return ;
			}
			if(is_left_(node)){

				if(brother->left&&brother->left->color==RED)
				{
					rotate_right(brother);
					rotate_left(father);
					node->color=RED;
					father->color=BLACK;
				}else{
					rotate_left(father);
					node->color=RED;
					father->color=BLACK;
					brother->color=RED;
					brother->right->color=BLACK;
					//brother's right is still itself
				}
			}else{

				if(brother->right&&brother->right->color==RED)
				{
					rotate_left(brother);
					rotate_right(father);
					node->color=RED;
					father->color=BLACK;
				}else{
					rotate_right(father);
					node->color=RED;
					father->color=BLACK;
					brother->color=RED;
					brother->left->color=BLACK;
					//brother's left is still itself
				}
			}
			return;
		}
		if(Compare()(key,node->val.first)){
			if(node->left&&node->left->color==BLACK)
			{
				rotate_left(node);
				std::swap(node->color,node->parent->color);
			}
		}else if(Compare()(node->val.first,key)){
			if(node->right&&node->right->color==BLACK)
			{
				rotate_right(node);
				std::swap(node->color,node->parent->color);
			}
		}else{
			//delete node
			if(!node->left){
				rotate_left(node);
				std::swap(node->color,node->parent->color);
			}else if(!node->right){
				rotate_right(node);
				std::swap(node->color,node->parent->color);
			}else{
				if(node->right->color==BLACK)
				{
					rotate_right(node);
					std::swap(node->color,node->parent->color);
				}
			}
		}	
		
	}
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong std::ce";exit(0);throw invalid_iterator();//.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	 public:
	class const_iterator;
	class iterator : public iterator_base{
		public:
		friend class map;
	#ifndef DEBUG
	private:
	#endif
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		 Node * ptr;
         bool is_end=true;
		const map *treeptr;
	public:
		iterator() {
			// TODO
            ptr=nullptr;
			is_end=true;
			treeptr=nullptr;
		}
		iterator(const iterator &other) {
			// TODO
			ptr=other.ptr;
			is_end=other.is_end;
			treeptr=other.treeptr;
		}
		iterator(Node *node,const map *tis,bool is_end=false):ptr(node),treeptr(tis),is_end(is_end)	{}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			if(is_end){
				throw invalid_iterator();//("iterator++: is_end");
			}
			iterator tmp(*this);
			ptr=find_next(ptr);
			if(ptr)
				*this=iterator(ptr,treeptr);
			else
				*this= iterator(nullptr,treeptr,true);
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
			if(is_end){
				throw invalid_iterator();//("++iterator: is_end");
			}
			Node* tmp=ptr;
			ptr=find_next(ptr);
			if(ptr)
				return *this=iterator(ptr,treeptr);
			else
				return *this=iterator(nullptr,treeptr,true);
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			if(is_end){
				Node * tmp=treeptr->find_last_element();
				if(!tmp)
					throw invalid_iterator();//("iterator--: is_end");
				this->is_end=false;
				this->ptr=tmp;
				return iterator(nullptr,treeptr,true);
			}
			Node *tmp=ptr;
			ptr=find_prev(ptr);
			if(!ptr)
				throw invalid_iterator();//("iterator--: is_end");
			else
				return iterator(tmp,treeptr);
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
			if(is_end){
				Node * tmp=treeptr->find_last_element();
				if(!tmp)
					throw invalid_iterator();//("iterator--: is_end");
				this->is_end=false;
				this->ptr=tmp;
				return *this;
			
			}
			ptr=find_prev(ptr);
			if(!ptr)
				throw invalid_iterator();//("--iterator: is_begin");
			else
				return *this;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
			if(is_end||!ptr){
				throw invalid_iterator();//("iterator*: is_end");
			}
			return ptr->val;
		}
		bool operator==(const iterator &rhs) const {
			return ptr==rhs.ptr&&is_end==rhs.is_end&&treeptr==rhs.treeptr;
		}
		bool operator==(const const_iterator &rhs) const {
			return ptr==rhs.ptr&&is_end==rhs.is_end&&treeptr==rhs.treeptr;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return ptr!=rhs.ptr||is_end!=rhs.is_end||treeptr!=rhs.treeptr;
		}
		bool operator!=(const const_iterator &rhs) const {
			return ptr!=rhs.ptr||is_end!=rhs.is_end||treeptr!=rhs.treeptr;
		}

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
			if(is_end||!ptr){
				throw invalid_iterator();//("iterator->: is_end");
			}
			return &ptr->val;
		}
	};
	class const_iterator : public iterator_base{
		friend class map;
		private:
			const Node * ptr;
			bool is_end;
			const map *treeptr;
		public:
			const_iterator():ptr(nullptr),is_end(true),treeptr(nullptr) {}
			const_iterator(const const_iterator &other) {
				ptr=other.ptr;
				is_end=other.is_end;
				treeptr=other.treeptr;
			}
			const_iterator(const iterator &other) {
				ptr=other.ptr;
				is_end=other.is_end;
				treeptr=other.treeptr;
			}
			const_iterator(const Node *node,const map* treeptr,bool is_end=false):ptr(node),treeptr(treeptr),is_end(is_end){}
			const_iterator& operator=(const const_iterator &other) {
				ptr=other.ptr;
				is_end=other.is_end;
				treeptr=other.treeptr;
				return *this;
			}
			const_iterator& operator=(const iterator &other) {
				ptr=other.ptr;
				is_end=other.is_end;
				treeptr=other.treeptr;
				return *this;
			}
			const_iterator& operator++() {
				if(is_end){
					throw invalid_iterator();//("++iterator: is_end");
				}
				const Node *tmp=ptr;
				ptr=find_next(ptr);
				if(ptr)
					return *this;
				else
					return *this=const_iterator(nullptr,treeptr,true);
			}
			const_iterator operator++(int) {
				if(is_end){
					throw invalid_iterator();//("++iterator: is_end");
				}
				const_iterator tmp(*this);
				ptr=find_next(ptr);
				if(ptr)
					return tmp;
				else{
					is_end=true;
					return tmp;
				}
			}
			const_iterator& operator--() {
				if(is_end){
					const Node * tmp=treeptr->find_last_element();
					if(!tmp)
						throw invalid_iterator();//("iterator--: is_end");
					this->is_end=false;
					this->ptr=tmp;
					return *this;
				
				}
				ptr=find_prev(ptr);
				if(!ptr)
					throw invalid_iterator();//("--iterator: is_begin");
				else
					return *this;
				
			}
			const_iterator operator--(int) {
				if(is_end){
					const Node * tmp=treeptr->find_last_element();
					if(!tmp)
						throw invalid_iterator();//("iterator--: is_end");
					this->is_end=false;
					this->ptr=tmp;
					return iterator(nullptr,treeptr,true);
				}
				const Node *tmp=ptr;
				ptr=find_prev(ptr);
				if(!ptr)
					throw invalid_iterator();//("iterator--: is_end");
				else
					return const_iterator(tmp,treeptr);
			}
			const value_type& operator*() const {
				if(is_end||!ptr){
					throw invalid_iterator();//("iterator*: is_end");
				}
				return ptr->val;
			}
			bool operator==(const const_iterator &rhs) const {
				return ptr==rhs.ptr&&is_end==rhs.is_end&&treeptr==rhs.treeptr;
			}
			bool operator==(const iterator &rhs) const {
				return ptr==rhs.ptr&&is_end==rhs.is_end&&treeptr==rhs.treeptr;
			}
			bool operator!=(const const_iterator &rhs) const {
				return ptr!=rhs.ptr||is_end!=rhs.is_end	||treeptr!=rhs.treeptr;
			}
			bool operator!=(const iterator &rhs) const {
				return ptr!=rhs.ptr||is_end!=rhs.is_end	||treeptr!=rhs.treeptr;
			}
			const value_type* operator->() const noexcept {
				if(is_end||!ptr){
					throw invalid_iterator();//("iterator->: is_end");
				}
				return &ptr->val;
			}
	};
	
	// class const_iterator {
	// 	// it should has similar member method as iterator.
	// 	//  and it should be able to construct from an iterator.
	// 	private:
	// 		// data members.
	// 		const Node * ptr;
	// 		bool is_end;
	// 	public:
	// 		const_iterator():ptr(nullptr),is_end(true) {}
	// 			// TODO
			
	// 		const_iterator(const const_iterator &other) {
	// 			// TODO
	// 			ptr=other.ptr;
	// 			is_end=other.is_end;
	// 		}
	// 		const_iterator(const iterator &other) {
	// 			// TODO
	// 			ptr=other.ptr;
	// 			is_end=other.is_end;
	// 		}
			
	// 		// And other methods in iterator.
	// 		// And other methods in iterator.
	// 		// And other methods in iterator.
	// };
	/**
	 * TODO two constructors
	 */
	map(const map &other) {
		// TODO
		root=nullptr;
		// int cnt=0;
		// std::cerr<<"**";
		for(const_iterator it=other.cbegin();it!=other.cend();it++)
		{
			// std::cerr<<++cnt<<std::endl;
			insert(*it);
		}
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {
		// TODO
		if(this==&other)
			return *this;
		clear();
		for(const_iterator it=other.cbegin();it!=other.cend();it++)
		{
			insert(*it);
		}
		return *this;
	}
	/**
	 * TODO Destructors
	 */
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) {
		Node *node=search(key);
		if(node==nullptr)
			throw index_out_of_bound();//("at: no such element");
		return node->val.second;
	}
	const T & at(const Key &key) const {
		Node *node=search(key);
		if(node==nullptr)
			throw index_out_of_bound();//("at: no such element");
		return node->val.second;
	}
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
		pair<Node*,bool>res=insert_bykey(value_type(key,T()));
		Node *node=res.first;
		return node->val.second;
	}
	/**
	 * behave like at() std::ce";exit(0);throw index_out_of_bound();// if such key does not exist.
	 */
	const T & operator[](const Key &key) const {
		Node *node=search(key);
		if(node==nullptr)
			throw index_out_of_bound();//("operator[]: no such element");
		return node->val.second;
	}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {
		Node *node=find_first_element();
		if(node)
			return iterator(node,this);
		else
			return iterator(nullptr,this,true);
	}
	const_iterator cbegin() const {
		const Node *node=find_first_element();
		if(node)
			return const_iterator(node,this);
		else
			return const_iterator(nullptr,this,true);
	}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {
		// Node * node=find_last_element();
		// if(node)
		// 	return iterator(node,this,true);
		// else
		// 	
		return iterator(nullptr,this,true);
	}
	const_iterator cend() const {
		// const Node * node=find_last_element();
		// if(node)
		// 	return const_iterator(node,this,true);
		// else
		// 	
		return const_iterator(nullptr,this,true);
	}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	// bool empty() const {}
	/**
	 * returns the number of elements.
	 */
	// size_t size() const {}
	/**
	 * clears the contents
	 */
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	/**
	 * erase the element at pos.
	 *
	 * std::ce";exit(0);throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {
		if(pos.is_end)
			throw invalid_iterator();//("erase: pos==end()");
		if(pos.ptr==nullptr)
			throw invalid_iterator();//("erase: pos.ptr==nullptr");
		// if(pos.is_end||pos.ptr==nullptr)
		// 	return ;
		if(pos.treeptr!=this)
			throw invalid_iterator();//("not on this tree");
		erase(pos->first);
		
	}
	// void erase(const Key &key)
	// {
	// 	erase()(key);
	// }
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
		Node *node=search(key);
		if(node==nullptr)
			return 0;
		return 1;
	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	auto find(const Key &key)->iterator  {
		Node *node=search(key);
		if(node==nullptr)
			return end();
		return iterator(node,this);
	}
	auto find(const Key &key)const ->const_iterator  {
		Node *node=search(key);
		if(node==nullptr)
			return cend();
		return const_iterator(node,this);
	}
	
	// const_iterator find(const Key &key) const {
	// 	Node *node=search(key);
	// 	if(node==nullptr)
	// 		return cend();
	// 	return const_iterator(node);
	// }

	//this is debug
#ifdef SJTU_MAP_DEBUG 
	void print_treenode(Node *node,int f=0,int mi=0,int mx=100000)
	{
		
		if(node==nullptr)
			return ;
        if(f>=2)goto P;
//		if(f==1)exit(0);
		std::cout<<node->val.first<<" ";
		std::cout<<(node->color==RED?"RED":"BLACK")<<std::endl;
		std::cout<<"left"<<((node->left)?node->left->val.first:0)<<' '<<"right"<<((node->right)?node->right->val.first:0)<<std::endl;
        if(node->left&&node->left->parent!=node){
            std::cerr<<"erro";
            int p;std::cin>>p;

        }
        if(node->right&&node->right->parent!=node){
            std::cerr<<"erro";
            int p;std::cin>>p;

        }
        P:
        if(f==2){
            if(node->val.first<mi||node->val.first>mx){
                std::cerr<<"hhhhh"<<mi<<mx;            int p;std::cin>>p;

            }
            if(mp[node->val.first]!=node->val.second){
                std::cerr<<"nooooo";            int p;std::cin>>p;

            }
        }
        print_treenode(node->left,f,mi,node->val.first);
		re.push_back(node->val.first);
        print_treenode(node->right,f,node->val.first,mx);
	}
	void print_tree(int f=0)
	{
		if(f<2)std::cout<<"-------------------\n";
		print_treenode(root,f);
		if(f<2)std::cout<<"-------------------\n";
	}
    int chk(Node*node,int f=0)
    {
        if(!node)return 1;
        if(!node->parent) {
            if (node->color == RED)return f==-2?-2:-110;
        }else{
            if(node->color==RED&&node->parent->color==RED)
                return f==-2?-2:-110;
        }
        if(node->left&&node->left->parent!=node)return f==-3?-3:-110;
        if(node->right&&node->right->parent!=node)return f==-3?-3:-110;

        int nl=chk(node->left,f);
        int nr=chk(node->right,f);
        if(nl<0||nr<0||nl!=nr)return f==nl?f:(f==nr?f:-110);
        return nl+(node->color==BLACK?1:0);
    }
#endif

};
}

    #ifndef MY_MEMORY_CLASS
    #define MY_MEMORY_CLASS

    // #include <fstream>
    // #include <fstream>
    #include <iostream>
    // #include <map>
    // #include <vector>

    using std::string;
    using std::fstream;
    using std::ifstream;
    using std::ofstream;

    struct Mystring{
        char c[65];int l=0;
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

#ifndef BPLUSTREE_HPP
#define BPLUSTREE_HPP
#include <cassert>
// #include <fstream>
#include <iostream>
// #include <map>
// #include <vector>
// #include <queue>
// #include "utility.hpp"
// #include "hashmap.hpp"

// #define DEBUG
using namespace sjtu;
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
        int next=-1;
        innerTreeNode(bool isLeafNode=false) {
            isLeaf = isLeafNode;
            num = 0;
        }
        #ifdef DEBUG
        void print()
        {
            std::cerr<<"--------\n";
            std::cerr<<"tree:  "<<id<<std::endl;
            std::cerr<<"num:  "<<num<<std::endl;
            std::cerr<<"isLeaf:  "<<isLeaf<<std::endl;
            for(int i=0;i<num-1;i++){
                std::cerr<<keys[i]<<" ";
            }
            std::cerr<<std::endl;
            for(int i=0;i<num;i++){
                std::cerr<<children[i]<<" ";
            }
            std::cerr<<"--------\n";
            
            
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
    config Config;
    static const int buffersize=1000;
    innerTreeNode treebuffer[buffersize];
    dataNode databuffer[buffersize];
    priority_queue<pair<int,int>>treebufferqueue;
    priority_queue<pair<int,int>>databufferqueue;
    priority_queue<pair<int,int>>treevacantqueue;
    priority_queue<pair<int,int>>datavacantqueue;
    


    map<int,int>treepos;
    map<int,int>datapos;

    map<int,int>treetime;
    map<int,int>datatime;

    
    
    //缓存系统
    map<int,int > father;
    int time_stamp=0;
    int FSIZE=-1;

    #ifdef DEBUG
    map<int,int>test;
    map<int,int>testm;
    #endif    
public:
    #ifdef DEBUG
    void printconfig(){
        // config Config;
        // getconfig(Config);
        std::cerr<<"root: "<<Config.root<<std::endl;
        std::cerr<<"datahead: "<<Config.datahead<<std::endl;
        std::cerr<<"dataend: "<<Config.dataend<<std::endl;
        std::cerr<<"datacnt: "<<Config.datacnt<<std::endl;
        std::cerr<<"treecnt: "<<Config.treecnt<<std::endl;
    }
    #endif
    void getallelement(vector<key_t>&key,vector<val_t>&value){
        key.clear();
        value.clear();
        // config Config;
        // getconfig(Config);
        dataNode* datanw;
        buffergetdatafile(datanw,Config.datahead);
        while(datanw->id!=Config.dataend){
            for(int i=0;i<datanw->num;i++){
                key.push_back(datanw->keys[i]);
                value.push_back(datanw->values[i]);
            }
            buffergetdatafile(datanw,datanw->next);
        }
        for(int i=0;i<datanw->num;i++){
            key.push_back(datanw->keys[i]);
            value.push_back(datanw->values[i]);
        }

    }
    #ifdef DEBUG
    bool checktree()
    {
        //遍历树
        // config Config;
        // getconfig(Config);
        innerTreeNode *nw;
        dataNode* datanw;
        int st[5000],h=0,t=0;
        st[0]=Config.root;
        int las=Config.datahead;
        bool flag=false;
        int mm=-1,MM=100000000;
        test[Config.root]=100000000;
        testm[Config.root]=-1;

        while(h<=t){
            int u=st[h++];
            buffergettreefile(nw,u);
            if(testm[u]>test[u]){
                std::cout<<"__error in tree structure1"<<std::endl;
                return false;
            }
            if(nw->num>1&&nw->keys[0]<testm[u]){
                std::cout<<"__error in tree structure3"<<std::endl;
                return false;
            }
            if(nw->num>1&&nw->keys[nw->num-2]>test[u]){
                std::cout<<"__error in tree structure2"<<std::endl;
                //!!!!!!
                nw->print();

                return false;
            }

            for(int i=0;i<nw->num;i++){
                if(i+2<nw->num&&nw->keys[i]>nw->keys[i+1]){
                    std::cout<<"__error in tree structur4"<<std::endl;
                    return false;
                }
                if(!nw->isLeaf){
                    st[++t]=nw->children[i];
                    test[nw->children[i]]=(i+1==nw->num)?test[nw->id]:nw->keys[i];
                    testm[nw->children[i]]=(i==0)?testm[nw->id]:nw->keys[i-1];
                }else{
                    if(!flag){
                        if(nw->children[i]!=las){
                            std::cout<<"error in tree structure"<<std::endl;
                            return false;
                        }else {
                            flag=true;
                            continue;
                        }
                    }
                    buffergetdatafile(datanw,las);
                    if(datanw->next!=nw->children[i]){
                        std::cout<<"error in tree structrue"<<std::endl;
                        return false;
                    }
                    las=nw->children[i];
                    buffergetdatafile(datanw,las);
                    mm=(i==0)?testm[nw->id]:nw->keys[i-1];
                    MM=(i+1==nw->num)?test[nw->id]:nw->keys[i];
                    for(int j=0;j<datanw->num;j++){
                        if(j+1<datanw->num&&datanw->keys[j]>datanw->keys[j+1]){
                            datanw->print();
                            std::cerr<<"__error in tree structur5"<<std::endl;
                            return false;
                        }
                        if(datanw->keys[j]<mm){
                            datanw->print();
                            std::cout<<"__error in tree structure6"<<std::endl;
                            return false;
                        }
                        if(datanw->keys[j]>MM){
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
    void print_buffer()
    {
        std::cerr<<"treebuffer\n";
        if(treevacantqueue.size()+treepos.size()!=buffersize)
            std::cerr<<"error in treebuffer\n",getchar();
        for(int i=0;i<buffersize;i++){
            if(treebuffer[i].id==-1)continue;
            if(treepos.find(treebuffer[i].id)==treepos.end())
                std::cerr<<"error in treebuffer{{\n",getchar();
            if(treepos[treebuffer[i].id]!=i)
                std::cerr<<"error in treebuffer{{\n",getchar();
            
            std::cerr<<i<<":"<<treebuffer[i].id<<" ";
        }
        std::cerr<<"-------------------------\n";
        std::cerr<<"databuffer\n";
        if(datavacantqueue.size()+datapos.size()!=buffersize)
            std::cerr<<"error in databuffer\n",getchar();
        for(int i=0;i<buffersize;i++){
            if(databuffer[i].id==-1)continue;
            if(datapos.find(databuffer[i].id)==datapos.end())
                std::cerr<<"error in databuffer{{\n",getchar();
            if(datapos[databuffer[i].id]!=i)
                std::cerr<<"error in databuffer{{\n",getchar();
            
            std::cerr<<i<<":"<<databuffer[i].id<<" ";
        }
        std::cerr<<"finished----------------------------\n";

    }
    void print_tree()
    {
        // config Config;
        // getconfig(Config);
        innerTreeNode *nw;
        dataNode* datanw;
        int st[5000],h=0,t=0;
        st[0]=Config.root;
        int las=Config.datahead;
        bool flag=false;
        test[Config.root]=100000000;
        testm[Config.root]=-1;
        while(h<=t){
            int u=st[h++];
            buffergettreefile(nw,u);
            nw->print();
            for(int i=0;i<nw->num;i++){
                if(!nw->isLeaf){
                    st[++t]=nw->children[i];
                }else{
                    buffergetdatafile(datanw,nw->children[i]);
                    datanw->print();
                }
            }
            // getchar();
        }
    }
    #endif
    BPlusTree(std::string datafile,std::string treefile,bool isnew=false):datafile(datafile),treefile(treefile){
        time_stamp=0;
        treepos.clear();
        datapos.clear();
        while(treebufferqueue.size())treebufferqueue.pop();
        while(databufferqueue.size())databufferqueue.pop();  
        while(treevacantqueue.size())treevacantqueue.pop();
        while(datavacantqueue.size())datavacantqueue.pop();
        for(int i=0;i<buffersize;i++){
            treevacantqueue.push(sjtu::make_pair(0,i));
            datavacantqueue.push(sjtu::make_pair(0,i));
        }      
        for(int i=0;i<buffersize;i++){
            treebuffer[i].id=-1;
            databuffer[i].id=-1;
        }
        file.open(treefile, std::ios::app);
        if (isnew||file.tellp()==0){
            //建立第一个节点，存储空 
            file.close();   
            file.open(treefile, std::ios::out);
            file.write(reinterpret_cast<char *>(&Config), sizeof(config));
            innerTreeNode headtreenode(true);
            headtreenode.num=1;
            headtreenode.children[0]=0;
            file.write(reinterpret_cast<char *>(&headtreenode), sizeof(innerTreeNode));
            file.close();


            file.open(datafile, std::ios::out);
            dataNode headdatanode;
            headdatanode.num=0;
            file.write(reinterpret_cast<char *>(&headdatanode), sizeof(dataNode));
            
        }else{
            file.close();
            file.open(treefile, std::ios::in | std::ios::out);
            file.read(reinterpret_cast<char*>(&Config), sizeof(config));
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
        file.open(treefile, std::ios::in | std::ios::out);
        file.write(reinterpret_cast<char *>(&Config), sizeof(config));
        file.close();
        #ifdef DEBUG
        print_tree();
        #endif
    }
    //空间池

    //可以扩展缓存优化
    // void getconfig(config &head){
    //     file.open(treefile, std::ios::in | std::ios::out);
    //     file.read(reinterpret_cast<char *>(&head), sizeof(config));
    //     file.close();
    // }
    // void setconfig(config &head){
    //     file.open(treefile, std::ios::in | std::ios::out);
    //     file.write(reinterpret_cast<char *>(&head), sizeof(config));
    //     file.close();
    // }
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
                    dataNode* tmp;
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
    void buffergettreefile(innerTreeNode *&node,int pos){
        if(treepos.find(pos)==treepos.end()){
            if(treevacantqueue.empty()){
                // std::cerr<<"hhhhhhhhh"
                // exit(0);
                // std::cerr<<pos<<" "<<treebufferqueue.top().second<<'|'<<treebufferqueue.size()<<"tree:\n";

                while(true){
                    int p=treebufferqueue.top().second;
                    //这里指那个tree的id
                    int ppos=treepos[p];
                    if(treebufferqueue.top().first!=-treetime[p]){
                        treebufferqueue.pop();
                        treebufferqueue.push(sjtu::make_pair(-treetime[p],p));
                        continue;
                    }
                    treetime.erase(p);
                    treebufferqueue.pop();
                    treevacantqueue.push(sjtu::make_pair(0,ppos));
                    //vacant中的是树位置
                    if(treebuffer[ppos].id!=p)std::cerr<<"hkj";
                    assert(treebuffer[ppos].id==p);
                    settreefile(treebuffer[ppos], p);
                    treepos.erase(p);
                    break;
                }
            }
            int ppos=treevacantqueue.top().second;
            treevacantqueue.pop();
            treepos[pos]=ppos;
            treebufferqueue.push(sjtu::make_pair(-(treetime[pos]=++time_stamp),pos));
            //注记：大根堆
            gettreefile(treebuffer[ppos],pos);
            node=treebuffer+ppos;
        }else{
            node=treebuffer+treepos[pos];
            //bug: forget to update the time_stamp
            treetime[pos]=++time_stamp;
        }
        // //没有绑定同步设置，只是一个存档！！！
        // if(treepos.find(pos)==treepos.end()){
        //     treepos[pos]=time_stamp++;
        // }
        // for(int i=0;i<buffersize;i++){
        //     if(treebuffer[i].id==pos){
        //         node=treebuffer+i;
        //         return;
        //     }
        // }
        // settreefile(treebuffer[0],treebuffer[0].id);
        // for(int i=0;i<buffersize-1;i++){
        //     treebuffer[i]=treebuffer[i+1];
        // }
        // gettreefile(treebuffer[buffersize-1],pos);
        // node=treebuffer+buffersize-1;    
    }
    // void buffersettreefile(innerTreeNode &node,int pos){
    //     for(int i=0;i<buffersize;i++){
    //         if(treebuffer[i].id==pos){
    //             treebuffer[i]=node;
    //             return;
    //         }
    //     }
    //     if(treebuffer[0].id!=-1){
    //         settreefile(treebuffer[0],treebuffer[0].id);
    //     }
    //     for(int i=0;i<buffersize;i++){
    //         treebuffer[i]=treebuffer[i+1];
    //     }
    //     treebuffer[buffersize-1]=node;
    // }
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
    // void buffergetconfig
    //
    void buffergetdatafile(dataNode *&node,int pos){
        // std::cerr<<databufferqueue.size()<<"{}"<<pos<<"("<<'\n';
        if(datapos.find(pos)==datapos.end()){
            if(datavacantqueue.empty()){
                // std::cerr<<pos<<" "<<databufferqueue.top().second<<'|'<<databufferqueue.size()<<"data:\n";
                while(true){
                    int p=databufferqueue.top().second;
                    int ppos=datapos[p];
                    if(databufferqueue.top().first!=-datatime[p]){
                        databufferqueue.pop();
                        databufferqueue.push(sjtu::make_pair(-datatime[p],p));
                        continue;
                    }
                    datatime.erase(p);
                    databufferqueue.pop();
                    datavacantqueue.push(sjtu::make_pair(0,ppos));
                    if(databuffer[ppos].id!=p)std::cerr<<"hkj";
                    assert(databuffer[ppos].id==p);
                    setdatafile(databuffer[ppos], p);
                    datapos.erase(p);
                    break;
                }
            }
            int ppos=datavacantqueue.top().second;
            datavacantqueue.pop();
            datapos[pos]=ppos;
            databufferqueue.push(sjtu::make_pair(-(datatime[pos]=++time_stamp),pos));
            getdatafile(databuffer[ppos],pos);
            node=databuffer+ppos;
        }else{
            node=databuffer+datapos[pos];
            datatime[pos]=++time_stamp;
        }

    // std::cerr<<")";
        // for(int i=0;i<buffersize;i++){
        //     if(databuffer[i].id==pos){
        //         node=databuffer+i;
        //         return;
        //     }
        // }
        // setdatafile(databuffer[0],databuffer[0].id);
        // for(int i=0;i<buffersize-1;i++){
        //     databuffer[i]=databuffer[i+1];
        // }
        // getdatafile(databuffer[buffersize-1],pos);
        // node=databuffer+buffersize-1;    
    }
    // void buffersetdatafile(dataNode* &node,int pos){
    //     //应该使用循环队列的方法
    //     for(int i=0;i<buffersize;i++){
    //         if(databuffer[i].id==pos){
    //             databuffer[i]=node;
    //             return;
    //         }
    //     }
    //     if(databuffer[0].id!=-1){
    //         setdatafile(databuffer[0],databuffer[0].id);
    //     }
    //     for(int i=0;i<buffersize;i++){
    //         databuffer[i]=databuffer[i+1];
    //     }
    //     databuffer[buffersize-1]=node;
    // }
    bool search(const key_t &key, val_t &value) {
        // config Config;
        // getconfig(Config);
        innerTreeNode *nw;
        buffergettreefile(nw,Config.root);
        int depth=0;
        while (!nw->isLeaf) {
            int i = 0;
            while (i < nw->num-1 && key > nw->keys[i]) {
                i++;
            }
            buffergettreefile(nw,nw->children[i]);
            depth++;
            
            // if(key==33){
            //     std::cout<<nw->num<<" ||"<<std::endl;
            //     std::cout<<nw->children[0]<<" --"<<std::endl;
            //     std::cout<<nw->keys[0]<<""<<std::endl;

            //     std::cout<<nw->children[1]<<" --"<<std::endl;
            // }
        }
        int i = 0;
        while (i < nw->num-1 && key > nw->keys[i]) {
            i++;
        }
        depth++;
        // std::cout<<"depth: "<<depth<<std::endl;
        dataNode *datanw;
        buffergetdatafile(datanw,nw->children[i]);
        int j = 0;
        while (j < datanw->num && key > datanw->keys[j]) {
            j++;
        }
        if(j<datanw->num&&key==datanw->keys[j]){
            value = datanw->values[j];
            return true;
        }
        return false;

    }
    void searchall(const key_t &lower_bound,const key_t upper_bound,vector<val_t> &value)
    {
        value.clear();
        // config Config;
        // getconfig(Config);
        innerTreeNode* nw;
        buffergettreefile(nw,Config.root);
        while (!nw->isLeaf) {
            int i = 0;
            while (i < nw->num-1 && lower_bound > nw->keys[i]) {
                i++;
            }
            buffergettreefile(nw,nw->children[i]);
        }
        int i = 0;
        while (i < nw->num-1 && lower_bound > nw->keys[i]) {
            i++;
        }
        dataNode* datanw;
        buffergetdatafile(datanw,nw->children[i]);
        int j = 0;
        while (j < datanw->num && lower_bound > datanw->keys[j]) {
            j++;
        }
        while(datanw->id!=Config.dataend){
            for(int k=j;k<datanw->num;k++){
                if(datanw->keys[k]>upper_bound){
                    return;
                }
                value.push_back(datanw->values[k]);
            }
            buffergetdatafile(datanw,datanw->next);
            j=0;
        }

        for(int k=j;k<datanw->num;k++){
            if(datanw->keys[k]>upper_bound){
                return;
            }
            value.push_back(datanw->values[k]);
        }
    }
    // 插入关键字
    void insert(const key_t &key,const val_t &value) {
        // config Config;
        // getconfig(Config);
        innerTreeNode* nw;
        buffergettreefile(nw,Config.root);
        father[nw->id]=-1;
        // nw->print();
        while (!nw->isLeaf) {
            int i = 0;
            while (i < nw->num-1 && key > nw->keys[i]) {
                i++;
            }
            father[nw->children[i]]=nw->id;
            buffergettreefile(nw,nw->children[i]);
        }
        int i = 0;
        while (i < nw->num-1 && key > nw->keys[i]) {
            i++;
        }
        int place=nw->children[i];
        dataNode* datanw;
        buffergetdatafile(datanw,nw->children[i]);
        
        
        int j = 0;
        while (j < datanw->num && key > datanw->keys[j]) {
            j++;
        }
        
        for(int k=datanw->num;k>j;k--){
            datanw->keys[k]=datanw->keys[k-1];
            datanw->values[k]=datanw->values[k-1];
        }
        datanw->keys[j]=key;
        datanw->values[j]=value;
        datanw->num++;
        if(datanw->num<=L){
            // buffersetdatafile(datanw,datanw->id);
            return;
        }
        // std::cerr<<"{{{{{}}}}}";
        dataNode* newdatanw;
        if(Config.vacantdatablock!=-1){
            buffergetdatafile(newdatanw,Config.vacantdatablock);
            assert(newdatanw->id==Config.vacantdatablock);
            Config.vacantdatablock=newdatanw->next;
        }else{
            buffergetdatafile(newdatanw,++Config.datacnt);
            newdatanw->id=Config.datacnt;
        }
        newdatanw->num=0;
        

        //可以加入内存回收策略
        for(int i=((L+1)>>1);i<datanw->num;i++){
            newdatanw->keys[i-((L+1)>>1)]=datanw->keys[i];
            newdatanw->values[i-((L+1)>>1)]=datanw->values[i];
            newdatanw->num++;
        }
        datanw->num=(L+1)>>1;
        newdatanw->next=datanw->next;
        datanw->next=newdatanw->id;
        newdatanw->prev=datanw->id;
        // buffersetdatafile(datanw,datanw->id);
        // buffersetdatafile(newdatanw,newdatanw->id);
        if(datanw->id!=Config.dataend){
            dataNode* nextdatanw;
            buffergetdatafile(nextdatanw,newdatanw->next);
            nextdatanw->prev=newdatanw->id;
            // buffersetdatafile(nextdatanw,nextdatanw->id);
        }else{
            Config.dataend=newdatanw->id;
        }
        
        //data部分完成
        //开始更新树
        bool flag=false;
        int childid=newdatanw->id;
        key_t splitkey=datanw->keys[((L+1)>>1)-1];
        //叶子层
        while(!flag){
            int k;
            for(k=nw->num;k>1&&nw->children[k-1]!=place;k--){
                nw->keys[k-1]=nw->keys[k-2];
                nw->children[k]=nw->children[k-1];
            }
            nw->keys[k-1]=splitkey;
            nw->children[k]=childid;
            nw->num++;
            if(nw->num<=M){
                
                // buffersettreefile(nw,nw->id);
                flag=true;
                break;
            }

            innerTreeNode* newnw;
            if(Config.vacanttreeblock!=-1){
                buffergettreefile(newnw,Config.vacanttreeblock);
                assert(newnw->id==Config.vacanttreeblock);
                Config.vacanttreeblock=newnw->next;
            }else{
                buffergettreefile(newnw,++Config.treecnt);
                newnw->id=Config.treecnt;
            }
            newnw->isLeaf=nw->isLeaf;
            newnw->num=0;
            for(int i=((M+1)>>1);i<nw->num;i++){
                newnw->keys[i-((M+1)>>1)]=nw->keys[i];
                newnw->children[i-((M+1)>>1)]=nw->children[i];
                newnw->num++;
            }
            nw->num=(M+1)>>1;


            //可加入内存回收策略
            //如果是新建的空间必须先写入，否则文件大小、读写头出问题
            // buffersettreefile(newnw,newnw->id);
            innerTreeNode* parent;
            if(father[nw->id]==-1){
                if(Config.vacanttreeblock!=-1){
                    buffergettreefile(parent,Config.vacanttreeblock);
                    // assert(parent->id==Config.vacanttreeblock);
                    Config.vacanttreeblock=parent->next;
                }else{
                    buffergettreefile(parent,++Config.treecnt);
                    parent->id=Config.treecnt;
                }
                parent->isLeaf=false;
                Config.root=parent->id;
                //可加入内存回收策略
                parent->num=1;
                parent->children[0]=nw->id;
                father[parent->id]=-1;
                //如果是新建的空间必须先写入，否则文件大小、读写头出问题
                // buffersettreefile(parent,parent->id);
            }else{
                buffergettreefile(parent,father[nw->id]);
            }
            // buffersettreefile(nw,nw->id);
            // buffersettreefile(newnw,newnw->id);
            place=nw->id;
            childid=newnw->id;
            splitkey=nw->keys[((M+1)>>1)-1];
            nw=parent;//位置要对
        }
        // setconfig(Config);
    }

    // 删除关键字
    void remove(const key_t &key) {
        
        // config Config;
        // getconfig(Config);
        innerTreeNode* nw;
        buffergettreefile(nw,Config.root);
        father[nw->id]=-1;
        while (!nw->isLeaf) {
            int i = 0;
            while (i < nw->num-1 && key > nw->keys[i]) {
                i++;
            }
            father[nw->children[i]]=nw->id;
            buffergettreefile(nw,nw->children[i]);
        }
        int i = 0;
        while (i < nw->num-1 && key > nw->keys[i]) {
            i++;
        }
        dataNode* datanw;
        buffergetdatafile(datanw,nw->children[i]);
        
        
        int j = 0;
        while (j < datanw->num && key > datanw->keys[j]) {
            j++;
        }
        if(j>=datanw->num||key!=datanw->keys[j]){
            return;
        }
        for(int k=j;k<datanw->num-1;k++){
            datanw->keys[k]=datanw->keys[k+1];
            datanw->values[k]=datanw->values[k+1];
        }
        datanw->num--;
        if(datanw->num>=(L>>1)){
            // buffersetdatafile(datanw,datanw->id);
            return;
        }
        //借用节点
        int place=i;
        if(place>0){
            dataNode* prevdatanw;
            buffergetdatafile(prevdatanw,datanw->prev);
            // assert(datanw->prev==prevdatanw->id);
            // assert(nw->children[place-1]==prevdatanw->id);
            if(prevdatanw->num>(L>>1)){
                for(int i=datanw->num;i>0;i--){
                    datanw->keys[i]=datanw->keys[i-1];
                    datanw->values[i]=datanw->values[i-1];
                }
                datanw->keys[0]=prevdatanw->keys[prevdatanw->num-1];
                datanw->values[0]=prevdatanw->values[prevdatanw->num-1];
                datanw->num++;
                prevdatanw->num--;
                // buffersetdatafile(datanw,datanw->id);
                // buffersetdatafile(prevdatanw,prevdatanw->id);
                nw->keys[place-1]=prevdatanw->keys[prevdatanw->num-1];
                // buffersettreefile(nw,nw->id);
                return;
            }
        }
        if(place<nw->num-1){
            dataNode* nextdatanw;
            buffergetdatafile(nextdatanw,datanw->next);
            // assert(datanw->next==nextdatanw->id);
            // assert(nw->children[place+1]==nextdatanw->id);
            if(nextdatanw->num>(L>>1)){
                datanw->keys[datanw->num]=nextdatanw->keys[0];
                datanw->values[datanw->num]=nextdatanw->values[0];
                datanw->num++;
                nextdatanw->num--;
                for(int i=0;i<nextdatanw->num;i++){
                    nextdatanw->keys[i]=nextdatanw->keys[i+1];
                    nextdatanw->values[i]=nextdatanw->values[i+1];
                }
                // buffersetdatafile(datanw,datanw->id);
                // buffersetdatafile(nextdatanw,nextdatanw->id);
                nw->keys[place]=datanw->keys[datanw->num-1];
                // buffersettreefile(nw,nw->id);
                return;
            }
        }
        
        int removeid;
        if(place>0){
            dataNode* prevdatanw;
            buffergetdatafile(prevdatanw,datanw->prev);
            for(int i=0;i<datanw->num;i++){
                prevdatanw->keys[prevdatanw->num+i]=datanw->keys[i];
                prevdatanw->values[prevdatanw->num+i]=datanw->values[i];
            }
            prevdatanw->num+=datanw->num;
            prevdatanw->next=datanw->next;
            if(datanw->id!=Config.dataend){
                dataNode* nextdatanw;
                buffergetdatafile(nextdatanw,datanw->next);
                nextdatanw->prev=prevdatanw->id;
                // buffersetdatafile(nextdatanw,nextdatanw->id);
            }else{
                Config.dataend=prevdatanw->id;
            }
            // buffersetdatafile(prevdatanw,prevdatanw->id);
            removeid=place;
            datanw->next=Config.vacantdatablock;
            Config.vacantdatablock=datanw->id;
        }else if(place<nw->num-1){
            dataNode* nextdatanw;
            buffergetdatafile(nextdatanw,datanw->next);
            for(int i=0;i<nextdatanw->num;i++){
                datanw->keys[datanw->num+i]=nextdatanw->keys[i];
                datanw->values[datanw->num+i]=nextdatanw->values[i];
            }
            datanw->num+=nextdatanw->num;
            datanw->next=nextdatanw->next;
            // assert(datanw->id!=Config.dataend);
            if(nextdatanw->id!=Config.dataend){
                dataNode* nextnextdatanw;
                buffergetdatafile(nextnextdatanw,nextdatanw->next);
                nextnextdatanw->prev=datanw->id;
                // buffersetdatafile(nextnextdatanw,nextnextdatanw->id);
            }else{
                Config.dataend=datanw->id;
            }
            // buffersetdatafile(datanw,datanw->id);
            removeid=place+1;
            nextdatanw->next=Config.vacantdatablock;
            Config.vacantdatablock=nextdatanw->id;
        }else{
            //不可能(除非删光了)
            // buffersetdatafile(datanw, datanw->id);
            // setconfig(Config);
            return;
        }
        
        while(true){
            //不断向上合并直到不用再合并
            nw->keys[removeid-1]=nw->keys[removeid];//之前错了removeid是一个下标
            for(int i=removeid;i<nw->num-1;i++){
                nw->keys[i]=nw->keys[i+1];
                nw->children[i]=nw->children[i+1];
            }
            nw->num--;
            if(nw->num>=(M>>1)||father[nw->id]==-1){
                // buffersettreefile(nw,nw->id);
                break;
            }
            innerTreeNode* parent;
            buffergettreefile(parent,father[nw->id]);
            // assert(parent->id==father[nw->id]);
            for(place=0;place<parent->num&&parent->children[place]!=nw->id;place++);
            //借用节点
            if(place>0){
                innerTreeNode* prevnw;
                buffergettreefile(prevnw,parent->children[place-1]);
                if(prevnw->num>(M>>1)){
                    for(int i=nw->num;i>0;i--){
                        nw->keys[i]=nw->keys[i-1];
                        nw->children[i]=nw->children[i-1];
                    }
                    nw->keys[0]=parent->keys[place-1];

                    nw->children[0]=prevnw->children[prevnw->num-1];
                    prevnw->num--;
                    parent->keys[place-1]=prevnw->keys[prevnw->num-1];

                    nw->num++;
                    // buffersettreefile(nw,nw->id);
                    // buffersettreefile(prevnw,prevnw->id);
                    // buffersettreefile(parent,parent->id);
                    break;
                }
            }
            if(place<parent->num-1){
                innerTreeNode* nextnw;
                buffergettreefile(nextnw,parent->children[place+1]);
                if(nextnw->num>(M>>1)){

                    //bug take me a year!!!!!!!! nw->num-1
                    nw->keys[nw->num-1]=parent->keys[place];
                    nw->children[nw->num]=nextnw->children[0];
                    parent->keys[place]=nextnw->keys[0];
                    for(int i=0;i<nextnw->num-1;i++){
                        nextnw->keys[i]=nextnw->keys[i+1];
                        nextnw->children[i]=nextnw->children[i+1];
                    }
                    nextnw->num--;
                    nw->num++;
                    // buffersettreefile(nw,nw->id);
                    // buffersettreefile(nextnw,nextnw->id);
                    // buffersettreefile(parent,parent->id);
                    break;
                }

            }
            //合并
            if(place>0){
                innerTreeNode* prevnw;
                buffergettreefile(prevnw,parent->children[place-1]);
                prevnw->keys[prevnw->num-1]=parent->keys[place-1];
                for(int i=0;i<nw->num;i++){
                    prevnw->keys[prevnw->num+i]=nw->keys[i];
                    prevnw->children[prevnw->num+i]=nw->children[i];
                }
                prevnw->num+=nw->num;
                // buffersettreefile(prevnw,prevnw->id);
                removeid=place;
                nw->next=Config.vacanttreeblock;
                Config.vacanttreeblock=nw->id;
                nw=parent;
            }else if(place<parent->num-1){
                innerTreeNode* nextnw;
                buffergettreefile(nextnw,parent->children[place+1]);
                nw->keys[nw->num-1]=parent->keys[place];
                for(int i=0;i<nextnw->num;i++){
                    nw->keys[nw->num+i]=nextnw->keys[i];
                    nw->children[nw->num+i]=nextnw->children[i];
                }
                nw->num+=nextnw->num;
                // buffersettreefile(nw,nw->id);
                removeid=place+1;
                nextnw->next=Config.vacanttreeblock;
                Config.vacanttreeblock=nextnw->id;
                nw=parent;
            }else{
                //不可能(除非删光了)
                // buffersettreefile(nw, nw->id);
                break;
            }
        }

        // setconfig(Config);
    }

    

    // 查找关键字
    
};
#endif

    








unsigned long long hashh(const Mystring &s){
    unsigned long long res=0;
    for(int i=0;s.c[i];i++){
        res=res*131+(unsigned long long)s.c[i];
    }
    return res;
}

    const int MAXblocknum=3000;
    const int blocklength=3000;

    #endif //MY_MEMORY_CLASS
    using namespace std;
    int main()
    {
        // const Mystring a("const323233");
        // Mystring b(a);
        // a.c[1]='8';
        // cout<<a.tostr()<<' '<<b.tostr()<<'\n';
        
        BPlusTree<sjtu::pair<unsigned long long, int>, int, 500, 500>A("datafile","treefile",false);
        int T;cin>>T;
        while(T--){
            string s;string a;int b;
            cin>>s;
            if(s=="insert"){
                cin>>a>>b;
                A.insert(sjtu::make_pair(hashh(Mystring(a)),b), b);
            }
            if(s=="delete"){
                cin>>a>>b;
                A.remove(sjtu::make_pair(hashh(Mystring(a)), b));
            }
            if(s=="find"){
                cin>>a;//cout<<"|||";
                vector<int>v;
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