# TelegramLED Bot
Een tool die een Ledstrip kan besturen via een ESP32 doormiddel van Telegram commands.

## Hardware & Software
1. 2x EPS32
2. Visual Studio Code
3. LED Strip (In dit geval met 12 LEDS)
4. Button met 3 pins
5. Wifi Verbinding
6. Adafruit.IO Account

## Onderdeel 0: Installeren Hardware
1. Sluit de 2 ESP32's aan op je computer doormiddel van de USB aansluiting.
2. Sluit de LED Strip als volgt aan op een van de EPS's: +5V Kabeltje -> 3V3 Pin op de ESP, GND kabeltje -> GND Pin op de ESP, Din kabeltje -> D4 Pin op de ESP.
3. Sluit de Button als volgt aan op de andere ESP: S pin van button -> D4 pin op de ESP, - pin op de button -> GND pin op de ESP, en de middelste pin van de ESP -> 3v3 Pin op de ESP

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
10. Maak nu een 2e Project aan voor de a2e ESP.

## Onderdeel 2: Installeren van Liberaries voor de ESP's
In dit project maken we gebruik van een aantal Liberaries. Sommige staan standaard op de ESP32 en sommige dienen toegevoegd te worden.
1. Klik op de homepage van Platformio op de Liberaries knop.
2. Zoek naar "Adafruit NeoPixel", en klik deze aan.
![image](https://github.com/user-attachments/assets/dd486731-2ef8-4eaa-8586-52d4d9e4e1a0)
3. Vervolgens klik je op "Add to project", en selecteerd je het project die we in onderdeel 1 hebben gemaakt. Vervolgens klik je op "Add" om te liberarie toe te voegen
![image](https://github.com/user-attachments/assets/c8d2a78f-ea29-457f-847d-ec6e0350cfe0)
4. Herhaal de stappen 2-3 nogmaals voor de liberaries "Adafruit IO Arduino"
7. Open de platformio.ini file.
8. Voeg na de regel framework = arduino de volgende regel toe: "monitor_speed = 115200" (Dit is zodat de serial monitor later goed functioneert)
![image](https://github.com/user-attachments/assets/0b03e16e-f194-43ae-83bf-124dd2e90184)
9. Selecteer nu de andere ESP, dit kan je doen door op het stekker icoontje onderin te klikken, en de andere COM poort te selecteren.
10. Selecteer nu de 2e project folder, dit kan je doen door op het folder icoontje onderin te klikken en de andere project folder te selecteren.
![image](https://github.com/user-attachments/assets/2e2b450f-fb62-4ec9-8ed2-50d80e5d674a)
11. Hier hebben we de Liberaries Adafruit Unified Sensor, en Adafruit IO Arduino nodig. (Deze voeg je toe op dezelfde manier als bij de stappen 1-3)
12. Nu hebben we 2 projecten, eentje voor de ESP met de button, en eentje voor de ESP met de LED strip.

## Onderdeel 3: Het toevoegen van de code
1. Kopieer en plak nu de code van het eerste project: "ESPBFF" in jouw project waar je "Adafruit Unified Sensor" liberary hebt toegevoegd.
2. Kopieer en plak nu de code van het tweede project: "ESPBFF_Receiver" in jouw project waar je de "Adafruit NeoPixel" liberary hebt toegevoegd.

## Onderdeel 4: Het instellen van de gegevens
1. Log in op je Adafruit IO account (Of maak er een aan als je er nog geen hebt) https://io.adafruit.com/
2. Op de homepagina van je account, klik je op "Feeds"
3. Klik op de geopende pagina op "New Feed" en maak een feed aan. (De naam mag je zelf kiezen)
![image](https://github.com/user-attachments/assets/fc4e31b4-1fa4-4e78-8b19-e7f7e4d9c70a)
4. Open de zojuist gemaakte feed, en klik op het sleutel icoontje rechts bovenin.
![image](https://github.com/user-attachments/assets/a5c577c1-039e-4811-888a-afc5e2e332d3)
5. Open nu weer VSCode, en open beide main.cpp files.
6. In beide files moet je nu bij de #define IO_USERNAME "xxxxxx" en #define IO_KEY "xxxxxxxxxxxxxxxxxxx" gaan aanpassen. Vervang de xxxxx met de gegevens die je ziet als je op het sleuteltje klik op Adafruit IO. (Dit zijn de Username en Active Key)
7. Vervang nu in beide main.cpp files de #define WIFI_SSID "xxxxx" en #define WIFI_PASS "xxxxxxxxxxxx" met de gegevens van jouw Wifi of Hotspot. WIFI_SSID is de naam van de wifi of Hotspot, en WIFI_PASS is het wachtwoord.
8. Sla nu beide bestanden op door CTRL + S in de drukken.

## Onderdeel 5: Het uploaden van de software.
1. Open nu het eerste project (Het project waar je de Adafruit Unified Sensor liberary hebt toegevoegd.) - En zorg ervoor dat je ook deze project folder hebt geselecteerd (Zie Onderdeel 2 stap 10)
2. Zorg ervoor je ook de ESP selecteerd waar de button is op aangesloten.
3. Klik op het Upload knopje onderin.
![image](https://github.com/user-attachments/assets/ead4d70d-ee14-45bb-954b-07117ecc730a)
4. Selecteerd nu het 2e project. (Het project waar je de Adafruit NeoPixel liberary hebt toegevoegd)
5. Selecteer nu de 2e ESP. (De ESP waar de ledstrip aanvast zit)
6. Klik weer op het upload knopje.

## Onderdeel 6: Het testen van de functie
1. Zorg ervoor dat beide ESP's aan staan (Zijn verbonden met de computer)
2. Klik op het knopje dat vast zit aan de eerste ESP.
3. De LED strip zal aangaan bij de 2e ESP.

## Onderdeel 7: Troubleshooting.
1. Lukt het uploaden niet? Zorg ervoor dat de juiste COM poort is geselecteerd.
![image](https://github.com/user-attachments/assets/0a40029c-f7c8-4406-a0b7-55e9b7f08a55)
2. Doet de LED Strip het niet? Zorg ervoor dat hij op de juiste pinnetjes is aangesloten!
3. Doet de Button het niet? Zorg ervoor dat hbij op de juiste pinnetjes is aangesloten!
4. Herkent je computer de ESP niet? Download dan de drivers. "https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/establish-serial-connection.html"
5. Gaat de ledstrip op de 2e ESP niet aan? Open dan de Adafruit IO Feed, en kijk of er wel een Feed binnenkomt
![image](https://github.com/user-attachments/assets/e3e321f1-acca-4321-ae0a-d1c392fb61db)
6. Heb je mogelijk toch de verkeerde code op de verkeerde ESP geupload? Wissel dan de ledstrip en button om.




