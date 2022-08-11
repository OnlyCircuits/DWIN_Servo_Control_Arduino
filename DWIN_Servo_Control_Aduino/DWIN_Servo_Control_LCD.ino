unsigned char buff[9];

void usart_init (void){
  UCSR0A = (1<<U2X0);
  UCSR0B = (1<<RXEN0);
  UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);
  UBRR0 = 16;
}
unsigned char usart_receive(void){
  
  while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}
void DWIN_receiver(void){
  for (uint8_t c = 0; c <= 8; c++)
  {
    buff[c] = usart_receive();
  }
}
void Timer_PWM(void){
  TCCR1A = 0xC2;
  TCCR1B = 0x1A;
  ICR1 = 39999;
}
void setup() {
  usart_init();
  Timer_PWM();
  
  DDRB = 0xFF;
  PORTB = 0x00;
}

void loop() {
  DWIN_receiver();
    switch (buff[8])
    {
    case 0x00:
      OCR1A = ICR1 - 1199;
    break;
    case 0x5A:
      OCR1A = ICR1 - 3099;
    break;
    case 0xB4:
      OCR1A = ICR1 - 4999;
    break;
    }
}
