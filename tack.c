/**
 * PiPilot tack loop
 *
 * @return void
 */
void pipilot_run_tack() {
	print_to_screen( "tack", "initializing", 0 );

	int loop_i = 1;

	while ( MODE_TACK == get_master_mode() ) {
		print_to_screen( "tack", "loop iteration", loop_i );

		// Vars that go into PID
		int selected_radius = get_selected_course(); // @todo - total hack
		int current_rudder_angle = get_rudder_angle();

		// PID
		int new_rudder_angle = ellipse_pid( selected_radius, current_rudder_angle );

		// Change rudder
		set_rudder_angle( new_rudder_angle );

		// 1-second delay
		usleep( 1000000 );

		loop_i++;
	}
}