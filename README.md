# AtomWave | Pebble Watchface

Zeit im Fluss.
Ein dynamisches, physikalisches Pixel-Art Watchface für alle Pebble Smartwatches.

![AtomWave Header](https://raw.githubusercontent.com/atomlabor/atomwave/main/AtomWave_Header.png.png)


!!! ENG BELOW !!! 

## Über das Projekt

AtomWave visualisiert das Verstreichen der Zeit auf organische Weise. **Der Wasserpegel auf dem Display steigt synchron zu den Minuten der aktuellen Stunde an:** Zur vollen Stunde (Minute 0) ist der Bildschirm leer, bis Minute 59 füllt er sich vollständig. Das Design verbindet klassische Pixel-Art-Ästhetik mit intelligenter Datendarstellung und extrem effizientem Ressourcenmanagement.

Das Watchface wurde für alle Pebble-Plattformen entwickelt und speziell für die hohe Auflösung der Pebble Time 2 (Emery) optimiert.

## Funktionen

### Dynamischer Wasserstand (Stündlicher Zyklus)
Der Wasserpegel repräsentiert den Fortschritt der aktuellen Stunde. Je höher das Wasser steht, desto näher rückt die nächste volle Stunde.

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
* **Sternenhimmel:** Ein dynamischer Sternenhimmel, der realistisch vom steigenden Wasser verdeckt wird.
* **Wellenphysik:** Sanfte Sinus-Wellen und aufsteigende Luftblasen werden animiert.
* **Seltene Ereignisse:** Gelegentlich können aufmerksame Nutzer etwas beobachten – aber nur, wenn der Wasserstand es physikalisch zulässt.

### Technische Optimierung (v2.0)
* **Eco-Mode:** Die Animations-Intervalle wurden auf 15 Minuten optimiert und die Bildwiederholrate begrenzt, um die Akkulaufzeit der Uhr massiv zu verlängern.
* **High-Res Support:** Native Unterstützung für die 200x228 Pixel Auflösung der Pebble Time 2 (Emery).
* **Lokalisierung:** Automatische Erkennung der Systemsprache für die korrekte Datumsanzeige (z.B. deutsche Wochentage).

## Installation & Build

Dieses Projekt basiert auf dem Pebble SDK 4.0 (`package.json`).

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
* Pebble Classic
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

AtomWave visualises the passing of time in an organic way. **The water level on the display rises in sync with the minutes of the current hour:** at minute 0 the screen is empty, and by minute 59 it fills completely. The design combines classic pixel art aesthetics with intelligent data presentation and highly efficient resource management.

The watchface has been developed for all Pebble platforms and specifically optimised for the high resolution of the Pebble Time 2 (Emery).

## Features

### Dynamic Water Level (Hourly Cycle)
The water level represents the progress of the current hour. The higher the water, the closer the next full hour approaches.

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
* **Starry Sky:** A dynamic starry sky that is realistically obscured by the rising water.
* **Wave Physics:** Gentle sine waves and rising air bubbles are animated.
* **Rare Events:** Occasionally, observant users might spot something special – but only if the water level physically allows it.

### Technical Optimisation (v2.0)
* **Eco Mode:** Animation intervals have been optimised to 15 minutes and frame rates are limited to maximize the watch's battery life.
* **High-Res Support:** Native support for the 200x228 pixel resolution of the Pebble Time 2 (Emery).
* **Localisation:** Automatic detection of the system language for correct date display (e.g. German weekdays).

## Installation & Build

This project is based on the Pebble SDK 4.0 (`package.json`).

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
* Pebble Classic
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
