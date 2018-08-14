const int PWM_1 = 9;
const int OUT_A = 5;
const int OUT_B = 2;
const int OUT_C = 3;
const int OUT_D = 4;
const int PWM_2 = 10;

void init_motores(){
  pinMode(PWM_1, OUTPUT);
  pinMode(OUT_A, OUTPUT);
  pinMode(OUT_B, OUTPUT);
  pinMode(OUT_C, OUTPUT);
  pinMode(OUT_D, OUTPUT);
  pinMode(PWM_2, OUTPUT);
}






void PWM_Controle_Motores(double comando){
  










if(comando > 255.0){
  comando = 255.0;
  
}else if(comando < -255.0){
  comando = -255.0;
}


if (comando < 0){  //JOGA O ROBO p FRENTE

  analogWrite(PWM_2, -comando);
  digitalWrite(OUT_A, 1);
  digitalWrite(OUT_B, 0);


  analogWrite(PWM_1, -comando);
  digitalWrite(OUT_C, 0);
  digitalWrite(OUT_D, 1);
  
//  Serial.print("INDO PRA FRENTE ");
//  Serial.println(-comando);

}else if(comando == 0){  //PARE OS MOTORES
  analogWrite(PWM_2, 0);
  digitalWrite(OUT_A, 1);
  digitalWrite(OUT_B, 0);


  analogWrite(PWM_1, 0);
  digitalWrite(OUT_C, 1);
  digitalWrite(OUT_D, 0);
  
  
}else if(comando > 0){  //JOGA O ROBO p TRAZ
 
   analogWrite(PWM_2, comando);
  digitalWrite(OUT_A, 0);
  digitalWrite(OUT_B, 1);


  analogWrite(PWM_1, comando);
  digitalWrite(OUT_C, 1);
  digitalWrite(OUT_D, 0);
 
}
   // Serial.println(comando);
}
  
