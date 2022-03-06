#include <iostream>
#include <thread>
#include <unistd.h>

class scoped_thread{
    std::thread t;
public:
    explicit scoped_thread (std::thread t_) :
       t(std::move(t_)){
        if (!t.joinable()){
            std::cout << "No thread. Error \n";
            throw std::logic_error("No thread");
        }
        else
            std::cout<<"Thread should be up and running \n";
    }
    ~scoped_thread(){
        t.join();
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete;
};

struct func
{
    int& i;
    func(int &i_) : i(i_){}
    void operator() (){
        for (unsigned j = 0; j < 100000000;  ++j)
            i = (i+1)& 0x0FF;;
        std::cout << i <<" thread\n";
    }
};

void f (){
    unsigned int some_local_state=0;
    scoped_thread t( std::thread{func(some_local_state)});
    some_local_state = 300 ;
    sleep(2);
    std::cout << some_local_state <<" main\n";
}

int main(){
    f();
    return 0;
}
