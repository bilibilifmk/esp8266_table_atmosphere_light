/*
项目地址：https://github.com/bilibilifmk/esp8266_table_atmosphere_light
# esp8266_table_atmosphere_light

# 基于ESP8266开发的桌下氛围灯 （ws2812b灯带）
重置 D3---------/ --------gnd
2812b灯带
D1-------------------input
vcc-------------------vin
g-------------------gnd
*/

#define FS_CONFIG
//激活文件系统模式配网
#include <wifi_link_tool.h>
#include <FastLED.h>
#define DATA_PIN 1 //设置io 示开发而定 nodemcu D1 =1 ESP8266 GPIO 16=16

#define NUM_LEDS 60//设置灯珠数量

CRGB leds[NUM_LEDS];

int eeproml, eepromr, eepromg, eepromb;

void setup() {
  EEPROM.begin(4096);
  initled();//初始化 及灯条自检 加载EEPROM数据


  Serial.begin(115200);
  //开启串口
  /////////////////////////////////////////////////////////基础设置//////////////////////////////////////////////////////////
  rstb = 0;
  //重置io
  stateled = 2;
  //指示灯io
  Hostname = "桌下灯";
  //设备名称 允许中文名称 不建议太长
  wxscan = true;
  //是否被小程序发现设备 开启意味该设备具有后台 true开启 false关闭
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //此处请勿添加代码
  load();
  webServer.on("/favicon.ico", favicon);
  webServer.on("/js/knockout-min.js", knockout);
  webServer.on("/js/clipboard.min.js", clipboard);
  webServer.on("/rgb", rgbs);
  webServer.on("/l", ls);





}

void favicon() {

  File file = SPIFFS.open("/favicon.ico", "r");
  webServer.streamFile(file, "image/vnd.microsoft.icon");
  file.close();
}

void knockout() {

  File file = SPIFFS.open("/knockout-min.js", "r");
  webServer.streamFile(file, "application/javascript");
  file.close();

}

void clipboard() {

  File file = SPIFFS.open("/clipboard.min.js", "r");
  webServer.streamFile(file, "application/javascript");
  file.close();

}
void rgbs() {
  if (webServer.arg("r") != "" && webServer.arg("g") != ""&webServer.arg("b") != "" && webServer.arg("r") != "undefined" && webServer.arg("g") != "undefined" && webServer.arg("b") != "undefined")
  {
    //    Serial.println(webServer.arg("r"));
    //    Serial.println(webServer.arg("g"));
    //    Serial.println(webServer.arg("b"));
    eepromr = webServer.arg("r").toInt();
    eepromg = webServer.arg("g").toInt();
    eepromb = webServer.arg("b").toInt();
    ledcolor(eepromr, eepromg, eepromb);
    EEPROM.put(400, eepromr);
    EEPROM.put(500, eepromg);
    EEPROM.put(600, eepromb);
    EEPROM.commit();
    delay(10);

  }
  webServer.send(200, "text/plain", "ojbk");
}
void ls() {

  if (webServer.arg("l") != "")
  {
    FastLED.setBrightness(webServer.arg("l").toInt());
    FastLED.show();
    eeproml = webServer.arg("l").toInt();
    EEPROM.put(300, eeproml);
    EEPROM.commit();
    delay(10);
  }
  webServer.send(200, "text/plain", "ojbk");
}

void initled()
{
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(100);
  //灯光自检
  for (int a = 0; a < NUM_LEDS; a++)
  {
    leds[a] = CRGB(255, 255, 255);
    FastLED.show();
    delay(10);
    leds[a] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
  }
  for (int a = NUM_LEDS; a >= 0; a--)
  {
    leds[a] = CRGB(255, 255, 255);
    FastLED.show();
    delay(10);
    leds[a] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
  }
  //加载EEPROM
  EEPROM.get(300, eeproml);
  EEPROM.get(400, eepromr);
  EEPROM.get(500, eepromg);
  EEPROM.get(600, eepromb);
  delay(10);
  FastLED.setBrightness(eeproml);
  // Serial.println(eeproml);
  // leds[0] = CRGB(eepromg, eepromr, eepromb);
  // FastLED.show();
  ledcolor(eepromr, eepromg, eepromb);


}
void ledcolor(int r, int g, int b)
{
  for (int a = 0; a < NUM_LEDS; a++)
  {
    leds[a] = CRGB(g, r, b);
    FastLED.show();
    delay(5);
  }
}

void loop() {
  //请勿此处添加代码
  pant();
  //WiFi link tool 服务维持函数  请勿修改位置
  //请在下面添加自己的代码
}
