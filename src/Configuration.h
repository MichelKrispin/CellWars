#pragma once

// The maximal number of cells per field
#define MAX_COUNT_PER_FIELD 100

// The window size in pixels
#define WINDOW_SIZE 800

// The number of fields per row/column
#define GRID_SIZE 50

// After how many turns is the game finished
#define MAX_TURN_COUNT 2000

// How long does a turn take
#define TURN_DURATION_IN_MS 50

// Possible options are White and Black
#define BACKGROUND_COLOR Black

// The font which will be used for the turn number 
// This is the relative path off the working directory
#define FONT_PATH "arial.ttf"

// Pause on startup? values are true or false
#define PAUSE_ON_STARTUP true

// Rule to define whether the increasing of 10 Percent happens for splitvalues immediately
// true  -> increase of splitvalues in this turn
// false -> increase only of fields which are owned at the start of the turn 
#define INCREASING_SPLIT_VALUES true
