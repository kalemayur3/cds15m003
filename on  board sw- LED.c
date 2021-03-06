
#include <stdint.h>
#include "tm4c123gh6pm.h"

	
void PortD_Init(void);
void Delay(unsigned long time);
void PortF_Init(void);

int main(void){
	long led;
	PortD_Init();
	
	
	
	
	while(1)
	{led=GPIO_PORTD_DATA_R;
		led=led^0x09;
		GPIO_PORTD_DATA_R=led;
		Delay(1);
		
	}
	
}
/ 2. Declarations Section
//   Global Variables
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)

//   Function Prototypes
void PortF_Init(void);
void Delay(void);
void EnableInterrupts(void);


// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){    
  TExaS_Init(SW_PIN_PF40,LED_PIN_PF321); 
  // TExaS_Init initializes the real board grader for lab 4
  PortF_Init();        // Call initialization of port PF4, PF3, PF2, PF1, PF0    
  EnableInterrupts();  // The grader uses interrupts
  while(1){
    SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
    SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2
    if(SW1&&SW2){                     // both pressed
      GPIO_PORTD_DATA_R = 0x04;       // LED is blue
    } else{                           
      if(SW1&&(!SW2)){                // just SW1 pressed
        GPIO_PORTD_DATA_R = 0x02;     // LED is red
      } else{                        
        if((!SW1)&&SW2){              // just SW2 pressed
          GPIO_PORTD_DATA_R = 0x08;   // LED is green
        }else{                        // neither switch
          GPIO_PORTD_DATA_R = 0x00;   // LED is off
        }
      }
    }
  }
}

void PortD_Init(void)
	{volatile unsigned long delay;
		SYSCTL_RCGC2_R |= 0x08;           // Port D clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTD_DIR_R |= 0x09;         // PD3 PD0 output
  GPIO_PORTD_AFSEL_R &= ~0x09;      // not alternative
  GPIO_PORTD_AMSEL_R &= ~0x09;      // no analog
  GPIO_PORTD_PCTL_R &= ~0x0000F00F; // bits for PD3, PD0
  GPIO_PORTD_DEN_R |= 0x09;         // enable PD3, PD0
	}
	
	
	void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
	void Delay(unsigned long time)
	{
		unsigned long i;
		while(time>0)
		{i=1333333;
			while(i>0)
			{i=i-1;
			}
			time=time-1;
		}
	}

		
	
	
	