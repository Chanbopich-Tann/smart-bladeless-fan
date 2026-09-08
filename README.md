# 🌀 Smart Bladeless Fan

An open-source, embedded smart cooling system developed as a Graduate Independent Project at the **University of North Carolina at Charlotte (UNCC)**. This project combines digital fabrication technologies (3D printing and laser cutting) with Arduino microcontrollers to create a safer, quieter, and multi-functional desk fan.

---

## 📸 Overview & Hardware Design

| Complete Assembly | 3D Printed Components | Laser Cut Enclosure |
| :---: | :---: | :---: |
| ![Assembled Fan](docs/assembled_fan.jpg) | ![3D Printed Parts](docs/3d_parts.jpg) | ![Laser Cut Box](docs/laser_box.jpg) |

Unlike traditional cooling fans with exposed blades, this design utilizes a hidden internal impeller housed safely inside the fan body to eliminate injury risks and significantly reduce acoustic noise.

---

## 🛠️ Key Features & Interactive Modes

1. **Fan Speed Control (PWM Motor Drive):**
   * Control the internal DC motor speed using an analog potentiometer mapped from 0 to 255 PWM values.
2. **Multi-Mode RGB Lighting:**
   * Cycle through 7 dynamic LED color modes (Red, Green, Blue, Purple, Teal, Orange, White, and OFF) using a dedicated push-button with software debouncing.
3. **Interactive Audio Playback:**
   * Trigger melody playback ("Jingle Bells") through an integrated piezo speaker using a secondary push-button input.

---

## 🧱 Digital Fabrication & CAD Specifications

### 3D Printing (Prusa i3 MK3)
All 3D components were designed in **Fusion 360** and sliced using **PrusaSlicer**:
* **Inner & Outer Circular Fan Heads:** Form the aerodynamically constrained circular airflow chamber.
* **Circular Fan Body:** Connects the air intake base to the fan head with intake slots.
* **Hidden Impeller Blade & Motor Holder:** Holds the DC motor centrally aligned to prevent mechanical vibration and damage.

### Laser Cutting (Mini Laser Cutter)
Designed in **Inkscape** and **Adobe Illustrator**:
* **6-Sided Finger-Jointed Box:** Serves as the structural base and enclosure for the Arduino circuit.
* **Control Panel & Custom Rastering:** Features front cutout ports for switches/potentiometer and custom underside branding ("Tann's Bladeless Fan").

---

## ⚡ Circuit Schematic & Hardware Components

![Tinkercad Schematic](docs/tinkercad_schematic.png)

### Hardware List
* **Microcontroller:** Arduino Uno
* **Actuators & Outputs:** 5V DC Motor, RGB LED, Piezo Speaker
* **Inputs & Controls:** 10k Potentiometer, 2 Push-Buttons / Snap Switches
* **Power & Driver:** NPN Transistor / MOSFET, Resistors (220Ω), 9V Battery / Barrel Jack, Dual Breadboards

---

## 💻 Code Structure

The source code (`/src/main.ino`) handles three asynchronous hardware interactions:

```cpp
// Motor PWM Speed Control Example
val = analogRead(POT);
val = map(val, 0, 1023, 0, 255);
analogWrite(MOTOR, val);

// Software Button Debouncing for RGB Mode Switching
boolean currentButton2 = debounceButton(BUTTON2, lastButton2);
if (lastButton2 == LOW && currentButton2 == HIGH) {
    ledMode = (ledMode + 1) % 8;
    setMode(ledMode);
}
