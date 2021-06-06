#define USE_AND_OR /* To enable AND_OR mask setting */
#include <p24FJ128GA010.h>
#include <p24Fxxxx.h>
#include "freeRTOS.h"
#include <adc.h>
#include <stdio.h>
#include "semphr.h"
#include "list.h"
#include "task.h"
#include "queue.h"
#include<timer.h>


extern xSemaphoreHandle xSemaphore;
void vADCTask() {
    extern xSemaphoreHandle xSemaphore; //déconmtez cette ligne
    vSemaphoreCreateBinary(xSemaphore); //déconmtez cette ligne
    xSemaphoreTake(xSemaphore,portMAX_DELAY);
    unsigned int channel, config1, config2, config3, configscan;
    unsigned int ADCResult[16]; //pour récupérer les résultats des 16 conversions
    unsigned int mesure; //successives
    int i;
    AD1PCFG = 0x0000; //portB en entrée analogique
    CloseADC10();
    /*choix du canal AN0*/
    channel = ADC_CH0_POS_SAMPLEA_AN0;
    SetChanADC10(channel);
    /*Configure adc*/
    config1 = ADC_MODULE_OFF | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON | ADC_FORMAT_INTG;
    config2 = ADC_SCAN_ON | ADC_INTR_16_CONV;; //activer le mode scan
    config3 = ADC_SAMPLE_TIME_3 | ADC_CONV_CLK_2Tcy;
    configscan = ADC_SCAN_AN0;
    OpenADC10(config1, config2, config3, 0, configscan);
    EnableADC1; //activer le convertisseur
    T2CONbits.TON = 1;
    while (1) {

       if (xSemaphoreTake(xSemaphore,portMAX_DELAY)==pdTRUE){ //déconmtez cette ligne
     DisableIntT2;
        mesure = 0;
        i = 0;
        while (i < 16) { //i indice des 16 conversions successives
            ConvertADC10(); //lancer la ième conversion
            while (BusySampADC1); //attendre que la ième conversion se termine
            ADCResult[i] = ReadADC10(i); //lire le ième résultat de conversion
            mesure = mesure + ADCResult[i]; //faire la somme des 16 résultats
            i++;
        }
        mesure = mesure >>2;
        OC1RS = mesure;
        EnableIntT2;
      }
       //mesure = mesure >>2; //faire la moyenne en divisant par 4 la somme obtenue
        /*if ((mesure <= 1023) && (mesure >= 0)) {
            temp = ((unsigned long int) mesure * (unsigned long int) 4);
            if ((temp <= (UINT32) 4092) && (temp >= (UINT32) 0)) mesure = (UINT) temp;
        }*/
       //SetDCOC1PWM_v1(mesure);

        //OC1RS = mesure;
       
    }
}