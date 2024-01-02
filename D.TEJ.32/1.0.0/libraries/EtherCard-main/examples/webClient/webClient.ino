/*
  @file webClient.ino
  @brief Demo using DHCP and DNS to perform a web client request.
  @detail Ping a remote server, also uses DHCP and DNS.

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

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "www.google.com";

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}

void setup () {
  delay(1000);
  Serial.begin(115200);
  Serial.println(F("\n[webClient]"));

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

#if 1
  // use DNS to resolve the website's IP address
  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
#elif 2
  // if website is a string containing an IP address instead of a domain name,
  // then use it directly. Note: the string can not be in PROGMEM.
  char websiteIP[] = "192.168.1.1";
  ether.parseIp(ether.hisip, websiteIP);
#else
  // or provide a numeric IP address instead of a string
  byte hisip[] = { 192,168,1,1 };
  ether.copyIp(ether.hisip, hisip);
#endif

  ether.printIp("SRV: ", ether.hisip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 5000;
    Serial.println();
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/foo/"), "bar", website, my_callback);
  }
}
