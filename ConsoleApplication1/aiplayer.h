#pragma once

#include<vector>

class aiplayer {
private:
	double learningrate = 0.01;
	double discountfactor = 1.0;
	double eps = 0.1;
	int lastaction;
	bool usegreedy = true;

	std::vector<double> leftq;
	std::vector<double> middq;
	std::vector<double> righq;
	
public:
	aiplayer(double lr, double df);
	aiplayer(double lr, double df, double epsin);
	int greedymove(int pos);
	int epsilongreedymove(int pos, double epsilon, bool purelygreedy);
	int randommove();
	void updateq(double reward, int pos, int action, int newpos);
	double getLearningRate() { return learningrate; }
	double getEps() { return eps; }
	double getDiscountFactor() { return discountfactor; }
	bool getGreedy() { return usegreedy; }
	void setLearningRate(double newlr) { learningrate = newlr; }
	void setEps(double neweps) { eps = neweps; }
	void setDiscountFactor(double newdf) { discountfactor = newdf; }
	void setGreedy(bool greedyin) { usegreedy = greedyin; }
};