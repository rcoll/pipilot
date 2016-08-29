/**
 * Get magnetic heading from hmc5883l magnetometer
 * 
 * @param int fd Device connection
 * @return int Magnetic heading
 */
double get_magnetic_heading( int fd ) {
	wiringPiI2CWriteReg8( fd, 0x02, 0x00 );

	uint8_t xmsb = wiringPiI2CReadReg8( fd, 0x03 );
	uint8_t xlsb = wiringPiI2CReadReg8( fd, 0x04 );
	uint8_t ymsb = wiringPiI2CReadReg8( fd, 0x07 );
	uint8_t ylsb = wiringPiI2CReadReg8( fd, 0x08 );
	uint8_t zmsb = wiringPiI2CReadReg8( fd, 0x05 );
	uint8_t zlsb = wiringPiI2CReadReg8( fd, 0x06 );

	short x = xmsb << 8 | xlsb;
	short y = ymsb << 8 | ylsb;

	double hdg = atan2( (double) y, (double) x ) * ( 180 / PI ) + 180;
	int heading = (int) hdg;

	return heading;
}

/**
 * Get and calibrate the magnetic heading
 *
 * @return int
 */
int get_actual_heading() {
	// Get reading from compass
	int uncalibrated = get_magnetic_heading( fd );

	// Do some stuff with uncalibrated heading
	// foo
	// bar

	print_to_screen( "global", "uncalibrated heading", uncalibrated );

	// Return 
	return uncalibrated;
}