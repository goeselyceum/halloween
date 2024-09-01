#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13   // SPI Clock, shared with SD card
#define MISO 12  // Input data, from VS1053/SD card
#define MOSI 11  // Output data, to VS1053/SD card

// These are the pins used for the music maker shield
#define SHIELD_RESET 8  // VS1053 reset pin (unused!)
#define SHIELD_CS 6     // VS1053 chip select pin (output)
#define SHIELD_DCS 7    // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 9  // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2  // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
// create shield-example object!

int track = 0;
int previousTrack = 0;
int trigPin = 4;
int echoPin = 5;
long cm, duration;
int treshold = 100;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  Serial.println("VS1053 Test");

  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1)
      ;  // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(5, 5);


  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int


  // Play one file, don't return until complete
  Serial.println(F("Playing track 0"));
  musicPlayer.playFullFile("0.mp3");
  // Play another file in the background, REQUIRES interrupts!
}


void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);


  // Convert the time into a distance
  cm = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343


  Serial.print(cm);
  Serial.print(" cm  ");
  Serial.print("track: ");
  Serial.println(track);


  /*if (cm < treshold) {
    if (track == previousTrack) {
      track = random(4, 11);
    }
    playSound();
  }
  */
  if (cm < treshold) {

    do {
      track = random(4, 11);
    } while (track == previousTrack);
    playSound();
  }
  delay(200);
}

void playSound() {
  Serial.print("Playing track: ");
  Serial.println(track);
  if (track == 1) {
    musicPlayer.playFullFile("1.mp3");
  } else if (track == 2) {
    musicPlayer.playFullFile("2.mp3");
  } else if (track == 3) {
    musicPlayer.playFullFile("3.mp3");
  } else if (track == 4) {
    musicPlayer.playFullFile("4.mp3");
  } else if (track == 5) {
    musicPlayer.playFullFile("5.mp3");
  } else if (track == 6) {
    musicPlayer.playFullFile("6.mp3");
  } else if (track == 7) {
    musicPlayer.playFullFile("7.mp3");
  } else if (track == 8) {
    musicPlayer.playFullFile("8.mp3");
  } else if (track == 9) {
    musicPlayer.playFullFile("9.mp3");
  } else if (track == 10) {
    musicPlayer.playFullFile("10.mp3");
  } else if (track == 11) {
    musicPlayer.playFullFile("11.mp3");
  }
  previousTrack = track;
  delay(1000);
}
