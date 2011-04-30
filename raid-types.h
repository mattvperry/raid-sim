/**
 * RAID File Server Farm Simulation
 *
 * FILE: raid-types.h
 * AUTHOR: Matt Perry
 * DATE: Apr 27 2011
 */

#ifndef RAID_TYPES_H
#define RAID_TYPES_H

#include "raid.h"

/* constants */
#define MAX_HOURS 43800 // 5 years
#define MTTF 1000000    // 1M hours

#define CONT_PER_FS 4   // 4 controllers per file server
#define DISK_PER_RC 8   // 8 disks per raid controller

/* typedef */
typedef struct _server_state ServerState;
typedef struct _controller_state ContState;
typedef struct _disk_state DiskState;
typedef struct _nic_state NicState;
typedef struct _message_data MsgData;
typedef enum _event Event;
typedef enum _controller_condition ContCondition;

/* event types */
enum _event
{
    THROTTLE_DOWN,
    THROTTLE_UP,
    REBUILD_START,
    REBUILD_FINISH,
    FAILURE,
    REPLACED
};

/* message */
struct _message_data
{
    Event event_type;
};

/* raid-server.c */
struct _server_state
{
    tw_lpid m_nic;
    tw_lpid m_controllers[CONT_PER_FS];
    int num_controllers_good_health;
    int num_controllers_rebuilding;
    int num_controllers_failure;
};

/* raid-controller.c */
enum _controller_condition
{
    HEALTHY,
    REBUILD,
    FAILED
};

struct _controller_state
{
    tw_lpid m_server;
    tw_lpid m_disks[DISK_PER_RC];
    ContCondition condition;
    int num_rebuilds;
};

/* raid-disk.c */
struct _disk_state
{
    tw_lpid m_controller;
    int num_failures;
};

#endif
