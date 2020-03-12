#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#include "CommonXray.h"
#include "CalibSRC.h"

class PrimaryGeneratorMessenger;
class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class G4ParticleTable;
class PrimaryGeneratorMessenger;
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);
  void SetRndmFlag(G4String val) { rndmFlag = val;}
  void SetParticleName(G4String);
  void SetmeanKineticEnergy(G4double);
  void SetSigmaEnergy(G4double);
  void SetPositionX(G4double);
  void SetPositionY(G4double);
  void SetPositionZ(G4double);
  void SetSigmaX(G4double);
  void SetSigmaY(G4double);
  void SetSigmaZ(G4double);
  void SetDirMomentum(G4double, G4double, G4double);
  void SetmeanMomentumAmp(G4double);
  void SetbiteMomentumAmp(G4double);
  void SetgausMomentumAmp(G4double);
  void SetSigmaMomentumX(G4double);
  void SetSigmaMomentumY(G4double);
  void SetSigmaMomentumZ(G4double);

private:
  PrimaryGeneratorMessenger* primarygeneratorMessenger;
  G4ParticleTable* particleTable;
  G4String particleName="geantino";
  G4double meanKineticEnergy=0;
  G4double sigmaEnergy=0;
  G4double X0=0;
  G4double Y0=0;
  G4double Z0=0;
  G4double sigmaX=0;
  G4double sigmaY=0;
  G4double sigmaZ=0;
  G4ThreeVector positionXYZ;
  G4ThreeVector dirMomentum;
  G4double meanMomentumAmp=0;
  G4double biteMomentumAmp=0;
  G4double gausMomentumAmp=0;
  G4double sigmaMomentumX=0;
  G4double sigmaMomentumY=0;
  G4double sigmaMomentumZ=0;
  //G4GeneralParticleSource* particleGun;
  G4ParticleGun*            particleGun;
  G4String                  rndmFlag;

};

#endif
