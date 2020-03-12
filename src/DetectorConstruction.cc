#include "globals.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Para.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4EllipticalTube.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4PVReplica.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VSensitiveDetector.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Color.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "Materials.hh"
#include "TESSD.hh"
#include "TGSD.hh"
#include "DEGSD.hh"
#include "Common.h"

using namespace CLHEP;

DetectorConstruction::DetectorConstruction()
{
  detectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::DetectorConstruction(Materials *Mat)
  :mat(Mat)
{
  targetMat = mat->NeGas;
  detectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
  delete detectorMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // -- sensitive detectors --
  G4SDManager* SDman  = G4SDManager::GetSDMpointer();
  DEGSD* DEG  = new DEGSD("DEG");
  TESSD* TES  = new TESSD("TES");
  TGSD*  TG   = new TGSD("TG");
  SDman->AddNewDetector(DEG);
  SDman->AddNewDetector(TES);
  SDman->AddNewDetector(TG);

  // beam line along z axis
  G4RotationMatrix* rot0 = new G4RotationMatrix();
  rot0->rotateY(-twopi/4.);
  //rot0->rotateX(-twopi/8.);

  G4VisAttributes *deg_att = new G4VisAttributes(G4Color (0.9, 0.3, 0.5));
  deg_att->SetForceWireframe(true);
  deg_att->SetVisibility(true);
  G4VisAttributes *target_att = new G4VisAttributes(G4Color (0.2, 0.9, 0.2));
  target_att->SetForceWireframe(true);
  target_att->SetVisibility(true);
  G4VisAttributes *mylar_att = new G4VisAttributes(G4Color (0.9, 0.3, 0.9));
  mylar_att->SetForceWireframe(true);
  mylar_att->SetVisibility(true);
  G4VisAttributes *sus_att = new G4VisAttributes(G4Color (0.5, 0.5, 0.4));
  sus_att->SetForceWireframe(true);
  sus_att->SetVisibility(true);
  G4VisAttributes *al_att = new G4VisAttributes(G4Color (0.3, 0.3, 0.3));
  al_att->SetForceWireframe(true);
  al_att->SetVisibility(true);

  //-----------  VOLUME  ----------------------
  // world (Vacuum)
  world_box = new G4Box("world_box",world_size[0],world_size[1],world_size[2]);
  world_log = new G4LogicalVolume(world_box,
                                  mat->Vacuum,
                                  "world_log",0,0,0);
  world_phys = new G4PVPlacement(0,
                                 G4ThreeVector(),
                                 world_log,"world",0,false,0);
  world_log->SetVisAttributes(G4VisAttributes::Invisible);

  // accelerator window (Kapton)
  aw_tube = new G4Tubs("aw_tube",aw_rmin,aw_rmax,aw_z/2.,0.0,twopi);
  aw_log  = new G4LogicalVolume(aw_tube,
                                mat->Kapton,
                                "aw_log",0,0,0);
  aw_phys = new G4PVPlacement(0,
                              G4ThreeVector(aw_pos[0],aw_pos[1],aw_pos[2]),
                              aw_log,"aw",world_log,false,0);
  aw_log->SetVisAttributes(deg_att);  
  
  // Air
  air_tube = new G4Tubs("air_tube",air_rmin,air_rmax,air_z/2.,0.0,twopi);
  air_log  = new G4LogicalVolume(air_tube,
                                 mat->Air,
                                 "air_log",0,0,0);
  air_phys = new G4PVPlacement(0,
                               G4ThreeVector(air_pos[0],air_pos[1],air_pos[2]),
                               air_log,"air",world_log,false,0);
  air_log->SetVisAttributes(mylar_att);  

  // beam window (Kapton)
  bw_tube = new G4Tubs("bw_tube",bw_rmin,bw_rmax,bw_z/2.,0.0,twopi);
  bw_log  = new G4LogicalVolume(bw_tube,
                                mat->Kapton,
                                "bw_log",0,0,0);
  bw_phys = new G4PVPlacement(0,
                              G4ThreeVector(bw_pos[0],bw_pos[1],bw_pos[2]),
                              bw_log,"bw",world_log,false,0);
  bw_log->SetVisAttributes(deg_att);  
  //bw_log->SetSensitiveDetector(DEG);

  // target (Ne gas)
  target_tube = new G4Tubs("target_tube",target_rmin,target_rmax,target_z/2.,0.0,twopi);
  target_log  = new G4LogicalVolume(target_tube,
                                    targetMat,
                                    "target_log",0,0,0);
  target_phys = new G4PVPlacement(0,
                                  G4ThreeVector(target_pos[0],target_pos[1],target_pos[2]),
                                  target_log,"target",world_log,false,0);
  target_log->SetVisAttributes(target_att);  
  target_log->SetSensitiveDetector(TG);

  // target side1 (SUS)
  targetside1_tube = new G4Tubs("targetside1_tube",targetside1_rmin,targetside1_rmax,targetside1_z/2.,0.0,twopi);
  targetside1_log  = new G4LogicalVolume(targetside1_tube,
                                        mat->SUS,
                                        "targetside1_log",0,0,0);
  targetside1_phys = new G4PVPlacement(0,
                                      G4ThreeVector(targetside1_pos[0],targetside1_pos[1],targetside1_pos[2]),
                                      targetside1_log,"targetside1",world_log,false,0);
  targetside1_log->SetVisAttributes(sus_att);
  // target side2 (SUS)
  targetside2_tube = new G4Tubs("targetside2_tube",targetside2_rmin,targetside2_rmax,targetside2_z/2.,0.0,twopi);
  targetside2_log  = new G4LogicalVolume(targetside2_tube,
                                        mat->SUS,
                                        "targetside2_log",0,0,0);
  targetside2_phys = new G4PVPlacement(0,
                                      G4ThreeVector(targetside2_pos[0],targetside2_pos[1],targetside2_pos[2]),
                                      targetside2_log,"targetside2",world_log,false,0);
  targetside2_log->SetVisAttributes(sus_att);
  // target side3 (SUS)
  //targetside3_tube = new G4Tubs("targetside3_tube",targetside3_rmin,targetside3_rmax,targetside3_z/2.,twopi/8.,twopi/8.*6.);
  targetside3_tube = new G4Tubs("targetside3_tube",targetside3_rmin,targetside3_rmax,targetside3_z/2.,twopi/8.,twopi/8.*2.);
  targetside3_log  = new G4LogicalVolume(targetside3_tube,
                                        mat->SUS,
                                        "targetside3_log",0,0,0);
  targetside3_phys = new G4PVPlacement(0,
                                      G4ThreeVector(targetside3_pos[0],targetside3_pos[1],targetside3_pos[2]),
                                      targetside3_log,"targetside3",world_log,false,0);
  targetside3_log->SetVisAttributes(sus_att);
  
  targetside4_tube = new G4Tubs("targetside4_tube",targetside3_rmin,targetside3_rmax,targetside3_z/2.,twopi*5./8.,twopi/8.*2.);
  targetside4_log  = new G4LogicalVolume(targetside4_tube,
                                         mat->SUS,
                                         "targetside4_log",0,0,0);
  targetside4_phys = new G4PVPlacement(0,
                                       G4ThreeVector(targetside3_pos[0],targetside3_pos[1],targetside3_pos[2]),
                                       targetside4_log,"targetside4",world_log,false,0);
  targetside4_log->SetVisAttributes(sus_att);
  // target end (SUS)
  targetend_tube = new G4Tubs("targetend_tube",targetend_rmin,targetend_rmax,targetend_z/2.,0.0,twopi);
  targetend_log  = new G4LogicalVolume(targetend_tube,
                                       mat->SUS,
                                       "targetend_log",0,0,0);
  targetend_phys = new G4PVPlacement(0,
                                     G4ThreeVector(targetend_pos[0],targetend_pos[1],targetend_pos[2]),
                                     targetend_log,"targetend",world_log,false,0);
  targetend_log->SetVisAttributes(sus_att);  
  

  // snout 300K (SUS)
  snout300k_tube = new G4Tubs("snout300k_tube",snout300k_rmin,snout300k_rmax,snout300k_z/2.,0.0,twopi);
  snout300k_log = new G4LogicalVolume(snout300k_tube,
                                      mat->SUS,
                                      "snout300k_log",0,0,0);
  snout300k_phys = new G4PVPlacement(rot0,
                                     G4ThreeVector(snout300k_pos[0],snout300k_pos[1],snout300k_pos[2]),
                                     snout300k_log, "snout300k", world_log, false,0);
  snout300k_log->SetVisAttributes(sus_att);
  // snout 300K (SUS)
  snout300kside_tube = new G4Tubs("snout300kside_tube",snout300kside_rmin,snout300kside_rmax,snout300kside_z/2.,0.0,twopi);
  snout300kside_log = new G4LogicalVolume(snout300kside_tube,
                                          mat->SUS,
                                          "snout300kside_log",0,0,0);
  snout300kside_phys = new G4PVPlacement(rot0,
                                         G4ThreeVector(snout300kside_pos[0],snout300kside_pos[1],snout300kside_pos[2]),
                                         snout300kside_log, "snout300kside", world_log, false,0);
  snout300kside_log->SetVisAttributes(sus_att);    
  // snout 300K wnd (Be)
  snout300kwnd_tube = new G4Tubs("snout300kwnd_tube",snout300kwnd_rmin,snout300kwnd_rmax,snout300kwnd_z/2.,0.0,twopi);
  snout300kwnd_log = new G4LogicalVolume(snout300kwnd_tube,
                                         mat->Be,
                                         "snout300kwnd_log",0,0,0);
  snout300kwnd_phys = new G4PVPlacement(rot0,
                                        G4ThreeVector(snout300kwnd_pos[0],snout300kwnd_pos[1],snout300kwnd_pos[2]),
                                        snout300kwnd_log, "snout300kwnd", world_log, false,0);
  snout300kwnd_log->SetVisAttributes(mylar_att);
  
  // snout 60K (Al)
  snout60k_tube = new G4Tubs("snout60k_tube",snout60k_rmin,snout60k_rmax,snout60k_z/2.,0.0,twopi);
  snout60k_log = new G4LogicalVolume(snout60k_tube,
                                     mat->Al,
                                     "snout60k_log",0,0,0);
  snout60k_phys = new G4PVPlacement(rot0,
                                    G4ThreeVector(snout60k_pos[0],snout60k_pos[1],snout60k_pos[2]),
                                    snout60k_log, "snout60k", world_log, false,0);
  snout60k_log->SetVisAttributes(al_att);    
  // snout 60K wnd (Mylar)
  snout60kwnd_tube = new G4Tubs("snout60kwnd_tube",snout60kwnd_rmin,snout60kwnd_rmax,snout60kwnd_z/2.,0.0,twopi);
  snout60kwnd_log = new G4LogicalVolume(snout60kwnd_tube,
                                        //mat->Be,
                                        //mat->Mylar,
                                        mat->Al,
                                        "snout60kwnd_log",0,0,0);
  snout60kwnd_phys = new G4PVPlacement(rot0,
                                       G4ThreeVector(snout60kwnd_pos[0],snout60kwnd_pos[1],snout60kwnd_pos[2]),
                                       snout60kwnd_log, "snout60kwnd", world_log, false,0);
  snout60kwnd_log->SetVisAttributes(mylar_att);
  
  // snout 3K (Al)
  snout3k_tube = new G4Tubs("snout3k_tube",snout3k_rmin,snout3k_rmax,snout3k_z/2.,0.0,twopi);
  snout3k_log = new G4LogicalVolume(snout3k_tube,
                                    mat->Al,
                                    "snout3k_log",0,0,0);
  snout3k_phys = new G4PVPlacement(rot0,
                                   G4ThreeVector(snout3k_pos[0],snout3k_pos[1],snout3k_pos[2]),
                                   snout3k_log, "snout3k", world_log, false,0);
  snout3k_log->SetVisAttributes(al_att);    
  // snout 3K wnd (Be)
  snout3kwnd_tube = new G4Tubs("snout3kwnd_tube",snout3kwnd_rmin,snout3kwnd_rmax,snout3kwnd_z/2.,0.0,twopi);
  snout3kwnd_log = new G4LogicalVolume(snout3kwnd_tube,
                                       //mat->Be,
                                       mat->Al,
                                       "snout3kwnd_log",0,0,0);
  snout3kwnd_phys = new G4PVPlacement(rot0,
                                      G4ThreeVector(snout3kwnd_pos[0],snout3kwnd_pos[1],snout3kwnd_pos[2]),
                                      snout3kwnd_log, "snout3kwnd", world_log, false,0);
  snout3kwnd_log->SetVisAttributes(mylar_att);

  // snout 50mK (Al)
  snout_tube = new G4Tubs("snout_tube",snout_rmin,snout_rmax,snout_z/2.,0.0,twopi);
  snout_log = new G4LogicalVolume(snout_tube,
                                  mat->Al,
                                  "snout_log",0,0,0);
  snout_phys = new G4PVPlacement(rot0,
                                 G4ThreeVector(snout_pos[0],snout_pos[1],snout_pos[2]),
                                 snout_log, "snout", world_log, false,0);
  snout_log->SetVisAttributes(al_att);    
  // snout 50mK wnd (Be)
  snoutwnd_tube = new G4Tubs("snoutwnd_tube",snoutwnd_rmin,snoutwnd_rmax,snoutwnd_z/2.,0.0,twopi);
  snoutwnd_log = new G4LogicalVolume(snoutwnd_tube,
                                     //mat->Be,
                                     mat->Al,
                                     "snoutwnd_log",0,0,0);
  snoutwnd_phys = new G4PVPlacement(rot0,
                                    G4ThreeVector(snoutwnd_pos[0],snoutwnd_pos[1],snoutwnd_pos[2]),
                                    snoutwnd_log, "snoutwnd", world_log, false,0);
  snoutwnd_log->SetVisAttributes(mylar_att);
  // sdd (Si)
  sdd_box = new G4Box("sdd_box",sdd_size[0]/2.,sdd_size[1]/2.,sdd_size[2]/2.);
  
  sdd_log = new G4LogicalVolume(sdd_box,
                                mat->Si,
                                "sdd_log",0,0,0);
  sdd_phys = new G4PVPlacement(rot0,
                               G4ThreeVector(sdd_pos[0],sdd_pos[1],sdd_pos[2]),
                               sdd_log, "sdd", world_log, false,0);
  sdd_log->SetVisAttributes(mylar_att);
  sdd_log->SetSensitiveDetector(DEG);
  // sdd wnd (Be)
  sddwnd_tube = new G4Tubs("sddwnd_tube",sddwnd_rmin,sddwnd_rmax,sddwnd_z/2.,0.0,twopi);
  sddwnd_log = new G4LogicalVolume(sddwnd_tube,
                                   mat->Be,
                                   "sddwnd_log",0,0,0);
  sddwnd_phys = new G4PVPlacement(rot0,
                                  G4ThreeVector(sddwnd_pos[0],sddwnd_pos[1],sddwnd_pos[2]),
                                  sddwnd_log, "sddwnd", world_log, false,0);
  sddwnd_log->SetVisAttributes(mylar_att);

  // sdd wnd (SUS)
  sddwndsus_tube = new G4Tubs("sddwndsus_tube",sddwndsus_rmin,sddwndsus_rmax,sddwndsus_z/2.,0.0,twopi);
  sddwndsus_log = new G4LogicalVolume(sddwndsus_tube,
                                      mat->SUS,
                                      "sddwndsus_log",0,0,0);
  sddwndsus_phys = new G4PVPlacement(rot0,
                                     G4ThreeVector(sddwndsus_pos[0],sddwndsus_pos[1],sddwndsus_pos[2]),
                                     sddwndsus_log, "sddwndsus", world_log, false,0);
  sddwndsus_log->SetVisAttributes(sus_att);

  // calo (Bismuth)
  G4VisAttributes *calo_att = new G4VisAttributes(G4Color (0.1, 0.1, 0.9));
  calo_att->SetForceWireframe(true);
  calo_att->SetVisibility(true);
  calo_box = new G4Box("calo_box",calo_size[0]/2.,calo_size[1]/2.,calo_size[2]/2.);
  G4double calo_pos[NbOfTES][3];
  G4String TESNAME[NbOfTES];
  G4double NLTES = sqrt(NbOfTES);// sqrt(196)=14, sqrt(256)=16
  G4double calo_pos_ini[3] = 
    {calo_pos_c[0],
     calo_pos_c[1] - calo_size[0]*45./4.,
     calo_pos_c[2] - calo_size[1]*45./4.
    };
  for (G4int i=0; i<(G4int)NLTES; i++) {
    for (G4int j=0; j<(G4int)NLTES; j++) {
      calo_pos[j + (G4int)NLTES*i][2] = calo_pos_ini[2] + i*(1.5*calo_size[1]);
      calo_pos[j + (G4int)NLTES*i][1] = calo_pos_ini[1] + j*(1.5*calo_size[0]);
    }
  }
  for (G4int i=0; i<NbOfTES; i++) {
    calo_pos[i][0] = calo_pos_ini[0];
    TESNAME[i] = Form("calo_log_%d",i);
    calo_log[i]  = new G4LogicalVolume(calo_box,
                                       mat->Bi,
                                       TESNAME[i],0,0,0);
    calo_phys[i] = new G4PVPlacement(rot0,
                                     G4ThreeVector(calo_pos[i][0],calo_pos[i][1],calo_pos[i][2]),
                                     calo_log[i], "calo", world_log, false,i);
    calo_log[i]->SetVisAttributes(calo_att);  
    calo_log[i]->SetSensitiveDetector(TES);
  }


  // ------------------------------------------------------
  // These collimator codes destrcut the visualization
  // To use the mac/vis.mac, you need to comment out all of collimator sections
  G4double sub_pos[NbOfTES][3];
  for (G4int i=0; i<(G4int)NLTES; i++) {
    for (G4int j=0; j<(G4int)NLTES; j++) {
      sub_pos[j + (G4int)NLTES*i][0] = - calo_size[1]*45./4. + i*(1.5*calo_size[1]);
      sub_pos[j + (G4int)NLTES*i][1] = - calo_size[0]*45./4. + j*(1.5*calo_size[0]);
      sub_pos[j + (G4int)NLTES*i][2] = 0.;
    }
  }
  // collimator1 (Si)
  coli1_box = new G4Box("coli1_box",coli1_size[0]/2.,coli1_size[1]/2.,coli1_size[2]/2.);
  dummy_box = new G4Box("dummy_box",calo_size[0]/2.,calo_size[1]/2.,coli1_size[2]/2.);
  for (G4int i=0; i<NbOfTES; i++) {
    if (i==0) coli1_sub = new G4SubtractionSolid("coli1_sub", coli1_box, dummy_box, 0, G4ThreeVector(sub_pos[i][0],sub_pos[i][1],0.));
    else coli1_sub = new G4SubtractionSolid("coli1_sub", coli1_sub, dummy_box, 0, G4ThreeVector(sub_pos[i][0],sub_pos[i][1],0.));
  }
  coli1_sub_log = new G4LogicalVolume(coli1_sub,
                                      mat->Si,
                                      "coli1_sub_log",0,0,0);
  coli1_sub_phys = new G4PVPlacement(rot0,
                                     G4ThreeVector(coli1_pos[0],coli1_pos[1],coli1_pos[2]),
                                     coli1_sub_log, "coli1_sub", world_log, false,0);
  //coli1_sub_log->SetVisAttributes(sus_att);
  
  // collimator2 (Au)
  coli2_box = new G4Box("coli2_box",coli2_size[0]/2.,coli2_size[1]/2.,coli2_size[2]/2.);
  dummy_box = new G4Box("dummy_box",calo_size[0]/2.,calo_size[1]/2.,coli2_size[2]/2.);
  for (G4int i=0; i<NbOfTES; i++) {
    if (i==0) coli2_sub = new G4SubtractionSolid("coli2_sub", coli2_box, dummy_box, 0, G4ThreeVector(sub_pos[i][0],sub_pos[i][1],0.));
    else coli2_sub = new G4SubtractionSolid("coli2_sub", coli2_sub, dummy_box, 0, G4ThreeVector(sub_pos[i][0],sub_pos[i][1],0.));
  }
  coli2_sub_log = new G4LogicalVolume(coli2_sub,
                                      mat->Au,
                                      "coli2_sub_log",0,0,0);
  coli2_sub_phys = new G4PVPlacement(rot0,
                                     G4ThreeVector(coli2_pos[0],coli2_pos[1],coli2_pos[2]),
                                     coli2_sub_log, "coli2_sub", world_log, false,0);
  //coli2_sub_log->SetVisAttributes(sus_att);
  // ------------------------------------------------------
  
  
  return world_phys;
}


G4bool DetectorConstruction::SetTargetMaterial(G4String material)
{
  // the target material is set by the DetectorMessenger
  // string is used to specify the target
  // the Material object 'mat' and the members should be prepared in include/Material.hh
  if (material=="NeGas")           targetMat = mat->NeGas;
  else if (material=="NeGas1atm")  targetMat = mat->NeGas1atm;
  else if (material=="NeGas05atm") targetMat = mat->NeGas05atm;
  else if (material=="NeGas01atm") targetMat = mat->NeGas01atm;
  else if (material=="NeGas100atm") targetMat = mat->NeGas100atm;
  else if (material=="NeGas090atm") targetMat = mat->NeGas090atm;
  else if (material=="NeGas075atm") targetMat = mat->NeGas075atm;
  else if (material=="NeGas050atm") targetMat = mat->NeGas050atm;
  else if (material=="NeGas040atm") targetMat = mat->NeGas040atm;
  else if (material=="NeGas025atm") targetMat = mat->NeGas025atm;
  else if (material=="NeGas010atm") targetMat = mat->NeGas010atm;
  else if (material=="NeGas001atm") targetMat = mat->NeGas001atm;
  
  else if (material=="ArGas100atm") targetMat = mat->ArGas100atm;
  else if (material=="ArGas050atm") targetMat = mat->ArGas050atm;
  else if (material=="ArGas030atm") targetMat = mat->ArGas030atm;
  else if (material=="ArGas010atm") targetMat = mat->ArGas010atm;
  
  else if (material=="He4Gas") {
    targetMat = mat->He4Gas;
  }
  else if (material=="He3Gas") {
    targetMat = mat->He3Gas;
  }
  else {
    G4cout << "WARNING: material " << material << " is not available. Please check Materials.hh" << G4endl;
    return false;
  }
  if (target_log) {
    target_log->SetMaterial(targetMat);
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
    G4cout << "=========================================================" << G4endl;
    G4cout << "The material of Target has been changed to " << material << G4endl;
    G4cout << "" << targetMat->GetName() << G4endl;
    G4cout << "Z: " << targetMat->GetZ() << ", A: " << targetMat->GetA()/(g/mole) << " g/mole" << G4endl;
    G4cout << "density: " << targetMat->GetDensity()/(mg/cm3) << " mg/cm3" << G4endl;
    G4cout << "Formula: " << targetMat->GetChemicalFormula()
           << " MlcMass: " << targetMat->GetMassOfMolecule()
           << " NElm: " << targetMat->GetNumberOfElements() << G4endl;
    G4cout << "=========================================================" << G4endl;
  }
  return true;
}

void DetectorConstruction::SetTargetDensity(G4double density)
{
  G4String tgname = targetMat->GetName();
  G4double pre_d = targetMat->GetDensity();
  targetMat = new G4Material(Form("%s_new",tgname.data()),density,targetMat);
  if (target_log) {
    target_log->SetMaterial(targetMat);
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
    G4cout << "=========================================================" << G4endl;
    G4cout << "The density of Target has been changed from " << pre_d/(mg/cm3) << " to " << density/(mg/cm3) << " mg/cm3 " << G4endl;
    G4cout << "" << targetMat->GetName() << G4endl;
    G4cout << "Z: " << targetMat->GetZ() << ", A: " << targetMat->GetA()/(g/mole) << " g/mole" << G4endl;
    G4cout << "Formula: " << targetMat->GetChemicalFormula()
           << " MlcMass: " << targetMat->GetMassOfMolecule()
           << " NElm: " << targetMat->GetNumberOfElements() << G4endl;
    G4cout << "=========================================================" << G4endl;
  }
}
