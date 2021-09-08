#include <MPU6050_tockn.h> //Biblioteca para facilitar a leitura de dados
#include <Wire.h> //Biblioteca para a comunicação I2C

MPU6050 mpu6050(Wire); //Entrega a biblioteca Wire.h como argumento para a biblioteca MPU6050_tockn.h

const float ax = 1, ay = 1, az = 1, bx = -22.575, by = 71.9675, bz = 0.925; //Parâmetro de Calibração do Arduino
//z está aumentando muito com o tempo

float Grau_x = 0, Grau_y = 0, Grau_z = 0, Aceleracao_x = 0, Aceleracao_y = 0, Aceleracao_z = 0; // Declaração de variáveis
int count = 0;

void setup() {
  Serial.begin(9600); //Inicializa a comunicação serial a uma taxa de 9600 bit por segundo
 
  Wire.begin(); //Inicializa a biblioteca Wire.h
  
  mpu6050.begin(); //Inicializa a biblioteca MPU6050_tockn.h
  mpu6050.calcGyroOffsets(true); //Ativa a calibração interna da biblioteca

}

void loop() {

  count = 0;

  Grau_x = 0;
  Grau_y = 0;
  Grau_z = 0;

  while(count < 100){

    mpu6050.update(); //atualiza a leitura

    //Obtém os angulos
  
    Grau_x = Grau_x + mpu6050.getAngleX();
    Grau_y = Grau_y + mpu6050.getAngleY();
    Grau_z = Grau_z + mpu6050.getAngleZ();
    Aceleracao_x = mpu6050.getAccX();
    Aceleracao_y = mpu6050.getAccY();
    Aceleracao_z = mpu6050.getAccZ();
    count++;
  }

  //Média dos angulos medidos
  Grau_x = Grau_x/100;
  Grau_y = Grau_y/100;
  Grau_z = Grau_z/100;

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

  delay(1); //delay para ser possivel ler os dados
}

//funções para calibrar os eixos

float calcoffX(){
  return bx + Grau_x*ax;
}

float calcoffY(){
  return by + Grau_y*ay;
}

float calcoffZ(){
  return bz + Grau_z*az;
}
