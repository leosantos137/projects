/*Trabalho Interdisciplinar 
   Eletronica de Potencia
   Eletronica Digital
   Comados Elétricos Industriais 
  Retirado do site: http://www.ELECTRONOOBS.com/eng_circuitos_tut20.php

*/
int detectado = 0;     // variavel 
int valor=0;      // variavel que faz a leitura do potenciometro
int estado = 0;

void setup() {
  
   
  PCICR |= (1 << PCIE0);    // ativar varredura PCMSK0                                                 
  PCMSK0 |= (1 << PCINT0);  // Entrada do optoacopladorO pino de ajuste D8 dispara uma interrupção na mudança de estado. 
  pinMode(3,OUTPUT);        // Define o pino D3 como saída para o pulso

}

void loop() {



 
   
    if (detectado)
    {

      valor = map(analogRead(A0),0,1024,7200,8);
      delayMicroseconds(valor); //Esse atraso controla a tensão
      digitalWrite(3,HIGH);
      delayMicroseconds(50);
      digitalWrite(3,LOW);
      detectado=0;
    } 
}




//Esta é a rotina de interrupção
//----------------------------------------------

/*
   Esta sendo usado interrupção ao invés de digitalwrite e digitalRead por serem mais lentos
   
   
   
   */

ISR(PCINT0_vect){
  /////////////////////////////////////               // Entrada do optoacoplador
  if(PINB & B10000000){                               // Fazemos um AND com o registrador de estado do pino, Verificamos se o pino 8 é HIGH
    if(estado == 0){                          //Se o último estado foi 0, então temos uma mudança de estado ...
      detectado=1;                                    //Nós detectamos uma mudança de estado!
    }
  }
  else if(estado == 1){                       //Se o pino 8 for LOW e o último estado for HIGH, então teremos uma mudança de estado      
    detectado=1;                                      // Detectamos uma mudança de estado!
    estado = 0;                               //Armazena o estado atual no último estado do próximo loop
    }
}
