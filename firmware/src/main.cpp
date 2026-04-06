#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET -1

#define BTN_LEFT 0
#define BTN_MIDDLE 1
#define BTN_RIGHT 2
#define BUZZER 18

#define CHANNEL 0

const unsigned char PROGMEM NEUTRAL_BLOBFI[] = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000001, 0b10000000, 0b00000000,
  0b00000000, 0b00001110, 0b01110000, 0b00000000,
  0b00000000, 0b00110000, 0b00001100, 0b00000000,
  0b00000000, 0b11000000, 0b00000011, 0b00000000,
  0b00000011, 0b00000000, 0b00000000, 0b11000000,
  0b00001100, 0b00000000, 0b00000000, 0b00110000,
  0b00010000, 0b10000000, 0b00000001, 0b00001000,
  0b00100000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00001000, 0b00010000, 0b00000100,
  0b01000000, 0b00001000, 0b00010000, 0b00000010,
  0b01000000, 0b00001000, 0b00010000, 0b00000010,
  0b10000111, 0b11101000, 0b00010111, 0b11100001,
  0b10001000, 0b00000100, 0b00100000, 0b00010001,
  0b10001011, 0b11110011, 0b11001111, 0b11010001,
  0b10001000, 0b00000000, 0b00000000, 0b00010001,
  0b10000111, 0b11111111, 0b11111111, 0b11100001,
  0b10000000, 0b00000000, 0b00000000, 0b00000001,
  0b01100000, 0b00000000, 0b00000000, 0b00000110,
  0b00011100, 0b00000000, 0b00000000, 0b00111000,
  0b00000011, 0b11100000, 0b00000111, 0b11000000,
  0b00000000, 0b00011111, 0b11111000, 0b00000000
};

const unsigned char PROGMEM HAPPY_BLOBFI[] = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000001, 0b10000000, 0b00000000,
  0b00000000, 0b00001110, 0b01110000, 0b00000000,
  0b00000000, 0b00110000, 0b00001100, 0b00000000,
  0b00000000, 0b11000000, 0b00000011, 0b00000000,
  0b00000011, 0b00000000, 0b00000000, 0b11000000,
  0b00001100, 0b00000000, 0b00000000, 0b00110000,
  0b00010000, 0b10000000, 0b00000001, 0b00001000,
  0b00100000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00001000, 0b00010000, 0b00000100,
  0b01000111, 0b10001000, 0b00010001, 0b11100010,
  0b01001000, 0b01101000, 0b00010110, 0b00010010,
  0b10001011, 0b00001000, 0b00010000, 0b11010001,
  0b10001000, 0b11000100, 0b00100011, 0b00010001,
  0b10000110, 0b00110011, 0b11001100, 0b01100001,
  0b10000001, 0b10000000, 0b00000001, 0b10000001,
  0b10000000, 0b01111111, 0b11111110, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000001,
  0b01100000, 0b00000000, 0b00000000, 0b00000110,
  0b00011100, 0b00000000, 0b00000000, 0b00111000,
  0b00000011, 0b11100000, 0b00000111, 0b11000000,
  0b00000000, 0b00011111, 0b11111000, 0b00000000
};

const unsigned char PROGMEM SAD_BLOBFI[] = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000001, 0b10000000, 0b00000000,
  0b00000000, 0b00001110, 0b01110000, 0b00000000,
  0b00000000, 0b00110000, 0b00001100, 0b00000000,
  0b00000000, 0b11000000, 0b00000011, 0b00000000,
  0b00000011, 0b00000000, 0b00000000, 0b11000000,
  0b00001100, 0b00000000, 0b00000000, 0b00110000,
  0b00010000, 0b10000000, 0b00000001, 0b00001000,
  0b00100000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00001000, 0b00010000, 0b00000100,
  0b01000000, 0b00001000, 0b00010000, 0b00000010,
  0b01000000, 0b00001000, 0b00010000, 0b00000010,
  0b10000001, 0b11101000, 0b00010111, 0b10000001,
  0b10001110, 0b00000100, 0b00100000, 0b01110001,
  0b10010000, 0b11110011, 0b11001111, 0b00001001,
  0b10010111, 0b00000000, 0b00000000, 0b11101001,
  0b10010000, 0b01111111, 0b11111110, 0b00001001,
  0b10001111, 0b10000000, 0b00000001, 0b11110001,
  0b01100000, 0b00000000, 0b00000000, 0b00000110,
  0b00011100, 0b00000000, 0b00000000, 0b00111000,
  0b00000011, 0b11100000, 0b00000111, 0b11000000,
  0b00000000, 0b00011111, 0b11111000, 0b00000000
};

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

struct Pet {
  int hunger;
  int happiness;
  int energy;
  unsigned long age;
};

Pet pet;

enum Screen {
  SCREEN_MAIN, SCREEN_FEED, SCREEN_PLAY, SCREEN_SLEEP
};

Screen currentScreen = SCREEN_MAIN;
unsigned long lastScreenChange = 0;

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_MIDDLE, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  ledcSetup(CHANNEL, 0, 8);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  pet.energy = 80;
  pet.happiness = 80;
  pet.hunger = 80;
  pet.age = 0; // in minutes
}

unsigned long lastButtonPress = 0;

void handleButtons() {
  if (millis() - lastButtonPress < 200) return;

  if (digitalRead(BTN_LEFT) == LOW) {
    currentScreen = SCREEN_FEED;
    pet.hunger += 10;
    ledcWriteTone(CHANNEL, 1000);
  }
  else if (digitalRead(BTN_MIDDLE) == LOW) {
    currentScreen = SCREEN_PLAY;
    pet.happiness += 10;
    ledcWriteTone(CHANNEL, 1200);
  }
  else if (digitalRead(BTN_RIGHT) == LOW) {
    currentScreen = SCREEN_SLEEP;
    pet.energy += 10;
    ledcWriteTone(CHANNEL, 700);
  }
}

void render() {
  if (currentScreen != SCREEN_MAIN && millis() - lastScreenChange > 5000) {
    currentScreen = SCREEN_MAIN;
  }

  switch (currentScreen)
  {
  case SCREEN_FEED:
    display.clearDisplay();
    display.setCursor(WIDTH/2-20,HEIGHT/2-8);
    display.print("Feeding blobfi");
    break;

  case SCREEN_PLAY:
    display.clearDisplay();
    display.setCursor(WIDTH/2-20,HEIGHT/2-8);
    display.print("Playing with blobfi");
    break;

  case SCREEN_SLEEP:
    display.clearDisplay();
    display.setCursor(WIDTH/2-20,HEIGHT/2-8);
    display.print("Blobfi is sleeping");
    break;
  
  default:
    const unsigned char* sprite;
    if (pet.hunger < 30 || pet.happiness < 30 || pet.energy < 30) {
      sprite = SAD_BLOBFI;
    } else if (pet.hunger > 65 && pet.happiness > 65 && pet.energy > 65) {
      sprite = HAPPY_BLOBFI;
    } else {
      sprite = NEUTRAL_BLOBFI;
    }

    display.drawBitmap(64, 10, sprite, 22, 22, SSD1306_WHITE);

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print("Hunger");
    drawBar(0, 9, pet.hunger);

    display.setCursor(0, 18);
    display.print("Happiness");
    drawBar(0, 27, pet.happiness);

    display.setCursor(0, 36);
    display.print("Energy");
    drawBar(0, 45, pet.hunger);

    display.setCursor(0, 56);
    display.print("[Feed] [Play] [Sleep]");

    break;
  }

  if (currentScreen != SCREEN_MAIN) {
    for (int i = 0; i < (millis()/200)%4; i++) {
      display.print(".");
    }

    if (millis() - lastScreenChange > 500) {
      ledcWriteTone(CHANNEL, 0);
    }
  } 

  display.display();
}

void drawBar(int x, int y, int value) {
  int width = 50;
  int height = 6;

  int fillWidth = map(value, 0, 100, 0, width);
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  display.fillRect(x, y, fillWidth, height, SSD1306_WHITE);
}

unsigned long lastUpdate = 0;

void updatePet() {
  if (millis() - lastUpdate > 300000) {
    pet.energy--;
    pet.happiness--;
    pet.hunger--;

    if (pet.hunger < 0) pet.hunger = 0;
    if (pet.happiness < 0) pet.happiness = 0;
    if (pet.energy < 0) pet.energy = 0;

    pet.age += 5;
    lastUpdate = millis();
  }
}

void loop() {
  handleButtons();  
  updatePet();
  render();
  delay(100);
}
