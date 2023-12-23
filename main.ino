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
  pinMode(13,OUTPUT);
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
  {
    lcd.setCursor(0, 0);
    lcd.print("  Connecting to ");
    lcd.setCursor(0, 1);
    lcd.print("    WiFi    ");
    Serial.println("Connecting To    WiFi...");
  }
  lcd.setCursor(0, 0);
  lcd.print("  Connected to ");
  lcd.setCursor(0, 1);
  lcd.print("    WiFi    ");
  Serial.println("Connected to     WiFi...");
  delay(2000);
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
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("    WELCOME     ");
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
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("    WELCOME     ");
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
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("    WELCOME     ");
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
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("    WELCOME     ");
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
      digitalWrite(13,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("    WELCOME     ");
      lcd.setCursor(0, 1);
      lcd.print(String("   ") + NAME);
      delay(3000);
      lcd.clear();
    }
  }
  else{
    val = "0";
    digitalWrite(13,LOW);
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
        response += ".title-header { display: flex; align-items: center; justify-content: center; color: #FFC60B; text-align: center; margin-left: 38px; font-family: 'Trebuchet MS', sans-serif; }";
        response += ".container { margin: 25px 50px 75px 400px; }";
        response += ".content-table { border-collapse: collapse; margin: 25px 0; font-size: 0.9em; min-width: 400px; border-radius: 5px 5px 0 0; overflow: hidden; box-shadow: 0 10px 10px black; }";
        response += ".content-table thead tr { background-color: #009879; color: #ffffff; text-align: left; font-weight: bold; }";
        response += ".content-table th, .content-table td { padding: 12px 15px; text-align: center; font-family: 'Verdana'; }";
        response += ".content-table tbody tr { border-bottom: 1px solid #dddddd; }";
        response += ".content-table tbody tr:nth-of-type(even) { background-color: #f3f3f3; }";
        response += ".content-table tbody tr:last-of-type { border-bottom: 2px solid #009879; }";
        response += ".content-table tbody tr.active-row { font-weight: bold; color: #009879; }";
        response += ".even-row { background-color: #F8F6FF; }";
        response += ".group { display: flex; line-height: 28px; align-items: center; position: relative; max-width: 190px; margin-left: 1100px; }";
        response += ".input { width: 100%; height: 40px; line-height: 28px; padding: 0 1rem; padding-left: 2.5rem; border: 2px solid transparent; border-radius: 8px; outline: none; background-color: #f3f3f4; color: #0d0c22; transition: 0.3s ease; }";
        response += ".input::placeholder { color: #9e9ea7; }";
        response += ".input:focus, input:hover { outline: none; border-color: rgba(247, 127, 0, 0.4); background-color: #fff; box-shadow: 0 0 0 4px rgb(247 127 0 / 10%); }";
        response += ".icon { position: absolute; left: 1rem; fill: #9e9ea7; width: 1rem; height: 1rem; }";
        response += ".button { position: relative; margin-left: 15px; width: 150px; height: 37px; cursor: pointer; display: flex; align-items: center; border: 1px solid #17795E; background-color: #209978; overflow: hidden; border-radius: 7px; }";
        response += ".button, .button__icon, .button__text { transition: all 0.3s; }";
        response += ".button .button__text { transform: translateX(22px); color: #fff; font-weight: 600; }";
        response += ".button .button__icon { position: absolute; transform: translateX(109px); height: 100%; width: 39px; background-color: #17795E; display: flex; align-items: center; justify-content: center; }";
        response += ".button .svg { width: 20px; fill: #fff; }";
        response += ".button:hover { background: #17795E; }";
        response += ".button:hover .button__text { color: transparent; }";
        response += ".button:hover .button__icon { width: 148px; transform: translateX(0); }";
        response += ".button:active .button__icon { background-color: #146c54; }";
        response += ".button:active { border: 1px solid #146c54; }";

        response += "</style></head><body>";

    
        response += "</head>\n";
        response += "<body>\n";

        response += "<div class=\"group\">";
        response += "    <svg viewBox=\"0 0 24 24\" aria-hidden=\"true\" class=\"icon\">";
        response += "        <g>";
        response += "            <path";
        response += "                d=\"M21.53 20.47l-3.66-3.66C19.195 15.24 20 13.214 20 11c0-4.97-4.03-9-9-9s-9 4.03-9 9 4.03 9 9 9c2.215 0 4.24-.804 5.808-2.13l3.66 3.66c.147.146.34.22.53.22s.385-.073.53-.22c.295-.293.295-.767.002-1.06zM3.5 11c0-4.135 3.365-7.5 7.5-7.5s7.5 3.365 7.5 7.5-3.365 7.5-7.5 7.5-7.5-3.365-7.5-7.5z\"";
        response += "            ></path>";
        response += "        </g>";
        response += "    </svg>";
        response += "    <input class=\"input\" type=\"search\" placeholder=\"Search\" id=\"searchInput\" onkeyup=\"myFunction()\"/>";
        response += "</div>";
        
        response += "<div class=\"title-header\">";
        response += "<h1>Attendance History</h1>";
        response += "<button class=\"button\" type=\"button\" onclick=\"exportToCSV()\">";
        response += "    <span class=\"button__text\">Download</span>";
        response += "    <span class=\"button__icon\">";
        response += "        <svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 35 35\" id=\"bdd05811-e15d-428c-bb53-8661459f9307\" data-name=\"Layer 2\" class=\"svg\">";
        response += "            <path d=\"M17.5,22.131a1.249,1.249,0,0,1-1.25-1.25V2.187a1.25,1.25,0,0,1,2.5,0V20.881A1.25,1.25,0,0,1,17.5,22.131Z\"></path>";
        response += "            <path d=\"M17.5,22.693a3.189,3.189,0,0,1-2.262-.936L8.487,15.006a1.249,1.249,0,0,1,1.767-1.767l6.751,6.751a.7.7,0,0,0,.99,0l6.751-6.751a1.25,1.25,0,0,1,1.768,1.767l-6.752,6.751A3.191,3.191,0,0,1,17.5,22.693Z\"></path>";
        response += "            <path d=\"M31.436,34.063H3.564A3.318,3.318,0,0,1,.25,30.749V22.011a1.25,1.25,0,0,1,2.5,0v8.738a.815.815,0,0,0,.814.814H31.436a.815.815,0,0,0,.814-.814V22.011a1.25,1.25,0,1,1,2.5,0v8.738A3.318,3.318,0,0,1,31.436,34.063Z\"></path>";
        response += "        </svg>";
        response += "    </span>";
        response += "</button>";
        response += "</div>";
        
        response += "<div class=\"container\">";
        response += "<table class=\"content-table\" id=\"myTable\">";
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

        response += "});";
        
        response += "val = '0';"; 

        response += "function exportToCSV() {";
        response += "    var storedData = JSON.parse(localStorage.getItem('StudentData')) || [];";
        response += "    if (storedData.length === 0) {";
        response += "        alert('No data to export.');";
        response += "        return;";
        response += "    }";
        response += "    var csvContent = 'data:text/csv;charset=utf-8,';";
        response += "    csvContent += 'Student Name,Student ID,Time,Date\\n';";
        response += "    storedData.forEach(function(student) {";
        response += "        csvContent += `${student.name},${student.id},${student.time},${student.date}\\n`;";
        response += "    });";
        response += "    var encodedUri = encodeURI(csvContent);";
        response += "    var link = document.createElement('a');";
        response += "    link.setAttribute('href', encodedUri);";
        response += "    link.setAttribute('download', 'attendance_data.csv');";
        response += "    document.body.appendChild(link);";
        response += "    link.click();";
        response += "    document.body.removeChild(link);";
        response += "}";
        
        response += "function myFunction() {";
        response += "    var input, filter, table, tr, td, i, txtValue;";
        response += "    input = document.getElementById('searchInput');";
        response += "    filter = input.value.toUpperCase();";
        response += "    table = document.getElementById('myTable');"; // Note: The table ID 'myTable' needs to be defined in your HTML
        response += "    tr = table.getElementsByTagName('tr');";
        response += "    for (i = 0; i < tr.length; i++) {";
        response += "        td = tr[i].getElementsByTagName('td')[0];";
        response += "        if (td) {";
        response += "            txtValue = td.textContent || td.innerText;";
        response += "            if (txtValue.toUpperCase().indexOf(filter) > -1) {";
        response += "                tr[i].style.display = '';";
        response += "            } else {";
        response += "                tr[i].style.display = 'none';";
        response += "            }";
        response += "        }";
        response += "    }";
        response += "}";
        
        
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
