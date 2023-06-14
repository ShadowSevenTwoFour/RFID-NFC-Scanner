#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// WiFi Login Info
const char* ssid = "yourWifiName";
const char* password = "yourWifiPassword";

// Create A HTTP Client Instance.
HTTPClient http;

// Host To Get Data From.
const char* host= "http://thehouseofdeath.com/arduino3readscript.php";

void setup() {

  // Start The Serial Monitor & Try To Connect.
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Wait For The WiFi To Connect.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting...");
  }
  delay(3000);

  // Let the user know the WiFi connected and the address of the board.
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Send An HTTP GET Request.
  http.begin(host);
  int httpCode = http.GET();
  String propStatus = http.getString(); // get data from webhost continously

  // Just For Debugging.
  Serial.print(propStatus);

  // If A 1 Is Returned, Activate The Relay.
  if(propStatus == "1"){
      digitalWrite(relayPin, HIGH);
  }

  // If A 0 Is Returned, Make Sure The Relay Is Off.
  else if(propStatus == "0"){
    digitalWrite(relayPin, LOW);
  }

  // Wait 500 milliseconds before sending another request.
  delay(500);

  // End the HTTP Session.
  http.end();

}