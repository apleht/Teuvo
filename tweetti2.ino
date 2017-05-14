#include <Twitter.h>
#include <SPI.h>
#include <WiFi.h>



char ssid[] = "";  //  your network SSID (name)
char pass[] = "";  // your network password

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter(""); 

int soil=0;
char msg[140];

void setup()
{
  delay(100000);
  WiFi.begin(ssid, pass);
  // or you can use DHCP for automatic IP address configuration.
  // WiFi.begin(mac);
  delay(100000);
  Serial.begin(9600);
}
void tweet(char msg[])
{
 
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    // Specify &Serial to output received response to Serial.
    // If no output is required, you can just omit the argument, e.g.
    // int status = twitter.wait();
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop() {
  
int x = random(100000);

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  sensorValue = constrain(sensorValue, 485, 1023);
  // print out the value you read:
  //Serial.println(sensorValue);

  //map the value to a percentage
  soil = map(sensorValue, 485, 1023, 100, 0);
  
  // print out the soil water percentage you calculated:
  sprintf(msg, "Mullan kosteus: %d%% ID%d", soil, x);
 

 delay(10000000);
 tweet(msg);
}
