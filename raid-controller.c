/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid-controller.c
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */
#include "raid.h"

// Helpers
void raid_controller_gen_send( tw_lpid dest, Event event_type, tw_stime event_time, tw_lp* lp )
{
    // Generate and send message to dest
    tw_event* event = tw_event_new( dest, event_time, lp );
    MsgData* message = (MsgData*)tw_event_data( event );
    message->event_type = event_type;
    tw_event_send( event );
}

// Initialize
void raid_controller_init( ContState* s, tw_lp* lp )
{
    // Initialize state
    // TODO: Calculate server gid
    // TODO: Calculate disk gids
    s->condition = HEALTHY;
    s->num_rebuilds = 0;
}

// Event Handler
void raid_controller_eventhandler( ContState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    // Save the controller's initial condition
    m->rc.controller_condition = s->condition;
    // Only handle events if the controller isnt dead
    if( s->condition != FAILED )
    {
        // Check message type
        switch( m->event_type )
        {
            case DISK_FAILURE:
                if( s->condition == REBUILD || s->condition == WAIT )
                    s->condition = FAILED;
                else
                    s->condition = WAIT;

                // Generate and send message to the file server
                raid_controller_gen_send( s->m_server, RAID_FAILURE, 0, lp );
                break;
            case DISK_REPLACED:
                s->condition = REBUILD;

                // Schedule rebuild completion
                tw_stime rebuild_time = REBUILD_TIME; // TODO: Make random
                raid_controller_gen_send( lp->gid, REBUILD_FINISH, rebuild_time, lp );

                // Generate and send message to the file server
                raid_controller_gen_send( s->m_server, REBUILD_START, 0, lp );
                break;
            case REBUILD_FINISH:
                s->condition = HEALTHY;

                // Generate and send message to the file server
                raid_controller_gen_send( lp->gid, REBUILD_FINISH, 0, lp );
                break;
            default:
                message_error( m->event_type );
        }
    }
}

// Reverse Event Handler
void raid_controller_eventhandler_rc( ContState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    s->condition = m->rc.controller_condition;
}

// Finish
void raid_controller_finish( ContState* s, tw_lp* lp )
{
}
