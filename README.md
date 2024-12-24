# ESP8285_WebRemoteControl

This project implements a web-based remote control for an ESP8285 microcontroller. It allows you to control two output pins (PIN_A and PIN_B) via a web interface.

## Features

-   **Dual WiFi Mode:** The ESP8285 operates in both Access Point (AP) and Station (STA) modes. It creates its own WiFi network and connects to an existing WiFi network.
-   **Web Server:** Hosts a web server on port 80, allowing control via HTTP requests.
-   **Pin Control:** Controls two output pins (PIN_A and PIN_B) based on HTTP POST requests.

## Setup

1.  **Configure WiFi Credentials:**
    -   Set the `Wifi_ssid` and `Wifi_password` variables to your existing WiFi network credentials.
    -   Set the `Apssid` and `Appassword` variables for the ESP8285's access point.
2.  **Upload Code:** Upload the `ESP8285_WebRemoteControl.ino` code to your ESP8285 board using the Arduino IDE.
3.  **Connect to WiFi:**
    -   The ESP8285 will connect to your specified WiFi network.
    -   It will also create a WiFi access point with the specified `Apssid` and `Appassword`.
4.  **Access Web Interface:**
    -   Connect to the ESP8285's access point or your existing WiFi network.
    -   Open a web browser and navigate to the IP address of the ESP8285.

## Usage

-   Send HTTP POST requests to `/process` with the following parameters to control the pins:
    -   `A_On=1&B_On=0`: Sets PIN_A HIGH and PIN_B LOW.
    -   `A_On=0&B_On=1`: Sets PIN_A LOW and PIN_B HIGH.
    -   Any other combination will result in a 400 error.

## Pin Definitions

-   `PIN_A`: GPIO0
-   `PIN_B`: GPIO2

## Dependencies

-   ESP8266WiFi library
