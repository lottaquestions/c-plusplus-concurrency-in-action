#include <iostream>
#include <thread>

class thread_guard{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) :
       t(t_)
    {}
    ~thread_guard(){
        if (t.joinable()){
            t.join();
        }
    }
    thread_guard(thread_guard const &)=delete;
    thread_guard& operator=(thread_guard const &)=delete;
};

struct func
{
    unsigned int &i;
    func(unsigned int &i_) : i(i_){}
    void operator() (){
        for (unsigned j = 0; j < 260;  ++j)
            i = (i+1)& 0x0FF;
        std::cout << i <<" thread\n";
    }
};

void oops (){
    unsigned int some_local_state=0;
    func myfunc(some_local_state);
    std::thread my_thread(myfunc);
    thread_guard g(my_thread);
    some_local_state=300;
    std::cout << some_local_state <<" main\n";
}

int main(){
    oops();
    return 0;
}
