#include <iostream>
#include <string>

using namespace std;

// costPerformance[job #][employee #]
const int costPerformance[5][5] = {
	{356, 381, 368, 399, 375}, // cost for job 0
	{259, 348, 295, 398, 324}, // cost for job 1
	{302, 265, 242, 285, 237}, // cost for job 2
	{199, 268, 369, 347, 261}, // cost for job 3
	{347, 216, 260, 390, 341}, // cost for job 4
};

double Cost(int a0, int a1, int a2, int a3, int a4) {
	return costPerformance[a0][0]
	     + costPerformance[a1][1]
	     + costPerformance[a2][2]
	     + costPerformance[a3][3]
	     + costPerformance[a4][4];
}

int main() {
	/**
	 * jobTaken[x] means if the job-x is taken or not, used to check if
	 * the job is already taken by previous loop.
	 *
	 * (usage: record the job taken at the beginning of each loop,
	 *         but REMEMBER to release the job taken status at the
	 *         end of each loop)
	 */
	bool jobTaken[5] = {false, false, false, false, false};
	
	// record the min cost & status of that job permutation
	double minCost = 5000.0;
	int minCostJobStatus[5];

	/**
	 * start traversing through each job permutation:
	 * 
	 * e[0~4] here represent the job # taken by employee-0~4
	 * for instance, e[2] = 3 means the employee-2 takes the job-3
	 */
	int e[5];
	for (e[0]=0; e[0]<5; ++e[0]) {
		jobTaken[e[0]] = true;                        // record the job taken by employee-0
		for (e[1]=0; e[1]<5; ++e[1]) {
			if (jobTaken[e[1]]) continue;
			jobTaken[e[1]] = true;                    // record the job taken by employee-1
			for (e[2]=0; e[2]<5; ++e[2]) {
				if (jobTaken[e[2]]) continue;
				jobTaken[e[2]] = true;                // record the job taken by employee-2
				for (e[3]=0; e[3]<5; ++e[3]) {
					if (jobTaken[e[3]]) continue;
					jobTaken[e[3]] = true;            // record the job taken by employee-3
					for (e[4]=0; e[4]<5; ++e[4]) {
						// if the job is taken by previous employees, then use 'continue' to skip this loop
						// if the job is not taken, then go on at this loop
						// same reason for the previous few "if (...) continue;"
						if (jobTaken[e[4]]) continue;
						
						// last employee, no need to record/release job taken, count the cost directly!!
						double totalCost = Cost(e[0], e[1], e[2], e[3], e[4]);
						if (totalCost < minCost) {
							minCost = totalCost;
							for (int i=0; i<5; ++i)
								minCostJobStatus[i] = e[i];
						}
					}
					jobTaken[e[3]] = false;           // release the job taken by employee-3
				}
				jobTaken[e[2]] = false;               // release the job taken by employee-2
			}
			jobTaken[e[1]] = false;                   // release the job taken by employee-1
		}
		jobTaken[e[0]] = false;                       // release the job taken by employee-0
	}
	
	cout << "The lowest cost is " << minCost << endl;
	for (int i=0; i<5; ++i)
		cout << "Employee " << i << " = work " << minCostJobStatus[i] << endl;
}