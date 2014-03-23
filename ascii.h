#ifndef ascii_h
#define ascii_h
#include <avr/pgmspace.h>



PROGMEM  const unsigned char letters[] = {
// Blank - 0  
0b00000000, 
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
  
// A - 1
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b01000010,
0b01000010,
0b01000010,

// B - 2
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b01000010,
0b01000010,
0b01111110,

// C - 3
0b00000000, 
0b01111110,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01111110,

// D - 4
0b00000000, 
0b01111000,
0b01000100,
0b01000010,
0b01000010,
0b01000010,
0b01000100,
0b01111000,

// E - 5
0b00000000, 
0b01111110,
0b01000000,
0b01000000,
0b01111110,
0b01000000,
0b01000000,
0b01111110,

// F - 6
0b00000000, 
0b01111110,
0b01000000,
0b01000000,
0b01111110,
0b01000000,
0b01000000,
0b01000000,

// G - 7
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b00000010,
0b00000010,
0b01111110,

// H - 8
0b00000000, 
0b01000010,
0b01000010,
0b01000010,
0b01111110,
0b01000010,
0b01000010,
0b01000010,

// I - 9
0b00000000, 
0b01111110,
0b00010000,
0b00010000,
0b00010000,
0b00010000,
0b00010000,
0b01111110,

// J - 10
0b00000000, 
0b01111110,
0b00000010,
0b00000010,
0b00000010,
0b01000010,
0b01100110,
0b01111100,

//K - 11
0b00000000, 
0b01000110,
0b01001000,
0b01010000,
0b01100000,
0b01010000,
0b01001000,
0b01000110,

// L - 12
0b00000000, 
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01111110,

// M - 13
0b00000000, 
0b01000010,
0b01100110,
0b01011010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,

// N - 14
0b00000000, 
0b01000010,
0b01100110,
0b01010010,
0b01001010,
0b01001010,
0b01000110,
0b01000010,

// O - 15
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01111110,

// P - 16
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b01000000,
0b01000000,
0b01000000,

// Q - 17
0b00000000, 
0b01000010,
0b01100110,
0b01011010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,

// R - 18
0b00000000, 
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b01100000,
0b01011000,
0b01000110,

// S - 19
0b00000000, 
0b01111110,
0b01000000,
0b01000000,
0b01111110,
0b00000010,
0b00000010,
0b01111110,

// T - 20
0b00000000, 
0b01111110,
0b00010000,
0b00010000,
0b00010000,
0b00010000,
0b00010000,
0b00010000,

// U - 21
0b00000000, 
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01111110,

// V - 22
0b00000000, 
0b01000010,
0b01000110,
0b01000100,
0b00100100,
0b00101100,
0b00011000,
0b00011000,

// w - 23
0b00000000, 
0b10000010,
0b10010010,
0b10010010,
0b10010010,
0b10010010,
0b10010010,
0b11111110,

// x - 24
0b00000000, 
0b01000010, 
0b00100010, 
0b00010100, 
0b00001000, 
0b00010100, 
0b00100010, 
0b01000010,

// y - 25
0b00000000, 
0b01000010, 
0b00100010, 
0b00010100, 
0b00001000, 
0b00001000, 
0b00001000, 
0b00001000,

//26
0b00000000, 
0b11111110, 
0b00000100, 
0b00001000, 
0b00010000, 
0b00100000, 
0b01000000, 
0b11111110,

//27
0b11111111, 
0b00000000, 
0b00000000, 
0b00000000, 
0b00000000, 
0b00000000, 
0b00000000, 
0b11111111,

//28
0b00000000,
0b01000000,
0b01110000,
0b01111100, 
0b01111100, 
0b01110000, 
0b01000000, 
0b00000000,

//29
0b00000010,
0b00000110,
0b00001110,
0b00111110, 
0b00111110, 
0b00001110, 
0b00000110, 
0b00000010};

// Array with numbers, "-", ".", ":" and blank

PROGMEM  const char numbers[] = {
  // -  
0b00000000,
0b00000000,
0b00000000,
0b01111110,
0b01111110,
0b00000000,
0b00000000,
0b00000000, 

// .  
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00111000,
0b00111000,  
  
// /
0b00000000,
0b00000010,
0b00000010,
0b00000100,
0b00001000,
0b00010000,
0b00100000,
0b01000000,
  
// 0  
0b00000000,
0b01111110,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01000010,
0b01111110,

  // 1
0b00000000,
0b00010000,
0b00110000,
0b01010000,
0b00010000,
0b00010000,
0b00010000,
0b01111110,

// 2
0b00000000,
0b01111110,
0b00000010,
0b00000010,
0b01111110,
0b01000000,
0b01000000,
0b01111110,

// 3
0b00000000,
0b01111110,
0b00000010,
0b00000010,
0b00111110,
0b00000010,
0b00000010,
0b01111110,

// 4
0b00000000,
0b01000010,
0b01000010,
0b01000010,
0b01111110,
0b00000010,
0b00000010,
0b00000010,

// 5
0b00000000,
0b01111110,
0b01000000,
0b01000000,
0b01111110,
0b00000010,
0b00000010,
0b01111110,

// 6
0b00000000,
0b01111110,
0b01000000,
0b01000000,
0b01111110,
0b01000010,
0b01000010,
0b01111110,

// 7
0b00000000,
0b01111110,
0b01000010,
0b00000100,
0b00001000,
0b00010000,
0b00100000,
0b00100000,

// 8
0b00000000,
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b01000010,
0b01000010,
0b01111110,

// 9
0b00000000,
0b01111110,
0b01000010,
0b01000010,
0b01111110,
0b00000010,
0b00000010,
0b00000010,

0b00000000,
0b00000000,
0b00011100,
0b00011100,
0b00000000,
0b00011100,
0b00011100,
0b00000000,

0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000};

// Large numbers. I prefer the large numbers, but feel free to use the smaller ones.

PROGMEM  const unsigned char LargeNumbers[] ={
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00111111,0b11111100,
0b01111111,0b11111110,
0b01111111,0b11111110,
0b01111111,0b11111110,
0b00111111,0b11111100,  
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

// 1
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000011,0b11000000,
0b00000111,0b11100000,
0b00000111,0b11100000,
0b00000111,0b11100000,
0b00000111,0b11100000,  
0b00000011,0b11000000,

// 2
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000011,0b10000000,
0b00000111,0b11000000,
0b00000111,0b11000000,
0b00000011,0b10000000,  
0b00000000,0b00000000, 
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000011,0b10000000,
0b00000111,0b11000000,
0b00000111,0b11000000,
0b00000011,0b10000000,  
0b00000000,0b00000000, 
0b00000000,0b00000000,

// 3
0b00000000,0b00000000,
0b00001111,0b11110000,
0b00011111,0b11111000,
0b00111111,0b11111000,
0b01111100,0b01111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111100,0b00111100,
0b00111111,0b11111000,
0b00011111,0b11111000,
0b00001111,0b11110000,

// 4
0b00000000,0b00000000,
0b00000001,0b11000000,
0b00000111,0b11000000,
0b00001111,0b11000000,
0b00011111,0b11000000,
0b00011111,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00000011,0b11000000,
0b00011111,0b11111000,
0b00111111,0b11111100,
0b00011111,0b11111000,

// 5
0b00000000,0b00000000,
0b00001111,0b11100000,
0b00011111,0b11110000,
0b00111111,0b11111000,
0b01111000,0b00111000,
0b01110000,0b00111000,
0b00000000,0b00111000,
0b00000000,0b11111000,
0b00000001,0b11110000,
0b00000111,0b11100000,
0b00011111,0b11000000,
0b00011110,0b00000000,
0b00111100,0b00000000,
0b00111111,0b11111000,
0b01111111,0b11111100,
0b00111111,0b11111000,

// 6
0b00000000,0b00000000,
0b00001111,0b11000000,
0b00111111,0b11110000,
0b00111111,0b11111000,
0b00111000,0b01111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000011,0b11111000,
0b00000111,0b11110000,
0b00000011,0b11111000,
0b00000000,0b01111100,
0b00000000,0b00111100,
0b00111000,0b01111000,
0b01111111,0b11111000,
0b00111111,0b11110000,
0b00001111,0b11000000,


// 7
0b00000000,0b00000000,
0b00110000,0b00011000,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111000,0b00111100,
0b01111111,0b11111100,
0b01111111,0b11111100,
0b00111111,0b11111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000000,0b00011000,

// 8
0b00000000,0b00000000,
0b00111111,0b11111000,
0b01111111,0b11111100,
0b01111111,0b11111000,
0b01111000,0b00000000,
0b01111000,0b00000000,
0b01111000,0b00000000,
0b01111111,0b11100000,
0b01111111,0b11111000,
0b00111111,0b11111100,
0b00000000,0b01111100,
0b00000000,0b00111100,
0b00111000,0b01111000,
0b01111111,0b11111000,
0b00111111,0b11110000,
0b00001111,0b11000000,

// 9
0b00000000,0b00000000,
0b00001111,0b11000000,
0b00011111,0b11110000,
0b00111111,0b11111000,
0b01111100,0b00111000,
0b01111000,0b00000000,
0b01111000,0b00000000,
0b11111111,0b11000000,
0b11111111,0b11111000,
0b11111111,0b11111100,
0b11110000,0b01111100,
0b11110000,0b00111100,
0b01111000,0b01111000,
0b01111111,0b11111000,
0b00111111,0b11110000,
0b00001111,0b11000000,

// 10
0b00000000,0b00000000,
0b00111111,0b11111000,
0b01111111,0b11111100,
0b00111111,0b11111100,
0b00000000,0b00111100,
0b00000000,0b00111100,
0b00000000,0b01111000,
0b00000000,0b11111000,
0b00000000,0b11110000,
0b00000001,0b11100000,
0b00000011,0b11000000,
0b00000111,0b10000000,
0b00001111,0b00000000,
0b00011111,0b00000000,
0b00111110,0b00000000,
0b00111100,0b00000000,

// 11
0b00000000,0b00000000,
0b00000111,0b11110000,
0b00011111,0b11111000,
0b00111111,0b11111100,
0b00111000,0b00011100,
0b00111000,0b00011100,
0b00111100,0b00111100,
0b00011111,0b11111000,
0b00001111,0b11110000,
0b00011111,0b11111000,
0b00111100,0b00111100,
0b00111000,0b00011100,
0b00111000,0b00011100,
0b00111111,0b11111100,
0b00011111,0b11111000,
0b00000111,0b11110000,

// 12
0b00000000,0b00000000,
0b00000111,0b11100000,
0b00011111,0b11111000,
0b00111111,0b11111100,
0b01111100,0b00111100,
0b01111000,0b00011110,
0b01111100,0b00011110,
0b01111111,0b11111110,
0b00111111,0b11111110,
0b00000111,0b11111110,
0b00000000,0b00111110,
0b00111000,0b00111110,
0b01111100,0b01111100,
0b01111111,0b11111100,
0b00111111,0b11111100,
0b00001111,0b11110000,

// 13
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00111111,0b11111100,
0b01111111,0b11111110,
0b01111111,0b11111110,
0b01111111,0b11111110,
0b00111111,0b11111100,  
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

// 14
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

// 15
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00111000,0b00000000,
0b01111100,0b00000000,
0b11111110,0b00000000,
0b11111110,0b00000000,
0b01111100,0b00000000,  
0b00111000,0b00000000};


PROGMEM const unsigned char HomeArrow[] ={
0b00000000,0b00000000,
0b00000001,0b10000000,
0b00000011,0b11000000,  
0b00000111,0b11100000,  
0b00001111,0b11110000,  
0b00011111,0b11111000,  
0b00111111,0b11111100,  
0b00111111,0b11111100,  
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000, 
0b00000001,0b10000000,  

0b00000000,0b00000000,  
0b00000000,0b00000000,  
0b00000111,0b11111110,  
0b00000111,0b11111110,  
0b00000011,0b11111110, 
0b00000001,0b11111110,
0b00000001,0b11111110,  
0b00000011,0b11111110,  
0b00000111,0b11111110,
0b00001111,0b10001110,  
0b00011111,0b00000110,  
0b00111110,0b00000000,  
0b01111100,0b00000000,
0b01111000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,  

0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b01100000,
0b00000000,0b01110000,
0b00000000,0b01111000,
0b00000000,0b11111100,
0b01111111,0b11111110,
0b11111111,0b11111110,
0b11111111,0b11111110,
0b01111111,0b11111110,
0b00000000,0b01111100,
0b00000000,0b01111000,
0b00000000,0b01110000,
0b00000000,0b01100000,
0b00000000,0b00000000,
0b00000000,0b00000000,

0b00000000,0b00000000,
0b00000000,0b00000000, 
0b00000000,0b00000000, 
0b01110000,0b00000000,  
0b11111000,0b00000000,
0b01111100,0b00000000,  
0b00111110,0b00000110,  
0b00011111,0b00001110, 
0b00001111,0b10011110,
0b00000111,0b11111110,  
0b00000011,0b11111110,   
0b00000001,0b11111110,    
0b00000001,0b11111110,  
0b00000011,0b11111110,   
0b00000111,0b11111110, 
0b00000111,0b11111110,

0b00000000,0b00000000,
0b00000001,0b10000000,
0b00000011,0b11000000, 
0b00000011,0b11000000, 
0b00000011,0b11000000,  
0b00000011,0b11000000,  
0b00000011,0b11000000, 
0b00000011,0b11000000,
0b00000011,0b11000000,  
0b00111111,0b11111100,  
0b00111111,0b11111100,
0b00011111,0b11111000,  
0b00001111,0b11110000,  
0b00000111,0b11100000,  
0b00000011,0b11000000,  
0b00000001,0b10000000,

0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00111100,
0b00000000,0b01111100,
0b00000000,0b11111000,
0b11000001,0b11110000,
0b11100011,0b11100000,
0b11111111,0b11000000,
0b11111111,0b10000000,
0b11111111,0b10000000,
0b11111111,0b11100000,
0b11111111,0b11110000,
0b11111111,0b11110000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000110,0b00000000,
0b00001110,0b00000000,
0b00011110,0b00000000,
0b00111110,0b00000000,
0b01111111,0b11111100,
0b01111111,0b11111110,
0b01111111,0b11111110,
0b01111111,0b11111100,
0b00111110,0b00000000,
0b00011110,0b00000000,
0b00001110,0b00000000,
0b00000110,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b11100000,
0b01111111,0b11100000,
0b01111111,0b11000000,
0b01111111,0b10000000,
0b01111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11100000,
0b01110001,0b11110000,
0b01100000,0b11111100,
0b00000000,0b01111110,
0b00000000,0b00111110,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000};

#endif
