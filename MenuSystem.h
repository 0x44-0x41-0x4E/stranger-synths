#include <LiquidCrystal.h>

// initialize the lcd with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// MENU VARIABLES
String currentMenu = "main";
uint8_t menuSelection = 0;
String keys[] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
String selectedKey = "A";
String selectedMode = "dur";

void menuSystem_setup() {
  // SET UP LCD (rows, col)
  lcd.begin(16, 2);
}

void menuSystem_print (String _line, bool _isSelected) {
  if (_isSelected) {
    lcd.print("> " + _line);
  } else {
    lcd.print("  " + _line);
  }
}

void menuSystem_mainMenu() {

  String fsharp = "F#";
  String saw = "Saw";

  String key = "Key: " + fsharp;
  String wave = "Wave: " + saw;
  
  lcd.setCursor(0, 0);
  menuSystem_print(key, menuSelection == 0);

  lcd.setCursor(0, 1);
  menuSystem_print(wave, menuSelection == 1);
}

void menuSystem_keySelection() {

  if (menuSelection > 11) {
    menuSelection = 0;
  }
  
  if (menuSelection == 0) {
    lcd.setCursor(0, 0);
    menuSystem_print(keys[0], true);
    lcd.setCursor(0, 1);
    menuSystem_print(keys[1], false);
  } else {
    lcd.setCursor(0, 0);
    menuSystem_print(keys[menuSelection - 1], false);
    lcd.setCursor(0, 1);
    menuSystem_print(keys[menuSelection], true);
  }
  
}

void menuSystem_goToMenu (String _menu) {

  if (currentMenu != _menu) {
    menuSelection = 0;
  }
  
  lcd.clear();
  
  currentMenu = _menu;
  if (_menu == "main") {
    menuSystem_mainMenu();
  } else if (_menu == "keySelection") {
    menuSystem_keySelection();
  }
}

void menuSystem_refresh () {
  menuSystem_goToMenu(currentMenu);
}

void menuSystem_goDown() {
  menuSelection++;
  menuSystem_refresh();
}
