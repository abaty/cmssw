#ifndef SISTRIPAPPROXIMATECLUSTER_CLASSES_H
#define SISTRIPAPPROXIMATECLUSTER_CLASSES_H

#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/SiStripApproximateCluster/interface/SiStripApproximateCluster.h"
#include "DataFormats/Common/interface/ContainerMask.h"

namespace DataFormats_SiStripApproximateCluster {
  struct dictionary2 {


    edmNew::DetSetVector<SiStripApproximateCluster> dsvn;

    edm::Wrapper< SiStripApproximateCluster > dummy0;
    edm::Wrapper< std::vector<SiStripApproximateCluster>  > dummy1;

    edm::Wrapper< edmNew::DetSetVector<SiStripApproximateCluster> > dummy4_bis;
    
    edm::Wrapper<edm::ContainerMask<edmNew::DetSetVector<SiStripApproximateCluster> > > dummy_w_cm1;

    std::vector<edm::Ref<edmNew::DetSetVector<SiStripApproximateCluster>,SiStripApproximateCluster,edmNew::DetSetVector<SiStripApproximateCluster>::FindForDetSetVector> > dummy_v;
    edmNew::DetSetVector<edm::Ref<edmNew::DetSetVector<SiStripApproximateCluster>,SiStripApproximateCluster,edmNew::DetSetVector<SiStripApproximateCluster>::FindForDetSetVector> > dumm_dtvr;
    edm::Wrapper<edmNew::DetSetVector<edm::Ref<edmNew::DetSetVector<SiStripApproximateCluster>,SiStripApproximateCluster,edmNew::DetSetVector<SiStripApproximateCluster>::FindForDetSetVector> > > dumm_dtvr_w;


    edm::Ref<edmNew::DetSetVector<SiStripApproximateCluster>, SiStripApproximateCluster, edmNew::DetSetVector<SiStripApproximateCluster>::FindForDetSetVector > refNew;
  };
}


#endif // SISTRIPAPPROXIMATECLUSTER_CLASSES_H
