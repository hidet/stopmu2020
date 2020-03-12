#include "TESSD.hh"
#include "TESHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"

#include "Randomize.hh"
#include <math.h>
#include "G4ios.hh"
#include "globals.hh"


TESSD::TESSD(const G4String name)
  :G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="tesCollection");
  sensitiveDetectorName=name;
}

TESSD::~TESSD(){;}

void TESSD::Initialize(G4HCofThisEvent* HCE)
{
  // create hit collection object
  hitsCollection = new TESHitsCollection
    (sensitiveDetectorName,collectionName[0]);

  for(G4int l=0; l<NbOfTES; l++) {
    TESHCID[l] = -1;
  }
  //verboseLevel = 0;
}


G4bool TESSD::ProcessHits(G4Step*aStep, G4TouchableHistory*)
{
  G4double edep  = aStep->GetTotalEnergyDeposit();
  G4TrackStatus trackstatus = aStep->GetTrack()->GetTrackStatus();
  G4double stepl = aStep->GetStepLength();
  G4int trackID = aStep->GetTrack()->GetTrackID();
  G4int parentID = aStep->GetTrack()->GetParentID();
  G4String pname = aStep->GetTrack()->GetDefinition()->GetParticleName();
  G4int pdg = aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();
  
  if (pname!="geantino" && trackstatus!=2 && edep==0) { return true; }  

  G4ThreeVector trackpos = aStep->GetTrack()->GetPosition();
  G4ThreeVector trackmom = aStep->GetTrack()->GetMomentum();
  G4double tracktime = aStep->GetTrack()->GetGlobalTime();
  G4double trackkene = aStep->GetTrack()->GetKineticEnergy();
  G4double trackl = aStep->GetTrack()->GetTrackLength();

  G4ThreeVector prepos = aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector premom = aStep->GetPreStepPoint()->GetMomentum();
  G4double pretime = aStep->GetPreStepPoint()->GetGlobalTime();
  G4double prekene = aStep->GetPreStepPoint()->GetKineticEnergy();
 
  // volume
  G4int absNo = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetCopyNo();
  G4String logname = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetLogicalVolume()->GetName();
  
  // vertex information
  G4ThreeVector    vpos = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector   vmomd = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double        vkene = aStep->GetTrack()->GetVertexKineticEnergy();
  G4String        vname = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
  G4int           vlvid = dID.GetDetectorID(vname);  
  
  G4String cproc = "";  G4int cprocessID  = -9999;
  if (aStep->GetTrack()->GetCreatorProcess() != NULL) {
    cproc = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
    cprocessID = interaction.GetProcessID(cproc,prekene);
  } else {
    cproc = "Primary";
    cprocessID = 9999;
  }

  G4String proc = "";  G4int processID  = -9999;
  if ( aStep->GetPostStepPoint()->GetProcessDefinedStep() != NULL ) {
    proc = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    processID = interaction.GetProcessID(proc,prekene);
  } else {
    G4cout << "Not well defined a PostSetpPoint" << G4endl;
    return true;
  }
  
  G4bool SEC=false;
  if (vname==logname) SEC=true;

  if (verboseLevel>0) {
    if (vname==logname) G4cout << "Secondary" << G4endl;
    G4cout << "   TESSD " << G4endl;
    G4cout << "   Track ID      = " << trackID << G4endl;
    G4cout << "   PDG code      = " << pdg << " " << pname << G4endl;
    G4cout << "   vertex vol : " << vname << " " << vlvid << G4endl;
    G4cout << "   vertex pos    = " << vpos.x() << " " << vpos.y() << " " << vpos.z() << G4endl;
    G4cout << "   vertex momd   = " << vmomd.x() << " " << vmomd.y() << " " << vmomd.z() << G4endl;
    G4cout << "   vertex kene   = " << vkene << G4endl;
    G4cout << "   cprocess " << cproc << " " << cprocessID << G4endl;
    G4cout << "   touch vol  : " << logname << G4endl;
    G4cout << "   prekene(MeV)  = " << prekene/MeV << G4endl;
    G4cout << "   postkene(MeV) = " << trackkene/MeV << G4endl;
    G4cout << "   edep(MeV)     = " << edep/MeV << G4endl;
    G4cout << "   stepl(mm)     = " << stepl/mm << G4endl;
    G4cout << "   trackl(mm)    = " << trackl/mm << G4endl;
    G4cout << "   process " << proc << " " << processID << G4endl;
    G4cout << G4endl;
  }
  
  if (TESHCID[absNo]==-1) {// first step & first hit
    TESHit* aHit = new TESHit
	(aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetLogicalVolume(),absNo);
    hit_trackID = trackID;
    
    aHit->SetTrackID(trackID);
    aHit->SetParentID(parentID);
    aHit->SetPDGcode(pdg);
    aHit->SetStatus(trackstatus);
    aHit->SetVertexPos(vpos);
    aHit->SetVertexMomd(vmomd);
    aHit->SetVertexKene(vkene);
    aHit->SetVertexLvid(vlvid);
    aHit->SetcProcessID(cprocessID);
    aHit->SetProcessID(processID);
    aHit->SetEdep(edep);
    aHit->SetTrackl(stepl);
      
    // ---- pre-information ----
    aHit->SetHitPos(prepos);
    aHit->SetHitMom(premom);
    aHit->SetHitTime(pretime);
      
    // ---- post-information ----
    aHit->SetLastPos(trackpos);
    aHit->SetLastMom(trackmom);
    aHit->SetLastTime(tracktime);
      
    G4int icell = hitsCollection->insert(aHit);
    TESHCID[absNo] = icell - 1;
  } else {// next step or next hit
    (*hitsCollection)[TESHCID[absNo]]->AddEdep(edep);
    
    // same particle next step
    if (trackID==hit_trackID) {
      (*hitsCollection)[TESHCID[absNo]]->SetStatus(trackstatus);
      (*hitsCollection)[TESHCID[absNo]]->SetProcessID(processID);
      (*hitsCollection)[TESHCID[absNo]]->SetLastPos(trackpos);
      (*hitsCollection)[TESHCID[absNo]]->SetLastMom(trackmom);
      (*hitsCollection)[TESHCID[absNo]]->SetLastTime(tracktime);
      (*hitsCollection)[TESHCID[absNo]]->AddTrackl(stepl);
    } else if (trackID!=hit_trackID && SEC==false) {
      if (TESHCID[absNo]==TESMultiMax-1) {
        G4cout << "ERROR: too much number of Hit in TESSD: "  << TESMultiMax-1 << G4endl;
        return true;
      }
      TESHit* aHit = new TESHit
        (aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetLogicalVolume(),absNo);
      hit_trackID = trackID;
      
      aHit->SetTrackID(trackID);
      aHit->SetParentID(parentID);
      aHit->SetPDGcode(pdg);
      aHit->SetStatus(trackstatus);
      aHit->SetVertexPos(vpos);
      aHit->SetVertexMomd(vmomd);
      aHit->SetVertexKene(vkene);
      aHit->SetVertexLvid(vlvid);
      aHit->SetcProcessID(cprocessID);
      aHit->SetProcessID(processID);
      aHit->SetEdep(edep);
      aHit->SetTrackl(stepl);

      // ---- pre-information ----
      aHit->SetHitPos(prepos);
      aHit->SetHitMom(premom);
      aHit->SetHitTime(pretime);
	
      // ---- post-information ----
      aHit->SetLastPos(trackpos);
      aHit->SetLastMom(trackmom);
      aHit->SetLastTime(tracktime);
	
      G4int icell = hitsCollection->insert(aHit);
      TESHCID[absNo] = icell - 1;
    }
  }
  
  return true;
}

void TESSD::EndOfEvent(G4HCofThisEvent* HCE)
{ 
  static G4int HCID = -1;
  if(HCID<0)
    { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);
}
