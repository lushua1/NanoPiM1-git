#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include "libfahw.h"

#define STATUS_CHANGE_TIMES     (5)

int pin = GPIO_PIN(7);
int pin1 = GPIO_PIN(8);
int value;

void sigrootine(int signo)
{
  int ret = -1;
//  printf("adadadsad\n");
  if(getGPIOValue(pin1))
  {
      value = GPIO_HIGH;
      printf("HIGH!\n");
  }else{
      value = GPIO_LOW;
      printf("LOW!\n");
  }

  if ((ret = setGPIOValue(pin, value)) > 0) {
      printf("%d: GPIO_PIN value is %d\n", pin, value);
   } else {
      printf("setGPIOValue(%d) failed\n", pin);
   }

}

int main(int argc, char ** argv) 
{
    //int pin = GPIO_PIN(7);
    //int pin1 = GPIO_PIN(8);
    //int i, value, board;
    int board;
    int ret = -1;

    struct itimerval valueI,ovalue;
    signal(SIGALRM,sigrootine);
    valueI.it_value.tv_sec = 0;
    valueI.it_value.tv_usec = 500000;
    valueI.it_interval.tv_sec = 0;
    valueI.it_interval.tv_usec = 500000; 
    setitimer(ITIMER_REAL,&valueI,&ovalue);
    
    if ((board = boardInit()) < 0) {
        printf("Fail to init board\n");
        return -1;
    }
    if (board == BOARD_NANOPC_T2 || board == BOARD_NANOPC_T3)
        pin = GPIO_PIN(15);
    
    if (argc == 2)
        pin = GPIO_PIN(atoi(argv[1]));
    if ((ret = exportGPIOPin(pin)) == -1) {   
        printf("exportGPIOPin(%d) failed\n", pin);
    }
    if ((ret = setGPIODirection(pin, GPIO_OUT)) == -1) {
        printf("setGPIODirection(%d) failed\n", pin);
    }

    if ((ret = exportGPIOPin(pin1)) == -1) {
        printf("exportGPIOPin(%d) failed\n", pin1);
    }


    if ((ret = setGPIODirection(pin1, GPIO_IN)) == -1) {
        printf("setGPIODirection(%d) failed\n", pin);
    }

    while(1){
/*
    for (i = 0; i < STATUS_CHANGE_TIMES; i++) {
        if (i % 2) {
            value = GPIO_HIGH;
        } else {
            value = GPIO_LOW;
        }
        if ((ret = setGPIOValue(pin, value)) > 0) {
            printf("%d: GPIO_PIN(%d) value is %d\n", i+1, pin, value);
        } else {
            printf("setGPIOValue(%d) failed\n", pin);
        }
        sleep(1);
    }*/
    }
    unexportGPIOPin(pin);
    return 0;
}
