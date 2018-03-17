#auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3_Andre --data --runUnscheduled --conditions auto:phase1_2017_realistic -s RAW2DIGI,L1Reco,RECO --repacked --datatier GEN-SIM-RECO -n 2 --era Run2_2017_pp_on_XeXe --eventcontent RECO --filein file:/eos/cms/tier0/store/hidata/XeXeRun2017/HIMinimumBias1/RAW/v1/000/304/849/00000/10659883-3FAF-E711-B440-02163E014494.root --fileout file:step3.root --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('REPACK',eras.Run2_2018_pp_on_AA)
#process = cms.Process('REPACK',eras.Run2_HI)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#process.Timing = cms.Service("Timing",
#  summaryOnly = cms.untracked.bool(False),
#  useJobReport = cms.untracked.bool(True)
#)

# Input source
#process.source = cms.Source("NewEventStreamFileReader",
#    filenames = cms.untracked.vstring('')
#)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'file:/data/abaty/XeXeData/Run304899_lumi33_5000EvtRAW.root'),
        '/store/user/mnguyen//Hydjet_Quenched_MB_1000//fifthMB.root'),
#    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch///store/hidata/HIRun2015/HITrackerVirginRaw/RAW/v1/000/262/495/00000/82CB9DA4-5493-E511-9E68-02163E01457B.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3_Andre nevts:2'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    outputCommands = cms.untracked.vstring('keep *',
       'drop *_*_*_REPACK',
       'keep *_myRawDataCollector*_*_*',
       'keep *_rawDataRepacker_*_*',
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('file:/afs/cern.ch/work/a/abaty/public/forPeople/for2018Reco/output.root'),
    #outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

process.siPixelRawData = cms.EDProducer("SiPixelDigiToRaw",
    Timing = cms.untracked.bool(False),
    InputLabel = cms.InputTag("siPixelDigis"),
##  Use phase1
#    UsePhase1 = cms.bool(True),
)
process.siStripRawData = cms.EDProducer(
    "SiStripDigiToRawModule",
    InputModuleLabel = cms.string('siStripDigis'),
    InputDigiLabel = cms.string('ZeroSuppressed'),
    FedReadoutMode = cms.string('ZERO_SUPPRESSED'),
    UseFedKey = cms.bool(False),
    UseWrongDigiType = cms.bool(False),
    CopyBufferHeader = cms.bool(False),
    RawDataTag = cms.InputTag('rawDataCollector')
    )
process.hcalRawData = cms.EDProducer("HcalDigiToRaw",
    #HBHE = cms.untracked.InputTag("hcalDigis"),
    HF = cms.untracked.InputTag("hcalDigis"),
    #HO = cms.untracked.InputTag("hcalDigis"),
    #ZDC = cms.untracked.InputTag("hcalUnsuppressedDigis"),
    #TRIG =  cms.untracked.InputTag("hcalTriggerPrimitiveDigis")
)
process.myRawDataCollector = cms.EDProducer("RawDataCollectorByLabel",
    verbose = cms.untracked.int32(0),     # 0 = quiet, 1 = collection list, 2 = FED list
    RawCollectionList = cms.VInputTag( cms.InputTag('hcalRawData'),
                   #                    cms.InputTag('siStripRawData'),
                   #                    cms.InputTag('siPixelRawData'),
    ),
)


# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.digi2Raw = cms.Path(process.siPixelRawData*process.hcalRawData*process.siStripRawData*process.myRawDataCollector)
#process.digi2Raw = cms.Path(process.siStripRawData*process.myRawDataCollector)
#process.L1Reco_step = cms.Path(process.L1Reco)
#process.load("RecoLocalCalo.HcalRecProducers.HFPhase1Reconstructor_cfi")
#process.reconstruction_step = cms.Path(process.reconstruction_trackingOnly*process.hfreco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)





# Schedule definition
#process.dump=cms.EDAnalyzer('EventContentAnalyzer')
#process.dumpPath = cms.Path(process.dump)
process.schedule = cms.Schedule(process.raw2digi_step,process.digi2Raw,process.endjob_step,process.RECOoutput_step)
#process.schedule = cms.Schedule(process.raw2digi_step,process.digi2Raw,process.reconstruction_step,process.dumpPath,process.endjob_step,process.RECOoutput_step)
#from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
#associatePatAlgosToolsTask(process)

#from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
#MassReplaceInputTag(process)

#do not add changes to your config after this point (unless you know what you are doing)
#from FWCore.ParameterSet.Utilities import convertToUnscheduled
#process=convertToUnscheduled(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
#from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
#process = customiseEarlyDelete(process)
# End adding early deletion
