// ***************************************************************************
// Profile.h (c) 2018 Zhenhua Yu <qasim0208@163.com>
// Health Informatics Lab, Ningxia University
// All rights reserved.

#ifndef _PROFILE_H
#define _PROFILE_H

#include <vector>
#include <map>
#include <string>
#include <pthread.h>

#include "Matrix.h"

using namespace std;

class KmerIndex {
	public:
		int index;
		map<char, KmerIndex> nextIndexs;
		KmerIndex() {index = -1;}
};

class Profile {
	private:
		int minBaseQuality;
		int maxBaseQuality;
		
		double indelRate;
		
		char **kmers;
		KmerIndex rIndex;
		int kmerCount;
		
		double stdISize;
		
		Matrix<int> baseAlphabet;
		Matrix<int> qualityAlphabet;
		Matrix<int> iSizeAlphabet;
		
		Matrix<double> kmersDist;
		
		Matrix<double> *subsDist1;
		Matrix<double> *subsDist2;
		Matrix<double> *subsCdf1;
		Matrix<double> *subsCdf2;
		
		Matrix<double> *qualityDist;
		Matrix<double> *qualityCdf;
		
		Matrix<double> iSizeDist;
		Matrix<double> iSizeCdf;
		
		//GC-content bias
		double gcMeans[101];
		double gcStd;
		vector<default_random_engine> gc_generators;
		vector<normal_distribution<double> > gc_normDists;
		
		vector<double> gcs;
		vector<double> readCounts;
		
		void initKmers();
		int getKmerIndx(const char *s);
		void setBins();
		
		void initGCParas();
		void estimateGCParas();
		int countGC(string chr, long position);
		
		void saveResults();
		void load(string proFile);
		
		void initCDFs();
		void normParas(bool isLoaded);
		
		int getSubBaseIndx1(char *kmer, int binIndx);
		int getSubBaseIndx2(char *kmer, int binIndx);
		int getIndelSeq(vector<int> &baseIndxs);
		int getBaseQuality(int basePairIndx, int binIndx);
		int getRandBaseQuality();
		
	public:
		Profile();
		~Profile();
		
		static int fragSize;
		
		static int getFragSize() {return fragSize;}
		
		void init();
		
		int processRead(char* read);
		
		int yieldInsertSize();
		double getStdISize();
		int getMaxInsertSize();
		
		double getGCFactor(int gc);
		
		void train(string proFile);
		void train();
		char* predict(char* refSeq, int isRead1);
		void predict(char* refSeq, char* results, int num, int isRead1);
		
};


#endif
