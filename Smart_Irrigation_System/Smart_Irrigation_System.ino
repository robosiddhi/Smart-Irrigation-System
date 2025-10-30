/*
Code Name: Smart Irrigation System
Author: RoboSiddhi

⚠ Warning

This project and its code are shared for learning and personal use only.  
Commercial use, redistribution, or selling (in any form) of this code or
project is not allowed without proper permission.  

                                                                                 .                 
              !^           .   ..   ..            
              ??^~~~^.      ....:....             
             :P5J?7?JY5.   ...^:::^..             
            .BG5JY75&JYG   ...^:::^..             
            .BBBP57?YYYG.   ....::::              
             :YBBGYJ??Y?   .  .^ YGGY.            
              :!BBBBY!:       .G??5BP^            
            ~GP5P5??77!7:    .^J55Y!              
           ^#57!7#5777!?57~:~77JG~                
           ?#G5PB#57777!B5GG5YPJ.                 
          .BGYY&&BPY???J!!Y5Y7:                   
          :7!~!7777!!!!^     
                               
Description: This is an smart irrigation system.Which use Arduino to collect data
from the soil sensor and the microcontroller provides signal to the relay and
the water pump starts to irrigate plants.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#define SOIL_PIN A0
#define RELAY_PIN 7

int threshold = 500;

bool pumpRunning = false;
unsigned long pumpStartTime = 0;
const unsigned long pumpMaxRunTime = 15000; // 15 sec
const unsigned long earlyStopCheck = 5000;  // 5 sec early stop window

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Smart Pump Control Started ✅");
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);
  Serial.print("Soil: ");
  Serial.println(soilValue);

  // ✅ Pump ON only when dry and currently OFF
  if (soilValue > threshold && !pumpRunning) {
    digitalWrite(RELAY_PIN, HIGH);
    pumpRunning = true;
    pumpStartTime = millis();
    Serial.println("Soil Dry → Pump ON 💧");
  }

  // ✅ If pump is ON → check stopping conditions
  if (pumpRunning) {

    // Soil becomes wet within 5 sec → immediate OFF ✅
    if (soilValue <= threshold && (millis() - pumpStartTime) < earlyStopCheck) {
      digitalWrite(RELAY_PIN, LOW);
      pumpRunning = false;
      Serial.println("Soil Wet quickly → Pump OFF ✅");
    }

    // Max 15 sec run time completed → OFF ✅
    else if (millis() - pumpStartTime >= pumpMaxRunTime) {
      digitalWrite(RELAY_PIN, LOW);
      pumpRunning = false;
      Serial.println("Pump 15 sec completed → OFF ✅");
    }
  }

  delay(200);
}
