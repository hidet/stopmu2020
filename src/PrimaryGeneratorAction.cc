#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UImanager.hh"
#include "G4LorentzVector.hh"
#include "G4LorentzConvertor.hh"

#include "globals.hh"
#include "Randomize.hh"
#include "math.h"

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "Common.h"

using namespace CLHEP;

PrimaryGeneratorAction::PrimaryGeneratorAction()
  :rndmFlag("on")
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  particleTable = G4ParticleTable::GetParticleTable();

  SetParticleName("mu-");
  SetmeanMomentumAmp(20.0*MeV);
  SetDirMomentum(0.,0.,1.);
  SetPositionX(0.*mm);
  SetPositionY(0.*mm);
  SetPositionZ(-10.*mm);
  SetSigmaX(0.*mm);
  SetSigmaY(0.*mm);
  SetSigmaZ(0.*mm);

  primarygeneratorMessenger = new PrimaryGeneratorMessenger(this);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete primarygeneratorMessenger;
  delete particleGun;
}

void PrimaryGeneratorAction::SetParticleName(G4String pname){particleName = pname;}
void PrimaryGeneratorAction::SetmeanMomentumAmp(G4double momamp){meanMomentumAmp=momamp;}
void PrimaryGeneratorAction::SetbiteMomentumAmp(G4double mombite){biteMomentumAmp=mombite;}
void PrimaryGeneratorAction::SetgausMomentumAmp(G4double momgaus){gausMomentumAmp=momgaus;}
void PrimaryGeneratorAction::SetPositionX(G4double x){X0=x;}
void PrimaryGeneratorAction::SetPositionY(G4double y){Y0=y;}
void PrimaryGeneratorAction::SetPositionZ(G4double z){Z0=z;}
void PrimaryGeneratorAction::SetSigmaX(G4double sigx){sigmaX=sigx;}
void PrimaryGeneratorAction::SetSigmaY(G4double sigy){sigmaY=sigy;}
void PrimaryGeneratorAction::SetSigmaZ(G4double sigz){sigmaZ=sigz;}
void PrimaryGeneratorAction::SetDirMomentum(G4double xdir, G4double ydir, G4double zdir)
{
  dirMomentum=G4ThreeVector(xdir,ydir,zdir);
}
void PrimaryGeneratorAction::SetSigmaMomentumX(G4double sigmomx){sigmaMomentumX=sigmomx;}
void PrimaryGeneratorAction::SetSigmaMomentumY(G4double sigmomy){sigmaMomentumY=sigmomy;}
void PrimaryGeneratorAction::SetSigmaMomentumZ(G4double sigmomz){sigmaMomentumZ=sigmomz;}
void PrimaryGeneratorAction::SetmeanKineticEnergy(G4double ene){meanKineticEnergy=ene;}
void PrimaryGeneratorAction::SetSigmaEnergy(G4double sigene){sigmaEnergy=sigene;}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // not acceptance mode (normal beam mode)
#ifndef ACCEPTANCE
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  G4double particle_mass = particleTable->FindParticle(particleName)->GetPDGMass();
  G4double beam_mom = meanMomentumAmp;
  if (biteMomentumAmp!=0) {
    beam_mom = meanMomentumAmp * (1 + RandFlat::shoot(-biteMomentumAmp,biteMomentumAmp)/100.0);
  }
  else if (gausMomentumAmp!=0) {
    beam_mom = RandGauss::shoot(meanMomentumAmp, meanMomentumAmp*gausMomentumAmp/100.);
  }
  G4double beam_kene = sqrt(beam_mom*beam_mom + particle_mass*particle_mass) - particle_mass;
  //G4double beam_kene = RandGauss::shoot(meanKineticEnergy, sigmaEnergy);
  
  // generate position
  G4double vtx = RandGauss::shoot(X0, sigmaX);
  G4double vty = RandGauss::shoot(Y0, sigmaY);
  G4double vtz = RandGauss::shoot(Z0, sigmaZ);
  positionXYZ = G4ThreeVector(vtx,vty,vtz);
  
  // for random radiation direction
  //G4double PhiVal   = 2.*pi*G4UniformRand()*rad;  
  //G4double ZVal     = 2.0*(0.5-G4UniformRand());  
  //xdir = sqrt(1-ZVal*ZVal)*cos(PhiVal);
  //ydir = sqrt(1-ZVal*ZVal)*sin(PhiVal);
  //zdir = ZVal;
  //dirMomentum=G4ThreeVector(xdir,ydir,zdir);  

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticlePosition(positionXYZ);
  particleGun->SetParticleMomentumDirection(dirMomentum);
  particleGun->SetParticleEnergy(beam_kene);
  particleGun->SetParticleTime(0.0);
  particleGun->GeneratePrimaryVertex(anEvent);

  //G4cout << G4endl;
  //G4cout << "#############" << G4endl;
  //G4cout << "N PrimVertex " << anEvent->GetNumberOfPrimaryVertex() << G4endl;
  //G4cout << "#############" << G4endl;
  //
  //G4PrimaryVertex* primvtx;
  //for (int i=0; i<anEvent->GetNumberOfPrimaryVertex(); i++){
  //  primvtx = anEvent->GetPrimaryVertex(i);
  //  primvtx->Print();
  //  G4cout << particleName << G4endl;
  //  G4cout << beam_mom/MeV << " MeV/c " << meanKineticEnergy/MeV << " MeV " << G4endl; 
  //}
  //G4cout << G4endl;  
  return;
#endif

  
#ifdef ACCEPTANCE
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  G4double particle_mass = particleTable->FindParticle(particleName)->GetPDGMass();
  G4double beam_mom = meanMomentumAmp;
  G4double beam_kene = sqrt(beam_mom*beam_mom + particle_mass*particle_mass) - particle_mass;

  // generate position
  G4double vtx_lim=58*mm;
  G4double vty_lim=58*mm;
  G4double vtx = 0.;
  G4double vty = 0.;
  G4bool fail=true;
  while (fail) {
    vtx = RandGauss::shoot(X0, sigmaX);
    vty = RandGauss::shoot(Y0, sigmaY);
    if ( abs(vtx)<=vtx_lim && abs(vty)<=vty_lim ) {fail=false; break;}
  }
  G4double vtz = snout300k_pos[2] + 50.*2.*(G4UniformRand()-0.5)*mm;
  positionXYZ = G4ThreeVector(vtx,vty,vtz);
  
  // for random radiation direction
  G4double PhiVal   = 2.*pi*G4UniformRand()*rad;  
  G4double ZVal     = 2.0*(0.5-G4UniformRand());  
  G4double xdir = sqrt(1-ZVal*ZVal)*cos(PhiVal);
  G4double ydir = sqrt(1-ZVal*ZVal)*sin(PhiVal);
  G4double zdir = ZVal;
  dirMomentum=G4ThreeVector(xdir,ydir,zdir);
  
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticlePosition(positionXYZ);
  particleGun->SetParticleMomentumDirection(dirMomentum);
  particleGun->SetParticleEnergy(beam_kene);
  particleGun->SetParticleTime(0.0);
  particleGun->GeneratePrimaryVertex(anEvent);
  
  return;
#endif
  

  
}
