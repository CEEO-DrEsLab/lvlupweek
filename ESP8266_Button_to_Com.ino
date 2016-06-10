#include <SoftwareSerial.h>
SoftwareSerial ESP8266(8, 9); // RX, TX
#define rst_pin 11

// Input Buttons for Displays and Exhibits
int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int button5 = 6;

int iterCount = 1; // Counts total number of button presses since last reset
String getReq = ""; // Storage string for GET-request text
String cipStart = ""; // storage string for CIPSTART command 
String cipSend = ""; // storage string for CIPSEND command
String IPADDR = "130.64.95.38"; // "tuftswireless" wifi network IP
//"10.245.201.55"; // "tuftsguest" wifi network IP


// System Setup Fcn
//  Sets up input and reset pins, activates Serial and ESP8266 serial connections
//  and constructs Wifi connection request string
void setup() {
  digitalWrite(rst_pin, HIGH); // hard reset triggers when pin is LOW

  // Pin setups
  pinMode(rst_pin, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  delay(100);

  // Start Serial for user monitering
  Serial.begin(9600); 
  Serial.println("Setup//:Serial start");

  // Start ESP8266 Serial for Arduino-WifiShield Comms, enables AT command usage
  ESP8266.begin(9600); 
  Serial.println("Setup//:ESP8266 start");
  delay(50);
  
  Serial.println("Setup//:testing...");
  delay(100);
  
  ESP8266.print("AT+CIPMODE=0"); // Set Wifi Mode to default (single send mode)
  ESP8266.print("\r\n\r\n");
  Serial.println("Setup//:Mode Set to 0 (normal)");
  
  // GET-request and CIPSTART command string concatenation
  getReq = "GET /handler.php?info=a1 HTTP/1.0";
  cipStart = "AT+CIPSTART=";
    cipStart +="\"TCP\",\"";
    cipStart += IPADDR;
    cipStart +="\",80";
    cipStart +="\r\n\r\n";
   Serial.println("Setup//:cipStart string constructed");
}

// System Loop Fcn
//  Waits for button press. When detected, runs CIPSTART AT command to confirm connection to
//  the server, then sends the appropriate button number code with the CIPSEND AT command.  
void loop() {
  bool pressed = false; // button trigger bool, runs CIPSEND if True
  String bNumCode = ""; // button number storage string

  // Read buttons 1-5, check if pressed.
  if (digitalRead(button1)) {
    pressed = true;
    bNumCode = "a1";
    Serial.println("SysLoop//:Button A1 pressed");
  }
  else if (digitalRead(button2)) {
    pressed = true;
    bNumCode = "a2";
    Serial.println("SysLoop//:Button A2 pressed");
  }
  else if (digitalRead(button3)) {
    pressed = true;
    bNumCode = "a3";
    Serial.println("SysLoop//:Button A3 pressed");
  }
  else if (digitalRead(button4)) {
    pressed = true;
    bNumCode = "a4";
    Serial.println("SysLoop//:Button A4 pressed");
  }
  else if (digitalRead(button5)) {
    pressed = true;
    bNumCode = "a5";
    Serial.println("SysLoop//:Button A5 pressed");
  }

  // If pressed, connect to server with CIPSTART and execute CIPSEND
  if (pressed) {
    cipSend = "AT+CIPSEND=";
      cipSend += String(getReq.length(),DEC);
      cipSend +="\r\n\"GET /handler.php?info=";
      cipSend += bNumCode;
      cipSend += " HTTP/1.0\"\r\n\r\n";

    Serial.print("SysLoop//:starting test# ");
    Serial.println(iterCount);

    // Execute CIPSTART command to connect to server
    ESP8266.print(cipStart);
    waitForReturn("AT+CIPSTART");

    // Execute CIPSEND command to send button code to server
    ESP8266.print(cipSend);
    waitForReturn("AT+CIPSEND");

    Serial.print("SysLoop//:test# ");
    Serial.print(iterCount);
    Serial.print(" complete \r\n\r\n");
  /*
    ESP8266.print("AT+CIPSTATUS?"); // Check Wifi connection status
    ESP8266.print("\r\n");
    waitForReturn("AT+CIPSTATUS?");
    ESP8266.print("AT+CIPCLOSE");
    ESP8266.print("\r\n\r\n");
    waitForReturn("AT+CIPCLOSE");
    
    while(ESP8266.available()) Serial.write(ESP8266.read());
    while(Serial.available()) ESP8266.write(Serial.read());
    */
  iterCount++;
  Serial.flush();
  }
}


// waitForReturn Fcn
// Scans ESP8266 Serial bus for AT Command completion messages.
//  Waits until OK or ERROR Message is found and then prints message
//  to the Serial monitor.
void waitForReturn(String cmdName) {
    Serial.println("waitForReturn//:Function Start");
    Serial.print("waitForReturn//:waiting for command \"");
    Serial.print(cmdName);
    Serial.println("\"");
    bool task_complete = false;
    int failCount = 0;
    while (!task_complete) {
      if (ESP8266.find("OK") or ESP8266.find ("SEND OK")) {
        Serial.print("waitForReturn//:RECEIVED//: OK");
        Serial.flush();
        task_complete = true;
      }
      else if (ESP8266.find("ERROR")) {
        Serial.println("waitForReturn//:RECEIVED//: Error");
        Serial.println("waitForReturn//:Trying again...");
      }
      else {
        Serial.println("waitForReturn//:RECEIVED//: No Response");
        Serial.println("waitForReturn//:Trying again...");
        delay(50);
        if (failCount > 3) {
            Serial.println("waitForReturn//:FAILCOUNT OVERFLOW RESET");
            digitalWrite(rst_pin, LOW);
          }
          failCount++;
      }
    }
    Serial.print("\n");
}

/*
// Ensures that the Arduino is connected to the server, 
//  connects the Arduino to the server via Wifi if it is not currently connected.
void connectTest() {
  ESP8266.print("AT+CIPSTATUS?");
  ESP8266.print("\r\n\r\n");
  waitForReturn("AT+CIPSTATUS");
    if (ESP8266.find("DISCONNECTED")) {
      ESP8266.print("AT+CWJAP?");
      ESP8266.print("\r\n\r\n");
      waitForReturn("AT+CWJAP?");
      if(ESP8266.find(SSID)) {
        ESP8266.print(cipStart)
        waitForReturn("AT+CIPSTART");
      }
      else {
        
        }
      }
    }
    else if (ESP8266.find("CONNECTED") or ESP8266.find("GOT IP")) {
      Serial.print("connectTest//:Connected to Server")    
    
}
*/
