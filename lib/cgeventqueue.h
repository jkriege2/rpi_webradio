#ifndef CGMESSAGEQUEUE_H
#define CGMESSAGEQUEUE_H

#include <queue>
#include <mutex>
#include "cgbasics.h"
#include "cgevents.h"

class CGWidget; // forward


/** \brief thread-safe (mutex-locked) queue for CGEvent s */
class CGEventQueue
{
    public:
        explicit CGEventQueue();
        ~CGEventQueue();

        bool hasEvents() const;
        void addEvent(const CGEvent& e);
        CGEvent popEvent();
        CGEvent peekEvent();
        void clear();
        static CGEventQueue* instance();
        static void registerMainWidget(CGWidget* main);
        static void deployEvents();

    protected:
        void thisRegisterMainWidget(CGWidget* main);
        void thisDeployEvents();
        std::queue<CGEvent> m_events;
        mutable std::mutex m_mutex;
        static CGEventQueue* inst;
        CGWidget* m_mainWidget;
};

#endif // CGMESSAGEQUEUE_H
