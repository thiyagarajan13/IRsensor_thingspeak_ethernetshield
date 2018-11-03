/*
  WriteSingleField 
  
  Description:Takes input from IRsensor and sends 0 or 1 to field based on detections  [Writes a value to a channel on ThingSpeak every 20 seconds].
  
  Hardware: Arduino Ethernet
  Note:
  - Requires the Ethernet library
  
*/


#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 4); //type ipconfig in cmd and enter your LAN/WLAN ip address
IPAddress myDns(192, 168, 1, 1); // type ipconfig in cmd and enter your default GATEWAY address here

EthernetClient client;

unsigned long myChannelNumber = <YOUR_CHANNEL_NUMBER>; //enter your channel number here
const char * myWriteAPIKey = "XXXXXXXXXXXXX"; // enter write api key here

int number = 0;

void setup() {
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
    
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  int number=0;
  isObstacle = digitalRead(5);
  if (isObstacle == HIGH)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    number=1;
  }
  else
  {
    Serial.println("clear");
    number=0;
  }
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey); //mention which field you want to write to
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  
  delay(20000); // Wait 20 seconds to update the channel again
}
