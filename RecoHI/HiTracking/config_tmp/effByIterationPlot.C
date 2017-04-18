#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TAttLine.h"
#include "TAttFill.h"
#include "TAttMarker.h"
#include "TAxis.h"
#include "TLegend.h"

void effByIterationPlot(float etaCut = 2.4, float ptCut = 0, bool onlyInclusive = false){

  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0.);
  const int nIterations = 5;

  TH2D * hsim[10];
  TH2D * hrec[10];
  TH2D * hfak[10];
  TH2D * heff[10];
  
  TH1D * hsimPt[10];
  TH1D * hrecPt[10];
  TH1D * hfakPt[10];
  TH1D * heffPt[10];
  TH1D * hsimEta[10];
  TH1D * hrecEta[10];
  TH1D * hfakEta[10];
  TH1D * heffEta[10];

  const int nptBins = 51;
  const float ptBins[nptBins] = {
        0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45,
        0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95,
        1.0, 1.05, 1.1, 1.15, 1.2,
        1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
        2.5, 3.0, 4.0, 5.0, 7.5, 10.0, 12.0, 15.0,
        20.0, 25.0, 30.0, 45.0, 60.0, 90.0, 120.0, 
        180.0, 300.0, 500.0};
  const int netaBins = 13;
  const float etaBins[netaBins] = {
        -2.4, -2.0, -1.6, -1.2, -0.8, -0.4, 0.0,
        0.4, 0.8, 1.2, 1.6, 2.0, 2.4};

  TFile * f;
  if(!onlyInclusive) f = TFile::Open("trk.root","read");
  else               f = TFile::Open("test/trk.root","read");
  hsim[0] = (TH2D*)f->Get("HITrackCorrections/hsim");
  hrec[0] = (TH2D*)f->Get("HITrackCorrections/hrec");
  hfak[0] = (TH2D*)f->Get("HITrackCorrections/hfak"); 
  heff[0] = (TH2D*)f->Get("HITrackCorrections/heff"); 
  hsim[0]->SetDirectory(0);
  hrec[0]->SetDirectory(0);
  hfak[0]->SetDirectory(0);
  heff[0]->SetDirectory(0);
  f->Close();

  if(!onlyInclusive){
  for(int i = 0; i<nIterations; i++){
    TFile * f = TFile::Open(Form("trk_%d.root",i),"read");
    hsim[i+1] = (TH2D*)f->Get("HITrackCorrections/hsim");
    hrec[i+1] = (TH2D*)f->Get("HITrackCorrections/hrec");
    hfak[i+1] = (TH2D*)f->Get("HITrackCorrections/hfak"); 
    heff[i+1] = (TH2D*)f->Get("HITrackCorrections/heff"); 
    hsim[i+1]->SetDirectory(0);
    hrec[i+1]->SetDirectory(0);
    hfak[i+1]->SetDirectory(0);
    heff[i+1]->SetDirectory(0);
    f->Close();   
  }
  }

  TFile * f1 = TFile::Open("effByIteration.root","recreate");
  for(int i = 0; i<nIterations+1; i++){
    if(onlyInclusive && i>0) continue;
    //defining profiles
    hsimPt[i] = new TH1D(Form("hsimPt%d",i),"",nptBins-1,ptBins);
    hrecPt[i] = new TH1D(Form("hrecPt%d",i),"",nptBins-1,ptBins);
    hfakPt[i] = new TH1D(Form("hfakPt%d",i),"",nptBins-1,ptBins);
    heffPt[i] = new TH1D(Form("heffPt%d",i),"",nptBins-1,ptBins);
    hsimEta[i] = new TH1D(Form("hsimEta%d",i),"",netaBins-1,etaBins);
    hrecEta[i] = new TH1D(Form("hrecEta%d",i),"",netaBins-1,etaBins);
    hfakEta[i] = new TH1D(Form("hfakEta%d",i),"",netaBins-1,etaBins);
    heffEta[i] = new TH1D(Form("heffEta%d",i),"",netaBins-1,etaBins);

    //making profiles
    for(int j = 0; j<hsim[0]->GetXaxis()->GetNbins()+2; j++){//eta
      if(TMath::Abs(hsim[0]->GetXaxis()->GetBinCenter(j))>etaCut) continue;
      for(int k = 0; k<hsim[0]->GetYaxis()->GetNbins()+2; k++){//pt
        if((hsim[0]->GetYaxis()->GetBinCenter(k))<ptCut) continue;
        hsimPt[i]->SetBinContent(k,hsim[i]->GetBinContent(j,k)+hsimPt[i]->GetBinContent(k));
        hrecPt[i]->SetBinContent(k,hrec[i]->GetBinContent(j,k)+hrecPt[i]->GetBinContent(k));
        hfakPt[i]->SetBinContent(k,hfak[i]->GetBinContent(j,k)+hfakPt[i]->GetBinContent(k));
        heffPt[i]->SetBinContent(k,heff[i]->GetBinContent(j,k)+heffPt[i]->GetBinContent(k));
        hsimPt[i]->SetBinError(k,hsim[i]->GetBinError(j,k)+hsimPt[i]->GetBinError(k));
        hrecPt[i]->SetBinError(k,hrec[i]->GetBinError(j,k)+hrecPt[i]->GetBinError(k));
        hfakPt[i]->SetBinError(k,hfak[i]->GetBinError(j,k)+hfakPt[i]->GetBinError(k));
        heffPt[i]->SetBinError(k,heff[i]->GetBinError(j,k)+heffPt[i]->GetBinError(k));
        
        hsimEta[i]->SetBinContent(j,hsim[i]->GetBinContent(j,k)+hsimEta[i]->GetBinContent(j));
        hrecEta[i]->SetBinContent(j,hrec[i]->GetBinContent(j,k)+hrecEta[i]->GetBinContent(j));
        hfakEta[i]->SetBinContent(j,hfak[i]->GetBinContent(j,k)+hfakEta[i]->GetBinContent(j));
        heffEta[i]->SetBinContent(j,heff[i]->GetBinContent(j,k)+heffEta[i]->GetBinContent(j));
        hsimEta[i]->SetBinError(j,hsim[i]->GetBinError(j,k)+hsimEta[i]->GetBinError(j));
        hrecEta[i]->SetBinError(j,hrec[i]->GetBinError(j,k)+hrecEta[i]->GetBinError(j));
        hfakEta[i]->SetBinError(j,hfak[i]->GetBinError(j,k)+hfakEta[i]->GetBinError(j));
        heffEta[i]->SetBinError(j,heff[i]->GetBinError(j,k)+heffEta[i]->GetBinError(j));
      }
    }
    heffPt[i]->Divide(hsimPt[0]);
    hfakPt[i]->Divide(hrecPt[0]);
    heffEta[i]->Divide(hsimEta[0]);
    hfakEta[i]->Divide(hrecEta[0]);
    heffPt[i]->Write();
    hfakPt[i]->Write();
    heffEta[i]->Write();
    hfakEta[i]->Write();
  }

  //pteff
  TCanvas * c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx();
  heffPt[0]->GetXaxis()->SetTitle("p_{T} (GeV)");
  heffPt[0]->GetXaxis()->CenterTitle();
  heffPt[0]->GetYaxis()->SetTitle("Efficiency");
  heffPt[0]->GetYaxis()->CenterTitle();
  heffPt[0]->GetYaxis()->SetRangeUser(0,1.2);
  heffPt[0]->GetXaxis()->SetRangeUser(0.3,10);
  heffPt[0]->SetLineColor(kBlack);
  heffPt[0]->SetLineWidth(1);
  heffPt[0]->SetMarkerStyle(8);
  heffPt[0]->SetMarkerColor(kBlack);
  heffPt[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  heffPt[0]->SetLineColor(kBlack);
  heffPt[0]->SetLineWidth(1);
  heffPt[0]->SetFillColor(41);
  heffPt[0]->Draw("same hist"); 
  heffPt[5]->SetLineColor(kBlack);
  heffPt[5]->SetLineWidth(1);
  heffPt[5]->SetFillColor(30);
  heffPt[5]->Draw("same hist");
  heffPt[4]->SetLineColor(kBlack);
  heffPt[4]->SetLineWidth(1);
  heffPt[4]->SetFillColor(46);
  heffPt[4]->Draw("same hist");
  heffPt[3]->SetLineColor(kBlack);
  heffPt[3]->SetLineWidth(1);
  heffPt[3]->SetFillColor(kBlue-2);
  heffPt[3]->Draw("same hist");
  heffPt[2]->SetLineColor(kBlack);
  heffPt[2]->SetLineWidth(1);
  heffPt[2]->SetFillColor(38);
  heffPt[2]->Draw("same hist");
  heffPt[1]->SetLineColor(kBlack);
  heffPt[1]->SetLineWidth(1);
  heffPt[1]->SetFillColor(33);
  heffPt[1]->Draw("same hist");
  heffPt[0]->Draw("same p");
  c1->RedrawAxis();

  TLegend * leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(heffPt[0],"All Iterations","p");
  leg->AddEntry(heffPt[1],"hiBasicTracking","f");
  leg->AddEntry(heffPt[2],"hiLowPtQuadStep","f");
  leg->AddEntry(heffPt[3],"hiHighPtTripletStep","f");
  leg->AddEntry(heffPt[4],"hiDetachedQuadStep","f");
  leg->AddEntry(heffPt[5],"hiDetachedTripletStep","f");
  leg->AddEntry(heffPt[0],"hiLowPtTripletStep","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTEffByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;


  //etaeff
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx(0);
  heffEta[0]->GetXaxis()->SetTitle("#eta");
  heffEta[0]->GetXaxis()->CenterTitle();
  heffEta[0]->GetYaxis()->SetTitle("Efficiency");
  heffEta[0]->GetYaxis()->CenterTitle();
  heffEta[0]->GetYaxis()->SetRangeUser(0,1.2);
  heffEta[0]->GetXaxis()->SetRangeUser(-2.4,2.4);
  heffEta[0]->SetLineColor(kBlack);
  heffEta[0]->SetLineWidth(1);
  heffEta[0]->SetMarkerStyle(8);
  heffEta[0]->SetMarkerColor(kBlack);
  heffEta[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  heffEta[0]->SetLineColor(kBlack);
  heffEta[0]->SetLineWidth(1);
  heffEta[0]->SetFillColor(41);
  heffEta[0]->Draw("same hist"); 
  heffEta[5]->SetLineColor(kBlack);
  heffEta[5]->SetLineWidth(1);
  heffEta[5]->SetFillColor(30);
  heffEta[5]->Draw("same hist");
  heffEta[4]->SetLineColor(kBlack);
  heffEta[4]->SetLineWidth(1);
  heffEta[4]->SetFillColor(46);
  heffEta[4]->Draw("same hist");
  heffEta[3]->SetLineColor(kBlack);
  heffEta[3]->SetLineWidth(1);
  heffEta[3]->SetFillColor(kBlue-2);
  heffEta[3]->Draw("same hist");
  heffEta[2]->SetLineColor(kBlack);
  heffEta[2]->SetLineWidth(1);
  heffEta[2]->SetFillColor(38);
  heffEta[2]->Draw("same hist");
  heffEta[1]->SetLineColor(kBlack);
  heffEta[1]->SetLineWidth(1);
  heffEta[1]->SetFillColor(33);
  heffEta[1]->Draw("same hist");
  heffEta[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(heffEta[0],"All Iterations","p");
  leg->AddEntry(heffEta[1],"hiBasicTracking","f");
  leg->AddEntry(heffEta[2],"hiLowPtQuadStep","f");
  leg->AddEntry(heffEta[3],"hiHighPtTripletStep","f");
  leg->AddEntry(heffEta[4],"hiDetachedQuadStep","f");
  leg->AddEntry(heffEta[5],"hiDetachedTripletStep","f");
  leg->AddEntry(heffEta[0],"hiLowPtTripletStep","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaEffByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
  
  //ptfake
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx();
  hfakPt[0]->GetXaxis()->SetTitle("p_{T} (GeV)");
  hfakPt[0]->GetXaxis()->CenterTitle();
  hfakPt[0]->GetYaxis()->SetTitle("Fake Rate");
  hfakPt[0]->GetYaxis()->CenterTitle();
  hfakPt[0]->GetYaxis()->SetRangeUser(0,1.8);
  hfakPt[0]->GetXaxis()->SetRangeUser(0.3,10);
  hfakPt[0]->SetLineColor(kBlack);
  hfakPt[0]->SetLineWidth(1);
  hfakPt[0]->SetMarkerStyle(8);
  hfakPt[0]->SetMarkerColor(kBlack);
  hfakPt[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hfakPt[0]->SetLineColor(kBlack);
  hfakPt[0]->SetLineWidth(1);
  hfakPt[0]->SetFillColor(41);
  hfakPt[0]->Draw("same hist"); 
  hfakPt[5]->SetLineColor(kBlack);
  hfakPt[5]->SetLineWidth(1);
  hfakPt[5]->SetFillColor(30);
  hfakPt[5]->Draw("same hist");
  hfakPt[4]->SetLineColor(kBlack);
  hfakPt[4]->SetLineWidth(1);
  hfakPt[4]->SetFillColor(46);
  hfakPt[4]->Draw("same hist");
  hfakPt[3]->SetLineColor(kBlack);
  hfakPt[3]->SetLineWidth(1);
  hfakPt[3]->SetFillColor(kBlue-2);
  hfakPt[3]->Draw("same hist");
  hfakPt[2]->SetLineColor(kBlack);
  hfakPt[2]->SetLineWidth(1);
  hfakPt[2]->SetFillColor(38);
  hfakPt[2]->Draw("same hist");
  hfakPt[1]->SetLineColor(kBlack);
  hfakPt[1]->SetLineWidth(1);
  hfakPt[1]->SetFillColor(33);
  hfakPt[1]->Draw("same hist");
  hfakPt[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hfakPt[0],"All Iterations","p");
  leg->AddEntry(hfakPt[1],"hiBasicTracking","f");
  leg->AddEntry(hfakPt[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hfakPt[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hfakPt[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hfakPt[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hfakPt[0],"hiLowPtTripletStep","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/pTFakByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
  

  //etafak
  c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogx(0);
  hfakEta[0]->GetXaxis()->SetTitle("#eta");
  hfakEta[0]->GetXaxis()->CenterTitle();
  hfakEta[0]->GetYaxis()->SetTitle("Fake Rate");
  hfakEta[0]->GetYaxis()->CenterTitle();
  hfakEta[0]->GetYaxis()->SetRangeUser(0,1.4);
  hfakEta[0]->GetXaxis()->SetRangeUser(-2.4,2.4);
  hfakEta[0]->SetLineColor(kBlack);
  hfakEta[0]->SetLineWidth(1);
  hfakEta[0]->SetMarkerStyle(8);
  hfakEta[0]->SetMarkerColor(kBlack);
  hfakEta[0]->Draw();

  //stacking histograms
  if(!onlyInclusive){
  hfakEta[0]->SetLineColor(kBlack);
  hfakEta[0]->SetLineWidth(1);
  hfakEta[0]->SetFillColor(41);
  hfakEta[0]->Draw("same hist"); 
  hfakEta[5]->SetLineColor(kBlack);
  hfakEta[5]->SetLineWidth(1);
  hfakEta[5]->SetFillColor(30);
  hfakEta[5]->Draw("same hist");
  hfakEta[4]->SetLineColor(kBlack);
  hfakEta[4]->SetLineWidth(1);
  hfakEta[4]->SetFillColor(46);
  hfakEta[4]->Draw("same hist");
  hfakEta[3]->SetLineColor(kBlack);
  hfakEta[3]->SetLineWidth(1);
  hfakEta[3]->SetFillColor(kBlue-2);
  hfakEta[3]->Draw("same hist");
  hfakEta[2]->SetLineColor(kBlack);
  hfakEta[2]->SetLineWidth(1);
  hfakEta[2]->SetFillColor(38);
  hfakEta[2]->Draw("same hist");
  hfakEta[1]->SetLineColor(kBlack);
  hfakEta[1]->SetLineWidth(1);
  hfakEta[1]->SetFillColor(33);
  hfakEta[1]->Draw("same hist");
  hfakEta[0]->Draw("same p");
  c1->RedrawAxis();

  leg = new TLegend(0.15,0.6,0.35,0.85);
  leg->AddEntry(hfakEta[0],"All Iterations","p");
  leg->AddEntry(hfakEta[1],"hiBasicTracking","f");
  leg->AddEntry(hfakEta[2],"hiLowPtQuadStep","f");
  leg->AddEntry(hfakEta[3],"hiHighPtTripletStep","f");
  leg->AddEntry(hfakEta[4],"hiDetachedQuadStep","f");
  leg->AddEntry(hfakEta[5],"hiDetachedTripletStep","f");
  leg->AddEntry(hfakEta[0],"hiLowPtTripletStep","f");
  leg->Draw("same");
 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.png",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.pdf",(int)(ptCut*10),(int)(etaCut*10))); 
  c1->SaveAs(Form("plots/EtaFakByIteration_%d_%d.C",(int)(ptCut*10),(int)(etaCut*10))); 
  delete leg;
  }
  delete c1;
}
