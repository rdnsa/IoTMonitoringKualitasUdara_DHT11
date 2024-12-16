#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C
#define DHTPIN D4 
#define DHTTYPE DHT11

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
DHT dht(DHTPIN, DHTTYPE);

float humi, temp; 

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  dht.begin();   
  delay(1000);
}

void readDHT11()
{
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("DHT11 tidak terbaca... !");
    return;
  }
  else{
  Serial.print("Suhu=");  
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.print("Humi=");
  Serial.print(humi);   
  Serial.println(" %RH");
  Serial.println();
  }  
}

void loop() {
  readDHT11();  
 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("~ DHT11 ~"); 
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,22);
  display.print("T:");
  display.print(temp);
  display.println(" C");
  display.display();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,42);
  display.print("H:");
  display.print(humi);
  
  display.setTextColor(WHITE);
  display.println(" %");
  display.display();  

 
  delay(2000);
}
