/*
 * parse.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: chl
 */

#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include "sims.h"

void Parse(Simulation& sims, const char* test_file) {
	FILE* F = fopen(test_file, "r");
	if (!F) {
		printf("Failed to open file '%s'\n", test_file);
		exit(EXIT_FAILURE);
	}

	char buff[1000];

	while (fgets(buff, sizeof(buff), F)) {
		std::stringstream ss(buff);
		std::string item, name;
		if (!(ss >> item) || !item.size() || item[0] == '#')
			continue;
		if (item == "size") {
			FSszie w, h;
			ss >> w >> h;
			assert(ss);
			sims.ChangeGrid(w, h);
		} else if (item == "duration") {
			FSFloat t;
			ss >> t;
			assert(ss);
			sims.ChangeDuration(t);
		} else if (item == "delta") {
			FSFloat dt;
			ss >> dt;
			assert(ss);
			sims.ChangeDeltaT(dt);
		} else if (item == "cell") {
			FSszie x, y;
			FSFloat p, vx, vy;
			ss >> x >> y >> p >> vx >> vy;
			assert(ss);
			FSF2D u(vx, vy);
			sims.Set(x, y, p, u);
		} else if (item == "wall") {
			FSszie x, y;
			int right;
			ss >> x >> y >> right;
			assert(ss);
			if (right) {
				sims.SetWall(x, y, true, true);
			} else {
				sims.SetWall(x, y, true, false);
			}
		} else {
			std::cout << "Failed to parse: " << buff << std::endl;
			exit(EXIT_FAILURE);
		}
	}

}
