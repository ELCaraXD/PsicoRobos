
#include <WiFi.h>

void setup() {
 
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
 
  delay(200);

  Serial.print("Endereço MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() {

}