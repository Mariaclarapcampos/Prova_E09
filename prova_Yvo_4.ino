int main() {
  DDRB = 0;
  DDRD = (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3);  
  PORTB = (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3);  
  
  unsigned char estado;
  unsigned char ligado;

  estado = 0;
  ligado = 0;
  while(1){
    if(estado == 0){ //P pressionado
      if((PINB & (1<<PB0)) == 0){
         ligado |= (1<<PD1) | (1<<PD0);
         estado = 1;
      }
    }

     else if(estado == 1){
      if((PINB & (1<<PB1)) == 0){ //Espera S1
        ligado &= ~((1<<PD1) | (1<<PD0));
        ligado |= (1<<PD2);
        estado = 2;
      }
    }

    else if(estado == 2){
      if((PINB & (1<<PB2)) == 0){ //Espera S2
          ligado &= ~(1<<PD2);
          ligado |= (1<<PD3);
          PORTD = ligado; // aplica nos pinos: motor desliga, V1 liga e sobrescreve os ultimos valores
          delay(3500);
          ligado &= ~(1<<PD3);
          ligado |= (1<<PD2);
          estado = 3;
      }
    }

    else if(estado == 3){
      if((PINB & (1<<PB3)) == 0){
        ligado &= ~(1<<PD2); // Espera S3
        estado = 0;
      }
    }
    PORTD = ligado;
  }
}

/*
aperta o botão P liga
C1 -> S1 -> S2 -> PARA 3,5s -> LIGA -> S3

P, S1, S2, S3 - ENTRADA
ALIMENTADOR(LIBERA PEÇA), C1(CILINDRO), MOTOR, V1(RESFRIAMENTO) - SAÍDA

 ENTRADAS: P = PB0, S1 = PB1, S2 = PB2, S3 = PB3
 SAÍDAS:   ALIMENTADOR = PD0, C1 = PD1, MOTOR = PD2, V1 = PD3
*/