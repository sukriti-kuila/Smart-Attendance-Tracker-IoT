#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>  
// Download the library --> https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <LiquidCrystal_I2C.h> //SDA -> GP4 and SCL -> GP5
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

const char* ssid = "SOA UNIVERSITY";      
const char* password = "password";

const char* NAME;
const char* ID;

WiFiServer server(80);
void setup()
{
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  lcd.begin();    
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("  ATTENDANCE ");
  lcd.setCursor(0, 1);
  lcd.print("    SYSTEM");
  Serial.begin(9600);
  while (!Serial);  
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  lcd.clear();
  server.begin();
}

void loop()                     
{
  lcd.setCursor(0, 0);
  lcd.print("No Finger !!");
  getFingerprintID();
  delay(50);            
  if (finger.fingerID == 1) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Student a         ";
    ID = "1";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(NAME);
      lcd.setCursor(0, 1);
      lcd.print(ID);
      delay(3000);
      lcd.clear();
    }
  }
  if (finger.fingerID == 2) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Student b      ";
    ID = "2";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(NAME);
      lcd.setCursor(0, 1);
      lcd.print(ID);
      delay(3000);
      lcd.clear();
      // digital write - open the door
    }

  }
  if (finger.fingerID == 3) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Student c           ";
    ID = "3               ";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print(NAME);
      lcd.setCursor(0, 1);
      lcd.print(ID);
      delay(3000);
      lcd.clear();
    }
  }

  if (finger.fingerID == 4) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Student d       ";
    ID = "4                 ";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
    }
  }
  else{
    digitalWrite(12,LOW);
    digitalWrite(14,LOW);
  }
  finger.fingerID = 0;
  WiFiClient client = server.available();
  if (client) {
      Serial.println("New client connected");
  
      String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
      response += "<!DOCTYPE html><html><body>";
      response += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
      response += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
      response += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
      response += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
      response += "</style>\n";
      response += "</head>\n";
      response += "<body>\n";
    
      response += "<h1>Attendance History</h1>";
      response += "<table border=\"1\">";
      response += "<thead><tr><th>Name</th><th>Roll</th><th>Time</th></tr></thead>";
      response += "<tbody><tr>";
      response += "<td id=\"StudentName\"></td>";
      response += "<td id=\"StudentRollNo\"></td>";
      response += "<td id=\"show_time\"></td>";
      response += "</tr></tbody></table>";
      response += "<script>document.getElementById(\"StudentName\").innerHTML = '" + String(NAME) + "';</script>";
      response += "<script>document.getElementById(\"StudentRollNo\").innerHTML = '" + String(ID) + "';</script>";
      response += "<script>document.getElementById(\"show_time\").innerHTML = new Date().toLocaleTimeString();</script>";
      response += "</body></html>";


      response += "</body></html>";


      Serial.println(response);
  
      client.print(response);
      client.stop();
      Serial.println("Client disconnected");
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_BLUE);
      finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_RED);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 25, FINGERPRINT_LED_PURPLE, 10);
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 25, FINGERPRINT_LED_RED, 10);
    delay(1000);
    Serial.println("Did not find a match");
    digitalWrite(14,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Did not find");
    lcd.setCursor(0, 1);
    lcd.print("Finger");
    delay(3000);
    lcd.clear();
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
