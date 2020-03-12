#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWith3Vector;

class PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
  ~PrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);
  
private:
  PrimaryGeneratorAction* PGAction;
  G4UIcmdWithAString*               particleNameCmd;
  G4UIcmdWithADoubleAndUnit*        meanKineticEnergyCmd;    
  G4UIcmdWithADoubleAndUnit*        sigmaEnergyCmd;  
  G4UIcmdWithADoubleAndUnit*        positionXCmd;   
  G4UIcmdWithADoubleAndUnit*        positionYCmd; 
  G4UIcmdWithADoubleAndUnit*        positionZCmd;
  G4UIcmdWithADoubleAndUnit*        sigmaXCmd; 
  G4UIcmdWithADoubleAndUnit*        sigmaYCmd; 
  G4UIcmdWithADoubleAndUnit*        sigmaZCmd;
  G4UIcmdWith3Vector*               dirMomentumCmd;
  G4UIcmdWithADoubleAndUnit*        meanMomentumAmpCmd;
  G4UIcmdWithADouble*               biteMomentumAmpCmd;
  G4UIcmdWithADouble*               gausMomentumAmpCmd;
  G4UIcmdWithADoubleAndUnit*        sigmaMomentumXCmd; 
  G4UIcmdWithADoubleAndUnit*        sigmaMomentumYCmd;
  G4UIcmdWithADoubleAndUnit*        sigmaMomentumZCmd; 
  
  G4UIdirectory*                    beamParametersDir;
  G4UIdirectory*                    EnergyDir;
  G4UIdirectory*                    PositionDir;
  G4UIdirectory*                    MomentumDir;
};

#endif

