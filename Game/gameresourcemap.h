#ifndef GAMERESOURCEMAP_H
#define GAMERESOURCEMAP_H
#include "../CourseLib/core/basicresources.h"


namespace Game {

namespace ConstGameResourceMap {

const Course::ResourceMap EMPTY = {};

// Building - Farm
const Course::ResourceMap FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, 50},
};
const Course::ResourceMap FARM_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
};


// Building - Logging cabin
const Course::ResourceMap LOGGING_BUILD_COST = {
    {Course::BasicResource::MONEY, 750},
};
const Course::ResourceMap LOGGING_PRODUCTION = {
    {Course::BasicResource::MONEY, 10},
};


// Building - Fishing hut
const Course::ResourceMap FISHING_BUILD_COST = {
    {Course::BasicResource::MONEY, 750},
};
const Course::ResourceMap FISHING_PRODUCTION = {
    {Course::BasicResource::MONEY, 10},
};


// Worker - NoviceWorker
const Course::ResourceMapDouble NW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
};

const Course::ResourceMap NW_RECRUITMENT_COST = {
    {Course::MONEY, 10},
};

// Worker - ApprenticeWorker
const Course::ResourceMapDouble AW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
};

const Course::ResourceMap AW_RECRUITMENT_COST = {
    {Course::MONEY, 10},
};

// Worker - MasterWorker
const Course::ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
};

const Course::ResourceMap MW_RECRUITMENT_COST = {
    {Course::MONEY, 10},
};
const Course::ResourceMap TILE_BP = {
    {Course::MONEY, 0},
};
}
}

#endif // GAMERESOURCEMAP_H
