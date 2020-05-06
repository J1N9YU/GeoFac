

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "MyDataAnalysisHelper.hh"
#include "time.h"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class GeoFacRunAction : public G4UserRunAction
{
  public:
    GeoFacRunAction();
    virtual ~GeoFacRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddHits(int n =1);


  private:
    MyDataAnalysisHelper* fMDAH;
    clock_t startTick;
    G4Accumulable<int> hits;

};

#endif

