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
    try{
        some_local_state--;//Intentional race condition
    }
    catch (...)
    {
        my_thread.join();
        throw;
    }
    my_thread.join();
}

int main(){
    oops();
    return 0;
}
