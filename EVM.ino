#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>

#define BUTTONS_PIN A0 // Analog pin for buttons
#define BUZZER_PIN 4
#define SD_CS_PIN 10

LiquidCrystal_I2C lcd(0x27, 16, 2);

File dataFile;

const int numButtons = 4; // Number of buttons
const int buttonThresholds[numButtons] = {100, 300, 500, 700}; // Adjust thresholds as needed

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed.");
    while (1);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setting Up EVM");

  delay(2000);

  // Initialize other components or perform additional setup tasks here
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vote For:");

  lcd.setCursor(0, 1);
  lcd.print("1. Candidate A");
  lcd.setCursor(0, 2);
  lcd.print("2. Candidate B");

  int vote = waitForVote();

  if (vote == 1) {
    recordVote("Candidate A");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You voted for:");
    lcd.setCursor(0, 1);
    lcd.print("Candidate A");
  } else if (vote == 2) {
    recordVote("Candidate B");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You voted for:");
    lcd.setCursor(0, 1);
    lcd.print("Candidate B");
  }

  // You can add more candidates and logic as needed

  delay(5000); // Display result for 5 seconds

  // Additional EVM logic and state handling can be added here
}

int waitForVote() {
  while (true) {
    int analogValue = analogRead(BUTTONS_PIN);
    for (int i = 0; i < numButtons; i++) {
      if (analogValue < buttonThresholds[i]) {
        buzz();
        return i + 1; // Button i pressed, vote for Candidate i+1
      }
    }
  }
}

void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void recordVote(const char* candidate) {
  dataFile = SD.open("votes.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(candidate);
    dataFile.close();
    Serial.println("Vote recorded: " + String(candidate));
  } else {
    Serial.println("Error opening file.");
  }
}

void displayStatus(const char* status) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(status);
}
