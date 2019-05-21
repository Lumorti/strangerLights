char charBuffer = ' ';
String stringBuffer = "";

String currentMessage = "";
const int maxPresets = 10;
String savedMessages[maxPresets];
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

	savedMessages[0] = "";
	savedMessages[1] = "";
	savedMessages[2] = "";
	savedMessages[3] = "";
	savedMessages[4] = "";
	
	savedMessages[5] = "a,c,e,g,i,k,m,o,q,s,u,w,yb,d,f,h,j,l,n,p,r,t,v,x,z"; //half on
	savedMessages[6] = "akumeoyqgowmcksi"; // bouncing
	savedMessages[7] = "i,ra,j,sb,k,tc,l,ud,m,ve,n,wf,o,xg,p,yh,q,z"; //moving line
	savedMessages[8] = "a,b,c,lb,c,d,mc,d,e,nd,e,f,oe,f,g,pf,g,h,qs,t,k,u,f,g,h,qt,u,v,l,f,g,h,qu,v,w,m,f,g,h,qv,w,x,n,f,g,h,qw,x,y,o,f,g,h,qx,y,z,p,f,g,h,qh,za,j,s,k,h,zb,k,t,l,h,zc,l,u,m,h,zd,m,v,n,h,ze,n,w,o,h,zf,o,x,p,h,zg,p,y,h,q,z "; //tetris
	savedMessages[9] = "i,a,k,u,m,e,o,y,q r,j,b,l,v,n,f,p,z i,s,k,c,m,w,o,g,q j,t,l,d,n,x,p,h"; // sine wave

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

	int j = 0;
	int index = 0;	
	while (j < message.length()){

		if (message[j] == '.'){

			index = message.substring(j+1, 1).toInt();
			message = message.substring(0, j) + savedMessages[index-1] + message.substring(j+2, message.length());

		}

		j++;

	}


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

		} else if (message[1] == 'p'){
		
			int index = message.substring(2,1).toInt();	
			savedMessages[index-1] = message.substring(3, message.length());
			Serial.println("Preset " + String(index) + " is now: " + savedMessages[index-1]);

		} else if (message[1] == 'b'){

			float bpm = message.substring(2, message.length()).toInt();
			Serial.println("Setting to " + String(int(bpm)) + " bpm");
			offTime = int(1000*(60.0/bpm))-onTime;
			
			if (offTime <= 5){

				onTime = 200;
				Serial.println("On delay is now " + String(onTime) + " ms");
				offTime = int(1000*(60.0/bpm))-onTime;

			}
			
			Serial.println("Off delay is now " + String(offTime) + " ms");

		} else if (message[1] == 'r'){

			Serial.println(F("Resetting on and off times"));
			onTime = 1000;
			offTime = 100;

		} 
 
	} else {

		if (message[0] == ','){message=" ";}
		Serial.print("Changing message to: " + message);
		currentMessage = message;
		nextLetter = 0;		
		
	}

}
