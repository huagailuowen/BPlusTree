#include<bits/stdc++.h>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
const int N=30000;
// template <typename T>
// class SafeQueue
// {
// private:
//     std::queue<T> m_queue; //利用模板函数构造队列
 
//     std::mutex m_mutex; // 访问互斥信号量
 
// public:
//     SafeQueue() {}
//     SafeQueue(SafeQueue &&other) {}
//     ~SafeQueue() {}
 
//     bool empty() // 返回队列是否为空
//     {
//         std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
 
//         return m_queue.empty();
//     }
 
//     int size()
//     {
//         std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
 
//         return m_queue.size();
//     }
 
//     // 队列添加元素
//     void enqueue(T &t)
//     {
//         std::unique_lock<std::mutex> lock(m_mutex);
//         m_queue.emplace(t);
//     }
 
//     // 队列取出元素
//     bool dequeue(T &t)
//     {
//         std::unique_lock<std::mutex> lock(m_mutex); // 队列加锁
 
//         if (m_queue.empty())
//             return false;
//         t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，并进行右值引用
 
//         m_queue.pop(); // 弹出入队的第一个元素
 
//         return true;
//     }
// };
// // Submit a function to be executed asynchronously by the pool
//     template <typename F, typename... Args>
//     auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))> 
//     {
//         // Create a function with bounded parameter ready to execute
//         std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // 连接函数和参数定义，特殊函数类型，避免左右值错误

//         // Encapsulate it into a shared pointer in order to be able to copy construct
//         auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);  

//         // Warp packaged task into void function
//         std::function<void()> warpper_func = [task_ptr]()
//         {
//             (*task_ptr)();
//         };  

//         // 队列通用安全封包函数，并压入安全队列
//         m_queue.enqueue(warpper_func);

//         // 唤醒一个等待中的线程
//         m_conditional_lock.notify_one();  

//         // 返回先前注册的任务指针
//         return task_ptr->get_future();
//     }
// std::mutex mtx_tree[N];
// std::condition_variable cv_tree[N];
// // theard_pool pool(4);
std::shared_mutex t;
void test()
{
    std::unique_lock<std::shared_mutex> lock(t);
    // cout<<"test"<<endl;
    sleep(5);
    lock.unlock();
    while(1){
        // std::cerr<<lock.owns_lock()<<endl;
        // getchar();
    }

}
void test2()
{
    std::cerr<<"Oksss"<<endl;

    std::shared_lock<std::shared_mutex> lock(t);
    // cout<<"test"<<endl;
    std::cerr<<"Ok"<<endl;
    lock.unlock();
}

int main()
{
    std::thread t1(test);
    sleep(1);
    std::thread t2(test2);
    t1.join();
    t2.join();
    return 0;
}