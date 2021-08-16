#include <MPU6050_tockn.h> //Biblioteca para facilitar a leitura de dados
#include <Wire.h> //Biblioteca para a comunicação I2C

MPU6050 mpu6050(Wire); //Entrega a biblioteca Wire.h como argumento para a biblioteca MPU6050_tockn.h

float Grau_x = 0, Grau_y = 0, Grau_z = 0, Aceleracao_x = 0, Aceleracao_y = 0, Aceleracao_z = 0; // Declaração de variáveis

void setup() {
  Serial.begin(9600); //Inicializa a comunicação serial a uma taxa de 9600 bit por segundo
 
  Wire.begin(); //Inicializa a biblioteca Wire.h
  
  mpu6050.begin(); //Inicializa a biblioteca MPU6050_tockn.h
  mpu6050.calcGyroOffsets(true); //Ativa a calibração interna da biblioteca

}

void loop() {

  //Obtém os angulos
  
  Grau_x = mpu6050.getAngleX();
  Grau_y = mpu6050.getAngleY();
  Grau_z = mpu6050.getAngleZ();


  //Imprime os dados no monitor serial
  Serial.print("Angulo em x: ");
  Serial.println(Grau_x);
  Serial.print("Angulo em y: ");
  Serial.println(Grau_y);
  Serial.print("Angulo em z: ");
  Serial.println(Grau_z);
  Serial.print("\n");

  delay(500); //delay para ser possivel ler os dados
   
 
}
