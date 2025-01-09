#include <WiFi.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Redmi Note 8 Pro";
const char* password = "pratik123";

// Pin definitions
#define IR_SENSOR_PIN 23
#define SERVO_PIN 19
#define DHTPIN 18
#define DHTTYPE DHT11
#define ENA 4
#define IN1 2
#define IN2 5
#define GREEN 12
#define Blue 27
#define buzzer 13
#define LDR 36
#define rainSensor 35

// Objects
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
LiquidCrystal_PCF8574 lcd(0x27);
WiFiServer server(80);

// Variables
bool fanState = false, doorState = false, lightState = false, rainDetected = false, fanWebOverride = false;
float temperature = 0.0, humidity = 0.0;
String doorMessage = "", rainMessage = "", lightMessage = "",fanMessage="";

// Timing variables
unsigned long lastIRTime = 0, lastLDRTime = 0, lastRainTime = 0;
const unsigned long debounceDelay = 200;

// Thresholds
const int lightThreshold = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(GREEN, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LDR, INPUT);
  pinMode(rainSensor, INPUT);
  dht.begin();
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.print("Connecting...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  lcd.clear();
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());
  delay(5000);
  lcd.clear();
  server.begin();
}

void loop() {
  unsigned long currentTime = millis();

  // Parallel handling of sensors and functionality
  handleIRSensor(currentTime);
  handleLDRSensor(currentTime);
  handleRainSensor(currentTime);
  handleFanControl(currentTime);
  updateTemperatureDisplay();

  // Handle web requests
  handleWebRequests();
}

// Handle IR Sensor
void handleIRSensor(unsigned long currentTime) {
  if (digitalRead(IR_SENSOR_PIN) == LOW && currentTime - lastIRTime > debounceDelay) {
    lastIRTime = currentTime;
    doorState = true;
    doorMessage = "Someone is at the door"; // Set message
    myServo.write(90);
    lcd.setCursor(0, 0);
    lcd.print("Door: OPEN");
    digitalWrite(buzzer, HIGH);
    digitalWrite(Blue, HIGH);
    delay(2000);
    myServo.write(0);
    doorState = false;
    digitalWrite(buzzer, LOW);
    digitalWrite(Blue, LOW);
   
  }
}

// Handle LDR Sensor
void handleLDRSensor(unsigned long currentTime) {
  if (digitalRead(LDR) == HIGH && currentTime - lastLDRTime > debounceDelay) {
    lastLDRTime = currentTime;
    lightState = true;
    lightMessage = "Lights are ON"; // Set message
    lcd.setCursor(0, 0);
    lcd.print("Light: ON");
    digitalWrite(Blue, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(Blue, LOW);
    lightState = false;
  }
}

// Handle Rain Sensor
void handleRainSensor(unsigned long currentTime) {
  if (digitalRead(rainSensor) == LOW && currentTime - lastRainTime > debounceDelay) {
    lastRainTime = currentTime;
    rainDetected = true;
    rainMessage = "It's raining"; // Set message
    lcd.setCursor(0, 1);
    lcd.print("Rain DETECTED");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    rainDetected = false;
  }
}

// Handle Fan Control
void handleFanControl(unsigned long currentTime) {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if (!isnan(temperature) && !isnan(humidity)) {
    if (!fanWebOverride) {
      if (temperature > 29.0 && !fanState) {
        fanState = true;
        fanMessage="Fan is ON";
        digitalWrite(ENA, HIGH);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Fan: ON ");
        lcd.print(temperature, 1);
      } else if (temperature <= 29.0 && fanState) {
        fanState = false;
        digitalWrite(ENA, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Fan: OFF");
      }
    }
  }
}

// Update Temperature and Humidity Display
void updateTemperatureDisplay() {
  if (!isnan(temperature) && !isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print(" %");
  } else {
    lcd.print("Temp: Error");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: Error");
  }
}
String generateStatusHTML() {
  String statusHTML = "<h3>Status Messages</h3>";
  statusHTML += "<p>Door: " + (doorMessage.isEmpty() ? "No Activity" : doorMessage) + "</p>";
  statusHTML += "<p>Rain: " + (rainMessage.isEmpty() ? "No Activity" : rainMessage) + "</p>";
  statusHTML += "<p>Light: " + (lightMessage.isEmpty() ? "No Activity" : lightMessage) + "</p>";
  statusHTML += "<p>Fan: " + (fanMessage.isEmpty() ? "No Activity" :fanMessage ) + "</p>";
  return statusHTML;
}

// Handle Web Requests
void handleWebRequests() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    request.trim();
    Serial.println("Request: " + request);
    client.flush();

    // Handle web actions
    if (request.indexOf("GET /fan=on") >= 0) {
      fanWebOverride = true;
      fanState = true;
      fanMessage = "Fan ON";
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } else if (request.indexOf("GET /fan=off") >= 0) {
      fanWebOverride = true;
      fanState = false;
      fanMessage = "Fan OFF";
      digitalWrite(ENA, LOW);
    } else if (request.indexOf("GET /door=open") >= 0) {
      doorState = true;
      doorMessage = "Door Opened!";
      myServo.write(90);
    } else if (request.indexOf("GET /door=close") >= 0) {
      doorState = false;
      doorMessage = "Door Closed!";
      myServo.write(0);
    } else if (request.indexOf("GET /light=on") >= 0) {
      lightState = true;
      lightMessage = "Lights Turned ON!";
      digitalWrite(Blue, HIGH);
    } else if (request.indexOf("GET /light=off") >= 0) {
      lightState = false;
      lightMessage = "Lights Turned OFF!";
      digitalWrite(Blue, LOW);
    } else if (request.indexOf("GET /status") >= 0) {
      String statusHTML = generateStatusHTML();
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
      client.print(statusHTML);
      return;
    }
      if (request.indexOf("GET /secure=on") >= 0) {
      doorState = false;
      doorMessage = "Home Secured!";
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      myServo.write(0); // Close door
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Home Secured!");
    }


    String html = generateHTML();
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print(html);
  }
}


// Generate HTML for Web Interface
String generateHTML() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Home Automation</title>
      <style>
        body { font-family: Arial, sans-serif; text-align: center; background: #f3f4f6; color: #333; }
        .card { margin: 20px auto; padding: 20px; width: 300px; border-radius: 8px; background: #fff; box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1); }
        h1 { color: #0066cc; }
        button { padding: 10px 20px; margin: 10px; background-color: #0066cc; color: white; border: none; border-radius: 5px; }
        button:hover { background-color: #005bb5; }
        .status { margin-top: 20px; padding: 10px; border-radius: 5px; background: #eaf4fc; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); }
        .status h3 { color: #0066cc; }
        .status p { margin: 8px 0; font-size: 16px; }
        .status .active { color: green; font-weight: bold; }
        .status .idle { color: gray; }
        .status-icon { margin-right: 5px; }
      </style>
    </head>
    <body>
      <h1>Home Automation</h1>
      <div class="card">
        <h2>Current Temp: )rawliteral" + String(temperature) + R"rawliteral( °C</h2>
        <h3>Humidity: )rawliteral" + String(humidity) + R"rawliteral( %</h3>
        <p>
          <button onclick="sendRequest('fan=on')">Fan ON</button>
          <button onclick="sendRequest('fan=off')">Fan OFF</button>
        </p>
        <p>
          <button onclick="sendRequest('door=open')">Door OPEN</button>
          <button onclick="sendRequest('door=close')">Door CLOSE</button>
        </p>
        <p>
          <button onclick="sendRequest('light=on')">Light ON</button>
          <button onclick="sendRequest('light=off')">Light OFF</button>
        </p>
        <p>
          <button onclick="sendRequest('secure=on')">Secure Home</button>
        </p>
        <div class="status" id="status">
          <h3>Status Messages</h3>
          <p><span class="status-icon">.</span>Door: <span class="idle">No Activity</span></p>
          <p><span class="status-icon">.</span>Rain: <span class="idle">No Activity</span></p>
          <p><span class="status-icon">.</span>Light: <span class="idle">No Activity</span></p>
          <p><span class="status-icon">.</span>Fan: <span class="idle">No Activity</span></p>
        </div>
      </div>
      <script>
        function sendRequest(action) {
          fetch('/' + action).then(() => updateStatus());
        }

        function updateStatus() {
          fetch('/status')
            .then(response => response.text())
            .then(data => {
              document.getElementById('status').innerHTML = data;
              setTimeout(resetMessages, 3000);
            });
        }

        // Auto-update status every second
        setInterval(updateStatus, 3000);
      </script>
    </body>
    </html>
  )rawliteral";
  return html;
}




