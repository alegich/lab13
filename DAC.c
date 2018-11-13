// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"
#include "..//FlagUtils.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	unsigned long volatile dummyDelay;
  INVOKE(SET_FLAG, SYSCTL_RCGC2_GPIOB, SYSCTL_RCGC2_R); // activate port B
  dummyDelay = SYSCTL_RCGC2_R; // make a dummy delay by reading value from register
	INVOKE(CLEAR_FLAG, PMC0 | PMC1 | PMC2 | PMC3, GPIO_PORTB_PCTL_R);
	INVOKE(CLEAR_FLAG, PIN0 | PIN1 | PIN2 | PIN3, GPIO_PORTB_AMSEL_R, GPIO_PORTB_AFSEL_R);
	INVOKE(SET_FLAG, PIN0 | PIN1 | PIN2 | PIN3, GPIO_PORTB_DIR_R, GPIO_PORTB_DR8R_R, GPIO_PORTB_DEN_R);
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = data;
}
