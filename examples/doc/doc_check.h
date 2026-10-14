/*
 * Helpers of the documentation snippets (examples/doc/).
 *
 * Every file of examples/doc/ is a complete program: the named sections
 * (`// --8<-- [start:name]` ... `// --8<-- [end:name]`) are the code shown in
 * the documentation, the rest prepares the inputs and checks the results.
 * scripts/check_doc_snippets.sh compiles and runs every program: a failed
 * DOC_CHECK makes the program return a non-zero exit code.
 *
 * Valid C99 and C++11.
 */
#ifndef MIPP_DOC_CHECK_H_
#define MIPP_DOC_CHECK_H_

#include <stdio.h>

/* Size of the test buffers, in elements: larger than the biggest register
 * group of the tested targets (1024-bit scalar target, LMUL = 8, 8-bit types
 * excepted). */
#define DOC_BUF 512

/* Alignment of the test buffers, in bytes: larger than the register size of
 * every tested target (up to 1024 bits for the scalar target). */
#if defined(__cplusplus)
#define DOC_ALIGNED alignas(128)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#define DOC_ALIGNED _Alignas(128)
#else
#define DOC_ALIGNED __attribute__((aligned(128)))
#endif

static int doc_failures = 0;

/* Variadic, so that the condition may contain template commas. */
#define DOC_CHECK(...)                                                                     \
    do {                                                                                   \
        if (!(__VA_ARGS__)) {                                                              \
            fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #__VA_ARGS__); \
            doc_failures++;                                                                \
        }                                                                                  \
    } while (0)

/* Exit code of the program: 0 if every check passed. */
static int doc_status(void)
{
    if (doc_failures)
        fprintf(stderr, "%d check(s) failed\n", doc_failures);
    return doc_failures ? 1 : 0;
}

#endif /* MIPP_DOC_CHECK_H_ */
