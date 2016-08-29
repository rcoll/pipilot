/**
 * Send a line of text to the debug log
 *
 * @return void
 */
void log_debug( char * message ) {
	openlog( "pipilot", LOG_PID|LOG_CONS, LOG_USER );
	syslog( LOG_DEBUG, message );
	closelog();
}

/**
 * Send a line of text to the info log
 *
 * @return void
 */
void log_info( char * message ) {
	openlog( "pipilot", LOG_PID|LOG_CONS, LOG_USER );
	syslog( LOG_INFO, message );
	closelog();
}

/**
 * Send a line of text to the error log
 *
 * @return void
 */
void log_error( char * message ) {
	openlog( "pipilot", LOG_PID|LOG_CONS, LOG_USER );
	syslog( LOG_ERR, message );
	closelog();
}

