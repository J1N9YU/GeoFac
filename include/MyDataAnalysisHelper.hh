#ifndef mdh
#define mdh 1

#include "iostream"
#include "G4ios.hh"
#include "fstream"
#include "time.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>


using namespace std;

typedef struct RnuRecord{
    float total;
    int hit;
    double ratio;
    double stdev;
    clock_t comsumedTick;
}RunRecord;

class MyDataAnalysisHelper{
    public:
        MyDataAnalysisHelper();
        ~MyDataAnalysisHelper();
        void AddHit();
        inline void SetHit(int n){hitCount=n;}
        inline void AddTotal(int n=1){totalCount+=n;};
        double GetHitRatio();
        void WriteToFile();
        void Clear();
        void WriteToRecord();
        inline int GetHitCount(){return hitCount;};
        inline int GetTotalCount(){return totalCount;};
        inline void SetDeltaTick(clock_t delta){deltaTick=delta;};
        inline void SetSavingMode(bool mode){isSaving=mode;}
        inline void SetNumThreads(int num){numThread = num;}
        inline void SetRepeats(int num){reapeatEachThread = num;};
        inline void SetExperimentType(string t){experimentType = t;}
        static MyDataAnalysisHelper* GetInstance();
        inline void __ADDTESTHIT__(){__TESTHIT__++;}



        int __TESTHIT__ ;
    
    private:

        

        static MyDataAnalysisHelper* fInstance;
        int hitCount;
        int totalCount;
        clock_t deltaTick;
        bool isSaving;
        int numThread;
        int reapeatEachThread;
        vector<RunRecord> record;//data of runs
        string experimentType;

        //These two vectors duplicate from "record" after each simulation, keeping the origin data of each run.
        vector<RunRecord> GSourceV;
        vector<RunRecord> GReemitV;

        //process data
        void ProcessRecord();
        vector<RunRecord> GetRunRatio(vector<RunRecord> a,vector<RunRecord> b);
        


};



#endif