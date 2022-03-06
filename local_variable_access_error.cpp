#include <iostream>
#include <thread>

struct func
{
    int& i;
    func(int &i_) : i(i_){}
    void operator() (){
        for (unsigned j = 0; j < 100000000;  ++j)
            i = (i++)& 0x0FFFF;
    }
};

void oops (){
    int some_local_state=0;
    func myfunc(some_local_state);
    std::thread my_thread(myfunc);
    my_thread.detach();
}

int main(){
    oops();
    return 0;
}
