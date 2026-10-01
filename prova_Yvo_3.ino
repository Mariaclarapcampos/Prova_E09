//temperatura PD2
//pressao PD4
//nivel PD5
//peso PB0

#include <avr/io.h>
int main() {
  DDRD |= (1<<PD0); //LED saída
  DDRB = 0; //entradas
  PORTB &= ~(1<<PB0); //pull-up desligado, ja que os sensores estao em nivel logico alto
  PORTD &= ~((1<<PD2) | (1<<PD4) | (1<<PD5)); //pull-up desligado, ja que os sensores estao em nivel logico alto
  //&= ~() faz com que somente esses bits tenham o pull-up desligados


  while(1){
    PORTD &= ~(1<<PD0); // começa com o LED apagado

    if((PIND &(1<<PD5)) && (PIND &(1<<PD2)) && (PIND &(1<<PD4))){
      PORTD |= (1<<PD0);
    }
   
    if(!(PIND &(1<<PD5)) && (PIND &(1<<PD2)) && (PINB &(1<<PB0))){
      PORTD |= (1<<PD0);
    }

    if(!(PIND &(1<<PD5)) && !(PIND &(1<<PD2)) && (PIND &(1<<PD4))){
      PORTD |= (1<<PD0);
    }
    
    if(!(PIND &(1<<PD5)) && (PIND &(1<<PD2)) && !(PINB &(1<<PB0))){
      PORTD |= (1<<PD0);
    }
  }
}


/* LED1 - PD0
4 sensores de saída ON/OFF em nível lógico alto (PULL-DOWN)
	temperatura
	pressão
	nível
	peso do fluído
Nível alto e temperatura alta e pressão alta (1110)
Nível baixo temperatura e peso alto (1001)
Nível baixo temperatura baixa e pressão alta (0100)
Nível baixo peso e temperatura alta (1000)*/
