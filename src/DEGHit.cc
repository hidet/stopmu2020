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

#include "DEGHit.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4Circle.hh"
#include "G4Tubs.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

#include "G4ios.hh"

G4Allocator<DEGHit> DEGHitAllocator;

DEGHit::DEGHit()
{pLogV=0;}

DEGHit::DEGHit(G4LogicalVolume* logVol,G4int absNo) 
  : AbsID(absNo), pLogV(logVol)
{
}

DEGHit::~DEGHit()
{;}


DEGHit::DEGHit(const DEGHit &right)
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

const DEGHit& DEGHit::operator=(const DEGHit &right)
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

int DEGHit::operator==(const DEGHit &right) const
{
  return (this==&right) ? 1 : 0;
}


std::map<G4String,G4AttDef> DEGHit::fAttDefs;

void DEGHit::Draw()
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



const std::map<G4String,G4AttDef>* DEGHit::GetAttDefs() const
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

std::vector<G4AttValue>* DEGHit::CreateAttValues() const
{
  // Create expendable G4AttsValues for picking...
  std::vector<G4AttValue>* attValues = new std::vector<G4AttValue>;
  attValues->push_back
    (G4AttValue("HitType","DEGHit",""));
  attValues->push_back
    (G4AttValue("AbsID",G4UIcommand::ConvertToString(AbsID),""));
  attValues->push_back
    (G4AttValue("EDep",G4BestUnit(edep,"Energy"),""));
  //G4cout << "Checking...\n" << G4AttCheck(attValues, GetAttDefs());
  return attValues;
}


void DEGHit::Print()
{
}


