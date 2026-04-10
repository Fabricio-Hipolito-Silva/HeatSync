#include <Arduino.h>
#include <DHT.h>

//Definições
#define DHTPIN 40
#define DHTTYPE DHT11
DHT sensor (DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor Iniciado"));
  sensor.begin();
}

void loop() {
 delay(2000); // Delay para não dar sobrecarga
 float h = sensor.readHumidity();
 float t = sensor.readTemperature();

 if(isnan(h) || isnan(t)){ //Se a temperatura ou humidade não for um número (isnan), ele falha
  Serial.println("Leitura Falhou");
  return;
 }

 //Isso aqui calcula a sensação térmica (Irado)
 float st = sensor.computeHeatIndex(t, h, false);

//Não vou mentir, pedi pro ChatGPT deixar essa parte aqui bonitinha.
  Serial.println(F("------ Leitura do Ambiente ------"));

  Serial.print(F("Umidade: "));
  Serial.print(h);
  Serial.println(F(" %"));

  Serial.print(F("Temperatura: "));
  Serial.print(t);
  Serial.println(F(" °C"));

  Serial.print(F("Sensação Térmica: "));
  Serial.print(st);
  Serial.println(F(" °C"));

  Serial.println(F("---------------------------------\n"));
}
