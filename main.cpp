#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> 

#define LED_PIN     4     
#define NUM_LEDS    12     
#define BRIGHTNESS  255
#define LED         2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "";
const char* password = "";
const String weatherApiUrl = "https://api.open-meteo.com/v1/forecast?latitude=52.374&longitude=4.8897&hourly=temperature_2m,precipitation&forecast_days=1";

void fetchWeatherData();
void displayWeatherData(float temperatures[], float precipitations[]);
uint32_t getTemperatureColor(float temperature);
uint32_t getPrecipitationColor(float precipitation);

void setup() {
  Serial.begin(115200);
  
  // Connecting to WiFi with LED confirmation 2X blink
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
   digitalWrite(LED,LOW);
  }

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  fetchWeatherData();
}

void loop() {
  // Refresh the weather data periodically, every 30 sec.
  delay(15000); 
  fetchWeatherData(); 
}

// Function to fetch weather data from the Open Meteo API
void fetchWeatherData() {
  HTTPClient http;
  http.begin(weatherApiUrl); 

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println(payload);

    DynamicJsonDocument doc(4096); 
    deserializeJson(doc, payload);

    // Array with selectedHours so it'll only read those hours as LED strip only has 12 LEDS.
    const int selectedHours[] = {4, 9, 14, 19, 23};
    float temperatures[5];
    float precipitations[5];

    // Get temperature and precipitation for the next 5 hours
    for (int i = 0; i < 5; i++) {
      int hourIndex = selectedHours[i];
      temperatures[i] = doc["hourly"]["temperature_2m"][hourIndex];
      precipitations[i] = doc["hourly"]["precipitation"][hourIndex];
    }

    // Display weather data on the LED strip with error handling 4X blink
    displayWeatherData(temperatures, precipitations);
  } else {
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
  }
  
  http.end();
}

// Function to display temperature and precipitation data on the LED strip
void displayWeatherData(float temperatures[], float precipitations[]) {
  // Set the first 5 LEDs for temperature
  for (int i = 0; i < 5; i++) {
    uint32_t color = getTemperatureColor(temperatures[i]);
    strip.setPixelColor(i, color);
  }

  // Set the last 5 LEDs for precipitation
  for (int i = 7; i < 12; i++) {
    uint32_t color = getPrecipitationColor(precipitations[i - 7]);
    strip.setPixelColor(i, color);
  }

  // Set the middle 2 LEDs to Green for split
  strip.setPixelColor(5, strip.Color(0, 255, 0));
  strip.setPixelColor(6, strip.Color(0, 255, 0));

  strip.show();
}

// Function to determine the color for temperature, Blue 5C is cold = Blue, 15C is hot = Red. This makes 10 orange / white = Middle temperature. Using Colro mapping.
uint32_t getTemperatureColor(float temperature) {
  if (temperature <= 5) {
    return strip.Color(0, 0, 255);
  } else if (temperature >= 15) {
    return strip.Color(255, 0, 0); 
  } else {
    int red = map(temperature, 5, 15, 0, 255); 
    int blue = map(temperature, 5, 15, 255, 0); 
    int green = map(temperature, 5, 10, 0, 255);

    if (temperature > 10) {
      green = map(temperature, 10, 15, 255, 0);
    }
    
    return strip.Color(red, green, blue);
  }
}

// Function to determine the color for precipitation, White is clear, blue is precipitation
uint32_t getPrecipitationColor(float precipitation) {
  if (precipitation > 0) {
    return strip.Color(0, 0, 255);
  } else {
    return strip.Color(255, 255, 255);
  }
}
