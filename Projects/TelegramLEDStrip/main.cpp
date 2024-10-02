#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <Universaltelegrambot.h>

#define LED_PIN     4     
#define NUM_LEDS    12     
#define BRIGHTNESS  255
#define LED         2
#define BOT_TOKEN   "xxxxxxx:xxxxxxxxxxxxxxxxx"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "xxxxxx";
const char* password = "xxxxxx";
const unsigned long BOT_MTBS = 1000;

unsigned long lastUpdate = 0;
int discoStep = 0;
int transitionStep = 0;
bool discoMode = false;
const int transitionSpeed = 1;  // Speed of color transition

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;

// Disco mode for led strip. Uses transitionStep, discoStep and transitionSpeed to determain Disco state.
void runDisco()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= transitionSpeed) {
        lastUpdate = currentMillis;

        for (int i = 0; i < NUM_LEDS; i++) {
            // Gradually transition between colors based on discoStep and transitionStep
            uint32_t color;

            switch (discoStep) {
                case 0:
                    color = strip.Color(255 - transitionStep, transitionStep, 0);
                    break;
                case 1:
                    color = strip.Color(0, 255 - transitionStep, transitionStep);
                    break;
                case 2:
                    color = strip.Color(transitionStep, 0, 255 - transitionStep);
                    break;
            }

            strip.setPixelColor(i, color);
        }

        strip.show(); 

        transitionStep++;
        if (transitionStep > 255) {
            transitionStep = 0;
            discoStep++;
            if (discoStep > 2) {
                discoStep = 0; 
            }
        }
    }
}

bool manageLED(String color)
{
  color.toLowerCase();

  if (color == "disco") {
    discoMode = true; 
    return true;
  } 
  else {
    discoMode = false;  // Disable disco mode if any other color is selected
    uint32_t ledColor;
    bool validColor = true;

    // Determine the color based on the input
    switch (color[0]) {
      case 'w': // White
        ledColor = strip.Color(255, 255, 255);
        break;
      case 'r':
        ledColor = strip.Color(255, 0, 0);
        break;
      case 'g':
        ledColor = strip.Color(0, 255, 0);
        break;
      case 'b':
        ledColor = strip.Color(0, 0, 255);
        break;
      default:  // Invalid color
        validColor = false;
        break;
    }

    if (validColor) {
      for (int i = 0; i < 12; i++) {
        strip.setPixelColor(i, ledColor);
      }
      strip.show();
    }

    return validColor;
  }
}

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    bot.sendMessage(bot.messages[i].chat_id, "log': message received", "");
    Serial.println(bot.messages[i].text);

    // Check if the command starts with "/light"
    if (bot.messages[i].text.startsWith("/light"))
    {
      // Check if the message has an additional color argument
      int spaceIndex = bot.messages[i].text.indexOf(' ');
      if (spaceIndex != -1) // If there is a space after "/light"
      {
        String color = bot.messages[i].text.substring(spaceIndex + 1); // Extract the color
        color.toLowerCase();

        bool validColor = manageLED(color);

        if (validColor) {
          bot.sendMessage(bot.messages[i].chat_id, "Ledstrip aan; Kleur " + color + ".", "");
        } else {
           bot.sendMessage(bot.messages[i].chat_id, "Deze kleur bestaat niet. Je kann kiezen uit; White, Red, Green, Blue of Disco.", "");
        }
      }
      else
      {
        // If no color is provided, ask the user to choose a color
        bot.sendMessage(bot.messages[i].chat_id, "Je moet een kleur kiezen. Je kan kiezen uit: White, Red, Green, Blue & Disco. (Usage: /light disco)", "");
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(LED,OUTPUT);

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED,HIGH);

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  strip.begin();
  strip.clear();
}

void loop()
{
  // If disco mode is active, run the disco animation
  if (discoMode) {
    runDisco();
  }

  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}