#ifndef CGEVENTS_H
#define CGEVENTS_H

#include <string>


/** \brief baseclass for events */
class CGEvent {
     public:
        explicit CGEvent();
        virtual ~CGEvent() {}
        virtual std::string toString() const;
        void accept();
        inline bool accepted() const {
            return m_accepted;
        }
    protected:
        bool m_accepted;
};

/** \brief a mous clicked event */
class CGClickEvent: public CGEvent {
     public:
        enum Button {
            Button1=1,
            Button2=2,

            ButtonDefault=Button1,
            ButtonLeft=Button1,
            ButtonRight=Button2
        };

        explicit CGClickEvent(int x, int y, Button button=ButtonDefault);
        virtual ~CGClickEvent() {}
        virtual std::string toString() const;

        inline int x() const { return m_x; }
        inline int y() const { return m_y; }
        inline Button button() const { return m_button; }

    protected:
        Button m_button;
        int m_x;
        int m_y;
};

/** \brief a button-clicked event */
class CGButtonClickedEvent: public CGEvent {
     public:

        explicit CGButtonClickedEvent(int button);
        virtual ~CGButtonClickedEvent() {}
        virtual std::string toString() const;
        inline int button() const { return m_button; }
        inline int id() const { return m_button; }
    protected:
        int m_button;
};

/** \brief a button double-clicked event */
class CGButtonDoubleClickedEvent: public CGButtonClickedEvent {
     public:

        explicit CGButtonDoubleClickedEvent(int button): CGButtonClickedEvent(button) {}
        virtual ~CGButtonDoubleClickedEvent() {}
        virtual std::string toString() const;
};

/** \brief a input state changed event, the state() is the current state! */
class CGInputStateChanged: public CGEvent {
     public:

        explicit CGInputStateChanged(int id, bool m_state);
        virtual ~CGInputStateChanged() {}
        virtual std::string toString() const;
        inline int id() const { return m_id; }
        inline bool state() const { return m_state; }
    protected:
        int m_id;
        bool m_state;
};

/** \brief a scroll-event from e.g. a rotary encoder */
class CGInputScroll: public CGEvent {
     public:

        explicit CGInputScroll(int id, int inc);
        virtual ~CGInputScroll() {}
        virtual std::string toString() const;
        inline int id() const { return m_id; }
        inline int inc() const { return m_inc; }
    protected:
        int m_id;
        int m_inc;
};

/** \brief a key-pressed event */
class CGKeyEvent: public CGEvent {
     public:

        explicit CGKeyEvent(int key, bool shift=false, bool ctrl=false, bool alt=false);
        virtual ~CGKeyEvent() {}
        virtual std::string toString() const;

        inline int key() const { return m_key; }
        inline bool shift() const { return m_shift; }
        inline bool ctrl() const { return m_ctrl; }
        inline bool alt() const { return m_alt; }
    protected:
        int m_key;
        bool m_shift;
        bool m_ctrl;
        bool m_alt;
};

#endif // CGEVENTS_H
