char charBuffer = ' ';
String stringBuffer = "";

String currentMessage = "";
int nextLetter = 0;

int startPin = 22;
int pinArray[26];
int pin = -1;
int numPins = 1;
int onTime = 1000;
int offTime = 100;

void setup(){

  Serial.begin(9600);

  for (int i=startPin; i <= startPin+26; i++){

    pinMode(i, OUTPUT);
    
  }

}

void loop(){

  if (Serial.available() > 0) {
    
    charBuffer = Serial.read();
    //Serial.print("I received char code: ");
    //Serial.println(int(charBuffer));

    if (charBuffer == 10) {

      processMessage(stringBuffer);
      stringBuffer = "";
    
    } else {

      stringBuffer = stringBuffer + charBuffer;
      
    }
    
  } else {

      pin = int(currentMessage[nextLetter])-97+startPin;

			if (pin >= startPin && pin <= startPin+26){

				numPins = 1;
				pinArray[numPins-1] = pin;

				nextLetter++;

				while (currentMessage[nextLetter] == ','){

					nextLetter++;
					pin = int(currentMessage[nextLetter])-97+startPin;

					if (pin >= startPin && pin <= startPin+26){
	
						numPins++;
						pinArray[numPins-1] = pin;
								
					}

					nextLetter++;
					if (nextLetter >= currentMessage.length()){nextLetter = 0;}

				}

			} else {

				numPins = 0;
				nextLetter++;

			}

			if (nextLetter >= currentMessage.length()){nextLetter = 0;}

			for (int i = 0; i < numPins; i++){digitalWrite(pinArray[i], HIGH);}
			delay(onTime);
			for (int i = 0; i < numPins; i++){digitalWrite(pinArray[i], LOW);}
			delay(offTime);

	}

}

void processMessage(String message){

  if (message[0] == '#'){

    Serial.println("Recieved command: " + message);

		if (message[1] == 'n'){

			onTime = message.substring(2, message.length()).toInt();
			if (onTime+offTime < 100){onTime = 1000;}
			Serial.println("On delay is now " + String(onTime) + " ms");

		} else if (message[1] == 'f'){

			offTime = message.substring(2, message.length()).toInt();
			if (offTime+onTime < 100){offTime = 100;}
			Serial.println("Off delay is now " + String(offTime) + " ms");

		}   
 
  } else {

		if (message[0] == ','){message=" ";}
    Serial.print("Changing message to: " + message);
	  currentMessage = message;
		if (currentMessage[message.length()] != ' '){currentMessage += " ";}		
		nextLetter = 0;    
    
  }

}
