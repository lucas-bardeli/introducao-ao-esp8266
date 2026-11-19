/*
  Exemplo de uso do display no ESP8266 com comunicação I2C
  Modelo Aliexpress HW-364A - Link: https://pt.aliexpress.com/item/1005006263058736.html
  OBS: As portas SDA e SCL estão invertidas no link do produto
  Documentação da biblioteca U8g2 - https://github.com/olikraus/u8g2/wiki/
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

const int SDA_PORT = 14; // Variável declarada para uso nessa placa - porta SDA
const int SCL_PORT = 12; // Variável declarada para uso nessa placa - porta SCL

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption.
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE); // All Boards without Reset of the Display
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL_PORT, SDA_PORT, U8X8_PIN_NONE); // Display I2C emulado

void setup(void)
{
  u8g2.begin();           // Inicializa o display
  u8g2.enableUTF8Print(); // Habilitar a impressão UTF-8 no display
}

void loop(void)
{
  u8g2.clearBuffer();                         // Clear the internal memory
  u8g2.setFont(u8g2_font_sirclivethebold_tr); // Choose a suitable font
  u8g2.drawStr(0, 8, "Hello World!");         // Write something to the internal memory
  u8g2.drawStr(0, 24, "Bem vindo a");         // Write something to the internal memory
  u8g2.drawStr(20, 36, "FATEC Jahu");         // Escrevendo linha 3
  u8g2.sendBuffer();                          // Transfer internal memory to the display
  delay(10000);
}
