# IRsensor_thingspeak_ethernetshield
Simple arduino program to detect object from IR sensor and send 0 or 1 based on detection to ThingSpeak channel via EthernetShield
Connect arduino to ethernet shield, connect IR sensor to the shield and give digital out of the sensor to D5(change if you want in the program) on board.
Make sure you have installed latest version of Ethernet.h AND Thingspeak.h libraries.
Upload and wait 20 seconds to recieve channel updates.
