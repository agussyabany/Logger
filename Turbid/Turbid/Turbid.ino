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

int sensorPin = 36;
float volt;
float ntu;
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  Serial.begin(9600); //Baud rate: 9600

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
 volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/4095)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }
    else{
      ntu = (-781.25*volt) + 3000; 
    }
  Serial.println(ntu); // print out the value you read:
  delay(1000);
  Serial.println(volt);

  display.clearDisplay();
  display.setCursor(10,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("TURBIDITY");
  
  display.println();
  display.print(ntu);
  display.println("NTU");
  display.display();

    int x = ThingSpeak.writeField(channel, 1, ntu, apiKey);
      if (x == 200) {
        Serial.println("Data " + String(ntu));
        Serial.print("turbidity: "); Serial.println(ntu);
        Serial.println("Update Successful.");
      }
      else {
        Serial.println("Data " + String(ntu));
        Serial.println("Problem updating data. HTTP error code " + String(x));
      }
    
      Serial.println("Waiting...\n");
      delay(20000);
  

  
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
