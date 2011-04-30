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

/* raid-globals.c */
extern int g_disk_distro;

#endif
