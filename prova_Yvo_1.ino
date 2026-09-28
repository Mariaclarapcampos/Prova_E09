int main() {
 DDRB = 0; //são entradas
 DDRD = (1<<PD0) | (1<<PD1) | (1<<PD2); //são saídas
 PORTB = (1<<PB5) | (1<<PB4) | (1<<PB3); //ligando os pinos que preciso

  int m1 = 30;
  int m2 = 50;
  int m3 = 70;
  int valor = 0;
  unsigned char ligado;

while(1){
      ligado = 0;
      valor = 0;

      if((PINB & (1<<PB5)) == 0){ //se ligado
        ligado |= (1<<PD0); //mostra qual pino liga
        valor += m1; //define o valor
      }
      
      if((PINB & (1<<PB4)) == 0){ //se ligado
        ligado |= (1<<PD1); //mostra qual pino liga
        valor += m2; //define o valor
      }

      if((PINB & (1<<PB3)) == 0){ //se ligado
        ligado |= (1<<PD2); //mostra qual pino liga
        valor += m3; //define o valor
    }

    if(valor > 90 && (ligado & (1<<PD0))){ //desligando o de menor potencia
      ligado &= ~(1<<PD0);
      valor -= m1;
    } 
    
    if(valor > 90 && (ligado & (1<<PD1))){ //desligando a 2º menor potencia
      ligado &= ~(1<<PD1);
      valor -= m2;
    }
  }
  PORTD = ligado; //garante que esteja ligado
}