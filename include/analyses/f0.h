#ifndef F0_H
#define F0_H
#include "analysis.h"
#include "logger.h"

class f0 : public analysis 
{
    public:
        void create_analysis() {LOGDEBUG << "Creating F0 analysis (WARNING: currently not implemented)";};
    private:
};
#endif
