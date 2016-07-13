#include <SoftwareSerial.h>

// WARNING, WARNING ... DANGER, WILL ROBINSON, DANGER!!!
// The station ID letter is unique to each Arduino Module and must be manually entered.
// Double and triple check this value is what you intend it to be.
const char ArduinoID[] = "a"; // Station ID letter - Must to match ID printed on the housing.

//////////////////////// Wireless network information //////////////////////////////////

const char SSID[] = "Tufts_Wireless";
int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int button5 = 6;
int button6 = 7;

int cnxtLed = 10;
int startLed = 11;
int sendLed = 12;

// PW = Empty string since network is not password protected. This particular network is 
// mac address registry based. We are not registering the mac addresses of these so
// they are limited to accessing internal IPs or websites hosted by Tufts. 
const char PSK[] = ""; 
// Static IP of the directory location
const char DBIP[] = "130.64.159.200";

/////////////////////////////////// Hardware assignments /////////////////////////////

SoftwareSerial ESP8266(8, 9); // D8 -> ESP8266 RX, D9 -> ESP8266 TX

#define reset_delay 1000

void setup() {
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);
    pinMode(button5, INPUT);
    pinMode(button6, INPUT);
    
    pinMode(cnxtLed, OUTPUT);
    pinMode(startLed, OUTPUT);
    pinMode(sendLed, OUTPUT);

    digitalWrite(cnxtLed, HIGH);
    digitalWrite(startLed, HIGH);
    digitalWrite(sendLed, HIGH);
    
    // Initialize Serial Communications
    Serial.begin(9600);   // with the PC for debugging displays
    ESP8266.begin(9600);

    while(!ESP8266_Check()){ delay(reset_delay); }
    Serial.println(F("esp8266 checked!"));

    while( !ESP8266_Mode(3) ){ delay(reset_delay); }
    Serial.println(F("esp8266 set to mode 3!"));

    while( !connectWiFi() ){ delay(reset_delay); }
    Serial.println(F("esp8266 successfully connected to wifi!"));  
}


void loop() {
    delay(100);
    String id = "";
    bool pressed = false;
    if (digitalRead(button1) == HIGH) {
      id = ArduinoID;
      id += "1";
      pressed = true;
    }
    else if (digitalRead(button2) == HIGH) {
      id = ArduinoID;
      id += "2";
      pressed = true;
    }
    else if (digitalRead(button3) == HIGH) {
      id = ArduinoID;
      id += "3";
      pressed = true;
    }
    else if (digitalRead(button4) == HIGH) {
      id = ArduinoID;
      id += "4";
      pressed = true;
    }
    else if (digitalRead(button5) == HIGH) {
      id = ArduinoID;
      id += "5";
      pressed = true;
    }
    else if (digitalRead(button6) == HIGH) {
      id = ArduinoID;
      id += "6";
      pressed = true;
    }
    if (pressed) {
        //for debugging: wait for serial commands while looping
        while(ESP8266.available()) Serial.write(ESP8266.read());
        //while(Serial.available()) ESP8266.write(Serial.read());
        String resp = ReqJMN( id);
        Serial.println(resp);
        delay(3000);
    }
}

////////////////////////////////////////////////////////////////////////
/////////////////////// WIFI / DATABASE UTILITIES //////////////////////
////////////////////////////////////////////////////////////////////////

String ReqJMN(String id1)
{
    String resp="";
    char z;
    Serial.println(F("Starting request..."));

    String httpReq = "GET /handler.php?id=";
    httpReq += id1; // local input
    httpReq += " HTTP/1.0\r\n\r\n";
    delay(50);
    Serial.println(httpReq);
    //  Send AT command to ESP8266
    // Start connection - 
    Serial.println(F("CIPStart..."));
    Serial.print(F("AT+CIPSTART=\"TCP\",\""));
    Serial.print(DBIP);
    Serial.print(F("\",80\r\n"));

    ESP8266.print(F("AT+CIPSTART=\"TCP\",\""));
    ESP8266.print(DBIP);
    ESP8266.print(F("\",80\r\n"));

    delay(100);
    if(ESP8266.find("OK")) {
      Serial.println(F("CIPSTART: OK"));
      retCode(startLed, "OK");
    }
    
    else if(ESP8266.find("ERROR")) {
      Serial.println(F("CIPSTART: Error"));
      retCode(startLed, "ERROR");
      return "Error";
    }

    else {
      Serial.println(F("CIPSTART: No Response"));
      retCode(startLed, "NO RESPONSE");
      return "Error";
    }

    // Send request - 
    Serial.println(F("CIPSEND..."));
    Serial.print(F("AT+CIPSEND=")); 
    Serial.print(httpReq.length());
    Serial.print(F("\r\n"));

    ESP8266.print("AT+CIPSEND="); 
    ESP8266.print(httpReq.length()); // Specifies how much data is being sent
    ESP8266.print("\r\n");
    // while(ESP8266.available()) Serial.write(ESP8266.read());
    delay(500);

    if(ESP8266.find("OK")) {
      Serial.println(F("Sent Request - "));
      Serial.print(httpReq);
      ESP8266.print(httpReq); // Send HTTP request
    }
    else {
      Serial.println(F("No request sent. Try again."));
    }

    int j = 0;
    while(!ESP8266.find("OK")) {
      delay(100);
      j++;
      Serial.print(j);
      if (j>50) {
        Serial.println(F("Error - could not find response"));
        retCode(sendLed, "NO RESPONSE");
        return F("Error - could not find response");
      }
    }

    Serial.println(F("Found Success:..."));
    retCode(sendLed, "OK");
    for (int i = 0; i<=18; i++) {
      while(!ESP8266.available());
      z = (char)ESP8266.read();
      Serial.write(z);
      resp.concat(z);
    }

    Serial.println(F("<-- END"));
    return resp;
}

boolean ESP8266_Check()
{ 
    ESP8266.println(F("AT"));
    delay(200);
    if(ESP8266.find("OK")) {
      Serial.flush();
      return true;
    }
    
    else if(ESP8266.find("ERROR")) {
      Serial.println(F("RECEIVED: Error"));
      Serial.println(F("Trying again.."));
      return false;
    }
    else {
      Serial.println(F("RECEIVED: No Response"));
      Serial.println(F("Trying again.."));
      return false;
    }
}

boolean ESP8266_Mode(int mode)
{
    ESP8266.println(F("AT+CWMODE?"));
    if(ESP8266.find(mode)) {
      Serial.print(F("Mode already set"));
      return true;
    }

    ESP8266.print(F("AT+CWMODE="));
    ESP8266.println(mode);
    
    if(ESP8266.find("OK")) {
      Serial.println(F("RECEIVED: OK"));
      return true;
    }
    else if(ESP8266.find("ERROR")) {
      Serial.println(F("RECEIVED: Error"));
      Serial.println(F("Trying again.."));
      return false;
    }
    else {
      Serial.println(F("RECEIVED: No Response"));
      Serial.println(F("Trying again.."));
      return false;
    }
    delay(100);
}


boolean connectWiFi()
{
    ESP8266.println(F("AT+CWJAP?"));
    delay(250);
    if(ESP8266.find("tuftswireless")) 
    {
        Serial.flush();
        while(ESP8266.available()) Serial.write(ESP8266.read());
        Serial.print(F("\n"));  
        // Serial.println(F("Already connected"));
        return true;
    }
    delay(100);
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PSK;
    cmd+="\"";
    ESP8266.println(cmd);
    Serial.println(cmd);
    delay(500);
    while ( !ESP8266.available() ){
        delay(100);
    }

    if(ESP8266.find("OK")) {
        Serial.println(F("RECEIVED: OK"));
        retCode(cnxtLed, "OK");
        ESP8266.flush();
        return true;
    }

    else if(ESP8266.find("ERROR")) {
        Serial.println(F("RECEIVED: Error"));
        retCode(cnxtLed, "ERROR");
        return false;
    }

    else {
        Serial.println(F("RECEIVED: Couldn't connect to wifi; no response"));
        retCode(cnxtLed, "NO RESPONSE");
        return false;
    }
}

void retCode(int LEDname, String response)
{
  if (response == "OK") {
      digitalWrite(LEDname, HIGH);
  }
  else if (response == "ERROR") {
      digitalWrite(LEDname, LOW);
      delay(100);
      digitalWrite(LEDname, HIGH);
      delay(100);
      digitalWrite(LEDname, LOW);
      delay(100);
      digitalWrite(LEDname, HIGH);
      delay(100);
      digitalWrite(LEDname, LOW);
      delay(100);
      digitalWrite(LEDname, HIGH);
      delay(100);
      digitalWrite(LEDname, LOW);
  }
  else if (response == "NO RESPONSE"){
      digitalWrite(LEDname, LOW);
  }
}
