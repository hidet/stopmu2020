#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

#include "Common.h"
#include "AnaManager.hh"
#include "Materials.hh"

class G4Box;
class G4Para;
class G4Tubs;
class G4Cons;
class G4Trd;
class G4Trap;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PVPlacement;
class G4SubtractionSolid;
class G4UnionSolid;
class G4EllipticalTube;
class G4UniformMagField;
class G4Material;
//class FieldSetup;
class Materials;
class DetectorMessenger;
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  DetectorConstruction(Materials *Mat);
  ~DetectorConstruction();

public:
  virtual
  G4VPhysicalVolume* Construct();

private:
  G4VPhysicalVolume* ConstructVolumes();
  void CheckOverlaps();

public:
  G4bool SetTargetMaterial(G4String material);
  void SetTargetDensity(G4double density);
  //void UpdateGeometry();

  G4int GetDetectorID(G4String det)
  {
    G4int lvid=-9999;
    if (det=="world_log")                 lvid =  0;             
    else if (det=="air_log")              lvid =  1;
    else if (det=="aw_log")               lvid = 10;
    else if (det=="bw_log")               lvid = 11;
    else if (det=="target_log")           lvid = 20;
    else if (det=="targetside1_log")      lvid = 21;
    else if (det=="targetside2_log")      lvid = 22;
    else if (det=="targetside3_log")      lvid = 23;
    else if (det=="targetside4_log")      lvid = 24;
    else if (det=="targetend_log")        lvid = 25;
    else if (det.contains("calo_log_"))   lvid = 30;
    else if (det=="sdd_log")              lvid = 31;
    else if (det=="snout300k_log")        lvid = 40;
    else if (det=="snout300kside_log")    lvid = 41;
    else if (det=="snout300kwnd_log")     lvid = 42;
    else if (det=="snout60k_log")         lvid = 43;
    else if (det=="snout60kwnd_log")      lvid = 44;
    else if (det=="snout3k_log")          lvid = 45;
    else if (det=="snout3kwnd_log")       lvid = 46;
    else if (det=="snout_log")            lvid = 47;
    else if (det=="snoutwnd_log")         lvid = 48;
    return lvid;
  }
  
private:
  DetectorMessenger* detectorMessenger;
  Materials *mat;
  G4Material *targetMat;
  
  //G4UniformMagField* magField;

  // world
  G4Box*             world_box; 
  G4LogicalVolume*   world_log;
  G4String           world_log_name;
  G4VPhysicalVolume* world_phys;
  // target
  G4Tubs*            target_tube; 
  G4LogicalVolume*   target_log;
  G4VPhysicalVolume* target_phys;
  // targetside1
  G4Tubs*            targetside1_tube; 
  G4LogicalVolume*   targetside1_log;
  G4VPhysicalVolume* targetside1_phys;
  // targetside2
  G4Tubs*            targetside2_tube; 
  G4LogicalVolume*   targetside2_log;
  G4VPhysicalVolume* targetside2_phys;
  // targetside3
  G4Tubs*            targetside3_tube; 
  G4LogicalVolume*   targetside3_log;
  G4VPhysicalVolume* targetside3_phys;
  // targetside4
  G4Tubs*            targetside4_tube; 
  G4LogicalVolume*   targetside4_log;
  G4VPhysicalVolume* targetside4_phys;
  // targetend
  G4Tubs*            targetend_tube; 
  G4LogicalVolume*   targetend_log;
  G4VPhysicalVolume* targetend_phys;
  // accelerator window
  G4Tubs*            aw_tube; 
  G4LogicalVolume*   aw_log;
  G4VPhysicalVolume* aw_phys;
  // Air
  G4Tubs*            air_tube; 
  G4LogicalVolume*   air_log;
  G4VPhysicalVolume* air_phys;
  // beam window
  G4Tubs*            bw_tube; 
  G4LogicalVolume*   bw_log;
  G4VPhysicalVolume* bw_phys;
  // SDD
  G4Box*             sdd_box; 
  G4LogicalVolume*   sdd_log;
  G4VPhysicalVolume* sdd_phys;
  // SDD Window Be
  G4Tubs*            sddwnd_tube; 
  G4LogicalVolume*   sddwnd_log;
  G4VPhysicalVolume* sddwnd_phys;
  // SDD Window SUS
  G4Tubs*            sddwndsus_tube; 
  G4LogicalVolume*   sddwndsus_log;
  G4VPhysicalVolume* sddwndsus_phys;
  // TES
  G4Box*             calo_box; 
  G4LogicalVolume*   calo_log[NbOfTES];
  G4VPhysicalVolume* calo_phys[NbOfTES];
  // Collimator1 (Si)
  G4Box*             dummy_box;
  G4Box*             coli1_box;
  G4VSolid*          coli1_sub;
  G4LogicalVolume*   coli1_sub_log;
  G4VPhysicalVolume* coli1_sub_phys;
  // Collimator2 (Au)
  G4Box*             coli2_box;
  G4VSolid*          coli2_sub;
  G4LogicalVolume*   coli2_sub_log;
  G4VPhysicalVolume* coli2_sub_phys;
  // 50mK
  G4Tubs*            snout_tube; 
  G4LogicalVolume*   snout_log;
  G4VPhysicalVolume* snout_phys;
  // 50mK
  G4Tubs*            snoutwnd_tube; 
  G4LogicalVolume*   snoutwnd_log;
  G4VPhysicalVolume* snoutwnd_phys;
  // 3K
  G4Tubs*            snout3k_tube; 
  G4LogicalVolume*   snout3k_log;
  G4VPhysicalVolume* snout3k_phys;
  // 3K
  G4Tubs*            snout3kwnd_tube; 
  G4LogicalVolume*   snout3kwnd_log;
  G4VPhysicalVolume* snout3kwnd_phys;
  // 60K
  G4Tubs*            snout60k_tube; 
  G4LogicalVolume*   snout60k_log;
  G4VPhysicalVolume* snout60k_phys;
  // 60K
  G4Tubs*            snout60kwnd_tube; 
  G4LogicalVolume*   snout60kwnd_log;
  G4VPhysicalVolume* snout60kwnd_phys;
  // 300K
  G4Tubs*            snout300kside_tube; 
  G4LogicalVolume*   snout300kside_log;
  G4VPhysicalVolume* snout300kside_phys;
  // 300K
  G4Tubs*            snout300k_tube; 
  G4LogicalVolume*   snout300k_log;
  G4VPhysicalVolume* snout300k_phys;
  // 300K
  G4Tubs*            snout300kwnd_tube; 
  G4LogicalVolume*   snout300kwnd_log;
  G4VPhysicalVolume* snout300kwnd_phys;

};


#endif
