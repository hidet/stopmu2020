#ifndef TESHit_h
#define TESHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;
class TESHit : public G4VHit
{
public:
  TESHit();
  TESHit(G4LogicalVolume* logVol, G4int absNo);
  TESHit(const TESHit &right);
  ~TESHit();
  const TESHit& operator=(const TESHit &right);
  G4int operator==(const TESHit &right) const;
  
  inline void *operator new(size_t);
  inline void  operator delete(void *aHit);
  
  void Draw();
  const std::map<G4String,G4AttDef>* GetAttDefs() const;
  std::vector<G4AttValue>* CreateAttValues() const;
  void Print();
  
private:
  G4int AbsID;
  G4int trackID;
  G4int status;
  G4int processID;
  G4int cprocessID;
  G4int parentID;
  G4int PDGcode;
  G4double edep;
  G4double trackl;
  G4double hittime;
  G4double lasttime;
  G4ThreeVector hitmom;
  G4ThreeVector hitpos;
  G4ThreeVector lastmom;
  G4ThreeVector lastpos;
  G4ThreeVector vpos;
  G4ThreeVector vmomd;
  G4double vkene;
  G4int    vlvid;
  
  G4RotationMatrix rot;
  const G4LogicalVolume* pLogV;
  static std::map<G4String,G4AttDef> fAttDefs;
  
public:
  inline void SetDetectorID(G4int absNo)       {AbsID = absNo;}
  inline void SetTrackID(G4int tid)            {trackID = tid;}
  inline void SetStatus(G4int sta)             {status = sta;}
  inline void SetProcessID(G4int procid)       {processID = procid;}
  inline void SetcProcessID(G4int cprocid)     {cprocessID = cprocid;}
  inline void SetParentID(G4int pid)           {parentID = pid;}
  inline void SetPDGcode(G4int pdg)            {PDGcode = pdg;} 
  inline void SetEdep(G4double de)             {edep = de;}
  inline void AddEdep(G4double de)             {edep += de;}
  inline void SetTrackl(G4double tl)           {trackl = tl;}
  inline void AddTrackl(G4double tl)           {trackl += tl;}
  inline void SetHitTime(G4double t)           {hittime = t;}
  inline void SetHitMom(G4ThreeVector p)       {hitmom = p;}
  inline void SetHitPos(G4ThreeVector xyz)     {hitpos = xyz;}
  inline void SetLastTime(G4double t)          {lasttime = t;}
  inline void SetLastMom(G4ThreeVector p)      {lastmom = p;}
  inline void SetLastPos(G4ThreeVector xyz)    {lastpos = xyz;}
  inline void SetVertexPos(G4ThreeVector vp)   {vpos = vp;}
  inline void SetVertexMomd(G4ThreeVector vmd) {vmomd = vmd;}
  inline void SetVertexKene(G4double vk)       {vkene = vk;}
  inline void SetVertexLvid(G4int    vn)       {vlvid = vn;}
  
  inline G4int GetAbsID()                   {return AbsID;}
  inline G4int GetTrackID()                 {return trackID;}
  inline G4int GetStatus()                  {return status;}
  inline G4int GetProcessID()               {return processID;}
  inline G4int GetcProcessID()              {return cprocessID;}
  inline G4int GetParentID()                {return parentID;}
  inline G4int GetPDGcode()                 {return PDGcode;} 
  inline G4double GetEdep()                 {return edep;}
  inline G4double GetTrackl()               {return trackl;}
  inline G4double GetHitTime()              {return hittime;}
  inline G4ThreeVector GetHitMom()          {return hitmom;}
  inline G4ThreeVector GetHitPos()          {return hitpos;}
  inline G4double GetLastTime()             {return lasttime;}
  inline G4ThreeVector GetLastMom()         {return lastmom;}
  inline G4ThreeVector GetLastPos()         {return lastpos;}
  inline G4ThreeVector GetVertexPos()       {return vpos;}
  inline G4ThreeVector GetVertexMomd()      {return vmomd;}
  inline G4double GetVertexKene()           {return vkene;}
  inline G4int    GetVertexLvid()           {return vlvid;}

  inline void SetRot(G4RotationMatrix rmat){rot = rmat;}
  inline G4RotationMatrix GetRot()  {return rot;}
  inline const G4LogicalVolume * GetLogV() {return pLogV;}

};

typedef G4THitsCollection<TESHit> TESHitsCollection;

extern G4Allocator<TESHit> TESHitAllocator;

inline void* TESHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)TESHitAllocator.MallocSingle();
  return aHit;
}

inline void TESHit::operator delete(void* aHit)
{
  TESHitAllocator.FreeSingle((TESHit*) aHit);
}

#endif

