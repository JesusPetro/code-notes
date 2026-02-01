#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* VARIALBES A UTILIZAR*/
byte barChar[8];       // píxeles de cada casilla
int n = 0;             // píxeles encendidos (0..5)
int lcd_row = 0;       // fila del carácter (0..7)
int lcd_col = 0;       // columna del carácter (0..5)

int colChar = 0;

bool mitadDibujada = false;  

void resetFill(){
  for (int i = 0; i < 8; i++) barChar[i] = 0b00000;
}

void makeRowFill(int row, int n){
  if (n < 0) n = 0;
  if (n > 5) n = 5;

  byte mask = (1 << n) - 1;
  mask <<= (5 - n);

  barChar[row] = mask;
}

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop(){
  makeRowFill(lcd_row, n);

  // Dibujamos la mitad izquierda una sola vez
  if (colChar >= 8 && !mitadDibujada){
    for (int c = 0; c < 8; c++) {
      lcd.setCursor(c, 1);
      lcd.write((char)255);
    }
    mitadDibujada = true;
  }

  int charIndex = colChar % 8;

  lcd.createChar(charIndex, barChar);
  lcd.setCursor(colChar, 1);
  lcd.write(byte(charIndex));

  lcd_row++;
  
  if (lcd_row > 7){

    // Avance del relleno
    lcd_row = 0;
    n++;

    // Avance de colChar
    if (n > 5) {
      resetFill(); // Reiniciamos nuestro barChar

      n = 0;
      colChar++;

      if (colChar >= 16){
        colChar = 0;
        mitadDibujada = false;
        lcd.clear();
      }
    }
  }

}