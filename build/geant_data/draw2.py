import ROOT
import numpy as np
import sys


'''
"mu-20MeV_Mylar75um_Ne1atm.root"
"mu-20MeV_Mylar175um_Ne1atm.root"
"mu-20MeV_Mylar195um_Ne1atm.root"
"mu-20MeV_Mylar225um_Ne1atm.root"
"mu-20MeV_Mylar275um_Ne1atm.root"


"mu-17MeV_Mylar75um_Ne1atm.root"
"mu-16MeV_Mylar75um_Ne1atm.root"
"mu-15MeV_Mylar75um_Ne1atm.root"
"mu-14MeV_Mylar75um_Ne1atm.root"


"mu-20MeV_Mylar195um_Ne01atm.root"
"mu-20MeV_Mylar205um_Ne01atm.root"
"mu-20MeV_Mylar215um_Ne01atm.root"

"mu-17MeV_Mylar75um_Ne01atm.root"
"mu-16MeV_Mylar75um_Ne01atm.root"
"mu-15MeV_Mylar75um_Ne01atm.root"
"mu-14MeV_Mylar75um_Ne01atm.root"
"mu-13MeV_Mylar75um_Ne01atm.root"
"mu-10MeV_Mylar75um_Ne01atm.root"
"mu-5MeV_Mylar75um_Ne01atm.root"
'''



fnames = ["mu-20MeV_Mylar75um_Ne1atm",
          "mu-20MeV_Mylar175um_Ne1atm",
          "mu-20MeV_Mylar195um_Ne1atm",
          "mu-20MeV_Mylar225um_Ne1atm",
          "mu-20MeV_Mylar275um_Ne1atm"]
          


beamI = np.array([6.0,4.0,2.8,2.3,1.7])# 20, 17, 16, 15, 14
bscale = beamI/beamI[0]

nbin=100
minx=0.
maxx=1000.

fs = [ROOT.TFile.Open(fnames[i]+".root") for i in xrange(len(fnames))]
hs = [ROOT.TH1F("h%d"%(i),"h%d"%(i),nbin,minx,maxx) for i in xrange(len(fnames))]

ROOT.gStyle.SetOptStat(0)
c1 = ROOT.TCanvas("c1","c1")
legend = ROOT.TLegend(0.6, 0.68, 0.99, 0.78)
legend.SetFillColor(0)
legend.SetTextSize(0.03)

for i in xrange(len(fnames)):
    fs[i].tree.Draw("tglastpos[0][2]>>h%d"%(i),"tgpdg==13 && tg_proc==60","GOFF")
    legend.AddEntry(hs[i], fnames[i], "l");
    hs[i].SetLineColor(i+1)
    #hs[i].Scale(bscale[i])
    if i==0:
        hs[i].SetTitle("mu- stopped position degrader dependence")
        hs[i].GetXaxis().SetTitle("Z pos [mm]")
        hs[i].GetYaxis().SetTitle("Counts / 10 mm")
        hs[i].GetYaxis().SetRangeUser(0,1000)
        hs[i].Draw("hist")
    else:
        hs[i].Draw("histsame")
legend.Draw("same")
c1.SaveAs("mu-stoppos_degdep_Ne1atm.pdf")
