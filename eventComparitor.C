#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TTree.h"

void eventComparitor(){

  TH1::SetDefaultSumw2();

  TFile * f = TFile::Open("step3_nominal.root");
//  TFile * f1 = TFile::Open("step3_RAW2DIGI_L1Reco_RECO_new.root");
  TFile * f1 = TFile::Open("step3_CM5.root");

  TTree * t = (TTree*)f->Get("Events");
  TTree * t1 = (TTree*)f1->Get("Events");

  const int nBins = 33;
  const float bins[nBins] = {0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.4,1.6,1.8,2,2.4,2.8,3.2,3.6,4,5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50};

  TH1F * trkPt = new TH1F("trkPt","",nBins,bins);
  TH1F * trkPt1 = new TH1F("trkPt1","",nBins,bins);
  TH1F * trkPtC = new TH1F("trkPtC","",nBins,bins);
  TH1F * trkPtC1 = new TH1F("trkPtC1","",nBins,bins);

  TH1F * hit = new TH1F("hit","",30,0,30);
  TH1F * hit1 = new TH1F("hit1","",30,0,30);
  
  t->Draw("recoTracks_hiGeneralTracks__RECO2.obj->pt()>>trkPt","");
  t1->Draw("recoTracks_hiGeneralTracks__RECO2.obj->pt()>>trkPt1","");
  t->Draw("recoTracks_hiGeneralTracks__RECO2.obj->pt()>>trkPtC","recoTracks_hiGeneralTracks__RECO2.obj.quality_>100 && recoTracks_hiGeneralTracks__RECO2.obj->ptError()/recoTracks_hiGeneralTracks__RECO2.obj->pt()<0.3");// && TMath::Abs(recoTracks_hiGeneralTracks__RECO2.obj->eta())<1");
  t1->Draw("recoTracks_hiGeneralTracks__RECO2.obj->pt()>>trkPtC1","recoTracks_hiGeneralTracks__RECO2.obj.quality_>100 && recoTracks_hiGeneralTracks__RECO2.obj->ptError()/recoTracks_hiGeneralTracks__RECO2.obj->pt()<0.3");// && TMath::Abs(recoTracks_hiGeneralTracks__RECO2.obj->eta())<1");
  t->Draw("recoTracks_hiGeneralTracks__RECO2.obj.hitPattern_.hitCount>>hit","");
  t1->Draw("recoTracks_hiGeneralTracks__RECO2.obj.hitPattern_.hitCount>>hit1","");

  for(int i = 1; i<trkPt->GetSize()-1; i++){
    trkPt->SetBinContent(i,trkPt->GetBinContent(i)/(bins[i]-bins[i-1]));
    trkPt1->SetBinContent(i,trkPt1->GetBinContent(i)/(bins[i]-bins[i-1]));
    trkPt->SetBinError(i,trkPt->GetBinError(i)/(bins[i]-bins[i-1]));
    trkPt1->SetBinError(i,trkPt1->GetBinError(i)/(bins[i]-bins[i-1]));
    trkPtC->SetBinContent(i,trkPtC->GetBinContent(i)/(bins[i]-bins[i-1]));
    trkPtC1->SetBinContent(i,trkPtC1->GetBinContent(i)/(bins[i]-bins[i-1]));
    trkPtC->SetBinError(i,trkPtC->GetBinError(i)/(bins[i]-bins[i-1]));
    trkPtC1->SetBinError(i,trkPtC1->GetBinError(i)/(bins[i]-bins[i-1]));
  }

  TCanvas * c1 = new TCanvas("c1","c1",800,600);
  trkPt->SetLineColor(kBlue);
  trkPt->GetXaxis()->SetRangeUser(0,50);
  trkPt->SetStats(0);
  trkPt->SetMarkerStyle(8);
  trkPt->SetMarkerColor(kBlue);
  trkPt->GetYaxis()->SetTitle("#frac{dN}{dp_{T}}");
  trkPt->GetXaxis()->SetTitle("p_{T}");
  trkPt1->SetLineColor(kRed);
  trkPt1->SetMarkerStyle(8);
  trkPt1->SetMarkerColor(kRed);
  trkPt->Draw();
  trkPt1->Draw("same");
  c1->SetLogx();
  c1->SetLogy();
  TLegend * l = new TLegend(0.7,0.7,0.9,0.9);
  //l->AddEntry(trkPt,"2015 RECO","p");
  //l->AddEntry(trkPt1,"new Baseline","p");
  l->AddEntry(trkPt,"Median","p");
  l->AddEntry(trkPt1,"CMNThresh = 10","p");
  l->Draw("same");
  c1->SaveAs("img/trkComparison_noCuts.png");
  c1->SaveAs("img/trkComparison_noCuts.pdf");

  trkPt1->Divide(trkPt);
  trkPt1->GetXaxis()->SetRangeUser(0,50);
  trkPt1->GetYaxis()->SetRangeUser(0.5,1.5);
  trkPt1->SetStats(0);
  trkPt1->SetMarkerStyle(8);
  trkPt1->SetMarkerColor(kRed);
  trkPt1->GetXaxis()->SetTitle("p_{T}");
  c1->SetLogy(0);
  trkPt1->GetYaxis()->SetTitle("Ratio (CMNThresh=5/Median)");
  trkPt1->Draw("");
  c1->SaveAs("img/trkComparison_noCuts_ratio.png");
  c1->SaveAs("img/trkComparison_noCuts_ratio.pdf");


  trkPtC->SetLineColor(kBlue);
  trkPtC->GetXaxis()->SetRangeUser(0,50);
  trkPtC->SetStats(0);
  trkPtC->SetMarkerStyle(8);
  trkPtC->SetMarkerColor(kBlue);
  trkPtC->GetYaxis()->SetTitle("#frac{dN}{dp_{T}}");
  trkPtC->GetXaxis()->SetTitle("p_{T}");
  trkPtC1->SetLineColor(kRed);
  trkPtC1->SetMarkerStyle(8);
  trkPtC1->SetMarkerColor(kRed);
  trkPtC->Draw("");
  trkPtC1->Draw("same");
  c1->SetLogx();
  c1->SetLogy();
  TLegend * l1 = new TLegend(0.7,0.7,0.9,0.9);
  //l1->AddEntry(trkPt,"2015 RECO","p");
  //l1->AddEntry(trkPt1,"new Baseline","p");
  l1->AddEntry(trkPt,"Median","p");
  l1->AddEntry(trkPt1,"CMNThresh=5","p");
  l1->Draw("same");
  c1->SaveAs("img/trkComparison_HP_pterror0p3.png");
  c1->SaveAs("img/trkComparison_HP_pterror0p3.pdf");

  trkPtC1->Divide(trkPtC);
  trkPtC1->GetYaxis()->SetRangeUser(0.5,1.5);
  trkPtC1->GetXaxis()->SetRangeUser(0,50);
  trkPtC1->SetStats(0);
  trkPtC1->SetMarkerStyle(8);
  trkPtC1->SetMarkerColor(kRed);
  trkPtC1->GetXaxis()->SetTitle("p_{T}");
  c1->SetLogy(0);
  trkPtC1->GetYaxis()->SetTitle("Ratio (CMNThresh=5/Median)");
  trkPtC1->Draw("");
  c1->SaveAs("img/trkComparison_HP_pterror0p3_ratio.png");
  c1->SaveAs("img/trkComparison_HP_pterror0p3_ratio.pdf");

  int hits = hit->GetEntries();
  hit->Scale(1/(float)hits);
  int hits1 = hit1->GetEntries();
  hit1->Scale(1/(float)hits1);
  hit->SetLineColor(kBlue);
  hit->SetStats(0);
  hit->SetMarkerStyle(8);
  hit->SetMarkerColor(kBlue);
  hit->GetYaxis()->SetTitle("normalized to unity");
  hit->GetXaxis()->SetTitle("nHits");
  hit1->SetLineColor(kRed);
  hit1->SetMarkerColor(kRed);
  hit->Draw();
  hit1->Draw("same");
  c1->SetLogx(0);
  c1->SetLogy(0);
  l->Draw("same");
  c1->SaveAs("img/nHitComparison_noCuts.png");
  c1->SaveAs("img/nHitComparison_noCuts.pdf");
  

}
