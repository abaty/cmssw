import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.JetAnalysis.rerecoTracks_cff import highPurityTracks

highPurityTracks.src = 'hiGeneralTracks'

from HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi import (
    ggHiNtuplizer, ggHiNtuplizerGED)

ggHiNtuplizer.recoPhotonSrc            = 'photons'
ggHiNtuplizer.gsfElectronLabel         = 'gedGsfElectrons'
ggHiNtuplizer.recoPhotonHiIsolationMap = 'photonIsolationHIProducer'

ggHiNtuplizerGED.recoPhotonSrc            = 'gedPhotonsTmp'
ggHiNtuplizerGED.recoPhotonHiIsolationMap = 'photonIsolationHIProducerGED'

from HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi import (
    pfcandAnalyzer, pfcandAnalyzerCS)

pfcandAnalyzer.pfCandidateLabel = "particleFlowTmp"
pfcandAnalyzer.genLabel = "hiGenParticles"

pfcandAnalyzerCS.genLabel = "hiGenParticles"

from HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi import (
    hiEvtAnalyzer)

hiEvtAnalyzer.Vertex = "hiSelectedVertex"

from HeavyIonsAnalysis.Configuration.collisionEventSelection_cff import(
    primaryVertexFilter)

primaryVertexFilter.src = "hiSelectedVertex"
