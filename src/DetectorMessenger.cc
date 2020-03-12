#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* detector)
  :DC(detector)
{
  // change target density
  changeTargetDir = new G4UIdirectory("/target/");
  changeTargetDir -> SetGuidance("Command to change the taregt density");
  changeTargetDensityCmd = new G4UIcmdWithADoubleAndUnit("/target/density", this);
  changeTargetDensityCmd -> SetGuidance("set target density");
  changeTargetDensityCmd -> SetParameterName("targetDensity", false);
  changeTargetDensityCmd -> SetDefaultUnit("mg/cm3");
  changeTargetDensityCmd -> SetUnitCandidates("g/cm3 mg/cm3"); 
  changeTargetDensityCmd -> AvailableForStates(G4State_Idle);
  // Change target material 
  changeTargetMaterialCmd = new G4UIcmdWithAString("/target/material", this);
  changeTargetMaterialCmd -> SetGuidance("set target material"); 
  changeTargetMaterialCmd -> SetParameterName("targetMaterial", false);
  changeTargetMaterialCmd -> SetDefaultValue("NeGas");
  changeTargetMaterialCmd -> AvailableForStates(G4State_Idle);
}

/////////////////////////////////////////////////////////////////////////////
DetectorMessenger::~DetectorMessenger()
{
    delete changeTargetDir; 
    delete changeTargetDensityCmd;
    delete changeTargetMaterialCmd; 
    //delete updateCmd;
}

/////////////////////////////////////////////////////////////////////////////
void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if ( command == changeTargetDensityCmd) {
    DC -> SetTargetDensity( changeTargetDensityCmd -> GetNewDoubleValue(newValue) );
  }
  else if (command == changeTargetMaterialCmd) {
    DC -> SetTargetMaterial(newValue);
  }
  //else if (command == updateCmd) {
  //DC -> UpdateGeometry();
  //}
}
