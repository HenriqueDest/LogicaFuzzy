// Define os pinos para o sensor ultrassônico
const int TRIGGER_PIN = 11;
const int ECHO_PIN = 6;
int speedValue;
// Define o pino para o sensor de temperatura LM35
const int TEMP_PIN = A0;

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);

  // Configura os pinos do sensor ultrassônico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Variáveis para armazenar as medições
  float distance, temperature, duration;
  // Medição da distância
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) * 0.0343;
  if (distance > 50){
    distance = 50;
  }
  // Medição da temperatura
  int sensorValue = analogRead(TEMP_PIN);
  float millivolts = (sensorValue / 1024.0) * 5000;
  temperature = (millivolts / 10);

    // Envia as medições pela porta serial

  Serial.print("D");
  Serial.print(distance);
  Serial.println("T" +(String)temperature);

  if (Serial.available() > 0) {
  String incomingData = Serial.readStringUntil('\n');
  speedValue = incomingData.toInt();}

  
  analogWrite(9, speedValue);
 
  // Espera um segundo antes da próxima medição
  delay(1000);

}
