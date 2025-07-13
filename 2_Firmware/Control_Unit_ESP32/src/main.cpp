//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <BluetoothSerial.h>
#include <ESP32Time.h>
#include "headers.h"
#include <analogWrite.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define sw2 33
#define sw 32
#define solLed 12
#define sagLed 25
#define titresimMotoru 15
#define bluetoothKulaklik 26
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 64
//#define OLED_RESET     -1 
//#define SCREEN_ADDRESS 0x3C

String SerialdenEnSonGelenKomut = "";
String BTdenEnSonGelenKomut = "";
//String sonEkranaYazilan = "";

//yuzey 1
int lastButtonState = HIGH;  
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 25;  
bool buttonState = HIGH; 
byte tapCounter; 
int timediff;
bool flag1, flag2;
long double presstime, releasetime; 



//bool ekranBaglandiMi = true;
int titremeSuresi = 300;
int titremeTekrarSayisi = 1;

int solLedParlaklik = 0;
int sagLedParlaklik = 0;
int komutIndexi = 0;
#define touchKalibreDegeri 19

bool kameraKartiBasladiMi = false;

BluetoothSerial BLUETOOTH;
ESP32Time rtc;

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void bluetoothKulaklikTask(void *parameter){
  digitalWrite(bluetoothKulaklik,HIGH);
  vTaskDelay(3000 / portTICK_PERIOD_MS);
  digitalWrite(bluetoothKulaklik,LOW);
  vTaskDelete( NULL );
}
void bluetoothKulaklikStartStopTask(void *param){
  digitalWrite(bluetoothKulaklik,HIGH);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  digitalWrite(bluetoothKulaklik,LOW);
  vTaskDelete( NULL );
}
void titresimMotoruTask(void *parameter){
  for(int i = 0;i<titremeTekrarSayisi;i++){
    digitalWrite(titresimMotoru,HIGH);
    vTaskDelay(titremeSuresi / portTICK_PERIOD_MS);
    digitalWrite(titresimMotoru,LOW);
    vTaskDelay(titremeSuresi / portTICK_PERIOD_MS);
  }
  vTaskDelete( NULL );
}
void titresimMotorunuSur(int _time,int _tekrarSayisi){
  titremeSuresi = _time;
  titremeTekrarSayisi = _tekrarSayisi;
 xTaskCreate(
                    titresimMotoruTask,          /* Task function. */
                    "TitresimMotoruTask",        /* String with name of task. */
                    1000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);  
}
void bluetoothKulaklikSur(){
  
   xTaskCreate(
                    bluetoothKulaklikTask,          /* Task function. */
                    "BluetoothKulaklikTask",        /* String with name of task. */
                    1000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);  
}
void btKulaklikStopStart(){
   xTaskCreate(
                    bluetoothKulaklikStartStopTask,          /* Task function. */
                    "BluetoothKulaklikStartStopTask",        /* String with name of task. */
                    1000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);  
}
void btKulaklikReddetTask(void *param){
  digitalWrite(bluetoothKulaklik,HIGH);
  vTaskDelay(2170 / portTICK_PERIOD_MS);
  digitalWrite(bluetoothKulaklik,LOW);
  vTaskDelete( NULL );
}
void btKulaklikReddet(){
   xTaskCreate(
                    btKulaklikReddetTask,          /* Task function. */
                    "BtKulaklikReddetTask",        /* String with name of task. */
                    1000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);  
}

int ikiNoktadanSonrakiSayiNedir(String _s){
  return _s.substring(_s.indexOf(":")+1).toInt();
}
void btKomutuUygula(String _komut){
  if(_komut.indexOf("solLed:") >= 0){
    solLedParlaklik = ikiNoktadanSonrakiSayiNedir(_komut);
    analogWrite(solLed,solLedParlaklik);
  }else if (_komut.indexOf("sagLed:") >= 0){
    sagLedParlaklik = ikiNoktadanSonrakiSayiNedir(_komut);
    analogWrite(sagLed,sagLedParlaklik);
  }else if(_komut.indexOf("ekran:") >= 0){
    //ekranaYazdir(_komut.substring(_komut.indexOf(":")+1));
  }else if(_komut.indexOf("titresimMotoru:") >= 0){
    titresimMotorunuSur(ikiNoktadanSonrakiSayiNedir(_komut),1);
  }else if(_komut.indexOf("bluetoothKulaklik") >= 0){
    bluetoothKulaklikSur();
  }else if(_komut.indexOf("ledleriDegereGetir:") >= 0){
    sagLedParlaklik = ikiNoktadanSonrakiSayiNedir(_komut);
    analogWrite(sagLed,sagLedParlaklik);
    solLedParlaklik = sagLedParlaklik;
    analogWrite(solLed,solLedParlaklik);
  }else if(_komut.indexOf("herseyiSifirla") >= 0){
    analogWrite(sagLed,0);
    analogWrite(solLed,0);
    sagLedParlaklik = 0;
    solLedParlaklik = 0;
    //ekranaYazdir("");
  }else if(_komut.indexOf("zaman:") >= 0){
    rtc.setTime(ikiNoktadanSonrakiSayiNedir(_komut));
    String temp = "zaman:"+ikiNoktadanSonrakiSayiNedir(_komut);
    Serial.println(temp);

  }else if(_komut.indexOf("mod") >= 0){
    Serial.println("mod");
  }else if(_komut.indexOf("ftpModu") >= 0){
    Serial.println("ftpModu");
  }else if(_komut.indexOf("normalMod") >= 0){
    Serial.println("normalMod");
  }else if(_komut.indexOf("yayinModu") >= 0){
    Serial.println("yayinModu");
  }else if(_komut.indexOf("ipAdressi") >= 0){
    Serial.println("ipAdressi");
  }else if(_komut.indexOf("zaman?") >= 0){
    BLUETOOTH.println(rtc.getTime("%F %H.%M.%S"));
  }else{
    Serial.println(_komut);
  }
}
void bt_callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    //bağlanıldığında


  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    //disconn
  }
  else if (event == ESP_SPP_DATA_IND_EVT ) {
    BTdenEnSonGelenKomut = BLUETOOTH.readString();
    btKomutuUygula(BTdenEnSonGelenKomut);

  }
}




void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200); //for serial monitor
  Serial.setTimeout(10);
  BLUETOOTH.begin("AkıllıGözlük");
  BLUETOOTH.setTimeout(10);
  pinMode(solLed, OUTPUT);
  pinMode(sagLed, OUTPUT);
  pinMode(titresimMotoru, OUTPUT);
  pinMode(bluetoothKulaklik, OUTPUT);
  BLUETOOTH.register_callback(bt_callback_function);
 

 /*if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    ekranBaglandiMi = false;
  }else{
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("");
  display.display();
  }*/

}

void hataTitremesi(){
  titresimMotorunuSur(250,2);
}
void olumluTitreme(){
  titresimMotorunuSur(250,1);
}
void komutIndexiKontrolcusu(){
  unsigned long baslangictakiSure = millis();
  unsigned long basilmaSuresi;
  int touchDegeri = touchRead(sw2);
  if(touchDegeri<touchKalibreDegeri){
  delay(5);
  touchDegeri = touchRead(sw2);
  if(touchDegeri<touchKalibreDegeri){
  touchDegeri = touchRead(sw2);
  while(touchDegeri<touchKalibreDegeri){
    touchDegeri = touchRead(sw2);
  }
  basilmaSuresi =  millis() - baslangictakiSure;
  if(basilmaSuresi>=1000){
   komutIndexi = 0;
   titresimMotorunuSur(1000,1);
  }else if(basilmaSuresi>=30){
    if(komutIndexi<3){
    komutIndexi++;
    }else{
      komutIndexi = 0;
      titresimMotorunuSur(1000,1);
    }
  }

  }
  }
}
void komutuUygula(String _komut){
  if(_komut.indexOf("kartBasladi")>= 0){
    kameraKartiBasladiMi = true;
    String temp ="zaman:" + String(rtc.getEpoch());
    Serial.println(temp);
  }else if(_komut.indexOf("kartKapandi") >= 0){
    kameraKartiBasladiMi = false;
  }else if(_komut.indexOf("196.168") >= 0){
    String temp = "ipAdressi:"+_komut;
    BLUETOOTH.println(temp);
  }else if(_komut.indexOf("fotografCekilemedi") >= 0){
    hataTitremesi();
    BLUETOOTH.println(_komut);
  }else if(_komut.indexOf("kameraHatasi") >= 0){
    hataTitremesi();
    BLUETOOTH.println(_komut);
  }
  else if(_komut.indexOf("fotografCekildi") >= 0){
    olumluTitreme();
    BLUETOOTH.println(_komut);
  }else if(_komut.indexOf("SDhatasi") >= 0){
    hataTitremesi();
    BLUETOOTH.println(_komut);
  }else if(_komut.indexOf("ZamanAsimi") >= 0){
    hataTitremesi();
    BLUETOOTH.println(_komut);
  }else if(_komut.indexOf("SunucuyaAtilamadi") >= 0){
    hataTitremesi();
    BLUETOOTH.println(_komut);
  }else if(_komut.indexOf("200") >= 0){
    olumluTitreme();
    BLUETOOTH.println(_komut);
  }
  else{
    BLUETOOTH.println(_komut);
  }

}
/*void ekranaYazdir(String _s){
  if(ekranBaglandiMi){
  if(sonEkranaYazilan != _s){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(_s);
  display.display();
  sonEkranaYazilan = _s;
  }
  }
}*/


void loop() {
  if(Serial.available() > 0){
    SerialdenEnSonGelenKomut = Serial.readString();
    komutuUygula(SerialdenEnSonGelenKomut);
  }
  //yuzey bir 
  int readingOne = 0;
  if(touchRead(sw)>19){
    readingOne = 1;
  }
  if (readingOne != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingOne != buttonState) {
      buttonState = readingOne;
    }
  }
  if (buttonState == 0 && flag2 == 0)
  {
    presstime = millis(); 
    flag1 = 0;
    flag2 = 1;
    tapCounter++;
  }
  if (buttonState == 1 && flag1 == 0)
  {
    releasetime = millis(); 
    flag1 = 1;
    flag2 = 0;

    timediff = releasetime - presstime; 
  }
  if ((millis() - presstime) > 400 && buttonState == 1) 
  {
    if (tapCounter == 1)
    {
      if (timediff >= 400)
      {
        hold(); 
      }
      else
      {
        singleTap(); 
        }
    }else if (tapCounter ==2){
      doubleTap();
    }
    else if (tapCounter == 3) 
    {
      tripleTap(); 
    }
    tapCounter = 0;
  }
  lastButtonState = readingOne;

komutIndexiKontrolcusu();
  
}
void singleTap()
{
  BLUETOOTH.println("asistan");
  titresimMotorunuSur(100,1);
}
void doubleTap()
{
  doubleTapIndexYonlendiricisi();
  titresimMotorunuSur(100,2);
}
void tripleTap()
{
  tripleTapIndexYonlendiricisi();
  titresimMotorunuSur(100,3);
}
void hold()
{
  holdTapIndexYonlendiricisi();
  titresimMotorunuSur(1000,1);
}

void doubleTapIndexYonlendiricisi(){
  switch ( komutIndexi )
  {
  case 0:
  Serial.println("fotografCek");
  break;
  case 1:
  btKulaklikStopStart();
  break;
  case 2:
  Serial.println("fotografiYukle:fotograf-analizi/");
  break;
  case 3:
  Serial.println("fotografiYukle:para-tespiti/");
  break;
  }
}
void tripleTapIndexYonlendiricisi(){
  switch ( komutIndexi )
  {
  case 0:
  Serial.println("yayinModu");
  break;
  case 1:
  btKulaklikReddet();
  break;
  case 2:
  Serial.println("fotografiYukle:ocr/");
  break;
  case 3:
  Serial.println("fotografiYukle:yuz-tanima/");
  BLUETOOTH.println("yuzTanima");
  break;
  }
}

void ledDurumuDegistir(){
if(solLedParlaklik<255 || sagLedParlaklik<255){
    solLedParlaklik = 255;
    sagLedParlaklik = 255;
    analogWrite(sagLed,255);
    analogWrite(solLed,255);
  }else{
    solLedParlaklik = 0;
    sagLedParlaklik = 0;
    analogWrite(sagLed,0);
    analogWrite(solLed,0);   
  }
}
void holdTapIndexYonlendiricisi(){
  switch ( komutIndexi )
  {
  case 0:
  ledDurumuDegistir();
  break;
  case 1:
  bluetoothKulaklikSur();
  break;
  case 2:
  Serial.println("fotografiYukle:ocr/");
  BLUETOOTH.println("ceviriModu");
  break;
  case 3:
  BLUETOOTH.println("neredeyim");
  break;
  }
}