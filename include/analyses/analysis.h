#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "analysis_base.h"
#include "rms.h"
#include "f0.h"
#include <memory>
#include <map>
#include <string>

using namespace std;

namespace AudioAnalysis {
    enum analyses {
        RMS,
        F0,
    };

    static inline analyses analysis_index_from_string(const string& s) {
        static map<string, analyses> analysis_map = { {"RMS", RMS}, {"F0", F0} };
        return analysis_map[s];
    }

    class AnalysisFactory 
    {
        public:
            AnalysisFactory(const bool& reanalyse) : reanalyse(reanalyse) {}
            unique_ptr<analysis> create(analyses analysis_type)
            {
                switch(analysis_type)
                {
                    case RMS:
                        return make_unique<rms>();
                    case F0:
                        return make_unique<f0>();
                }
            }
        private:
            bool reanalyse;
    };
}
#endif
