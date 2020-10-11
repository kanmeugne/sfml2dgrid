#ifndef DYNAMICS_H
#define DYNAMICS_H

namespace dynamics
{
	// pheromon parameters
	const float PMAX = 1000.f ; // maximum amount of pheromon
	const float PMIN = 1.f; // minimum amount of pheromon
	const float DELTAMAX = 500.f; // maximum diff of pheromon per move
	const float RHO = 0.08f; // evaporation coefficient
}
#endif