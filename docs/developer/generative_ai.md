# Generative AI in MIPPv2

MIPPv2 was written with the help of generative AI assistants. This page says why, how the design of the library keeps that help under control, and what a contributor who works with such an assistant can rely on.

---

## 1. Why

MIPP has existed since 2016. Years of use left a list of ideas that were clear on paper and costly in engineering time: one implementation shared by a C and two C++ APIs, a fallback for every function on every target, register groups, four masking variants everywhere, tests generated from the same description as the code, a documentation that cannot drift. The new vector extensions, SVE and RVV, were on that list too: they were studied, and watched as they evolved, before pragmatic choices were made, such as a vector width fixed at compile time.

Generative AI made that list affordable. It was taken as an opportunity to build what had been designed, not as a way to produce code faster than it can be checked. The rest of this page is about that second half: the checks.

---

## 2. A Design That Keeps Control

The architecture of MIPPv2 separates what is generated from what is decided, and makes each step visible.

**An engine and data.** The generator is a Python engine (`generator/*.py`) that reads declarative JSON registries: the functions and their prototypes, the scalar reference, and, for each SIMD extension, its instructions and its emulations. Adding a function or an extension is mostly a matter of data. The data has a narrow, regular shape, which is easy to write, and easy to review line by line.

**Inputs checked before any code is written.** Every registry is validated against a JSON Schema, and the generator stops on the first inconsistency. Optional [audits](reference/audits.md) report what looks suspicious without being wrong: an entry that is never reached, two implementations that overlap, an implementation declared at the wrong level.

**Generated code made to be read.** The headers are flat C functions that call the intrinsics directly, with no layer of macros or templates in between. Each function states its [implementation level](../user/implementation_levels.md) in a comment. A reviewer reads the same code as the compiler.

**One description, several outputs.** The headers, the unit tests, the reference pages of this site and the data of the API Explorer are produced from the same registries. An error in the description shows up in several places at once.

---

## 3. Checked Against a Scalar Reference

Each function has a scalar reference: a plain C loop that defines the expected result for every datatype and mask variant. The [test generator](internals/test_generator.md) writes, for every function, a test that runs the implementation under test and the reference on the same random inputs and compares the results lane by lane, exactly or within a documented tolerance.

The tests are generated for the three APIs. The [continuous integration](process/ci.md) runs the tests of the C++ Object API (LMUL 1, LMUL 8 and the half-vectors, every mask variant) with two compilers on 16 targets, from SSE to AVX-512, NEON, SVE and RVV.

This is what makes a new SIMD extension safe to add: its implementations are accepted when they agree with the reference, whoever, or whatever, wrote them. It is a test and not a proof. It covers the inputs that are drawn, in the domains the specifications give, and its strength is that of the reference itself, which is short, sequential, and reviewed by hand.

---

## 4. Seeing What Was Generated

The [API Explorer](../explorer/index.md) does not rely on a separate description. Its levels come from the candidate resolver that writes the headers, and its Algorithm modal reads the generated headers themselves. For a function, a datatype, a mask variant and a target, it shows:

- the code that is really compiled for the selected compiler flags, and its level;
- what this code is built from: the tree of the MIPP functions it calls, down to the intrinsics;
- the levels of the function on every target, side by side.

It answers in a few seconds the question a review starts with: what does this function become on this machine? It is the tool used to follow the generated code as the library grows, and it is open to every user for the same purpose.

---

## 5. A Documentation an Assistant Can Trust

An assistant is only as good as what it reads. The [Developer Guide](index.md) is kept in step with the code by construction:

- the reference of the registries is generated from the JSON Schemas that validate them;
- the command-line reference is generated from the scripts;
- the code examples of the User Guide are complete programs, compiled and run by the continuous integration.

A contributor, human or not, who follows the tutorials ([a function](tutorials/add_function.md), [an implementation](tutorials/add_implementation.md), [an ISA](tutorials/add_isa.md)) works from a description that matches the code. This is what makes AI-assisted contributions practical: the task is well specified, the result is checked by the schemas, the audits and the tests, and the review reads a small, regular diff.

---

## 6. What Stays Human

Generative AI did not design MIPPv2. The decisions below are made, discussed and reviewed by the maintainers:

- the API: the names, the semantics of each function, what is undefined behavior;
- the scalar reference, which every implementation is measured against;
- the architecture of the generator, and what it does not do;
- what is merged: every change is reviewed, and tested, whatever tool wrote it.

Contributions written with an assistant are welcome on the same terms as any other: they follow the tutorials, pass the validation, the audits and the tests, and are reviewed.
