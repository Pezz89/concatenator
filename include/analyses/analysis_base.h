#ifndef ANALYSIS_BASE_H
#define ANALYSIS_BASE_H

class analysis 
{
    public:
        virtual ~analysis() {};
        virtual void create_analysis() = 0;
    private:
};
#endif
