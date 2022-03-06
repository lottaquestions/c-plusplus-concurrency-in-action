#include <iostream>
#include <thread>
#include <vector>
#include <functional> //for mem_fn
#include <algorithm> // for for_each

void func(unsigned int &i, unsigned id );

void func(unsigned int &i, unsigned id ){
    int k = i;
    for (unsigned j = 0; j < 260;  ++j)
        k = (k+1)& 0x0FF;
    std::cout << k <<" " <<id<<" thread\n";
}

void f(){
    unsigned int some_local_state=0;
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < 20; ++i){
        threads.push_back(std::thread(func, std::ref(some_local_state), i));
    }
    
    std::for_each(threads.begin(), threads.end(),
        std::mem_fn(&std::thread::join));
}

int main(){
    f();
    return 0;
}
