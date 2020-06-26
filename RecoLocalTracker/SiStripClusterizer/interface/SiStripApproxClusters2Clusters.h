#ifndef RecoLocalTracker_SiStripApproxClusters2Clusters_h
#define RecoLocalTracker_SiStripApproxClusters2Clusters_h

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/SiStripApproximateCluster/interface/SiStripApproximateCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/DetSetVector.h"

#include <vector>
#include <memory>

class SiStripApproxClusters2Clusters: public edm::stream::EDProducer<>  {

public:

  explicit SiStripApproxClusters2Clusters(const edm::ParameterSet& conf);
  void produce(edm::Event&, const edm::EventSetup&) override;

private:

  edm::InputTag inputClusters;
  edm::EDGetTokenT< edmNew::DetSetVector<SiStripApproximateCluster> > clusterToken;  
};

DEFINE_FWK_MODULE(SiStripApproxClusters2Clusters);
#endif

