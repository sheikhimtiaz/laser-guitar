
#include <SD.h>
#include <SPI.h>
#include <Audio.h>

int s1, s2, s3, s4, s5, s6;
int Th = 100;

long cm = 0, pm = 0;

void setup() {

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  delay(2000);

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println(" failed!");
    while (true);
  }

  Serial.println(" done.");
  Audio.begin(88200, 10);


  playAudioStart();

}

void loop() {
  int count = 0;

  File myFile1 = SD.open("z1.wav");
  File myFile2 = SD.open("z2.wav");
  File myFile3 = SD.open("z3.wav");
  File myFile4 = SD.open("z4.wav");
  File myFile5 = SD.open("z5.wav");
  File myFile6 = SD.open("z6.wav");

  if (!myFile1 && !myFile2 && !myFile3 && !myFile4 && !myFile5 && !myFile6) {
     Serial.println("error opening");
     while (true);
  }

  const int S = 1024; // Number of samples to read in block
  short buffer[S];

  while (1) {
     Serial.println("Again playing");

111
    File myFile1 = SD.open("X1.wav");
    File myFile2 = SD.open("X2.wav");
    File myFile3 = SD.open("X3.wav");
    File myFile4 = SD.open("X4.wav");
    File myFile5 = SD.open("X5.wav");
    File myFile6 = SD.open("X6.wav");


    myFile1.seek(10240);
    myFile2.seek(10240);
    myFile3.seek(10240);
    myFile4.seek(10240);
    myFile5.seek(10240);
    myFile6.seek(10240);

    checkLaser();

    while ((myFile1.available() && s1 == 1) || (myFile2.available() && s2 == 1) || (myFile3.available() && s3 == 1) || (myFile4.available() && s4 == 1) || (myFile5.available() && s5 == 1) || (myFile6.available() && s6 == 1) ) {

      checkLaser();

      if (myFile1.available() && s1 == 1) {
        myFile1.read(buffer, sizeof(buffer));
      }

      else if (myFile2.available() && s2 == 1) {
        myFile2.read(buffer, sizeof(buffer));
      }


      else if (myFile3.available() && s3 == 1) {
        myFile3.read(buffer, sizeof(buffer));
      }

      else if (myFile4.available() && s4 == 1) {
        myFile4.read(buffer, sizeof(buffer));
      }

      else if (myFile5.available() && s5 == 1) {
        myFile5.read(buffer, sizeof(buffer));
      }

      else if (myFile6.available() && s6 == 1) {
        myFile6.read(buffer, sizeof(buffer));
      }


      int volume = 1024;
      Audio.prepare(buffer, S, volume);
      Audio.write(buffer, S);

    }

    Audio.rst();
    myFile1.close();
    myFile2.close();
    myFile3.close();
    myFile4.close();
    myFile5.close();
    myFile6.close();
  }

}



void checkLaser() {

  int ss1 = analogRead(A0);
  int ss2 = analogRead(A1);
  int ss3 = analogRead(A2);
  int ss4 = analogRead(A3);
  int ss5 = analogRead(A4);
  int ss6 = analogRead(A5);

  // Serial.printn(ss1);
  // Serial.printn(ss2);

  if (ss1 > Th) {
    s1 = 1;
    s2 = 0;
    s3 = 0;
    s4 = 0;
    s5 = 0;
    s6 = 0;

    pm = millis();
  }


  else if (ss2 > Th) {
    s1 = 0;
    s2 = 1;
    s3 = 0;
    s4 = 0;
    s5 = 0;
    s6 = 0;

    pm = millis();
  }

  else if (ss3 > Th) {
    s1 = 0;
    s2 = 0;
    s3 = 1;
    s4 = 0;
    s5 = 0;
    s6 = 0;

    pm = millis();
  }

  else if (ss4 > Th) {
    s1 = 0;
    s2 = 0;
    s3 = 0;
    s4 = 1;
    s5 = 0;
    s6 = 0;

    pm = millis();
  }

  else if (ss5 > Th) {
    s1 = 0;
    s2 = 0;
    s3 = 0;
    s4 = 0;
    s5 = 1;
    s6 = 0;

    pm = millis();
  }

  else if (ss6 > Th) {
    s1 = 0;
    s2 = 0;
    s3 = 0;
    s4 = 0;
    s5 = 0;
    s6 = 1;

    pm = millis();
  }

  cm = millis();
  if (cm - pm > 30000) {
    playAudioEND();
    digitalWrite(7, LOW);
  }
  else if (cm - pm > 1000) {
    s1 = 0;
    s2 = 0;
    s3 = 0;
    s4 = 0;
    s5 = 0;
    s6 = 0;
  }


}




void playAudioStart() {

  File myFile = SD.open("puja1.wav");

  const int S = 1024;
  short buffer[S];

  while (myFile.available()) {
    myFile.read(buffer, sizeof(buffer));

    int volume = 1024;
    Audio.prepare(buffer, S, volume);
    Audio.write(buffer, S);

  }

  Audio.rst();
  myFile.close();

}


void playAudioEND() {

  File myFile = SD.open("puja2.wav");

  const int S = 1024;
  short buffer[S];

  while (myFile.available()) {
    myFile.read(buffer, sizeof(buffer));

    int volume = 1024;
    Audio.prepare(buffer, S, volume);
    Audio.write(buffer, S);

  }

  Audio.rst();
  myFile.close();

}


