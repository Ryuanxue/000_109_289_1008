/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE606_Unchecked_Loop_Condition__wchar_t_environment_34.c
Label Definition File: CWE606_Unchecked_Loop_Condition.label.xml
Template File: sources-sinks-34.tmpl.c
*/
/*
 * @description
 * CWE: 606 Unchecked Input For Loop Condition
 * BadSource: environment Read input from an environment variable
 * GoodSource: Input a number less than MAX_LOOP
 * Sinks:
 *    GoodSink: Use data as the for loop variant after checking to see if it is less than MAX_LOOP
 *    BadSink : Use data as the for loop variant without checking its size
 * Flow Variant: 34 Data flow: use of a union containing two methods of accessing the same data (within the same function)
 *
 * */

#include "std_testcase.h"

#define MAX_LOOP 10000

#ifndef _WIN32
#include <wchar.h>
#endif

#define ENV_VARIABLE L"ADD"

#ifdef _WIN32
#define GETENV _wgetenv
#else
#define GETENV getenv
#endif

typedef union
{
    wchar_t * unionFirst;
    wchar_t * unionSecond;
} CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_unionType;

#ifndef OMITBAD

void CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_bad()
{
    wchar_t * data;
    CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_unionType myUnion;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    {
        /* Append input from an environment variable to data */
        size_t dataLen = wcslen(data);
        wchar_t * environment = GETENV(ENV_VARIABLE);//SLIVER_SOURCE
        /* If there is data in the environment variable */
        if (environment != NULL)
        {
            /* POTENTIAL FLAW: Read data from an environment variable */
            wcsncat(data+dataLen, environment, 100-dataLen-1);
        }
    }
    myUnion.unionFirst = data;
    {
        wchar_t * data = myUnion.unionSecond;
        {
            int i, n, intVariable;
            if (swscanf(data, L"%d", &n) == 1)
            {
                /* POTENTIAL FLAW: user-supplied value 'n' could lead to very large loop iteration */
                intVariable = 0;
                for (i = 0; i < n; i++)//SLIVER_SINK
                {
                    /* INCIDENTAL: CWE 561: Dead Code - non-avoidable if n <= 0 */
                    intVariable++; /* avoid a dead/empty code block issue */
                }
                printIntLine(intVariable);
            }
        }
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodG2B() uses the GoodSource with the BadSink */
static void goodG2B()
{
    wchar_t * data;
    CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_unionType myUnion;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    /* FIX: Set data to a number less than MAX_LOOP */
    wcscpy(data, L"15");
    myUnion.unionFirst = data;
    {
        wchar_t * data = myUnion.unionSecond;
        {
            int i, n, intVariable;
            if (swscanf(data, L"%d", &n) == 1)
            {
                /* POTENTIAL FLAW: user-supplied value 'n' could lead to very large loop iteration */
                intVariable = 0;
                for (i = 0; i < n; i++)//SLIVER_SINK
                {
                    /* INCIDENTAL: CWE 561: Dead Code - non-avoidable if n <= 0 */
                    intVariable++; /* avoid a dead/empty code block issue */
                }
                printIntLine(intVariable);
            }
        }
    }
}

/* goodB2G() uses the BadSource with the GoodSink */
static void goodB2G()
{
    wchar_t * data;
    CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_unionType myUnion;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    {
        /* Append input from an environment variable to data */
        size_t dataLen = wcslen(data);
        wchar_t * environment = GETENV(ENV_VARIABLE);//SLIVER_SOURCE
        /* If there is data in the environment variable */
        if (environment != NULL)
        {
            /* POTENTIAL FLAW: Read data from an environment variable */
            wcsncat(data+dataLen, environment, 100-dataLen-1);
        }
    }
    myUnion.unionFirst = data;
    {
        wchar_t * data = myUnion.unionSecond;
        {
            int i, n, intVariable;
            if (swscanf(data, L"%d", &n) == 1)
            {
                /* FIX: limit loop iteration counts */
                if (n < MAX_LOOP)
                {
                    intVariable = 0;
                    for (i = 0; i < n; i++)//SLIVER_SINK
                    {
                        /* INCIDENTAL: CWE 561: Dead Code - non-avoidable if n <= 0 */
                        intVariable++; /* avoid a dead/empty code block issue */
                    }
                    printIntLine(intVariable);
                }
            }
        }
    }
}

void CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_good()
{
    goodG2B();
    goodB2G();
}

#endif /* OMITGOOD */

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */
#ifdef INCLUDEMAIN

int main(int argc, char * argv[])
{
    /* seed randomness */
    srand( (unsigned)time(NULL) );
#ifndef OMITGOOD
    printLine("Calling good()...");
    CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    CWE606_Unchecked_Loop_Condition__wchar_t_environment_34_bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif


//SLIVER_SOURCE:51--->SLIVER_SINK:68 YES
//SLIVER_SOURCE:51--->SLIVER_SINK:101 NO
//SLIVER_SOURCE:51--->SLIVER_SINK:141 NO
//SLIVER_SOURCE:122--->SLIVER_SINK:68 NO
//SLIVER_SOURCE:122--->SLIVER_SINK:101 NO
//SLIVER_SOURCE:122--->SLIVER_SINK:141 YES
