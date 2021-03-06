#pragma once

const uint8_t LEVEL_X_SIZE = 26;
const uint8_t LEVEL_Y_SIZE = 25;
const uint8_t TILE_SIZE = 24;

const uint8_t level[LEVEL_Y_SIZE][LEVEL_X_SIZE] = {
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 5, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 7, 0, 0, 0, 9, 0, 0, 0, 0, 9, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 7, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 7, 0, 5 },
	{ 5, 7, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 1, 1, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 5 },
	{ 5, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 0, 7, 1, 1, 5 },
	{ 5, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 7, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 5 },
	{ 5, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 5 },
	{ 5, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 5 },
	{ 5, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 7, 0, 0, 0, 1, 1, 5 },
	{ 5, 0, 0, 0, 7, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 0, 0, 1, 1, 7, 0, 0, 0, 0, 0, 7, 0, 1, 1, 0, 0, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 7, 0, 5 },
	{ 5, 7, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 0, 0, 1, 1, 8, 0, 1,10, 0, 1, 8, 0, 1, 1, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 5 },
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
};