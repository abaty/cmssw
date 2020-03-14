#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include <vector>
#include <cmath>

class HiPFCandCleaner : public edm::EDProducer {
 public:
  explicit HiPFCandCleaner(const edm::ParameterSet&);
  ~HiPFCandCleaner();

  // class methods


private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  edm::InputTag pfCandidateLabel_;
  edm::EDGetTokenT<reco::PFCandidateCollection> pfCandidatePF_;
  edm::EDGetTokenT<reco::CandidateView> pfCandidateView_;

  // cuts
  Double_t        pfPtMin_;
  Double_t        pfAbsEtaMax_;
};
