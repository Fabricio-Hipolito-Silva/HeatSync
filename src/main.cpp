#include <Arduino.h>
#include <DHT.h>
#include <TFT_eSPI.h>

//Definições
#define DHTPIN 40
#define DHTTYPE DHT11
#define Y_TITULO 10
#define Y_U 40
#define Y_T 70
#define Y_ST 100
#define X_F 155
DHT sensor (DHTPIN, DHTTYPE);
TFT_eSPI tela = TFT_eSPI();


void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor Iniciado"));
  sensor.begin();
  tela.init();
  tela.setRotation(1);
  tela.fillScreen(TFT_BLACK);
  tela.setTextColor(TFT_WHITE);
  tela.setTextFont(2);

// Header
  tela.setTextDatum(MC_DATUM);
  tela.drawString("Quarto", 80, 10);
// Body
  tela.setTextDatum(ML_DATUM);
  tela.drawString("Umidade: ", 10, Y_U);
  tela.drawString("Temperatura: ", 10, Y_T);
  tela.drawString("Sens.Termica: ", 10, Y_ST);


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

  // Limpa só a área dos valores
  tela.fillRect(X_F - 70, Y_U - 12, 70, 24, TFT_BLACK); 
  tela.fillRect(X_F - 70, Y_T - 12, 70, 24, TFT_BLACK);
  tela.fillRect(X_F - 70, Y_ST - 12, 70, 24, TFT_BLACK);
  //A lógica é: ele começa a -70 pixels do final do texto, e um pouco acima, (-12).
  //Depois ele limpa em preto os 70 pixels de largura e 24 de algura, pra pegar todo o texto (Mais por garantia)

  //Alinhamento
  tela.setTextDatum(MR_DATUM);

  tela.setTextColor(TFT_GREEN);
  tela.drawString(String(h, 0) + " %", X_F, Y_U);
  tela.setTextColor(TFT_CYAN);
  tela.drawString(String(t, 1) + " C", X_F, Y_T);
  tela.setTextColor(TFT_YELLOW);
  tela.drawString(String(st, 1) + " C", X_F, Y_ST);

}
