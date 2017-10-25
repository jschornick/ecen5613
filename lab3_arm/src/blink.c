#include "msp432p401r.h"
#include <stdint.h>

int main(void) {
    uint32_t i;

    P1->DIR |= BIT0; // LED pin as output

    while (1) {
      P1->OUT ^= BIT0; // toggle LED pin
        for (i = 0; i < 50000; i++); // delay
    }
}

