#include "TGSD.hh"
#include "TGHit.hh"

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

TGSD::TGSD(const G4String name)
  :G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="tgCollection");
  sensitiveDetectorName=name;
}

TGSD::~TGSD(){;}

void TGSD::Initialize(G4HCofThisEvent* HCE)
{
  // create hit collection object
  hitsCollection = new TGHitsCollection
    (sensitiveDetectorName,collectionName[0]);
  
  for(G4int k=0; k<NbOfTG; k++) {
    TGHCID[k] = -1;
  }
  //verboseLevel = 0;
}

G4bool TGSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4double          edep = aStep->GetTotalEnergyDeposit();
  G4double         stepl = aStep->GetStepLength();
  G4Track      *theTrack = aStep->GetTrack();
  G4TrackStatus   status = theTrack->GetTrackStatus();
  if (status!=2 && edep==0) { return true; }
  G4int          trackID = theTrack->GetTrackID();
  G4int         parentID = theTrack->GetParentID();
  G4String         pname = theTrack->GetDefinition()->GetParticleName();
  G4int              pdg = theTrack->GetDynamicParticle()->GetPDGcode();
  G4ThreeVector trackpos = theTrack->GetPosition();
  G4ThreeVector trackmom = theTrack->GetMomentum();
  G4double     tracktime = theTrack->GetGlobalTime();
  G4double     trackkene = theTrack->GetKineticEnergy();
  G4double        trackl = theTrack->GetTrackLength();
  // vertex information
  G4ThreeVector    vpos  = theTrack->GetVertexPosition();
  G4ThreeVector   vmomd  = theTrack->GetVertexMomentumDirection();
  G4double        vkene  = theTrack->GetVertexKineticEnergy();
  G4String        vname  = theTrack->GetLogicalVolumeAtVertex()->GetName();
  G4int           vlvid  = dID.GetDetectorID(vname);
  // step point
  G4StepPoint*   PreStep = aStep->GetPreStepPoint();
  G4StepPoint*  PostStep = aStep->GetPostStepPoint();
  // prestep
  G4ThreeVector   prepos = PreStep->GetPosition();
  G4ThreeVector   premom = PreStep->GetMomentum();
  G4double       pretime = PreStep->GetGlobalTime();
  G4double       prekene = PreStep->GetKineticEnergy();
  // pre volume
  G4int            absNo = PreStep->GetTouchable()->GetVolume()->GetCopyNo();
  G4String       logname = PreStep->GetTouchable()->GetVolume()->GetLogicalVolume()->GetName();
  // process ID
  G4String cproc = "";  G4int cprocessID  = -9999;
  if (theTrack->GetCreatorProcess() != NULL) {
    cproc = theTrack->GetCreatorProcess()->GetProcessName();
    cprocessID = interaction.GetProcessID(cproc,prekene);
  } else {
    cproc = "Primary";
    cprocessID = 9999;
  }
  G4String proc = "";  G4int processID  = -9999;
  if ( PostStep->GetProcessDefinedStep() != NULL ) {
    proc = PostStep->GetProcessDefinedStep()->GetProcessName();
    processID = interaction.GetProcessID(proc,prekene);
  } else {
    G4cout << "Not well defined a PostSetpPoint" << G4endl;
    return true;
  }
  // secondary
  G4bool SEC=false;
  if (vname==logname) SEC=true;

  if (verboseLevel>0) {
    if (vname==logname) G4cout << "Secondary" << G4endl;
    G4cout << "   TGSD " << G4endl;
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
  
  if (TGHCID[absNo]==-1) {// first step & first hit
    TGHit* aHit = new TGHit
      (PreStep->GetTouchable()->GetVolume()->GetLogicalVolume(),absNo);
    hit_trackID = trackID;
    
    aHit->SetTrackID(trackID);
    aHit->SetParentID(parentID);
    aHit->SetPDGcode(pdg);
    aHit->SetStatus(status);
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
    TGHCID[absNo] = icell - 1;
  } else {// next step or next hit
    (*hitsCollection)[TGHCID[absNo]]->AddEdep(edep);
    if (trackID==hit_trackID) {// same particle next step
      (*hitsCollection)[TGHCID[absNo]]->SetStatus(status);
      (*hitsCollection)[TGHCID[absNo]]->SetProcessID(processID);
      (*hitsCollection)[TGHCID[absNo]]->SetLastPos(trackpos);
      (*hitsCollection)[TGHCID[absNo]]->SetLastMom(trackmom);
      (*hitsCollection)[TGHCID[absNo]]->SetLastTime(tracktime);
      (*hitsCollection)[TGHCID[absNo]]->AddTrackl(stepl);
    } else if (trackID!=hit_trackID && SEC==false) {
      if (TGHCID[absNo]==TGMultiMax-1) {
        G4cout << "ERROR: too much number of Hit in TGSD: "  << TGMultiMax-1 << G4endl;
        return true;
      }
      TGHit* aHit = new TGHit
        (PreStep->GetTouchable()->GetVolume()->GetLogicalVolume(),absNo);
      hit_trackID = trackID;
      
      aHit->SetTrackID(trackID);
      aHit->SetParentID(parentID);
      aHit->SetPDGcode(pdg);
      aHit->SetStatus(status);
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
      TGHCID[absNo] = icell - 1;
    }
  }
  return true;
}

void TGSD::EndOfEvent(G4HCofThisEvent* HCE)
{ 
  static G4int HCID = -1;
  if(HCID<0)
    { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);
}
