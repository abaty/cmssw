#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripApproxClusters2Clusters.h"
#include <iostream>


SiStripApproxClusters2Clusters::SiStripApproxClusters2Clusters(const edm::ParameterSet& conf){
   inputClusters = conf.getParameter< edm::InputTag >("inputClusters");
   clusterToken = consumes< edmNew::DetSetVector< SiStripApproximateCluster > >(inputClusters);

   produces< edmNew::DetSetVector< SiStripCluster > >(); 

}

void SiStripApproxClusters2Clusters::produce(edm::Event& e, edm::EventSetup const&){
  std::unique_ptr<edmNew::DetSetVector< SiStripCluster > > result(new edmNew::DetSetVector< SiStripCluster > );

  edm::Handle<edmNew::DetSetVector< SiStripApproximateCluster >> clusterCollection;
  e.getByToken(clusterToken, clusterCollection);

  for( edmNew::DetSetVector<SiStripApproximateCluster>::const_iterator i = clusterCollection->begin(); i!=clusterCollection->end(); i++){

    edmNew::DetSetVector<SiStripCluster>::FastFiller ff = edmNew::DetSetVector<SiStripCluster>::FastFiller(*result, i->id());

    for( edmNew::DetSet<SiStripApproximateCluster>::const_iterator j = i->begin(); j!=i->end(); j++){

      uint16_t firstStrip = j->firstStrip(); 
      uint8_t width = j->width();
      uint8_t  avgCharge = j->avgCharge();

      std::vector< uint8_t > amplitudes = std::vector< uint8_t >(width, avgCharge);   
 
      SiStripCluster cluster = SiStripCluster( firstStrip,  amplitudes.begin(), amplitudes.end(), false );

      ff.push_back(cluster);
    }
  }

  e.put(std::move(result));
}


