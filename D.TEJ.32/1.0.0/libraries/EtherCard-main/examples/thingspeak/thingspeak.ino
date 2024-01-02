/*
  @file thingspeak.ino
  @brief Simple demo for feeding some random data to Pachube.
  @detail Simple demo for feeding some random data to Pachube.

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
// change these settings to match your own setup
//#define FEED "000"
#define APIKEY "VGFJWLT1XCIKWUDZ" // put your key here

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
const char website[] PROGMEM = "api.thingspeak.com";
byte Ethernet::buffer[700];
uint32_t timer;
Stash stash;
byte session;

//timing variable
int res = 100; // was 0


void initialize_ethernet(void){
  for(;;){ // keep trying until you succeed
    //Reinitialize ethernet module
    //pinMode(5, OUTPUT);  // do notknow what this is for, i ve got something elso on pin5
    //Serial.println("Reseting Ethernet...");
    //digitalWrite(5, LOW);
    //delay(1000);
    //digitalWrite(5, HIGH);
    //delay(500);

    // Change 'SS' to your Slave Select pin, if you arn't using the default pin
    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0){
      Serial.println( "Failed to access Ethernet controller");
      continue;
    }

    if (!ether.dhcpSetup()){
      Serial.println("DHCP failed");
      continue;
    }

    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);
    ether.printIp("DNS: ", ether.dnsip);

    if (!ether.dnsLookup(website))
      Serial.println("DNS failed");

    ether.printIp("SRV: ", ether.hisip);

    //reset init value
    res = 180;
    break;
  }
}

void setup () {
  delay(1000);
  Serial.begin(115200);
  Serial.println("\n[ThingSpeak example]");

  //Initialize Ethernet
  initialize_ethernet();
}

void loop () {
  //if correct answer is not received then re-initialize ethernet module
  if (res > 220){
    initialize_ethernet();
  }

  res = res + 1;

  ether.packetLoop(ether.packetReceive());

  //200 res = 10 seconds (50ms each res)
  if (res == 200) {

    // Generate random info
    float demo = random(0,500);
    //word one = random(0,500);
    char* msje;

    if (demo < 250){
      msje = "low";
    }
    else{
      msje = "high";
    }

    // generate two fake values as payload - by using a separate stash,
    // we can determine the size of the generated message ahead of time
    // field1=(Field 1 Data)&field2=(Field 2 Data)&field3=(Field 3 Data)&field4=(Field 4 Data)&field5=(Field 5 Data)&field6=(Field 6 Data)&field7=(Field 7 Data)&field8=(Field 8 Data)&lat=(Latitude in Decimal Degrees)&long=(Longitude in Decimal Degrees)&elevation=(Elevation in meters)&status=(140 Character Message)
    byte sd = stash.create();
    stash.print("field1=");
    stash.print(demo);
    //stash.print("&field2=");
    //stash.print(one);
    //stash.print("&field3=");
    //stash.print(msje);
    stash.save();

    //Display data to be sent
    Serial.println(demo);


    // generate the header with payload - note that the stash size is used,
    // and that a "stash descriptor" is passed in as argument using "$H"
    Stash::prepare(PSTR("POST /update HTTP/1.0" "\r\n"
      "Host: $F" "\r\n"
      "Connection: close" "\r\n"
      "X-THINGSPEAKAPIKEY: $F" "\r\n"
      "Content-Type: application/x-www-form-urlencoded" "\r\n"
      "Content-Length: $D" "\r\n"
      "\r\n"
      "$H"),
    website, PSTR(APIKEY), stash.size(), sd);

    // send the packet - this also releases all stash buffers once done
    session = ether.tcpSend();

 // added from: http://jeelabs.net/boards/7/topics/2241
 int freeCount = stash.freeCount();
    if (freeCount <= 3) {   Stash::initMap(56); }
  }

   const char* reply = ether.tcpReply(session);

   if (reply != 0) {
     res = 0;
     Serial.println(F(" >>>REPLY recieved...."));
     Serial.println(reply);
   }
   delay(300);
}
