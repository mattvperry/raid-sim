/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid-disk.c
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */
#include "raid.h"

// Initialize
void raid_disk_init( DiskState* s, tw_lp* lp )
{
    // Initialize state
    // TODO: Initialize controller gid
    s->num_failures = 0;

    tw_bf init_bf;
    raid_disk_eventhandler( s, &init_bf, NULL, lp );
}

// Event Handler
void raid_disk_eventhandler( DiskState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    tw_stime fail_time;

    switch( g_disk_distro )
    {
        case 0:
            fail_time = (tw_stime)((double)tw_rand_integer( lp->rng, 0, 2 * MTTF ));
            break;

        case 1:
            fail_time = (tw_stime)tw_rand_exponential( lp->rng, MTTF );
            break;

        case 2:
            fail_time = (tw_stime)tw_rand_weibull( lp->rng, MTTF, 0.1 );
            break;

        case 3:
            fail_time = (tw_stime)tw_rand_weibull( lp->rng, MTTF, 0.5 );
            break;

        case 4:
            fail_time = (tw_stime)tw_rand_weibull( lp->rng, MTTF, 1.0 );
            break;

        case 5:
            fail_time = (tw_stime)tw_rand_weibull( lp->rng, MTTF, 5.0 );
            break;

        case 6:
            fail_time = (tw_stime)tw_rand_weibull( lp->rng, MTTF, 10.0 );
            break;

        default:
            printf( "Bad disk_distro setting (%d)\n", g_disk_distro );
            exit( -1 );
    }

    if( ( tw_now( lp ) + fail_time ) < (tw_stime)MAX_HOURS )
    {
        // Generate and send messages
        tw_event* event = tw_event_new( s->m_controller, fail_time, lp );
        MsgData* fail_message = (MsgData*)tw_event_data( event );
        fail_message->event_type = DISK_FAILURE;
        tw_event_send( event );
        tw_event_send( tw_event_new( lp->gid, fail_time, lp ) );

        // Modify state
        cv->c0 = 1;
        s->num_failures++;
    }
}

// Reverse Event Handler
void raid_disk_eventhandler_rc( DiskState* s, tw_bf* cv, MsgData* m, tw_lp* lp )
{
    tw_rand_reverse_unif( lp->rng );
    if( cv->c0 )
        s->num_failures--;
}

// Finish
void raid_disk_finish( DiskState* s, tw_lp* lp )
{
}
