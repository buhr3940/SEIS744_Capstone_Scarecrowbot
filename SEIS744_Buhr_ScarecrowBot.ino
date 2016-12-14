// This #include statement was automatically added by the Particle IDE.
#include "Tinker/Tinker.h"




STARTUP(System.enableFeature(FEATURE_RETAINED_MEMORY));

int motiondetectPin = D0;              // input pin (for motion sensor)
int ledPin = D1;      
int pzbuzzerPin = D2;              
int motionState = LOW;             // state of motion sensor - begins with LOW or no motion
int readVal = 0;                    // read the value of the motion sensor input

int activateTime = 10000;      // wait for system/sensor to be ready to detect
int frequency = 1;            // frequency of buzzer in Hz -- higher the number, the higher the pitch  
int repeatTime = 900000;      //
String aMotion;             // motion event string    
int detectCount = 0;
int firstCount = 0;
int repeatCount = 0;
int diff = 0;
int tStart = 0;
int tStop = 0;
int t = 0;
bool sleepOn = false;
String sleepOnS = "off";
int setFreq (String limit);
int setSleep (String command);     // Set the deep sleep mode (WiFi off, powerdown)


void setup()

{
    
  Serial.begin(9600);    
  pinMode( ledPin, OUTPUT );
  pinMode(motiondetectPin, INPUT);  
  //particle variable exposed for Porter App to display
  Particle.variable ("motionState", motionState);        
  Particle.variable ("frequency", frequency);
  Particle.variable ("repeatCount", repeatCount);
  Particle.variable ("detectCount", detectCount);
  Particle.variable ("sleepOnS", sleepOnS);
  // particle functions exposed for Porter App so that user can take action
  Particle.function("set_Freq", setFreq);
  Particle.function("set_Sleep", setSleep);
 
}
// attempt to use system sleep rising with activate pin for nighttime (because squirrels are not active then) -- could not get working
void gotoSleep() {
    System.sleep(D0,RISING,57600);
}

void setSleepT() {
  
  tStart = millis();
  
  // nighttime deep sleep mode between 4pm to 8am using Time.hour -- could not get working   
  if ((Time.hour() > 16) || (Time.hour() < 8 )){
    //  delay(2);  
    //  gotoSleep();
    //  sleepOn = true;
    }
  if (detectCount == 0) {
     t = tStart - millis(); 
  // If sensor makes no detections for 30 min during day --attempt to use system sleep with RISING , Activate Pin -- could not get working 
    if (t==1800000) { 
      gotoSleep();
      sleepOn = true;
      }
    }
// User intiated deep sleep mode set for 30 seconds -- did work from iOS app
  if (sleepOnS == "on"){
      sleepOn = true;
      delay(2);
      System.sleep(SLEEP_MODE_DEEP, 30);
      }
    
 // if (sleepOnS == "off"){
 //     sleepOn = false;
 // }
}

void loop()
{
     // if the sensor is ready to detect/activated
  if ( activated() )
  {
  // get motion data from the sensor
    readMotionSensor();

    // report out, if sensor state has changed
    
    reportData();
  }
  
  setSleepT();
  
}

void readMotionSensor() {
  readVal = digitalRead(motiondetectPin);
}

bool activated() {
  return millis() - activateTime > 0;
}



void reportData() {

  // reading is  high (i.e. motion is detected)
 
  if (readVal == HIGH) {
   
    // the current state is no motion
    // but reading just changed state
    // publish motion event 
    if (motionState == LOW) {
      // number of detetions
      detectCount++;
      firstCount = millis();
      Particle.publish("motion", aMotion);
      
      // Update sensor state
      motionState = HIGH;
      setLED( motionState );
      //this is the time in milliseconds between the previous and current detection
      diff = millis() - firstCount;
      // detect count is more than 1 and the difference is less than or eqiual to 15 min, then publish repeat event
      if (detectCount > 1 && diff <= repeatTime) {
        Particle.publish ("repeat");
        repeatCount++;
        delay(600);
        
        // Bot adjusts frequncy up 100 Hz ; making buzzer higher pitch to minimize repeat event
        frequency = frequency + 100;
        }
    
    }
  } else {
    if (motionState == HIGH) {
        tone(pzbuzzerPin, frequency, 500);
      // we have just turned of
      // Update the current state
      motionState = LOW;
      setLED( motionState );
    }
  }
}

// Sets temperature scale. Returns 1 if input is "F" or "C",

// otherwise returns -1.

int setSleep (String command){

  command.toLowerCase();


  if( command == "off" || command == "on" ) {
        
         sleepOnS = command;
        
         
    return 1;

  } else {
    sleepOn = true;
    return -1;
    

  }

}


// Set the frequency

int setFreq(String limit){

  frequency = limit.toInt();

  return 1;

}

void setLED( int state )
{
  digitalWrite( ledPin, state );
}
