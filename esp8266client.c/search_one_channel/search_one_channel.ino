
/*
 * NativeSdk by Simon Peter
 * Access functionality from the Espressif ESP8266 SDK
 * This example code is in the public domain
 * 
 * This is for advanced users.
 * Note that this makes your code dependent on the ESP8266, which is generally
 * a bad idea. So you should try to use esp8266/Arduino functionality
 * where possible instead, in order to abstract away the hardware dependency.
 */

// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
#include "c_types.h"
#include "osapi.h"
}
#endif

void setup() {
  Serial.begin(115200);
}

static  void  ICACHE_FLASH_ATTR scan_done(void *arg, STATUS  status){
  // method call after scanning is finished
    struct  bss_info  *bss_link = (struct bss_info  *)arg;
    bss_link = bss_link->next.stqe_next;  //ignore the first one , it's invalid.
    
    while (bss_link != NULL)
    {
      Serial.println("FOUND:");
      Serial.println((char*)bss_link->ssid);
      Serial.println("");
      bss_link = bss_link->next.stqe_next;
    }
}

void loop() {
  // Call Espressif SDK functionality - wrapped in ifdef so that it still
  // compiles on other platforms
#ifdef ESP8266
  scan_config scan = {
      NULL,
      NULL,
      6,
      false
  };
  
  wifi_station_scan(&scan, scan_done);
#endif
  delay(1000);
}
