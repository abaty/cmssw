import FWCore.ParameterSet.Config as cms

# import and alias HI calo jet producers
from HeavyIonsAnalysis.JetAnalysis.akCaloJets_cfi import (
    ak1CaloJets, akPu1CaloJets,
    ak2CaloJets, akPu2CaloJets,
    ak3CaloJets, akPu3CaloJets,
    ak4CaloJets, akPu4CaloJets,
    ak5CaloJets, akPu5CaloJets,
    ak6CaloJets, akPu6CaloJets)

# import and alias HI particle flow jet producers
from HeavyIonsAnalysis.JetAnalysis.akPFJets_cfi import (
    ak1HIPFJets, akPu1PFJets, akCs1HIPFJets,
    ak2HIPFJets, akPu2PFJets, akCs2HIPFJets,
    ak3HIPFJets, akPu3PFJets, akCs3HIPFJets,
    ak4HIPFJets, akPu4PFJets, akCs4HIPFJets,
    ak5HIPFJets, akPu5PFJets, akCs5HIPFJets,
    ak6HIPFJets, akPu6PFJets, akCs6HIPFJets)

ak1PFJets = cms.EDAlias(ak1HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak2PFJets = cms.EDAlias(ak2HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak3PFJets = cms.EDAlias(ak3HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak4PFJets = cms.EDAlias(ak4HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak5PFJets = cms.EDAlias(ak5HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak6PFJets = cms.EDAlias(ak6HIPFJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))

akCs1PFJets = cms.EDAlias(akCs1HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
akCs2PFJets = cms.EDAlias(akCs2HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
akCs3PFJets = cms.EDAlias(akCs3HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
akCs4PFJets = cms.EDAlias(akCs4HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
akCs5PFJets = cms.EDAlias(akCs5HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
akCs6PFJets = cms.EDAlias(akCs6HIPFJets = cms.VPSet(
    cms.PSet(type = cms.string('recoPFJets')),
    cms.PSet(type = cms.string('recoPFCandidates'))))
