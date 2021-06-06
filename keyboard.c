#include <stdio.h>
#include <stdlib.h>
#include <p24Fxxxx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "string.h"
#include "portmacro.h"


extern QueueHandle_t xQueueKeyboard;

unsigned int ucPollKeyboard(void) {
    PORTG = 0x0001; //KeyBoard's column 3 is on
    switch (PORTG & 0xF000) {
            //masks all bits except RG12 to RG15
        case 0x1000: //RG12=1 Key 3 is pressed
        {
            while ((PORTG & 0x1000)); //wait until key released
            return 3; //return the character ‘ 3 ‘
        }
        case 0x2000: //RG13=1 Key 6 is pressed
        {
            while ((PORTG & 0x2000));
            return 6;
        }
        case 0x4000: //RG14=1 Key 9 is pressed
        {
            while ((PORTG & 0x4000));
            return 9;
        }
        case 0x8000: //RG9=1 Key # is pressed
        {
            while ((PORTG & 0x8000));
            return 10;
        }
    }
    PORTG = 0x0002; //KeyBoard's column 2 is on
    switch (PORTG & 0xF000) {
        case 0x1000:
        {
            while ((PORTG & 0x1000));
            return 2;
        }
        case 0x2000:
        {
            while ((PORTG & 0x2000));
            return 5;
        }
        case 0x4000:
        {
            while ((PORTG & 0x4000));
            return 8;
        }
        case 0x8000:
        {
            while ((PORTG & 0x8000));
            return 0;
        }
    }
    PORTG = 0x0004; //KeyBoard's column 1 is on
    switch (PORTG & 0xF000) {
        case 0x1000:
        {
            while ((PORTG & 0x1000));
            return 1;
        }
        case 0x2000:
        {
            while ((PORTG & 0x2000));
            return 4;
        }
        case 0x4000:
        {
            while ((PORTG & 0x4000));
            return 7;
        }
        case 0x8000:
        {
            while ((PORTG & 0x8000));
            return 11;
        }
    }
    return 12; //error more than one key are pressed or any key pressed
}

void vKeyboardTask(void *pv) {
    unsigned int I;
    TRISG = 0xFFF8;
    while (1) {
        I = ucPollKeyboard(); //scruter le clavier pour détecter la touche appuyée

        if (I != 12) {//une touche est appuyée
            xQueueSendToBack(xQueueKeyboard, &I, portMAX_DELAY);
        } else;
    }

}
