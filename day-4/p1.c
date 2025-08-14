#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fact(int n){int f=1;for(int i=2;i<=n;i++)f*=i;return f;}

int main(){
    int n=7,sum=0;
    for(int i=1;i<=n;i++){
        pid_t pid=fork();
        if(pid==0){
            long long f=fact(i);
            printf("Child PID:%d PPID:%d\n",getpid(),getppid());
            exit(f);
        }
    }
    for(int i=1;i<=n;i++){
        int st;pid_t cp=wait(&st);
        sum+=WEXITSTATUS(st);
        printf("Parent got %d from child %d\n",WEXITSTATUS(st),cp);
        if (i==n)
            printf("%d!= %lld\n",i,WEXITSTATUS(st));
    }
    printf("Sum =%d\n",sum);
}


// Child PID:13681 PPID:13680
// Child PID:13682 PPID:13680
// Child PID:13683 PPID:13680
// Child PID:13684 PPID:13680
// Child PID:13685 PPID:13680
// Parent got 1 from child 13681
// Parent got 2 from child 13682
// Parent got 6 from child 13683
// Parent got 24 from child 13684
// Parent got 120 from child 13685
// 5!= 120
// Sum = 153