#include "aiplayer.h"
#include<vector>

aiplayer::aiplayer(double lr, double df) {
	learningrate = lr;
	discountfactor = df;
	std::vector<double> tmp(16, 0);

	leftq = tmp;
	middq = tmp;
	righq = tmp;

}

aiplayer::aiplayer(double lr, double df, double epsin) {
	learningrate = lr;
	discountfactor = df;
	eps = epsin;
	std::vector<double> tmp(7, 0);

	leftq = tmp;
	middq = tmp;
	righq = tmp;

}


int aiplayer::greedymove(int pos) {

	double vl = leftq[pos];
	double vm = middq[pos];
	double vr = righq[pos];

	if (vl >= vm and vl >= vr) {
		lastaction = 1;
		return lastaction;
	}
	else if (vm >= vl and vm >= vr) {
		lastaction = 2;
		return lastaction;
	}
	else if (vr >= vm and vr >= vl) {
		lastaction = 3;
		return lastaction;
	}
}
int aiplayer::epsilongreedymove(int pos, double epsilon, bool purelygreedy = false) {
	double ra = (1.0*(rand() % 100 + 1)) / 100.0; //0 och 1
	if (ra < epsilon and not(purelygreedy)) {
		return randommove();
	}
	else {
		return greedymove(pos);
	}
}
int aiplayer::randommove() {
	int v2 = rand() % 100 + 1;
	if (v2 < 30) {
		return 1;
	}
	else if (v2 < 63) {
		return 2;
	}
	else {
		return 3;
	}
}

void aiplayer::updateq(double reward, int pos, int action, int newpos) {

	double maxQ = 0;
	if (leftq[newpos] >= middq[newpos] and leftq[newpos] >= righq[newpos]) {
		maxQ = leftq[newpos];
	}
	else if (middq[newpos] >= leftq[newpos] and middq[newpos] >= righq[newpos]) {
		maxQ = middq[newpos];
	}
	else if (righq[newpos] >= middq[newpos] and righq[newpos] >= leftq[newpos]) {
		maxQ = righq[newpos];
	}


	if (1 == action) {
		leftq[pos] = leftq[pos] + learningrate * (reward + discountfactor * maxQ - leftq[pos]);
	}
	if (2 == action) {
		middq[pos] = middq[pos] + learningrate * (reward + discountfactor * maxQ - middq[pos]);
	}
	if (3 == action) {
		righq[pos] = righq[pos] + learningrate * (reward + discountfactor * maxQ - righq[pos]);
	}

}