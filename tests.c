#include "types.h"
#include "stat.h"
#include "user.h"


//int test_exit(){}

//int test_wait(){}

int success=0, fail=0,ans=1;
void test_detach_success(){
  int pid;
  pid = fork();
  if(pid > 0) {
   ans = detach(pid);

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

void make_test(void (*f)(void) , int expected ,char * fail_msg){

  (*f)();
  if(ans == expected)
    success++;
  else {
    fail++;
    printf(2,"%s\n",fail_msg);
  }

}

int main(void){

   make_test(test_detach_success,0,"test_detach_success failed\n");
   make_test(test_detach_fail,-1,"test_detach_fail failed\n");
   make_test(test_detach_wrong_parent,-1,"test_detach_wrong_parent failed\n");
   printf(2,"num of success:%d num of failures: %d\n",success,fail );

   exit(0);

}
