// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup() {
  delay(1000);
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(2000);             // Bits per sec

  vw_rx_start();  // Start the receiver PLL running

  pinMode(led_pin, OUTPUT);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))  // Non-blocking
  {
    int i;

    digitalWrite(led_pin, HIGH);  // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");

    for (i = 0; i < buflen; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
    digitalWrite(led_pin, LOW);
  }
}
