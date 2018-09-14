#include "bb_Generator.h"
#include "FastLED.h"

#define NUM_LEDS 10


#define BB_5V 2
#define BB_14V 3

#define LED_PIN 4

CRGB leds[NUM_LEDS];


bb_Generator cap(A0);
bb_Generator battery(A1);
//bb_Generator bike1(A2);
//bb_Generator bike2(A3);

bool outOn = false;

void setup() {

	pinMode(BB_5V, OUTPUT);
	pinMode(BB_14V, OUTPUT);

	digitalWrite(BB_5V, LOW);
	digitalWrite(BB_14V, LOW);

	cap.setNumReadings(30);
	cap.setEnergyDecrement(0);
	cap.setDiff(2);
	cap.setLowCutoff(0);
	cap.begin();


	battery.setLowCutoff(0);
	battery.begin();

	FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);


	Serial.begin(115200);
	Serial.println("s,");

}

void loop() {

	cap.update();
	battery.update();

	if (cap.getVoltage() > 5) {
		digitalWrite(BB_5V, HIGH);
	}
	if (cap.getVoltage() < 4.5) {
		digitalWrite(BB_5V, LOW);
	}

	if(cap.hasChanged()){
		Serial.print("c,");
		Serial.println(cap.getVoltage());
		if(cap.getVoltage() > 9.8 && !outOn){
			digitalWrite(BB_14V, HIGH);
			outOn = true;
		}
		if(cap.getVoltage() < 5 && outOn){
			digitalWrite(BB_14V, LOW);
			outOn = false;
		} 

		
	}
	delay(30);

}
