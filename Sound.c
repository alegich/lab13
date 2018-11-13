// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

unsigned char Index;  

// 3-bit 16-element sine wave
// const unsigned char SineWave[16] = {4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3};
// 4-bit 16-element sine wave
unsigned char SineWave[16] = {9,11,13,15,15,15,13,11,9,7,5,3,3,3,5,7};
unsigned char EmptyWave[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
unsigned char* outWave = EmptyWave;

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();          // Port B is DAC
  Index = 0;
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = 50000 - 1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
  NVIC_ST_CTRL_R = 0x0007;  // enable SysTick with core clock and interrupts  
}

//int enabled = 0;

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	NVIC_ST_RELOAD_R = period - 1; // reload value
	outWave = SineWave;
}

// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	outWave = EmptyWave;
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
  //GPIO_PORTF_DATA_R ^= 0x08;     // toggle PF3, debugging
  Index = (Index + 1) & 0x0F;  
  DAC_Out(outWave[Index]);
}
