#include <MPU6050_tockn.h> //Biblioteca para facilitar a leitura de dados
#include <Wire.h> //Biblioteca para a comunicação I2C


MPU6050 mpu6050(Wire); //Entrega a biblioteca Wire.h como argumento para a biblioteca MPU6050_tockn.h
//z está aumentando muito com o tempo

float Grau_x = 0, Grau_y = 0, Grau_z = 0, Aceleracao_x = 0, Aceleracao_y = 0, Aceleracao_z = 0, m1, m2, grau_padrao_parado[3]; // Declaração de variáveis
int count = 0;
char k;

void setup() {
  
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH); 
  
  Serial.begin(9600); //Inicializa a comunicação serial a uma taxa de 9600 bit por segundo


  Wire.begin(); //Inicializa a biblioteca Wire.h
 
  mpu6050.begin(); //Inicializa a biblioteca MPU6050_tockn.h
  mpu6050.calcGyroOffsets(true); //Ativa a calibração interna da biblioteca
  Serial.println();

  padrao_parado();
 
  m1 = millis();
}
void loop() {
  
  m2 = millis() - m1;

  leitor();
  
  //Calibração dos angulos
  Grau_x = calcoffX();
  Grau_y = calcoffY();
  Grau_z = calcoffZ();

 
  //Imprime os dados no monitor serial
  Serial.print("Angulo em x: ");
  Serial.println(Grau_x);
  Serial.print("Angulo em y: ");
  Serial.println(Grau_y);
  Serial.print("Angulo em z: ");
  Serial.println(Grau_z);
  Serial.print("\n");
 
  /*Serial.print("Aceleração em x: ");
  Serial.println(Aceleracao_x);
  Serial.print("Aceleração em y: ");
  Serial.println(Aceleracao_y);
  Serial.print("Aceleração em z: ");
  Serial.println(Aceleracao_z);
  Serial.print("\n");*/
    
  delay(0); //delay para ser possivel ler os dados
}

//função que lê os dados do mpu
void leitor(){
  
  int count = 0;

  Grau_x = 0;
  Grau_y = 0;
  Grau_z = 0;
  Aceleracao_x = 0;
  Aceleracao_y = 0;
  Aceleracao_z = 0;
  
  while(count < 100){

    mpu6050.update(); //atualiza a leitura

    //Obtém os angulos
  
    Grau_x = Grau_x + mpu6050.getAngleX();
    Grau_y = Grau_y + mpu6050.getAngleY();
    Grau_z = Grau_z + mpu6050.getAngleY();
    Aceleracao_x = Aceleracao_x + mpu6050.getAccX();
    Aceleracao_y = Aceleracao_y + mpu6050.getAccY();
    Aceleracao_z = Aceleracao_z + mpu6050.getAccZ();
    count++;
  
  }

  //Média dos angulos medidos
  Grau_x = Grau_x/100;
  Grau_y = Grau_y/100;
  Grau_z = Grau_z/100;
  Aceleracao_x = Aceleracao_x/100;
  Aceleracao_y = Aceleracao_y/100;
  Aceleracao_z = Aceleracao_z/100;

}

//função que define qual a posição inicial
void padrao_parado(){
  
  int count = 0;
 
  grau_padrao_parado[0] = 0;
  grau_padrao_parado[1] = 0;
  grau_padrao_parado[3] = 0;
  
  while (count < 10){
  
    leitor();
    grau_padrao_parado[0] += Grau_x;
    grau_padrao_parado[1] += Grau_y;
    grau_padrao_parado[1] += Grau_z;
    count++;
  
  }
  
  grau_padrao_parado[0] /= 10;
  grau_padrao_parado[1] /= 10;
  grau_padrao_parado[2] /= 10;
  
}

//funções para calibrar os eixos
float calcoffX(){
  
  //return 23.553 - 0.99796*Grau_x;
  return -34.926 + 1.4536*Grau_x - grau_padrao_parado[0];

}

float calcoffY(){
  
  return -81.648 - 1.0952*Grau_y - grau_padrao_parado[1];
  //return 3.7585 - 1.4776*Grau_y;

}

float calcoffZ(){

  return -0.39868 + 0.47298*Grau_z - grau_padrao_parado[2];

}

float calcoffaX(){

  return 23.553 - 0.99796*Aceleracao_x - grau_padrao_parado[3];

}

float calcoffaY(){

  return -81.648 - 1.0952*Aceleracao_y - grau_padrao_parado[4];

}

float calcoffaZ(){

  return -0.39868 + 0.47298*Aceleracao_z - grau_padrao_parado[5];

}
