

#ifndef GeoFacPrimaryGeneratorAction_h
#define GeoFacPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "GeoFacDetectorConstruction.hh"

#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class GeoFacPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GeoFacPrimaryGeneratorAction();    
    virtual ~GeoFacPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    G4ThreeVector GetRandomDirection();
    G4ThreeVector GetRandomPosition();
    G4ThreeVector GetSpecificDirection();
    G4ThreeVector GetSpecificPosition();
    void SetRandomOptPhotonPolar();
    inline void SetTestMode(bool mode){isTestMode=mode;}
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    bool isTestMode;              // in test mode, particle gun shoot photon with specific positiong and direction instead of random generating them.



};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
