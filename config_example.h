/*
 * Configuration:
 * L1 RGB or White
 * if white: only one Channel can be used
 * if RGB_ CH1-3 will be used for RGB PWM
 * of RGBW pwm channel 4 is used for white output.  
 * 
 * L2 RGB or White
 * if white: CH4 will be used as white channel
 * if RGB CH4 - CH6 will be used for RGB PWM output
 * 
 * L3-L4: white only
 * can only be used when L2 is NOT RGB
 * corrosponding PWM Channels will be used
 */
#define MASTER_NAME "example"
 
#define L1_NAME "rgb1"
//#define CH1_RGBW
#define CH1_RGB
//#define CH1_SINGLE 

#define L2_NAME "white1"
//#define CH2_RGB
#define CH2_SINGLE


#define L3_NAME "white2"
//#define CH3_SINGLE

#define L4_NAME "white3"
//#define CH4_SINGLE
/////////////////////////////////////////////////////////////////////////////////////////////////
/*Serial LEDs
 * 
 */

//uncomment for serial LED function

//#define SERIAL_LED 

#define SECTION_PREFIX "section_"
const int data_pin = 26;         
//where is the Dataline attachted to: Pin 26
#define SERIAL_COUNT 2 //Number of Sections
#define SERIAL_LEDS 2 //Number of ALL LEDs in the stripe   
//#define SERIAL_LEDS 300    
//should be the sum of all sections
uint8_t section_count[SERIAL_COUNT] = {1,1}; //LED count per Section

boolean subscribe_sections = true; //should the sections be subscribed as individual lights ?


/*
 * Network configuration
 * Change SSID and Password according to your network
 */
#include "credentials_example.h"
const char* WIFI_SSID = SECRET_WIFI_SSID;
const char* WIFI_PASSWORD = SECRET_WIFI_PASSWORD;
#define AP_NAME "ESP32_Kombilampe"
//#define AP_PASS "ESP32"

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "example";
const PROGMEM char* MQTT_SERVER_IP = "192.168.178.2"; //change for your server
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = SECRET_MQTT_USER;
const PROGMEM char* MQTT_PASSWORD = SECRET_MQTT_PASSWORD;


long changetime = 500; //How long will the fading take
/////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Configuration of PWM:
 * Resolution can be changed according to ESP32 output
 * Frequency can be changedd according to ESP32 
 * PIN config: See Layout
 */

#define RESOLUTION 12
#define FREQUENCY 20000
#define MQTT_RETRY 2000
#define WIFI_RETRY 5000
#define PIN_CH_0 12 
#define PIN_CH_1 14 
#define PIN_CH_2 13 
#define PIN_CH_3 27
#define PIN_CH_4 26
#define PIN_CH_5 25
const PROGMEM char* LIGHT_ON = "ON";
const PROGMEM char* LIGHT_OFF = "OFF";
#define START_RED 4095
#define START_GREEN 1968
#define START_BLUE 288
#define START_WHITE 1024


const PROGMEM char* SUNRISE = "sunrise";
#define SUNRISE_RED 4095
#define SUNRISE_GREEN 1968
#define SUNRISE_BLUE 288
#define SUNRISE_WHITE 4095
#define SUNRISE_TIME_S 900

//order: MQTT_PREFEIX + NAME + MQTT_FUNCTIONs
const PROGMEM char* MQTT_PREFIX = "/light/example"; //Will be used as Prefix

//global commands
const PROGMEM char* MQTT_GLOBAL = "global"; //for global commands (sunrise)
char MQTT_LIGHT_GLOBAL_TOPIC[128];

//Functions:
const PROGMEM char* MQTT_LIGHT_SWITCH = "/switch";
const PROGMEM char* MQTT_LIGHT_STATE = "/state";

const PROGMEM char* MQTT_BRIGHTNESS_STATE = "/brightness/state";
const PROGMEM char* MQTT_BRIGHTNESS_SET = "/brightness/set";
const PROGMEM char* MQTT_WHITE_STATE = "/white/state";
const PROGMEM char* MQTT_WHITE_SET = "/white/set";
const PROGMEM char* MQTT_RGB_STATE = "/rgb/state";
const PROGMEM char* MQTT_RGB_SET = "/rgb/set";
const PROGMEM char* MQTT_EFFECT_STATE = "/effect/state";
const PROGMEM char* MQTT_EFFECT_SET = "/effect/set";

/*Channel 1: RGB
 * PWM Channel 1-3 will be set together to one RGB-Light
 */
/////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(CH1_RGB) || defined(CH1_RGBW)
char MQTT_LIGHT_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH1[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH1[128];
// colors (rgb)
char MQTT_LIGHT_RGB_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_RGB_COMMAND_TOPIC_CH1[128];
// Effects
char MQTT_LIGHT_EFFECT_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_EFFECT_COMMAND_TOPIC_CH1[128];
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH1_RGBW
//white
char MQTT_LIGHT_WHITE_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_WHITE_COMMAND_TOPIC_CH1[128];
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////

//Channel 2: RGB
// PWM Channel 4-6 will be set together to one RGB-Light
//
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH2_RGB
char MQTT_LIGHT_STATE_TOPIC_CH2[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH2[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH2[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH2[128];

// colors (rgb)
char MQTT_LIGHT_RGB_STATE_TOPIC_CH2[128];
char MQTT_LIGHT_RGB_COMMAND_TOPIC_CH2[128];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

//Channel 1: SINGLE
// Only Channel X will be used.
//
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH1_SINGLE
char MQTT_LIGHT_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH1[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH1[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH1[128];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH2_SINGLE
char MQTT_LIGHT_STATE_TOPIC_CH2[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH2[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH2[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH2[128];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH3_SINGLE
char MQTT_LIGHT_STATE_TOPIC_CH3[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH3[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH3[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH3[128];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CH4_SINGLE
char MQTT_LIGHT_STATE_TOPIC_CH4[128];
char MQTT_LIGHT_COMMAND_TOPIC_CH4[128];

// brightness
char MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC_CH4[128];
char MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC_CH4[128];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef SERIAL_LED
char MQTT_LIGHT_SERIAL_STATE_TOPIC[128];
char MQTT_LIGHT_SERIAL_COMMAND_TOPIC[128];

// brightness
char MQTT_LIGHT_SERIAL_BRIGHTNESS_STATE_TOPIC[128];
char MQTT_LIGHT_SERIAL_BRIGHTNESS_COMMAND_TOPIC[128];
//white
char MQTT_LIGHT_SERIAL_WHITEIC[128];
char MQTT_LIGHT_SERIAL_WHITE_COMMAND_TOPIC[128];
// colors (rgb)
char MQTT_LIGHT_SERIAL_RGB_STATE_TOPIC[128];
char MQTT_LIGHT_SERIAL_RGB_COMMAND_TOPIC[128];
// Effects
char MQTT_LIGHT_SERIAL_EFFECT_STATE_TOPIC[128];
char MQTT_LIGHT_SERIAL_EFFECT_COMMAND_TOPIC[128];

//Channels for Sections
char MQTT_LIGHT_SERIAL_SECTION_STATE_TOPIC[SERIAL_COUNT][128];
char MQTT_LIGHT_SERIAL_SECTION_COMMAND_TOPIC[SERIAL_COUNT][128];

// brightness
char MQTT_LIGHT_SERIAL_SECTION_BRIGHTNESS_STATE_TOPIC[SERIAL_COUNT][128];
char MQTT_LIGHT_SERIAL_SECTION_BRIGHTNESS_COMMAND_TOPIC[SERIAL_COUNT][128];
// white
char MQTT_LIGHT_SERIAL_SECTION_WHITE_STATE_TOPIC[SERIAL_COUNT][128];
char MQTT_LIGHT_SERIAL_SECTION_WHITE_COMMAND_TOPIC[SERIAL_COUNT][128];
// colors (rgb)
char MQTT_LIGHT_SERIAL_SECTION_RGB_STATE_TOPIC[SERIAL_COUNT][128];
char MQTT_LIGHT_SERIAL_SECTION_RGB_COMMAND_TOPIC[SERIAL_COUNT][128];
// Effects
char MQTT_LIGHT_SERIAL_SECTION_EFFECT_STATE_TOPIC[SERIAL_COUNT][128];
char MQTT_LIGHT_SERIAL_SECTION_EFFECT_COMMAND_TOPIC[SERIAL_COUNT][128];
#endif
