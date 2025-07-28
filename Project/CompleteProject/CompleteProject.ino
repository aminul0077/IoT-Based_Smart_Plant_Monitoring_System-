#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int water;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int soilMoisturePin = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();         
  lcd.backlight();
  pinMode(3,OUTPUT);
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read soil moisture from YL-69 sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Map the soil moisture value to a percentage (adjust the mapping based on your sensor and soil)
  int soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Print the sensor values to the serial monitor
  // Serial.print("Temperature: ");
  // Serial.print(temperature);
  // Serial.print(" °C, Humidity: ");
  // Serial.print(humidity);
  // Serial.print("%, Soil Moisture: ");
  // Serial.print(soilMoisturePercentage);
  // Serial.println("%");
  lcd.setCursor(1, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(1, 1);
  lcd.print(temperature);
  lcd.print("C");
  delay(3000);
  lcd.clear();


  lcd.setCursor(1, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(1, 1);
  lcd.print(humidity);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(1, 1);
  lcd.print(soilMoisturePercentage);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  water = soilMoisturePercentage;  // reading the coming signal from the soil sensor
  if(water <= 50) // if water level is full then cut the relay 
  {
  digitalWrite(3,LOW); // low is to cut the relay
  lcd.setCursor(1, 0);
  lcd.print("Motor OFF");
  }
  else 
  {
  digitalWrite(3,HIGH); //high to continue proving signal and water supply
  lcd.setCursor(1, 0);
  lcd.print("Motor ON");
  }

  delay(2000);  // Wait for 2 seconds before reading again
}




