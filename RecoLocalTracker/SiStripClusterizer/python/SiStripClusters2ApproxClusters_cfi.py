import FWCore.ParameterSet.Config as cms

SiStripClusters2ApproxClusters = cms.EDProducer("SiStripClusters2ApproxClusters",
	inputClusters = cms.InputTag("siStripClusters")
)

