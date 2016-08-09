#ifndef RMS_H
#define RMS_H
#include "analysis.h"
#include "logger.h"

class rms : public analysis 
{
    public:
        void create_analysis() {LOGDEBUG << "Creating RMS analysis (WARNING: currently not implemented)";};
    private:
};
#endif
