#include <p24Fxxxx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
extern QueueHandle_t xQueueKeyboard;

void vPortETask(void *p) {
    TRISE = 0x0000;
    PORTE = 0x0000;
    unsigned int I;
    while (1) {
        xQueueReceive(xQueueKeyboard, &I, portMAX_DELAY);
        switch (I) {
            case 1:
            {
                if (_RE1 == 0)_RE1 = 1;
                else
                    _RE1 = 0;

            }
                break;
            case 2:
            {
                if (_RE2 == 0) _RE2 = 1;
                else _RE2 = 0;
            }
                break;
            case 3:
            {
                if (_RE3 == 0) _RE3 = 1;
                else _RE3 = 0;
            }
                break;
            case 4:
            {
                if (_RE4 == 0) _RE4 = 1;
                else _RE4 = 0;
            }
                break;
            case 5:
            {
                if (_RE5 == 0) _RE5 = 1;
                else _RE5 = 0;
            }
                break;
            case 6:
            {
                if (_RE6 == 0) _RE6 = 1;
                else _RE6 = 0;
            }
                break;
            case 7:
            {
                if (_RE7 == 0) _RE7 = 1;
                else _RE7 = 0;
            }
                break;
             case 8:
            {
                if (_RE8 == 0) _RE8 = 1;
                else _RE8 = 0;
            }
                break;
            case 9:
            {
                if (_RE9 == 0) _RE9 = 1;
                else _RE9 = 0;
            }
                break;
            case 0:
            {
                if (_RE0 == 0) _RE0 = 1;
                else _RE0 = 0;
            }
                break;
            case 10:
            {
                PORTE = 0xFFFF;
            }
                break;
            case 11:
            {
                PORTE = 0x0000;
            }
                break;

        }
    }
}
