
//
//
#include "GeoFacPhotonDetSD.hh"
#include "GeoFacPhotonDetHit.hh"


#include "G4Track.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"


GeoFacPhotonDetSD::GeoFacPhotonDetSD(G4String name)
  : G4VSensitiveDetector(name), fPhotonDetHitCollection(0)
{
  collectionName.insert("PhotonDetHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacPhotonDetSD::~GeoFacPhotonDetSD() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeoFacPhotonDetSD::Initialize(G4HCofThisEvent* HCE)
{
  fPhotonDetHitCollection =
       new GeoFacPhotonDetHitsCollection(SensitiveDetectorName,collectionName[0]);
  //Store collection with event and keep ID
  static G4int HCID = -1;
  if (HCID<0) HCID = GetCollectionID(0);
  HCE->AddHitsCollection( HCID, fPhotonDetHitCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool GeoFacPhotonDetSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
  if (aStep == NULL) return false;
  G4Track* theTrack = aStep->GetTrack();

  // Need to know if this is an optical photon
  if(theTrack->GetDefinition()
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

  // Find out information regarding the hit
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
 
 
  G4TouchableHistory* theTouchable
      = (G4TouchableHistory*)(thePostPoint->GetTouchable());
 

  G4ThreeVector photonArrive = thePostPoint -> GetPosition();
  G4ThreeVector photonExit   = photonArrive;
  G4double      arrivalTime  = theTrack -> GetGlobalTime();

  // Convert the global coordinate for arriving photons into
  // the local coordinate of the detector
  photonArrive = theTouchable->GetHistory()->GetTopTransform().TransformPoint(photonArrive);

  // Creating the hit and add it to the collection

  fPhotonDetHitCollection->insert(new GeoFacPhotonDetHit(photonExit, photonArrive, arrivalTime));

  return true;
}


