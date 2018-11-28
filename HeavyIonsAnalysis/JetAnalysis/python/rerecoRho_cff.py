import FWCore.ParameterSet.Config as cms

# import kt jets for rho estimators
from HeavyIonsAnalysis.JetAnalysis.ktPFJets_cfi import PFTowers, kt4PFJets, kt4PFJetsForRho

from RecoHI.HiJetAlgos.hiFJRhoProducer import hiFJRhoProducer
from RecoHI.HiJetAlgos.hiFJGridEmptyAreaCalculator_cff import hiFJGridEmptyAreaCalculator

rhoSequence = cms.Sequence(
    PFTowers +
    kt4PFJets +
    kt4PFJetsForRho +
    hiFJRhoProducer +
    hiFJGridEmptyAreaCalculator
)
