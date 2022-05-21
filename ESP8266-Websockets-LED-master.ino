/*
Sketch developed 11/30/2018 Wirekraken
*/
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>
#include <FastLED.h>

const char* ssid = ""; // Wifi Name
const char* password = ""; // Wifi password

IPAddress Ip(192,168,0,17); // IP-address for ESP
IPAddress Gateway(192,168,0,1); // IP-address for Gateway
IPAddress Subnet(255,255,255,0); // Subnet Mask
 
#define LED_COUNT 30 // Number of led pixel
#define LED_DT 5     // Pin where led tap is connected - D1

uint8_t bright = 25; // bright value (0 - 255)
uint8_t ledMode = 0; // led effects flag (0 - 29)

uint8_t flag = 1; // effect cancellation flag

CRGBArray<LED_COUNT> leds;

uint8_t delayValue = 20; // dalay value
uint8_t stepValue = 10;  // pixel pitch
uint8_t hueValue = 0;    // tone value

// Grove Button Setup
const int buttonPin = 4; // D2    // the number of the pushbutton pin, D4
const int buttonLed = 0; // D3    // LED within the button. D2

// Initialize websocket on port 81
WebSocketsServer webSocket(81);
ESP8266WebServer server(80);

void loop()
{
  int button_flag = digitalRead(buttonPin);

  if(button_flag == LOW)
  {
    digitalWrite(buttonLed, HIGH);
    
    ledMode += 1;
    if(ledMode > 29)
    {
      ledMode = 0;
    }
    
    ledEffect(ledMode);
    delay(500);
    digitalWrite(buttonLed, LOW);
    delay(500);
  }
  else
  {
    // Handle incoming HTTP or WebSockets requests
    webSocket.loop();
    server.handleClient();

    // Turn the Led with "ledMode" value
    ledEffect(ledMode);
  } 
}

// LED effects function
void ledEffect(int ledMode){ 
    switch(ledMode){
      case 0: updateColor(0,0,0); break;
      case 1: rainbow_fade(); delayValue = 20; break;       
      case 2: rainbow_loop(); delayValue = 20; break;
      case 3: new_rainbow_loop(); delayValue = 5; break;
      case 4: random_march(); delayValue = 40; break;  
      case 5: rgb_propeller(); delayValue = 25; break;
      case 6: rotatingRedBlue(); delayValue = 40; hueValue = 0; break;
      case 7: Fire(55, 120, delayValue); delayValue = 15; break; 
      case 8: blueFire(55, 250, delayValue); delayValue = 15; break;  
      case 9: random_burst(); delayValue = 20; break;
      case 10: flicker(); delayValue = 20; break;
      case 11: random_color_pop(); delayValue = 35; break;                                      
      case 12: Sparkle(255, 255, 255, delayValue); delayValue = 0; break;                   
      case 13: color_bounce(); delayValue = 20; hueValue = 0; break;
      case 14: color_bounceFADE(); delayValue = 40; hueValue = 0; break;
      case 15: red_blue_bounce(); delayValue = 40; hueValue = 0; break;
      case 16: rainbow_vertical(); delayValue = 50; stepValue = 15; break;
      case 17: matrix(); delayValue = 50; hueValue = 95; break; 
  
      // heavy effects
      case 18: rwb_march(); delayValue = 80; break;                         
      case 19: flame(); break;
      case 20: theaterChase(255, 0, 0, delayValue); delayValue = 50; break;
      case 21: Strobe(255, 255, 255, 10, delayValue, 1000); delayValue = 100; break;
      case 22: policeBlinker(); delayValue = 25; break;
      case 23: kitt(); delayValue = 100; break;
      case 24: rule30(); delayValue = 100; break;
      case 25: fade_vertical(); delayValue = 60; hueValue = 180; break;
      case 26: fadeToCenter(); break;
      case 27: runnerChameleon(); break;
      case 28: blende(); break;
      case 29: blende_2();
    }
}
