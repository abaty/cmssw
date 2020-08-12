import FWCore.ParameterSet.Config as cms

SiStripClusters2ApproxClustersv2 = cms.EDProducer("SiStripClusters2ApproxClustersv2",
	inputClusters = cms.InputTag("siStripClusters")
)

