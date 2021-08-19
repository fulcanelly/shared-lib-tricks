#include <dlfcn.h>
#include <iostream>

using std::cout;
using std::endl;


struct dynamic_library {

    void* handle;

    dynamic_library(void* handle): handle(handle) {
        handle_dlerror(handle);
    }

    template<class T> 
    auto get_function(const char* name) {
        auto func = dlsym(handle, name);

        handle_dlerror(func);

        return (T*)func;
    }


    
    //temporary stub methods
    void close() {
     //   cout << "close code: " << dlclose(handle) << endl;

    }

protected:
    void handle_dlerror(void* any) {
        if (any == nullptr) {
            
            throw std::runtime_error(dlerror());
        } 

    }
};

/**
 * 
 * first example 
 */

extern "C" int get_some_number() {
    auto get_some_number_next = (decltype(get_some_number)*)dlsym(RTLD_NEXT, "get_some_number");

    std::cout << "<> intercepted method called, the actual number: " << get_some_number_next() << endl << std::endl;
    return 123;
}

void intercept_shared_function() {
    cout << "it intercepts call to lib.cc:int get_some_number()" << endl;
    auto it = dynamic_library(dlopen("./prelib.so", RTLD_LAZY ));
    it.get_function<int()>("start")();
    cout << endl;
    it.close();

}


/**
 * 
 * second example 
 */


extern void lol() __attribute__ ((weak));;

void load_lol_from_lib_to_all() {

    cout << "it should print lol twice which mean it injected lol() from another.so into executable and prelib.so" << endl;
    auto another = dynamic_library(dlopen("./another.so", RTLD_LAZY | RTLD_GLOBAL));
    lol();
    auto prelib = dynamic_library(dlopen("./prelib.so", RTLD_LAZY));
    prelib.get_function<int()>("test")();
    prelib.close();
    another.close();
}


/**
 * todo
 */


void own_namespace() {

    auto lib = dynamic_library(
        dlmopen(LM_ID_NEWLM, "./prelib.so", RTLD_LAZY));

}


int main() {
    
    //for some reason reverse order will break interception 
    intercept_shared_function();
    cout << "===" << endl;

    load_lol_from_lib_to_all();
    cout << "===" << endl;


}
