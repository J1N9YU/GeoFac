//
// ********************************************************************

//
//
#include "GeoFacPhotonDetHit.hh"

G4ThreadLocal G4Allocator<GeoFacPhotonDetHit>* GeoFacPhotonDetHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacPhotonDetHit::GeoFacPhotonDetHit()
{
  fArrivalTime = 0.;
  fPosArrive   = G4ThreeVector(0., 0., 0.);
  fPosExit     = G4ThreeVector(0., 0., 0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacPhotonDetHit::GeoFacPhotonDetHit(G4ThreeVector pExit,
                                 G4ThreeVector pArrive,
                                 G4double pTime)
{
  fPosExit     = pExit;
  fPosArrive   = pArrive;
  fArrivalTime = pTime;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacPhotonDetHit::~GeoFacPhotonDetHit() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacPhotonDetHit::GeoFacPhotonDetHit(const GeoFacPhotonDetHit &right)
  : G4VHit()
{
  *this = right;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const GeoFacPhotonDetHit& GeoFacPhotonDetHit::operator=(const GeoFacPhotonDetHit &right)
{
  fPosExit     = right.fPosExit;
  fPosArrive   = right.fPosArrive;
  fArrivalTime = right.fArrivalTime;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool GeoFacPhotonDetHit::operator==(const GeoFacPhotonDetHit& right) const
{
  return fPosExit     == right.fPosExit    &&
         fPosArrive   == right.fPosArrive  &&
         fArrivalTime == right.fArrivalTime;  
}
