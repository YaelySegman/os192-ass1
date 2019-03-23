#include "types.h"
#include "stat.h"
#include "user.h"




int success=0, fail=0,ans=-2;

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

void round_robin_sanity(){
  int pid,pid2;
  pid = fork();
  if(pid>0){
    pid2=fork();
    if(pid2==0){
      int i;sleep(3);
      for(i=0;i<3;i++){

        write(2,"Going to sleep son 2\n",21);
        sleep(1);
        write(2,"woke up son 2\n",16);
      }
      write(2,"son 2 exiting\n",16);
      sleep(1);
        exit(0);
    }
    else {  wait(0);wait(0);}
  }
  else{
    int i;
    for(i=0;i<3;i++){
      write(2,"Going to sleep son 1\n",21);
      sleep(3);
      write(2,"woke up son 1\n",16);
    }
    write(2,"son 1 exiting\n",16);
    exit(0);
  }
}
void test_3sons(int pol){
  policy(pol);
  int pid,pid2,pid3;
  pid = fork();
  if(pid>0){
    sleep(1);
    pid2=fork();
    if(pid2>0){
      sleep(1);
      pid3=fork();
      if(pid3 == 0){
        //sleep(1);
        int i;
        for(i=0;i<3;i++){
          write(2,"Going to sleep son 3\n",21);
          sleep(1);
          write(2,"woke up son 3\n",15);
        }
        write(2,"son 3 exiting\n",15);
        sleep(1);
          exit(0);
      }
      else {wait(0);wait(0);wait(0);}
    }
    else{
      sleep(2);
      int i;
      for(i=0;i<3;i++){
        write(2,"Going to sleep son 2\n",21);
        sleep(1);
        write(2,"woke up son 2\n",15);
      }
      write(2,"son 2 exiting\n",15);
      sleep(1);
        exit(0);
    }
  }
  else{
    sleep(3);
    int i;
    for(i=0;i<3;i++){
      write(2,"Going to sleep son 1\n",21);
      sleep(1);
      write(2,"woke up son 1\n",15);
    }
    write(2,"son 1 exiting\n",15);
    exit(0);
  }
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
void some(){
  printf(2,"start some\n" );
  policy(2);
}
int main(void){
  //round_robin_sanity();

//  some();
  for (int i=0;i<100;i++){
  test_3sons(1);
}

  //make_test(test_exit_wait_success, 1, "test_exit_wait_success failed\n");
  //make_test(test_exit_wait_fail, -1 , "test_exit_wait_fail failed\n");
  //make_test(test_detach_success,0,"test_detach_success failed\n");
  //make_test(test_detach_fail,-1,"test_detach_fail failed\n");
  //make_test(test_detach_wrong_parent,-1,"test_detach_wrong_parent failed\n");
  printf(2,"num of success:%d num of failures: %d\n",success,fail );

  exit(0);

}
