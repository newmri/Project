#pragma once
#define W_MAX 600
#define H_MAX 800
#define PI 3.14
#define C_W 60
#define C_H 60

#define WEAPONE_W 30
#define WEAPONE_H 60

#define FIRST_W 30
#define FIRST_H 60

#define SECOND_W 40
#define SECOND_H 50


#define THIRD_W 50
#define THIRD_H 40

static const int NUM_OF_STAGE = 2;
static const int NUM_OF_ENEMY = 1;
static const int NUM_OF_BOSS = 2;


static const float FPS = 60.f;
static const float STAGE_TIME = 180.f; // Second
static const float STAGE_SPEED = FPS * STAGE_TIME;

static const int NORMAL_ENEMY_ARRIVAL_TIEM = 3;
static const int NORMAL_ENEMY_SEARCH_AREA = H_MAX / 2;
static const int NORMAL_ENEMY_SPEED = NORMAL_ENEMY_SEARCH_AREA / (FPS * NORMAL_ENEMY_ARRIVAL_TIEM);

static const int PLAYER_IMAGE_NUM = 7;
static const int PLAYER_H_ANIMATION_NUM = 3;
static const int PLAYER_V_ANIMATION_NUM = 7;


static const int PLAYER_LEFT_IMG_END = 0;
static const int PLAYER_STILL_IMG = 4;
static const int PLAYER_RIGHT_IMG_END = 6;

static const int PLAYER_UP_IMG_END = 6;
static const int PLAYER_DOWN_IMG_END = 0;

static const int NUM_OF_BULLET = 4;
static const int NUM_OF_MISSILE = 2;
static const int NUM_OF_ENEMY_BULLET = 1;

static const int NORMAL_ENEMY_MAX_SPAWN_NUM = 20;
static const int NORMAL_ENEMY_MIN_SPAWN_NUM = 8;
static const float NORMAL_ENEMY_SPAWN_PERCENT = 5.f;
static const int NORMAL_ENEMY_NEXT_SPAWN_TIME = (NORMAL_ENEMY_SPAWN_PERCENT * 0.01f) * STAGE_TIME * 1000;

static const int NORMAL_ENEMY_BULLET_MAX_SPAWN_TIME = 2500;
static const int NORMAL_ENEMY_BULLET_MIN_SPAWN_TIME = 1500;


static const int ITEM_IMAGE_NUM = 6;
static const int ITEM_SPAWN_PERCENT = 40;

static const int IMAGE_NAME_LEN = 128;

static const int ITEM_SCORE = 100;
static const int ENEMY_SCORE = 50;
static const int BOSS_SCORE = 2000;