# AtomWave | Pebble Watchface

Zeit im Fluss.
Ein dynamisches, physikalisches Pixel-Art Watchface für alle Pebble Smartwatches.

![AtomWave Header](https://raw.githubusercontent.com/atomlabor/atomwave/main/AtomWave_Header.png)

!!! ENG BELOW !!!


## Über das Projekt

AtomWave visualisiert das Verstreichen der Zeit auf organische Weise. Der Wasserpegel auf dem Display steigt synchron zur aktuellen Uhrzeit an: Um 00:00 Uhr ist der Bildschirm leer, bis 23:59 Uhr füllt er sich vollständig. Das Design verbindet klassische Pixel-Art-Ästhetik mit intelligenter Datendarstellung und effizientem Ressourcenmanagement.

Das Watchface wurde für alle Pebble-Plattformen entwickelt und speziell für die hohe Auflösung der Pebble Time 2 (Emery) optimiert.

## Funktionen

### Dynamischer Wasserstand
Der Wasserpegel repräsentiert die Minuten des Tages. Je höher das Wasser steht, desto weiter ist der Tag fortgeschritten.

### Intelligenter Kontrast (Smart Contrast)
Um eine optimale Lesbarkeit zu gewährleisten, reagiert die Typografie auf den Wasserstand. Die Uhrzeit wird automatisch invertiert, sobald sie von der Wasserlinie bedeckt wird:
* Himmel: Weißer Text auf schwarzem Grund.
* Wasser: Schwarzer Text auf farbigem Grund.

### Akku-Status durch Farbkodierung
Auf Geräten mit Farbdisplay ändert das Wasser seine Farbe basierend auf dem aktuellen Ladestand der Pebble:
* Über 50%: Electric Ultramarine (Blau)
* Über 20%: Chrome Yellow (Gelb/Warnung)
* Unter 20%: Shocking Pink (Kritisch)

### Atmosphärische Details
* **Sternenhimmel:** Ein dynamischer Sternenhimmel, der im Laufe des Tages realistisch vom steigenden Wasser verdeckt wird.
* **Wellenphysik:** Sanfte Sinus-Wellen und aufsteigende Luftblasen werden bei Bewegung des Handgelenks oder zum Minutenwechsel animiert.
* **Seltene Ereignisse:** Gelegentlich können aufmerksame Nutzer etwas beobachten.

### Technische Optimierung
* **Eco-Mode:** Die Bildwiederholrate der Animationen ist begrenzt und die Aktivitätsdauer minimiert, um die Akkulaufzeit der Uhr zu schonen.
* **High-Res Support:** Native Unterstützung für die 200x228 Pixel Auflösung der Pebble Time 2 (Emery).
* **Lokalisierung:** Automatische Erkennung der Systemsprache für die korrekte Datumsanzeige (z.B. deutsche Wochentage).

## Installation & Build

Dieses Projekt basiert auf dem Pebble SDK 4.0.

1. Repository klonen:
   git clone https://github.com/dein-username/AtomWave.git
   cd AtomWave

2. Build erstellen:
   pebble clean
   pebble build

3. Installation (Beispiele):
   pebble install --emulator basalt
   pebble install --emulator emery

## Kompatibilität

AtomWave unterstützt folgende Hardware:
* Pebble Time
* Pebble Time Steel
* Pebble Time Round
* Pebble 2 (Monochrom-Modus wird unterstützt)
* Pebble Time 2

## Credits

* Code & Konzept: atomlabor
* Schriftart: Custom Block Font (42px)
* Grafiken: Custom Pixel Assets

Made for the Pebble Community with love from https://atomlabor.de


_______________________________________________________________

## ENG

# AtomWave

Time in Flow.
A dynamic, physics-based pixel art watchface for all Pebble smartwatches.

## About the Project

AtomWave visualises the passing of time in an organic way. The water level on the display rises in sync with the current time: at 00:00 the screen is empty, and by 23:59 it fills completely. The design combines classic pixel art aesthetics with intelligent data presentation and efficient resource management.

The watchface has been developed for all Pebble platforms and specifically optimised for the high resolution of the Pebble Time 2 (Emery).

## Features

### Dynamic Water Level
The water level represents the minutes of the day. The higher the water, the further the day has progressed.

### Smart Contrast
To ensure optimal readability, the typography reacts to the water level. The time is automatically inverted as soon as it is covered by the water line:
* Sky: White text on a black background.
* Water: Black text on a coloured background.

### Battery Status via Colour Coding
On devices with colour displays, the water changes its colour based on the Pebble's current charge level:
* Above 50%: Electric Ultramarine (Blue)
* Above 20%: Chrome Yellow (Yellow/Warning)
* Below 20%: Shocking Pink (Critical)

### Atmospheric Details
* **Starry Sky:** A dynamic starry sky that is realistically obscured by the rising water throughout the day.
* **Wave Physics:** Gentle sine waves and rising air bubbles are animated upon wrist movement or at the turn of the minute.
* **Rare Events:** Occasionally, observant users might spot something special.

### Technical Optimisation
* **Eco Mode:** The animation frame rate is limited and activity duration minimised to conserve the watch's battery life.
* **High-Res Support:** Native support for the 200x228 pixel resolution of the Pebble Time 2 (Emery).
* **Localisation:** Automatic detection of the system language for correct date display (e.g. German weekdays).

## Installation & Build

This project is based on the Pebble SDK 4.0.

1. Clone repository:
   git clone https://github.com/your-username/AtomWave.git
   cd AtomWave

2. Create build:
   pebble clean
   pebble build

3. Installation (Examples):
   pebble install --emulator basalt
   pebble install --emulator emery

## Compatibility

AtomWave supports the following hardware:
* Pebble Time
* Pebble Time Steel
* Pebble Time Round
* Pebble 2 (Monochrome mode supported)
* Pebble Time 2

## Credits

* Code & Concept: atomlabor
* Font: Custom Block Font (42px)
* Graphics: Custom Pixel Assets

Made for the Pebble Community with love from https://atomlabor.de
