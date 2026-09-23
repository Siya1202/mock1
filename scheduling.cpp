#include <iostream>
using namespace std;

int n;
int bt[20],prior[20],p[20];

void input(){
    count<<"ENTER NUMBER OF PROCESSES: ";
    cin>>n;
    for(int i=0;i<n;i++){
        p[i]=i+1;
        cout<<"BURST TIME OF "<<p[i]<<" : ";
        cin>>b[i];
        cout<<"PRIORITY TIME OF "<<p[i]<<" : ";
        cin>>p[i];
    }
}

void print(int pid[],int bt,int prio[],int tat[],int wt[]]){
    int awt=0,atat=0
    cout<<"\nPID\tBURST TIME\tPRIORITY\tWATING\TURNAROUND\n";
    for(int i=0;i<n;i++){
        cout << "P" << pid[i] << "\t" << bt[i] << "\t" <<prio[i]<<"\t"<< wt[i] << "\t" << tat[i] << "\n";
        awt += wt[i];
        atat += tat[i];
    }
    cout << "Average Waiting Time = " << awt / n << endl;
    cout << "Average Turnaround Time = " << atat / n << endl;
}

void cfs(){
    int wt[n],tat[n];
    wt[0]=0;
    for(int i=0;i<n-1;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
    }
    print(p,bt,prior,tat,wt);
}

void sjf(){
    int b[n];
    int pid[n];
    for(int i=0;i<n;i++){
        b[i]=bt[i];
        pid[i]=p[i];
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(b[j]>b[j+1]){
                swap(b[j],b[j+1]);
                swap(pid[j],pid[j+1]);
            }
        }
    }
    int wt[n],tat[n];
    wt[0]=0;
    for(int i=0;i<n-1;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
    }
    print(p,bt,prior,tat,wt);
}

void priority(){
    int b[n];
    int pid[n];
    int pr[n];
    for(int i=0;i<n;i++){
        pr[i]=prior[i];
        b[i]=bt[i];
        pid[i]=p[i];
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(pr[j]>pr[j+1]){
                swap(pr[j],pr[j+1]);
                swap(b[j],b[j+1]);
                swap(pid[j],pid[j+1]);
            }
        }
    }
    int wt[n],tat[n];
    wt[0]=0;
    for(int i=0;i<n-1;i++){
        wt[i]=wt[i-1]+bt[i-1];
    }
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
    }
    print(p,bt,prior,tat,wt);

}

void roundrobin(){
    int q;
    cout<<"ENTER THE TIME QUANTUM: ";
    cin>>q;
    int rem[n],wt[n],tat[n], t=0,isdone=0;
    for(int i=0;i<n;i++){
        rem[i]=bt[i];
    }
    while(isdone<n){
        bool didwork=false;
        for(int i=0;i<n;i++){
            if(rem[i]>0){
                didwork=true;
                if(rem[i]>q){
                    t+=q;
                    rem[i]-=q;
                }
                else{
                    t+=rem[i];
                    wt[i]=t-bt[i];
                    rem[i]=0;
                    isdone++;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
    }
    print(p,bt,prior,tat,wt);
}

int main() {
    input();
    int ch;
    do {
        cout << "\n1.FCFS 2.SJF 3.Priority 4.Round Robin 5.Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: priority(); break;
            case 4: roundRobin(); break;
            case 5: break;
            default: cout << "Invalid choice\n";
        }
    } while (ch != 5);
    return 0;
}