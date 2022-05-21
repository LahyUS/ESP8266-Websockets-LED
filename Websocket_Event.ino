// Fuction: for processing incoming messages
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
   if(type == WStype_CONNECTED)
   {
      IPAddress ip = webSocket.remoteIP(num);

      String message = String("Connected");
      webSocket.broadcastTXT(message);  // broadcast message to all clients when connecting 
    }
    
    if(type == WStype_TEXT)
    {
        String data;
        for(int x = 0; x < length; x++)
        {
          if(!isdigit(payload[x])) continue;
          data += (char) payload[x];
          
        }
        
        if(payload[0] == 'B')
        {
          flag = 0;
          Serial.print("Bright: ");
          bright = data.toInt();
          Serial.println(data);
          LEDS.setBrightness(bright);

        }  
        else if(payload[0] == 'F')
        {
          flag = 0;
          Serial.print("Function: ");
          ledMode = data.toInt();
          Serial.println(data);
          ledEffect(ledMode);

        }
        else if(payload[0] == '#')
        {
  
          if(!flag)
          {
              Serial.print("flag : ");
              Serial.println(flag);
              ledMode = flag;
              ledEffect(ledMode);
              flag = 1;

          }
          else // Change LED with picked color.
          {
           // Convert to 24 bit color number
           uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);
          
           // Convert 24 bits at 8 bits per channel
           uint8_t r = abs(int(0 + (rgb >> 16) & 0xFF));
           uint8_t g = abs(int(0 + (rgb >>  8) & 0xFF));
           uint8_t b = abs(int(0 + (rgb >>  0) & 0xFF));
           
           Serial.print("ColorPicker: ");
           Serial.print(r);
           Serial.print(g);
           Serial.println(b);
           
           for(int x = 0; x < LED_COUNT; x++)
           {
             leds[x].setRGB(r,g,b);
           }
           LEDS.show();
          }
       }
   } 
}
