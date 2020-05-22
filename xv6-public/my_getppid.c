#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
    printf(1, "my pid is %d\nmy ppid is %d\n",getpid(),getppid());
    exit();
}
