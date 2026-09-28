int main() {
  DDRD = (1<<PD0) | (1<<PD1);               // PD0 = motor, PD1 = válvula (saídas)
  DDRB = 0;                                 // sensores: entrada
  PORTB = (1<<PB1) | (1<<PB2) | (1<<PB3);   // pull-up (sensor ativo = 0)
  PORTD = 0;                                // motor desligado, válvula fechada

  unsigned char estado = 0;

  while(1){

    if(estado == 0){                        // espera SP1 e confere a partida
      if(((PINB & (1<<PB1)) == 0) && ((PINB & (1<<PB2)) != 0) && ((PINB & (1<<PB3)) != 0) && ((PORTD & (1<<PD1)) == 0)){
        PORTD |= (1<<PD0);                  // liga o motor
        estado = 1;
      }
    }

    else if(estado == 1){                   // espera SP2
      if((PINB & (1<<PB2)) == 0){
        PORTD &= ~(1<<PD0);                 // desliga o motor
        estado = 2;
      }
    }

    else if(estado == 2){                   // enchimento
      PORTD |= (1<<PD1);                    // abre a válvula
      _delay_ms(3000);                      // 3 segundos
      PORTD &= ~(1<<PD1);                   // fecha a válvula
      PORTD |= (1<<PD0);                    // religa o motor
      estado = 3;
    }

    else if(estado == 3){                   // espera SP3
      if((PINB & (1<<PB3)) == 0){
        PORTD &= ~(1<<PD0);                 // desliga o motor
        estado = 0;                         // pronto para novo ciclo
      }
    }
  }
}