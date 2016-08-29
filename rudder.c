/**
 * Read the rudder angle from I2C ATD and calibrate into degrees
 *
 * @return int
 */
int get_rudder_angle() {
	int current_rudder_angle = 0;

	print_to_screen( "global", "current rudder angle", current_rudder_angle );

	return current_rudder_angle;
}