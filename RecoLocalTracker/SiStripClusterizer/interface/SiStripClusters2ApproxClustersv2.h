#ifndef RecoLocalTracker_SiStripClusters2ApproxClustersv2_h
#define RecoLocalTracker_SiStripClusters2ApproxClustersv2_h

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/SiStripApproximateClusterv2/interface/SiStripApproximateClusterv2.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include <vector>
#include <memory>

class SiStripClusters2ApproxClustersv2: public edm::stream::EDProducer<>  {

public:

  explicit SiStripClusters2ApproxClustersv2(const edm::ParameterSet& conf);
  void produce(edm::Event&, const edm::EventSetup&) override;

private:

  edm::InputTag inputClusters;
  edm::EDGetTokenT< edmNew::DetSetVector<SiStripCluster> > clusterToken;  
};

DEFINE_FWK_MODULE(SiStripClusters2ApproxClustersv2);
#endif

