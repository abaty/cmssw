import FWCore.ParameterSet.Config as cms

SiStripApproxClusters2Clusters = cms.EDProducer("SiStripApproxClusters2Clusters",
	inputClusters = cms.InputTag("SiStripClusters2ApproxClusters")
)

