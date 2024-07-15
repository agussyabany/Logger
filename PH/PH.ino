#include <ThingSpeak.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
const int potPin=39;
float ph;
float Value=0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Hostpot
const char *ssid =  "AGUS";
const char *pass =  "agus1234";
WiFiClient client;
//thingspeak settings
unsigned long channel = 2542864; //your channel ID number
const char *apiKey = "JLHGPMTWWQEBDGIR"; //your channel write API Key
void setup() {
  Serial.begin(9600);
  pinMode(potPin,INPUT);
  delay(1000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
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

  Value= analogRead(potPin);
    Serial.print(Value);
    Serial.print(" | ");
    float voltage=Value*(3.3/4095.0);
    ph=(4545.1 - Value)/ 232.59;;
    Serial.println(ph);
    delay(500);
  display.clearDisplay();
  display.setCursor(40,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("pH");
  
  display.println();
  display.print(ph);
  display.display();

   int x = ThingSpeak.writeField(channel, 4, ph, apiKey);
      if (x == 200) {
        Serial.println("Data " + String(ph));
        Serial.print("Pressure: "); Serial.println(ph);
        Serial.println("Update Successful.");
      }
      else {
        Serial.println("Data " + String(ph));
        Serial.println("Problem updating data. HTTP error code " + String(x));
      }
    
      Serial.println("Waiting...\n");
      delay(5000);
}
