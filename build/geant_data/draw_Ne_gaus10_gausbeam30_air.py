from ROOT import gROOT
gROOT.SetBatch()

import ROOT
import numpy as np
import sys
import os
import optparse

import beam_intensity as bi
import importlib
importlib.reload(bi)

parser = optparse.OptionParser()
parser.add_option('--p1',  dest='p1', action="store",type=str, help='NeGas atm 010',default=None)
parser.add_option('--p2',  dest='p2', action="store",type=str, help='NeGas atm 0.10',default=None)
options,args = parser.parse_args()

#p1="010"
#p2="0.10"
p1=options.p1
p2=options.p2

cs=bi.cs
nbeam=1e4# 10k

#Mom=np.arange(160,275,5,dtype=np.float)
Mom=np.arange(160,280,10,dtype=np.float)
#fnames = ["mu-_mom%d_gaus3_Ne%satm_gausbeam30_120air"%(int(mom),p1) for mom in Mom]
fnames = ["mu-_mom%d_gaus10_Ne%satm_gausbeam30_132air"%(int(mom),p1) for mom in Mom]
Mom=Mom/10.
i_150kw = cs(Mom)# mu-/sec
i_550kw = i_150kw*550./150.# mu-/sec

stop_rate=np.zeros_like(fnames,dtype=np.float)

nbin=100
minx=-10.
maxx=990.
fs = [ROOT.TFile.Open("./geant_"+fname+".root") for fname in fnames]
hs = [ROOT.TH1F("h%d"%(i),"h%d"%(i),nbin,minx,maxx) for i in range(len(fnames))]
htgs = [ROOT.TH1F("htg%d"%(i),"htg%d"%(i),nbin,minx,maxx) for i in range(len(fnames))]

# assumed target acceptance
# TES position +-5 cm
#16.+3.9+200.+120.# mm
air_add=352.-200.-3.9-16.0
tes_center = air_add+16.+3.9+200.
lbin=htgs[0].FindBin(tes_center-50.)
hbin=htgs[0].FindBin(tes_center+50.)
tes_accept_rate=np.zeros_like(fnames,dtype=np.float)


ROOT.gStyle.SetOptStat(0)

c1 = ROOT.TCanvas("c1","c1")
ROOT.gPad.SetGrid(0,0);
ROOT.gPad.SetTicks();
legend = ROOT.TLegend(0.4, 0.40, 0.9, 0.80)
legend.SetFillColor(0)
legend.SetFillStyle(0)
legend.SetTextSize(0.02)
for i,(f,fname,h) in enumerate(zip(fs,fnames,hs)):
    f.tree.Draw("beamlastpos[0][2]>>h%d"%(i),"beampdg[0]==13 && beamproc[0]==60","GOFF")
    h.SetLineColor(30+i*2)
    if i==0:
        bw=h.GetBinWidth(1)
        h.SetTitle("mu- stopped position")
        h.GetXaxis().SetTitle("Z pos [mm]")
        h.GetYaxis().SetTitle("Counts / %.1f mm"%bw)
        h.GetYaxis().SetRangeUser(0,1000)
        h.Draw("hist")
    else:
        h.Draw("histsame")
    legend.AddEntry(h.GetName(), fname, "l");
legend.Draw("same")
c1.SaveAs("mu-_stoppos_momdep_Ne%satm_gausbeam30_air_momgaus10.pdf"%(p1))



c2 = ROOT.TCanvas("c2","c2")
ROOT.gPad.SetGrid(0,0);
ROOT.gPad.SetTicks();
legend = ROOT.TLegend(0.4, 0.40, 0.9, 0.80)
legend.SetFillColor(0)
legend.SetFillStyle(0)
legend.SetTextSize(0.02)
for i,(f,fname,htg) in enumerate(zip(fs,fnames,htgs)):
    f.tree.Draw("tglastpos[0][2]>>htg%d"%(i),"tgpdg[0]==13 && tgproc[0]==60","GOFF")
    tes_accept_rate[i]=htg.Integral(lbin,hbin)/nbeam
    htg.SetLineColor(30+i*2)
    stop_rate[i] = htg.GetEntries()/nbeam
    if i==0:
        bw=htg.GetBinWidth(1)
        htg.SetTitle("mu- stopped position on NeGas target / 10k")
        htg.GetXaxis().SetTitle("Z pos [mm]")
        htg.GetYaxis().SetTitle("Counts / %.1f mm"%bw)
        h.GetYaxis().SetRangeUser(0,1000)
        htg.Draw("hist")
    else:
        htg.Draw("histsame")
    legend.AddEntry(htg.GetName(), fname+" stpr=%.2f"%(stop_rate[i]), "l");
legend.Draw("same")
c2.SaveAs("mu-_target_stoppos_momdep_Ne%satm_gausbeam30_air_momgaus10.pdf"%(p1))

for m,i,st,acc in zip(Mom,i_150kw,stop_rate,tes_accept_rate):
    print ("%.1f %.1f %.4f %.2f %.4f"%(m,i,st,st*i,acc*i))


#maxi=5
maxi=np.argmax(stop_rate*i_150kw)
print ("maxi =",maxi)

    
import pylab as plt
plt.close('all')
plt.ion()

maxi_acc=np.argmax(tes_accept_rate*i_150kw)
plt.figure()
plt.plot(Mom,tes_accept_rate*i_150kw,"o-",label='150kW')# stop/sec
plt.plot(Mom,tes_accept_rate*i_550kw,"o-",label='550kW')# stop/sec
plt.xlabel("Momentum [MeV/c]")
plt.ylabel("# of stopped $\mu^-$ on Ne %s atm target [/sec]"%(p2))
plt.title("stopped $\mu^-$ within TES position +- 5 cm")
maxh=np.max(tes_accept_rate*i_550kw)
plt.ylim(-maxh*0.05,maxh*1.2)
plt.legend()
plt.text(Mom[maxi_acc],np.max(tes_accept_rate*i_150kw), "%.1f"%(np.max(tes_accept_rate*i_150kw)))
plt.text(Mom[maxi_acc],maxh,"%.1f"%(maxh))
plt.tight_layout()
plt.savefig("Ne%satm_tesaccept_stopmu_per_sec_air_momgaus10_gausbeam30.pdf"%(p1))

plt.figure()
plt.plot(Mom,stop_rate*i_150kw,"o-",label='150kW')# stop/sec
plt.plot(Mom,stop_rate*i_550kw,"o-",label='550kW')# stop/sec
plt.xlabel("Momentum [MeV/c]")
plt.ylabel("# of stopped $\mu^-$ on Ne %s atm target [/sec]"%(p2))
plt.title("stopped $\mu^-$ on Ne %s atm target"%(p2))
maxh=np.max(stop_rate*i_550kw)
plt.ylim(-maxh*0.05,maxh*1.2)
plt.legend()
plt.text(Mom[maxi],np.max(stop_rate*i_150kw), "%.1f"%(np.max(stop_rate*i_150kw)))
plt.text(Mom[maxi],np.max(stop_rate*i_550kw), "%.1f"%(np.max(stop_rate*i_550kw)))
plt.tight_layout()
plt.savefig("Ne%satm_stopmu_per_sec_air_momgaus10.pdf"%(p1))

# activity calculation
iso  = ["22F","21F","20F","19F","18F","17F"]
na   = np.array([9.25,0.27,90.48])# natual abundant (%)
Pcap = np.array([30.,30.,30.])# capture rate (%)
# branching ratio (%)
BR=[[10,0,0],
    [45,10,0],
    [30,45,10],
    [10,30,40],
    [5,10,50],
    [0,5,10]]
br=np.array(BR,dtype=np.float)
fra  = np.array([0.,0.,0.,0.,0.,0.])# fraction
for i,b in enumerate(br):
    for a,c,bi in zip(na,Pcap,b):
        fra[i] += a*c*bi/1e6
    print (iso[i], fra[i])

# half life time (sec)
hlife = np.array([4.230,4.158,11.070,1e30,6586.2,64.690])
# decay rate
dc = [np.log(2)/hl for hl in hlife]



hour=24
tend=hour*3600.
t = np.arange(tend)# time sec
A = [i_150kw[maxi]*stop_rate[maxi]*frai*(1.-np.exp(-dci*t)) for frai,dci in zip(fra,dc)]
A2 = [i_550kw[maxi]*stop_rate[maxi]*frai*(1.-np.exp(-dci*t)) for frai,dci in zip(fra,dc)]
# after
t_a = np.arange(tend+1,2.*tend+2,1)# time sec
A_a = [i_150kw[maxi]*stop_rate[maxi]*frai*(1.-np.exp(-dci*tend))*np.exp(-dci*(t_a - tend)) for frai,dci in zip(fra,dc)]
A2_a = [i_550kw[maxi]*stop_rate[maxi]*frai*(1.-np.exp(-dci*tend))*np.exp(-dci*(t_a - tend)) for frai,dci in zip(fra,dc)]

x=np.hstack((t,t_a))
y=np.hstack((A,A_a))
y2=np.hstack((A2,A2_a))

plt.figure()
for i,(yi,y2i) in enumerate(zip(y,y2)):
    plt.plot(x/3600.,yi,"-",label="%s 150kW"%iso[i])
    #plt.plot(x/3600.,y2i,"-",label="%s 550kW"%iso[i])
plt.plot(x/3600.,np.sum(y,axis=0),"-",label="total 150kW")
plt.xlabel("Time [hour]")
plt.ylabel("Radiation activity [Bq]")
plt.legend()
plt.tight_layout()
plt.savefig("Activity_Ne%satm_stopmu_Bq_150kW_air_momgaus10_gausbeam30.pdf"%(p1))


plt.figure()
for i,(yi,y2i) in enumerate(zip(y,y2)):
    #plt.plot(x/3600.,yi,"-",label="%s 150kW"%iso[i])
    plt.plot(x/3600.,y2i,"-",label="%s 550kW"%iso[i])
plt.plot(x/3600.,np.sum(y2,axis=0),"-",label="total 550kW")
plt.xlabel("Time [hour]")
plt.ylabel("Radiation activity [Bq]")
plt.legend()
plt.tight_layout()
plt.savefig("Activity_Ne%satm_stopmu_Bq_550kW_air_momgaus10_gausbeam30.pdf"%(p1))

