import FWCore.ParameterSet.Config as cms


ecalShiftParticleFlow = cms.EDProducer('EcalEscaleShiftPFProducer',
                                           src    = cms.InputTag('particleFlow'),
                                           removePreshower = cms.bool(True), 
                                           scaleEB = cms.double(0.9928),
                                           scaleEE = cms.double(1.1537), 
)

