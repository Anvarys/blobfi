#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <OneWireNg_CurrentPlatform.h>
#include <DallasTemperature.h>


#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET -1

#define BTN_LEFT 0
#define BTN_MIDDLE 1
#define BTN_RIGHT 2
#define VIBRATION_MOTOR 10
#define TEMP_SENSOR 3

#define BTN_LEFT_PIN_BITMASK (1ULL << GPIO_NUM_0)
#define BTN_MIDDLE_PIN_BITMASK (1ULL << GPIO_NUM_1)
#define BTN_RIGHT_PIN_BITMASK (1ULL << GPIO_NUM_2)

#define UPDATE_DELAY_IN_S 300
#define UPDATE_DELAY_IN_uS UPDATE_DELAY_IN_S * 100000ULL

#define SLEEP_AFTER_INACTIVE_FOR_S 30

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

OneWireNg_CurrentPlatform ow(TEMP_SENSOR, false);
DallasTemperature sensors((OneWire*)&ow);

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

struct Pet {
  int hunger;
  int happiness;
  int energy;
  unsigned long age; // = AGE_SECONDS / UPDATE_DELAY_IN_S
};

RTC_DATA_ATTR Pet pet = {80, 80, 80, 0};

RTC_DATA_ATTR uint64_t lastUpdate = -1; // uS

uint64_t lastUpdateBootRelative = 0; // uS

suseconds_t getRtcTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec;
}

float getTempC() {
  sensors.requestTemperatures();
  delay(110);

  return sensors.getTempCByIndex(0);
}

void setup() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_MIDDLE, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(VIBRATION_MOTOR, OUTPUT);

  uint64_t mask = BTN_LEFT_PIN_BITMASK | BTN_MIDDLE_PIN_BITMASK | BTN_RIGHT_PIN_BITMASK;
  esp_deep_sleep_enable_gpio_wakeup(mask, ESP_GPIO_WAKEUP_GPIO_HIGH);

  esp_sleep_enable_timer_wakeup(UPDATE_DELAY_IN_uS);
  sensors.begin();
  sensors.setResolution(9);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    updatePet();
    esp_deep_sleep_start();
    return;
  }

  if (lastUpdate == -1) {
    lastUpdate = getRtcTime();
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

uint64_t lastButtonPress = -200;

enum Screen {
  SCREEN_MAIN, SCREEN_FEED, SCREEN_PLAY, SCREEN_SLEEP
};

Screen currentScreen = SCREEN_MAIN;
uint64_t lastScreenChange = 0;

void goSleep() {
  display.clearDisplay();
  display.display();

  display.ssd1306_command(SSD1306_DISPLAYOFF);
  display.ssd1306_command(0x8D);
  display.ssd1306_command(0x10);

  esp_sleep_enable_timer_wakeup(UPDATE_DELAY_IN_uS - (getRtcTime() - lastUpdate));
  esp_deep_sleep_start();
}

void handleButtons() {
  if (currentScreen != SCREEN_MAIN || millis() - lastButtonPress < 150) return;

  if (digitalRead(BTN_LEFT) == LOW && digitalRead(BTN_RIGHT) == LOW) {
    goSleep();
  }

  if (digitalRead(BTN_LEFT) == LOW) {
    currentScreen = SCREEN_FEED;
    pet.hunger += 15;
    pet.energy += 5;
    if (pet.hunger > 100) {
      pet.hunger = 100;
    }

    lastScreenChange = millis();
  }
  else if (digitalRead(BTN_MIDDLE) == LOW) {
    currentScreen = SCREEN_PLAY;
    pet.happiness += 15;
    pet.energy -= 5;
    if (pet.happiness > 100) {
      pet.happiness = 100;
    }

    lastScreenChange = millis();
  }
  else if (digitalRead(BTN_RIGHT) == LOW) {
    currentScreen = SCREEN_SLEEP;
    pet.energy += 15;
    if (pet.energy > 100) {
      pet.energy = 100;
    }

    lastScreenChange = millis();
  }
}

void drawBar(int x, int y, int value) {
  if (value < 10 && (millis()/500)%2 == 0) {return;}

  int width = 50;
  int height = 6;

  int fillWidth = map(value, 0, 100, 0, width);
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  display.fillRect(x, y, fillWidth, height, SSD1306_WHITE);
}

void render() {
  if (currentScreen != SCREEN_MAIN && millis() - lastScreenChange > 3000) {
    currentScreen = SCREEN_MAIN;
  }

  switch (currentScreen)
  {
  case SCREEN_FEED:
    display.clearDisplay();
    display.setCursor(0,HEIGHT/2-4);
    display.print("Feeding blobfi");
    break;

  case SCREEN_PLAY:
    display.clearDisplay();
    display.setCursor(0,HEIGHT/2-4);
    display.print("Blobfi is playing");
    break;

  case SCREEN_SLEEP:
    display.clearDisplay();
    display.setCursor(0,HEIGHT/2-4);
    display.print("Blobfi is sleeping");
    break;
  
  case SCREEN_MAIN:
    const unsigned char* sprite;
    if (pet.hunger < 30 || pet.happiness < 30 || pet.energy < 30) {
      sprite = SAD_BLOBFI;
    } else if (pet.hunger > 65 && pet.happiness > 65 && pet.energy > 65) {
      sprite = HAPPY_BLOBFI;
    } else {
      sprite = NEUTRAL_BLOBFI;
    }
    display.clearDisplay();

    display.drawBitmap(78, 10, sprite, 32, 22, SSD1306_WHITE);

    display.setTextSize(1);

    display.setCursor(0, 0);
    display.print("Hunger");
    drawBar(0, 9, pet.hunger);

    display.setCursor(0, 18);
    display.print("Happiness");
    drawBar(0, 27, pet.happiness);

    display.setCursor(0, 36);
    display.print("Energy");
    drawBar(0, 45, pet.energy);

    display.setCursor(0, 56);
    display.print("[Feed] [Play] [Sleep]");
    break;
  }

  if (currentScreen != SCREEN_MAIN) {
    for (int i = 0; i < (millis()/200)%4; i++) {
      display.print(".");
    }
  } 

  display.display();
}

void handleSleeping() {
  if (millis() - lastButtonPress > SLEEP_AFTER_INACTIVE_FOR_S * 1000) {
    goSleep();
  }
}

void updatePet() {
  pet.age++;
  pet.energy--;
  pet.happiness--;
  pet.hunger--;

  if (getTempC() > 40 || getTempC() < 5) {
    pet.happiness--;
  }

  if (pet.energy < 0) {pet.energy = 0;}
  if (pet.happiness < 0) {pet.happiness = 0;}
  if (pet.hunger < 0) {pet.hunger = 0;}

  if (pet.energy == 0 || pet.happiness == 0 || pet.hunger == 0) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(VIBRATION_MOTOR, HIGH);
      delay(200);
      digitalWrite(VIBRATION_MOTOR, LOW);
      delay(80);
    }
  }

  lastUpdate = getRtcTime();
}

void handleAwakeUpdating() {
  if (getRtcTime() - lastUpdateBootRelative > UPDATE_DELAY_IN_S * 1000) {
    updatePet();
  }
}

void loop() {
  handleButtons();
  render();
  handleSleeping();
  delay(100);
}
