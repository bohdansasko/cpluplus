#ifndef CONSTANTS
#define CONSTANTS

#include <QString>

const QString OBJ_NAME_WATER            = "whater";
const QString OBJ_NAME_WHITE_WALL       = "whiteWall";
const QString OBJ_NAME_RED_WALL         = "redWall";
const QString OBJ_NAME_GRASS            = "grass";
const QString OBJ_NAME_ICE              = "ice";
const QString OBJ_NAME_BULLET           = "bullet";
const QString OBJ_NAME_STAR             = "star";
const QString OBJ_NAME_BASE             = "base";
const QString OBJ_NAME_TIME_BONUS       = "timer_bonus";
const QString OBJ_NAME_BASE_BONUS       = "base_bonus";
const QString OBJ_NAME_EXPLOSION_BONUS  = "explosion_bonus";

const QString OBJ_NAME_PLAYER_1   = "Player1";
const QString OBJ_NAME_PLAYER_2   = "Player2";

const QString OBJ_NAME_BOT_1        = "Bot_1";
const QString OBJ_NAME_BOT_2        = "Bot_2";
const QString OBJ_NAME_BOT_3        = "Bot_3";
const QString OBJ_NAME_BOT_4        = "Bot_4";

const QString PATH_TO_STAR            = ":/walls/star.jpg";
const QString PATH_TO_BONUS_BASE      = ":/walls/secure.jpg";
const QString PATH_TO_BONUS_TIME      = ":/bonuses/time.png";
const QString PATH_TO_BONUS_EXPLOSION = ":/walls/gnanade.jpg";

const QString IMG_STAR_SCORE         = ":/score/bonuses/score/300score.png";
const QString IMG_GRANADE_SCORE     = ":/score/bonuses/score/300score.png";
const QString IMG_SPADE_SCORE       = ":/score/bonuses/score/300score.png";
const QString IMG_TIME_SCORE        = ":/score/bonuses/score/300score.png";

const QString PATH_TO_WHITE_WALL      = ":/walls/5.jpg";
const QString PATH_TO_RED_WALL        = ":/walls/3.jpg";
const QString PATH_TO_TANK_EXPLOSION  = ":/Explosion/tankExplosion.png";
const QString PATH_TO_BASE_EXPLOSION  = ":/Explosion/explosionBase.png";

const QString PATH_TO_BIG_EXPLOSION         = ":/Explosion/bigExplosion.png";
const QString PATH_TO_SMALL_EXPLOSION       = ":/Explosion/smallExplosion.png";
const QString PATH_TO_MINI_EXPLOSION        = ":/Explosion/miniExplosion.png";
const QString PATH_TO_SMALL_MINI__EXPLOSION = ":/Explosion/smallMiniExplosion.png";

const int OBJ_TYPE_WATER          = 1;
const int OBJ_TYPE_ICE            = 2;
const int OBJ_TYPE_RED_WALL       = 3;
const int OBJ_TYPE_GRASS          = 4;
const int OBJ_TYPE_WHITE_WALL     = 5;
const int OBJ_TYPE_BASE           = 6;

const int CNT_ROWS_MAP  = 32;
const int CNT_COLS_MAP  = 32;

const int SIZE_WALL     = 16;

const int WINDOW_HEIGHT = 512;
const int WINDOW_WIDTH  = 512;

const int CNT_SECOND_SHOW_STAR          = 5000/*10000*/;
const int CNT_SECOND_PROTECTION_BASE    = 6000/*20000*/;
const int CNT_SECOND_STOP_ALL_BOT       = 3000/*40000*/;
const int CNT_SECOND_EXPLOSION_ALL_BOTS = 6500/*60000*/;

const int CNT_NOT_FOUND_WAY = 999;

const int CNT_BEGIN_X_ONE_PLAYER = 150;
const int CNT_BEGIN_Y_ONE_PLAYER = 476;
const int CNT_BEGIN_X_TWO_PLAYER = 350;
const int CNT_BEGIN_Y_TWO_PLAYER = 475;
const int CNT_BEGIN_X_ONE_PLAYER_BATTLE = 250;
const int CNT_BEGIN_Y_ONE_PLAYER_BATTLE = 0;

const int CNT_BEGIN_X_ONE_BOT   = 0;
const int CNT_BEGIN_Y_ONE_BOT   = 0;
const int CNT_BEGIN_X_TWO_BOT   = 400;
const int CNT_BEGIN_Y_TWO_BOT   = 0;
const int CNT_BEGIN_X_THREE_BOT = 32;
const int CNT_BEGIN_Y_THREE_BOT = 0;
const int CNT_BEGIN_X_FOUR_BOT  = 350;
const int CNT_BEGIN_Y_FOUR_BOT  = 0;

const int CNT_SPEED_MOVE_ONE_PLAYER = 40;
const int CNT_SPEED_MOVE_BOTS       = 60;

const int CNT_CHANGE_SPEED_BOTS     = 10000;

const int CNT_TIME_APPEARANCE_ONE_BOT   = 1000;
const int CNT_TIME_APPEARANCE_TWO_BOT   = 7000;
const int CNT_TIME_APPEARANCE_THREE_BOT = 14000;
const int CNT_TIME_APPEARANCE_FOUR_BOT  = 21000;

const int CNT_TIME_SHOW_BONUS = 10000;
const int CNT_TIME_STOP_BOTS  = 5000;

const int DELAY_BEFORE_CREATE_BOTS  = 2000;  // Затримка перед створенням ботів

const int CNT_TIMER_FOR_SEND_POS_PLAYER = 10;

const int CNT_PORT_FOR_CONNECT = 2424;

const int CNT_SECOND_SEARCH_NEW_WAY = 4000;

#endif // CONSTANTS

