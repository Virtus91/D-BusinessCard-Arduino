
#include <Firebase_Arduino_WiFiNINA.h>
#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"
#include "MemoryFree.h"
#include "credentials.h"


#define COLORED     0
#define UNCOLORED   1



FirebaseData firebaseData;

int counter;
char text_line1[41];
char text_line2[41];
char text_line3[41];
char text_line4[41];
char text_line5[41];

const char FIREBASE_HOST[] = S_FIREBASE_HOST;
const char FIREBASE_AUTH[] = S_FIREBASE_AUTH;
const char WIFI_SSID[] = S_WIFI_SSID;
const char WIFI_PASSWORD[] = S_WIFI_PASSWORD;


void setup() {

  unsigned char image[1024];
  Paint paint(image, 0, 0);    // width should be the multiple of 8 
  Epd epd;

  Serial.begin(115200);
  delay(100);
  if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(23);
  paint.SetHeight(296);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(6, 2, "Connecting to Wi-Fi", &Font20, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 58, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  if (Firebase.getInt(firebaseData, "/counter")) {
      counter = firebaseData.intData();
  } else {
    Serial.println(firebaseData.errorReason());
  }

  String background_color;
  int font_line1;
  int font_line2;
  int font_line3;
  int font_line4;
  int font_line5;
  
  Firebase.getString(firebaseData, "/background_color");
  background_color = firebaseData.stringData();
 
  Firebase.getInt(firebaseData, "/font_line1");
  font_line1 = firebaseData.intData();

  Firebase.getInt(firebaseData, "/font_line2");
  font_line2 = firebaseData.intData();;

  Firebase.getInt(firebaseData, "/font_line3");
  font_line3 = firebaseData.intData();

  Firebase.getInt(firebaseData, "/font_line4");
  font_line4 = firebaseData.intData();

  Firebase.getInt(firebaseData, "/font_line5");
  font_line5 = firebaseData.intData();



  Firebase.getString(firebaseData, "/text_line1");
  strcpy(text_line1, firebaseData.stringData().c_str());
 

  Firebase.getString(firebaseData, "/text_line2");
  strcpy(text_line2, firebaseData.stringData().c_str());

  Firebase.getString(firebaseData, "/text_line3");
  strcpy(text_line3, firebaseData.stringData().c_str());

  Firebase.getString(firebaseData, "/text_line4");
  strcpy(text_line4, firebaseData.stringData().c_str());

  Firebase.getString(firebaseData, "/text_line5");
  strcpy(text_line5, firebaseData.stringData().c_str());

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  paint.Clear(backgroundcolor(background_color,1));
  epd.SetFrameMemory(paint.GetImage(), 104, 0, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(backgroundcolor(background_color,1));
  paint.DrawStringAt(6, 2, text_line1, font(font_line1), backgroundcolor(background_color,2));
  epd.SetFrameMemory(paint.GetImage(), 102, 0, paint.GetWidth(), paint.GetHeight());

  paint.Clear(backgroundcolor(background_color,1));
  paint.DrawStringAt(6, 2, text_line2, font(font_line2), backgroundcolor(background_color,2));
  epd.SetFrameMemory(paint.GetImage(), 78, 0, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(backgroundcolor(background_color,1));
  paint.DrawStringAt(6, 2, text_line3, font(font_line3), backgroundcolor(background_color,2));
  epd.SetFrameMemory(paint.GetImage(), 54, 0, paint.GetWidth(), paint.GetHeight());

  paint.Clear(backgroundcolor(background_color,1));
  paint.DrawStringAt(6, 2, text_line4, font(font_line4), backgroundcolor(background_color,2));
  epd.SetFrameMemory(paint.GetImage(), 30, 0, paint.GetWidth(), paint.GetHeight());

  paint.Clear(backgroundcolor(background_color,1));
  paint.DrawStringAt(6, 2, text_line5, font(font_line5), backgroundcolor(background_color,2));
  epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();
}
  

void loop() {
  Firebase.getInt(firebaseData, "/counter");
  if (counter != firebaseData.intData())
    {
    counter = firebaseData.intData();

    String background_color;
    int font_line1;
    int font_line2;
    int font_line3;
    int font_line4;
    int font_line5;
    unsigned char image[1024];
    Paint paint(image, 0, 0); 
    Epd epd;

    
    Firebase.getString(firebaseData, "/background_color");
    background_color = firebaseData.stringData();
 
 
    Firebase.getInt(firebaseData, "/font_line1");
    font_line1 = firebaseData.intData();

    Firebase.getInt(firebaseData, "/font_line2");
    font_line2 = firebaseData.intData();;

    Firebase.getInt(firebaseData, "/font_line3");
    font_line3 = firebaseData.intData();

    Firebase.getInt(firebaseData, "/font_line4");
    font_line4 = firebaseData.intData();

    Firebase.getInt(firebaseData, "/font_line5");
    font_line5 = firebaseData.intData();

    Firebase.getString(firebaseData, "/text_line1");
    strcpy(text_line1, firebaseData.stringData().c_str());

    Firebase.getString(firebaseData, "/text_line2");
    strcpy(text_line2, firebaseData.stringData().c_str());

    Firebase.getString(firebaseData, "/text_line3");
    strcpy(text_line3, firebaseData.stringData().c_str());

    Firebase.getString(firebaseData, "/text_line4");
    strcpy(text_line4, firebaseData.stringData().c_str());

    Firebase.getString(firebaseData, "/text_line5");
    strcpy(text_line5, firebaseData.stringData().c_str());


    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    paint.SetRotate(ROTATE_90);
    paint.SetWidth(23);
    paint.SetHeight(296);
  
    paint.Clear(backgroundcolor(background_color,1));
    epd.SetFrameMemory(paint.GetImage(), 104, 0, paint.GetWidth(), paint.GetHeight());
  
    paint.Clear(backgroundcolor(background_color,1));
    paint.DrawStringAt(6, 2, text_line1, font(font_line1), backgroundcolor(background_color,2));
    epd.SetFrameMemory(paint.GetImage(), 102, 0, paint.GetWidth(), paint.GetHeight());

    paint.Clear(backgroundcolor(background_color,1));
    paint.DrawStringAt(6, 2, text_line2, font(font_line2), backgroundcolor(background_color,2));
    epd.SetFrameMemory(paint.GetImage(), 78, 0, paint.GetWidth(), paint.GetHeight());
  
    paint.Clear(backgroundcolor(background_color,1));
    paint.DrawStringAt(6, 2, text_line3, font(font_line3), backgroundcolor(background_color,2));
    epd.SetFrameMemory(paint.GetImage(), 54, 0, paint.GetWidth(), paint.GetHeight());

    paint.Clear(backgroundcolor(background_color,1));
    paint.DrawStringAt(6, 2, text_line4, font(font_line4), backgroundcolor(background_color,2));
    epd.SetFrameMemory(paint.GetImage(), 30, 0, paint.GetWidth(), paint.GetHeight());

    paint.Clear(backgroundcolor(background_color,1));
    paint.DrawStringAt(6, 2, text_line5, font(font_line5), backgroundcolor(background_color,2));
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());

    Serial.println(freeMemory());
    epd.DisplayFrame();
    }
  delay(2000);
}

sFONT * font(int f){
  switch(f) {
    case 12:
      return &Font12;
      break;
    case 16:
      return &Font16;
      break;
    case 20:
      return &Font20;
      break;
    case 24:
      return &Font24;
      break;
  }
}

int backgroundcolor(String bc, int b){
  if (bc == "light" && b == 1)
    return 1;
  if (bc == "light" && b == 2)
    return 0;
  if (bc == "dark" && b == 1)
     return 0;
  if (bc == "dark" && b == 2)
    return 1;
}
