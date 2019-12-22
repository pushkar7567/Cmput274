#include "Arduino.h"

//Declaring LED pins in global scope
int ledPin[5] = {9, 10, 11, 12 ,13};

//Setup function
void setup() {
	init();
	Serial.begin(9600);

	//For loop for declaring OUTPUT pinmodes for all pins
	for(int i=0; i<5; i++){
		pinMode(ledPin[i], OUTPUT);
	}

}

//This function finds out the value of incrementation as each key is pressed
int8_t getHexValue(char digit){
	int value;
	//Case for numbers 0-9
	if (int(digit)>=48 and int(digit)<=57){
		value = int(digit)-48;
		return value;
	}

	//Case for all uppercase letters
	else if (int(digit)>=65 and int(digit)<=70){
		value = int(digit)-55;
		return value;
	}

	//Case of all lowercase hexadecimal letters
	else if (int(digit)>=97 and int(digit)<=102){
		value = int(digit)-87;
		return value;
	}

	//Case if invalid key is pressed
	else {
		return -1;
	}


}

//This function updates the LED's based on the binary number
void updateLEDs(uint8_t total){
 	int i;

 	//Runs a for loop to check weather the most significant bit is 1 or 0
 	for(i=0; i<=5; i++){
 		if (total & 1){
 			digitalWrite(ledPin[i], HIGH);		
 		}

 		else{
 			digitalWrite(ledPin[i], LOW);
 		}

 		total >>= 1;
 	}	
	
}


//Main function runs as soon as the program is executed
int main(){
	uint8_t total =0;
	uint8_t value;
	setup();
	while (true){
		//Checking if user gives an input in the serial moniter
		if (Serial.available() > 0){
			char digit = Serial.read();
			//In case user enters a space or return character
			if (digit==32 or digit==13){
				total = 0;
			}
			//In case user gives any other valid key
			else{
			value = getHexValue(digit);
			total = total+value;
			}
			updateLEDs(total);
		}
	}
	return 0;	
}