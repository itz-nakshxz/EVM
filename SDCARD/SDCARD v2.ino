#include <SPI.h>
#include <SD.h>

const int buttonPin1 = 2;
const int buttonPin2 = 7;
const int buzzerPin = 4; // Pin for the buzzer
const int chipSelect = 10;

File dataFile;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  digitalWrite(buttonPin1, HIGH); // Enable internal pull-up resistor
  digitalWrite(buttonPin2, HIGH); // Enable internal pull-up resistor

  initializeSDCard(); // Attempt to initialize SD card
}

void loop() {
  if (digitalRead(buttonPin1) == LOW) { // Button 1 is pressed
    uploadData("data.txt", "Data for Button 1");
    beepBuzzer();
    delay(1000); // Debounce delay
  }

  if (digitalRead(buttonPin2) == LOW) { // Button 2 is pressed
    uploadData("data.txt", "Data for Button 2");
    beepBuzzer();
    delay(1000); // Debounce delay
  }
}

void initializeSDCard() {
  if (SD.begin(chipSelect)) {
    Serial.println("SD card initialized.");
  } else {
    Serial.println("Error initializing SD card.");
    longBeepBuzzer(); // Produce a longer beep for initialization error
  }
}

void uploadData(const char *filename, const char *data) {
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("Data written to SD card: " + String(filename));
  } else {
    Serial.println("Error opening " + String(filename));
  }
}

void beepBuzzer() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(100); // Beep duration
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
}

void longBeepBuzzer() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(500); // Longer beep duration
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
}
