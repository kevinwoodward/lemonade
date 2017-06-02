#include "CuTest.h"
#include <stdio.h>

//CuSuite* StrUtilGetSuite();
CuSuite* backendGetSuite();

void RunAllTests(void) {
		CuString *output = CuStringNew();
		CuSuite* suite = CuSuiteNew();

		CuSuiteAddSuite(suite, backendGetSuite());

		CuSuiteRun(suite);
		CuSuiteSummary(suite, output);
		CuSuiteDetails(suite, output);
		printf("%s\n", output->buffer);
}
