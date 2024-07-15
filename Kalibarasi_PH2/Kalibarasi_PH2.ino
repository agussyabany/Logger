const int sensorPin = A0; // Pin AO sebagai input analog
const float slope = -326.87; // Gradien dari rumus yang kita hitung sebelumnya
const float intercept = 5303.48; // Intersep dari rumus yang kita hitung sebelumnya

void setup() {
  Serial.begin(9600); // Mulai komunikasi serial dengan baud rate 9600
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Baca nilai analog dari sensor pH
  float pHValue = calculatepH(sensorValue); // Hitung nilai pH berdasarkan nilai ADC
  
  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print("   pH: ");
  Serial.println(pHValue);
  
  delay(1000); // Tunda 1 detik sebelum membaca nilai lagi
}

float calculatepH(int adcValue) {
  float pH = slope * adcValue + intercept; // Hitung nilai pH menggunakan rumus yang telah ditentukan
  return pH;
}
