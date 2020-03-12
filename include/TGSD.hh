#ifndef TGSD_h
#define TGSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TGHit.hh"
#include "globals.hh"

#include "Common.h"
#include "DetectorConstruction.hh"
#include "Interaction.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class Interaction;
class DetectorConstruction;
class TGSD : public G4VSensitiveDetector
{
  
public:
  TGSD(G4String name);
  ~TGSD();
  
  void   Initialize(G4HCofThisEvent*HCE);
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*);
  void   EndOfEvent(G4HCofThisEvent*HCE);

private:
  TGHitsCollection* hitsCollection;
  G4String          sensitiveDetectorName;
  G4int             TGHCID[NbOfTG];
  G4int             hit_trackID;
  Interaction       interaction;
  DetectorConstruction        dID;
};

#endif
