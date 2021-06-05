#define USE_AND_OR
#include <uart.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern QueueHandle_t xUartQueue;


void init_UART1(void){
    CloseUART1();
    ConfigIntUART1(UART_RX_INT_DIS | UART_TX_INT_DIS);
    OpenUART1(UART_EN, UART_TX_ENABLE,25);
}

void vTaskUARTReceiver(void *p){
    unsigned int c;
    unsigned char chaine[5];
    unsigned int val,mul;
    while(1){
        int i=0; val=0; mul=1;
      while(1){
        if(DataRdyUART1()){
        c=ReadUART1();
        if(c!='\r')
            if((c>='0')&&(c<='9')&&(i<5))
                chaine[i++] = c;
            else;
        else{//fin de saisie par detection de retour
            i--;
            while(i>=0){
                val = val + (chaine[i--] - '0') * mul;
                mul=mul * 10;
            } break;

        }
        
        }
        else;
    }//fin de saisie
        xQueueSend(xUartQueue,&val,portMAX_DELAY);
  }
}

void vTaskUARTOC1(void *p){
    unsigned int I;
    while (1) {
        xQueueReceive(xUartQueue, &I, portMAX_DELAY);
        OC1RS = I;
}
}

