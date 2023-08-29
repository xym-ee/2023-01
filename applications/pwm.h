#ifndef __PWM_H__
#define __PWM_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


/* 调整速度 */
#define SERVO_VELOCITY  300
#define DEATH_LIMIT     100

#define DOWN_LIMIT      500000
#define UP_LIMIT        2500000





/* A */
#define PWM_SERVO_DEV           "pwm3"
#define PWM_SERVO_YAW           1
#define PWM_SERVO_PITCH         2



/* pwm电机控制线程 */
#define SERVO_PWM_PRIORITY         10
#define SERVO_PWM_STACK_SIZE       1024
#define SERVO_PWM_TIMESLICE        5

extern rt_int32_t yaw_pwm;
extern rt_int32_t pitch_pwm;


#endif



