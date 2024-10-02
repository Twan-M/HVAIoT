# TelegramLED Bot
Een tool die een Ledstrip kan besturen via een ESP32 doormiddel van Telegram commands.

## Hardware & Software
1. EPS32
2. Visual Studio Code
3. LED Strip (In dit geval met 12 LEDS)
4. Wifi Verbinding

## Onderdeel 0: Installeren Hardware
1. Sluit de ESP32 aan op je computer doormiddel van de USB aansluiting.
2. Sluit de LED Strip als volgt aan: +5V Kabeltje -> 3V3 Pin op de ESP, GND kabeltje -> GND Pin op de ESP, Din kabeltje -> D4 Pin op de ESP.

## Onderdeel 1: Installeren software
1. Installeer VScode "https://code.visualstudio.com/"
2. Click op het "Extensies" icoontje in VSCode in de linker navigatiebalk
![Screenshot 2024-10-02 194856](https://github.com/user-attachments/assets/cefc23d5-3452-4084-9c74-2dcd56a496dd)
3. Zoek naar "PlatformIO IDE", en klik op install. Wacht totdat PlatformIO IDE is geinstalleerd en de "Uninstall" knop verschijnt.
![Screenshot 2024-10-02 194947](https://github.com/user-attachments/assets/0219dffb-c65a-4104-aad5-027b6444f16c)
4. Klik op het PlatformIO icoontje in VSCode in de linker navigatiebalk
5. Je komt nu op de Startpagina van PlatformIO. (Mocht dit niet het geval zijn, dan kan je op deze pagina komen door op "PIO Home" te klikken, en vervolgens op "Open" te klikken
![Screenshot 2024-10-02 195428](https://github.com/user-attachments/assets/c7b199de-6870-40a6-a328-816ee9326899)
6. Klik op de knop "New Project"
![image](https://github.com/user-attachments/assets/d08b246e-c371-48a9-b77b-9d6330414c0c)
7. Voor je Project name in
8. Selecteerd je ESP device in het Board menu. (In ons geval is dit een Espressif ESP32 Dev Module)
9. Klik op Finish om je project te starten
![image](https://github.com/user-attachments/assets/a5c1d99c-6e9f-4247-a1c0-84bc7efee2db)

## Onderdeel 2: Installeren van Liberaries
In dit project maken we gebruik van een aantal Liberaries. Sommige staan standaard op de ESP32 en sommige dienen toegevoegd te worden.
1. Klik op de homepage van Platformio op de Liberaries knop.
2. Zoek naar "Adafruit NeoPixel", en klik deze aan.
![image](https://github.com/user-attachments/assets/dd486731-2ef8-4eaa-8586-52d4d9e4e1a0)
3. Vervolgens klik je op "Add to project", en selecteerd je het project die we in onderdeel 1 hebben gemaakt. Vervolgens klik je op "Add" om te liberarie toe te voegen
![image](https://github.com/user-attachments/assets/c8d2a78f-ea29-457f-847d-ec6e0350cfe0)
4. Herhaal de stappen 2-3 nogmaals voor de liberaries "ArduinoJson", "UniversalTelegramBot"
5. Zoals gezegd zijn er ook een aantal liberaries die al in de ESP32 aanwezig zijn, waar we graag gebruik van willen maken.
6. Navigeer naar de VSCode Explorer om zo je project map te zien.
7. Open de platformio.ini file.
8. Voeg na de regel framework = arduino de volgende regel toe: "monitor_speed = 115200" (Dit is zodat de serial monitor later goed functioneert)
9. Voeg onderaan, de regel "WiFi" toe.
![image](https://github.com/user-attachments/assets/cc31277f-c865-4595-8bc9-e84a93c5542e)
(Zorg ervoor dat het rood omcirkelde blok er bij jou hetzelfde uitziet als op de screenshot)

## Onderdeel 3: Het toevoegen van de code
Nadat alle software en liberaries zijn geinstalleerd (Onderdeel 1 & 2) is het tijd om de code te gaan toevoegen
1. Kopieer de code van de main.cpp file op Github pagina. https://github.com/Twan-M/HVAIoT/blob/main/Projects/TelegramLEDStrip/main.cpp
2. Navigeer naar de "Explorer" van VSCode. En open je project folder.
3. Open de folder "src", en open het bestand "main.cpp"
4. Plak de code van de Github in het main.cpp bestand.
![image](https://github.com/user-attachments/assets/1d9100fe-a0d2-4b87-9fc7-2485106418d6)

## Onderdeel 4: Het aanmaken en koppelen van de Telegram bot
1. Open telegram (Maak een account mocht je dit nog niet hebben), en zoek naar de username "BotFather"
![image](https://github.com/user-attachments/assets/132ee7eb-45ca-4c58-8b6d-4c108d2b2a52)
2. Klik op "Start"
3. Je krijgt nu een uitleg wat BotFather allemaal commando's heeft en wat ze doen. Wij gebruiken de command "/newbot"
4. BotFather zal je nu een aantal stappen laten doorlopen, waarna je een bericht krijgt met de Acces code voor de HTTP API.

## Onderdeel 5: Het toevoegen van de informatie
1. Navigeer nu terug naar het main.cpp bestand waar je zojuist alle code hebt ingeplakt.
2. Plaats de API key die je zojuist van BotFather hebt ontvangen op de plek: #define BOT_TOKEN "XXXXXXX:XXXXXXXXXXXXXX" Je vervangt de kruisjes met de juiste API Key.
3. Op regel "const char* ssid = "xxxxxx";" vervang je de xxxxxxx met het SSID van je WiFi of Hotspot (Dit is vaak de naam die je ook ziet als je verbind met het WiFi netwerk)
4. Op regel const char* password = "xxxxxx"; vervang je de xxxxxx met het Wachtwoord van je WiFi of Hotspot.
![image](https://github.com/user-attachments/assets/c249fd07-9c12-468a-8e04-26f0184e0bba)
5. Sla het bestand op door CTRL + S in te drukken.

## Onderdeel 6: Het opstarten van alles.
1. Zorg dat je ESP32 nog steeds zit aangesloten op je PC / Laptop.
2. Zorg dat de LED strip nog steeds juist zit aangesloten op de ESP32.
3. Klik op het "Upload" pijltje om de code naar de ESP32 te sturen.
![image](https://github.com/user-attachments/assets/e98054c3-f0a7-4fe1-9d3b-8e8942754fb9)
4. De code wordt nu verstuurd naar de ESP32. Wacht totodat dit process voltooid is.
5. Klik op het "Serial Monitor" stekker icoontje om de serial monitor te openen. (Hierin kan je informatie zien over wat er gaande is)
![image](https://github.com/user-attachments/assets/821bead7-023b-4c7e-905e-52a3d2d0b410)
6. Als alles is geladen, ga open je Telegram, en klik je op de link die BotFather naar je heeft gestuurd. (Dit is hetzelfde bericht als waar de API key in staat en ziet eruit als t.me/{naam van de bot}
7. Je kan nu je LED strip bedienen door "/light {kleur}" te sturen naar de bot. Bijvoorbeeld /light blue. Je zult zien dat de LED strip blauw word.

## Onderdeel 7: Troubleshooting.
1. Lukt het uploaden niet? Zorg ervoor dat de juiste COM poort is geselecteerd.
![image](https://github.com/user-attachments/assets/0a40029c-f7c8-4406-a0b7-55e9b7f08a55)
2. Doet de LED Strip het niet? Zorg ervoor dat hij op de juiste pinnetjes is aangesloten!
3. Krijg je een fout melding in de Serial monitor die lijkt op: "Software caused connection abort". Wacht dan even, je BOT zal na enkele seconden weer werken. Dit heeft te maken met Telegram API limits.
4. Herkent je computer de ESP niet? Download dan de drivers. "https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/establish-serial-connection.html"










