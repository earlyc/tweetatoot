/*
  Send-a-Tweet
  
  Based on kid-summoner.ino by Jen Looper
  Additions and edits by Anouska de Graaf - www.anouskadegraaf.nl
  
*/
 
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
/*void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  if(sensorValue > 3000){
    Serial.println(sensorValue);
  }
  // print out the value you read:
  delay(100);        // delay in between reads for stability
}*/

int val1 = 0; //variable for push-button status scenario 1
//int val2 = 0; //variable for push-button status scenario 2
int state = 1; //variable for on/off state

const char * SAT1 = "v4FFBEBB71A6A599";     // Send-a-Tweet scenario 1 - Change DEVICE_ID1 with your Device ID!!!
//const char * SAT2 = "DEVICE_ID2";     // Send-a-Tweet scenario 2 - Change DEVICE_ID2 with your Device ID!!!
const char * DEVID = "";
 
const char * serverName = "api.pushingbox.com";   // Pushingbox API URL
 
TCPClient client;
 
void setup() {
    pinMode(A0, INPUT);
    //pinMode(D2, INPUT);
    Serial.begin(9600);
    Serial.println("Serial open");
}
 
 
void loop() {
    val1 = analogRead(A0); //read the state of the push-button
    //val2 = digitalRead(D2);
      // read the input on analog pin 0:
  int sensorValue = val1;
  if(sensorValue > 3000){
        DEVID = SAT1;
        Serial.println("We have a toot!");
        sendToPushingBox(DEVID);
    Serial.println(sensorValue);
  }
  // print out the value you read:
  delay(100);        // delay in between reads for stability
    /*else if (val2 == LOW) { //if push-button pressed
        DEVID = SAT2;
        state = !state; //reverse on/off state
        delay(250); //primitive button debounce
        Serial.println("button scenario2 pushed!");
        sendToPushingBox(DEVID);
    }*/
}
 
void sendToPushingBox(const char * devid)
{
    Serial.println("Start sendToPushingBox");
    client.stop();
    if (client.connect(serverName, 80)) {
        client.print("GET /pushingbox?devid=");
        client.print(devid);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(serverName);
        client.println("User-Agent: Spark");
        client.println();
        client.flush();
    }
    else{
        Serial.println("connection failed");
    }
}