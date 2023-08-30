#ifndef __STATUS_H
#define __STATUS_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



typedef enum {
    MANUAL = 0,
    AUTO = 1,
}control_mode_t;

typedef enum {
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN,
} pst_control_t;


typedef struct {
    control_mode_t control_mode;
    
    pst_control_t pts_control;
    
} status_t;




extern status_t status;



#endif
