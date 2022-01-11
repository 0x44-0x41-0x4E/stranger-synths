#include <LiquidCrystal.h>

// initialize the lcd with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// MENU VARIABLES
String currentMenu = "main";
uint8_t menuSelection = 0;
String menus[] = { "keySelection", "waveSelection"};
String keys[] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
String modes[] = { "dur", "mol"};
int selectedKey = 0;
int selectedMode = 0;
uint8_t menuLength = 0;

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

  menuLength = 2;

  String saw = "Saw";

  String key = "Key: " + keys[selectedKey] + " " + modes[selectedMode];
  String wave = "Wave: " + saw;
  
  lcd.setCursor(0, 0);
  menuSystem_print(key, menuSelection == 0);

  lcd.setCursor(0, 1);
  menuSystem_print(wave, menuSelection == 1);
}

void menuSystem_keySelection() {

  menuLength = 12;
  
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

  selectedKey = menuSelection;
  
}

void menuSystem_modeSelection() {

  menuLength = 2;

  if (menuSelection == 0) {
    lcd.setCursor(0,0);
    menuSystem_print("Dur", true);
    lcd.setCursor(0,1);
    menuSystem_print("Mol", false);
  } else if (menuSelection == 1) {
    lcd.setCursor(0,0);
    menuSystem_print("Dur", false);
    lcd.setCursor(0,1);
    menuSystem_print("Mol", true);
  }

  selectedMode = menuSelection;
  
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
  } else if (_menu == "modeSelection") {
    menuSystem_modeSelection();
  } else {
    menuSystem_goToMenu("main");
  }
}

void menuSystem_refresh () {
  menuSystem_goToMenu(currentMenu);
}

void menuSystem_goDown() {
  if (menuSelection >= menuLength - 1) {
    menuSelection = 0;
  } else {
    menuSelection++;
  }
  menuSystem_refresh();
}

void menuSystem_onButtonPress() {
  if (currentMenu == "main") {
    menuSystem_goToMenu(menus[menuSelection]);
  } else if (currentMenu == "keySelection") {
    menuSystem_goToMenu("modeSelection");
  } else if (currentMenu == "modeSelection") {
    if (selectedMode == 0) {
      musicSettings_setScale(selectedKey, scaleBlueprint_DurPentaton);
    } else if (selectedMode == 1) {
      musicSettings_setScale(selectedKey, scaleBlueprint_MolPentaton);
    }
    
    menuSystem_goToMenu("main");
  }
}
