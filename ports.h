/* add your own struct here!
 * just need to pass struct name without "struct" to ADD_STRUCT_TO_ARRAY macro */
#ifdef DDRA && PORTA && PINA
X(A)
#endif
#ifdef DDRB && PORTB && PINB
X(B)
#endif
#ifdef DDRC && PORTC && PINC
X(C)
#endif
#ifdef DDRD && PORTD && PIND
X(D)
#endif
#ifdef DDRE && PORTE && PINE
X(E)
#endif
#ifdef DDRF && PORTF && PINF
X(F)
#endif
#ifdef DDRG && PORTG && PING
X(G)
#endif
#ifdef DDRH && PORTH && PINH
X(H)
#endif