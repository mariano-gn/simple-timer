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

#ifndef _TIMER_H_
#define _TIMER_H_
#include <chrono>

namespace util {
    template<typename time_ratio_t>
    class Timer {
    public:
        void snap() {
            m_snap = clock::now();
        }

        template<typename count_t>
        count_t get_delta() const {
            return get_diff<count_t>(m_snap, clock::now());
        }

        template<typename count_t>
        count_t get_total() const {
            return get_diff<count_t>(m_start, clock::now());
        }
        
    private:
        using clock = std::chrono::high_resolution_clock;
        using point = std::chrono::time_point<clock>;
        point m_start = clock::now();
        point m_snap = m_start;
        
        template<typename count_t>
        static count_t get_diff(const point& start, const point& end) {
            using duration_t = std::chrono::duration<count_t, time_ratio_t>;
            return std::chrono::duration_cast<duration_t>(end - start).count();
        }
    };
}

#endif // _TIMER_H_