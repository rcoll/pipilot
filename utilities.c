struct DmnLatLon {
	int t;
	char latc[1];
	float lat;
	char lonc[1];
	float lon;
};

void print_dmn_point( struct DmnLatLon p, int with_time, int line_breaks ) {
	if ( 1 == with_time ) {
		printf( "%d %4.4f%s%5.4f%s", p.t, p.lat, p.latc, p.lon, p.lonc );
	} else {
		printf( "%f%s %f%s", p.lat, p.latc, p.lon, p.lonc );
	}

	int i;
	for ( i = 0; i < line_breaks; i++ ) {
		printf( "\n" );
	}
}

struct DmsLatLon {
	char latc[1];
	int latd;
	int latm;
	int lats;

	char lonc[1];
	int lond;
	int lonm;
	int lons;

	int t;
};

struct DmsLatLon get_random_dms_point() {
	struct DmsLatLon p;

	strcpy( p.latc, "N" );
	p.latd = 24;
	p.latm = 29;
	p.lats = 834;

	strcpy( p.lonc, "W" );
	p.lond = 80;
	p.lonm = 28;
	p.lons = 931;

	return p;
}

void print_dms_point( struct DmsLatLon p ) {
	printf( "%s %d %d.%d %s %d %d.%d", p.latc, p.latd, p.latm, p.lats, p.lonc, p.lond, p.lonm, p.lons );
}

struct DecLatLon {
	int t;
	float lat;
	float lon;
};

struct DecLatLon get_random_dec_point() {
	struct DecLatLon p;
	
	p.lat = 24.298394;
	p.lon = -80.289384;

	return p;
}

void print_dec_point( struct DecLatLon p, int with_time, int line_breaks ) {
	if ( 1 == with_time ) {
		printf( "%d %2.6f,%2.6f", p.t, p.lat, p.lon );
	} else {
		printf( "%2.6f,%2.6f", p.lat, p.lon );
	}

	int i;
	for ( i = 0; i < line_breaks; i++ ) {
		printf( "\n" );
	}
}

double get_distance_between_points( struct DecLatLon p1, struct DecLatLon p2 ) {
	float dtr = M_PI / 180;
	float phi1 = ( 90 - p1.lat ) * dtr;
	float phi2 = ( 90 - p2.lat ) * dtr;
	float theta1 = p1.lon * dtr;
	float theta2 = p2.lon * dtr;
	float c = ( sin( phi1 ) * sin( phi2 ) * cos( theta1 - theta2 ) + cos( phi1 ) * cos( phi2 ) );
	
	return acos( c ) * 3959;
}

float get_bearing_between_points( struct DecLatLon p1, struct DecLatLon p2 ) {
	float delta = p2.lon - p1.lon;
	float head = atan2( ( sin( delta ) * cos( p2.lat ) ), ( ( cos( p1.lat ) * sin( p2.lat ) ) - ( sin( p1.lat ) * cos( p2.lat ) * cos( delta ) ) ) );
	
	return radiansToDegrees( head );
}

struct DecLatLon dms_to_dec( struct DmsLatLon dms ) {
	struct DecLatLon dec;

	dec.lat = dms.latd + ( dms.latm / 60.0 ) + ( dms.lats / 3600.0 );
	dec.lon = dms.lond + ( dms.lonm / 60.0 ) + ( dms.lons / 3600.0 );

	if ( 0 == strcmp( dms.latc, "S" ) ) {
		dec.lat = dec.lat * -1;
	}

	if ( 0 == strcmp( dms.lonc, "W" ) ) {
		dec.lon = dec.lon * -1;
	}

	return dec;
}

int first_2_of_4( int value ) {
	assert( value >= 0 );

	if ( value >= 100000 ) 
		return value / 10000;
	if ( value >= 10000 )
		return value / 1000;
	if ( value >= 1000 )
		return value / 100;
	if ( value >= 100 )
		return value / 10;
	
	return value;
}

int first_3_of_5( int value ) {
	assert( value >= 0 );

	if ( value >= 100000 )
		return value / 1000;
	if ( value >= 10000 )
		return value / 100;
	if ( value >= 1000 )
		return value / 10;

	return value;
}

int last_2_of_4( int value ) {
	int first2 = first_2_of_4( value );

	return value - first2 * 100;
}

int last_2_of_5( int value ) {
	int first3 = first_3_of_5( value );

	return value - first3 * 100;
}

/**
 * Convert a "decimal-minutes" coordinate to a "decimal-degrees" coordinate
 */
struct DecLatLon dmn_to_dec( struct DmnLatLon dmn ) {
	// Initialize empty lat/lon
	struct DecLatLon dec;
	dec.t = 0;
	dec.lat = 0.00;
	dec.lon = 0.00;

	// Get latd, latm, lats and formulate dec.lat
	double _latdm;
	int latdm = 0, latd = 0, latm = 0;
	double lats = modf( dmn.lat, &_latdm );
	latdm = (int) _latdm;
	latd = first_2_of_4( latdm );
	latm = last_2_of_4( latdm );
	dec.lat = latd + ( latm / 60.0 ) + ( lats / 360.0 );

	// Get lond, lonm, lons and formulate dec.lon
	double _londm;
	int londm = 0, lond = 0, lonm = 0;
	double lons = modf( dmn.lon, &_londm );
	londm = (int) _londm;
	lond = first_3_of_5( londm );
	lonm = last_2_of_5( londm );
	dec.lon = lond + ( lonm / 60.0 ) + ( lons / 360.0 );

	// Make latitude negative if it's a Southern coordinate
	if ( 0 == strcmp( dmn.latc, "S" ) ) {
		dec.lat = dec.lat * -1;
	}

	// Make longitude negative if it's a Western coordinate
	if ( 0 == strcmp( dmn.lonc, "W" ) ) {
		dec.lon = dec.lon * -1;
	}

	// Copy time to new struct
	dec.t = dmn.t;
	
	return dec;
}

// EOF