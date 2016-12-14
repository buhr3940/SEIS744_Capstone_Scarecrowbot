Scarecrowbot
Eric Buhr
IOT Capstone project
SEIS 744 
Instructors: Justin Grammens & John Pritchard

Problem: In my backyard, squirrels destroy plants, lawn furniture and even packages left near the back door.  We have tried many ways to
deter them with minimal success. We wanted to find a non-lethal way to do so and repel them from an area on a consistent basis using IoT. 

There are many commerically available solutions out in market today. People are desparate to keep critters out of their gardens or damaging
things in their yard. Non-lethal means have become very popular. Several different products exist including that use : 1) Water like
Scarecrow Motion Activated Animial repellent which uses water coneected from a hose, 2) Visual Decoys such as Natural Enemies Scarecrow,
 3) Scent like Critter Ridder and 4) Sound and Lights like THe Guardian which uses changing pitch, predator calls and strobe lights.

Solution: Scarecrowbot is an IOT the squirrel using sound. The bot detects the squirrel using a PIR motion sensor (made by Parallax). The 
user determines the initial frequency (i.e  pitch).  The bot would then emit a sound using a piezo buzzer once the creature is detected.
The device platform (microcontroller) used is the Particle Photon to keep the footprint relatively small and take advantage of existing 
WiFi communications which reaches my yeard. The device is housed in a 3D printed enclosure shaped either like a bird house or shelter with
canopy. The enclosure is hooked onto a garden stake to elevate the device a few inches above ground at squirrel level. The idea is that
the roof or canopy would act as blinders to focus the detection to directly in front of the device. 

Hardware: 

1) Particle Photon (and Half Breadboard) --I used this microcontroller becuase of its small footprint and WiFi communications that I
could use around my house and yard.

2) PIR sensor -- to detect motion of squirrels (light/occupancy sensor is not sensitive enough) and PIR has better range

3) Piezo buzzer -- emits annoying sound or beep using tone() function -- simple to use and has small footprint

4) LED  -- to light up on detection

5) 100 Ohm resistor (for LED)

6) A myriad of wires

7) 3D printed enclosure with garden stake(s)

How to Get Started and Operate Scarecrowbot

1. Connect device (particle photon) via USB to laptop.
2. Using Particle Build or Arduino , create new app and copy .ino file from reposiory to new file. Save.
3. Add Tinker library to app. (either from Build or using Particle App).
4. Flash code to Photon.
5. When Photon's status LED is blue, then device is ready.
6, Go to Porter App at http://porterapp.com/ or use iOS application. Click signin/preview. 
7. Enter ID and Password (will email to instructor). 
8. Wave your hand or move in front of PIR sensordata
9. Hit refresh and data will be updated. 
10. View event and repeat data. See variables. OR Change frequency or put device into sleep mode for 30 seconds (demo purposes).

Software Used:

1) Particle Build IDE/Logs
2) Particle App
3) Porter App (both web and iOS version)
4) AutoCAD Fusion 360
5) Afinia 3D Printer Software (connected to Afinia H800 3D printer)
6) Fritzing App
7) Github

At first, I had planned to use a combination the PIR motion sesnor with an Ultrasonic Range Finder. Since you can only change the PIR
range through either jumpers or dials on the sesnor, I thought I could use range finder to set the range limit and kick any detections
that were outside the range programmatically. 

However I ditched this idea and went with just using the PIR sensor and adjusting the frequency of the peizo buzzer instead for several 
reasons: 1)the device can better satisfy the minimal viable product simplifying my design and coding, 2) the ultrasonic sensor footprint 
is large,  3) squirrels are more sensitive to higher frequencies than humans detecting as high as 49 KHz, 4) the buzzer's upper limit goes
up to 60 Khz so it is more capable of reaching that range (whereas the device woudl be more limitied with distance, and 5) the device
could offer frequencies that squirrels could hear but not humans making the technologyto  even calmer. 

Collection Point
The bots have been tested on Particle’s iPhone app. Eventually, I chose to use the Porter App to collect and display the device device.

There are several reasons why I used the Porter App  1) it automatically accepts Particle variables, events, and functions without
adding libraries, 2) has an easy to use UI builder, and  3) available iOs app as well as browser based interface. Other third party 
platform such as Bluemix (IBM Watson IOT) and Blynk were difficult to incorporate due to problems with their respective libraries (would
not compile in Particle Build IDE). Often there were files not found or incorrect paths. I probably spent more time unsuccessfully 
trying get to their libraries to work than any other task with this project. 

The app allows the user change the frequency of the sound. The bot detects a squirrel and sends the time stamp of both detection and 
repeat event to the application to be collected. If the most recent detection is within 15 minutes of the previous one, then it 
is a repeat detection. The goal is to reduce or eliminate this return trip by the squirrel. The bot will adjust the frequency upwards to
 see if the new pitch is more effective. If a repeat detection occurs again, then the device will increase frequency once more. And the bot
 will continue this process until the repeat detection is stopped or the maximum frequency is reached. The adjusted frequency will be
 communicated to the application. The user has the option to change it. The user can also put the device into a sleep mode (currently deep
 sleep for temporary period) which saves on battery power. There is code for deep sleep during overnight hours since squirrels are active 
 during the day (but this code has not been tested and is commented out.) The goal is for the application to provide the user the following options: 1) see event data,
 2) repeat events, 3) change frequency, 4) show current frequency and 5) put bot into sleep mode (low power).
