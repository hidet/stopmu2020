#include "TESHit.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

G4Allocator<TESHit> TESHitAllocator;

TESHit::TESHit()
{pLogV=0;}

TESHit::TESHit(G4LogicalVolume* logVol,G4int absNo) 
  : AbsID(absNo), pLogV(logVol)
{;}

TESHit::TESHit(const TESHit &right)
: G4VHit() 
{
  AbsID = right.AbsID;
  trackID = right.trackID;
  status = right.status;
  processID = right.processID;
  cprocessID = right.cprocessID;
  parentID = right.parentID;
  PDGcode = right.PDGcode; 
  edep = right.edep;
  trackl = right.trackl;
  hittime = right.hittime;
  hitmom = right.hitmom;
  hitpos = right.hitpos;
  lasttime = right.lasttime;
  lastmom = right.lastmom;
  lastpos = right.lastpos;
  vpos = right.vpos;
  vmomd = right.vmomd;
  vkene = right.vkene;
  vlvid = right.vlvid;
  rot = right.rot;
  pLogV = right.pLogV;
}

TESHit::~TESHit()
{;}

const TESHit& TESHit::operator=(const TESHit &right)
{
  AbsID = right.AbsID;
  trackID = right.trackID;
  status = right.status;
  processID = right.processID;
  cprocessID = right.cprocessID;
  parentID = right.parentID;
  PDGcode = right.PDGcode; 
  edep = right.edep;
  trackl = right.trackl;
  hittime = right.hittime;
  hitmom = right.hitmom;
  hitpos = right.hitpos;
  lasttime = right.lasttime;
  lastmom = right.lastmom;
  lastpos = right.lastpos;
  vpos = right.vpos;
  vmomd = right.vmomd;
  vkene = right.vkene;
  vlvid = right.vlvid;
  rot = right.rot;
  pLogV = right.pLogV;
  return *this;
}

int TESHit::operator==(const TESHit &right) const
{
  return (this==&right) ? 1 : 0;
}

std::map<G4String,G4AttDef> TESHit::fAttDefs;

void TESHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      G4Transform3D trans(rot,hitpos);
      G4VisAttributes attribs;
      const G4VisAttributes* pVA = pLogV->GetVisAttributes();
      if(pVA) attribs = *pVA;
      G4Colour colour(1.,0.,0.);
      attribs.SetColour(colour);
      attribs.SetForceSolid(true);
      pVVisManager->Draw(*pLogV,attribs,trans);
    }
}

const std::map<G4String,G4AttDef>* TESHit::GetAttDefs() const
{
  // G4AttDefs have to have long life.  Use static member...
  if (fAttDefs.empty()) {
    fAttDefs["HitType"] =
      G4AttDef("HitType","Type of hit","Physics","","G4String");
    fAttDefs["AbsID"]   = G4AttDef("AbsID","Abs ID","Physics","","G4int");
    fAttDefs["EDep"] =
      G4AttDef("EDep","Energy deposited","Physics","G4BestUnit","G4double");
  }
  return &fAttDefs;
}

std::vector<G4AttValue>* TESHit::CreateAttValues() const
{
  // Create expendable G4AttsValues for picking...
  std::vector<G4AttValue>* attValues = new std::vector<G4AttValue>;
  attValues->push_back
    (G4AttValue("HitType","TESHit",""));
  attValues->push_back
    (G4AttValue("AbsID",G4UIcommand::ConvertToString(AbsID),""));
  attValues->push_back
    (G4AttValue("EDep",G4BestUnit(edep,"Energy"),""));
  //G4cout << "Checking...\n" << G4AttCheck(attValues, GetAttDefs());
  return attValues;
}

void TESHit::Print()
{;}


