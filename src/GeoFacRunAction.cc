//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file GeoFacRunAction.cc
/// \brief Implementation of the GeoFacRunAction class

#include "GeoFacRunAction.hh"
#include "GeoFacPrimaryGeneratorAction.hh"
#include "GeoFacDetectorConstruction.hh"
// #include "GeoFacRun.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"





GeoFacRunAction::GeoFacRunAction()
: G4UserRunAction()
{ 

  // Register accumulable to the accumulable manager
  //G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  fMDAH = MyDataAnalysisHelper::GetInstance();


}



GeoFacRunAction::~GeoFacRunAction()
{}



void GeoFacRunAction::BeginOfRunAction(const G4Run* aRun)
{ 


  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  if(!IsMaster()){
    return;
  }
  //data analysis
  fMDAH->Clear();
  int n=aRun->GetNumberOfEventToBeProcessed();
  fMDAH->AddTotal(n);
  
  //run info
  startTick = clock();
  G4cout<<n<<" event to be processed"<<G4endl;
}



void GeoFacRunAction::EndOfRunAction(const G4Run* run)
{
  //G4int nofEvents = run->GetNumberOfEvent();



  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const GeoFacPrimaryGeneratorAction* generatorAction
   = static_cast<const GeoFacPrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        


  //counting time
  clock_t endTick = clock();
  time_t deltaTick = endTick-startTick;
  G4cout<<"It takes "<<deltaTick/CLOCKS_PER_SEC<<" s"<<G4endl;

    // Data analysis
  //G4cout<<fMDAH->GetHitCount()<<" in "<<fMDAH->GetTotalCount()<<" photon has hit the SiPD"<<G4endl;
  fMDAH->SetDeltaTick(deltaTick);
  fMDAH->WriteToRecord();


}



