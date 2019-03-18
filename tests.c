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

   // have a child with this pid.
} else
  {
    sleep(10);
    exit(0);
  }


}
void test_detach_fail(int * ans){
  int pid;
  pid = fork();
  if(pid > 0) {
    wait(0);
   *ans = detach(pid+9); // status = -1

   // have a child with this pid.
  }
  else
  { //sleep(10);
    exit(0);
  }

}

void test_detach_wrong_parent(int * ans){
  int pid;
  pid = fork();
  if(pid == 0) {
      *ans = detach(pid); // status = -1
      exit(0);
  }
  else wait(0);
}



int main(void){
  static int success=0, fail=0;
  int * ans = malloc(sizeof(int));
  *ans = 1;
  test_detach_success(ans);
  if(*ans!=0){//here we want 0;
    fail++;
    printf(2,"test_detach_success failed\n");
  }
   else success++;

   test_detach_fail(ans);
   if(*ans!=-1){
     fail++;
     printf(2,"test_detach_fail failed\n");
   }
   else success++;

    test_detach_wrong_parent(ans);
    if(*ans!=-1){
      fail++;
      printf(2,"test_detach_wrong_parent failed\n");
    }
    else
      success++;

    printf(2,"num of success:%d num of failures: %d\n",success,fail );
    exit(0);



}
