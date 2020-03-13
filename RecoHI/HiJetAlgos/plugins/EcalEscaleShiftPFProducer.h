#ifndef EcalEscaleShiftPFProducer_h
#define EcalEscaleShiftPFProducer_h


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"


class EcalEscaleShiftPFProducer : public edm::EDProducer {
 public:
  explicit EcalEscaleShiftPFProducer(const edm::ParameterSet&);
  ~EcalEscaleShiftPFProducer() override;
  
 private:
  void beginJob() override ;
  void produce(edm::Event&, const edm::EventSetup&) override;
  void endJob() override ;

  // ----------member data ---------------------------

  edm::EDGetTokenT<reco::PFCandidateCollection> src_;  
  edm::EDGetTokenT<reco::PFCandidateCollection> pfCands_;  

  bool removePreshower_;
  double scaleEE_, scaleEB_;
  
};
#endif
