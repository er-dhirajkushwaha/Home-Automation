
// Blynk credentials
#define BLYNK_TEMPLATE_ID "your_template_id"
#define BLYNK_TEMPLATE_NAME "your_template_name"
#define BLYNK_AUTH_TOKEN "your_auth_token"

// header files
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Preferences.h>

// wifi credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";


// Pin for controlling the LED
#define LED_PIN 14 // Using pin D5

// NVS (Non-Volatile Storage) object
Preferences preferences;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Start the Preferences library (this is where LED state will be saved)
  preferences.begin("ledControl", false); // "ledControl" is the namespace, false means read-write

  // Check and restore the last LED state from NVS
  int ledState = preferences.getInt("ledState", LOW);  // Default is LOW (OFF) if not set
  digitalWrite(LED_PIN, ledState);  // Restore the LED state

  // Attempt to connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Once connected, print the IP address
  Serial.println();
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.println();
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);

}

BLYNK_WRITE(V0) { 
  int state = param.asInt();  // Get button state (1 or 0)
  if (state == 1) {
    // Turn ON the LED (AC appliance or light)
    digitalWrite(LED_PIN, HIGH);
    preferences.putInt("ledState", HIGH);  // Save LED state to NVS (HIGH means ON)
    Serial.println("LED ON");
  } else {
    // Turn OFF the LED (AC appliance or light)
    digitalWrite(LED_PIN, LOW);
    preferences.putInt("ledState", LOW);  // Save LED state to NVS (LOW means OFF)
    Serial.println("LED OFF");
  }
}

void loop() {
  // Run Blynk tasks
  Blynk.run();
}
