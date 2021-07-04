# esp8266_table_atmosphere_light
# 基于ESP8266开发的桌下氛围灯 （ws2812b灯带） 断电后会保存当前设置状态 （配合智能插座使用）
# 视频：https://www.bilibili.com/video/BV1Zg411M7rR/
## 环境
* Arduino 
* wifi_link_tool (https://github.com/bilibilifmk/wifi_link_tool)
* FastLED (https://github.com/FastLED/FastLED)

## 配置
* #define NUM_LEDS xx //设置灯珠数量
* Hostname = "桌下灯"; //配置设备名称
## 接线
重置   
D3 ---------/ --------gnd  
2812b灯带  
D1 -------------------input  
vcc-------------------vin  
g  -------------------gnd  
## API
您可以使用API接口进行更自由的控制  你可以使用自动化脚本之类的软件达到电脑开机对灯光的控制及关闭（安卓不支持mdns 需要替换成IP）  
* 亮度控制 http://桌下灯/l?l=xx   (xx的范围为0-255 0即为关闭)
* 颜色自定义 http://桌下灯/rgb?r=x&g=x&b=x （x的的范围0-255 编码为rgb 例如白色r=255 g=255 b=255 ）
