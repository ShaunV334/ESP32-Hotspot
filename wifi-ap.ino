#include <WiFi.h>
#include "esp_wifi.h"

#define STA_SSID "" //set your uplink ssid (the wifi network you want to connect to)
#define STA_PASS "" //uplink password

#define AP_SSID "ESP32-STA-WIFI-BRIDGE" //default ssid of the esp32
#define AP_PASS "12345678" // default password


IPAddress ap_ip(192, 168, 4, 1);
IPAddress ap_mask(255, 255, 255, 0);
IPAddress ap_leaseStart(192, 168, 4, 2);
IPAddress ap_dns(8, 8, 4, 4);

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Network.onEvent(onEvent);
  
 WiFi.mode(WIFI_STA);

    //Display the ESP32's default Mac Address
    Serial.print("This ESP32's default Mac Address is:  ");
    Serial.println(WiFi.macAddress());

    //Temporarily change the ESP32's Mac Address
    //Note that this will only override the ESP32's Mac address while this sketch is running.
    //If you upload a new sketch then the ESP32 will revert to its factory set Mac Address.
    //Note: The bit 0 of the first byte of MAC address cannot be 1 (so it can be 0xA0 but not 0xA1).

    uint8_t newMacAddress[] = {0xA0, 0x00, 0x00, 0x00, 0x00, 0x00};//Set your custom MAC address here (use one that is registered to campus wifi to use college wifi as a hotspot.)
    
    //To decrypt the result look in here: https://github.com/espressif/esp-idf/blob/v5.2.1/components/esp_wifi/include/esp_wifi.h
    //The base error is 0x3000 (12288 in decimal) so ESP_ERR_WIFI_NOT_INIT is 12289
    //An error of 0 means the Mac Address change was successful
    esp_err_t macAddressChangeResult = esp_wifi_set_mac(WIFI_IF_STA, &newMacAddress[0]);

    if (macAddressChangeResult == ESP_OK) {
      Serial.println("Mac Address successfully changed!");
      Serial.print("This ESP32's new Mac Address is:  ");
      Serial.println(WiFi.macAddress());
      Serial.println("");
    }


  WiFi.AP.begin();
  WiFi.AP.config(ap_ip, ap_ip, ap_mask, ap_leaseStart, ap_dns);
  WiFi.AP.create(AP_SSID, AP_PASS);
  if(!WiFi.AP.waitStatusBits(ESP_NETIF_STARTED_BIT, 1000)){
    Serial.println("Failed to start AP!");
    return;
  }
  
  WiFi.begin(STA_SSID, STA_PASS);
}

void loop() {
  delay(20000);
}

void onEvent(arduino_event_id_t event, arduino_event_info_t info) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_START:
      Serial.println("STA Started");
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("STA Connected");
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("STA Got IP");
      Serial.println(WiFi.STA);
      WiFi.AP.enableNAPT(true);
      break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
      Serial.println("STA Lost IP");
      WiFi.AP.enableNAPT(false);
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("STA Disconnected");
      WiFi.AP.enableNAPT(false);
      break;
    case ARDUINO_EVENT_WIFI_STA_STOP:
      Serial.println("STA Stopped");
      break;

    case ARDUINO_EVENT_WIFI_AP_START:
      Serial.println("AP Started");
      Serial.println(WiFi.AP);
      break;
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
      Serial.println("AP STA Connected");
      break;
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
      Serial.println("AP STA Disconnected");
      break;
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
      Serial.print("AP STA IP Assigned: ");
      Serial.println(IPAddress(info.wifi_ap_staipassigned.ip.addr));
      break;
    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
      Serial.println("AP Probe Request Received");
      break;
    case ARDUINO_EVENT_WIFI_AP_STOP:
      Serial.println("AP Stopped");
      break;
      
    default:
      break;
  }
}
