# ESP32 WiFi Hotspot Bridge

Transform your ESP32 into a WiFi bridge/hotspot that connects to an existing WiFi network and shares that connection with other devices. Perfect for extending WiFi range, bypassing device limitations, or creating a portable hotspot.

## 🌟 Features

- **WiFi Bridge Mode**: Connects to an existing WiFi network (STA mode) and creates its own access point (AP mode)
- **NAPT Support**: Network Address Port Translation allows connected devices to access the internet through the ESP32
- **MAC Address Spoofing**: Optionally change the ESP32's MAC address (useful for campus/restricted networks)
- **Serial Monitoring**: Detailed connection status and event logging
- **Configurable Network Settings**: Customizable AP credentials and IP addressing

## 🧰 Hardware Requirements

- **ESP32 board** (Tested on: **Seeed Studio XIAO ESP32-C3**)
- USB cable for programming and power

> **Note**: This project has been tested and verified working on the Seeed Studio XIAO ESP32-C3. Other ESP32 variants may work but have not been tested.

## 📋 Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (or Arduino CLI)
- ESP32 board support installed in Arduino IDE
  - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to **File → Preferences → Additional Board Manager URLs**
  - Install **ESP32** boards via **Tools → Board → Boards Manager**

## 🚀 Getting Started

### 1. Configure WiFi Credentials

Open `wifi-ap.ino` and update the following lines with your WiFi network credentials:

```cpp
#define STA_SSID "" // Your WiFi network name
#define STA_PASS "" // Your WiFi password
```

**Example:**
```cpp
#define STA_SSID "MyHomeWiFi"
#define STA_PASS "MySecurePassword123"
```

### 2. (Optional) Customize Hotspot Settings

You can modify the ESP32's access point name and password:

```cpp
#define AP_SSID "ESP32-STA-WIFI-BRIDGE" // Hotspot name visible to devices
#define AP_PASS "12345678"               // Hotspot password (min 8 characters)
```

### 3. (Optional) Change MAC Address

If you need to spoof the MAC address (e.g., for campus networks), modify line 32:

```cpp
uint8_t newMacAddress[] = {0xA0, 0x00, 0x00, 0x00, 0x00, 0x00};
```

> **Important**: The first byte's bit 0 must be 0 (e.g., `0xA0` is valid, `0xA1` is not)

### 4. Flash to ESP32

1. Connect your ESP32 board via USB
2. In Arduino IDE:
   - Select your board: **Tools → Board → ESP32 → (your board)**
   - Select the port: **Tools → Port → (your COM port)**
3. Click **Upload** (➡️ button)
4. Wait for the upload to complete

### 5. Connect Your Device

1. On your phone/laptop, search for WiFi networks
2. Connect to `ESP32-STA-WIFI-BRIDGE` (or your custom AP_SSID)
3. Enter the password: `12345678` (or your custom AP_PASS)
4. You're now connected through the ESP32 bridge! 🎉

## 📡 How It Works

```
[Internet] ← WiFi → [Your Router] ← WiFi → [ESP32 Bridge] ← WiFi → [Your Phone/Device]
                     (STA_SSID)              (AP Mode)
```

The ESP32 operates in dual mode:
- **Station Mode (STA)**: Connects to your existing WiFi network
- **Access Point Mode (AP)**: Creates its own WiFi network for devices to connect to
- **NAPT**: Routes traffic between the two networks, allowing internet access

## 🔍 Monitoring Connection Status

Open the **Serial Monitor** (Tools → Serial Monitor) at **115200 baud** to view:
- MAC address information
- Connection status updates
- IP address assignments
- Client connections/disconnections

## 📝 Network Configuration

Default AP network settings:

| Setting | Value |
|---------|-------|
| AP IP Address | 192.168.4.1 |
| Subnet Mask | 255.255.255.0 |
| DHCP Start | 192.168.4.2 |
| DNS Server | 8.8.4.4 |

To modify these, edit lines 11-14 in the code.

## ⚠️ Troubleshooting

- **ESP32 won't connect to WiFi**: Double-check your `STA_SSID` and `STA_PASS` credentials
- **Can't see the hotspot**: Verify `AP_SSID` and `AP_PASS` are configured, and the AP started successfully (check Serial Monitor)
- **Connected but no internet**: Ensure your upstream WiFi has internet access and NAPT is enabled
- **Upload fails**: Make sure you've selected the correct board and port in Arduino IDE
- **MAC address change fails**: Check Serial Monitor for error codes; ensure the first byte is valid

## 📜 License

This project is open source. Feel free to use, modify, and distribute as needed.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Tested hardware configurations are especially appreciated.

## 💡 Use Cases

- Extend WiFi range to hard-to-reach areas
- Share a single connection with devices that have MAC address restrictions
- Create a portable hotspot for travel
- Bypass device connection limits on networks
- Educational projects and WiFi experimentation

---
