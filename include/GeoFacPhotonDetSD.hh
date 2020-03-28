

#ifndef GeoFacPhotonDetSD_h
#define GeoFacPhotonDetSD_h 1

#include "GeoFacPhotonDetHit.hh"

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class GeoFacPhotonDetSD : public G4VSensitiveDetector
{
  public:

    GeoFacPhotonDetSD(G4String );
    virtual ~GeoFacPhotonDetSD();

    virtual void Initialize(G4HCofThisEvent* );

    virtual G4bool ProcessHits(G4Step* , G4TouchableHistory* );

  private:

    GeoFacPhotonDetHitsCollection* fPhotonDetHitCollection;
};

#endif
