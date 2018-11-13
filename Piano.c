// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"
#include "..//FlagUtils.h"

// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	unsigned long volatile dummyDelay;
  INVOKE(SET_FLAG, SYSCTL_RCGC2_GPIOE, SYSCTL_RCGC2_R); // activate port E
  dummyDelay = SYSCTL_RCGC2_R; // make a dummy delay by reading value from register
	INVOKE(CLEAR_FLAG, PMC0 | PMC1 | PMC2 | PMC3, GPIO_PORTE_PCTL_R);
	INVOKE(CLEAR_FLAG, PIN0 | PIN1 | PIN2 | PIN3, GPIO_PORTE_AMSEL_R, GPIO_PORTE_AFSEL_R, GPIO_PORTE_DIR_R);
	INVOKE(SET_FLAG, PIN0 | PIN1 | PIN2 | PIN3, GPIO_PORTE_DEN_R);  
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  return GPIO_PORTE_DATA_R & 0xF;
}
