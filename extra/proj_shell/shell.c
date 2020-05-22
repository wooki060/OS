#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#define MAX_COMMAND 2097152
int pro(char *inp){
	char *outp[1000];
	char *command,*parse;
	int count,pid[100000],pcount;
    pcount=0;
    while((command = strtok_r(inp,";\n",&inp))){
        count=0;
        while((parse = strtok_r(command," ",&command)))
            outp[count++] = parse;
        outp[count] = '\0';
        if(strcmp(outp[count-1],"quit") == 0){
            for(int i=0;i<pcount;i++) if(pid[i] > 0) wait(NULL);
            return 1;
        }
        pid[pcount] = fork();
        if(pid[pcount] < 0){
            fprintf(stdout,"fail fork\n");
        }
        else if(pid[pcount] == 0){
            if(execvp(outp[0],outp) == -1){
                fprintf(stdout,"%s : command not found\n",outp[0]);
                exit(0);
            }
        }
        pcount++;
	}
    int stat;
    for(int i=0;i<pcount;i++){
        if(pid[i] > 0){
            wait(&stat);
            if(stat != 0) fprintf(stdout,"wait error number is %d\n",pid[i]);
        }
    }
    return 0;
}
int main(int argc, char *argv[]){
    char inp[MAX_COMMAND];
    if(argc == 1){
        while(1){
            fprintf(stdout,"prompt> ");
            if(fgets(inp, MAX_COMMAND-1, stdin) == 0) break;
            if(strcmp(inp,"quit\n") == 0)
                break;
            if(pro(inp) == 1) break;
        }
    }
    else if(argc == 2){
        FILE *fp;
        if(!(fp= fopen(argv[1],"r")))
            fprintf(stdout,"%s is not exist\n",argv[1]);
        else{
            while(fgets(inp,MAX_COMMAND-1,fp) != 0){
                fprintf(stdout,"%s",inp);
                if(pro(inp)==1) break;
            }
        }
    }
    else fprintf(stdout,"you must input one file name\n");
    exit(0);
}
