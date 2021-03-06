
#include <inttypes.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 38400
#include <util/setbaud.h>

void init_uart (void);

int main (void)
{
    cli();
    init_uart();
    char *s = "Hello world.\n";
    for (int i = 0; i < strlen(s) + 1; i++) {
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = *(s + i);
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
