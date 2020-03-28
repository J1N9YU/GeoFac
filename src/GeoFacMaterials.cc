
#include "GeoFacMaterials.hh"

#include "G4SystemOfUnits.hh"

GeoFacMaterials* GeoFacMaterials::fInstance = 0; //Link error would occur without this, why?

GeoFacMaterials::GeoFacMaterials()
{
  fNistMan = G4NistManager::Instance();

  fNistMan->SetVerbose(2);

  CreateMaterials();

  fInstance = 0;
}


GeoFacMaterials::~GeoFacMaterials()
{
  delete    fPMMA;
  delete    fPCB;
  delete    fMetal;
  delete    fSiPD;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacMaterials* GeoFacMaterials::GetInstance()
{
  if (fInstance == 0)
    {
      fInstance = new GeoFacMaterials();
    }
  return fInstance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* GeoFacMaterials::GetMaterial(const G4String material)
{
  G4Material* mat =  fNistMan->FindOrBuildMaterial(material);

  if (!mat) mat = G4Material::GetMaterial(material);
  if (!mat) {
     std::ostringstream o;
     o << "Material " << material << " not found!";
     G4Exception("GeoFacMaterials::GetMaterial","",
                 FatalException,o.str().c_str());
  }

  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeoFacMaterials::CreateMaterials()
{
  G4double density;
  G4int ncomponents;
  G4double fractionmass;
  std::vector<G4int> natoms;
  std::vector<G4double> fractionMass;
  std::vector<G4String> elements;

  // Materials Definitions
  // =====================

  //elements and density are irrelevant but necessary as Geant4 requires.
  elements.push_back("C");     natoms.push_back(5);
  elements.push_back("H");     natoms.push_back(8);
  elements.push_back("O");     natoms.push_back(2);

  density = 1.190*g/cm3;

  //--------------------------------------------------
  // Vacuum
  //--------------------------------------------------

  fNistMan->FindOrBuildMaterial("G4_Galactic");

  //--------------------------------------------------
  // Air
  //--------------------------------------------------
  fAir = fNistMan->FindOrBuildMaterial("G4_AIR");
  //--------------------------------------------------
  //PMMA
  //--------------------------------------------------
  fPMMA = fNistMan->ConstructNewMaterial("PMMA", elements, natoms, density);
  //--------------------------------------------------
  // PCB
  //--------------------------------------------------
  fPCB = fNistMan->ConstructNewMaterial("PCB", elements, natoms, density);
  //--------------------------------------------------
  // Metal
  //--------------------------------------------------
  fMetal = fNistMan->ConstructNewMaterial("Metal", elements, natoms, density);
  //--------------------------------------------------
  // SiPD
  //--------------------------------------------------
  fSiPD = fNistMan->ConstructNewMaterial("SiPD", elements, natoms, density);



  //
  // ------------ Generate & Add Material Properties Table ------------
  //
  
  G4double photonEnergy[] =
  {2.00*eV,2.03*eV,2.06*eV,2.09*eV,2.12*eV,
   2.15*eV,2.18*eV,2.21*eV,2.24*eV,2.27*eV,
   2.30*eV,2.33*eV,2.36*eV,2.39*eV,2.42*eV,
   2.45*eV,2.48*eV,2.51*eV,2.54*eV,2.57*eV,
   2.60*eV,2.63*eV,2.66*eV,2.69*eV,2.72*eV,
   2.75*eV,2.78*eV,2.81*eV,2.84*eV,2.87*eV,
   2.90*eV,2.93*eV,2.96*eV,2.99*eV,3.02*eV,
   3.05*eV,3.08*eV,3.11*eV,3.14*eV,3.17*eV,
   3.20*eV,3.23*eV,3.26*eV,3.29*eV,3.32*eV,
   3.35*eV,3.38*eV,3.41*eV,3.44*eV,7.47*eV};

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  //--------------------------------------------------
  // Air
  //--------------------------------------------------

  G4double refractiveIndex[] =
  { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

  assert(sizeof(refractiveIndex) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
  mpt->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);

  fAir->SetMaterialPropertiesTable(mpt);

  //--------------------------------------------------
  //  PMMA 
  //--------------------------------------------------

  G4double refractiveIndexPMMA[] =
  { 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23,
    1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23,
    1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23,
    1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23,
    1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23};

  assert(sizeof(refractiveIndexPMMA) == sizeof(photonEnergy));

  G4double absGeoFacfiber[] =
  {5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,
   5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,
   5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,5.40*m,1.10*m,
   1.10*m,1.10*m,1.10*m,1.10*m,1.10*m,1.10*m, 1.*mm, 1.*mm, 1.*mm, 1.*mm,
    1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*mm, 1.*m, 1.*m};

  assert(sizeof(absGeoFacfiber) == sizeof(photonEnergy));

  G4double emissionFib[] =
  {0.05, 0.10, 0.30, 0.50, 0.75, 1.00, 1.50, 1.85, 2.30, 2.75,
   3.25, 3.80, 4.50, 5.20, 6.00, 7.00, 8.50, 9.50, 11.1, 12.4,
   12.9, 13.0, 12.8, 12.3, 11.1, 11.0, 12.0, 11.0, 17.0, 16.9,
   15.0, 9.00, 2.50, 1.00, 0.05, 0.00, 0.00, 0.00, 0.00, 0.00,
   0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

  assert(sizeof(emissionFib) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable* mptGeoFacfiber = new G4MaterialPropertiesTable();
  mptGeoFacfiber->AddProperty("RINDEX",photonEnergy,refractiveIndexPMMA,nEntries);
  mptGeoFacfiber->AddProperty("ABSLENGTH",photonEnergy,absGeoFacfiber,nEntries);


  fPMMA->SetMaterialPropertiesTable(mptGeoFacfiber);

  //--------------------------------------------------
  //  PCB
  //--------------------------------------------------

  G4double refractiveIndexClad1[] =
  { 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
    1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
    1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
    1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49,
    1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49};

  assert(sizeof(refractiveIndexClad1) == sizeof(photonEnergy));

  G4double absClad[] =
  {20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,
   20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,
   20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,
   20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,
   20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm,20.0*mm};

  assert(sizeof(absClad) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable* mptClad1 = new G4MaterialPropertiesTable();
  mptClad1->AddProperty("RINDEX",photonEnergy,refractiveIndexClad1,nEntries);
  mptClad1->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);

  fPCB->SetMaterialPropertiesTable(mptClad1);

  //--------------------------------------------------
  // Metal
  //--------------------------------------------------

   G4double refractiveIndexClad2[] =
   { 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
     1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
     1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
     1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42,
     1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42, 1.42};

   assert(sizeof(refractiveIndexClad2) == sizeof(photonEnergy));

  // Add entries into properties table
  G4MaterialPropertiesTable* mptClad2 = new G4MaterialPropertiesTable();
  //mptClad2->AddProperty("RINDEX",photonEnergy,refractiveIndexClad2,nEntries);
  mptClad2->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);
 

  fMetal->SetMaterialPropertiesTable(mptClad2);

  //--------------------------------------------------
  // SiPD
  //--------------------------------------------------

   G4double refractiveIndexSilicone[] =
   { 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489,
     1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489,
     1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489,
     1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489,
     1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489, 1.489};

   assert(sizeof(refractiveIndexSilicone) == sizeof(photonEnergy));

    G4double absSiPD[] =
  { 20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,
    20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,
    20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,
    20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,
    20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm,20.0*nm};

  // Add entries into properties table
  G4MaterialPropertiesTable* mptSilicone = new G4MaterialPropertiesTable();
  mptSilicone->AddProperty("RINDEX",photonEnergy,refractiveIndexSilicone,nEntries);
  mptSilicone->AddProperty("ABSLENGTH",photonEnergy,absSiPD,nEntries);

  fSiPD->SetMaterialPropertiesTable(mptSilicone);

  

}
