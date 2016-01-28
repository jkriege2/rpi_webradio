#include "cgeventqueue.h"
#include "cgwidget.h"

CGEventQueue* CGEventQueue::inst=NULL;

CGEventQueue::CGEventQueue()
{
    if (!inst) inst=this;
}

CGEventQueue::~CGEventQueue()
{
    if (inst==this) inst=NULL;
}

bool CGEventQueue::hasEvents() const
{
    m_mutex.lock();
    bool res= !m_events.empty();
    m_mutex.unlock();
    return res;
}

void CGEventQueue::addEvent(CGEvent *e)
{
    if (!e) return;
    m_mutex.lock();
    m_events.push(e);
    std::cout<<"added event "<<e->toString()<<"\n";
    m_mutex.unlock();
}

CGEvent* CGEventQueue::popEvent()
{
    m_mutex.lock();
    CGEvent* e=m_events.front();
    m_events.pop();
    m_mutex.unlock();
    return e;
}

CGEvent* CGEventQueue::peekEvent()
{
    m_mutex.lock();
    CGEvent* e= m_events.front();
    m_mutex.unlock();
    return e;
}

void CGEventQueue::clear()
{
    m_mutex.lock();
    while (!m_events.empty()) m_events.pop();
    m_mutex.unlock();
}

CGEventQueue *CGEventQueue::instance()
{
    if (!inst) inst=new CGEventQueue();
    return inst;
}

void CGEventQueue::registerMainWidget(CGWidget *main)
{
    if (instance()) {
        instance()->thisRegisterMainWidget(main);
    }
}

void CGEventQueue::thisRegisterMainWidget(CGWidget *main)
{
    m_mutex.lock();
    m_mainWidget=main;
    m_mutex.unlock();
}

void CGEventQueue::deployEvents()
{
    if (instance()) {
        instance()->thisDeployEvents();
    }
}

void CGEventQueue::thisDeployEvents()
{
    while (hasEvents() && m_mainWidget) {
        CGEvent* e=popEvent();
        if (e) {
            m_mainWidget->postEvent(e);
            delete e;
        }
    }
}

