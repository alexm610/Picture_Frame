#ifndef BLINKY_TASK_H_
#define BLINKY_TASK_H_

#define DELAY_BLINKY 2000000
/* Expose the function so main.c can call xTaskCreate() */
void Blinky(void);

#endif /* BLINKY_TASK_H_ */
