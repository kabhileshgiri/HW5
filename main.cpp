/*
 * Full Name:     [Your Name]
 * Student ID:    [Your NUID]
 * Course:        EECE 2140 - Computing Fundamentals for Engineers
 * Section:       [Your Section]
 * Semester:      Fall 2026
 * Assignment:    Homework 5 - Signal Workbench
 * Compilation:   g++ -std=c++11 main.cpp -o main
 * Description:   A menu-driven program that stores digital signals (lists
 *                of integer samples) in a Signal class that owns a dynamic
 *                array. It reads signals typed as comma-separated text,
 *                and mixes, amplifies, inverts, compares, and edits them
 *                with overloaded operators.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>

// ---------------------------------------------------------------------
// Global named constants (provided in the template)
// ---------------------------------------------------------------------
const int MAX_DIGITS = 6;     // most digits allowed in one sample value
const int MAX_GAIN = 100;     // gains run from -MAX_GAIN to MAX_GAIN

// ---------------------------------------------------------------------
// Class definition (provided in the template)
// ---------------------------------------------------------------------
class Signal
{
public:
    Signal();
    Signal(int theLength);
    Signal(const std::vector<int>& values);
    Signal(const Signal& other);
    ~Signal();
    Signal& operator =(const Signal& right);

    int getLength() const;
    int& operator [](int index);
    Signal operator *(int gain) const;

    friend Signal operator +(const Signal& a, const Signal& b);
    friend Signal operator -(const Signal& s);
    friend bool operator ==(const Signal& a, const Signal& b);
    friend std::ostream& operator <<(std::ostream& outs, const Signal& s);

private:
    int *samples;   // dynamic array that holds the samples
    int length;     // number of samples in the signal
};

// ---------------------------------------------------------------------
// Function declarations (provided in the template)
// ---------------------------------------------------------------------
bool parseSignal(const std::string& text, Signal& result);
bool readSignalNumber(const std::vector<Signal>& bank, const std::string& prompt,
                      int& number);

// ---------------------------------------------------------------------
// main() -- provided; do not modify anything above the line of "=" signs.
// ---------------------------------------------------------------------
int main()
{
    std::vector<Signal> bank;   // the stored signals, numbered from 0
    int choice = 0;

    std::cout << "=== EECE 2140 Signal Workbench ===" << std::endl;

    do
    {
        std::cout << std::endl
                  << "1) Enter a new signal" << std::endl
                  << "2) List all signals" << std::endl
                  << "3) Mix two signals (a + b)" << std::endl
                  << "4) Amplify a signal (s * gain)" << std::endl
                  << "5) Invert a signal (-s)" << std::endl
                  << "6) Compare two signals (a == b)" << std::endl
                  << "7) Change one sample (s[i] = value)" << std::endl
                  << "8) Exit" << std::endl
                  << "Enter your choice: ";

        if (!(std::cin >> choice))
        {
            choice = 8;   // end of input: leave the menu
        }

        if (choice == 1)
        {
            std::string text;
            Signal entered;

            std::cin.ignore(1000, '\n');   // discard the rest of the choice line
            std::cout << "Enter the samples, separated by commas: ";
            std::getline(std::cin, text);

            if (parseSignal(text, entered))
            {
                bank.push_back(entered);
                std::cout << "Stored signal #" << bank.size() - 1 << ": "
                          << entered << std::endl;
            }
            else
            {
                std::cout << "Not a valid list of samples." << std::endl;
            }
        }
        else if (choice == 2)
        {
            if (bank.empty())
            {
                std::cout << "No signals are stored yet." << std::endl;
            }
            for (unsigned int i = 0; i < bank.size(); i++)
            {
                std::cout << "#" << i << " (length " << bank[i].getLength()
                          << "): " << bank[i] << std::endl;
            }
        }
        else if (choice == 3)
        {
            int first = 0, second = 0;
            if (readSignalNumber(bank, "Enter the first signal number: ", first) &&
                readSignalNumber(bank, "Enter the second signal number: ", second))
            {
                Signal mixed = bank[first] + bank[second];
                bank.push_back(mixed);
                std::cout << "Stored signal #" << bank.size() - 1 << ": "
                          << mixed << std::endl;
            }
        }
        else if (choice == 4)
        {
            int number = 0, gain = 0;
            if (readSignalNumber(bank, "Enter the signal number: ", number))
            {
                std::cout << "Enter the gain (" << -MAX_GAIN << " to "
                          << MAX_GAIN << "): ";
                if (!(std::cin >> gain) || gain < -MAX_GAIN || gain > MAX_GAIN)
                {
                    std::cout << "The gain must be between " << -MAX_GAIN
                              << " and " << MAX_GAIN << "." << std::endl;
                }
                else
                {
                    Signal amplified = bank[number] * gain;
                    bank.push_back(amplified);
                    std::cout << "Stored signal #" << bank.size() - 1 << ": "
                              << amplified << std::endl;
                }
            }
        }
        else if (choice == 5)
        {
            int number = 0;
            if (readSignalNumber(bank, "Enter the signal number: ", number))
            {
                Signal inverted = -bank[number];
                bank.push_back(inverted);
                std::cout << "Stored signal #" << bank.size() - 1 << ": "
                          << inverted << std::endl;
            }
        }
        else if (choice == 6)
        {
            int first = 0, second = 0;
            if (readSignalNumber(bank, "Enter the first signal number: ", first) &&
                readSignalNumber(bank, "Enter the second signal number: ", second))
            {
                std::cout << "Signals #" << first << " and #" << second;
                if (bank[first] == bank[second])
                {
                    std::cout << " are equal." << std::endl;
                }
                else
                {
                    std::cout << " are different." << std::endl;
                }
            }
        }
        else if (choice == 7)
        {
            int number = 0, index = 0, value = 0;
            if (readSignalNumber(bank, "Enter the signal number: ", number))
            {
                std::cout << "Enter the sample index: ";
                std::cin >> index;
                std::cout << "Enter the new value: ";
                if (std::cin >> value)
                {
                    bank[number][index] = value;
                    std::cout << "Signal #" << number << " is now "
                              << bank[number] << std::endl;
                }
            }
        }
        else if (choice == 8)
        {
            std::cout << "Goodbye." << std::endl;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1-8." << std::endl;
        }
    } while (choice != 8);

    return 0;
}

// Reads a signal number for main(). Returns true when number names a
// stored signal; otherwise prints a message (unless the input ended) and
// returns false. Provided; do not modify.
bool readSignalNumber(const std::vector<Signal>& bank, const std::string& prompt,
                      int& number)
{
    std::cout << prompt;
    if (!(std::cin >> number))
    {
        return false;   // end of input: main() leaves the menu next
    }
    if (number < 0 || number >= static_cast<int>(bank.size()))
    {
        std::cout << "There is no signal #" << number << "." << std::endl;
        return false;
    }
    return true;
}

// =====================================================================
// Complete each function below. Do not change the class definition, any
// function's name, return type, or parameter list, main(),
// readSignalNumber(), or the provided constants. Each placeholder
// statement is there only so that the template compiles; replace it
// with your own code.
// =====================================================================

// TODO 1: default constructor
//   Behavior:   Creates an empty signal: a signal with 0 samples.
Signal::Signal()
{
}

// TODO 2: Signal(int theLength)
//   Parameters: theLength -- the number of samples (theLength >= 0).
//   Behavior:   Creates a signal with theLength samples, every one of
//               which is 0.
Signal::Signal(int theLength)
{
}

// TODO 3: Signal(const std::vector<int>& values)
//   Parameters: values -- the sample values, in order (not modified).
//   Behavior:   Creates a signal with values.size() samples; sample i is
//               values[i].
Signal::Signal(const std::vector<int>& values)
{
}

// TODO 4: copy constructor
//   Parameters: other -- the signal to copy (not modified).
//   Behavior:   Creates a signal with the same length and samples as
//               other. Afterward the two signals are independent:
//               changing a sample of one never changes the other, and
//               destroying one never affects the other.
Signal::Signal(const Signal& other)
{
}

// TODO 5: destructor
//   Behavior:   Returns the memory of the signal's dynamic array to the
//               heap. Every array the class creates must be deleted
//               exactly once.
Signal::~Signal()
{
}

// TODO 6: assignment operator
//   Parameters: right -- the signal whose value is assigned (not
//                        modified).
//   Behavior:   Gives the calling signal the same length and samples as
//               right, so that the two are independent afterward. The
//               memory the calling signal held before is returned to the
//               heap. Assigning a signal to itself (s = s) leaves it
//               unchanged.
//   Returns:    The calling object, so that assignments can be chained
//               (a = b = c).
Signal& Signal::operator =(const Signal& right)
{
    return *this;
}

// TODO 7: getLength
//   Returns:    The number of samples in the signal.
int Signal::getLength() const
{
    return -1;
}

// TODO 8: index operator
//   Parameters: index -- the position of a sample (0 is the first).
//   Returns:    A reference to the sample at position index, so that
//               s[i] can be both read and changed (s[i] = value).
//   Behavior:   If index is not a valid position (0 to length - 1),
//               prints exactly
//                   Sample index out of range: <index>
//               as one line on the screen and then ends the whole program
//               with exit status 1.
int& Signal::operator [](int index)
{
    return length;
}

// TODO 9: operator * (member)
//   Parameters: gain -- the factor to multiply by.
//   Returns:    A new signal, as long as the calling signal, in which
//               sample i is sample i of the calling signal times gain.
//               The calling signal does not change. Must create its
//               result with the Signal(int theLength) constructor.
Signal Signal::operator *(int gain) const
{
    return Signal();
}

// TODO 10: operator + (friend)
//   Parameters: a, b -- the two signals to mix (not modified).
//   Returns:    A new signal as long as the longer of a and b, in which
//               sample i is the sum of sample i of a and sample i of b.
//               A signal that has fewer samples than i + 1 contributes 0
//               at position i. Must create its result with the
//               Signal(int theLength) constructor.
Signal operator +(const Signal& a, const Signal& b)
{
    return Signal();
}

// TODO 11: unary operator - (friend)
//   Parameters: s -- the signal to invert (not modified).
//   Returns:    A new signal, as long as s, in which every sample is the
//               negative of the matching sample of s. Must create its
//               result with the Signal(int theLength) constructor.
Signal operator -(const Signal& s)
{
    return Signal();
}

// TODO 12: operator == (friend)
//   Parameters: a, b -- the two signals to compare (not modified).
//   Returns:    true if a and b have the same length and every sample of
//               a equals the matching sample of b; false otherwise. Two
//               empty signals are equal.
bool operator ==(const Signal& a, const Signal& b)
{
    return false;
}

// TODO 13: operator << (friend)
//   Parameters: outs -- the output stream to write to (cout or any other
//                       ostream).
//               s    -- the signal to write (not modified).
//   Behavior:   Writes s to outs in the exact format given in the
//               assignment handout: a left bracket, the samples in order
//               separated by a comma and one blank, and a right bracket,
//               for example [3, 5, -2, 7]. The empty signal is written as
//               []. Writes no line break.
//   Returns:    outs, so that << can be chained.
std::ostream& operator <<(std::ostream& outs, const Signal& s)
{
    return outs;
}

// TODO 14: parseSignal
//   Parameters: text   -- one line of text typed by the user (not
//                         modified).
//               result -- the signal to set when text is valid.
//   Returns:    true if text is a valid sample list, in the exact format
//               given in the assignment handout; false otherwise.
//   Behavior:   When text is valid, result becomes the signal it
//               describes (an empty or all-blank text describes the
//               empty signal). When text is not valid, result does not
//               change. Must collect the values in a std::vector<int> and
//               create the signal with the Signal(const std::vector<int>&)
//               constructor.
bool parseSignal(const std::string& text, Signal& result)
{
    return false;
}
