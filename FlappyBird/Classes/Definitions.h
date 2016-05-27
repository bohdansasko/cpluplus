#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

const unsigned int      DISLPAY_TIME_SPLASH_SCENE   = 2;
const float             TRANSITION_TIME             = 0.5;

const float             PIPE_SPAWN_FREQUENCY        = 0.005;
const unsigned int      PIPE_GAP                    = 10;
const float             UPPER_SCREEN_PIPE_THRESHOLD = 0.65;
const float             LOWER_SCREEN_PIPE_THRESHOLD = 0.35;
const float             PIPE_MOVEMENT_SPEED         = 0.03;

const unsigned short    BIRD_COLLISION_BITMASK      = 0x00000001;
const unsigned short    OBSTACLE_COLLISION_BITMASK  = 0x00000002;
const unsigned short    POINT_COLLISION_BITMASK     = 0x00000003;

const float             BIRD_FALLING_SPEED          = 0.0025;
const float             BIRD_FLYING_SPEED           = 0.00375;
const float             BIRD_FLY_DURATION           = 0.25;
const float             SCORE_FONT_SIZE             = 0.1;

//#define    BIRD_COLLISION_BITMASK     0x000001
//#define    OBSTACLE_COLLISION_BITMASK 0x000002
#endif // __DEFINITIONS_H__
