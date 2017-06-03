#include "CuTest.h"
#include <stdio.h>

CuSuite* backendGetSuite();
CuSuite* helpersGetSuite();

void RunAllTests(void) {
		CuString *output = CuStringNew();
		CuSuite* suite = CuSuiteNew();

		CuSuiteAddSuite(suite, backendGetSuite());
		CuSuiteAddSuite(suite, helpersGetSuite());

		CuSuiteRun(suite);
		CuSuiteSummary(suite, output);
		CuSuiteDetails(suite, output);
		printf("%s\n", output->buffer);
}
