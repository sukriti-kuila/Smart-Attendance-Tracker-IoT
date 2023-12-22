#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> //SDA -> GP4 and SCL -> GP5
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

const char* ssid = "M2 Pro (Poco)";      
const char* password = "pqrstuv123";

const char* NAME;
const char* ID;
char* val;
WiFiServer server(80);
void setup()
{
  val = "0";
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
    lcd.setCursor(0, 0);
    lcd.print("  Connecting to ");
    lcd.setCursor(0, 1);
    lcd.print("    WiFi    ");
    Serial.println("Connecting to WiFi...");
  }
  lcd.setCursor(0, 0);
  lcd.print("  Connected to ");
  lcd.setCursor(0, 1);
  lcd.print("    WiFi    ");
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
  lcd.print("  PLACE FINGER");
  getFingerprintID();
  delay(50);           
  if (finger.fingerID == 1) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "STUDENT A         ";
    ID = "1";
    if (finger.confidence >= 60) {
      val = "1";
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("     WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }
  }
  if (finger.fingerID == 2) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "STUDENT B      ";
    ID = "2";
    
    if (finger.confidence >= 60) {
      val = "1";
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("     WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }

  }
  if (finger.fingerID == 3) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "STUDENT C           ";
    ID = "3               ";
    if (finger.confidence >= 60) {
      val = "1";
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("     WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }
  }

  if (finger.fingerID == 4) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "STUDENT D       ";
    ID = "4                 ";
    if (finger.confidence >= 60) {
       val = "1";
       Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("     WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }
  }

  if (finger.fingerID == 5) {
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "STUDENT E           ";
    ID = "5               ";
    if (finger.confidence >= 60) {
      val = "1";
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      digitalWrite(12,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("     WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }
  }
  else{
    val = "0";
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
    
        // CSS 
        response += "<style>";
        response += "body { background-color: #323150; }";
        response += ".title-header { color: #FFC60B; text-align: center; margin-left: 32px;";
        response += "font-family: 'Trebuchet MS', sans-serif; }";
        response += ".container { margin: 25px 50px 75px 400px; }";
        response += ".content-table { border-collapse: collapse; margin: 25px 0; font-size: 0.9em;";
        response += "min-width: 400px; border-radius: 5px 5px 0 0; overflow: hidden;";
        response += "box-shadow: 0 5px 5px black; }";
        response += ".content-table thead tr { background-color: #009879; color: #ffffff;";
        response += "text-align: left; font-weight: bold; }";
        response += ".content-table th, .content-table td { padding: 12px 15px; text-align: center;";
        response += "font-family: 'Verdana'; }";
        response += ".content-table tbody tr { border-bottom: 1px solid #dddddd; }";
        response += ".content-table tbody tr:nth-of-type(even) { background-color: #f3f3f3; }";
        response += ".content-table tbody tr:last-of-type { border-bottom: 2px solid #009879; }";
        response += ".content-table tbody tr.active-row { font-weight: bold; color: #009879; }";
        response += ".even-row { background-color: #F8F6FF; }";
        response += "</style></head><body>";

    
        response += "</head>\n";
        response += "<body>\n";
        response += "<div class=\"title-header\">";
        response += "<h1>Attendance History</h1>";
        response += "</div>";
        response += "<div class=\"container\">";
        response += "<table class=\"content-table\">";
        response += "<thead class=\"header-row\"><tr><th>Student Name</th><th>Roll Number</th><th>Time</th><th>Date</th></tr></thead>";
        response += "<tbody id=\"studentTableBody\">";
        response += "</tbody></table></div>";

        //JavaScript
        response += "<script>";
        response += "var storedData = JSON.parse(localStorage.getItem('StudentData')) || [];";
        
        response += "var currentTime = new Date();";
        response += "const options = { year: 'numeric', month: 'short', day: 'numeric' };";
        response += "var date = currentTime.toLocaleDateString('en-IN', options);";

//        response += "if (" + String(val) + " == 1 && " + String(finger.confidence) + " >= 60) {";
        
        response += "  var newStudent = { name: '" + String(NAME) + "', id: '" + String(ID) + "', time: new Date().toLocaleTimeString(), date: date };";
        response += "  storedData.push(newStudent);";
        response += "  localStorage.setItem('StudentData', JSON.stringify(storedData));";
        
//        response += "}";
        
        response += "var tableBody = document.getElementById('studentTableBody');";
        response += "tableBody.innerHTML = '';";
    
        response += "storedData.forEach(function(student, index) {";
        response += "var row = tableBody.insertRow();";
        response += "var nameCell = row.insertCell(0);";
        response += "var idCell = row.insertCell(1);";
        response += "var timeCell = row.insertCell(2);";
        response += "var dateCell = row.insertCell(3);";
    
        response += "nameCell.textContent = student.name;";
        response += "idCell.textContent = student.id;";
        response += "timeCell.textContent = student.time;";
        response += "dateCell.textContent = student.date;";
        response += "row.className = index % 2 === 0 ? 'even-row' : 'odd-row';";
        
        response += "val = '0';"; 
        response += "});";
        
        response += "</script>";
        response += "</body></html>";
        

        Serial.println(String(ID));
        Serial.println(finger.confidence);
    
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
    lcd.print("AUTHENTICATION");
    lcd.setCursor(0, 1);
    lcd.print("    FAILED");
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
