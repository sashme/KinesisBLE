#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "keycodes.h"
#include "keymap.h"
#include "bluetooth.h"
#include "battery.h"
#include "button.h"
#include "Adafruit_MCP23017.h"

#define ROWS 15
#define COLS 7

#define DEBOUNCING_DELAY 10

uint8_t col_pins[COLS] = COL_PINS;
uint8_t row_pins[ROWS] = ROW_PINS;

uint8_t prev_states[ROWS] = { 0 };
uint8_t curr_states[ROWS] = { 0 };
uint8_t temp_states[ROWS] = { 0 };
uint8_t debouncing = DEBOUNCING_DELAY;

inline
state_t get_state(uint8_t row, uint8_t col) {
  return (curr_states[row] >> (col)) & 1;
}

const int baudrate = 115200;

Adafruit_MCP23017 mcp;

/**
 * Battery LED on time
 */
bool  batteryLedOn = false; 
int   batteryLedTimer = 0;
int   batteryOnTime = 900000;             // Keep battery LEDs on for 5 minutes each time.

/**
 * Timestamp of last key press activity. Used to
 * check if keyboard can go into deep-sleep.
 */
int lastKeyActivityTimer = 0;
int idleBeforeSleepTime = 60000;                   // 15 minutes

void setup(void) {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  mcp.begin();

  Serial.begin(baudrate);
  
  init_bluetooth();

  for (uint8_t row = 0; row < ROWS; row++) {
    mcp.pinMode(row_pins[row], OUTPUT);
    mcp.digitalWrite(row_pins[row], HIGH);
  }
  
  for (uint8_t col = 0; col < COLS; col++) {
    pinMode(col_pins[col], INPUT_PULLUP);
    digitalWrite(col_pins[col], HIGH);
  }


//  Serial.print("Ready");

  pinMode(LED_CAPS_PIN, OUTPUT);
  pinMode(LED_NUM_PIN, OUTPUT);
  pinMode(LED_SCR_PIN, OUTPUT);
  pinMode(LED_KEY_PIN, OUTPUT);

  showBatteryLevel();
}


void loop(void) {

  if (batteryLedOn && ((millis() - batteryLedTimer) > batteryOnTime)) {
    turnOffBatteryLed();
  }
   
    
   /**
    * Power Button LED
    */
    int UsbMv = readUSB();

    if(UsbMv < 1000) {
      buttonColor(BLUE);                        // USB NOT CONNECTED
    } else {
      if(UsbMv >= 5000) {
        buttonColor(GREEN);                     // FULL
      } else {
        buttonColor(ORANGE);                    // CHARGING
      }
    }
    
   
  for (uint8_t row = 0; row < ROWS; row++) {
    
    uint8_t row_read = 0;

    /**
     * Pull current row to low as columns are set to INPUT_PULLUP.
     * The alternative would be to wire pulldown resistors.
     */

    mcp.digitalWrite(row_pins[row], LOW);                  
  
    delayMicroseconds(30);

    /**
     * Loop through each column on each row to check to see if a key
     * was pressed. The column pin will read LOW too if a key 
     * switch is down.
     */
    for (uint8_t col = 0; col < COLS; col++) {            
      if (digitalRead(col_pins[col]) == LOW) {            
        
        /**
         * Turn first bit into 1 and shift left by column number.
         * If the 5th and 7th column of the row was pressed, 
         * row_read for the row would be 101000.
         */         
        row_read |= 1 << col;
        
      }
    }

    /**
     * Set Debouncing Delay
     * Every new row_read needs to be the same (stored in temp_states)
     * for DEBOUNCING_DELAY amount of time. ie. Prevent the row
     * states from rapidly changing.
     */
    if (temp_states[row] != row_read) {
      temp_states[row] = row_read;          
      debouncing = DEBOUNCING_DELAY;        
    }
    
    mcp.digitalWrite(row_pins[row], HIGH);
    
  }

  /**
   * Update States
   * If debouncing delay is up and the states are still the same, 
   * then go ahead and store the new states to be processed.
   */
  if (debouncing) {
    if (--debouncing) {
      delay(1);          
    } else {
      for (uint8_t row = 0; row < ROWS; row++) {
        prev_states[row] = curr_states[row];
        curr_states[row] = temp_states[row];
      }
    }
  }

  /**
   * Compare Row States
   * Check to see if anything has changed and subsequently handle
   * the change.
   */
  for (uint8_t row = 0; row < ROWS; row++) {

    if (curr_states[row] == prev_states[row]) {
      continue;
    }

    for (uint8_t col = 0; col < COLS; col++) {
      
      // shift right to look at current column, then bitwise & 1 which
      // ignores columns to the left and checks to see if state is a
      // 1 or 0.

      /**
       * Check Each Column
       * Examines each bit to see if the state is a 0 or a 1. Shift
       * right by column index to get current column and & 1 to
       * ignore all bits to the left.
       */
      state_t curr = (curr_states[row] >> col) & 1;       
      state_t prev = (prev_states[row] >> col) & 1;
      
      if (curr != prev) {
        handle_keychange(row, col, curr);
        prev_states[row] ^= (uint16_t)1 << col;
        lastKeyActivityTimer = millis();                    // Update last activity timer to prevent sleep
        goto END_OF_LOOP;                                   // Handle 1 key change at a time
      }
    }
    
  }

  END_OF_LOOP:;

  if( (millis() - lastKeyActivityTimer) > idleBeforeSleepTime) {
    keyboardShutdown();
  }

  waitForEvent();
  
}

/**
 * Read battery and update Kinesis LEDs
 * 
 */
void showBatteryLevel() {
   uint8_t battery = batteryPercentage();
   if(battery > 75) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, HIGH);
    digitalWrite(LED_KEY_PIN, HIGH);
   } else if (battery > 50) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, HIGH);
    digitalWrite(LED_KEY_PIN, LOW);
   } else if (battery > 25) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   } else {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, LOW);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   }
   batteryLedOn = true;
   batteryLedTimer = millis();
}

/**
 * Turns off all battery level
 * indicator LEDs.
 */
void turnOffBatteryLed() {
    digitalWrite(LED_CAPS_PIN, LOW);
    digitalWrite(LED_NUM_PIN, LOW);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
}

/**
 * Deep-sleep (max power saving)
 * Enter this mode if keyboard has been idle for
 * some time.
 */
void keyboardShutdown() {

  digitalWrite(LED_BUILTIN, LOW);
  buttonColor(OFF);       // Power button LED
  turnOffBatteryLed();    // Battery indicator LEDs
  
  
  // Loop through columns and pull them down
  for (uint8_t col = 0; col < COLS; col++) {
    pinMode(col_pins[col], INPUT_PULLDOWN);
    NRF_GPIO->PIN_CNF[col_pins[col]] |= ((uint32_t) GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);
  }

  uint8_t sd_en;
  (void) sd_softdevice_is_enabled(&sd_en);

  // Enter System OFF state
  if ( sd_en )
  {
    sd_power_system_off();
  }else
  {
    NRF_POWER->SYSTEMOFF = 1;
  }
}

