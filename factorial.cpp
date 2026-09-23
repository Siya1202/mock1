#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[]){
    if(argc<2){
        cout<<"Usage : "<< argv[0]<<"<number>"<<endl;
    }
    int n=atoi(argv[0]);
    unsigned long long f=1;
    for(int i=0;i<=n;i++){
        f*=i;
    }
    cout<<"child:factorial of "<<n<<"="<<f;
    cout<<"parent"<<getpid();
    return 0;
}