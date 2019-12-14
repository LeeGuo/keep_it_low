#include <iostream>

using namespace std;

const int MAX_TASK_NUM = 20;
const int MAX_EMPLOYEE_NUM = 20;

int ReadInputFile(int costArrPtr[MAX_TASK_NUM][MAX_EMPLOYEE_NUM])
{
    FILE *f;
    f = fopen("HW7.txt", "r");

    int taskCnt = 0;
    fscanf(f, "%d", &taskCnt);
    printf("Total employee = %d\n", taskCnt);
    
    if (taskCnt > 0)
    {
        for (int i=0; i<taskCnt; ++i)
            for (int j=0; j<taskCnt; ++j)
				fscanf(f, "%d", &costArrPtr[i][j]);
    }

    fclose(f);
    return taskCnt;
}

bool AlreadyUsed(int solution[MAX_EMPLOYEE_NUM], int c)
{
    for (int i=c-1; i>=0; --i)
        if (solution[c] == solution[i])
            return true;
    return false;
}

double TotalCost(int costArr[MAX_TASK_NUM][MAX_EMPLOYEE_NUM],
                 int solution[MAX_EMPLOYEE_NUM],
				 int size)
{
    double totalCost = 0.0;
    for (int i=0; i<size; ++i)
    {
        int taskOfEmployeeI = solution[i];
        totalCost += costArr[taskOfEmployeeI][i];
    }
    return totalCost;
}

int main()
{
    int costArr[MAX_TASK_NUM][MAX_EMPLOYEE_NUM];
    int totalEmployee = 0;
	
	// read file
	totalEmployee = ReadInputFile(costArr);
	if (totalEmployee <= 0)
	{
		// no employee, return directly
		return 0;
	}
    
	// start reading assignments from user-input
    int solution[MAX_EMPLOYEE_NUM] = {0};
    int nowEmployee = 0;
    while (true)
    {
        cout << "Enter work for employee " << nowEmployee <<": ";
        cin >> solution[nowEmployee];
        
        // Error-proof Logic: out of range
        if (solution[nowEmployee] < 0 || solution[nowEmployee] >= totalEmployee)
		{
			cout << "Out of range, invalid" << endl;

			// continue: ignore the remaining logic of current loop and continue straightly to "next loop"
			continue;
		}
		
		// Error-proof Logic: duplicated assignment
		if (AlreadyUsed(solution, nowEmployee))
		{
			cout << solution[nowEmployee] << " duplicate, invalid" << endl;

			// continue: ignore the remaining logic of current loop and continue straightly to "next loop"
			continue;
		}
		
		// successful assignment, next one!
		++nowEmployee;
		
		// assignments done?
		if (nowEmployee == totalEmployee)
		{
			// break: ignore the remaining logic of current loop and "leave the loops"
			break;
		}
    }
	// ps. "continue" and "break" used above work for both "while-loop" and "for-loop"
	
	cout << "Total cost = " << TotalCost(costArr, solution, totalEmployee) << endl;
	cout << "Your assignment" << endl;
	for (int i=0; i<totalEmployee; ++i)
	{
		/*
		 * semantic:
		 *    value = (evaluation_logic) ? A : B;
		 *
		 * meaning:
		 *    if the 'evaluation_logic' is true, then the value is assigned as A;
		 *    if the 'evaluation_logic' is false, then the value is assigned as B;
		 */
		char separator = (i == totalEmployee - 1) ? '\n' : ',';
		cout << solution[i] << separator;
	}

    return 0;
}
