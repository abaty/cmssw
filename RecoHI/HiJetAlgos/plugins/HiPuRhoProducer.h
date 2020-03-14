#ifndef HiJetBackground_HiPuRhoProducer_h
#define HiJetBackground_HiPuRhoProducer_h

// system include files
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "boost/shared_ptr.hpp"

// user include files
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "RecoJets/JetProducers/interface/AnomalousTower.h"

#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"

//
// class declaration
//

class HiPuRhoProducer : public edm::EDProducer {
 public:
  explicit HiPuRhoProducer(const edm::ParameterSet&);
  ~HiPuRhoProducer();
  
  typedef boost::shared_ptr<fastjet::ClusterSequence>        ClusterSequencePtr;
  typedef boost::shared_ptr<fastjet::JetDefinition>          JetDefPtr;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  virtual void setupGeometryMap(edm::Event& iEvent,const edm::EventSetup& iSetup);
  virtual void calculatePedestal(std::vector<fastjet::PseudoJet> const & coll);
  virtual void subtractPedestal(std::vector<fastjet::PseudoJet> & coll);
  virtual void calculateOrphanInput(std::vector<fastjet::PseudoJet> & orphanInput);
  virtual void packageRho();
  virtual void putRho(edm::Event& iEvent,const edm::EventSetup& iSetup);

  const static int nMaxJets_ = 200;
  int nref;
  float jteta[nMaxJets_],jtphi[nMaxJets_],jtpt[nMaxJets_],jtpu[nMaxJets_],jtexpt[nMaxJets_];
  int jtexngeom[nMaxJets_], jtexntow[nMaxJets_];
  
  const static int nEtaTow_ = 82;
  int vngeom[nEtaTow_],vntow[nEtaTow_],vieta[nEtaTow_];
  float veta[nEtaTow_],vmean0[nEtaTow_],vrms0[nEtaTow_],vrho0[nEtaTow_],vmean1[nEtaTow_],vrms1[nEtaTow_],vrho1[nEtaTow_];

  int medianWindowWidth_;
  double towSigmaCut_;

  double etaedge[42];

  std::vector<double> etaEdgeLow_;
  std::vector<double> etaEdgeHi_;
  std::vector<double> etaEdges_;
  std::vector<double> rho_;
  std::vector<double> rhoMedian_;
  std::vector<double> rhoExtra_;
  std::vector<double> rhoM_;
  std::vector<int> nTow_;
  std::vector<double> towExcludePt_;
  std::vector<double> towExcludePhi_;
  std::vector<double> towExcludeEta_;

  int ieta(const reco::CandidatePtr & in) const;
  int iphi(const reco::CandidatePtr & in) const;

  bool postOrphan_;
  bool dropZeroTowers_;
  double minimumTowersFraction_;

 protected:
  double puPtMin_;
  double nSigmaPU_;                  // number of sigma for pileup
  double radiusPU_;                  // pileup radius
  double rParam_;                    // the R parameter to use
  edm::InputTag src_;                       // input constituent source                                
  std::vector<edm::Ptr<reco::Candidate> >       inputs_;          // input candidates
  ClusterSequencePtr              fjClusterSeq_;    // fastjet cluster sequence
  JetDefPtr                       fjJetDefinition_; // fastjet jet definition     
  std::vector<fastjet::PseudoJet> fjInputs_;        // fastjet inputs
  std::vector<fastjet::PseudoJet> fjJets_;          // fastjet jets
  std::vector<fastjet::PseudoJet> fjOriginalInputs_;        // to back-up unsubtracted fastjet inputs

  CaloGeometry const *  geo_=NULL;                       // geometry
  std::vector<HcalDetId> allgeomid_;                // all det ids in the geometry
  
  int                   ietamax_=-10000;                   // maximum eta in geometry
  int                   ietamin_=10000;                   // minimum eta in geometry       
  std::map<int,int>     ntowersWithJets_;           // number of towers with jets
  std::map<int,int>     geomtowers_;                // map of geometry towers to det id
  std::map<int,double>  esigma_;                    // energy sigma
  std::map<int,double>  emean_;                     // energy mean              
  std::map<int, std::vector<double> >  eTop4_;                     // energy mean              


  // This checks if the tower is anomalous (if a calo tower).
  virtual void inputTowers();

 private:
  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  //input
  edm::EDGetTokenT<reco::CandidateView> input_candidateview_token_;
      
  //members
};

#endif
