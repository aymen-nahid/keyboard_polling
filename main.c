/*
 * File:   main.c
 *
 * Created by Nahid mohammed Aymen
 */
#define USE_AND_OR
#include<timer.h>
#include<outcompare.h>
#include <p24Fxxxx.h>
#include "FreeRTOS.h"
#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "list.h"


_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRI)

/*
 *
 */
void vApplicationIdleHook(void);
unsigned int ucPollKeyboard(void);
void vKeyboardTask(void *pv);
void vPortETask(void *p);
void vTaskUARTReceiver(void *p);
void vTaskUARTOC1(void *p);
void init_OC1();
void init_UART1(void);

QueueHandle_t xQueueKeyboard;
QueueHandle_t xUartQueue;

int main(int argc, char** argv) {
    init_OC1();
    init_UART1();
    xQueueKeyboard = xQueueCreate(5, sizeof (unsigned int));
    xUartQueue = xQueueCreate(1, sizeof (unsigned int));

    xTaskCreate(vKeyboardTask, "ClavierTask", 150, NULL, 1, NULL);
    xTaskCreate(vPortETask, "PortE", 150, NULL, 1, NULL);
    xTaskCreate(vTaskUARTReceiver, "UARTR", 150, NULL, 1, NULL);
      xTaskCreate(vTaskUARTOC1, "UARTOC", 150, NULL, 1, NULL);

    vTaskStartScheduler();
    // On atteint ce point si le scheduler sâ€™est arrÃªtÃ© Ã  cause dâ€™un problÃ¨me ou il a Ã©tÃ© arrÃªtÃ© explicitement par le code
    return (EXIT_SUCCESS);

}

void vApplicationIdleHook(void) {
    // si on souhaite que la tÃ¢che idle execute un code on le met ici
}
//*************************************************************************************

void init_OC1() {
    // cette fonction configure le OC1 pour générer un signal de type PWM (Pulse Width
    //modulation) Modulation de largeur d’impulsion de rapport cyclique 50% et une
    //fréquence de 977 Hz pour une fréquence du quartz Fosc=8Mhz
    // Timer 2 est sélectionné comme horloge à l’OC1 et les interruptions du Timer2 //sontactivées.
    // Désactiver ‘Output Compare 1 Module’
    OC1CON = 0x0000;
    
    OC1R = 0x7FFF;
   
    OC1RS = 0x3FFF;
    
    OC1CON = 0x0006;
    
    PR2 =0xFFFF;//soit 65535
    //desactiver les interruptions du Timer 2
    IEC0bits.T2IE = 0; // activer l’interruption du Timer 2
    T2CONbits.TON = 1; // Démarrer Timer2
}


