#include "DHT.h"
#include <RH_ASK.h>

#define DHTPIN 2
#define DHTTYPE DHT11

char Unit_ID[] = "001";
char Packet_Type[] = "W1";  // Weather version 1

DHT dht(DHTPIN, DHTTYPE);
RH_ASK driver;

// Data packet
struct packet {
  char unit_id[3];
  char type[2];
  char temp[3];
  char humidity[3];
  char wind_speed[3];
  char rainfall[5];
};


char msg[27];
packet data;
packet *ptr_data;


void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  //if (!driver.init())
  //  Serial.println("init failed");

  data.unit_id[3] = *Unit_ID;
  data.type[2] = *Packet_Type;

  dht.begin();
}


void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  sprintf(data.temp,"%ld", f);
  sprintf(data.humidity,"%ld", h);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  packet2str(data).toCharArray(msg, 27);

  driver.send((uint8_t *)msg, 27);
  driver.waitPacketSent(); 
}



String packet2str(packet packet) {
    return String(packet.unit_id) + String(packet.type) + String(packet.temp) + String(packet.humidity) + String(packet.wind_speed) + String(packet.rainfall);
}
