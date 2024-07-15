#include <ThingSpeak.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Hostpot
const char *ssid =  "AGUS";
const char *pass =  "agus1234";
WiFiClient client;
//thingspeak settings
unsigned long channel = 2542864; //your channel ID number
const char *apiKey = "JLHGPMTWWQEBDGIR"; //your channel write API Key
const int analogPin = 36; // Pin analog untuk membaca sensor tekanan air

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  Serial.begin(9600); // Inisialisasi komunikasi serial
  //connect to WiFi
  Serial.print("Connecting to: "); Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected\n");
  ThingSpeak.begin(client); //initialize ThingSpeak
}

void loop() {
  // Baca nilai analog dari sensor tekanan air
  int sensorValue = analogRead(analogPin);

  // Konversi nilai analog menjadi tekanan dalam bar (diasumsikan menggunakan sensor yang sesuai)
  float pressure = map(sensorValue, 0, 4095, 0, 10); // Ubah dari rentang 0-4095 ke rentang 0-10 bar

  // Cetak nilai tekanan ke Serial Monitor
  Serial.print("Tekanan Air: ");
  Serial.print(pressure);
  Serial.println(" bar");

  display.clearDisplay();
  display.setCursor(10,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("PRESSURE");
  
  display.println();
  display.print(pressure);
  display.println(" BAR");
  display.display();

  int x = ThingSpeak.writeField(channel, 3, pressure, apiKey);
      if (x == 200) {
        Serial.println("Data " + String(pressure));
        Serial.print("Pressure: "); Serial.println(pressure);
        Serial.println("Update Successful.");
      }
      else {
        Serial.println("Data " + String(pressure));
        Serial.println("Problem updating data. HTTP error code " + String(x));
      }
    
      Serial.println("Waiting...\n");
      delay(20000);

  //delay(1000); // Tunda selama 1 detik sebelum membaca sensor lagi
}
