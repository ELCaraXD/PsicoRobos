//Ultrassonico
#include <Ultrasonic.h>
int distance;
float distReal;
int soma;
Ultrasonic ultrasonic(8, 7);

//Servo motores
#include <Servo.h>
Servo garDir;
Servo garEsq;


//Motores e velocidade
#define motFE1 53
  #define motFE2 52

#define motAE1 49
  #define motAE2 48

#define motFD1 51
  #define motFD2 50

#define motAD1 46
  #define motAD2 47

#define vel1FrenD 2
  #define vel2TrasD 5
    #define vel1FrenE 3
      #define vel2TrasE 6


//mapa
uint8_t Plano[3][3] = {
  {1, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

//Posição no plano cartesiano começando do zero, 0 = primeira linha e coluna
uint8_t pos_Atual[2] = {0, 0};
uint8_t pos_Antiga[2];

//Direca e pra onde ele ta apontando 
//       0
//   7       1
// 6           2
//   5       3
//       4
//Passos
int passo = 0;

void mover(uint16_t mot1,uint16_t mot2,uint16_t mot3 ,uint16_t mot4,uint8_t Direc,uint16_t vel = 255){
  
  pos_Antiga[0] = pos_Atual[0];
  pos_Antiga[1] = pos_Atual[1];

  switch (Direc){
    case 0:  pos_Atual[0]--; break;
    case 1:  pos_Atual[0]--; pos_Atual[1]++; break;
    case 2:  pos_Atual[1]++; break;
    case 3:  pos_Atual[0]++; pos_Atual[1]++; break;
    case 4:  pos_Atual[0]++; break;
    case 5:  pos_Atual[0]++; pos_Atual[1]--; break;
    case 6:  pos_Atual[1]--; break;
    case 7:  pos_Atual[0]--; pos_Atual[1]--; break;
  }

    int Hor[4];
    int AntHor[4];

    int mots[4] = { mot1,mot2,mot3,mot4 };

    int PinoMotores[4][2] = {
      {motFD1,motFD2},
      {motFE1,motFE2},
      {motAD1,motAD2},
      {motAE1,motAE2}
    };

    analogWrite(vel1FrenE,vel );
    analogWrite(vel2TrasE,vel );

    analogWrite(vel1FrenD,vel);
    analogWrite(vel2TrasD,vel );

  if (Plano[pos_Atual[0]][pos_Atual[1]] == 0){
    for(int i = 0;i <= 3;i++){
      if (mots[i] == 1) { Hor[i] = 0;  AntHor[i] = 1; }
      else{ Hor[i] = 1;  AntHor[i] = 0; }
        digitalWrite(PinoMotores[i][0],Hor[i]);
        digitalWrite(PinoMotores[i][1],AntHor[i]);
    }
    Plano[pos_Atual[0]][pos_Atual[1]] = Direc;
    Plano[pos_Antiga[0]][pos_Antiga[1]] = 0;
  }else{
    Serial.print("Espaço ocupado!!!");
    Plano[pos_Atual[0]][pos_Atual[1]] = Plano[pos_Atual[0]][pos_Atual[1]];
    Plano[pos_Antiga[0]][pos_Antiga[1]] = Direc;
  }

}

float distancia(){
  soma = 0;

  for (int i = 0;i<=9;i++){
    distance = ultrasonic.read();
    soma = soma + distance;
  }
  distReal = soma/10;
  Serial.print("Distance in CM: ");
  Serial.println(distReal);
  
  return distReal;
}


void MostrarPos(uint8_t linha, uint8_t coluna){
  for (uint8_t i = 0; i < linha; i++){
    for(uint8_t j = 0; j < coluna; j++){
      Serial.print(Plano[i][j]);
    }
    Serial.print("\n");
  }
}

void setup() {

 pinMode(vel1FrenE,OUTPUT);
    pinMode(motFE1,OUTPUT);
    pinMode(motFE2,OUTPUT);
    pinMode(vel2TrasE,OUTPUT);    
      pinMode(motAE1,OUTPUT);
      pinMode(motAE2,OUTPUT);

  pinMode(vel1FrenD,OUTPUT);
    pinMode(motFD1,OUTPUT);
    pinMode(motFD2,OUTPUT);
    pinMode(vel2TrasD,OUTPUT);
      pinMode(motAD1,OUTPUT);
      pinMode(motAD2,OUTPUT);

  pinMode(22,OUTPUT);

  garDir.attach(44);
  garEsq.attach(45);

  garDir.write(40);
  garEsq.write(40); 

  Serial.begin(9600);


}

void loop() {


}
