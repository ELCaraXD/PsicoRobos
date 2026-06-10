//Plano e igual a mapa mental
uint8_t Plano[3][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

//Posição no plano cartesiano começando do zero, 0 = primeira linha e coluna
uint8_t pos_Atual[2] = {0, 0};
uint8_t pos_Antiga[2];

//Direca e pra onde ele ta apontando 
//       0
//   3       1         
//       2
uint8_t Direcao = 0;

void frente(uint8_t passos,uint8_t vel = 255){
  switch (Direcao){
    case 0: Serial.printf("Indo %d passos para cima", passos);  break;
    case 1: Serial.printf("Indo %d passos para direita", passos); break;
    case 2: Serial.printf("Indo %d passos para baixo", passos); break;
    case 3: Serial.printf("Indo %d passos para esquerda", passos); break;
  }
}


void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
