#define ADC_PIN A0
#define NUM_VALS 30

int val;

int prevVal = 0;

int outputPin = 8;

bool outOn = false;

int sum = 0;
int vals[NUM_VALS];
int index = 0;

void setup() {
	Serial.begin(115200);
	pinMode(outputPin, OUTPUT);
	digitalWrite(outputPin, LOW);
	for(int i = 0; i < NUM_VALS; i++){
		vals[i] = 0;
	}
}

void loop() {
	vals[index] = analogRead(ADC_PIN);
	index++;
	if(index >= NUM_VALS){
		index = 0;
	}
	sum = 0;
	for(int i = 0; i < NUM_VALS; i++){
		sum += vals[i];
	}
	val = sum / NUM_VALS;

	if (abs(prevVal - val) > 2) {
		//int sendVal = map(val, 300, 750, 0, 1023);
		//sendVal = constrain(sendVal, 0, 1023);
		Serial.println(val);
		prevVal = val;
		if (val > 360 && !outOn) {
			digitalWrite(outputPin, HIGH);
			outOn = true;
		}
		if (val < 300 && outOn)
		{
			digitalWrite(outputPin, LOW);
			outOn = false;
		}
	}
	delay(30);

}
