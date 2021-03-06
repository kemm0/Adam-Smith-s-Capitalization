#ifndef GAMERESOURCEMAP_H
#define GAMERESOURCEMAP_H
#include "../CourseLib/core/basicresources.h"

//Contains all costs and production rates for buildings and workers as 
//well as penalties and gains for robbers and treasures

namespace Game {

namespace ConstGameResourceMap {

const Course::ResourceMap PLAYER_STARTING_RESOURCES = {
    {Course::BasicResource::MONEY, 200}
};
// No resources
const Course::ResourceMap EMPTY = {};

// Building - Farm
const Course::ResourceMap FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, -50},
};
const Course::ResourceMap FARM_PRODUCTION = {
    {Course::BasicResource::MONEY, 10},
};


// Building - Logging cabin
const Course::ResourceMap LOGGING_BUILD_COST = {
    {Course::BasicResource::MONEY, -100},
};
const Course::ResourceMap LOGGING_PRODUCTION = {
    {Course::BasicResource::MONEY, 20},
};


// Building - Fishing hut
const Course::ResourceMap FISHING_BUILD_COST = {
    {Course::BasicResource::MONEY, -200},
};
const Course::ResourceMap FISHING_PRODUCTION = {
    {Course::BasicResource::MONEY, 30},
};


// Worker - NoviceWorker
const Course::ResourceMapDouble NW_WORKER_EFFICIENCY = {
    {Course::MONEY, 10},
};

const Course::ResourceMap NW_RECRUITMENT_COST = {
    {Course::MONEY, -30},
};

// Worker - ApprenticeWorker
const Course::ResourceMapDouble AW_WORKER_EFFICIENCY = {
    {Course::MONEY, 20},
};

const Course::ResourceMap AW_RECRUITMENT_COST = {
    {Course::MONEY, -50},
};

// Worker - MasterWorker
const Course::ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {Course::MONEY, 30},
};

const Course::ResourceMap MW_RECRUITMENT_COST = {
    {Course::MONEY, -70},
};
// Tile without building doesnt have effect
const Course::ResourceMap TILE_BP = {
    {Course::MONEY, 1},
};
// Robbers
const Course::ResourceMap ROBBER = {
    {Course::MONEY, -200},
};
// Treasures
const Course::ResourceMap TREASURE = {
    {Course::MONEY, 200},
};

// Searching
const Course::ResourceMap SEARCH = {
    {Course::MONEY, -10},
};
}
}

#endif // GAMERESOURCEMAP_H
