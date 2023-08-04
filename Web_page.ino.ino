#include <WiFi.h>
int FloatSensor1 = 16;

int FloatSensor2 = 21; //D4 pin of NodeMCU
int buttonState1 ;
int buttonState2 ; //reads pushbutton statusl
const char* ssid = "Ashok"; //ssid of your wifi-
const char* password = "12345678"; //password of your wifi
String level;
int relay = 18; // D1 pin of NodeMCU
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //connecting to wifi
  while (WiFi.status() != WL_CONNECTED)// while wifi not connected
  {
    delay(500);
    Serial.print("."); //print "...."
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address
  pinMode(FloatSensor1, INPUT_PULLUP);
  pinMode(FloatSensor2, INPUT_PULLUP); //Arduino Internal Resistor 10K
  pinMode(relay, OUTPUT); // set relay pin as output
  digitalWrite(relay, LOW);
  delay(4000);
}
void loop()
{
  int value ;
  bool buttonState1 = digitalRead(FloatSensor1); 
  bool buttonState2 = digitalRead(FloatSensor2);  // read the value of float sensor
  if (buttonState1 == LOW && buttonState2==LOW)                 // if the value is HIGH
  {        
    delay(2000)   ;                             // the level is high
    Serial.println( "WATER LEVEL - HIGH");
    level = "Full";
    digitalWrite(relay, LOW);              // turn OFF the relay
    value = LOW;
  }
  else if(buttonState1 == HIGH && buttonState2==HIGH)
  {
    delay(2000);
    Serial.println( "WATER LEVEL - LOW" ); // if the value is LOW
    level = "Empty";                       // the level is low
    digitalWrite(relay, LOW);             // turn ON the relay
    value = HIGH;
  }
  WiFiClient client = server.available(); // Check if a client has connected
  if (!client)
  {
    return;
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
  if (request.indexOf("/MOTOR=ON") != -1)
  {
    digitalWrite(relay, HIGH);   // if request is ON, turn ON the Motor.
    value = HIGH;
  }
  if (request.indexOf("/MOTOR=OFF") != -1)
  {
    digitalWrite(relay, LOW);    // if request is OFF, turn OFF the relay.
    value = LOW;
  }
  delay(100);
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>IoT based Smart Water Level Monitoring</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td </style> </head> <body> <h1  style=";
  s += "font-size:300%;";
  s += " ALIGN=CENTER> IoT based Smart Water Level Monitoring</h1>";
  s += "<p ALIGN=CENTER style=""font-size:150%>";
  s += "<b>Water level - </b><b>";
  s += level;
  s += "</b></p>";
  s += "<br><br>";
  s += "<a href=\"/MOTOR=ON\"\"><button><ALIGN=CENTER style=""font-size:150%>On </button></a>";
  s += "<a href=\"/MOTOR=OFF\"\"><button><ALIGN=CENTER style=""font-size:150%>Off </button></a><br />";
  s += "</body> </html> \n";
  client.print(s); // all the values are send to the webpage
  delay(100);
}