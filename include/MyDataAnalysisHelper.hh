#ifndef mdh
#define mdh 1

#include "iostream"
#include "G4ios.hh"
#include "fstream"
#include "time.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include "G4RunManager.hh"
#include "GeoFacPrimaryGeneratorAction.hh"



using namespace std;

typedef struct RnuRecord{
    int total;
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
        inline void AddTotal(int n=1){totalCount+=n;};
        double GetHitRatio();
        void WriteToFile();
        void Clear();
        void WriteToRecord();
        inline int GetHitCount(){return hitCount;};
        inline int GetTotalCount(){return totalCount;};
        inline void SetDeltaTick(clock_t delta){deltaTick=delta;totalTimeCost+=delta/CLOCKS_PER_SEC;}
        inline void SetSavingMode(bool mode){isSaving=mode;}
        inline void SetNumThreads(int num){numThread = num;}
        inline void SetRepeats(int num){reapeatEachThread = num;};
        inline void SetExperimentType(string t){experimentType = t;}
        static MyDataAnalysisHelper* GetInstance();
        void TestRandom();
    
    private:

        static MyDataAnalysisHelper* fInstance;
        
        G4RunManager* fRunManager;
        int hitCount;
        int totalCount;
        clock_t deltaTick;
        bool isSaving;
        int numThread;
        int reapeatEachThread;
        vector<RunRecord> record;
        string experimentType;
        vector<G4double> GSourceV;
        vector<G4double> GReemitV;
        void ProcessRecord();
        double totalTimeCost;
        


};



#endif