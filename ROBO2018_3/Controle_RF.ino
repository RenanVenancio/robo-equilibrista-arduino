/*

ATENÇÃO, ESTÁ FUNCIONAL, POREM PRECISA DE MAIS AJUSTES


*/
void controleRf(){
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
//Serial.println("CAPTOU O SINAL");
     //verifica se houve solicitação de envio dos dados
     if (dadosRecebidos.ligando) {
        alterado = true;
        //Serial.println("HOUVE UMA SOLICITAÇÃO");
     } else {
        dadosRF = dadosRecebidos;
     }
  }



  //*************** Controle do Projeto LOCAL ************
  
  

  if ((viraEsquerda != viraEsquerdaAnt)) {
     dadosRF.viraEsquerda = viraEsquerda;
     Serial.println("VIRE À ESQUERDA!");
     alterado = true;  //esta variavel controla o envio dos dados sempre que houver uma alteração
  }
 viraEsquerdaAnt = viraEsquerda;


//Serial.println(dadosRF.anguloFrente);
    if ((anguloFrente != anguloFrenteAnt)) {
     dadosRF.anguloFrente = anguloFrente;
     Serial.println("Entrou no if ANG");
     alterado = true;  //esta variavel controla o envio dos dados sempre que houver uma alteração
     anguloFrenteAnt = anguloFrente;  
  }


  delay(10);
}
