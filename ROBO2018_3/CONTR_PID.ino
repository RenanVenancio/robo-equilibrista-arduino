double erro;
double kp = 32.1;   //AUMENTA A DEMORA DA RESPOSTA DOS MOTORES   25.1
double ki = 2.5;   //VALOR MAIOR = PULSOS MAIS VIOLENTOS 2.8
double kd = 0.1;




double P=0,I=0,D=0; //Proporcional integral derivativo
double PID; //Soma das 3 variaveis P,I,D
double valor_ideal = 0;   //Valor do grau que deseja atingir



double ultima_entrada;

double obterPid(double input){    //Recebe o angulo Y para dar saída ao PWM


Serial.println(dadosRF.anguloFrente);

  erro = (valor_ideal - input);

  P = (erro * kp);
  I += (erro * ki);
  D = (ultima_entrada - input)*kd;

  ultima_entrada = input;

  PID = P+I+D;

 //Serial.print(PID); Serial.print("\t");



//Serial.println("pid "); Serial.println(PID);
  return PID;    //Retorna saída para o sketch principal
}
