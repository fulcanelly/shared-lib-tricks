
#include <stdio.h>

extern "C" {
    int exportable() {
        puts(__FILE__);
        puts(__PRETTY_FUNCTION__);
        return 2332;
    }


    void do_thing() {
        puts(__PRETTY_FUNCTION__); 
        puts("thing");
    }

    
}

void lol() {
    puts("lol!");
}