#include "GeoFacEventAction.hh"
#include "GeoFacRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "GeoFacPhotonDetHit.hh"


//Constructor
GeoFacEventAction::GeoFacEventAction(GeoFacRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{
   fMDAH = MyDataAnalysisHelper::GetInstance();
} 


//destructor
GeoFacEventAction::~GeoFacEventAction()
{

}



void GeoFacEventAction::BeginOfEventAction(const G4Event*)
{
}



void GeoFacEventAction::EndOfEventAction(const G4Event* evt)
{   
 

  // Get Hits from the detector if any
  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  G4String colName = "PhotonDetHitCollection";
  fMPPCCollID = SDman->GetCollectionID(colName);

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  GeoFacPhotonDetHitsCollection* mppcHC = 0;

  // Get the hit collections
  if (HCE)
  {
     if (fMPPCCollID>=0) mppcHC = (GeoFacPhotonDetHitsCollection*)(HCE->GetHC(fMPPCCollID));
  }

  // Get hit information about photons that reached the detector in this event
  if (mppcHC)
  {
     G4int n_hit = mppcHC->entries();
     if(n_hit!=0){
        fRunAction->AddHits();
      }
  }
}


