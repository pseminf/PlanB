/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//#include <DHT.h>

//#define DHTPIN 21

uint32_t humidity_bme;
uint32_t pressure_bme;
uint32_t temperature_bme;



// Sensor DHT, Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//DHT dht(DHTPIN, DHTTYPE);

//char char_humidity[4];
//char char_temperature[4];







char bme_char[32]; // used to sprintf for Serial output

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C


void bme_setup() {

  /* nur für DHT
  uint32_t hum=0;
  hum = dht.readHumidity(true); // mal 100 um die Dezimalstellen zu eliminieren
uint32_t temp=0;
temp= dht.readTemperature(true);
sprintf(bme_char, "Humi: %f", hum);
      screen_print(bme_char);
      delay(MESSAGE_TO_SLEEP_DELAY);
sprintf(bme_char, "Tem: %f", temp);
      screen_print(bme_char);
      delay(MESSAGE_TO_SLEEP_DELAY);
   */

    
    Serial.begin(115200);
    bool status;
    status = bme.begin();
    if (!status) {
      screen_print("No BME");
      delay(MESSAGE_TO_SLEEP_DELAY);
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
       while (1);
    }
}


float humidity() {
    return bme.readHumidity();
}

float pressure() {
   return bme.readPressure();
}

float temperature() {
    return bme.readTemperature();
}

void buildPacket(uint8_t txBuffer[7])
{
  char buffer[40];
/*
  //
  // Relais
  //

  if (relais_on == true)
  {
    txBuffer[0] = ( 01 ) & 0xFF;
    Serial.println("Relais = On");
  }
  else
  {
    txBuffer[0] = ( 00 ) & 0xFF;
    Serial.println("Relais = Off");
  }
*/



  //
  // Humidity
  //
float humidity = bme.readHumidity();
  sprintf(bme_char, "Humidity: %f", humidity);
      Serial.println(bme_char);

  snprintf(buffer, sizeof(buffer), "Humidity: %10.1f\n", humidity);
screen_print(buffer);

  // adjust for the f2sflt16 range (-1 to 1)
 float   hum = humidity / (float)100.0;


  // float -> int
  uint16_t payloadHum = LMIC_f2sflt16(hum);
  //uint16_t payloadHum = 50;

  // int -> bytes
  byte humLow = lowByte(payloadHum);
  byte humHigh = highByte(payloadHum);

  txBuffer[1] = humLow;
  txBuffer[2] = humHigh;


  //
  // Pressure
  //

float pressure = bme.readPressure();

  sprintf(bme_char, "Pressure: %f", pressure / 100);
  Serial.println(bme_char);

 snprintf(buffer, sizeof(buffer), "Pressure: %10.1f\n", pressure / 100);
 screen_print(buffer);

  // adjust for the f2sflt16 range (-1 to 1)
  float press = pressure / (float)10000000.0;


  // float -> int
 uint16_t payloadPress = LMIC_f2sflt16(press);
 //uint16_t payloadPress = 10;

  // int -> bytes
  byte pressLow = lowByte(payloadPress);
  byte pressHigh = highByte(payloadPress);

  txBuffer[3] = pressLow;
  txBuffer[4] = pressHigh;


  //
  // Temperature
  //

float temperature = bme.readTemperature();

  sprintf(bme_char, "Temperature: %f", temperature);
  Serial.println(bme_char);

snprintf(buffer, sizeof(buffer), "Temperature: %10.1f\n", temperature);
screen_print(buffer);

  // adjust for the f2sflt16 range (-1 to 1)
  float temp = (float)(temperature / (float)100.0);


  // float -> int
  uint16_t payloadTemp = LMIC_f2sflt16(temp);
  //uint16_t payloadTemp = 11;

  // int -> bytes
  byte tempLow = lowByte(payloadTemp);
  byte tempHigh = highByte(payloadTemp);

  txBuffer[5] = tempLow;
  txBuffer[6] = tempHigh;

  //TEST
  txBuffer[0] = ( 01 ) & 0xFF;
  /*
      String var = "Hallo";
    txBuffer[0] = var[0];
    txBuffer[1] = var[1];
    txBuffer[2] = var[2];
    txBuffer[3] = var[3];
    txBuffer[4] = var[4];
    */
}
