#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 4       // De pin waarop je de LED-strip aansluit
#define NUMPIXELS 12     // Aantal pixels in je LED-strip

// Adafruit IO credentials
#define IO_USERNAME "xxxx"
#define IO_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxx"

// WiFi credentials
#define WIFI_SSID "xxxxx"
#define WIFI_PASS "xxxxxxxxxxxxx"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Maak een feed aan
AdafruitIO_Feed *feed = io.feed("ESP_BFF");

// Setup voor NeoPixel LED-strip
Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool isLEDOn = false;  // Variabele die de status van de LED-strip bijhoudt

// Deze functie wordt aangeroepen als een bericht binnenkomt
void handleMessage(AdafruitIO_Data *data) {
  String value = data->toString();
  Serial.print("Received: ");
  Serial.println(value);

  // Zet de LED-strip aan of uit op basis van de huidige status
  if (value == "love") {
    if (isLEDOn) {
      // Als de LED aan is, zet hem uit
      Serial.println("Turning off LED strip!");
      strip.clear();  // Zet alle pixels uit
      strip.show();
      isLEDOn = false;  // Update de status
    } else {
      // Als de LED uit is, zet hem aan
      Serial.println("Turning on LED strip!");
      for (int i = 0; i < NUMPIXELS; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));  // Zet alle pixels rood
      }
      strip.show();
      isLEDOn = true;  // Update de status
    }
  }
}

void setup() {
  // Start de seriële monitor voor debugging
  Serial.begin(115200);

  // Start de LED-strip
  strip.begin();
  strip.show(); // Maak alle pixels zwart (uit)

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

  // Abonneer op veranderingen in de feed
  feed->onMessage(handleMessage);
}

void loop() {
  // Verwerk de IO-verbinding
  io.run();
}