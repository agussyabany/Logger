#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
unsigned long start_times[300];
unsigned long stop_times[300];
unsigned long values[300];
float adc;
const int analogInPin = 36; // Pin A0 pada ESP32
const int PS_128 = 7; // Konstanta untuk prescaler pada ESP32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  // Konfigurasi ADC
  analogReadResolution(12); // Set resolusi ADC menjadi 12-bit
  analogSetClockDiv(PS_128); // Set prescaler ke 128
}

void loop() {
  adc = analogRead(analogInPin);

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
  display.print("NTU: ");
  display.println();
  display.display();
  delay(200); // Delay untuk stabilisasi
}
