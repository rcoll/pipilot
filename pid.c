unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp, ki, kd;

void set_pid_tuning( double Kp, double Ki, double Kd ) {
	kp = Kp;
	ki = Ki;
	kd = Kd;
}

void coursehold_pid_compute() {
   // How long since we last calculated
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   // Compute all the working error variables
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;
  
   // Compute PID Output
   Output = kp * error + ki * errSum + kd * dErr;
  
   // Remember some variables for next time
   lastErr = error;
   lastTime = now;
}

/**
 * Calculate an ideal rudder angle based on the difference 
 * between the selected course and the magnetic heading.
 *
 * @param int diff The difference between heading and course
 *
 * @return int Rudder angle (0-45)
 */
int calc_rudder_gain( int diff ) {
	float gain;

	// Ensure we have a positive integer to work with
	diff = abs( diff );

	// Maximum difference of 90 degrees - above 90 degrees, we'll use
	// the same rate of turn regardless of the distance
	if ( diff > 90 ) diff = 90;

	// Differences less than 10 (minimum threshold)
	if ( diff < 10 ) gain = diff / 4;

	// Our diff/gain map
	if ( diff >= 10 && diff < 20 ) gain = diff / 3.5;
	if ( diff >= 20 && diff < 30 ) gain = diff / 3;
	if ( diff >= 30 && diff < 40 ) gain = diff / 2;
	if ( diff >= 40 && diff < 50 ) gain = diff / 1.4;
	if ( diff >= 50 && diff < 70 ) gain = diff / 1.3;
	if ( diff >= 70 && diff < 90 ) gain = diff / 1.2;

	// Differences higher than 90 degrees get equal treatment
	if ( diff >= 90 ) gain = diff / 1.1;
	
	// Reduce the gain to a usable rudder angle
	gain = gain / 1.8;

	// Return as integer
	return (int) floor( gain );
}

void rudder_center() {}
void rudder_left() {}
void rudder_right() {}

/**
 * Determine what rudder action to take (left/center/right) based on
 * course, heading, and rudder position
 *
 * @param int course Current course setting
 * @param int heading Current magnetic heading
 * @param int rudder Current rudder angle (0-9)
 *
 * @return void
 */
void execute_rudder_action( int course, int heading, int rudder ) {
	
	// Get the heading delta
	int coursediff = course - heading;

	// Calculate rudder gain
	int gain = calc_rudder_gain( coursediff );

	// Currently on course
	if ( heading == course ) {
		// We are tracking perfectly center
		if ( rudder == 0 ) {
			rudder_center(); 
		}

		// We are going to end up right of course
		if ( rudder > 0 ) {
			rudder_center();
		}

		// We are going to end up left of course
		if ( rudder < 0 ) {
			rudder_center();
		}
	}

	// Currently left of course
	if ( heading < course ) {
		// We are just starting a turn to the right
		if ( rudder == 0 ) {
			rudder_right();
		}

		// We are already in a turn to the right
		if ( rudder > 0 ) {
			rudder_center();
		}

		// We are turning left - rudder_center() then start turn to right
		if ( rudder < 0 ) {
			rudder_right();
		}
	}

	// Currently right of course
	if ( heading > course ) {
		// We are just starting a turn to the left
		if ( rudder == 0 ) {
			rudder_left();
		}

		// We are turning right - rudder_center() then start turn to left
		if ( rudder > 0 ) {
			rudder_left();
		}

		// We are already in a turn to the left
		if ( rudder < 0 ) {
			rudder_center();
		}
	}
}

int coursehold_pid( int selected_course, int actual_heading, int current_rudder_angle ) {
	print_to_screen( "coursehold", "pid equation", 0 );

	int factor = 1;
	int delta = 0;
	int diff = 0;

	diff = selected_course - actual_heading;

	if ( diff < 0 ) {
		factor = -1;
	}

	diff = abs( diff );

	if ( diff > 44 && diff <= 50 ) delta = 9;
	if ( diff > 30 && diff <= 40 ) delta = 8;
	if ( diff > 20 && diff <= 30 ) delta = 7;
	if ( diff == 20 )              delta = 6;
	if ( diff > 17 && diff <= 19 ) delta = 5;
	if ( diff > 14 && diff <= 17 ) delta = 3;
	if ( diff > 10 && diff <= 14 ) delta = 2;
	if ( diff > 5 && diff <= 10 ) delta = 1;

	return delta * factor;
}

int ellipse_pid( int selected_radius, int current_rudder_angle ) {
	return 0;
}
