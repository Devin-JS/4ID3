// Libraries
#include <TheThingsNetwork.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//  Macros
#define DHTPIN 2
#define DHTTYPE DHT11
#define POLLING_PERIOD 2000
#define GROUP_NAME "Group4"
#define DEVICE_NAME "Device4"

DHT_Unified dht(DHTPIN, DHTTYPE);
#define lora_serial Serial1
#define debug_serial Serial

// Set your AppEUI and AppKey
#define FREQUENCY_PLAN TTN_FP_US915
const char *app_eui = "0000000000000001";
const char *app_key = "DA289E0E22BF76349FAC6703A55C0DA8";
TheThingsNetwork ttn(lora_serial, debug_serial, FREQUENCY_PLAN);

unsigned long start_time = millis();