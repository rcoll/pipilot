/**
 * Print a formatted line of text to the screen
 *
 * @return void
 */
void print_to_screen( char * module, char * line, int val ) {
	time_t timer;
	char timestamp[26];
	struct tm* info;
	
	time( &timer );
	info = localtime( &timer );
	strftime( timestamp, 26, "%Y-%m-%d-%H:%M:%S", info );

	if ( 0 != val ) {
		printf( "%s pipilot > %s > %s %d\n", timestamp, module, line, val );
	}

	if ( 0 == val ) {
		printf( "%s pipilot > %s > %s\n", timestamp, module, line );
	}
}