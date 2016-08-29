/**
 * Set the rudder to a current angle of +/- 30 degrees
 *
 * @return void
 */
void set_rudder_angle( int angle ) {
	print_to_screen( "global", "set rudder angle", angle );

	if ( angle > 0 ) {
		digitalWrite( PIN_RELAY_RIGHT, 1 );
		usleep( 500000 );
		digitalWrite( PIN_RELAY_RIGHT, 0 );
	}

	if ( angle < 0 ) {
		digitalWrite( PIN_RELAY_LEFT, 1 );
		usleep( 500000 );
		digitalWrite( PIN_RELAY_LEFT, 0 );
	}
}