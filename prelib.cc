#include <iostream>
#include <dlfcn.h>

extern void lol();

///extern "C" is actually optional and used just to simplify symbol lookup (remove mangled methods) 
extern "C" {

    extern int exportable();

    extern void do_thing();

    int start() {

        dlopen("./lib.so", RTLD_NOW | RTLD_GLOBAL);
        std::cout << __PRETTY_FUNCTION__ << std::endl
         << exportable()
         << std::endl;
        return 1;
    }

    void test() {
        do_thing();
        lol();
    }
}


