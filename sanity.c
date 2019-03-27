#include "types.h"
#include "user.h"
#include "fcntl.h"

int success=0, fail=0,ans=-2, fibNum=40;

// void test_path(){
//     int num=0;
//     num = exec("mkdir dir");
//     num+=exec("cd dir");
//     num+=exec("echo test worked");

// }

void test_exit_wait_success(){

    int pid = fork();
    if(pid!=0){
      wait(&ans);
    }
    else {
      exit(1);}
}
void test_exit_wait_fail(){

  int pid = fork();
  if(pid>0){
    wait(&ans);
  }
  else exit(-1);
}
void test_detach_success(){
  int pid;
  pid = fork();
  if(pid > 0) {
   ans = detach(pid);
   exit(0);

} else
  {
    sleep(10);
    exit(0);
  }
}
void test_detach_fail(){
  int pid;
  pid = fork();
  if(pid > 0) {
    wait(0);
   ans = detach(pid+9); // status = -1

  }
  else
  {
    exit(0);
  }

}

void test_detach_wrong_parent(){
  int pid;
  pid = fork();
  if(pid == 0) {
      ans = detach(pid); // status = -1
      exit(0);
  }
  else wait(0);
}

int fib(uint num){
    if (num == 0)
        return 0;
    if(num == 1)
        return 1;
    return fib(num-1) + fib(num-2);
}


void round_robin_sanity(){
    printf(1,"\n=====Started round_robin_sanity test======\n");
    int pid;
    for (int i=0;i<50;i++){
        
        pid  = fork();
        if(pid == 0 ){
            sleep(50-i);
             fib(fibNum);
            printf(1,"chiled %d \n",i);

            exit(0);
        }

    }
    for(int j=0; j<50 ; j++){
        int ret;
        wait(&ret);
        ans += ret;
    }
}
void priority_policy_sanity(){
    printf(1,"\n=======Started priority_policy_sanity test======\n");
    policy(2);
    int pid, status;
    for (int i = 0; i < 40; ++i) {
        pid = fork();
        if (pid == 0) {
             sleep(40-i);
            if ((i % 10) == 0) {
                priority(1);
            } else {
                priority(i % 10);
            }
        
            fib(fibNum);
            printf(1,"chiled %d \n",i);
            exit(0);
        }
    }
    for (int j = 0; j < 40; ++j) {
        wait(&status);
        ans +=status;
    }
    policy(1);
}
void extpriority_policy_sanity(){
        printf(1,"\n=======Started extpriority_policy_sanity test======\n");
    policy(3);
    int pid, status;
    for (int i = 0; i < 40; ++i) {
        pid = fork();
        if (pid == 0) {
            
          sleep(40-i);
            priority(i % 10);
        
        
            fib(fibNum);
            printf(1,"chiled %d \n",i);
            exit(0);
        }
    }
    for (int j = 0; j < 40; ++j) {
        wait(&status);
        ans +=status;
    }
    policy(1);
}
void make_test(void (*f)(void) , int expected ,char * fail_msg){

  f();
  if(ans == expected)
    success++;
  else {
    fail++;
    printf(1,"%s\n",fail_msg);
  }

}
int main(void){
  

    make_test(test_exit_wait_success, 1, "test_exit_wait_success failed\n");
    make_test(test_exit_wait_fail, -1 , "test_exit_wait_fail failed\n");
    // make_test(test_detach_success,0,"test_detach_success failed\n");
 
    make_test(test_detach_fail,-1,"test_detach_fail failed\n");
    make_test(test_detach_wrong_parent,-1,"test_detach_wrong_parent failed\n");
    ans =0;
    make_test(round_robin_sanity,0,"test_round_robin_sanity faild, ho no !\n");
    ans =0;
    make_test(priority_policy_sanity,0,"priority_policy_sanity faild, ho no !\n");
    ans = 0;
    make_test(extpriority_policy_sanity,0,"extpriority_policy_sanity faild, ho no!\n ");

    printf(1,"num of success:%d num of failures: %d\n",success,fail );

    exit(0);
  }