#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "ZTE_2.4G_KugzUh";
const char* password = "2QEftxgL";
int counterValue;
// Create a web server on port 80
ESP8266WebServer server(80);
float temperatureValue = 0.0;

void setup() {
  Serial.begin(9600);  // Communication with Arduino on hardware serial (pins 0, 1)

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  // Define routes for the web server
  server.on("/entrance_servo_on", []() {
    server.send(200, "text/plain", "Entrance Servo On");
    Serial.println("ENTRANCE_SERVO_ON");  // Send command to Arduino
  });

  server.on("/entrance_servo_off", []() {
    server.send(200, "text/plain", "Entrance Servo Off");
    Serial.println("ENTRANCE_SERVO_OFF");  // Send command to Arduino
  });

  server.on("/exit_servo_on", []() {
    server.send(200, "text/plain", "Exit Servo On");
    Serial.println("EXIT_SERVO_ON");  // Send command to Arduino
  });

  server.on("/exit_servo_off", []() {
    server.send(200, "text/plain", "Exit Servo Off");
    Serial.println("EXIT_SERVO_OFF");  // Send command to Arduino
  });

  server.on("/laser_on", []() {
    server.send(200, "text/plain", "Laser On");
    Serial.println("LASER_ON");
  });

  server.on("/laser_off", []() {
    server.send(200, "text/plain", "Laser Off");
    Serial.println("LASER_OFF");
  });

  server.on("/lights_on", []() {
    server.send(200, "text/plain", "Lights On");
    Serial.println("LIGHTS_ON");
  });

  server.on("/lights_off", []() {
    server.send(200, "text/plain", "Lights Off");
    Serial.println("LIGHTS_OFF");
  });

  server.on("/get_counter", []() {
    String message = String(counterValue);
    server.send(200, "text/plain", message);
  });

  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    if (data.startsWith("COUNTER:")) {
      counterValue = data.substring(8).toInt();
      Serial.printf("Received counter: %d\n", counterValue);
    } else if (data.startsWith("TEMP:")) {
      temperatureValue = data.substring(5).toFloat();  // Extract temperature value
      Serial.printf("Received temperature: %.2f\n", temperatureValue);
      server.on("/visitor_db", []() {
        String tempString = String(temperatureValue);
        server.send(200, "text/plain", tempString);
      });
      server.begin();
    }
  }
}
