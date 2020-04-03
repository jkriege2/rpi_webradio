#include "cgprecomp.h"
#include "cgevents.h"
#include "cgbasics.h"


CGClickEvent::CGClickEvent(int x, int y, CGClickEvent::Button button)
{
    this->m_x=x;
    this->m_y=y;
    this->m_button=button;
}

std::string CGClickEvent::toString() const
{
    return cgFormat("cgClickEvent(x=%d, y=%d, button=#%d)", m_x,m_y,(int)m_button);
}


CGEvent::CGEvent()
{
    m_accepted=false;
}

std::string CGEvent::toString() const
{
    return std::string("cgEvent()");
}

void CGEvent::accept()
{
    m_accepted=true;
}


CGButtonClickedEvent::CGButtonClickedEvent(int button)
{
    this->m_button=button;
}

std::string CGButtonClickedEvent::toString() const
{
    return cgFormat("CGButtonClickedEvent(button #%d)", m_button);
}


CGKeyEvent::CGKeyEvent(int key, bool shift, bool ctrl, bool alt)
{
    this->m_key=key;
    this->m_shift=shift;
    this->m_ctrl=ctrl;
    this->m_alt=alt;
}

std::string CGKeyEvent::toString() const
{
    return cgFormat("cgKeyEvent(key #%d, shift=%s, ctrl=%s, alt=%s)", m_key, cgBoolToStr(m_shift).c_str(), cgBoolToStr(m_ctrl).c_str(), cgBoolToStr(m_alt).c_str());
}


CGInputStateChanged::CGInputStateChanged(int input, bool state)
{
    m_id=input;
    m_state=state;
}

std::string CGInputStateChanged::toString() const
{
    return cgFormat("CGInputStateChanged(id #%d, state=%s)", m_id, cgBoolToStr(m_state).c_str());
}


CGInputScroll::CGInputScroll(int id, int inc)
{
    m_id=id;
    m_inc=inc;
}

std::string CGInputScroll::toString() const
{
    return cgFormat("CGInputScroll(id #%d, inc=%d)", m_id, m_inc);
}


std::string CGButtonDoubleClickedEvent::toString() const
{
    return cgFormat("CGButtonDoubleClickedEvent(button #%d)", m_button);
}
