
#include "ESP32_S3_Box_TFT.h"
#include <AsyncTelegram2.h>
#include <time.h>
#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <WiFiClient.h>
#include <SSLClient.h>
#include "tg_certificate.h"

#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

#define MIN_LIGHT_VALUE 500
#define LIGHT_IS_ON 1
#define LIGHT_IS_OFF 2
String LuzColor = "";

 enum  homeCommand {
  INTRO,
  LIGHT_ON,
  LIGHT_OFF,
  LIGHT_RED,
  LIGHT_BLUE,
  LIGHT_PINK,
  LIGHT_GREEN,
  LIGHT_WHITE,
  LIGHT_BRIGHT_IN,
  LIGHT_BRIGHT_DEC,
  LIGHT_SENSOR_AUTO,
  LIGHT_SENSOR_AUTO_OFF,
  FIN
};



WiFiClient base_client;
//Used Analog pin 12 
SSLClient client(base_client, TAs, (size_t)TAs_NUM, 12, 1, SSLClient::SSL_ERROR);

//Graficos ESP32 S3 BOX
ESP32S3BOX_TFT tft = ESP32S3BOX_TFT();
 
 bool autoLightControlEnabled = false;
 int lightCheck = 0;
 int brillo = 100;


//WIFI PARAMETERS
const char* ssid =  "Add your Wifi SSID";
const char* password = "Add your Wifi Password";


//Telegram Parameters
const char* token = "";//Add your Telegram Bot token Here!
AsyncTelegram2 myBot(client);


void executeCommand(homeCommand receivCommand)
{
  int httpCode;
  HTTPClient http;
  switch (receivCommand)
  {
      case INTRO:
        tft.setTextSize(2);   
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("    TECHWELL LIVING HOME");
        tft.setCursor(0, 40);
        tft.print("Bienvenido a Casa :)");
        tft.setCursor(0, 100);
        tft.setTextColor(ST7789_GREEN);
        tft.print("WIFI: CONECTADO");
        break;
      case LIGHT_ON:
      //sets up the connection to the specified URL
        http.begin("http://192.168.1.63/light/0?turn=on");
        //perform the GET request. The function returns the HTTP response code.
        httpCode = http.GET();
        /*
         If httpCode > 0 to response was received. If the response code is HTTP_CODE_OK (200) -->Successful Get Request
          We can then retrieve the response payload using http.getString() and print it to the serial monitor.
        */

        Serial.println("HTTP Code "+ httpCode);      
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: ON");
        break;

        case LIGHT_OFF:
        http.begin("http://192.168.1.63/light/0?turn=off");
        httpCode = http.GET();
         Serial.println("HTTP Code "+ httpCode);      
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: OFF");
        break;
      case LIGHT_RED:
        LuzColor = "ROJO";
        http.begin("http://192.168.1.63/light/0?turn=on&red=255&green=0&blue=0");
        httpCode = http.GET();
        Serial.println("HTTP Code "+ httpCode);      
        Serial.println("Color ROJOOOOOOO");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_RED);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: ROJO");
      break;

      case LIGHT_BLUE:
      LuzColor = "AZUL";
        http.begin("http://192.168.1.63/light/0?turn=on&red=0&green=0&blue=255");
        httpCode = http.GET();
        Serial.println("Color azul");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: AZUL");
      break;
      case LIGHT_PINK:
        LuzColor = "ROSA";
        http.begin("http://192.168.1.63/light/0?turn=on&red=255&green=6&blue=198");
        httpCode = http.GET();
        Serial.println("Color Rosa");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_MAGENTA);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: ROSA");
      break;

      case LIGHT_GREEN:
      LuzColor = "VERDE";
       http.begin("http://192.168.1.63/light/0?turn=on&red=0&green=255&blue=0"); 
        httpCode = http.GET();
        Serial.println("Color VERDE");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: VERDE");
      break;

      case LIGHT_WHITE:
      LuzColor = "BLANCO";
       http.begin("http://192.168.1.63/light/0?turn=on&red=255&green=255&blue=255"); //Specify the URL
        httpCode = http.GET();
        Serial.println("Color Blanco");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_WHITE);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_BLACK);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: BLANCO");
      break;
      case LIGHT_SENSOR_AUTO:
        lightCheck = 0;
        autoLightControlEnabled = true;
      break;
      case LIGHT_SENSOR_AUTO_OFF:
        autoLightControlEnabled = false;
      break;
      case LIGHT_BRIGHT_IN:
      if (brillo <= 80){
        brillo = brillo + 20;
      }
       http.begin("http://192.168.1.63/light/0?gain="+  (String)brillo); 
        httpCode = http.GET();
        Serial.println("Color Blanco");
        tft.setTextSize(2);    
        // large block of text
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: " + LuzColor);
        tft.setCursor(0, 100);
        tft.print("BRILLO: "+(String) brillo+"%");
      break;
      case LIGHT_BRIGHT_DEC:
        if (brillo >= 20){
        brillo = brillo - 20;
      }
       http.begin("http://192.168.1.63/light/0?gain="+(String)brillo);
        httpCode = http.GET();
        Serial.println("Color Blanco");
        tft.setTextSize(2);    
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TECHWELL LIVING HOME");
        tft.setCursor(0, 60);
        tft.print("LUZ DORMITORIO: " + LuzColor);
        tft.setCursor(0, 100);
        tft.print("BRILLO: "+(String) brillo+"%");

      break;
        case FIN:
        Serial.println(testLines(ST7789_CYAN));
        delay(300);
        Serial.print("Horiz/Vert Lines");
        Serial.println(testFastLines(ST7789_RED, ST7789_BLUE));
        delay(500);
        tft.setTextSize(2);   
        tft.fillScreen(ST7789_BLACK);
        tft.setTextWrap(true);
        tft.setTextColor(ST7789_WHITE);
        tft.setCursor(0, 0);
        tft.print("TechWell Living Home");
        tft.setCursor(0, 30);
        tft.print("Be TWL Suscriber my friend");
        tft.setCursor(0, 60); 
        tft.print("Muchas Gracias!");
        break;

        default:
        break;

  }

}
void setup()
{

  Serial.begin(115200);
  tft.init();
  tft.setRotation(0);
  tft.setTextSize(2);
  executeCommand(INTRO);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");

  // Set the Telegram bot properties
  myBot.setUpdateTime(500);//Time in ms to refresh Telegram queries
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  Serial.print("Bot name: @");
  Serial.println(myBot.getBotName());
}

void loop() 
{
    TBMessage msg;
    // if there is an incoming message...
    if (myBot.getNewMessage(msg)) {
      String msgText = msg.text;

      if (msgText.equals("/l1on")) {               
        myBot.sendMessage(msg, "LUZ ENCENDIDA");     
        executeCommand(LIGHT_ON);                
      }
      else if (msgText.equals("/l1off")) {         .
        myBot.sendMessage(msg, "LUZ APAGADA");      
        executeCommand(LIGHT_OFF);               
      }
      else if (msgText.equals("/l1red")) {        
        myBot.sendMessage(msg, "Luz en color Rojo!");
        executeCommand(LIGHT_RED);
      }
      else if (msgText.equals("/l1blue")) {          
        myBot.sendMessage(msg, "Luz en color Azul!");
        executeCommand(LIGHT_BLUE);
      }
      else if (msgText.equals("/l1white")) {          
        myBot.sendMessage(msg, "Luz en color Blanco!");
        executeCommand(LIGHT_WHITE);
      }
      else if (msgText.equals("/l1pink")) {          
        myBot.sendMessage(msg, "Luz en color Rosa!");
        executeCommand(LIGHT_PINK);
      }
      else if (msgText.equals("/l1green")) {          
        myBot.sendMessage(msg, "Luz en color Verde!");
        executeCommand(LIGHT_GREEN);
      }

      else if (msgText.equals("/auto")) {       
        myBot.sendMessage(msg, "Modo Automatico Activado!");
        executeCommand(LIGHT_SENSOR_AUTO);
      }
      else if (msgText.equals("/auto_off")) {       
        myBot.sendMessage(msg, "Modo Automatico Apagado!");
        executeCommand(LIGHT_SENSOR_AUTO_OFF);
      }
      else if (msgText.equals("/l1brimore")) {       
        executeCommand(LIGHT_BRIGHT_IN);
         myBot.sendMessage(msg, "Brillo Subido "+(String)brillo+"%");
      }
      else if (msgText.equals("/l1briless")) {       
        executeCommand(LIGHT_BRIGHT_DEC);
         myBot.sendMessage(msg, "Brillo Bajado "+(String)brillo+"%");
      }
      else if (msgText.equals("/fin")) {       
        myBot.sendMessage(msg, "Gracias por ver el Video!");
        executeCommand(FIN);
      }
  }
    if(autoLightControlEnabled){
      int readSensor = analogRead(11);
      if ((readSensor > MIN_LIGHT_VALUE) && (lightCheck != LIGHT_IS_OFF)) {
          myBot.sendMessage(msg, "LUZ APAGADA");       // notify the sender in Telegram
          executeCommand(LIGHT_OFF);
          lightCheck = LIGHT_IS_OFF; 
      }else if ((readSensor < MIN_LIGHT_VALUE) && (lightCheck != LIGHT_IS_ON)){
          myBot.sendMessage(msg, "LUZ ENCENDIDA");     // notify the sender in Telegram
          executeCommand(LIGHT_ON);
          lightCheck = LIGHT_IS_ON;    
      } 
    }
}


  /*
    Funciones para graficar en la pantalla
  */

unsigned long testFillScreen()
{
  unsigned long start = micros();
  tft.fillScreen(ST7789_BLACK);
  yield();
  tft.fillScreen(ST7789_RED);
  yield();
  tft.fillScreen(ST7789_GREEN);
  yield();
  tft.fillScreen(ST7789_BLUE);
  yield();
  tft.fillScreen(ST7789_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText()
{
  tft.fillScreen(ST7789_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ST7789_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7789_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ST7789_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ST7789_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("Add text");
  tft.setTextSize(1);
  tft.println("Add text");
  tft.println("");
  tft.println("Add text");
  tft.println("Add text");
  tft.println("Add text");
  tft.println("Add text");
  tft.println("Add text");
  return micros() - start;
}

unsigned long testLines(uint16_t color)
{
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ST7789_BLACK);
  yield();

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(ST7789_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ST7789_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(ST7789_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2)
{
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ST7789_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color)
{
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ST7789_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2)
{
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ST7789_BLACK);
  n = min(tft.width(), tft.height());
  for (i = n; i > 0; i -= 6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color)
{
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ST7789_BLACK);
  start = micros();
  for (x = radius; x < w; x += r2) {
    for (y = radius; y < h; y += r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color)
{
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = tft.width()  + radius,
                      h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for (x = 0; x < w; x += r2) {
    for (y = 0; y < h; y += r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles()
{
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ST7789_BLACK);
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles()
{
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ST7789_BLACK);
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(0, i * 10, i * 10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(i * 10, i * 10, 0));
    yield();
  }

  return t;
}

unsigned long testRoundRects()
{
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ST7789_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for (i = 0; i < w; i += 6) {
    i2 = i / 2;
    tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects()
{
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ST7789_BLACK);
  start = micros();
  for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
    i2 = i / 2;
    tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}
