# GainController

A lightweight VST plugin built with the JUCE framework for precise gain staging and stereo imaging control. GainController features a smooth gain knob, an intuitive pan control, a mono/stereo toggle switch, and an LED-style level indicator for real-time visual feedback.

---

## 🎛️ Features

- **Gain Control**  
  Adjust your track’s output level with a smooth rotary knob.

- **Pan Control**  
  Balance audio between left and right channels for perfect stereo placement.

- **Mono/Stereo Switch**  
  Quickly toggle between mono-summed and full-stereo output.

- **LED Level Indicator**  
  Monitor your signal with a classic LED-style meter to avoid clipping.

---

## 🛠️ Plugin Formats

- **VST3** (Windows, macOS)  
- **Audio Unit (AU)** (macOS)  
- **(Optional) LV2** — can be enabled via CMake

---

## 🔧 Requirements

- [JUCE 7.x](https://juce.com/get-juce)  
- C++17-capable compiler (Visual Studio 2019+/Xcode 12+)  
- CMake 3.15+ (or Projucer)  

---

## 🚧 Building

### Using the Projucer

1. Clone this repository:
   ```bash
   git clone https://github.com/jdqg24/GainController.git
   cd GainController
   
2. Open GainController.jucer in the Projucer app.

3. Configure your exporter (e.g., Visual Studio, Xcode).

4. Save, then “Open in IDE” and build.

---

## 💽 Installation

1. Locate the built plugin binary (e.g. .vst3 on Windows/macOS, .component for AU).

2. Copy it to your DAW’s plugin directory:

3. Windows VST3: C:\Program Files\Common Files\VST3\

4. macOS VST3: /Library/Audio/Plug-Ins/VST3/

5. macOS AU: /Library/Audio/Plug-Ins/Components/

6. Rescan plugins in your DAW.

---

## 🎚️ Usage

1. Insert GainController on your audio track.

2. Turn the Gain knob to set your desired level.

3. Adjust the Pan knob for stereo positioning.

4. Flip the Mono/Stereo switch to sum channels or keep stereo.

5. Watch the LED Indicator to ensure clean, unclipped audio.

