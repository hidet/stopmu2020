#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
  :PGAction(Gun)
{ 
  beamParametersDir = new G4UIdirectory("/beam/");
  beamParametersDir -> SetGuidance("set parameters of beam");

  EnergyDir = new G4UIdirectory("/beam/energy/");  
  EnergyDir -> SetGuidance ("set energy of beam");  

  PositionDir = new G4UIdirectory("/beam/position/");  
  PositionDir -> SetGuidance ("set position of particle");  
  
  MomentumDir = new G4UIdirectory("/beam/momentum/");  
  MomentumDir -> SetGuidance ("set momentum of particle ");  

  particleNameCmd = new G4UIcmdWithAString("/beam/particle", this);
  particleNameCmd -> SetGuidance("set beam particle"); 
  particleNameCmd -> SetParameterName("particleName", false);
  particleNameCmd -> SetDefaultValue("geantino");
  particleNameCmd -> AvailableForStates(G4State_Idle);
  
  sigmaMomentumXCmd = new G4UIcmdWithADoubleAndUnit("/beam/momentum/sigmaX",this);
  sigmaMomentumXCmd -> SetGuidance("set sigma momentum x");
  sigmaMomentumXCmd -> SetParameterName("sMomentumX",false);
  sigmaMomentumXCmd -> SetDefaultUnit("MeV");
  sigmaMomentumXCmd -> SetUnitCandidates("keV MeV GeV TeV");
  sigmaMomentumXCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  sigmaMomentumYCmd = new G4UIcmdWithADoubleAndUnit("/beam/momentum/sigmaY",this);
  sigmaMomentumYCmd -> SetGuidance("set sigma momentum y");
  sigmaMomentumYCmd -> SetParameterName("sMomentumY",false);
  sigmaMomentumYCmd -> SetDefaultUnit("MeV");
  sigmaMomentumYCmd -> SetUnitCandidates("keV MeV GeV TeV");
  sigmaMomentumYCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  sigmaMomentumZCmd = new G4UIcmdWithADoubleAndUnit("/beam/momentum/sigmaZ",this);
  sigmaMomentumZCmd -> SetGuidance("set sigma momentum z");
  sigmaMomentumZCmd -> SetParameterName("sMomentumZ",false);
  sigmaMomentumZCmd -> SetDefaultUnit("MeV");
  sigmaMomentumZCmd -> SetUnitCandidates("keV MeV GeV TeV");
  sigmaMomentumZCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   

  dirMomentumCmd = new G4UIcmdWith3Vector("/beam/momentum/dir",this);
  dirMomentumCmd -> SetGuidance("set X,Y, and Z direction of Momentum");
  dirMomentumCmd -> SetParameterName("dirMomentumX","dirMomentumY","dirMomentumZ",false);
  dirMomentumCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  meanMomentumAmpCmd = new G4UIcmdWithADoubleAndUnit("/beam/momentum/meanamp",this);
  meanMomentumAmpCmd -> SetGuidance("set mean Momentum amplitude");
  meanMomentumAmpCmd -> SetParameterName("mMomentumAmp",false);
  meanMomentumAmpCmd -> SetDefaultUnit("MeV");
  meanMomentumAmpCmd -> SetUnitCandidates("keV MeV GeV TeV");
  meanMomentumAmpCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  biteMomentumAmpCmd = new G4UIcmdWithADouble("/beam/momentum/bite",this);
  biteMomentumAmpCmd -> SetGuidance("set Momentum bite percentage");
  biteMomentumAmpCmd -> SetParameterName("MomentumBite",false);
  biteMomentumAmpCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  gausMomentumAmpCmd = new G4UIcmdWithADouble("/beam/momentum/gaus",this);
  gausMomentumAmpCmd -> SetGuidance("set Momentum gaus sigma percentage");
  gausMomentumAmpCmd -> SetParameterName("MomentumSigma",false);
  gausMomentumAmpCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   
  
  meanKineticEnergyCmd = new G4UIcmdWithADoubleAndUnit("/beam/energy/mean",this);
  meanKineticEnergyCmd -> SetGuidance("set mean Kinetic energy");
  meanKineticEnergyCmd -> SetParameterName("mEnergy",false);
  meanKineticEnergyCmd -> SetDefaultUnit("MeV");
  meanKineticEnergyCmd -> SetUnitCandidates("eV keV MeV GeV TeV");
  meanKineticEnergyCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   
 
  sigmaEnergyCmd = new G4UIcmdWithADoubleAndUnit("/beam/energy/sigma",this);
  sigmaEnergyCmd -> SetGuidance("set sigma energy");
  sigmaEnergyCmd -> SetParameterName("sEnergy",false);
  sigmaEnergyCmd -> SetDefaultUnit("keV");
  sigmaEnergyCmd -> SetUnitCandidates("eV keV MeV GeV TeV");
  sigmaEnergyCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   
  
  positionXCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/X",this);
  positionXCmd -> SetGuidance("set x coordinate of particle");
  positionXCmd -> SetParameterName("xposition",false);
  positionXCmd -> SetDefaultUnit("mm");
  positionXCmd -> SetUnitCandidates("mm cm m");
  positionXCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   

  positionYCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/Y",this);
  positionYCmd -> SetGuidance("set y coordinate of particle");
  positionYCmd -> SetParameterName("yposition",false);
  positionYCmd -> SetDefaultUnit("mm");
  positionYCmd -> SetUnitCandidates("mm cm m");
  positionYCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);

  positionZCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/Z",this);
  positionZCmd -> SetGuidance("set z coordinate of particle");
  positionZCmd -> SetParameterName("zposition",false);
  positionZCmd -> SetDefaultUnit("mm");
  positionZCmd -> SetUnitCandidates("mm cm m");
  positionZCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   

  sigmaXCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/sigmaX",this);
  sigmaXCmd -> SetGuidance("set sigma x");
  sigmaXCmd -> SetParameterName("sxposition",false);
  sigmaXCmd -> SetDefaultUnit("mm");
  sigmaXCmd -> SetUnitCandidates("mm cm m");
  sigmaXCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   
  
  sigmaYCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/sigmaY",this);
  sigmaYCmd -> SetGuidance("set sigma y");
  sigmaYCmd -> SetParameterName("syposition",false);
  sigmaYCmd -> SetDefaultUnit("mm");
  sigmaYCmd -> SetUnitCandidates("mm cm m");
  sigmaYCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   

  sigmaZCmd = new G4UIcmdWithADoubleAndUnit("/beam/position/sigmaZ",this);
  sigmaZCmd -> SetGuidance("set sigma z");
  sigmaZCmd -> SetParameterName("szposition",false);
  sigmaZCmd -> SetDefaultUnit("mm");
  sigmaZCmd -> SetUnitCandidates("mm cm m");
  sigmaZCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);   

}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete beamParametersDir;
  delete EnergyDir;
  delete PositionDir;
  delete MomentumDir;

  delete particleNameCmd;
  delete meanKineticEnergyCmd;  
  delete sigmaEnergyCmd;
  delete positionXCmd; 
  delete positionYCmd; 
  delete positionZCmd;
  delete sigmaXCmd; 
  delete sigmaYCmd; 
  delete sigmaZCmd;
  delete dirMomentumCmd;
  delete meanMomentumAmpCmd;
  delete biteMomentumAmpCmd;
  delete gausMomentumAmpCmd;
  delete sigmaMomentumXCmd; 
  delete sigmaMomentumYCmd; 
  delete sigmaMomentumZCmd;
}  

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)                
{
  if (command == particleNameCmd)
    { PGAction -> SetParticleName(newValue);}
  else  if ( command == meanKineticEnergyCmd )
    { PGAction -> SetmeanKineticEnergy(meanKineticEnergyCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaEnergyCmd )
    { PGAction -> SetSigmaEnergy(sigmaEnergyCmd -> GetNewDoubleValue(newValue));}
  else if ( command == positionXCmd )
    { PGAction -> SetPositionX(positionXCmd -> GetNewDoubleValue(newValue));}
  else if ( command == positionYCmd )
    { PGAction -> SetPositionY(positionYCmd -> GetNewDoubleValue(newValue));}
  else if ( command == positionZCmd )
    { PGAction -> SetPositionZ(positionZCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaXCmd )
    { PGAction -> SetSigmaX(sigmaXCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaYCmd )
    { PGAction -> SetSigmaY(sigmaYCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaZCmd )
    { PGAction -> SetSigmaZ(sigmaZCmd -> GetNewDoubleValue(newValue));}
  else if ( command == dirMomentumCmd )
    { G4ThreeVector size = dirMomentumCmd -> GetNew3VectorValue(newValue);
      PGAction -> SetDirMomentum(size.getX(),size.getY(),size.getZ());}
  else if ( command == meanMomentumAmpCmd )
    { PGAction -> SetmeanMomentumAmp(meanMomentumAmpCmd -> GetNewDoubleValue(newValue));}
  else if ( command == biteMomentumAmpCmd )
    { PGAction -> SetbiteMomentumAmp(biteMomentumAmpCmd -> GetNewDoubleValue(newValue));}
  else if ( command == gausMomentumAmpCmd )
    { PGAction -> SetgausMomentumAmp(gausMomentumAmpCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaMomentumXCmd )
    { PGAction -> SetSigmaMomentumX(sigmaMomentumXCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaMomentumYCmd )
    { PGAction -> SetSigmaMomentumY(sigmaMomentumYCmd -> GetNewDoubleValue(newValue));}
  else if ( command == sigmaMomentumZCmd )
    { PGAction -> SetSigmaMomentumZ(sigmaMomentumZCmd -> GetNewDoubleValue(newValue));}
}
