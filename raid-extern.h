/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid-extern.h
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */

#ifndef RAID_EXTERN_H
#define RAID_EXTERN_H

#include "raid.h"

/* raid.c */
void message_error( Event event_type );

/* raid-server.c */
extern void raid_server_init( ServerState* s, tw_lp* lp );
extern void raid_server_eventhandler( ServerState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_server_eventhandler_rc( ServerState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_server_finish( ServerState* s, tw_lp* lp );

/* raid-controller.c */
extern void raid_controller_init( ContState* s, tw_lp* lp );
extern void raid_controller_eventhandler( ContState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_controller_eventhandler_rc( ContState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_controller_finish( ContState* s, tw_lp* lp );

/* raid-disk.c */
extern void raid_disk_init( DiskState* s, tw_lp* lp );
extern void raid_disk_eventhandler( DiskState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_disk_eventhandler_rc( DiskState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_disk_finish( DiskState* s, tw_lp* lp );

/* raid-io.c */
extern void raid_io_gen_send( tw_lpid dest, Event next_event_type, tw_stime this_event_length, tw_lp* lp );
extern void raid_io_init( IOState* s, tw_lp* lp );
extern void raid_io_eventhandler( IOState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_io_eventhandler_rc( IOState* s, tw_bf* cv, MsgData* m, tw_lp* lp );
extern void raid_io_finish( IOState* s, tw_lp* lp );

/* raid-globals.c */
extern int g_disk_distro;

#endif
