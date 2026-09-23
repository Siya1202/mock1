#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    if(argc<2){
        cout<<"Usage : "<< argv[0]<<"<number>"<<endl;
    }
    pid_t pid=fork();
    if(pid==0){
        char *args[]={(char*)"./factorial",argv[1],NULL};
        execvp(args[0],args);
        preerror("execvp failed");
    }
    else{
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            cout<<"PArent:child finished successfully"<<endl;
        }
    }
}