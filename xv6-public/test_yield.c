#include "types.h"
#include "stat.h"
#include "user.h"
int main(int argc, char *argv[]){

    int pid;
    pid = fork();
    while(1){
        yield();
        if(pid > 0){
            printf(1,"Parent\n");
        }
        else if(pid == 0){
            printf(1,"Child\n");
        }
        else{
            printf(1,"fork failed\n");
            exit();
        }
    }

}
