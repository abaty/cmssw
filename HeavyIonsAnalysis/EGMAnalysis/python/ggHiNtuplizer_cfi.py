import FWCore.ParameterSet.Config as cms

ggHiNtuplizer = cms.EDAnalyzer("ggHiNtuplizer",
    doGenParticles = cms.bool(False),
    doElectrons = cms.bool(True),
    doPhotons = cms.bool(True),
    doMuons = cms.bool(True),

    isParticleGun = cms.bool(False),

    pileupSrc = cms.InputTag("addPileupInfo"),
    genParticleSrc = cms.InputTag("genParticles"),
    vertexSrc = cms.InputTag("offlineSlimmedPrimaryVertices"),
    rhoSrc = cms.InputTag("fixedGridRhoFastjetAll"),
    electronSrc = cms.InputTag("slimmedElectrons"),
    photonSrc = cms.InputTag("slimmedPhotons"),
    muonSrc = cms.InputTag("slimmedMuons"),
    beamSpotSrc = cms.InputTag('offlineBeamSpot'),
    conversionsSrc = cms.InputTag('reducedEgamma', 'reducedConversions', 'PAT'),
)
