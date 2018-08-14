#include <RF24.h>



//*************** Controle do RF ***********************
#define radioID 1   //Informar "0" para um dispositivo e "1" para o outro dispositivo

struct estruturaDadosRF
{
   boolean ligando = false;   //Esta variavel será usada para solicitar os dados do outro aparelho. Será útil quando o aparelho solicitante esta sendo ligado, para manter os valores do aparelho que já esta ligado.
   boolean viraEsquerda = false;
   boolean viraDireita = false;
   

   int anguloFrente = 0;
   int anguloTraz = 0;
};
typedef struct estruturaDadosRF tipoDadosRF;
tipoDadosRF dadosRF;
tipoDadosRF dadosRecebidos;

boolean transmitido = true;
boolean alterado = false;

RF24 radio(9, 10);

byte enderecos[][6] = {"1node","2node"};



//*************** Controle do Projeto LOCAL ************
boolean viraEsquerda = HIGH;
boolean viraEsquerdaAnt = HIGH;
char input= -1; 
int anguloFrente = 0;
int anguloFrenteAnt = 0;
int entrada = 0;          //Apenas para leitura da serial  PROVISÓRIO
/*
boolean botao1Ant = HIGH;
boolean botao1    = HIGH;
boolean botao2Ant = HIGH;
boolean botao2    = HIGH;
boolean botao3Ant = HIGH;
boolean botao3    = HIGH;
int pot1Ant = 0;
int pot1    = 0;
int pot2Ant = 0;
int pot2    = 0;

int angulo1 = 0;
int angulo2 = 0;

*/


/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 Contact information
 -------------------
 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

void setup() {

Serial.begin(9600);
  
 //*************** Controle do RF ***********************
  radio.begin();
  
  #if radioID == 0
      radio.openWritingPipe(enderecos[0]);
      radio.openReadingPipe(1, enderecos[1]);
  #else
      radio.openWritingPipe(enderecos[1]);
      radio.openReadingPipe(1, enderecos[0]);
  #endif

  //Solicita os dados do outro aparelho, se ele estiver ligado. Tenta a comunicação por 2 segundos.
  dadosRF.ligando = true;
  radio.stopListening();                                   
  long tempoInicio = millis();
  while ( !radio.write( &dadosRF, sizeof(tipoDadosRF) ) ) {
     if ((millis() - tempoInicio) > 2000) {
        break;
     }   
  }
  dadosRF.ligando = false; 
  radio.startListening();  


  //*************** Controle do Projeto LOCAL ************

  /*
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  pinMode(4, INPUT_PULLUP); 
*/
 


  //FIM_CONTROLERF_FIM_CONTROLERF_FIM_CONTROLERF_FIM_CONTROLERF_FIM_CONTROLERF_FIM_CONTROLERF_
 

}

void loop() {
  
  //*************** Controle do RF ***********************
  // se houve alteração dos dados, envia para o outro radio 
  if (alterado || !transmitido) {
     radio.stopListening();                                   
     transmitido = radio.write( &dadosRF, sizeof(tipoDadosRF) );
     radio.startListening();  
     alterado = false;
  }

  //verifica se esta recebendo mensagem       
  if (radio.available()) {                                   
     radio.read( &dadosRecebidos, sizeof(tipoDadosRF) ); 

     //verifica se houve solicitação de envio dos dados
     if (dadosRecebidos.ligando) {
        alterado = true;
     } else {
        dadosRF = dadosRecebidos;
     }
  }



  //*************** Controle do Projeto LOCAL ************


  if (Serial.available() > 0) {
    input= Serial.read();
    entrada = Serial.parseInt();
  
      anguloFrente = entrada;
  }

  
    if (input == '1'){
     // Serial.println("Recebi o valor 1");
      viraEsquerda = HIGH;
    }else if(input == '0'){
     // Serial.println("Recebi o valor 0");
      viraEsquerda = LOW;
    }


    
 //Serial.println(dadosRF.viraEsquerda);
  if ((viraEsquerda != viraEsquerdaAnt)) {
     dadosRF.viraEsquerda = viraEsquerda;
     Serial.println("Entrou no if");
     alterado = true;  //esta variavel controla o envio dos dados sempre que houver uma alteração
     viraEsquerdaAnt = viraEsquerda;  
  }

  
Serial.println(dadosRF.anguloFrente);
    if ((anguloFrente != anguloFrenteAnt)) {
     dadosRF.anguloFrente = anguloFrente;
     Serial.println("Entrou no if ANG");
     alterado = true;  //esta variavel controla o envio dos dados sempre que houver uma alteração
     anguloFrenteAnt = anguloFrente;  
  }


 

  delay(10);
 
}
