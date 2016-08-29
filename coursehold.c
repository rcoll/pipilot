/**
 * PiPilot course hold slave loop
 *
 * @return void
 */
void pipilot_run_coursehold() {
	print_to_screen( "coursehold", "initializing", 0 );

	int loop_i = 1;

	while ( MODE_COURSEHOLD == get_master_mode() ) {
		print_to_screen( "coursehold", "loop iteration", loop_i );

		// Vars that go into PID
		int selected_course = get_selected_course();
		int actual_heading = get_actual_heading();
		int current_rudder_angle = get_rudder_angle();

		// PID
		int new_rudder_angle = coursehold_pid( selected_course, actual_heading, current_rudder_angle );

		// Change rudder
		set_rudder_angle( new_rudder_angle );

		// 1-second delay
		usleep( 1000000 );

		loop_i++;
	}
}