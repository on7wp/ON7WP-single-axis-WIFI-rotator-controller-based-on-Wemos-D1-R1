#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "BLYNK AUTHORISATION TOKENr";
char ssid[] = "SSID";
char pass[] = "PASSWORD";
int temp;


// Motor Azimuth connections

int enA = 12;

int in1 = 14;

int in2 = 16;

 

int rotorfeedback; // variable to store the value coming from the analog pin

double act;// variable to store the position value coming from the conversion formula

double error;// variable to store the pointing error

int heading; // variable to store the position value coming from the remote control

double set;// variable to store the position value coming from the conversion formula

 


void setup() {

// Set all the motor control pins to outputs

pinMode(enA, OUTPUT); // PWM speed control ESP8266 uses 10 BIT PWM !!

pinMode(in1, OUTPUT);

pinMode(in2, OUTPUT);


 

// Turn off motors - Initial state

digitalWrite(in1, LOW);

digitalWrite(in2, LOW);

// Display wifi connect status on serial monitotr
 Serial.begin(115200);
  
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

Blynk.begin(auth, ssid, pass, "SERVER NAME", SERVER PORT);
}

#define HEADING V0
#define ACT V1


BLYNK_WRITE(V0) //writing the wanted direction from input with 20 degrees offset to protect potmeter in rotor
{
temp = param.asInt(); 
} 

 
// the loop function runs over and over again forever
void loop() {
Blynk.run(); 
int real=act-20;
Blynk.virtualWrite(ACT, real);

Blynk.virtualWrite(HEADING, temp);
set=temp+20;

rotorfeedback= analogRead(0); // read the analog in value:

act = (double) rotorfeedback * (400/1024.0); // position conversion formula

if(set < act)

{

TurnCCW();

}

else {

TurnCW();

}

//speedcontrol while reaching target

if ((abs(set-act))<20)

{

analogWrite(enA, 900);

}

if ((abs(set-act))<5)

{

analogWrite(enA, 800);

}

if ((abs(set-act))<1)

{

analogWrite(enA, 0);
Stop();

}

}

// This function lets you control the motor to turn clockwise

void TurnCW(){

analogWrite(enA, 1023);

digitalWrite(in1, LOW);

digitalWrite(in2, HIGH);

}

void TurnCCW(){

analogWrite(enA, 1023);

digitalWrite(in1, HIGH);

digitalWrite(in2, LOW);

}

void Stop(){

// Turn off motors

digitalWrite(in1, LOW);

digitalWrite(in2, LOW);

}
