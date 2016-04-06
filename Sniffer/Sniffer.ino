/*
 * Sniffing for WiFi packages in the air. 
 * This code is in the public domain.
 */

// Include ticker for frequently executing functions
#include <Ticker.h>

// External library files of Espressif SDK
extern "C" {
#include "user_interface.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "mem.h"
#include "user_config.h"
}

// Delay times
// Delay of loop function in milli seconds
# define __delay__ 10
// Delay of channel changing in seconds
# define __dlay_ChannelChange__ 0.5

//Ticker for channel hopping
Ticker ts; 

//Promiscuous callback structures for storing package data, see Espressif SDK handbook
struct RxControl {
    signed rssi:8;
    unsigned rate:4;
    unsigned is_group:1;
    unsigned:1;
    unsigned sig_mode:2;
    unsigned legacy_length:12;
    unsigned damatch0:1;
    unsigned damatch1:1;
    unsigned bssidmatch0:1;
    unsigned bssidmatch1:1;
    unsigned MCS:7;
    unsigned CWB:1;
    unsigned HT_length:16;
    unsigned Smoothing:1;
    unsigned Not_Sounding:1;
    unsigned:1;
    unsigned Aggregation:1;
    unsigned STBC:2;
    unsigned FEC_CODING:1;
    unsigned SGI:1;
    unsigned rxend_state:8;
    unsigned ampdu_cnt:8;
    unsigned channel:4;
    unsigned:12;
};
struct LenSeq {
    uint16_t length;
    uint16_t seq;
    uint8_t  address3[6];
};
struct sniffer_buf {
    struct RxControl rx_ctrl;
    uint8_t buf[36];
    uint16_t cnt;
    struct LenSeq lenseq[1];
};
struct sniffer_buf2{
    struct RxControl rx_ctrl;
    uint8_t buf[112];
    uint16_t cnt;
    uint16_t len;
};

// Function for printing the MAC adress i of the MAC header
void printMAC(uint8_t *buf, uint8 i)
{
Serial.printf("\t%02X:%02X:%02X:%02X:%02X:%02X", buf[i+0], buf[i+1], buf[i+2], buf[i+3], buf[i+4], buf[i+5]);
}

// Promiscuous callback function: is executed whenever package is received by ESP 8266
void promisc_cb(uint8_t *buf, uint16_t len)
{
    uint8_t* buffi;
    if ((len == 12)){
        return; // Nothing to do for this package, see Espressif SDK documentation.
    }
    if (len == 12){
        return;
    }
    else if (len == 128) {
        struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
        buffi=sniffer->buf;
    } 
     else {
        struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
        buffi=sniffer->buf;
    }
    Serial.printf("Channel %3d: Package Length %d", wifi_get_channel(), len); 
    printMAC(buffi,  4); // Print address 1
    printMAC(buffi, 10); // Print address 2
    printMAC(buffi, 16); // Print address 3
    if((bitRead(buffi[1],7)==1)&&(bitRead(buffi[1],6)==1)) printMAC(buffi, 24); // Print address 4
    Serial.print(" "); 
    Serial.print(bitRead(buffi[1],7));
    Serial.print(bitRead(buffi[1],6));
    Serial.printf("\n");
}

// Change the WiFi channel
void channelCh(void) 
{ 
    // Change the channels by modulo operation
    uint8 new_channel = wifi_get_channel()%12 + 1; 
    Serial.printf("** Hop to %d **\n", new_channel); 
    wifi_set_channel(new_channel); 
} 

// Setup procedure
void setup() 
{
  // Set baudrate UART
  Serial.begin(115200); 
  // Sniffer works only in station mode
  wifi_set_opmode(STATION_MODE);
  // Set the promiscuous related options
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(promisc_cb);
  wifi_promiscuous_enable(1);
  Serial.printf("Setup done!");
  // Change the channel every 0.5 seconds, change for different frequency
  ts.attach(__dlay_ChannelChange__, channelCh);   
}

// Loop
void loop() 
{
  // Duration of loop defined by delay function: note that during delay the WiFi stack can process the date in the background and is waiting for WiFi packages 
  delay(__delay__);
}
