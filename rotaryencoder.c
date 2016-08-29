#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define max_encoders 8

struct encoder {
	int pin_a;
	int pin_b;
	volatile long value;
	volatile int lastEncoded;
};

struct encoder encoders[max_encoders];

struct encoder *setupencoder( int pin_a, int pin_b );

int numberofencoders = 1;
int encodervalue = 0;

void updateEncoders() {
	struct encoder *encoder = encoders;
	
	for ( ; encoder < encoders + numberofencoders; encoder++ ) {
		int MSB = digitalRead( encoder->pin_a );
		int LSB = digitalRead( encoder->pin_b );

		int encoded = ( MSB << 1 ) | LSB;
		int sum = ( encoder->lastEncoded << 2 ) | encoded;

		if ( sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011 ) {
			if ( encoder->value >= 360 ) {
				encoder->value = 1;
			} else {
				encoder->value++;
			}
		}

		if ( sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000 ) {
			if ( encoder->value <= 1 ) {
				encoder->value = 360;
			} else {
				encoder->value--;
			}
		}

		printf( "Set course: %d\n", encoder->value );
		encodervalue = encoder->value;

		encoder->lastEncoded = encoded;
	}
}

struct encoder *setupencoder( int pin_a, int pin_b ) {
	if ( numberofencoders > max_encoders ) {
		printf( "Maximum number of encodered exceded: %i\n", max_encoders );
		return NULL;
	}

	struct encoder *newencoder = encoders + numberofencoders++;

	newencoder->pin_a = pin_a;
	newencoder->pin_b = pin_b;
	newencoder->value = 0;
	newencoder->lastEncoded = 0;

	pinMode( pin_a, INPUT );
	pinMode( pin_b, INPUT );
	pullUpDnControl( pin_a, PUD_UP );
	pullUpDnControl( pin_b, PUD_UP );
	wiringPiISR( pin_a,INT_EDGE_BOTH, updateEncoders );
	wiringPiISR( pin_b,INT_EDGE_BOTH, updateEncoders );

	return newencoder;
}

int get_selected_course() {
	int selected_course = encodervalue;

	if ( encodervalue <= 0 )
		encodervalue = 1;

	print_to_screen( "coursehold", "get selected course", selected_course );
	
	return selected_course;
}

// EOF