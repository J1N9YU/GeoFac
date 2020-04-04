

#include "GeoFacDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "GeoFacPhotonDetSD.hh"
#include "G4SDManager.hh"
#include "G4Colour.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4SurfaceProperty.hh"


GeoFacDetectorConstruction::GeoFacDetectorConstruction()
: G4VUserDetectorConstruction()
{
  fMaterials = GeoFacMaterials::GetInstance();
  thicknessOfPMMA = 0.3*cm;
  PMMA_pv = NULL;
  isOriginModel=false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacDetectorConstruction::~GeoFacDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GeoFacDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // construct materials via constructor
  
  
  G4cout<<"checking materials******************************************************************"<<G4endl<<*(G4Material::GetMaterialTable())<<G4endl;

  //world lv nad pv
  G4VPhysicalVolume* physWorld;
  
  

  //----------------------------------------------------------------------    
  // World
  //----------------------------------------------------------------------
  {
  G4double world_sizeXY = 12.0*cm;
  G4double world_sizeZ  = 12.0*cm;
  G4Material* world_mat = FindMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      false);        //overlaps checking

  }

  
  //----------------------------------------------------------------------    
  //SiPD
  //----------------------------------------------------------------------
  { 
  G4double dim_x = 0.26*cm;
  G4double dim_y = 0.05*cm;
  G4double dim_z = 0.26*cm;
  G4ThreeVector pos = G4ThreeVector(0*cm, dim_y+0.2*cm, 0*cm);

  G4Material* SiPD_mat = FindMaterial("SiPD");

  G4Box* SiPDbox = new G4Box("SiPDsolid",dim_x,dim_y,dim_z);
                      
  G4LogicalVolume* SiPD_lv =                         
    new G4LogicalVolume(SiPDbox,         //its solid
                        SiPD_mat,          //its material
                        "SiPD_lv");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos,                    //at position
                    SiPD_lv,             //its logical volume
                    "SiPD_pl",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    false);          //overlaps checking


  }


  
  //----------------------------------------------------------------------    
  // PMMA
  //----------------------------------------------------------------------
  
  ConstructPMMA();

  //----------------------------------------------------------------------    
  // shell edge (SHELL1)
  //----------------------------------------------------------------------
  if(!isOriginModel)
  {
  G4double innerRaduis = 0.5*cm;
  G4double outerRadius = 0.55*cm;
  G4double hz = 0.15*cm;
  G4double startAngle = 0.0 *deg;
  G4double endAngle = 360.0 * deg;

  G4double x = 0.0*cm;
  G4double y = 0.15*cm;
  G4double z = 0.0*cm;
  G4ThreeVector pos(x,y,z);
  G4double angle = 90*deg;
  G4RotationMatrix* rm = new G4RotationMatrix();
  
  rm->rotateX(angle);

  G4Material* SHELL1_mat = FindMaterial("Metal");

  G4Tubs* SHELL1_solid = new G4Tubs("SHELL1_solid",innerRaduis,outerRadius,hz,startAngle,endAngle);

  G4LogicalVolume* SHELL1_lv = new G4LogicalVolume(SHELL1_solid,SHELL1_mat,"SHELL1_lv");

  new G4PVPlacement(rm,pos,SHELL1_lv,"SHELL1_pl",logicWorld,false,0);

  //setting colour;

  //G4VisAttributes* colour = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.8));

  //SHELL1_lv->SetVisAttributes(colour);
  }

  //----------------------------------------------------------------------    
  // shell buttom (SHELL2)
  //----------------------------------------------------------------------
  if(!isOriginModel)
  {
  G4double innerRaduis = 0.0*cm;
  G4double outerRadius = 0.6*cm;
  G4double hz = 0.05*cm;
  G4double startAngle = 0.0 *deg;
  G4double endAngle = 360.0 * deg;

  G4double x = 0.0*cm;
  G4double y = -hz;
  G4double z = 0.0*cm;
  G4ThreeVector pos(x,y,z);
  G4double angle = 90*deg;
  G4RotationMatrix* rm = new G4RotationMatrix();
  
  rm->rotateX(angle);

  G4Material* SHELL2_mat = FindMaterial("Metal");

  G4Tubs* SHELL2_solid = new G4Tubs("SHELL2_solid",innerRaduis,outerRadius,hz,startAngle,endAngle);

  G4LogicalVolume* SHELL2_lv = new G4LogicalVolume(SHELL2_solid,SHELL2_mat,"SHELL2_lv");

  new G4PVPlacement(rm,pos,SHELL2_lv,"SHELL2_pl",logicWorld,false,0);

  //setting colour;

  //G4VisAttributes* colour = new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.8));

  //SHELL2_lv->SetVisAttributes(colour);

  }
  

  //----------------------------------------------------------------------    
  //PCB
  //----------------------------------------------------------------------
  if(!isOriginModel)
  { 
  G4double dim_x = 5.0*cm;
  G4double dim_y = 0.1*cm;
  G4double dim_z = 5.0*cm;
  G4ThreeVector pos = G4ThreeVector(0*cm, -dim_y-0.1*cm, 0*cm);

  G4Material* PCB_mat = FindMaterial("PCB");

  G4Box* PCB_solid = new G4Box("PCB_solid",dim_x,dim_y,dim_z);
                      
  G4LogicalVolume* PCB_lv =                         
    new G4LogicalVolume(PCB_solid,         //its solid
                        PCB_mat,          //its material
                        "PCB_lv");           //its name


  G4VPhysicalVolume* PCB_pv =        
  new G4PVPlacement(0,                       //no rotation
                    pos,                    //at position
                    PCB_lv,             //its logical volume
                    "PCB_pl",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    false);          //overlaps checking

  //PCB optical surface with air

  G4OpticalSurface* opSurface = new G4OpticalSurface("PCB_AIR");

  G4double sigma_alpha = 0.1;

  opSurface->SetType(dielectric_dielectric); 
  opSurface->SetModel(unified); 
  opSurface->SetFinish(groundfrontpainted); 
  opSurface->SetSigmaAlpha(sigma_alpha);


  G4LogicalBorderSurface* surface = new G4LogicalBorderSurface("PCB_AIR",physWorld,PCB_pv,opSurface);

  const G4int NUM = 2;

  G4double pp[NUM] = {2.038*eV, 7.144*eV}; 
  G4double reflectivity[NUM] = {0.2, 0.2}; 
  G4MaterialPropertiesTable* SMPT = new G4MaterialPropertiesTable();
  SMPT -> AddProperty("REFLECTIVITY",pp,reflectivity,NUM); 
  opSurface -> SetMaterialPropertiesTable(SMPT);





  


  }
  return physWorld;
}

G4Material* GeoFacDetectorConstruction::FindMaterial(G4String name) {
    G4Material* material = G4Material::GetMaterial(name,true);
    return material;
}

void GeoFacDetectorConstruction::ConstructSDandField(){
    if (!fmppcSD.Get()) {
     G4String mppcSDName = "GeppFac/PhotonDet";
     GeoFacPhotonDetSD* mppcSD = new GeoFacPhotonDetSD(mppcSDName);
     G4SDManager::GetSDMpointer()->AddNewDetector(mppcSD);
     fmppcSD.Put(mppcSD);
  }
  SetSensitiveDetector("SiPD_lv", fmppcSD.Get(), true);
}

void GeoFacDetectorConstruction::SetThicknessOfPMMA(G4double num){
  thicknessOfPMMA = num;
  ConstructPMMA();
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeoFacDetectorConstruction::ConstructPMMA(){
{
  if(PMMA_pv!=NULL)delete PMMA_pv;
  //hz = 0.583/2 or 0.3/2
  G4double outerRadius = 2.486*cm;
  G4double hz = thicknessOfPMMA/2;
  G4double startAngle = 0.0 *deg;
  G4double endAngle = 360.0 * deg;

  G4double x = 0.0*cm;
  G4double y = 0.35*cm+hz;
  G4double z = 0.0*cm;
  G4ThreeVector pos(x,y,z);
  G4double angle = 90*deg;
  G4RotationMatrix* rm = new G4RotationMatrix();
  
  rm->rotateX(angle);

  G4Material* PMMA_mat = FindMaterial("PMMA");

  G4Tubs* PMMA_shape = new G4Tubs("PMMAtube",0.0,outerRadius,hz,startAngle,endAngle);

  G4LogicalVolume* PMMA_lv = new G4LogicalVolume(PMMA_shape,PMMA_mat,"PMMA_lv");

  PMMA_pv = new G4PVPlacement(rm,pos,PMMA_lv,"PMMA_pl",logicWorld,false,0);
  
  }
}

void GeoFacDetectorConstruction::SetIsOriginModel(bool is){
  isOriginModel=is;
}