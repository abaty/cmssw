import FWCore.ParameterSet.Config as cms

approxSiStripMatchedRecHits = cms.EDProducer("ApproxSiStripRecHitConverter",
    ClusterProducer    = cms.InputTag('SiStripClusters2ApproxClusters'),
    StripCPE            = cms.ESInputTag('StripCPEfromTrackAngleESProducer:StripCPEfromTrackAngle'),
    Matcher             = cms.ESInputTag('SiStripRecHitMatcherESProducer:StandardMatcher'),
    siStripQualityLabel = cms.ESInputTag(''),
    useSiStripQuality = cms.bool(False),
    MaskBadAPVFibers  = cms.bool(False),
    rphiRecHits    = cms.string('rphiRecHit'),
    stereoRecHits  = cms.string('stereoRecHit'),
    matchedRecHits = cms.string('matchedRecHit'),
    VerbosityLevel = cms.untracked.int32(1)
)
