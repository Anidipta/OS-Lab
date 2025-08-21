#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int ae[1000],ap[1000],ne=0,np=0;

int prime(int n){if(n<2)return 0;for(int i=2;i*i<=n;i++)if(n%i==0)return 0;return 1;}

void printarr(char* t,int a[],int n){
    printf("%s:\n",t);
    for(int i=0;i<n;i++){
        printf("%d",a[i]);if(i<n-1)printf(",");
    }
    printf("\n");
}

int main(int c,char* v[]){
    if(c<3)return 0;int l=atoi(v[1]),h=atoi(v[2]);
    
    pid_t p1=vfork();
    if(p1==0){
    int ao[1000],no=0;
    for(int i=l;i<=h;i++){if(i%2==0)ae[ne++]=i;else ao[no++]=i;}
    printarr("even",ae,ne);printarr("odd",ao,no);
    printf("Child1 pid=%d ppid=%d\n",getpid(),getppid());_exit(0);
    }
    
    pid_t p2=vfork();
    if(p2==0){
    int an[1000],nn=0;
    for(int i=l;i<=h;i++){if(prime(i))ap[np++]=i;else an[nn++]=i;}
    printarr("prime",ap,np);printarr("nonprime",an,nn);
    printf("Child2 pid=%d ppid=%d\n",getpid(),getppid());_exit(0);
    }
    
    pid_t p3=vfork();
    if(p3==0){
    int se=0,sp=0;for(int i=0;i<ne;i++)se+=ae[i];for(int i=0;i<np;i++)sp+=ap[i];
    printf("sum_even=%d\nsum_prime=%d\n",se,sp);
    printf("Child3 pid=%d ppid=%d\n",getpid(),getppid());_exit(0);
    }
    
    while(wait(0)>0);
    printf("Parent pid=%d child1=%d child2=%d child3=%d\n",getpid(),p1,p2,p3);
}

// ./p2 2 6
// even:
// 2,4,6,8
// odd:
// 3,5,7,9
// Child1 pid=10693 ppid=10692
// prime:
// 2,3,5,7
// nonprime:
// 4,6,8,9
// Child2 pid=10694 ppid=10692
// sum_even=20
// sum_prime=17
// Child3 pid=10695 ppid=10692
// Parent pid=10692 child1=10693 child2=10694 child3=10695