/**
 * Get the position of the function selector switch
 *
 * @return int Selected mode
 */
int get_master_mode() {
	if ( 1 == digitalRead( PIN_SWITCH_COURSEHOLD ) ) {
		print_to_screen( "mode", "coursehold", 0 );
		return MODE_COURSEHOLD;
	}

	if ( 1 == digitalRead( PIN_SWITCH_ELLIPSE ) ) {
		print_to_screen( "mode", "ellipse", 0 );
		return MODE_ELLIPSE;
	}

	if ( 1 == digitalRead( PIN_SWITCH_PLOTTER ) ) {
		print_to_screen( "mode", "plotter", 0 );
		return MODE_PLOTTER;
	}

	print_to_screen( "mode", "disabled", 0 );
	return MODE_DISABLED;
}