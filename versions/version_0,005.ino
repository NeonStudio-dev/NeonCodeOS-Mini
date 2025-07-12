#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Przypisanie pinów przycisków
#define BUTTON_UP     2
#define BUTTON_DOWN   3
#define BUTTON_SELECT 4

// Zmienne systemowe
int menuIndex = 0;
String menuItems[] = {"Notatnik", "Ustawienia", "Dev Mode", " " , "Update"};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
bool inMenu = false;

void setup() {
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  showBootScreen();
  delay(2000);
  displayMainMenu();
}

void loop() {
  if (!inMenu) return;

  if (digitalRead(BUTTON_UP) == LOW) {
    menuIndex--;
    if (menuIndex < 0) menuIndex = menuLength - 1;
    displayMainMenu();
    delay(200);
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    menuIndex++;
    if (menuIndex >= menuLength) menuIndex = 0;
    displayMainMenu();
    delay(200);
  }

  if (digitalRead(BUTTON_SELECT) == LOW) {
    runApp(menuIndex);
    delay(300);
  }
}

void showBootScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print("NeonCode-OS");
  display.println("--MINI--");
  display.display();
}

void displayMainMenu() {
  inMenu = true;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  for (int i = 0; i < menuLength; i++) {
    if (i == menuIndex) {
      display.setCursor(0, i * 10);
      display.print("> ");
    } else {
      display.setCursor(0, i * 10);
      display.print("  ");
    }
    display.print(menuItems[i]);
  }
  display.display();
}

void runApp(int index) {
  inMenu = false;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Uruchamianie: ");
  display.println(menuItems[index]);
  display.println("--------------------");
  display.display();
  delay(1000);

  if (index == 0) {
    notepadApp();
  } else if (index == 1) {
    settingsApp();
  } else if (index == 2) {
    devMode();
  } else if (index == 4) {
    updateApp();
  } else if (index == 3) {
    easterEgg();
  }

  displayMainMenu();
}

// Szkielet aplikacji

void notepadApp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Notatnik [not good]");
  display.println("-tekst");
  display.println("- co chez napisac");
  display.display();
  waitForBack();
}

void settingsApp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Ustawienia");
  display.println("- Dźwięk");
  display.println("- Aplikacje");
  display.println("- gry i fps");
  display.println("- Kontrast");
  display.display();
  waitForBack();
}

void devMode() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Dev Mode");
  display.println("- Debug: OK");
  display.println("- Mode: Just NEON");
  display.println("- neoncode the best");
  display.display();
  waitForBack();
}
void easterEgg() {
  display.clearDisplay();
  display.setCursor(0 , 0);
  display.println("NEONCODEos");
  display.println("oh you here ");
  display.println("easter egg of neon");
  display.println("--------O----------");
}

void updateApp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("what's new on NeonCode");
  display.println("-new apps ");
  display.println("-better graphics");
  display.println("version 0.005 beta");
}

void waitForBack() {
  display.setCursor(0, 50);
  display.println("Kliknij SELECT");
  display.display();
  while (digitalRead(BUTTON_SELECT) == HIGH);
  delay(300);
}
