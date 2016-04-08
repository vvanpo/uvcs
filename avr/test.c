
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 38400
#include <util/setbaud.h>

#include <simavr/avr/avr_mcu_section.h>
AVR_MCU_SIMAVR_CONSOLE(GPIOR0);

void init_uart (void);

int main (void)
{
    char *s = "hello world";
    init_uart();
    while (1)
        for (int i = 0; i < 13; i++) {
            loop_until_bit_is_set(UCSR0A, UDRE0);
            UDR0 = *(s + i);
            GPIOR0 = *(s + i);
        }
    return 0;
}

void init_uart (void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~_BV(U2X0);
#endif
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
}
