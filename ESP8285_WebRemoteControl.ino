#include <ESP8266WiFi.h>               //Wifi library of esp8266 to access HARDWARRE APIS and othe functionality
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Set WiFi channel
#define AP_CHANNEL 1
// Set AP to hidden
#define AP_HIDDEN true
// Set AP max clients
#define AP_MAX_CON 4

#define PIN_A 0
#define PIN_B 2

/* Set these to your Wifi credentials. */

const char*Wifi_ssid = "SSID";                // SSID of your Router OR mobile hotspot
const char*Wifi_password = "SSID_PASSWORD";    //  PASSWORD of your Router or Mobile hotspot see below example

const char *Apssid = "AP_SSID";         //give Accesspoint SSID, your esp's hotspot name 
const char *Appassword = "AP_PASSWORD";        //password of your esp's hotspot

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleLogin();
void handleNotFound();

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);               //to enable Serial Commmunication with connected esp8266 board
  delay(500);
  
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  WiFi.mode(WIFI_AP_STA);           //changing ESP9266 wifi mode to AP + STATION

  WiFi.softAP(Apssid, Appassword);  //Starting AccessPoint on given credential
  IPAddress myIP = WiFi.softAPIP();        //IP Address of our Esp8266 accesspoint(where we can host webpages, and see data)
  Serial.print("Access Point IP address: ");
  Serial.println(myIP);
  
  Serial.println("");

  delay(1500);
  Serial.println("connecting to Wifi:");
  Serial.println(Wifi_ssid);

  WiFi.begin(Wifi_ssid, Wifi_password);                  // to tell ESP8266 Where to connect and trying to connect
  while (WiFi.status() != WL_CONNECTED) {                // While loop for checking Internet Connected or not
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());            // successful Connection of ESP8266,
                                            // printing Local IP given by your Router or Mobile Hotspot,
                                           // Esp8266 connect at this IP
  Serial.println("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  Serial.println("");

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/process", HTTP_POST, handleProcess); // Call the 'handleProcess' function when a POST request is made to URI "/process"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");

  digitalWrite(PIN_A, LOW);
  digitalWrite(PIN_B, LOW);
}

void loop() {
  server.handleClient();                     // Listen for HTTP requests from clients
}

void handleRoot() {                          // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "Please send proper command.");
}

void handleProcess() {                      
  if(!server.hasArg("A_On") || !server.hasArg("B_On") 
      || server.arg("A_On") == NULL || server.arg("B_On") == NULL) { 
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  if(server.arg("A_On") == "1" && server.arg("B_On") == "0") {
    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);    
    server.send(200, "text/html", "Ok A_On");
  } 
  else if(server.arg("A_On") == "0" && server.arg("B_On") == "1") {
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, HIGH);
    server.send(200, "text/html", "Ok B_On");
  }
  else {
    server.send(400, "text/plain", "400: Invalid Request");
  }
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}