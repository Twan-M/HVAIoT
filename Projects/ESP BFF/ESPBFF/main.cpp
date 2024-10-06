#include <AdafruitIO_WiFi.h>
#include <WiFi.h>

#define BUTTON_PIN 4  // ESP32 pin voor de knop (D0 op ESP8266 = GPIO0 op ESP32)
#define LED_PIN 2     // ESP32 pin voor de LED (in dit geval ingebouwde LED op GPIO2)

// Adafruit IO credentials
#define IO_USERNAME "xxxx"
#define IO_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

// WiFi credentials
#define WIFI_SSID "xxxxx"
#define WIFI_PASS "xxxxxxxxxx"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Maak een feed aan
AdafruitIO_Feed *feed = io.feed("ESP_BFF");

// Deze functie wordt aangeroepen als een bericht binnenkomt
void handleMessage(AdafruitIO_Data *data) {
  String value = data->toString();
  Serial.print("Received: ");
  Serial.println(value);

  // Zet de LED aan als we "love" ontvangen
  if (value == "love") {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);  // Zet de LED 1 seconde aan
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  // Start de seriële monitor voor debugging
  Serial.begin(115200);

  // Configureer de knoppin
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Gebruik pull-up omdat de knop naar GND schakelt

  // Start de verbinding met Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Wacht tot de verbinding tot stand komt
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  // Verwerk de IO-verbinding
  io.run();

  // Lees de knopstatus
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    // Verstuur "love" naar Adafruit IO als de knop is ingedrukt
    Serial.println("Button pressed, sending love!");
    feed->save("love");
    delay(1000);  // Debounce vertraging
  }
}