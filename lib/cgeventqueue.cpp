#include "cgeventqueue.h"

CGEventQueue::CGEventQueue()
{

}

CGEventQueue::~CGEventQueue()
{

}

bool CGEventQueue::hasEvents() const
{
    m_mutex.lock();
    bool res= !m_events.empty();
    m_mutex.unlock();
    return res;
}

void CGEventQueue::addEvent(const CGEvent &e)
{
    m_mutex.lock();
    m_events.push(e);
    m_mutex.unlock();
}

CGEvent CGEventQueue::popEvent()
{
    m_mutex.lock();
    CGEvent e=m_events.front();
    m_events.pop();
    m_mutex.unlock();
    return e;
}

CGEvent CGEventQueue::peekEvent()
{
    m_mutex.lock();
    CGEvent e= m_events.front();
    m_mutex.unlock();
    return e;
}

void CGEventQueue::clear()
{
    m_mutex.lock();
    while (!m_events.empty()) m_events.pop();
    m_mutex.unlock();
}

