/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid.c
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */

#include "raid.h"

void message_error( Event event_type )
{
    printf( "Unexpected Message Type (%d)\n", event_type );
    exit( -1 );
}

int main( int argc, char** argv )
{
    return 0;
}
