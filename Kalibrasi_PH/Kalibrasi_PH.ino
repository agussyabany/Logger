#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
int adc;
float ph;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
 }

void loop() {
  adc = analogRead(39);
  float volt = adc * (3.3 /4095.0);

  ph=(4545.1 - adc)/ 232.59;
  // Lakukan sesuatu dengan nilai NTU, misalnya kirim melalui Serial
  Serial.print("ADC: ");
  Serial.println(adc);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Kalibrasi");
  
//  display.println();
  display.print("ADC: ");
  display.println(adc);
  display.print("pH: ");
  display.println(ph);
   display.print("Volt: ");
  display.println(volt);
  display.display();
  delay(200); // Delay untuk stabilisasi
}
