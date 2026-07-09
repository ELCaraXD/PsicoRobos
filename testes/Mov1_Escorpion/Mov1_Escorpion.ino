
#define velD_1 32
  const uint8_t motD_1 = 25;
  const uint8_t motD_2 = 33;

#define velD_2 13
  const uint8_t motD_3 = 17;
  const uint8_t motD_4 = 16;


#define velE_1 14
  const uint8_t motE_1 = 26;
  const uint8_t motE_2 = 27;

#define velE_2 4
  const uint8_t motE_3 = 19;
  const uint8_t motE_4 = 18;

const int freqPWM = 20000;
const int resPWM  = 8;
const int velocidade = 255;


void setup() {
  Serial.begin(115200);
  
  ledcAttach(velD_1, freqPWM, resPWM);
    pinMode(motD_1, OUTPUT);
    pinMode(motD_2, OUTPUT);
  ledcAttach(velD_2, freqPWM, resPWM);
    pinMode(motD_3, OUTPUT);
    pinMode(motD_4, OUTPUT);

  ledcAttach(velE_1, freqPWM, resPWM);
    pinMode(motE_1, OUTPUT);
    pinMode(motE_2, OUTPUT);
  ledcAttach(velE_2, freqPWM, resPWM);
    pinMode(motE_3, OUTPUT);
    pinMode(motE_4, OUTPUT);

}

void loop() {
  ledcWrite(velD_1, velocidade);
  ledcWrite(velD_2, velocidade);

  ledcWrite(velE_1, velocidade);
  ledcWrite(velE_2, velocidade);

  digitalWrite(motD_1, HIGH);
  digitalWrite(motD_2, LOW);
    digitalWrite(motD_3, HIGH);
    digitalWrite(motD_4, LOW);

  digitalWrite(motE_1, HIGH);
  digitalWrite(motE_2, LOW);
    digitalWrite(motE_3, HIGH);
    digitalWrite(motE_4, LOW);


}
