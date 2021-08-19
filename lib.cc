#include <stdio.h>

extern "C" {


    int get_some_number() {
        puts("get_some_number");        

        return 1;
    }

    int exportable() {
        puts("exportable");        
        return get_some_number();
    }

}