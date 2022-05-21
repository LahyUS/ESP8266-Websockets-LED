void setup()
{
  Serial.begin(9600); 
  LEDS.setBrightness(bright);

  // Button setup
  pinMode(buttonPin, INPUT);
  pinMode(buttonLed, OUTPUT);
  digitalWrite(buttonLed, LOW);

  // Initialize LED tape
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  
  updateColor(0,0,0);
  LEDS.show(); 

  // Network setup
  WiFi.config(Ip, Gateway, Subnet);
  WiFi.begin(ssid, password);
  Serial.println("Wifi Connecting...");

  // Connection checking
  while (WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }

  // Show IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Handle webserver data not found
  server.onNotFound([]()
  {
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  // Activate server
  server.begin();
  SPIFFS.begin();

  // Activate websocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
