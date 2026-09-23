#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void forkoddeven()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        cout << "child pid=" << getpid() << "ppid" << getppid();
        for (int i = 1; i <= 10; i += 2)
        {
            cout << i << "\n";
        }
    }
    else
    {
        cout << "parent pid=" << getpid() << "ppid" << getppid();
        for (int i = 2; i <= 10; i += 2)
        {
            cout << i << "\n";
        }
        wait(NULL);
        cout << "child reaped";
    }
}

void orphan()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(2);
        cout << "child pid=" << getpid() << "ppid" << getppid();
    }
    else
    {
        cout << "parent pid" << getpid();
    }
}

void zombie()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        cout << "child pid=" << getpid() << "ppid" << getppid();
    }
    else
    {
        cout << "parent pid" << getpid();
        sleep(10);
    }
}

int main()
{
    int ch;
    cout << "1.ForkOddEven 2.Orphan 3.Zombie\nChoice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        forkoddeven();
        break;
    case 2:
        orphan();
        break;
    case 3:
        zombie();
        break;
    default:
        cout << "Invalid choice\n";
    }
    return 0;
}
