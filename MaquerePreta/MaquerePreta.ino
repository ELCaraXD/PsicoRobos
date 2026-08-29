//Ultrassonico
#include <Ultrasonic.h>
int distance;
float distReal;
int medDist;
int soma;
Ultrasonic ultrasonic(11, 10);

//Sensor Som
#define PinSenSom 12
int SenSom;

//Leds
#define Led 6

//Motores
#define mot1 7
#define mot2 8
#define Vel 9

//Passos
int passos = 0;
int passosAnt = 0;

float distancia(){
  soma = 0;

  for (int i = 0;i<=9;i++){
    distance = ultrasonic.read();
    soma = soma + distance;
  }
  distReal = soma/10;
  
  return distReal;
}

void setup() {
  Serial.begin(9600);

  //Som
  pinMode(PinSenSom,INPUT);
  
  //Led
  pinMode(Led,OUTPUT);

  //Motores
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(Vel,OUTPUT);

}

void loop() {

  SenSom = digitalRead(PinSenSom);

  medDist = distancia();
  analogWrite(Vel,125);

if (passos == 0 && SenSom == 1){
  digitalWrite(mot1,HIGH); digitalWrite(mot2,LOW);
  digitalWrite(Led,HIGH);
  delay(2000);
  digitalWrite(mot1,LOW); digitalWrite(mot2,LOW);
  digitalWrite(Led,LOW);
  passos++;
  passosAnt++;
}

if (passos == 1 && SenSom == 1 && passosAnt == 0){
  digitalWrite(mot1,HIGH); digitalWrite(mot2,LOW);
  digitalWrite(Led,HIGH);
  delay(4000);
  digitalWrite(mot1,LOW); digitalWrite(mot2,LOW);
  digitalWrite(Led,LOW);
  passos++;
  passosAnt++;
}

if (passos == 2 && SenSom == 1 && passosAnt == 0 && medDist <= 24){
  digitalWrite(mot1,HIGH); digitalWrite(mot2,LOW);
  digitalWrite(Led,HIGH);
  passos++;
  passosAnt++;
}
  passosAnt = 0;

}
