/*
  @file getDHCPandDNS.ino
  @brief This demo does web requests via DHCP and DNS lookup.
  @detail This demo does web requests via DHCP and DNS lookup.

  Useful links:
   
  * About VEGA Processors: https://vegaprocessors.in/
  * About Development board: https://vegaprocessors.in/devboards/
  * Blogs : https://vegaprocessors.in/blog/
  
   
  *** The ENC28J60 Ethernet Module ***
  Connections:
  Ethernet Module     Aries Board
  VCC              -   3.3V
  GND              -   GND
  SO               -   MISO-1
  SI               -   MOSI-1
  SCK              -   SCLK-1
  CS               -   GPIO-10
*/

#include <EtherCard.h>
#include <SPI.h>
SPIClass SPI(1);
#define REQUEST_RATE 5000 // milliseconds

// ethernet interface mac address
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
// remote website name
const char website[] PROGMEM = "www.google.com";

byte Ethernet::buffer[700];
static long timer;

// called when the client request is complete
static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.print(millis() - timer);
  Serial.println(" ms");
  Serial.println((const char*) Ethernet::buffer + off);
}

void setup () {
  delay(1000);
  Serial.begin(115200);
  Serial.println("\n[getDHCPandDNS]");

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println( "Failed to access Ethernet controller");

  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");

  ether.printIp("My IP: ", ether.myip);
  // ether.printIp("Netmask: ", ether.mymask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);

  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
  ether.printIp("Server: ", ether.hisip);

  timer = - REQUEST_RATE; // start timing out right away
}

void loop () {

  ether.packetLoop(ether.packetReceive());

  if (millis() > timer + REQUEST_RATE) {
    timer = millis();
    Serial.println("\n>>> REQ");
    ether.browseUrl(PSTR("/foo/"), "bar", website, my_result_cb);
  }
}
