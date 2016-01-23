/**
Copyright (c) 2016 Mariano Gonzalez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "timer.h"
#include <chrono> // milliseconds
#include <iostream> // For printing to console.
#include <thread> // To make this thread sleep and simulate some time. 

void doSomething() {
    std::chrono::milliseconds duration(2000);
    std::this_thread::sleep_for(duration);
}

int main() {
    // Instantiate a timer that will track time and give results in milliseconds (it's ratio)
    using Millis_Timer = util::Timer<std::milli>;
    Millis_Timer t1;

    std::cout << "This should be zero since no snapshot has been done: " << t1.get_delta<uint32_t>() << " milliseconds\n";
    std::cout << "This should be different from zero," 
                  " since it tracks the amout of time" 
                  " since the creation of the timer: " << t1.get_total<uint64_t>() << " milliseconds\n";
    
    // Let's make it do something and time how much it takes:
    t1.snap();
    doSomething();
    std::cout << "Doing something took: " << t1.get_delta<uint32_t>() << " milliseconds\n";

    // Let's make it do something and time how much it takes, 
    // but this time showing the result using a different representation (floating point):
    t1.snap();
    doSomething();
    std::cout << "Doing something took: " << t1.get_delta<float>() << " milliseconds\n";
}
