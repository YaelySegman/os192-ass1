#include "types.h"
#include "stat.h"
#include "user.h"




//int test_exit(){}

//int test_wait(){}


void test_detach_success(int * ans){
  int pid;
  pid = fork();
  if(pid > 0) {
   *ans = detach(pid);
   kill(pid);
   // have a child with this pid.
}


}
void test_detach_fail(int * ans){
  int pid;

  pid = fork();
  if(pid > 0) {
   *ans = detach(pid+1); // status = -1
   kill(pid);
   // have a child with this pid.
  }

}


void test_detach_wrong_parent(int * ans){
  int pid;
  pid = fork();
  if(pid == 0) {
     // have a child with this pid.
      *ans = detach(pid);
  }
  else kill(pid);
}

//third_status = detach(77); // status = -1, because this process doesn’t

int main(void){
  int success=0, fail=0;
  int ans;
  test_detach_success(&ans);
  if(ans!=0){//here we want 0;
    fail++;
    printf(2,"test_detach_success failed\n");
  }
   else success++;
   test_detach_fail(&ans);
   if(ans==0){
     fail++;
     printf(2,"test_detach_fail failed\n");
   }
    else success++;

    test_detach_wrong_parent(&ans);
    if(ans==0){
      fail++;
      printf(2,"test_detach_wrong_parent failed\n");
    }
     else success++;

    printf(2,"num of success:%d num of failures: %d\n",success,fail );
    return 0;



}
