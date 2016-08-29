// Loop modes
#define MODE_DISABLED         ( 1 )
#define MODE_COURSEHOLD       ( 2 )
#define MODE_ELLIPSE          ( 3 )
#define MODE_PLOTTER          ( 4 )
#define MODE_TACK             ( 5 )

// wiringPi pin numbers
#define PIN_RELAY_LEFT        ( 0 )
#define PIN_RELAY_RIGHT       ( 2 )
#define PIN_SWITCH_COURSEHOLD ( 3 )
#define PIN_SWITCH_ELLIPSE    ( 6 )
#define PIN_SWITCH_PLOTTER    ( 5 )

// Mathematics
#define PI 3.14159265

// Mathematics macros
#define degreesToRadians(angleDegrees) ( angleDegrees * M_PI / 180.0 )
#define radiansToDegrees(angleRadians) ( angleRadians * 180.0 / M_PI )

// Global vars
int fd;
struct encoder *rencoder;
int encodervalue;

// Prototypes
void print_to_screen( char * module, char * line, int val );
void set_rudder_angle( int angle );
void log_debug( char * message );
void log_info( char * message );
void log_error( char * message );