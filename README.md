# kash


# RP2040 Digital Photo Album

A compact digital photo album project using the **Waveshare RP2040-Zero** and a **GC9A01 1.28-inch Round LCD Display**. Features a startup animation, 16-image gallery, and auto-dimming power management.

## Features
- **16 Image Gallery**: Supports high-quality RGB bitmaps.
- **Power Management**: Toggle ON/OFF state with a dedicated button and automatic backlight dimming after 2 minutes of inactivity.
- **Startup Animation**: Smooth loading sequence upon power-up.
- **Navigation**: Simple 'Next' and 'Previous' tactile button control.

## Wiring Diagram

| Component       | Pin on GC9A01 / Button | RP2040-Zero Pin |
|-----------------|------------------------|-----------------|
| **Display SPI** | VCC                    | 5V or 3.3V      |
|                 | GND                    | GND             |
|                 | DIN (MOSI)             | GP3             |
|                 | CLK (SCK)              | GP2             |
|                 | CS                     | GP7             |
|                 | DC                     | GP5             |
|                 | RST                    | GP4             |
|                 | BLK (Backlight)        | GP6             |
| **Buttons** | Next Image             | GP15            |
|                 | Previous Image         | GP14            |
|                 | Power Toggle           | GP13            |

*Note: All buttons should be connected between the designated GP pin and GND (Active Low).*

## Button Functionality

### 1. Power Button (GP13)
- **Press Once**: Toggles the device state. 
- **OFF State**: Clears the screen and kills the backlight to save power.
- **ON State**: Triggers the startup animation and resumes the gallery at the last image.

### 2. Navigation Buttons (GP14 & GP15)
- **Next (GP15)**: Cycles forward through the 16 images.
- **Previous (GP14)**: Cycles backward through the images.
- **Wake Up**: Pressing either button while the screen is dimmed will restore full brightness.

### 3. Auto-Dimming
- If no navigation buttons are pressed for **120 seconds**, the backlight PWM duty cycle drops to 20/255 to conserve energy.

## Prerequisites
- **Arduino IDE** with Raspberry Pi Pico/RP2040 Board Package.
- **Libraries**: 
  - `Adafruit_GFX`
  - `Adafruit_GC9A01A`
