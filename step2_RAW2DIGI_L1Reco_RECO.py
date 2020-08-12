# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions 103X_dataRun2_Prompt_v2 -s RAW2DIGI,L1Reco,RECO --process reRECO -n 30 --data --era Run2_2018_pp_on_AA --eventcontent AOD --runUnscheduled --scenario pp --datatier AOD --repacked --filein file:out.root --fileout file:step2.root --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('reRECO',eras.Run2_2018_pp_on_AA)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_DataMapper_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("StripsRAW_v2.root"))

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/eos/cms/store/hidata/HIRun2018A/HIMinimumBias5/RAW/v1/000/326/573/00000/C4CDB29C-62C9-AF4D-B2A3-5D9793BE3832.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:30'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

RecoHiTrackerRECO = cms.PSet(
    outputCommands = cms.untracked.vstring(
	'keep *_*siStrip*_*_*', 
	'keep *_*SiStrip*_*_*',
        'keep *_*rawData*_*_*',
        'keep *_*RawData*_*_*',
        'keep *_*rawStep*_*_*',
        'keep *_*ApproximateRecHit*_*_*'
    )
)

process.AODEventContent.outputCommands.extend(RecoHiTrackerRECO.outputCommands)

process.AODoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AOD'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(31457280),
    fileName = cms.untracked.string('file:step2.root'),
    outputCommands = process.AODEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_v2', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODoutput_step = cms.EndPath(process.AODoutput)


process.load('RecoLocalTracker.SiStripClusterizer.SiStripClusters2ApproxClusters_cfi')
process.approxClusters = cms.Path(process.SiStripClusters2ApproxClusters)
process.load('RecoLocalTracker.SiStripClusterizer.SiStripClusters2ApproxClustersv2_cfi')
process.approxClustersv2 = cms.Path(process.SiStripClusters2ApproxClustersv2)
process.load('RecoLocalTracker.SiStripClusterizer.SiStripApproxClusters2Clusters_cfi')
process.load('RecoLocalTracker.SiStripRecHitConverter.SiStripRecHitConverter_cfi')
process.newSiStripMatchedRecHits = process.siStripMatchedRecHits.clone(
  ClusterProducer=cms.InputTag("SiStripApproxClusters2Clusters")
)
process.newClusters = cms.Path(process.SiStripApproxClusters2Clusters*process.newSiStripMatchedRecHits)

process.load('EventFilter.SiStripRawToDigi.SiStripDigiToRaw_cfi')
process.rawStep = process.SiStripDigiToRaw.clone(
InputDigis=cms.InputTag('siStripDigis', 'ZeroSuppressed'),
RawDataTag = cms.InputTag('StripRawDataCollector')
 )

process.load('EventFilter.RawDataCollector.rawDataCollector_cfi')
process.StripRawDataCollector = process.rawDataCollector.clone(RawCollectionList = cms.VInputTag( cms.InputTag('rawStep')))

process.load('EventFilter.SiPixelRawToDigi.SiPixelDigiToRaw_cfi')
process.rawStepPix = process.siPixelRawData.clone(
InputLabel=cms.InputTag('siPixelDigis'),
 )
process.PixelRawDataCollector = process.rawDataCollector.clone(RawCollectionList = cms.VInputTag( cms.InputTag('rawStepPix')))

process.load('EventFilter.HcalRawToDigi.HcalDigiToRaw_cfi')
process.rawStepHCAL = process.hcalRawDataVME.clone(
    HBHE = cms.untracked.InputTag("hcalDigis"),
    HF = cms.untracked.InputTag("hcalDigis"),
    HO = cms.untracked.InputTag("hcalDigis"),
    ZDC = cms.untracked.InputTag("hcalDigis"),
    TRIG =  cms.untracked.InputTag("hcalDigis")
)
process.HCALRawDataCollector = process.rawDataCollector.clone(RawCollectionList = cms.VInputTag( cms.InputTag('rawStepHCAL')))

process.load('EventFilter.ESDigiToRaw.esDigiToRaw_cfi')
process.rawStepES = process.esDigiToRaw.clone(
Label = cms.string('ecalPreshowerDigis'),
)
process.ESRawDataCollector = process.rawDataCollector.clone(RawCollectionList = cms.VInputTag( cms.InputTag('rawStepES')))

process.rawPath = cms.Path(process.rawStep*process.rawStepPix*process.rawStepHCAL*process.rawStepES*process.StripRawDataCollector*process.PixelRawDataCollector*process.HCALRawDataCollector*process.ESRawDataCollector)

#rechit converter
process.load('RecoLocalTracker.SiStripRecHitConverter.SiStripRecHitConverter_cfi')
process.ApproximateRecHits = process.approxSiStripMatchedRecHits.clone(
     ClusterProducer = 'SiStripClusters2ApproxClustersv2' 
)
process.ApproximateRecHitsPath = cms.Path(process.ApproximateRecHits)


# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.approxClusters,process.approxClustersv2,process.ApproximateRecHitsPath,process.newClusters,process.rawPath, process.endjob_step,process.AODoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process, new="rawDataMapperByLabel", old="rawDataCollector")

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
