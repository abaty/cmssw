// -*- C++ -*-
//
// Package:    HiJetBackground/HiFJRhoFlowModulationProducer
// Class:      HiFJRhoFlowModulationProducer

//ROOT dependencies
#include "TMath.h"
#include "TF1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TFile.h"
#include "TNamed.h"
#include "TStyle.h"

#include <cmath>

#include "RecoHI/HiJetAlgos/plugins/HiFJRhoFlowModulationProducer.h"
#include "DataFormats/Math/interface/deltaR.h"

using namespace std;
using namespace edm;

HiFJRhoFlowModulationProducer::HiFJRhoFlowModulationProducer(const edm::ParameterSet& iConfig)
{
  pfCandsToken_ = consumes<reco::PFCandidateCollection>(iConfig.getParameter<edm::InputTag>( "pfCandSource" ));
  EvtPlaneTag_ = consumes<reco::EvtPlaneCollection>(iConfig.getParameter<edm::InputTag>("EvtPlane"));
  doEvtPlane_ = iConfig.getParameter<bool> ("doEvtPlane");
  doFlatTest_ = iConfig.getParameter<bool> ("doFlatTest");
  doFreePlaneFit_ = iConfig.getParameter<bool> ("doFreePlaneFit");
  doJettyExclusion_ = iConfig.getParameter<bool> ("doJettyExclusion");
  jetTagLabel_ = iConfig.getParameter<InputTag>("jetTag");
  jetTag_ = consumes<reco::JetView> (jetTagLabel_);
  evtPlaneLevel_ = iConfig.getParameter<int>("evtPlaneLevel");

  //register your products
  produces<std::vector<double> >("rhoFlowFitParams");
}


HiFJRhoFlowModulationProducer::~HiFJRhoFlowModulationProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

// ------------ method called to produce the data  ------------
void
HiFJRhoFlowModulationProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  //Values from rho calculator 

  edm::Handle<reco::PFCandidateCollection> pfCands;
  iEvent.getByToken(pfCandsToken_, pfCands);

  edm::Handle<reco::EvtPlaneCollection> evtPlanes;
  nEvtPlanes = 0;
  if (doEvtPlane_) {
    iEvent.getByToken(EvtPlaneTag_,evtPlanes);
    if(evtPlanes.isValid()){
      nEvtPlanes += evtPlanes->size();
      for(unsigned int i = 0; i < evtPlanes->size(); ++i){
        hiEvtPlane[i] = (*evtPlanes)[i].angle(evtPlaneLevel_);
      }
    }
  }

  edm::Handle<reco::JetView> jets;
  if(doJettyExclusion_) iEvent.getByToken(jetTag_, jets);

  double eventPlane2 = -100;
  double eventPlane3 = -100;
  const reco::PFCandidateCollection *pfCandidateColl_p = pfCands.product();
  int nFill = 0;

  int nParamVals = 9;
  if(doFlatTest_) nParamVals *= 2;
  auto rhoFlowFitParamsOut = std::make_unique<std::vector<double> >(nParamVals,1e-6);
  
  rhoFlowFitParamsOut->at(0) = 0;
  rhoFlowFitParamsOut->at(1) = 0;
  rhoFlowFitParamsOut->at(2) = 0;
  rhoFlowFitParamsOut->at(3) = 0;
  rhoFlowFitParamsOut->at(4) = 0;
    
  if(!doEvtPlane_){
    double eventPlane2Cos = 0;
    double eventPlane2Sin = 0;
    
    double eventPlane3Cos = 0;
    double eventPlane3Sin = 0;
    
    for(unsigned pfIter = 0; pfIter < pfCandidateColl_p->size(); pfIter++){
      const reco::PFCandidate pfCandidate = pfCandidateColl_p->at(pfIter);
      
      if(pfCandidate.eta() < -1.0) continue;
      if(pfCandidate.eta() > 1.0) continue;      
      if(pfCandidate.pt() < .3) continue;
      if(pfCandidate.pt() > 3.) continue;
      if(pfCandidate.particleId() != 1) continue;

      if(doJettyExclusion_){
	bool isGood = true;
	for(unsigned int j = 0; j < jets->size(); ++j){
	  const reco::Jet& jet = (*jets)[j];
	  
	  if(deltaR(jet, pfCandidate) < .4){
	    isGood = false;
	    break;
	  }
	}      
	if(!isGood) continue;
      }

      nFill++;
      
      eventPlane2Cos += std::cos(2*pfCandidate.phi());
      eventPlane2Sin += std::sin(2*pfCandidate.phi());
      
      eventPlane3Cos += std::cos(3*pfCandidate.phi());
      eventPlane3Sin += std::sin(3*pfCandidate.phi());
    }
    
    eventPlane2 = std::atan2(eventPlane2Sin, eventPlane2Cos)/2.;
    eventPlane3 = std::atan2(eventPlane3Sin, eventPlane3Cos)/3.;    
  }
  else{
    eventPlane2 = hiEvtPlane[8];
    eventPlane3 = hiEvtPlane[15];

    for(unsigned pfIter = 0; pfIter < pfCandidateColl_p->size(); pfIter++){
      const reco::PFCandidate pfCandidate = pfCandidateColl_p->at(pfIter);

      if(pfCandidate.eta() < -1.0) continue;
      if(pfCandidate.eta() > 1.0) continue;

      if(pfCandidate.pt() < .3) continue;
      if(pfCandidate.pt() > 3.) continue;

      if(pfCandidate.particleId() != 1) continue;

      if(doJettyExclusion_){
        bool isGood = true;
        for(unsigned int j = 0; j < jets->size(); ++j){
          const reco::Jet& jet = (*jets)[j];

          if(deltaR(jet, pfCandidate) < .4){
            isGood = false;
            break;
          }
        }
        if(!isGood) continue;
      }

      nFill++;
    }
  }

  if(nFill >= 100 && eventPlane2 > -99){
    const int nPhiBins = std::fmax(10, nFill/30);

    std::string name = "phiTestIEta4_" + std::to_string(iEvent.id().event()) + "_h";
    std::string nameFlat = "phiTestIEta4_Flat_" + std::to_string(iEvent.id().event()) + "_h";

    TH1F* phi_h = new TH1F(name.c_str(), ";#phi;Track counts (.3 < p_{T} < 3.)", nPhiBins, -TMath::Pi(), TMath::Pi());
    TH1F* phi_Flat_h = new TH1F(nameFlat.c_str(), ";#phi;Track counts (.3 < p_{T} < 3.)", nPhiBins, -TMath::Pi(), TMath::Pi());

    for(unsigned pfIter = 0; pfIter < pfCandidateColl_p->size(); pfIter++){
      const reco::PFCandidate pfCandidate = pfCandidateColl_p->at(pfIter);

      if(pfCandidate.eta() < -1.0) continue;
      if(pfCandidate.eta() > 1.0) continue;

      if(pfCandidate.pt() < .3) continue;
      if(pfCandidate.pt() > 3.) continue;

      if(pfCandidate.particleId() != 1) continue;

      if(doJettyExclusion_){
        bool isGood = true;
        for(unsigned int j = 0; j < jets->size(); ++j){
          const reco::Jet& jet = (*jets)[j];

          if(deltaR(jet, pfCandidate) < .4){
            isGood = false;
            break;
          }
        }
        if(!isGood) continue;
      }

      phi_h->Fill(pfCandidate.phi());

      if(doFlatTest_){
	Float_t randPhi = randGen_p->Uniform(-TMath::Pi(), TMath::Pi());
	phi_Flat_h->Fill(randPhi);
      }
    }

    rhoFlowFitParamsOut->at(2) = eventPlane2;
    rhoFlowFitParamsOut->at(4) = eventPlane3;

    std::string flowFitForm = "[0]*(1. + 2.*([1]*TMath::Cos(2.*(x - " + std::to_string(eventPlane2) + ")) + [2]*TMath::Cos(3.*(x - " + std::to_string(eventPlane3) + "))))";

    TF1* flowFit_p = new TF1("flowFit", flowFitForm.c_str(), -TMath::Pi(), TMath::Pi());
    flowFit_p->SetParameter(0, 10);
    flowFit_p->SetParameter(1, 0);
    flowFit_p->SetParameter(2, 0);

    TF1* lineFit_p = new TF1("lineFit", "[0]", -TMath::Pi(), TMath::Pi());
    lineFit_p->SetParameter(0, 10);

    std::string flowFitForm2 = "[0]*(1. + 2.*([1]*TMath::Cos(2.*(x - [2])) + [3]*TMath::Cos(3*(x - [4]))))";

    TF1* flowFit2_p = new TF1("flowFit2", flowFitForm2.c_str(), -TMath::Pi(), TMath::Pi());
    flowFit2_p->SetParameter(0, 10);
    flowFit2_p->SetParameter(1, 0);
    flowFit2_p->SetParameter(2, eventPlane2);
    flowFit2_p->SetParameter(3, 0);
    flowFit2_p->SetParameter(4, eventPlane3);
    flowFit2_p->SetMarkerColor(kBlue);
    flowFit2_p->SetLineColor(kBlue);

    phi_h->Fit(flowFit_p, "Q", "", -TMath::Pi(), TMath::Pi());
    phi_h->Fit(lineFit_p, "Q", "", -TMath::Pi(), TMath::Pi());
    phi_h->Fit(flowFit2_p, "Q", "", -TMath::Pi(), TMath::Pi());

    if(!doFreePlaneFit_){
      rhoFlowFitParamsOut->at(0) = flowFit_p->GetParameter(0);
      rhoFlowFitParamsOut->at(1) = flowFit_p->GetParameter(1);
      rhoFlowFitParamsOut->at(3) = flowFit_p->GetParameter(2);
      
      rhoFlowFitParamsOut->at(5) = flowFit_p->GetChisquare();
      rhoFlowFitParamsOut->at(6) = nPhiBins-3;
    }
    else{
      rhoFlowFitParamsOut->at(0) = flowFit2_p->GetParameter(0);
      rhoFlowFitParamsOut->at(1) = flowFit2_p->GetParameter(1);
      rhoFlowFitParamsOut->at(2) = flowFit2_p->GetParameter(2);
      rhoFlowFitParamsOut->at(3) = flowFit2_p->GetParameter(3);
      rhoFlowFitParamsOut->at(4) = flowFit2_p->GetParameter(4);

      rhoFlowFitParamsOut->at(5) = flowFit2_p->GetChisquare();
      rhoFlowFitParamsOut->at(6) = nPhiBins-5;
    }

    rhoFlowFitParamsOut->at(7) = lineFit_p->GetChisquare();
    rhoFlowFitParamsOut->at(8) = nPhiBins-1;
      
    if(doFlatTest_){
      phi_Flat_h->Fit(flowFit_p, "Q", "", -TMath::Pi(), TMath::Pi());
      phi_Flat_h->Fit(lineFit_p, "Q", "", -TMath::Pi(), TMath::Pi());
      phi_Flat_h->Fit(flowFit2_p, "Q", "", -TMath::Pi(), TMath::Pi());

      rhoFlowFitParamsOut->at(nParamVals/2+2) = eventPlane2;
      rhoFlowFitParamsOut->at(nParamVals/2+4) = eventPlane3;

      if(!doFreePlaneFit_){
	rhoFlowFitParamsOut->at(nParamVals/2+0) = flowFit_p->GetParameter(0);
	rhoFlowFitParamsOut->at(nParamVals/2+1) = flowFit_p->GetParameter(1);
	rhoFlowFitParamsOut->at(nParamVals/2+3) = flowFit_p->GetParameter(2);
	
	rhoFlowFitParamsOut->at(nParamVals/2+5) = flowFit_p->GetChisquare();
	rhoFlowFitParamsOut->at(nParamVals/2+6) = nPhiBins-3;
      }
      else{
	rhoFlowFitParamsOut->at(nParamVals/2+0) = flowFit2_p->GetParameter(0);
	rhoFlowFitParamsOut->at(nParamVals/2+1) = flowFit2_p->GetParameter(1);
	rhoFlowFitParamsOut->at(nParamVals/2+2) = flowFit2_p->GetParameter(2);
	rhoFlowFitParamsOut->at(nParamVals/2+3) = flowFit2_p->GetParameter(3);
	rhoFlowFitParamsOut->at(nParamVals/2+4) = flowFit2_p->GetParameter(4);
	
	rhoFlowFitParamsOut->at(nParamVals/2+5) = flowFit2_p->GetChisquare();
	rhoFlowFitParamsOut->at(nParamVals/2+6) = nPhiBins-5;
      }
      
      rhoFlowFitParamsOut->at(nParamVals/2+7) = lineFit_p->GetChisquare();
      rhoFlowFitParamsOut->at(nParamVals/2+8) = nPhiBins-1;      
    }

    delete phi_h;
    delete phi_Flat_h;

    delete flowFit_p;
    delete lineFit_p;
    delete flowFit2_p;
  }

  iEvent.put(std::move(rhoFlowFitParamsOut), "rhoFlowFitParams");
}


// ------------ method called once each job just before starting event loop  ------------
void 
HiFJRhoFlowModulationProducer::beginJob()
{
  if(doFlatTest_) randGen_p = new TRandom3(0);
  if(doEvtPlane_){
    const int kMaxEvtPlanes = 1000;
    hiEvtPlane = new float[kMaxEvtPlanes];
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiFJRhoFlowModulationProducer::endJob() {
    if(doFlatTest_) delete randGen_p;
    if(doEvtPlane_) delete hiEvtPlane;
}
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void HiFJRhoFlowModulationProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(HiFJRhoFlowModulationProducer);

