#include <Wire.h> //Biblioteca para a comunicação I2C

const int endereco_MPU = 0x68; //Declara o endereço de comunicação entre o arduino eo MPU 

// Declaração de variáveis
float Grau_x = 0, Grau_y = 0, Grau_z = 0, Aceleracao_x = 0, Aceleracao_y = 0, Aceleracao_z = 0, Temperatura = 0, sensibilidade_giroscopio = 1, sensibilidade_acelerometro = 1;
float Auxiliar_Grau_x = 0, Auxiliar_Grau_y = 0, Auxiliar_Grau_z = 0, tempo_inicial = 0, tempo_final = 0, auxiliar_tempo = 0, Angulo_Grau_y = 0, Angulo_Grau_x = 0, Angulo_Grau_z = 0;
int auxiliar_giroscopio = 1, auxiliar_acelerometro = 1, somador = 0;

void setup() {
  
  Serial.begin(9600); //Inicializa a comunicação serial a uma taxa de 9600 bit por segundo
 
  Wire.begin(); //Inicializa a biblioteca Wire.h

  Wire.beginTransmission(endereco_MPU); //Inicia a tranmissão de dados para o dispositivo escravo
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);

  fundo_de_escala_giroscopio(auxiliar_giroscopio); // Configura o giroscópio para a escala escolhido
  /* auxiliar_giroscopio = 1 escala = 250°/s
     auxiliar_giroscopio = 2 escala = 500°/s
     auxiliar_giroscopio = 3 escala = 1000°/s
     auxiliar_giroscopio = 4 escala = 2000°/s */

 fundo_de_escala_acelerometro(auxiliar_acelerometro); // Configura o acelerômetro para a escala escolhido
  /* auxiliar_acelerometro = 1 escala = 2g
     auxiliar_acelerometro = 2 escala = 4g
     auxiliar_acelerometro = 3 escala = 8g
     auxiliar_acelerometro = 4 escala = 16g */
  
}

void loop() {

  //Inicia a tranmissão dos dados
  Wire.beginTransmission(endereco_MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(endereco_MPU, 14, true); // Solicita os dados do sensor


  get_data();

  //Imprime os dados no monitor serial
  Serial.print("Angulo em x: ");
  Serial.println(Angulo_Grau_x);
  Serial.print("Angulo em y: ");
  Serial.println(Angulo_Grau_y);
  Serial.print("Angulo em z: ");
  Serial.println(Angulo_Grau_z);
  Serial.print("\n");

  Serial.print("Aceleração em x: ");
  Serial.println(Aceleracao_x);
  Serial.print("Aceleração em y: ");
  Serial.println(Aceleracao_y);
  Serial.print("Aceleração em z: ");
  Serial.println(Aceleracao_z);
  Serial.print("\n");
  
  delay(500); //delay para ser possivel ler os dados
   
}

void fundo_de_escala_giroscopio(int i){
  
  // fundo de escala +/-250°/s
  if(i == 1){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1B);
    Wire.write(0b00000000);
    Wire.endTransmission();
    sensibilidade_giroscopio = 131;
  
  }

  // fundo de escala +/-500°/s
  if(i == 2){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1B);
    Wire.write(0b00001000);
    Wire.endTransmission();
    sensibilidade_giroscopio = 65.6;
  
  }

  // fundo de escala +/-1000°/s
  if(i == 3){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1B);
    Wire.write(0b00010000);
    Wire.endTransmission();
    sensibilidade_giroscopio = 32.8;
  
  }

  // fundo de escala +/-2000°/s
  if(i == 4){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1B);
    Wire.write(0b00011000);
    Wire.endTransmission();
    sensibilidade_giroscopio = 16.4;
  
  }
  
 }

 void fundo_de_escala_acelerometro(int i){
  
  // fundo de escala +/-2g
  if(i == 1){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1C);
    Wire.write(0b00000000);
    Wire.endTransmission();
    sensibilidade_acelerometro = 16384;
  
  }

  // fundo de escala +/-4g
  if(i == 2){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1C);
    Wire.write(0b00001000);
    Wire.endTransmission();
    sensibilidade_acelerometro = 8192;
  
  }

  // fundo de escala +/-8g
  if(i == 3){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1C);
    Wire.write(0b00010000);
    Wire.endTransmission();
    sensibilidade_acelerometro = 4096;
  
  }

  // fundo de escala +/-16g
  if(i == 4){
    
    Wire.beginTransmission(endereco_MPU);
    Wire.write(0x1C);
    Wire.write(0b00011000);
    Wire.endTransmission();
    sensibilidade_acelerometro = 2048;
  
  }
  
 }

 void get_data(){
  
    // Armazena os dados puros nas variaveis certas
    Aceleracao_x = Wire.read() << 8 | Wire.read();
    Aceleracao_y = Wire.read() << 8 | Wire.read();
    Aceleracao_z = Wire.read() << 8 | Wire.read();
    Temperatura = Wire.read() << 8 | Wire.read();
    Grau_x = Wire.read() << 8 | Wire.read();
    Grau_y = Wire.read() << 8 | Wire.read();
    Grau_z = Wire.read() << 8 | Wire.read();

    //Tranforma os dados puros em velocidade angular e aceleração
    Aceleracao_x = Aceleracao_x/sensibilidade_acelerometro;
    Aceleracao_y = Aceleracao_y/sensibilidade_acelerometro;
    Aceleracao_z = Aceleracao_z/sensibilidade_acelerometro;
    Grau_x = Grau_x/sensibilidade_giroscopio;
    Grau_y = Grau_y/sensibilidade_giroscopio;
    Grau_z = Grau_z/sensibilidade_giroscopio;
  
 }

 void converter(){
  
    tempo_inicial = millis(); 
    
    somador = 0;

    auxiliar_tempo = 0;
    
    while (auxiliar_tempo < 30){

      get_data();
      tempo_final = millis();
      auxiliar_tempo = tempo_final - tempo_inicial;
      Auxiliar_Grau_x += Grau_x;
      Auxiliar_Grau_y += Grau_y;
      Auxiliar_Grau_z += Grau_z;
      somador++;
      
    
   }
   
   //encontra a velocidade angular média
   Auxiliar_Grau_x = Auxiliar_Grau_x/somador;
   Auxiliar_Grau_y = Auxiliar_Grau_y/somador;
   Auxiliar_Grau_z = Auxiliar_Grau_z/somador;

   //encontra a angulo 
   Angulo_Grau_x += Auxiliar_Grau_x;
   Angulo_Grau_y += Auxiliar_Grau_y;
   Angulo_Grau_z += Auxiliar_Grau_z;
 
 }
