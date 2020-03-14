import FWCore.ParameterSet.Config as cms

# import and alias kt jets for rho estimators
from HeavyIonsAnalysis.JetAnalysis.ktPFJets_cfi import (
    HIPFTowers, kt4HIPFJets, kt4HIPFJetsForRho)

PFTowers = cms.EDAlias(HIPFTowers = cms.VPSet(cms.PSet(
    type = cms.string('CaloTowersSorted'))))
kt4PFJets = cms.EDAlias(kt4HIPFJets = cms.VPSet(cms.PSet(
    type = cms.string('recoPFJets'))))
kt4PFJetsForRho = cms.EDAlias(kt4HIPFJetsForRho = cms.VPSet(cms.PSet(
    type = cms.string('recoPFJets'))))

from RecoHI.HiJetAlgos.hiFJRhoProducer import hiFJRhoProducer
from RecoHI.HiJetAlgos.hiFJGridEmptyAreaCalculator_cff import hiFJGridEmptyAreaCalculator

rhoSequence = cms.Sequence(
    HIPFTowers +
    kt4HIPFJets +
    kt4HIPFJetsForRho +
    hiFJRhoProducer +
    hiFJGridEmptyAreaCalculator
)
