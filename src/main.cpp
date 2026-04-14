#include <Arduino.h>
#include <DHT.h>
#include <TFT_eSPI.h>
#include "face.h"

//Definições
#define DHTPIN 40
#define DHTTYPE DHT11
#define Y_TITULO 10
#define Y_U 40
#define Y_T 70
#define Y_ST 100
#define X_F 155
#define BUTTONPIN 35
DHT sensor (DHTPIN, DHTTYPE);
TFT_eSPI tela = TFT_eSPI();
bool doneSetup = false;
float h;
float t;
float st;
bool precisionMode;
enum stateClimate{
  FRIO,
  AGRADAVEL,
  QUENTE,
  INICIAL
};
stateClimate state;
static stateClimate lastState = INICIAL;
bool lastButton = HIGH;
bool ultimoModo = false;

void DetailedMode(){
  if(doneSetup == false){ //Lógica da Função pra ele não rodar o setup toda vez
// Header
  tela.setTextColor(TFT_WHITE);
  tela.setTextFont(2);
  tela.setTextDatum(MC_DATUM);
  tela.drawString("Quarto", 80, 10);
// Body
  tela.setTextDatum(ML_DATUM);
  tela.drawString("Umidade: ", 5, Y_U);
  tela.drawString("Temperatura: ", 5, Y_T);
  tela.drawString("Sen.Termica: ", 5, Y_ST);
  doneSetup = true;
  }
  //Código Modo Precisão

  // Limpa só a área dos valores
  tela.fillRect(X_F - 65, Y_U - 12, 65, 24, TFT_BLACK); 
  tela.fillRect(X_F - 65, Y_T - 12, 65, 24, TFT_BLACK);
  tela.fillRect(X_F - 65, Y_ST - 12, 65, 24, TFT_BLACK);
  //A lógica é: ele começa a -65 pixels do final do texto, e um pouco acima, (-12).
  //Depois ele limpa em preto os 60 pixels de largura e 24 de algura, pra pegar todo o texto (Mais por garantia)

  //Alinhamento
  tela.setTextDatum(MR_DATUM);

  tela.setTextColor(TFT_GREEN);
  tela.drawString(String(h, 0) + " %", X_F, Y_U);
  tela.setTextColor(TFT_CYAN);
  tela.drawString(String(t, 1) + " C", X_F, Y_T);
  tela.setTextColor(TFT_YELLOW);
  tela.drawString(String(st, 1) + " C", X_F, Y_ST);

};

void faceMode(){
  if(st < 20){
    state = FRIO;
  }else if(st < 28){
    state = AGRADAVEL;
  }else{
    state = QUENTE;
  };

  if (lastState != state)
  {
    switch (state)
    {
    case FRIO:
    desenharRostoFrio(tela);
    break;
    case AGRADAVEL:
    desenharRostoAgradavel(tela);
    break;
    case QUENTE:
    desenharRostoQuente(tela);
    break;
    }
    lastState = state;
 };
};


void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor Iniciado"));
  sensor.begin();
  tela.init();
  tela.setRotation(1);
  tela.fillScreen(TFT_BLACK);
  pinMode(BUTTONPIN, INPUT_PULLUP);
};


void loop() {

 delay(1000); // Delay para não dar sobrecarga
  h = sensor.readHumidity();
  t = sensor.readTemperature();

 if(isnan(h) || isnan(t)){ //Se a temperatura ou humidade não for um número (isnan), ele falha
  Serial.println("Leitura Falhou");
  return;
 }

 //Isso aqui calcula a sensação térmica (Irado)
 st = sensor.computeHeatIndex(t, h, false);

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


int buttonstate = digitalRead(BUTTONPIN);

// Esquema Flip/Flop
if (lastButton == HIGH && buttonstate == LOW) {
  precisionMode = !precisionMode;
}

lastButton = buttonstate;

 if (precisionMode != ultimoModo) {
  tela.fillScreen(TFT_BLACK);
  doneSetup = false;
  lastState = INICIAL;
  ultimoModo = precisionMode;
}
 
 if (precisionMode == true){ 
  DetailedMode();
 }else if(precisionMode == false){
  faceMode();
 };








}
