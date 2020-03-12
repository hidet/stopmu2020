#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Trajectory.hh"
#include "G4PrimaryParticle.hh"
#include "globals.hh"

#include "Common.h"
#include "AnaManager.hh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

class TFile;
class TTree;
class G4Event;
class AnaManager;
class FileMessenger;
class EventAction : public G4UserEventAction
{
public:
  EventAction(AnaManager* ana);
  ~EventAction();
  
public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  //void PrintPrimary(G4PrimaryParticle* pp,G4int ind);
  //void AddAbs(G4double de, G4double dl) {EnergyAbs += de; TrackLAbs += dl;};
  //void SetDrawFlag   (G4String val)  {drawFlag = val;};
  //void SetPrintModulo(G4int    val)  {printModulo = val;};
  
private:
  FileMessenger *fileMessenger;

  G4String FileName="hoge";
  G4bool   timenow=true;
  
  AnaManager* anam;

  G4int     TESHCID; 
  G4int     TGHCID; 
  G4int     DEGHCID;
  
  //G4String  drawFlag;
  //G4int     printModulo;

  G4int     NEVTBP;
  struct timeval tv1;
  struct timeval tv2;
  struct timeval tv3;
  
  TFile         *rootfile;
  TTree         *tree;
  //TTree         *reac;
  G4int         evid;
  // multiplicity
  G4int         nbeam;
  G4int         ndeg;
  G4int         ntg;
  G4int         ntes;

  G4int         beam_pdg[BeamMultiMax];
  G4int         beam_track[BeamMultiMax];
  G4int         beam_status[BeamMultiMax];  
  G4int         beam_proc[BeamMultiMax];  
  G4ThreeVector beam_hit_pos[BeamMultiMax];
  G4ThreeVector beam_hit_mom[BeamMultiMax];
  G4double      beam_hit_time[BeamMultiMax];  
  G4ThreeVector beam_last_pos[BeamMultiMax];
  G4ThreeVector beam_last_mom[BeamMultiMax];
  G4double      beam_last_time[BeamMultiMax];
  G4int         beam_logvid[BeamMultiMax];
  
  G4int         tg_pdg[TGMultiMax];
  G4int         tg_track[TGMultiMax];
  G4int         tg_status[TGMultiMax];  
  G4int         tg_proc[TGMultiMax];
  G4int         tg_parent[TGMultiMax];
  G4int         tg_cproc[TGMultiMax];
  G4double      tg_edep[TGMultiMax];
  G4double      tg_trackl[TGMultiMax];
  G4int         tg_chid[TGMultiMax];
  G4double      tg_hittime[TGMultiMax];
  G4ThreeVector tg_hitpos[TGMultiMax];
  G4ThreeVector tg_hitmom[TGMultiMax];
  G4double      tg_lasttime[TGMultiMax];
  G4ThreeVector tg_lastpos[TGMultiMax];
  G4ThreeVector tg_lastmom[TGMultiMax];
  G4ThreeVector tg_verpos[TGMultiMax];
  G4ThreeVector tg_vermomd[TGMultiMax];
  G4double      tg_verkene[TGMultiMax];
  G4int         tg_verlvid[TGMultiMax];

  G4int         deg_pdg[DEGMultiMax];
  G4int         deg_track[DEGMultiMax];
  G4int         deg_status[DEGMultiMax];  
  G4int         deg_proc[DEGMultiMax];
  G4int         deg_parent[DEGMultiMax];
  G4int         deg_cproc[DEGMultiMax];
  G4double      deg_edep[DEGMultiMax];
  G4double      deg_trackl[DEGMultiMax];
  G4int         deg_chid[DEGMultiMax];
  G4double      deg_hittime[DEGMultiMax];
  G4ThreeVector deg_hitpos[DEGMultiMax];
  G4ThreeVector deg_hitmom[DEGMultiMax];
  G4double      deg_lasttime[DEGMultiMax];
  G4ThreeVector deg_lastpos[DEGMultiMax];
  G4ThreeVector deg_lastmom[DEGMultiMax];
  G4ThreeVector deg_verpos[DEGMultiMax];
  G4ThreeVector deg_vermomd[DEGMultiMax];
  G4double      deg_verkene[DEGMultiMax];
  G4int         deg_verlvid[DEGMultiMax];
  
  G4int         tes_pdg[TESMultiMax];
  G4int         tes_track[TESMultiMax];
  G4int         tes_status[TESMultiMax];  
  G4int         tes_proc[TESMultiMax];
  G4int         tes_parent[TESMultiMax];
  G4int         tes_cproc[TESMultiMax];
  G4double      tes_edep[TESMultiMax];
  G4double      tes_trackl[TESMultiMax];
  //G4int         tes_layid[TESMultiMax];
  //G4int         tes_uniid[TESMultiMax];
  G4int         tes_chid[TESMultiMax];
  G4double      tes_hittime[TESMultiMax];
  G4ThreeVector tes_hitpos[TESMultiMax];
  G4ThreeVector tes_hitmom[TESMultiMax];
  G4double      tes_lasttime[TESMultiMax];
  G4ThreeVector tes_lastpos[TESMultiMax];
  G4ThreeVector tes_lastmom[TESMultiMax];
  G4ThreeVector tes_verpos[TESMultiMax];
  G4ThreeVector tes_vermomd[TESMultiMax];
  G4double      tes_verkene[TESMultiMax];
  G4int         tes_verlvid[TESMultiMax];
  
  
public:
  void SetFileName(G4String fn){FileName=fn;}
  void SetTimeNow(G4bool tn){timenow=tn;}

  inline const G4String get_localtime_str()
  {
    struct tm *local;
    time_t aclock;
    time(&aclock);
    local = localtime(&aclock);
    G4String localtime_str=Form("%04d%02d%02d%02d%02d%02d",
                                local->tm_year+1900,local->tm_mon+1,local->tm_mday,
                                local->tm_hour,local->tm_min,local->tm_sec);
    return localtime_str;
  }
  
  inline void BookOutputTree(G4String fname="hoge",G4bool tn=true)
  {
    G4String fsave = Form("%s/%s.root",SAVEDIR.data(),fname.data());
    if (tn) fsave = Form("%s/%s_%s.root",SAVEDIR.data(),FileName.data(),get_localtime_str().data());
    G4cout << " ### Saving " << fsave << G4endl;
  
    // --- define root files ---
    rootfile = new TFile(fsave,"NEW","GEANT4 simulation",1);
    tree = new TTree("tree","GEANT4 simulation");
  
    tree->Branch("evid",&evid,"EventID/I");
  
    tree->Branch("nbeam",         &nbeam,         "NBeamPro/I");
    tree->Branch("ndeg",          &ndeg,          "NDEGHit/I");
    tree->Branch("ntg",           &ntg,           "NTargetHit/I");  
    tree->Branch("ntes",          &ntes,          "NTESHit/I");

    tree->Branch("beampdg",       beam_pdg,       Form("BeamPDGcode[%d]/I",BeamMultiMax));  
    tree->Branch("beamtrack",     beam_track,     Form("BeamTrackID[%d]/I",BeamMultiMax));
    tree->Branch("beamstatus",    beam_status,    Form("BeamStatus[%d]/I",BeamMultiMax));
    tree->Branch("beamproc",      beam_proc,      Form("BeamProcessID[%d]/I",BeamMultiMax));
    tree->Branch("beamhittime",   beam_hit_time,  Form("BeamGeneTime[%d]/D",BeamMultiMax));
    tree->Branch("beamhitpos",    beam_hit_pos,   Form("BeamGenePos[%d][3]/D",BeamMultiMax));
    tree->Branch("beamhitmom",    beam_hit_mom,   Form("BeamGeneMom[%d][3]/D",BeamMultiMax));
    tree->Branch("beamlasttime",  beam_last_time, Form("BeamLastTime[%d]/D",BeamMultiMax));
    tree->Branch("beamlastpos",   beam_last_pos,  Form("BeamLastPos[%d][3]/D",BeamMultiMax));
    tree->Branch("beamlastmom",   beam_last_mom,  Form("BeamLastMom[%d][3]/D",BeamMultiMax));
    tree->Branch("beamlogvid",    beam_logvid,    Form("BeamLogVID[%d]/I",BeamMultiMax));  

    tree->Branch("degpdg",      deg_pdg,      Form("DEGPDGcode[%d]/I",DEGMultiMax));
    tree->Branch("degtrack",    deg_track,    Form("DEGTrackID[%d]/I",DEGMultiMax));
    tree->Branch("degstatus",   deg_status,   Form("DEGStatus[%d]/I",DEGMultiMax));
    tree->Branch("degproc",     deg_proc,     Form("DEGProcessID[%d]/I",DEGMultiMax));
    tree->Branch("degparent",   deg_parent,   Form("DEGParentID[%d]/I",DEGMultiMax));
    tree->Branch("degcproc",    deg_cproc,    Form("DEGcProcessID[%d]/I",DEGMultiMax));
    tree->Branch("degedep",     deg_edep,     Form("DEGEdep[%d]/D",DEGMultiMax));
    tree->Branch("degtrackl",   deg_trackl,   Form("DEGTrackl[%d]/D",DEGMultiMax));
    tree->Branch("degchid",     deg_chid,     Form("DEGChannelID[%d]/I",DEGMultiMax));
    tree->Branch("deghittime",  deg_hittime,  Form("DEGHitTime[%d]/D",DEGMultiMax));
    tree->Branch("deghitpos",   deg_hitpos,   Form("DEGHitPos[%d][3]/D",DEGMultiMax));
    tree->Branch("deghitmom",   deg_hitmom,   Form("DEGHitMom[%d][3]/D",DEGMultiMax));
    tree->Branch("deglasttime", deg_lasttime, Form("DEGLastTime[%d]/D",DEGMultiMax));
    tree->Branch("deglastpos",  deg_lastpos,  Form("DEGLastPos[%d][3]/D",DEGMultiMax));
    tree->Branch("deglastmom",  deg_lastmom,  Form("DEGLastMom[%d][3]/D",DEGMultiMax));
    tree->Branch("degverpos",   deg_verpos,   Form("DEGVertexPos[%d][3]/D",DEGMultiMax));
    tree->Branch("degvermomd",  deg_vermomd,  Form("DEGVertexMomd[%d][3]/D",DEGMultiMax));
    tree->Branch("degverkene",  deg_verkene,  Form("DEGVertexKene[%d]/D",DEGMultiMax));
    tree->Branch("degverlvid",  deg_verlvid,  Form("DEGVertexLvid[%d]/I",DEGMultiMax));
  
    tree->Branch("tgpdg",      tg_pdg,      Form("TGPDGcode[%d]/I",TGMultiMax));
    tree->Branch("tgtrack",    tg_track,    Form("TGTrackID[%d]/I",TGMultiMax));
    tree->Branch("tgstatus",   tg_status,   Form("TGStatus[%d]/I",TGMultiMax));
    tree->Branch("tgproc",     tg_proc,     Form("TGProcessID[%d]/I",TGMultiMax));
    tree->Branch("tgparent",   tg_parent,   Form("TGParentID[%d]/I",TGMultiMax));
    tree->Branch("tgcproc",    tg_cproc,    Form("TGcProcessID[%d]/I",TGMultiMax));
    tree->Branch("tgedep",     tg_edep,     Form("TGEdep[%d]/D",TGMultiMax));
    tree->Branch("tgtrackl",   tg_trackl,   Form("TGTrackl[%d]/D",TGMultiMax));
    tree->Branch("tgchid",     tg_chid,     Form("TGChannelID[%d]/I",TGMultiMax));
    tree->Branch("tghittime",  tg_hittime,  Form("TGHitTime[%d]/D",TGMultiMax));
    tree->Branch("tghitpos",   tg_hitpos,   Form("TGHitPos[%d][3]/D",TGMultiMax));
    tree->Branch("tghitmom",   tg_hitmom,   Form("TGHitMom[%d][3]/D",TGMultiMax));
    tree->Branch("tglasttime", tg_lasttime, Form("TGLastTime[%d]/D",TGMultiMax));
    tree->Branch("tglastpos",  tg_lastpos,  Form("TGLastPos[%d][3]/D",TGMultiMax));
    tree->Branch("tglastmom",  tg_lastmom,  Form("TGLastMom[%d][3]/D",TGMultiMax));
    tree->Branch("tgverpos",   tg_verpos,   Form("TGVertexPos[%d][3]/D",TGMultiMax));
    tree->Branch("tgvermomd",  tg_vermomd,  Form("TGVertexMomd[%d][3]/D",TGMultiMax));
    tree->Branch("tgverkene",  tg_verkene,  Form("TGVertexKene[%d]/D",TGMultiMax));
    tree->Branch("tgverlvid",  tg_verlvid,  Form("TGVertexLvid[%d]/I",TGMultiMax));

    tree->Branch("tespdg",      tes_pdg,      Form("TESPDGcode[%d]/I",TESMultiMax));
    tree->Branch("testrack",    tes_track,    Form("TESTrackID[%d]/I",TESMultiMax));
    tree->Branch("tesstatus",   tes_status,   Form("TESStatus[%d]/I",TESMultiMax));
    tree->Branch("tesproc",     tes_proc,     Form("TESProcessID[%d]/I",TESMultiMax));
    tree->Branch("tesparent",   tes_parent,   Form("TESParentID[%d]/I",TESMultiMax));
    tree->Branch("tescproc",    tes_cproc,    Form("TEScProcessID[%d]/I",TESMultiMax));
    tree->Branch("tesedep",     tes_edep,     Form("TESEdep[%d]/D",TESMultiMax));
    tree->Branch("testrackl",   tes_trackl,   Form("TESTrackl[%d]/D",TESMultiMax));
    tree->Branch("teschid",     tes_chid,     Form("TESChannelID[%d]/I",TESMultiMax));
    tree->Branch("teshittime",  tes_hittime,  Form("TESHitTime[%d]/D",TESMultiMax));
    tree->Branch("teshitpos",   tes_hitpos,   Form("TESHitPos[%d][3]/D",TESMultiMax));
    tree->Branch("teshitmom",   tes_hitmom,   Form("TESHitMom[%d][3]/D",TESMultiMax));
    tree->Branch("teslasttime", tes_lasttime, Form("TESLastTime[%d]/D",TESMultiMax));
    tree->Branch("teslastpos",  tes_lastpos,  Form("TESLastPos[%d][3]/D",TESMultiMax));
    tree->Branch("teslastmom",  tes_lastmom,  Form("TESLastMom[%d][3]/D",TESMultiMax));
    tree->Branch("tesverpos",   tes_verpos,   Form("TESVertexPos[%d][3]/D",TESMultiMax));
    tree->Branch("tesvermomd",  tes_vermomd,  Form("TESVertexMomd[%d][3]/D",TESMultiMax));
    tree->Branch("tesverkene",  tes_verkene,  Form("TESVertexKene[%d]/D",TESMultiMax));
    tree->Branch("tesverlvid",  tes_verlvid,  Form("TESVertexLvid[%d]/I",TESMultiMax));
  }
  
  inline void InitializeTree(G4int ev=0) {
    evid=ev;
    nbeam=0;
    ndeg=0;
    ntg=0;
    ntes=0;
    for (G4int i=0; i<BeamMultiMax; i++) {
      beam_pdg[i]           = -999;    
      beam_track[i]         = -999;    
      beam_status[i]        = -999;    
      beam_proc[i]          = -999;
      beam_hit_pos[i].set(-999.,-999.,-999.);
      beam_hit_mom[i].set(-999.,-999.,-999.);
      beam_hit_time[i]      = -999.;    
      beam_last_pos[i].set(-999.,-999.,-999.);
      beam_last_mom[i].set(-999.,-999.,-999.);
      beam_last_time[i]     = -999.;
      beam_logvid[i]        = -999;    
    }
    for (G4int i=0; i<TGMultiMax; i++){
      tg_pdg[i]         = -999;
      tg_track[i]       = -999;
      tg_status[i]      = -999;
      tg_proc[i]        = -999;
      tg_parent[i]      = -999;
      tg_cproc[i]       = -999;
      tg_edep[i]        = -999.;
      tg_trackl[i]      = -999.;
      tg_chid[i]        = -1;
      tg_hittime[i]     = -999.;
      tg_hitpos[i].set(-999.,-999.,-999.);
      tg_hitmom[i].set(-999.,-999.,-999.);
      tg_lasttime[i]    = -999.;
      tg_lastpos[i].set(-999.,-999.,-999.);
      tg_lastmom[i].set(-999.,-999.,-999.);
      tg_verpos[i].set(-999.,-999.,-999.);
      tg_vermomd[i].set(-999.,-999.,-999.);
      tg_verkene[i]     = -999.;
      tg_verlvid[i]     = -1;
    }
    for (G4int i=0; i<DEGMultiMax; i++){
      deg_pdg[i]        = -999;
      deg_track[i]      = -999;
      deg_status[i]     = -999;
      deg_proc[i]       = -999;
      deg_parent[i]     = -999;
      deg_cproc[i]      = -999;
      deg_edep[i]       = -999.;
      deg_trackl[i]     = -999.;
      deg_chid[i]       = -1;
      deg_hittime[i]    = -999.;
      deg_hitpos[i].set(-999.,-999.,-999.);
      deg_hitmom[i].set(-999.,-999.,-999.);
      deg_lasttime[i]   = -999.;
      deg_lastpos[i].set(-999.,-999.,-999.);
      deg_lastmom[i].set(-999.,-999.,-999.);
      deg_verpos[i].set(-999.,-999.,-999.);
      deg_vermomd[i].set(-999.,-999.,-999.);
      deg_verkene[i]    = -999.;
      deg_verlvid[i]    = -1;
    }  
    for (G4int i=0; i<TESMultiMax; i++){
      tes_pdg[i]        = -999;
      tes_track[i]      = -999;
      tes_status[i]     = -999;
      tes_proc[i]       = -999;
      tes_parent[i]     = -999;
      tes_cproc[i]      = -999;
      tes_edep[i]       = -999.;
      tes_trackl[i]     = -999.;
      tes_chid[i]       = -1;
      tes_hittime[i]    = -999.;
      tes_hitpos[i].set(-999.,-999.,-999.);
      tes_hitmom[i].set(-999.,-999.,-999.);
      tes_lasttime[i]   = -999.;
      tes_lastpos[i].set(-999.,-999.,-999.);
      tes_lastmom[i].set(-999.,-999.,-999.);
      tes_verpos[i].set(-999.,-999.,-999.);
      tes_vermomd[i].set(-999.,-999.,-999.);
      tes_verkene[i]    = -999.;
      tes_verlvid[i]    = -1;
    }
  }
  
  inline void PrintEventNumber(G4int evtNb,G4int totalev,struct timeval tvl1,
                               struct timeval tvl2,struct timeval tvl3)
  {
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
    timerclear(&tvl2);
    timerclear(&tvl3);
    gettimeofday(&tvl2, NULL);
    timerclear(&tvl3);
    timersub(&tvl2, &tvl1, &tvl3);
    G4double tdiff = (G4double)tvl3.tv_sec + (G4double)tvl3.tv_usec/1e6;
    G4double totalt = tdiff/(G4double)evtNb * (G4double)totalev;
    G4double remaint = totalt-tdiff;
    if (remaint>3600.) {
      G4cout << "Now " << tdiff/60. << " min, need more " 
	     << remaint/3600. << " h. " << (G4double)evtNb/(G4double)totalev*100. 
	     << " % of " << totalev << " events" << G4endl;
    } else if (remaint>120.) {
      G4cout << "Now " << tdiff/60. << " min, need more " 
	     << remaint/60. << " min. " << (G4double)evtNb/(G4double)totalev*100. 
	     << " % of " << totalev << " events" << G4endl;
    } else {
      G4cout << "Now " << tdiff/60. << " min, need more " 
	     << remaint << " sec. " << (G4double)evtNb/(G4double)totalev*100. 
	     << " % of " << totalev << " events" << G4endl;
    }
  }
  //public:
  //inline void SetVerbose(G4int val) { verboseLevel = val; }
  //inline G4int GetVerbose() const { return verboseLevel; }
};


#endif
