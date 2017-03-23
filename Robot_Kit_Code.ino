#include <Servo.h>

// create servo objects
Servo leftMotor;
Servo rightMotor;

const int serialPeriod = 250;       // only print to the serial console every 1/4 second
unsigned long timeSerialDelay = 0;

const int loopPeriod = 20;          // a period of 20ms = a frequency of 50Hz
unsigned long timeLoopDelay   = 0;

// UltraSonic Sensor Left
const int ultrasonicLeftTrigPin = 8;
const int ultrasonicLeftEchoPin = 9;
//UltraSonic RIght
const int USRightTrig= 4;
const int USRightEcho=5;

int ultrasonicLeftDistance;
int ultrasonicLeftDuration;
int USRDistance; 
int USRDuration;

void setup()
{
    Serial.begin(9600);
  
    // ultrasonic sensor pin configurations
    pinMode(ultrasonicLeftTrigPin, OUTPUT);
    pinMode(ultrasonicLeftEchoPin, INPUT);
    pinMode (USRightTrig, OUTPUT);
    pinMode (USRight, INPUT);
    leftMotor.attach(13);
    rightMotor.attach(12);
}


void loop()
{
    debugOutput(); // prints debugging messages to the serial console
    
    if(millis() - timeLoopDelay >= loopPeriod)
    {
        readUltrasonicSensors(); // read and store the measured distances
        
        stateMachine();
        
        timeLoopDelay = millis();
    }
}


void stateMachine()
{

        if(ultrasonicLeftDistance > 10 && ultrasonicLeftDistance < 0) // if there's nothing in front of us (note: ultrasonicDistance will be negative for some ultrasonics if there's nothing in range)
        {
            // drive forward
            rightMotor.write(180);
            leftMotor.write(0);
        }
        else // there's an object in front of us
        {
        }        unsigned long timeToTurnLeft = 1100; // it takes around 1.1 seconds to turn 90 degrees
        
        unsigned long turnStartTime = millis(); // save the time that we started turning

        while((millis()-turnStartTime) < timeToTurnLeft) // stay in this loop until timeToTurnLeft (1.1 seconds) has elapsed
        {
            // turn left
            rightMotor.write(180);
            leftMotor.write(180);
        }
        
        state = DRIVE_FORWARD;
    }

    // if both sensors see something, OR both sensors see nothing, move forward
    // else if right sensor see, move right
    // else if left sensor sees, move left
}


void readUltrasonicSensors()
{
    // ultrasonic 2
    digitalWrite(ultrasonicLeftTrigPin, HIGH);
    delayMicroseconds(10);                  // must keep the trig pin high for at least 10us
    digitalWrite(ultrasonicLeftTrigPin, LOW);
    
    ultrasonicLeftDuration = pulseIn(ultrasonicLeftEchoPin, HIGH);
    ultrasonicLeftDistance = (ultrasonicLeftDuration/2)/29;
}


void debugOutput()
{
    if((millis() - timeSerialDelay) > serialPeriod)
    {
        Serial.print("ultrasonic2Distance: ");
        Serial.print(ultrasonicLeftDistance);
        Serial.print("cm");
        Serial.println();
        
        timeSerialDelay = millis();
    }
}
