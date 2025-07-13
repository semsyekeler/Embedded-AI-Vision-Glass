#include <Arduino.h>
#include "esp_camera.h"
#include "esp_http_client.h"
#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include <WiFiClient.h>
#include "ESP32FtpServer.h"
#include "Base64.h"
#include "mbedtls/base64.h"
#include <Preferences.h>
#define CAMERA_MODEL_AI_THINKER
#define RECONNECT_TRY_TIMES 25
#include "camera_pins.h"
#include "headers.h"
#include <esp_sleep.h>
#include <driver/uart.h>
#include <ESP32Time.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "driver/rtc_io.h"

String komut = "";
String aktifOlanMod = "normalMod";
Preferences preferencesNesnesi;

const char *ssid = "AkilliCihazlar";
const char *password = "salakschedar";

const char *websocket_server_host = "3.67.198.158";
uint16_t websocket_server_port = 65080;

ESP32Time rtc;
camera_fb_t *fb = NULL;
void setCameraParam(int paramInt)
{
  sensor_t *s = esp_camera_sensor_get();
  s->set_quality(s, 10);
  switch (paramInt)
  {
  case 5:
    s->set_framesize(s, FRAMESIZE_QVGA);
    s->set_quality(s, 30);
    break;
  case 4:
    s->set_framesize(s, FRAMESIZE_UXGA);
    break;

  case 3:
    s->set_framesize(s, FRAMESIZE_SXGA);
    break;

  case 2:
    s->set_framesize(s, FRAMESIZE_XGA);
    break;

  case 1:
    s->set_framesize(s, FRAMESIZE_SVGA);
    break;

  case 0:
  default:
    s->set_framesize(s, FRAMESIZE_VGA);
    break;
  }
}
void disableWifi()
{
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
void enableWifi()
{
  WiFi.disconnect(false);
  WiFi.mode(WIFI_STA);
}
void wifiInit()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    enableWifi();
    WiFi.begin(ssid, password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      i++;
      if (i >= RECONNECT_TRY_TIMES)
      {
        Serial.println("ZamanAsimi");
        normalModaGec();
      }
    }
  }
}
void ftpModunaGec()
{
  preferencesNesnesi.putString("aktifOlanMod", "ftpModu");
  disableWifi();
  Serial.println("kartKapandi");
  ESP.restart();
}
void webSocketYayinModunaGec()
{
  preferencesNesnesi.putString("aktifOlanMod", "webSocketYayinModu");
  disableWifi();
  Serial.println("kartKapandi");
  ESP.restart();
}
void normalModaGec()
{
  preferencesNesnesi.putString("aktifOlanMod", "normalMod");
  Serial.println("kartKapandi");
  ESP.restart();
}
bool createDir(fs::FS &fs, const char *path)
{
  if (fs.mkdir(path))
  {
    return true;
  }
  else
  {
    return false;
  }
}
void kameraInit()
{
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.println("kameraHatasi");
    return;
  }
}
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
  Serial.println("");
  switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
    Serial.println("SunucuyaAtilamadi");
      break;
    case HTTP_EVENT_ON_CONNECTED:
      break;
    case HTTP_EVENT_HEADER_SENT:
    Serial.println("200");
    //s
      break;
    case HTTP_EVENT_ON_HEADER:
    //s
      break;
    case HTTP_EVENT_ON_DATA:
      break;
    case HTTP_EVENT_ON_FINISH:
      break;
    case HTTP_EVENT_DISCONNECTED:
    //sa
      break;
  }
  return ESP_OK;
}
static esp_err_t cekVeSunucuyaYukle(String Amac)
{
  fb = NULL;
  esp_err_t res = ESP_OK;


 
  fb = esp_camera_fb_get();
  if (!fb) {
    return ESP_FAIL;
  }
  
   
 int image_buf_size = 4000 * 1000;                                                  
 uint8_t *image = (uint8_t *)ps_calloc(image_buf_size, sizeof(char));
 size_t length=fb->len;
 size_t olen;
wifiInit();
 int err1 = mbedtls_base64_encode(image, image_buf_size, &olen, fb->buf, length);
 esp_http_client_handle_t http_client;
  esp_http_client_config_t config_client = {0};
   String post_url2 =  "https://xvenofsk9b.execute-api.eu-central-1.amazonaws.com/prod/";
   post_url2.concat(Amac);
   char post_url3[post_url2.length() + 1];
   post_url2.toCharArray(post_url3, sizeof(post_url3));
  
  config_client.url = post_url3;
  config_client.event_handler = _http_event_handler;
  config_client.method = HTTP_METHOD_POST;
  config_client.timeout_ms= 40000;
  http_client = esp_http_client_init(&config_client);

   esp_http_client_set_post_field(http_client, (const char *)fb->buf, fb->len);
  

  esp_http_client_set_header(http_client, "Content-Type", "image/jpeg");

  esp_err_t err = esp_http_client_perform(http_client);
  if (err == ESP_OK) {
    Serial.println(esp_http_client_get_status_code(http_client));
  }

  esp_http_client_cleanup(http_client);

  esp_camera_fb_return(fb);
}

bool fotografCekVeKaydet()
{
  fb = esp_camera_fb_get();
  if (!fb)
  {
    return false;
  }
  String dirPath = "/resimler/" + rtc.getTime("%F");
  if (!createDir(SD_MMC, dirPath.c_str()))
  {
    return false;
  }
  String path = dirPath + "/RESIM" + rtc.getTime("_%FZ_%H.%M.%S") + ".jpg";
  fs::FS &fs = SD_MMC;
  File file = fs.open(path.c_str(), FILE_WRITE);
  if (!file)
  {
    return false;
  }
  else
  {
    file.write(fb->buf, fb->len);
  }
  file.close();
  esp_camera_fb_return(fb);
  return true;
}
void kaydedilenAyarlariAyarla(){
preferencesNesnesi.begin("mod", false);
aktifOlanMod = preferencesNesnesi.getString("aktifOlanMod");

}
void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  kaydedilenAyarlariAyarla();
  Serial.begin(115200);
  Serial.setTimeout(10);
  pinMode(19, INPUT_PULLUP);
  SD_MMC.begin();
  if (aktifOlanMod == "ftpModu")
  {
    kameraInit();
    FtpServer ftpServer;
    wifiInit();
    if (SD_MMC.begin())
    {
      ftpServer.begin("akilli", "yekeler");
      Serial.println(WiFi.localIP());
      
    }else{
      Serial.println("SDhatasi");
      normalModaGec();
    }
    Serial.println("kartBasladi");
    while (1)
    {

      ftpServer.handleFTP();
      if (Serial.available() > 0)
      {
        komutUygula(Serial.readString());
      }
    }
  }
  else if (aktifOlanMod == "webSocketYayinModu")
  {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 10000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 30;
    config.fb_count = 2;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
      Serial.printf("Camera init failed with error 0x%x", err);
      return;
    }
    using namespace websockets;
    WebsocketsClient webSocket;
    wifiInit();
    int i = 0;
    while (!webSocket.connect(websocket_server_host, websocket_server_port, "/"))
    {
      delay(500);
      i++;
      if (i >= RECONNECT_TRY_TIMES)
      {
        normalModaGec();
      }
    }
    Serial.println("WebSocketBaglandi");
    Serial.println("kartBasladi");

    while (1)
    {
      if (Serial.available() > 0)
      {
        komutUygula(Serial.readString());
      }
      fb = esp_camera_fb_get();
      if (!fb)
      {
        Serial.println("Camera capture failed");
        esp_camera_fb_return(fb);
        return;
      }

      if (fb->format != PIXFORMAT_JPEG)
      {
        Serial.println("Non-JPEG data not implemented");
        return;
      }

      webSocket.sendBinary((const char *)fb->buf, fb->len);
      esp_camera_fb_return(fb);
    }
  }
  kameraInit();
  Serial.println("kartBasladi");
}

int ikiNoktadanSonrakiSayiNedir(String _s)
{
  return _s.substring(_s.indexOf(":") + 1).toInt();
}

void komutUygula(String _komut)
{
  if (_komut.indexOf("ftpModu") >= 0)
  {
    ftpModunaGec();
  }
  else if (_komut.indexOf("normalMod") >= 0)
  {
    normalModaGec();
  }  else if (_komut.indexOf("ssidAyarla:") >= 0)
  {
    //ssidAyarla();
  }  else if (_komut.indexOf("passwordAyarla:") >= 0)
  {
    //passwordAyarla();
  }  else if (_komut.indexOf("yayinSunucuAdresiAyarla:") >= 0)
  {
    //yayinSunucuAdresiAyarla();
  }
  else if (_komut.indexOf("yayinModu") >= 0)
  {
    webSocketYayinModunaGec();
  }
  else if (_komut.indexOf("mod") >= 0)
  {
    Serial.println(aktifOlanMod);
  }
  else if (_komut.indexOf("zaman:") >= 0)
  {
    rtc.setTime(ikiNoktadanSonrakiSayiNedir(_komut));
  }
  else if (_komut.indexOf("fotografCek") >= 0)
  {
    if(!fotografCekVeKaydet()){
      Serial.println("fotografCekilemedi");
    }else{
      Serial.println("fotografCekildi");
    }
  }
  else if (_komut.indexOf("ipAdressi") >= 0)
  {
    Serial.println(WiFi.localIP());
  }else if (_komut.indexOf("fotografiYukle:") >= 0)
  {
    
    cekVeSunucuyaYukle( _komut.substring(_komut.indexOf(":") + 1, _komut.indexOf('/')) );
  }else if (_komut.indexOf("wifiKapat") >= 0)
  {
    disableWifi();
  }
}
void loop()
{
  if (Serial.available() > 0)
  {
    komutUygula(Serial.readString());
  }
}