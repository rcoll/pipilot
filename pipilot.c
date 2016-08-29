#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <syslog.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// Definitions
#include "definitions.h"      // Common definitions

// Program logic
#include "coursehold.c"       // Coursehold control loop
#include "ellipse.c"          // Ellipse control loop
#include "plotter.c"          // Chart plotter control loop
#include "tack.c"             // Tack (zigzag) control loop

// Inputs
#include "hmc5883l.c"         // Magnetometer/compass functions
#include "rotaryencoder.c"    // Rotary encoder for course selector
#include "masterswitch.c"     // Master switch
#include "rudder.c"           // Rudder angle reading

// Controls
#include "steering.c"         // Set rudder angle
#include "throttle.c"         // Set throttle percent

// Math
#include "pid.c"              // PID functions

// Utilities
#include "utilities.c"        // Latitude and Longitude functions
#include "screen.c"           // Functions for writing to various screens
#include "log.c"              // System log functions

/**
 * PiPilot master loop
 *
 * Responsible for initializing the slave function and continuing on to the next 
 * slave function when the master switch is changed. Also holds the loop open 
 * when the function selector is switched to the off position. This allows PiPilot 
 * to run continuously, even when physically switched off.
 *
 * @param int argc Argument count
 * @param char *argv[] Argument list
 *
 * @return void
 */
void main ( int argc, char *argv[] ) {
	print_to_screen( "master", "initializing", 0 );

	// Set up wiringpi
	wiringPiSetup();

	rencoder = setupencoder( 4, 5 );

	// Set up wiringpi I2C for HMC
	fd = wiringPiI2CSetup( 0x1e );

	// Set the master switch pins to input
	pinMode( PIN_SWITCH_COURSEHOLD, INPUT );
	pinMode( PIN_SWITCH_ELLIPSE,    INPUT );
	pinMode( PIN_SWITCH_PLOTTER,    INPUT );

	// Set the directional relay pins to output
	pinMode( PIN_RELAY_LEFT,  OUTPUT );
	pinMode( PIN_RELAY_RIGHT, OUTPUT );

	print_to_screen( "master", "being master loop", 0 );

	// The master loop
	while ( 1 ) {
		print_to_screen( "master", "loop iteration", 0 );

		// Get the master mode from the selector switch
		int mode = get_master_mode();

		// Loop hold when master switch is off
		if ( mode == MODE_DISABLED ) {
			usleep( 1000000 );
			continue;
		}

		// Run coursehold when selected
		if ( mode == MODE_COURSEHOLD ) {
			pipilot_run_coursehold();
		}

		// Run ellipse when selected
		if ( mode == MODE_ELLIPSE ) {
			pipilot_run_ellipse();
		}

		// Run chartplotter when selected
		if ( mode == MODE_PLOTTER ) {
			pipilot_run_plotter();
		}

		// Run tack course when selected
		if ( mode == MODE_TACK ) {
			pipilot_run_tack();
		}
	}
}
