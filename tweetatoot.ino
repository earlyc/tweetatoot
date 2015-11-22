const char * SAT1 = "v4FFBEBB71A6A599";
 
const char * serverName = "api.pushingbox.com";   // Pushingbox API URL
 
TCPClient client;
 
void setup() {
    pinMode(A0, INPUT);
    Serial.begin(9600);
    Serial.println("Serial open");
}
 
 
void loop() {
    int sensorValue = analogRead(A0);
    double db = 20.0 * log10(sensorValue / 5.0);
    if(sensorValue > 3000){
        DEVID = SAT1;
        Serial.println("We have a toot!");
        sendToPushingBox(DEVID);
        Serial.println(db);
      }
  delay(100);
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
