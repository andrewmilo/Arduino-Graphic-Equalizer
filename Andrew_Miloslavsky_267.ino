/*
 * Andrew Miloslavsky
 * 
 * Graphic Equalizer Project
 * 
 * This code reads input from the MSGEQ7 Sound Equalizer chip,
 * and then controls an Adafruit 16x32 LED Matrix based off the 
 * amplitudes of frequencies that were read.
 * 
 * Parts:
 *       Arduino UNO R3
 *       Adafruit Electret Microphone
 *       MSGEQ7 Equalizer Chip
 *       Breadboard
 *       5v 2A Power supply for Matrix
 *       5v USB Power for Arduino
 *       
 */

/* Both libraries contain essential low level
*  code for the Arduino to be able to draw pixels
*  on the display.
 */
#include <Adafruit_GFX.h> // For 16x32 matrix
#include <RGBmatrixPanel.h> // For 16x32 matrix

// Define input pins
#define CLK 8
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

#define MIN 120 // Minimum input value to interpret
#define FREQ 7 // Total number of frequencies
#define MAX_COLOR 255 // Max color value
#define MAX_DIGITAL 1024 // Max digital value
#define FADE_RATE 70 // Fade rate for LEDs
#define FREQ_INPUT A5 // Input pin on MSGEQ7
#define FREQ_STROBE 12 // Strobe pin on MSGEQ7
#define SPECT_RESET 13 // Reset pin on MSGEQ7
#define MATRIX_WIDTH 32 // Matrix Width
#define MATRIX_HEIGHT 16 // Matrix Height

// Instantiate matrix
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int rows[ FREQ ]; // rows in matrix

void setup(){
  
  matrix.begin(); // Start matrix

  /* 
   *  Set up pin modes
   */
  pinMode( FREQ_INPUT, INPUT );
  pinMode( FREQ_STROBE, OUTPUT );
  pinMode( SPECT_RESET, OUTPUT );
  analogReference( DEFAULT );
  digitalWrite( SPECT_RESET, LOW );
  digitalWrite( FREQ_STROBE, HIGH );

  // Init
  for ( int s = 0; s < FREQ; s++ )
    rows[ s ] = 0; 
}

void loop(){
  
  read_MSGEQ7(); // Get MSGEQ7 inputs

  // Read input and scale it out of 255
  const int input_val = analogRead( FREQ_INPUT ) 
                  * MAX_COLOR 
                  / MAX_DIGITAL;

  // Iterate through columns
  for( int i = 0; i < MATRIX_WIDTH; i++ ){

    // Scale to matrix
    const int col = i * FREQ 
                / MATRIX_WIDTH;

    // Gets how high the column goes
    const int row = get_row( rows[ col ] );

    // Fill column for row
    for ( int y = MATRIX_HEIGHT; y > row; y-- ){

      // Draw color for row
      draw( i, y, MAX_COLOR, threshold( input_val ) );
    }

    // Erase LEDs
    for ( int y = row; y >= 0; y-- ){
      draw( i, y, 0, 0 );
    }
  }
}

/*
 * Read in input frequencies from MSGEQ7
 */
void read_MSGEQ7(){
  
  digitalWrite( SPECT_RESET, HIGH );
  digitalWrite( SPECT_RESET, LOW );

  // Strobe MSGEQ7 for various frequencies
  for ( int i = 0; i < FREQ; i++ ){
    
    digitalWrite( FREQ_STROBE, LOW );
    delayMicroseconds( 30 );

    // Read in frequency values
    rows[ i ] = analogRead( FREQ_INPUT );
  
    digitalWrite( FREQ_STROBE, HIGH );
  }
}

/*
 * Thresholds the minimum value allowed
 */
int threshold( const int value ){
  
  return value < MIN 
               ? MIN // Enforce min value.
               : value;
}

/*
 * Draws pixels based on HSV
 */
void draw( const int col, 
           const int row, 
           const int saturation,
           const int value ){
  
  matrix.drawPixel( col, // column
                    row, // row
                    matrix.ColorHSV( 1200 // Conversion from
                                   - 80   // HSV to Color
                                   * row, 
                      saturation, 
                      value, 
                      true 
                    ) 
                  );
}

/*
 * Gets the row for a value through scaling
 */
int get_row( const int val ){

  // Scale value to max matrix height
  int scaled = val
                   * MATRIX_HEIGHT
                   / MAX_DIGITAL;

  // Boost
  if( scaled > MATRIX_HEIGHT - 2 )
    scaled += 2;
  
  return MATRIX_HEIGHT - scaled;
}

