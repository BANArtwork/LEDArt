#ifndef SEGMENT_H
#define SEGMENT_H

#include <functional>

/**
 * @brief Class to define a segment of an LED 
 * strip and a mechanism for iterating over it.
 */
class Segment {

    public:

        Segment(int start, int count) : 
            _start { start },
            _count { count } {}

        int getStart() const {
            return _start;
        }

        int getCount() const {
            return _count;
        }

        void forEach(std::function<void(int index)> loopAction) const {
            int last = _start + _count;
            int i;
            for (i = _start; i < last; i++) {
                loopAction(i);
            }
        }

        bool isInSegment(int x) const {
            return (x >= _start) && (x < _start + _count);
        }

    private:

        int _start;
        int _count;
};

#endif
