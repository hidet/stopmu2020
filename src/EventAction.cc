#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ios.hh"
#include "Randomize.hh"

#include "EventAction.hh"
#include "RunAction.hh"
#include "TESHit.hh"
#include "TGHit.hh"
#include "DEGHit.hh"
#include "AnaManager.hh"
#include "FileMessenger.hh"
#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>


EventAction::EventAction(AnaManager* ana)
//  : anam(ana), drawFlag("all"),printModulo(1)
  : anam(ana)
{
  DEGHCID    = -1;
  TGHCID     = -1;
  TESHCID    = -1;
  SetFileName("hoge");
  SetTimeNow(true);
  fileMessenger = new FileMessenger(this);
}

EventAction::~EventAction()
{
  delete fileMessenger;
}


void EventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
  
  // ------------------------------------------------------------
  if (evtNb==0) {
    timerclear(&tv1);
    NEVTBP = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    //NEVTBP = anam->GetNumberOfToBeProcessed();
    gettimeofday(&tv1, NULL);
    BookOutputTree(FileName,timenow);
  }
  
  // get collection IDs
  if (TESHCID<0 || TGHCID<0 || DEGHCID<0) {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String colNam;
    TESHCID  = SDman->GetCollectionID(colNam="TES/tesCollection");
    TGHCID   = SDman->GetCollectionID(colNam="TG/tgCollection");
    DEGHCID  = SDman->GetCollectionID(colNam="DEG/degCollection");
  }

  InitializeTree(evtNb);
  anam->SetEventID(evtNb);

  if (evtNb<10) 
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
  else if (evtNb>=10 && evtNb<100) {
    if (evtNb%10 == 0) PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
  else if (evtNb>=100 && evtNb<1000) {
    if (evtNb%100 == 0)  PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
  else if (evtNb>=1e3 && evtNb<1e4) {
    if (evtNb%100 == 0)  PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
  else if (evtNb>=1e4 && evtNb<1e5) {
    if (evtNb%1000 == 0) PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
  else if (evtNb>=1e5 && evtNb<1e6) {
    if (evtNb%10000 == 0) PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
  else if (evtNb>=1e6) {
    if (evtNb%100000 == 0) PrintEventNumber(evtNb,NEVTBP,tv1,tv2,tv3);
  }
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  evid=evtNb;

  // beam
  G4int nofpv = evt->GetNumberOfPrimaryVertex();
  nbeam = nofpv;
  if (nofpv>BeamMultiMax) {
    G4cout << "Error: Number of Primary Beam is too much !" << G4endl;
    G4cout << "nofpv " << nofpv << G4endl;
    return;
  }
  
  for (G4int i=0; i<nofpv; i++) {
    beam_pdg[i]      = evt->GetPrimaryVertex(i)->GetPrimary()->GetPDGcode();
    beam_track[i]    = evt->GetPrimaryVertex(i)->GetPrimary()->GetTrackID();
    beam_hit_pos[i]  = evt->GetPrimaryVertex(i)->GetPosition();  	     
    beam_hit_mom[i]  = evt->GetPrimaryVertex(i)->GetPrimary()->GetMomentum();
    beam_hit_time[i] = evt->GetPrimaryVertex(i)->GetPrimary()->GetProperTime();// is this correct?
    if (beam_pdg[i]==-321 || beam_pdg[i]==-211 || beam_pdg[i]==11 ||
        beam_pdg[i]==13 || beam_pdg[i]==22) {
      if (evtNb==anam->GetEventIDStepKM()) {
        beam_proc[i]       = anam->GetProcessIDKM();      
        beam_status[i]     = anam->GetStatusKM();
        beam_last_time[i]  = anam->GetStepPostTimeKM();
        beam_last_pos[i]   = anam->GetStepPostPosKM();
        beam_last_mom[i]   = anam->GetStepPostMomKM();
        beam_logvid[i]     = anam->GetStepLogVIDKM();
      } else {
        G4cout << "Warning: evID mismatch to StepKM evID" << G4endl;
      }
    } else if (beam_pdg[i]==+321 || beam_pdg[i]==+211 || beam_pdg[i]==-11 ||
               beam_pdg[i]==-13) {
      if (evtNb==anam->GetEventIDStepKP()) {
        beam_proc[i]       = anam->GetProcessIDKP();      
        beam_status[i]     = anam->GetStatusKP();
        beam_last_time[i]  = anam->GetStepPostTimeKP();
        beam_last_pos[i]   = anam->GetStepPostPosKP();
        beam_last_mom[i]   = anam->GetStepPostMomKP();
        beam_logvid[i]     = anam->GetStepLogVIDKP();
      } else {
        G4cout << "Warning: evID mismatch to StepKP evID" << G4endl;
      }
    }
  }
  
  // ---------- Sensitive Detectors ------------
  if (TESHCID<0 && DEGHCID<0 && TGHCID<0) {
    G4cout << "No hit detector, skip this event." << G4endl;
    return;
  }
  
  // get hitscollection of this event
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  // hitcollections
  TESHitsCollection*   TESHC   = 0;
  TGHitsCollection*    TGHC    = 0;
  DEGHitsCollection*   DEGHC   = 0;
  if (HCE) {
    TESHC  = (TESHitsCollection*)   (HCE->GetHC(TESHCID));
    TGHC   = (TGHitsCollection*)    (HCE->GetHC(TGHCID));
    DEGHC  = (DEGHitsCollection*)   (HCE->GetHC(DEGHCID));
  }

  if (TGHC)   ntg    = TGHC->entries();
  if (DEGHC)  ndeg   = DEGHC->entries();
  if (TESHC)  ntes   = TESHC->entries();
  
  // number of hit detectors
  if (ntes>TESMultiMax || ntg>TGMultiMax || ndeg>DEGMultiMax) {
    G4cout << "Too much number of hits !" << G4endl;
    G4cout << " TES " << ntes << G4endl;
    G4cout << " Target " << ntg << G4endl;
    G4cout << " Degrader " << ndeg << G4endl;
    return;
  }
  
  // TG
  G4bool TGStatus = false;
  for (G4int i=0; i<ntg; i++) {
    tg_pdg[i]      = (*TGHC)[i] -> GetPDGcode();
    tg_track[i]    = (*TGHC)[i] -> GetTrackID();
    tg_status[i]   = (*TGHC)[i] -> GetStatus();
    tg_proc[i]     = (*TGHC)[i] -> GetProcessID();
    tg_parent[i]   = (*TGHC)[i] -> GetParentID();
    tg_cproc[i]    = (*TGHC)[i] -> GetcProcessID();
    tg_edep[i]     = (*TGHC)[i] -> GetEdep();
    tg_trackl[i]   = (*TGHC)[i] -> GetTrackl();
    tg_chid[i]     = (*TGHC)[i] -> GetAbsID();
    tg_hittime[i]  = (*TGHC)[i] -> GetHitTime();
    tg_hitpos[i]   = (*TGHC)[i] -> GetHitPos();
    tg_hitmom[i]   = (*TGHC)[i] -> GetHitMom();
    tg_lasttime[i] = (*TGHC)[i] -> GetLastTime();
    tg_lastpos[i]  = (*TGHC)[i] -> GetLastPos();
    tg_lastmom[i]  = (*TGHC)[i] -> GetLastMom();
    tg_verpos[i]   = (*TGHC)[i] -> GetVertexPos();
    tg_vermomd[i]  = (*TGHC)[i] -> GetVertexMomd();
    tg_verkene[i]  = (*TGHC)[i] -> GetVertexKene();
    tg_verlvid[i]  = (*TGHC)[i] -> GetVertexLvid();
    TGStatus = true;
  }

  // DEG
  G4bool DEGStatus = false;
  for (G4int i=0; i<ndeg; i++) {
    deg_pdg[i]      = (*DEGHC)[i] -> GetPDGcode();
    deg_track[i]    = (*DEGHC)[i] -> GetTrackID();
    deg_status[i]   = (*DEGHC)[i] -> GetStatus();
    deg_proc[i]     = (*DEGHC)[i] -> GetProcessID();
    deg_parent[i]   = (*DEGHC)[i] -> GetParentID();
    deg_cproc[i]    = (*DEGHC)[i] -> GetcProcessID();
    deg_edep[i]     = (*DEGHC)[i] -> GetEdep();
    deg_trackl[i]   = (*DEGHC)[i] -> GetTrackl();
    deg_chid[i]     = (*DEGHC)[i] -> GetAbsID();
    deg_hittime[i]  = (*DEGHC)[i] -> GetHitTime();
    deg_hitpos[i]   = (*DEGHC)[i] -> GetHitPos();
    deg_hitmom[i]   = (*DEGHC)[i] -> GetHitMom();
    deg_lasttime[i] = (*DEGHC)[i] -> GetLastTime();
    deg_lastpos[i]  = (*DEGHC)[i] -> GetLastPos();
    deg_lastmom[i]  = (*DEGHC)[i] -> GetLastMom();
    deg_verpos[i]   = (*DEGHC)[i] -> GetVertexPos();
    deg_vermomd[i]  = (*DEGHC)[i] -> GetVertexMomd();
    deg_verkene[i]  = (*DEGHC)[i] -> GetVertexKene();
    deg_verlvid[i]  = (*DEGHC)[i] -> GetVertexLvid();
    DEGStatus = true;
  }
  
  // TES
  G4bool TESStatus = false;
  for (G4int i=0; i<ntes; i++) {
   tes_pdg[i]      = (*TESHC)[i] -> GetPDGcode();
   tes_track[i]    = (*TESHC)[i] -> GetTrackID();
   tes_status[i]   = (*TESHC)[i] -> GetStatus();
   tes_proc[i]     = (*TESHC)[i] -> GetProcessID();
   tes_parent[i]   = (*TESHC)[i] -> GetParentID();
   tes_cproc[i]    = (*TESHC)[i] -> GetcProcessID();
   tes_edep[i]     = (*TESHC)[i] -> GetEdep();
   tes_trackl[i]   = (*TESHC)[i] -> GetTrackl();
   tes_chid[i]     = (*TESHC)[i] -> GetAbsID();
   tes_hittime[i]  = (*TESHC)[i] -> GetHitTime();
   tes_hitpos[i]   = (*TESHC)[i] -> GetHitPos();
   tes_hitmom[i]   = (*TESHC)[i] -> GetHitMom();
   tes_lasttime[i] = (*TESHC)[i] -> GetLastTime();
   tes_lastpos[i]  = (*TESHC)[i] -> GetLastPos();
   tes_lastmom[i]  = (*TESHC)[i] -> GetLastMom();
   tes_verpos[i]   = (*TESHC)[i] -> GetVertexPos();
   tes_vermomd[i]  = (*TESHC)[i] -> GetVertexMomd();
   tes_verkene[i]  = (*TESHC)[i] -> GetVertexKene();
   tes_verlvid[i]  = (*TESHC)[i] -> GetVertexLvid();
   TESStatus = true;
  }

  
  tree->Fill();// fill everything
  //if (TESStatus || DEGStatus) tree->Fill();// fill only hits on TES or SDD

  if (evtNb==NEVTBP-1) {
    rootfile->Write();
    rootfile->Close("R");
  }
  
  return;

  /*
  /////////////////////////////////////////////////////////////////////////
  // extract the trajectories and draw them
  
  // You can get a default drawing without this code by using, e.g.,
  // /vis/scene/add/trajectories 1000
  // The code here adds sophistication under control of drawFlag.
  
  // See comments in G4VTrajectory::DrawTrajectory for the
  // interpretation of the argument, 1000.
  
  G4VVisManager* pVisManager = G4VVisManager::GetConcreteInstance();
  if (pVisManager)
    {
      G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
      G4int n_trajectories = 0;
      if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
      
      for (G4int i=0; i<n_trajectories; i++) 
	{ G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
	  if (drawFlag == "all") pVisManager->Draw(*trj,1000);
	  else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
	    pVisManager->Draw(*trj,1000);
	  else if ((drawFlag == "neutral")&&(trj->GetCharge() == 0.))
	    pVisManager->Draw(*trj,1000);
	}
    }
  */
  

}




