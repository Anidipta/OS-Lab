#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int sum_res=0;
int prime(int n){if(n<2)return 0;for(int i=2;i*i<=n;i++)if(n%i==0)return 0;return 1;}
int main(int c,char* v[]){
 if(c<3)return 0;int l=atoi(v[1]),h=atoi(v[2]);
 pid_t p1=vfork();
 if(p1==0){
  for(int i=l;i<=h;i++)sum_res+=i;
  printf("Child1 pid=%d ppid=%d\n",getpid(),getppid());
  _exit(0);
 }
 pid_t p2=vfork();
 if(p2==0){
  printf("Child2 pid=%d ppid=%d sum=%d prime=%s\n",getpid(),getppid(),sum_res,prime(sum_res)?"yes":"no");
  _exit(0);
 }
 printf("Parent pid=%d child1=%d child2=%d\n",getpid(),p1,p2);
}

// ./p1 2 6
// Child1 pid=22297 ppid=22296
// Child2 pid=22298 ppid=22296 sum=20 prime=no
// Parent pid=22296 child1=22297 child2=22298