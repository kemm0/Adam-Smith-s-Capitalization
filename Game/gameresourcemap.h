#ifndef GAMERESOURCEMAP_H
#define GAMERESOURCEMAP_H
#include "../CourseLib/core/basicresources.h"

namespace Course {

namespace ConstGameResourceMap {

const ResourceMap EMPTY = {};

// Building - Farm
const ResourceMap FARM_BUILD_COST = {
    {BasicResource::MONEY, 50},
};
const ResourceMap FARM_PRODUCTION = {
    {BasicResource::MONEY, 1},
};


// Building - Logging cabin
const ResourceMap LOGGING_BUILD_COST = {
    {BasicResource::MONEY, 750},
};
const ResourceMap LOGGING_PRODUCTION = {
    {BasicResource::MONEY, 10},
};


// Building - Fishing hut
const ResourceMap FISHING_BUILD_COST = {
    {BasicResource::MONEY, 750},
};
const ResourceMap FISHING_PRODUCTION = {
    {BasicResource::MONEY, 10},
};


// Worker - NoviceWorker
const ResourceMapDouble NW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
};

const ResourceMap NW_RECRUITMENT_COST = {
    {MONEY, 10},
};

// Worker - ApprenticeWorker
const ResourceMapDouble AW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
};

const ResourceMap AW_RECRUITMENT_COST = {
    {MONEY, 10},
};

// Worker - MasterWorker
const ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
};

const ResourceMap MW_RECRUITMENT_COST = {
    {MONEY, 10},
};
}
}

#endif // GAMERESOURCEMAP_H
