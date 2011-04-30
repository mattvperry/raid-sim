/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid-io.c
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */
#include "raid.h"

// Helpers
void raid_io_gen_send( tw_lpid dest, Event next_event_type, tw_stime this_event_length, tw_lp* lp )
{
    // Start time of next event
    tw_stime next_start_time = tw_now( lp ) + this_event_length;

    // Generate and send message to dest
    tw_event* next_event = tw_event_new( dest, next_start_time, lp );
    MsgData* next_message = (MsgData*)tw_event_data( next_event );
    next_message->event_type = next_event_type;
    next_message->rc.io_time = this_event_length;
    tw_event_send( next_event );
}

// Initialize
void raid_io_init( IOState* s, tw_lp* lp )
{
    // Initial State
    s->m_server = 0; // TODO: Properly set fileserver from gid
    s->ttl_busy = 0;
    s->ttl_idle = 0;

    // Initialize event handler
    MsgData* init_msg = (MsgData*)malloc( sizeof( MsgData ) );
    init_msg->event_type = IO_IDLE;
    raid_io_eventhandler( s, NULL, init_msg, lp );
    free( init_msg );
}

// Event Handler
void raid_io_eventhandler( IOState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    Event next_event_type;
    tw_stime this_event_length;

    // Check the message type
    switch( m->event_type )
    {
        case IO_BUSY:
            s->mode = BUSY;
            // Calculate the time to spend in BUSY mode
            this_event_length = BUSY_TIME; // TODO: Make random
            s->ttl_busy += this_event_length; 
            next_event_type = IO_IDLE;
            break;
        case IO_IDLE:
            s->mode = IDLE;
            // Calculate the time to spend in IDLE mode
            this_event_length = IDLE_TIME; // TODO: Make random
            s->ttl_idle += this_event_length; 
            next_event_type = IO_BUSY;
            break;
        default:
            message_error( m->event_type );
    } 

    // Generate and send the BUSY message to self
    raid_io_gen_send( lp->gid, next_event_type, this_event_length, lp );
    // Generate and send the BUSY message to server
    raid_io_gen_send( s->m_server, next_event_type, this_event_length, lp );
}

// Reverse Event Handler
void raid_io_eventhandler_rc( IOState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    // Check the message type, reverse state
    switch( m->event_type )
    {
        case IO_BUSY:
            s->mode = IDLE;
            s->ttl_busy -= m->rc.io_time;
            break;
        case IO_IDLE:
            s->mode = BUSY;
            s->ttl_idle -= m->rc.io_time;
            break;
        default:
            message_error( m->event_type );
    }
}

// Finish
void raid_io_finish( IOState* s, tw_lp* lp )
{
}
