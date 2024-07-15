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


const int trigPin = 23; // Pin trigger sensor ultrasonik
const int echoPin = 19; // Pin echo sensor ultrasonik
const float HEIGHT_TABUNG = 14.5; // Tinggi tabung dalam cm

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  Serial.begin(9600); // Inisialisasi komunikasi serial
  pinMode(trigPin, OUTPUT); // Atur pin trigger sebagai output
  pinMode(echoPin, INPUT); // Atur pin echo sebagai input

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
  long duration, distance; // Variabel untuk menyimpan durasi dan jarak
  digitalWrite(trigPin, LOW); // Atur trigger ke LOW
  delayMicroseconds(2); // Tunda 2 mikrodetik
  digitalWrite(trigPin, HIGH); // Atur trigger ke HIGH
  delayMicroseconds(10); // Tunda 10 mikrodetik
  digitalWrite(trigPin, LOW); // Atur trigger kembali ke LOW

  duration = pulseIn(echoPin, HIGH); // Baca durasi dari pin echo
  distance = (duration / 2) * 0.0343; // Hitung jarak dalam cm

  // Kalkulasi tinggi air berdasarkan tinggi tabung dan jarak yang diukur
  float waterSurfaceHeight = HEIGHT_TABUNG - distance;

  // Cetak hasil ke Serial Monitor
  Serial.print("Tinggi Permukaan Air: ");
  Serial.print(waterSurfaceHeight);
  Serial.println(" cm");

  display.clearDisplay();
  display.setCursor(10,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("LEVEL AIR");
  
  display.println();
  display.print(waterSurfaceHeight);
  display.println("Cm");
  display.display();
  int x = ThingSpeak.writeField(channel, 2, waterSurfaceHeight, apiKey);
      if (x == 200) {
        Serial.println("Data " + String(waterSurfaceHeight));
        Serial.print("Level Air: "); Serial.println(waterSurfaceHeight);
        Serial.println("Update Successful.");
      }
      else {
        Serial.println("Data " + String(waterSurfaceHeight));
        Serial.println("Problem updating data. HTTP error code " + String(x));
      }
    
      Serial.println("Waiting...\n");
      delay(20000);

  //delay(1000); // Tunda selama 1 detik sebelum mengulangi pengukuran
}
