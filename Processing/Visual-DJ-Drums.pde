import processing.sound.*;
import processing.serial.*;

Serial myPort;
SoundFile file;

String samplesSuffix = "tree";
int numberOfSounds = 24;

SoundFile[] pads = new SoundFile[numberOfSounds];

void setup() {
  size(640, 360);
  background(255);
  
  for(int i = 1; i <= numberOfSounds; i++) {
    pads[i - 1] = new SoundFile(this, "pad" + i + "_" + samplesSuffix + ".wav");
  }
  
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[2], 9600);
}      

void draw() {
  while (myPort.available() > 0) {
    char key = (char)myPort.read();
    println(key);
    switch(key) {
    case 'a': pads[16].play(); break;
    case 's': pads[17].play(); break;
    case 'd': pads[19].play(); break;
    case 'f': pads[20].play(); break;
    case 'g': pads[21].play(); break;
    case 'h': pads[22].play(); break;
    case 'j': pads[23].play(); break;
    
    case 'z': pads[4].play(); break;
    case 'x': pads[5].play(); break;
    case 'c': pads[7].play(); break;
    case 'v': pads[8].play(); break;
    case 'b': pads[10].play(); break;
    case 'n': pads[11].play(); break;
  } 
  }
}

void keyPressed() {
  switch(key) {
    case 'o': pads[16].play(); break;
    case 'p': pads[17].play(); break;
    case 'l': pads[19].play(); break;
    case 'ò': pads[20].play(); break;
    case ',': pads[21].play(); break;
    case '.': pads[22].play(); break;
    case '-': pads[23].play(); break;
    
    case 'q': pads[4].play(); break;
    case 'w': pads[5].play(); break;
    case 'a': pads[7].play(); break;
    case 's': pads[8].play(); break;
    case '<': pads[10].play(); break;
    case 'z': pads[11].play(); break;
  } 
}
