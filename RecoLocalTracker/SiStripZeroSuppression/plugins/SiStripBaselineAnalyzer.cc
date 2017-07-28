// -*- C++ -*-
//
// Package:    SiStripBaselineAnalyzer
// Class:      SiStripBaselineAnalyzer
// 
/**\class SiStripBaselineAnalyzer SiStripBaselineAnalyzer.cc Validation/SiStripAnalyzer/src/SiStripBaselineAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Ivan Amos Cali
//         Created:  Mon Jul 28 14:10:52 CEST 2008
//
//
 

// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"

#include "DataFormats/SiStripDigi/interface/SiStripProcessedRawDigi.h"
#include "DataFormats/SiStripDigi/interface/SiStripRawDigi.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripClusterCollection.h"

#include "CondFormats/SiStripObjects/interface/SiStripPedestals.h"
#include "CondFormats/DataRecord/interface/SiStripPedestalsRcd.h"

#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripPedestalsSubtractor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripCommonModeNoiseSubtractor.h"
#include "RecoLocalTracker/SiStripZeroSuppression/interface/SiStripRawProcessingFactory.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "DataFormats/Provenance/interface/RunLumiEventNumber.h"

//ROOT inclusion
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TList.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "THStack.h"


//
// class decleration
//

class SiStripBaselineAnalyzer : public edm::EDAnalyzer {
   public:
      explicit SiStripBaselineAnalyzer(const edm::ParameterSet&);
      ~SiStripBaselineAnalyzer();


   private:
      virtual void beginJob() override ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override ;
      
	  std::auto_ptr<SiStripPedestalsSubtractor>   subtractorPed_;
          edm::ESHandle<SiStripPedestals> pedestalsHandle;
          std::vector<int> pedestals;
          uint32_t peds_cache_id;

          bool plotClusters_;
          bool plotBaseline_;
          bool plotBaselinePoints_;
          bool plotRawDigi_;
          bool plotAPVCM_;
          bool plotPedestals_;
	  
          edm::InputTag srcBaseline_;
          edm::InputTag srcBaselinePoints_;
          edm::InputTag srcAPVCM_;
	  edm::InputTag srcProcessedRawDigi_;
	  edm::InputTag srcClusters_;
      
          edm::Service<TFileService> fs_;
 
 
//	  TH1F* h1BadAPVperEvent_;
	  
          TH1F* h1RawDigis_;
	  TH1F* h1ProcessedRawDigis_;
	  TH1F* h1Baseline_;
	  TH1F* h1Clusters_;
//          TH1F* h1APVCM_;
//          TH1F* h1Pedestals_;	  

          TH1I* h1ClusterMult_; 
          TH1I* h1ClusterCharge_;
          TH1I* h1ClusterWidth_; 
          TH1I* h1ClusterMean_; 
          TH1I* h1ClusterSigma_; 
	  
//	  TCanvas* Canvas_;
//	  std::vector<TH1F> vProcessedRawDigiHisto_;
//	  std::vector<TH1F> vBaselineHisto_;
//          std::vector<TH1F> vBaselinePointsHisto_;
//	  std::vector<TH1F> vClusterHisto_;
	  
	  uint16_t nModuletoDisplay_;
	  uint16_t actualModule_;
};


SiStripBaselineAnalyzer::SiStripBaselineAnalyzer(const edm::ParameterSet& conf){
   
  srcBaseline_ =  conf.getParameter<edm::InputTag>( "srcBaseline" );
  srcBaselinePoints_ = conf.getParameter<edm::InputTag>( "srcBaselinePoints" );
  srcProcessedRawDigi_ =  conf.getParameter<edm::InputTag>( "srcProcessedRawDigi" );
  srcAPVCM_ =  conf.getParameter<edm::InputTag>( "srcAPVCM" );
  srcClusters_ =  conf.getParameter<edm::InputTag>( "srcClusters" );
  subtractorPed_ = SiStripRawProcessingFactory::create_SubtractorPed(conf.getParameter<edm::ParameterSet>("Algorithms"));
  nModuletoDisplay_ = conf.getParameter<uint32_t>( "nModuletoDisplay" );
  plotClusters_ = conf.getParameter<bool>( "plotClusters" );
  plotBaseline_ = conf.getParameter<bool>( "plotBaseline" );
  plotBaselinePoints_ = conf.getParameter<bool>( "plotBaselinePoints" );
  plotRawDigi_ = conf.getParameter<bool>( "plotRawDigi" );
  plotAPVCM_ = conf.getParameter<bool>( "plotAPVCM" );
  plotPedestals_ = conf.getParameter<bool>( "plotPedestals" );

/*
  h1BadAPVperEvent_ = fs_->make<TH1F>("BadAPV/Event","BadAPV/Event", 2001, -0.5, 2000.5);
  h1BadAPVperEvent_->SetXTitle("# Modules with Bad APVs");
  h1BadAPVperEvent_->SetYTitle("Entries");
  h1BadAPVperEvent_->SetLineWidth(2);
  h1BadAPVperEvent_->SetLineStyle(2);

  h1APVCM_ = fs_->make<TH1F>("APVCM","APVCM", 2048, -1023.5, 1023.5);
  h1APVCM_->SetXTitle("APV CM [adc]");
  h1APVCM_->SetYTitle("Entries");
  h1APVCM_->SetLineWidth(2);
  h1APVCM_->SetLineStyle(2);

  h1Pedestals_ = fs_->make<TH1F>("Pedestals","Pedestals", 2048, -1023.5, 1023.5);
  h1Pedestals_->SetXTitle("Pedestals [adc]");
  h1Pedestals_->SetYTitle("Entries");
  h1Pedestals_->SetLineWidth(2);
  h1Pedestals_->SetLineStyle(2);
*/  
  h1ClusterMult_ = fs_->make<TH1I>("ClusterMult","Cluster Multiplicity;nClusters;nEvents", 100, 0, 500000);
  h1ClusterCharge_ = fs_->make<TH1I>("ClusterCharge","Cluster Charge;Cluster Charge;nCluster", 100, 0, 5000);
  h1ClusterWidth_ = fs_->make<TH1I>("ClusterWidth","Cluster Width;Cluster Width;nCluster", 128, 0, 128);
  h1ClusterMean_ = fs_->make<TH1I>("ClusterMean","Cluster Mean;Cluster Mean;nCluster", 128, 0, 128);
  h1ClusterSigma_ = fs_->make<TH1I>("ClusterSigma","Cluster Sigma;Cluster Sigma;nCluster", 60, 0, 50);

}


SiStripBaselineAnalyzer::~SiStripBaselineAnalyzer()
{
 
   

}

void
SiStripBaselineAnalyzer::analyze(const edm::Event& e, const edm::EventSetup& es)
{
   bool ClusterDists = false;
   using namespace edm;
   char detIds[20];
   char evs[20];
   char runs[20];    
   

   TFileDirectory sdProcessedRawDigis_= fs_->mkdir("ProcessedRawDigis");
   TFileDirectory sdRawDigis_= fs_->mkdir("RawDigis");
   TFileDirectory sdBaseline_= fs_->mkdir("Baseline");
//   TFileDirectory sdBaselinePoints_= fs_->mkdir("BaselinePoints");
   TFileDirectory sdClusters_= fs_->mkdir("Clusters");
  
   //load processed raw digis (after ped subtraction is done) and event info 
   edm::RunNumber_t const run = e.id().run();
   edm::EventNumber_t const event = e.id().event();
   subtractorPed_->init(es);//pedestals
   //rawdigis 
   edm::Handle< edm::DetSetVector<SiStripRawDigi> > moduleRawDigi;
   e.getByLabel(srcProcessedRawDigi_,moduleRawDigi);
   //clusters
   edm::Handle<edmNew::DetSetVector<SiStripCluster> > clusters;
   if(plotClusters_){
     e.getByLabel(srcClusters_,clusters);
   //	edm::InputTag clusLabel("siStripClusters");
   //	e.getByLabel(clusLabel, clusters);
   }
   //baselines
   edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleBaseline;
   if(plotBaseline_) e.getByLabel(srcBaseline_, moduleBaseline); 
   edm::DetSetVector<SiStripProcessedRawDigi>::const_iterator itDSBaseline;
   if(plotBaseline_) itDSBaseline = moduleBaseline->begin();
  
   //loop through detectors
   edm::DetSetVector<SiStripRawDigi>::const_iterator itRawDigis = moduleRawDigi->begin();
   for (; itRawDigis != moduleRawDigi->end(); ++itRawDigis) {
     if(actualModule_ > nModuletoDisplay_) return;
     uint32_t detId = itRawDigis->id;
      if(plotBaseline_){
	if(itDSBaseline->id != detId){
		itDSBaseline = moduleBaseline->find(detId);
                if(itDSBaseline->id != detId){ if(plotBaseline_)itDSBaseline++; continue;}
//                else std::cout << "Resynched..." << std::endl;
	}	  
      }
     actualModule_++;
     
     //loop through all APVs in detector and get info for formatting plot size
     edm::DetSet<SiStripRawDigi>::const_iterator itRaw = itRawDigis->begin(); 
     bool restAPV[6] = {0,0,0,0,0,0};
     int strip =0, totADC=0;
     int minAPVRes = 7, maxAPVRes = -1;
     for(;itRaw != itRawDigis->end(); ++itRaw, ++strip){
           float adc = itRaw->adc();
           totADC+= adc;
           if(strip%128 ==127){
     		//std::cout << "totADC " << totADC << std::endl;
             int APV = strip/128;
             if(totADC!= 0){
     	    	restAPV[APV] = true;
     			totADC =0;
     			if(APV>maxAPVRes) maxAPVRes = APV;
     			if(APV<minAPVRes) minAPVRes = APV;
     	      }
           }
     }

     //set plot size, name, cosmetics
     uint16_t bins =768;
     float minx = -0.5, maxx=767.5;
     if(minAPVRes !=7){
     	minx = minAPVRes * 128 -0.5;
     	maxx = maxAPVRes * 128 + 127.5;
     	bins = maxx-minx;
     }
     sprintf(detIds,"%ul", detId);
     sprintf(evs,"%llu", event);
     sprintf(runs,"%u", run);
     char* dHistoName = Form("Id%s_run%s_ev%s",detIds, runs, evs);
     h1ProcessedRawDigis_ = sdProcessedRawDigis_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
     h1ProcessedRawDigis_->SetXTitle("strip#");  
     h1ProcessedRawDigis_->SetYTitle("ADC");
     h1ProcessedRawDigis_->SetMaximum(1024.);
     h1ProcessedRawDigis_->SetMinimum(-300.);
     h1ProcessedRawDigis_->SetLineWidth(2);
     h1RawDigis_ = sdRawDigis_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
     h1RawDigis_->SetXTitle("strip#");  
     h1RawDigis_->SetYTitle("ADC");
     h1RawDigis_->SetMaximum(1024.);
     h1RawDigis_->SetMinimum(-300.);
     h1RawDigis_->SetLineWidth(2);
     h1Clusters_ = sdClusters_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
     h1Clusters_->SetXTitle("strip#");  
     h1Clusters_->SetYTitle("ADC");
     h1Clusters_->SetMaximum(1024.);
     h1Clusters_->SetMinimum(-300.);
     h1Clusters_->SetLineWidth(2);
     h1Baseline_ = sdBaseline_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
     h1Baseline_->SetXTitle("strip#");
     h1Baseline_->SetYTitle("ADC");
     h1Baseline_->SetMaximum(1024.);
     h1Baseline_->SetMinimum(-300.);
     h1Baseline_->SetLineWidth(2);
     h1Baseline_->SetLineStyle(2);
     h1Baseline_->SetLineColor(2);
     
     //loop through and get raw digis into plots
     edm::DetSet<SiStripProcessedRawDigi>::const_iterator  itBaseline;
     if(plotBaseline_) itBaseline = itDSBaseline->begin(); 
     itRaw = itRawDigis->begin(); 
     strip=0;
     for(; itRaw != itRawDigis->end(); ++itRaw, ++strip){
       h1RawDigis_->Fill(strip,itRaw->adc());
     }
     //processed raw
     std::vector<int16_t> ProcessedRawDigis(itRawDigis->size());
     subtractorPed_->subtract( *itRawDigis, ProcessedRawDigis);
     strip =0;    
     for(std::vector<int16_t>::const_iterator itProcessedRawDigis = ProcessedRawDigis.begin();itProcessedRawDigis != ProcessedRawDigis.end(); itProcessedRawDigis++){ 
      	if(restAPV[strip/128]){
          float adc = *itProcessedRawDigis;     
          h1ProcessedRawDigis_->Fill(strip, adc);
          if(plotBaseline_){//baselines
            h1Baseline_->Fill(strip, itBaseline->adc()); 
            ++itBaseline;
          }
        }
       ++strip;
      }
      if(plotBaseline_) ++itDSBaseline; 
 
      //clusters	  
      if(plotClusters_){
          int nclust = 0;
	  edmNew::DetSetVector<SiStripCluster>::const_iterator itClusters = clusters->begin();
	  for ( ; itClusters != clusters->end(); ++itClusters ){
		for ( edmNew::DetSet<SiStripCluster>::const_iterator clus =	itClusters->begin(); clus != itClusters->end(); ++clus){
		  if(itClusters->id() == detId){
		    int firststrip = clus->firstStrip();
	            //std::cout << "Found cluster in detId " << detId << " " << firststrip << " " << clus->amplitudes().size() << " -----------------------------------------------" << std::endl;		
     		    strip=0;
		    for( auto itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
		      h1Clusters_->Fill(firststrip+strip, *itAmpl);
		      ++strip;
		    }
		  }
                  
                  //cluster plots from here on
                   
                  if(ClusterDists == false){
		    nclust++;

     		    int strip2=0;
                    double charge = 0;
                    double mean = 0;
                    double sigma = 0;
		    for( auto itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
                      charge += *itAmpl;
		      ++strip2;
                      mean += strip2*(*itAmpl);
		      sigma += strip2*strip2*(*itAmpl);
		    }
                    h1ClusterCharge_->Fill(charge);
                    h1ClusterWidth_->Fill(strip2);
                    mean = mean/charge;
                    h1ClusterMean_->Fill(mean);
                    sigma = TMath::Power((sigma/charge-mean*mean),0.5);
                    h1ClusterSigma_->Fill(sigma);
                  }              
		}
	  }
        if(ClusterDists==false)
        {
          h1ClusterMult_->Fill(nclust); 
          ClusterDists = true;
        }
      }
   } 
/*
   bool ClusterDists = false;
   using namespace edm;
   if(plotPedestals_&&actualModule_ ==0){
      uint32_t p_cache_id = es.get<SiStripPedestalsRcd>().cacheIdentifier();
      if(p_cache_id != peds_cache_id) {
	es.get<SiStripPedestalsRcd>().get(pedestalsHandle);
	peds_cache_id = p_cache_id;
      }
      
      
      std::vector<uint32_t> detIdV;
      pedestalsHandle->getDetIds(detIdV);
      
      for(uint32_t i=0; i < detIdV.size(); ++i){
        pedestals.clear();
        SiStripPedestals::Range pedestalsRange = pedestalsHandle->getRange(detIdV[i]);
        pedestals.resize((pedestalsRange.second- pedestalsRange.first));
	pedestalsHandle->allPeds(pedestals, pedestalsRange);
	for(uint32_t it=0; it < pedestals.size(); ++it) h1Pedestals_->Fill(pedestals[it]);
      }
   }

   if(plotAPVCM_){
     edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleCM;
     edm::InputTag CMLabel("siStripZeroSuppression:APVCM");
     e.getByLabel(srcAPVCM_,moduleCM);

     edm::DetSetVector<SiStripProcessedRawDigi>::const_iterator itCMDetSetV =moduleCM->begin();
     for (; itCMDetSetV != moduleCM->end(); ++itCMDetSetV){  
       edm::DetSet<SiStripProcessedRawDigi>::const_iterator  itCM= itCMDetSetV->begin();
       for(;itCM != itCMDetSetV->end(); ++itCM) h1APVCM_->Fill(itCM->adc());
     }
   }
   if(!plotRawDigi_) return;
   subtractorPed_->init(es); 
 
   edm::Handle< edm::DetSetVector<SiStripRawDigi> > moduleRawDigi;
   e.getByLabel(srcProcessedRawDigi_,moduleRawDigi);
 
   edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleBaseline;
   if(plotBaseline_) e.getByLabel(srcBaseline_, moduleBaseline); 

//here (2 lines)
   edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleBaselinePoints;
   if(plotBaselinePoints_) e.getByLabel(srcBaselinePoints_, moduleBaselinePoints); 
   
   edm::Handle<edmNew::DetSetVector<SiStripCluster> > clusters;
   if(plotClusters_){
   	edm::InputTag clusLabel("siStripClusters");
   	e.getByLabel(clusLabel, clusters);
   }
   
   char detIds[20];
   char evs[20];
   char runs[20];    
   

   TFileDirectory sdProcessedRawDigis_= fs_->mkdir("ProcessedRawDigis");
   TFileDirectory sdRawDigis_= fs_->mkdir("RawDigis");
   TFileDirectory sdBaseline_= fs_->mkdir("Baseline");
   TFileDirectory sdBaselinePoints_= fs_->mkdir("BaselinePoints");
   TFileDirectory sdClusters_= fs_->mkdir("Clusters");
   

//here
   edm::DetSetVector<SiStripProcessedRawDigi>::const_iterator itDSBaseline;
   if(plotBaseline_) itDSBaseline = moduleBaseline->begin();
   edm::DetSetVector<SiStripRawDigi>::const_iterator itRawDigis = moduleRawDigi->begin();
   
   uint32_t NBabAPVs = moduleRawDigi->size();     
   h1BadAPVperEvent_->Fill(NBabAPVs);
   
   for (; itRawDigis != moduleRawDigi->end(); ++itRawDigis) {
      if(actualModule_ > nModuletoDisplay_) return;
      uint32_t detId = itRawDigis->id;
	  
      if(plotBaseline_){
//	std::cout << "bas id: " << itDSBaseline->id << " raw id: " << detId << std::endl;
	if(itDSBaseline->id != detId){
		itDSBaseline = moduleBaseline->find(detId);
                if(itDSBaseline->id != detId){ if(plotBaseline_)itDSBaseline++; continue;}
//                else std::cout << "Resynched..." << std::endl;
	}	  
      }
      
    
      actualModule_++;
      edm::RunNumber_t const run = e.id().run();
      edm::EventNumber_t const event = e.id().event();
      //std::cout << "processing module N: " << actualModule_<< " detId: " << detId << " event: "<< event << std::endl; 
	 

	  
      edm::DetSet<SiStripRawDigi>::const_iterator itRaw = itRawDigis->begin(); 
      bool restAPV[6] = {0,0,0,0,0,0};
      int strip =0, totADC=0;
      int minAPVRes = 7, maxAPVRes = -1;
      for(;itRaw != itRawDigis->end(); ++itRaw, ++strip){
	    float adc = itRaw->adc();
	    totADC+= adc;
	    if(strip%128 ==127){
      		//std::cout << "totADC " << totADC << std::endl;
	      int APV = strip/128;
	      if(totADC!= 0){
      	    	restAPV[APV] = true;
      			totADC =0;
      			if(APV>maxAPVRes) maxAPVRes = APV;
      			if(APV<minAPVRes) minAPVRes = APV;
      	      }
	    }
      }

      uint16_t bins =768;
      float minx = -0.5, maxx=767.5;
      if(minAPVRes !=7){
      	minx = minAPVRes * 128 -0.5;
      	maxx = maxAPVRes * 128 + 127.5;
      	bins = maxx-minx;
      }
      

      sprintf(detIds,"%ul", detId);
      sprintf(evs,"%llu", event);
      sprintf(runs,"%u", run);
      char* dHistoName = Form("Id%s_run%s_ev%s",detIds, runs, evs);
      h1ProcessedRawDigis_ = sdProcessedRawDigis_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
      h1RawDigis_ = sdRawDigis_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 

      edm::DetSet<SiStripRawDigi>::const_iterator itRaw2 = itRawDigis->begin(); 
      int strip2=0;
      for(; itRaw2 != itRawDigis->end(); ++itRaw2, ++strip2){
            h1RawDigis_->Fill(strip2,itRaw2->adc());
      }
      
      if(plotBaseline_){
	h1Baseline_ = sdBaseline_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx); 
        h1Baseline_->SetXTitle("strip#");
	h1Baseline_->SetYTitle("ADC");
	h1Baseline_->SetMaximum(1024.);
	h1Baseline_->SetMinimum(-300.);
	h1Baseline_->SetLineWidth(2);
	h1Baseline_->SetLineStyle(2);
	h1Baseline_->SetLineColor(2);
      }

      if(plotClusters_){
        h1Clusters_ = sdClusters_.make<TH1F>(dHistoName,dHistoName, bins, minx, maxx);
	  
        h1Clusters_->SetXTitle("strip#");
        h1Clusters_->SetYTitle("ADC");
        h1Clusters_->SetMaximum(1024.);
        h1Clusters_->SetMinimum(-300.);
        h1Clusters_->SetLineWidth(2);
	h1Clusters_->SetLineStyle(2);
	h1Clusters_->SetLineColor(3);
      }

      h1ProcessedRawDigis_->SetXTitle("strip#");  
      h1ProcessedRawDigis_->SetYTitle("ADC");
      h1ProcessedRawDigis_->SetMaximum(1024.);
      h1ProcessedRawDigis_->SetMinimum(-300.);
      h1ProcessedRawDigis_->SetLineWidth(2);
      h1RawDigis_->SetXTitle("strip#");  
      h1RawDigis_->SetYTitle("ADC");
      h1RawDigis_->SetMaximum(1024.);
      h1RawDigis_->SetMinimum(-300.);
      h1RawDigis_->SetLineWidth(2);
      
      std::vector<int16_t> ProcessedRawDigis(itRawDigis->size());
      subtractorPed_->subtract( *itRawDigis, ProcessedRawDigis);

      edm::DetSet<SiStripProcessedRawDigi>::const_iterator  itBaseline;
      if(plotBaseline_) itBaseline = itDSBaseline->begin(); 
      
      std::vector<int16_t>::const_iterator itProcessedRawDigis;
     
      strip =0;    
      for(itProcessedRawDigis = ProcessedRawDigis.begin();itProcessedRawDigis != ProcessedRawDigis.end(); itProcessedRawDigis++){ 
       	if(restAPV[strip/128]){
	  float adc = *itProcessedRawDigis;     
	  h1ProcessedRawDigis_->Fill(strip, adc);
	  if(plotBaseline_){
	    h1Baseline_->Fill(strip, itBaseline->adc()); 
	    ++itBaseline;
	  }
	 }
	++strip;
       }	  
      if(plotBaseline_) ++itDSBaseline; 
      if(plotClusters_){
          int nclust = 0;
	  edmNew::DetSetVector<SiStripCluster>::const_iterator itClusters = clusters->begin();
	  for ( ; itClusters != clusters->end(); ++itClusters ){
		for ( edmNew::DetSet<SiStripCluster>::const_iterator clus =	itClusters->begin(); clus != itClusters->end(); ++clus){
		  if(itClusters->id() == detId){
		    int firststrip = clus->firstStrip();
	            //std::cout << "Found cluster in detId " << detId << " " << firststrip << " " << clus->amplitudes().size() << " -----------------------------------------------" << std::endl;		
     		    strip=0;
		    for( auto itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
		      h1Clusters_->Fill(firststrip+strip, *itAmpl);
		      ++strip;
		    }
		  }
                  
                  //cluster plots from here on
                   
                  if(ClusterDists == false){
		    nclust++;

     		    int strip2=0;
                    double charge = 0;
                    double mean = 0;
                    double sigma = 0;
		    for( auto itAmpl = clus->amplitudes().begin(); itAmpl != clus->amplitudes().end(); ++itAmpl){
                      charge += *itAmpl;
		      ++strip2;
                      mean += strip2*(*itAmpl);
		      sigma += strip2*strip2*(*itAmpl);
		    }
                    h1ClusterCharge_->Fill(charge);
                    h1ClusterWidth_->Fill(strip2);
                    mean = mean/charge;
                    h1ClusterMean_->Fill(mean);
                    sigma = TMath::Power((sigma/charge-mean*mean),0.5);
                    h1ClusterSigma_->Fill(sigma);
                  }              
		}
	  }
        if(ClusterDists==false)
        {
          h1ClusterMult_->Fill(nclust); 
          ClusterDists = true;
        }
      }
   }		
  */
}


// ------------ method called once each job just before starting event loop  ------------
void SiStripBaselineAnalyzer::beginJob()
{
  
  
actualModule_ =0;  
   
 
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SiStripBaselineAnalyzer::endJob() {
     
}

//define this as a plug-in
DEFINE_FWK_MODULE(SiStripBaselineAnalyzer);

