#include <SPI.h>
#include <SD.h>

const int buttonPin1 = 2;
const int buttonPin2 = 7;
const int buzzerPin = 4; 
const int chipSelect = 10;

File dataFile;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buzzerPin, OUTPUT); 
  digitalWrite(buttonPin, HIGH);

  initializeSDCard(); 
}
void loop() {
  checkSDCard();

  if (digitalRead(buttonPin1) == LOW) { 
    if (SD.exists("data.txt")) {
      dataFile = SD.open("EVM-data.txt", FILE_WRITE);
      if (dataFile) {
        dataFile.println("ABC VOTED ABC AS HEAD BOY");
        dataFile.close();
        Serial.println("Data written to SD card.");
        
        for (int i = 0; i < 1; i++) {
          beepBuzzer(); 
          delay(150); 
        }
      } else {
        Serial.println("Error opening data.txt");
        longBeepBuzzer(); 
      }
    } else {
      Serial.println("data.txt does not exist.");
       for (int i = 0; i < 3; i++) {
          longBeepBuzzer();
          delay(300); 
        }
    }
    delay(1000);
  }
  if (digitalRead(buttonPin2) == LOW) {
    if (SD.exists("data.txt")) {
      dataFile = SD.open("EVM-data.txt", FILE_WRITE);
      if (dataFile) {
        dataFile.println("ABC VOTED ABC AS HEAD BOY"); 
        dataFile.close();
        Serial.println("Data written to SD card.");
        
        for (int i = 0; i < 1; i++) {
          beepBuzzer();
          delay(150);
        }
      } else {
        Serial.println("Error opening data.txt");
        longBeepBuzzer(); 
      }
    } else {
      Serial.println("data.txt does not exist.");
       for (int i = 0; i < 3; i++) {
          longBeepBuzzer();
          delay(300);
        }
    }
    delay(1000); 
  }
}
void initializeSDCard() {
  
  while (!SD.begin(chipSelect)) {
    Serial.println("Error initializing SD card. Retrying...");
    longBeepBuzzer();
    delay(1000);
  }
  Serial.println("SD card initialized.");
}

void checkSDCard() {
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card not detected.");
    longBeepBuzzer(); 
    delay(1000);
  }
}

void beepBuzzer() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(50); // Beep duration
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  delay(50); // Delay between beeps
}

void longBeepBuzzer() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(500); // Longer beep duration
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
}
