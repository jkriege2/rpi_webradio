#ifndef CGMESSAGEQUEUE_H
#define CGMESSAGEQUEUE_H

#include <queue>
#include <mutex>
#include "cgbasics.h"

/** \brief thread-safe queue for CGEvent s */
class CGEventQueue
{
    public:
        CGEventQueue();
        ~CGEventQueue();

        bool hasEvents() const;
        void addEvent(const CGEvent& e);
        CGEvent popEvent();
        CGEvent peekEvent();
        void clear();
    protected:
        std::queue<CGEvent> m_events;
        mutable std::mutex m_mutex;
};

#endif // CGMESSAGEQUEUE_H
