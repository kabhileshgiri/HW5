> **Tip:** This file is written in Markdown. The raw view in the VS Code
> editor will show symbols such as `#`, `|`, and `` ``` `` instead of
> formatted headings, tables, and code blocks. For the formatted view,
> press **Ctrl+Shift+V** (macOS: **Cmd+Shift+V**) to open the rendered
> preview.

# Homework 5 — Signal Workbench

## Overview

A *digital signal* is a list of numbers called *samples*, such as the
readings a sensor or a microphone sends to a computer at regular time
steps. This program stores signals in a class named `Signal`, which keeps
its samples in a **dynamic array** whose size is chosen while the program
runs. A signal is typed as a list of integers separated by commas, for
example `3, 5, -2, 7`, and is displayed as `[3, 5, -2, 7]`.

From a menu, the user can:

1. enter a new signal,
2. list all stored signals,
3. mix two signals (`a + b`: add them sample by sample),
4. amplify a signal (`s * gain`: multiply every sample by a gain),
5. invert a signal (`-s`: negate every sample),
6. compare two signals (`a == b`), and
7. change one sample of a stored signal (`s[i] = value`).

Each new result is stored as a new signal. `main()`, the helper
`readSignalNumber()`, the class definition, and the global constants are
provided and complete. Your job is to write the fourteen member, friend,
and ordinary functions marked `TODO` in `main.cpp`. See the full
assignment handout on Canvas for the complete problem statement, the
exact sample-list formats, an example interaction, and the grading
rubric.

## Constraints

- Do **not** modify the class definition, `main()`, `readSignalNumber()`,
  the provided constants, the `#include` lines, or any function's name,
  return type, or parameter list. The autograder calls your functions
  directly.
- Use only the headers already included in the template (`<iostream>`,
  `<string>`, `<vector>`, `<cstdlib>`, `<cctype>`).
- Store the samples only in the dynamic array the class declares. Inside
  the member and friend functions, work with that array; use
  `std::vector` only in the `Signal(const std::vector<int>&)`
  constructor and in `parseSignal`.
- Do not use library algorithms such as `std::copy` or `std::fill`, and
  do not declare global variables (other than the provided constants).
- Every dynamic array your code creates must be deleted exactly once,
  with `delete []`.
- `operator +`, unary `operator -`, and `operator *` must create their
  result with the `Signal(int theLength)` constructor. `parseSignal` must
  collect the values in a `std::vector<int>` and create the signal with
  the `Signal(const std::vector<int>&)` constructor.
- Use the named constant `MAX_DIGITS` instead of writing its value (6).
- You may assume that no result is too large for an `int`.
- Your program must compile with no errors using
  `g++ -std=c++11 main.cpp -o main`.

## Function Interface

| Function | Parameters | Returns | Behavior |
|---|---|---|---|
| `Signal()` | none | — | Creates an empty signal (0 samples). |
| `Signal(int theLength)` | `int theLength` (≥ 0) | — | Creates a signal of `theLength` samples, all 0. |
| `Signal(const std::vector<int>& values)` | `const std::vector<int>& values` | — | Creates a signal whose samples are the elements of `values`, in order. |
| `Signal(const Signal& other)` | `const Signal& other` | — | Creates an independent copy of `other`. |
| `~Signal()` | none | — | Returns the signal's dynamic array to the heap. |
| `operator =` (member) | `const Signal& right` | `Signal&` | Makes the calling signal an independent copy of `right` (safe for `s = s`) and returns the calling object. |
| `getLength` (const member) | none | `int` | Returns the number of samples. |
| `operator []` (member) | `int index` | `int&` | Returns a reference to sample `index`, or prints `Sample index out of range: <index>` and ends the program with exit status 1. |
| `operator *` (const member) | `int gain` | `Signal` | Returns a new signal whose samples are the calling signal's samples times `gain`. |
| `operator +` (friend) | `const Signal& a`, `const Signal& b` | `Signal` | Returns the sample-by-sample sum, as long as the longer signal; a shorter signal counts as 0 after its last sample. |
| `operator -` (friend, unary) | `const Signal& s` | `Signal` | Returns a new signal with every sample of `s` negated. |
| `operator ==` (friend) | `const Signal& a`, `const Signal& b` | `bool` | Returns `true` when both signals have the same length and the same samples. |
| `operator <<` (friend) | `std::ostream& outs`, `const Signal& s` | `std::ostream&` | Writes `s` to `outs` in the format `[3, 5, -2, 7]` (`[]` when empty) and returns `outs`. |
| `parseSignal` | `const std::string& text`, `Signal& result` | `bool` | Returns `true` and sets `result` when `text` is a valid sample list; otherwise returns `false` and leaves `result` unchanged. |

A valid sample list is empty or all blanks (the empty signal), or one or
more items separated by commas, where each item is optional blanks, an
optional minus sign, 1 to `MAX_DIGITS` digits, and optional blanks. The
handout gives examples of valid and invalid lists.

## Compiling and Running

```
g++ -std=c++11 main.cpp -o main
./main            # macOS / Linux
.\main.exe        # Windows
```

The program reads everything it needs from the keyboard. To repeat a
long test, you can type the inputs into a text file, one per line, and
run `./main < inputs.txt` (macOS / Linux; in Windows PowerShell use
`Get-Content inputs.txt | .\main.exe`).

## Submission Checklist

- [ ] Filled in the file header at the top of `main.cpp` (name, student ID, section).
- [ ] Program compiles with no errors using `g++ -std=c++11 main.cpp -o main`.
- [ ] Tested every menu option, including the empty signal, signals of different lengths, invalid sample lists, and sample indexes just outside the valid range.
- [ ] Checked that a copied or assigned signal does not change when the original is changed (option 7), and that the program does not crash at the end.
- [ ] Code is commented and consistently formatted.
- [ ] Committed and pushed all changes to GitHub (not just once, right before the deadline).
- [ ] Submitted through Gradescope by selecting this repository and the correct branch.
- [ ] Submitted the Part A Concept Check answers as a PDF on Canvas.

## Academic Integrity

Write this code independently. Do not copy code from another student,
share your submission files with classmates, or use an AI tool to
generate, complete, modify, or correct any part of this program. See
the course syllabus, Section B, for the full policy. Keep this
repository private for the entire semester.
