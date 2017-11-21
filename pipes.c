#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  int pipe1[2]; // Parent to child
  int pipe2[2]; // Child to parent

  int READ = 0;
  int WRITE = 1;

  pipe(pipe1);
  pipe(pipe2);

  int f = fork();

  if(f){
    //Parent
    close(pipe1[READ]); //Parent sends data
    close(pipe2[WRITE]); //Parent reads data

    //Send the number
    int send = 5;
    write(pipe1[WRITE], &send, sizeof(send));
    printf("[parent] sending: %d\n", send);

    wait(0); //Not sure if this is needed?

    //Get back the mathified number
    int receive;
    read(pipe2[READ], &receive, sizeof(receive));
    printf("[parent] received: %d (should be 1755000) \n", receive);
  }

  else{
    //Child
    close(pipe1[WRITE]); //Child Reads Data
    close(pipe2[READ]); //Child Writes Data

    //Get the OG Number
    int receive;
    read(pipe1[READ], &receive, sizeof(receive));
    printf("[child] doing maths on: %d\n", receive);

    //Send out the mathified number
    int send = ((receive * 5) % 56) * 234 * 300;
    write(pipe2[WRITE], &send, sizeof(send));
  }
}
