#ifndef GAMERESOURCEMAP_H
#define GAMERESOURCEMAP_H
#include "../CourseLib/core/basicresources.h"

//Contains all costs and production rates for buildings and workers as 
//well as penalties and gains for robbers and treasures

namespace Game {

namespace ConstGameResourceMap {

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
    {Course::MONEY, 1.25},
};

const Course::ResourceMap NW_RECRUITMENT_COST = {
    {Course::MONEY, -30},
};

// Worker - ApprenticeWorker
const Course::ResourceMapDouble AW_WORKER_EFFICIENCY = {
    {Course::MONEY, 1.5},
};

const Course::ResourceMap AW_RECRUITMENT_COST = {
    {Course::MONEY, -50},
};

// Worker - MasterWorker
const Course::ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {Course::MONEY, 1.75},
};

const Course::ResourceMap MW_RECRUITMENT_COST = {
    {Course::MONEY, -70},
};
// Tile without building doesnt have effect
const Course::ResourceMap TILE_BP = {
    {Course::MONEY, 0},
};
// Robbers
const Course::ResourceMap ROBBER = {
    {Course::MONEY, -500},
};
// Treasures
const Course::ResourceMap TREASURE = {
    {Course::MONEY, 500},
};
}
}

#endif // GAMERESOURCEMAP_H
