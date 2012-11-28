/*
 * textcommandinput.h
 *
 *  Created on: May 24, 2010
 *      Author: ivan
 */

#ifndef TEXTCOMMANDINPUT_H_
#define TEXTCOMMANDINPUT_H_

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>



// #include "vmolgui.h"
// #include "../command/vmolcommand.h"



/*
class CommandInputTextBox : public Fl_Input
{
    static void Copy_CB(Fl_Widget*, void *userdata)
    {
//        printf("*** COPY ***\n");
        CommandInputTextBox *in = (CommandInputTextBox*)userdata;
        in->copy(0);    // text selection clipboard
        in->copy(1);    // copy/paste clipboard
    }
    static void Paste_CB(Fl_Widget*, void *userdata)
    {
//        printf("*** PASTE ***\n");
        CommandInputTextBox *in = (CommandInputTextBox*)userdata;
        Fl::paste(*in);
    }

    static void callbackReturnKey(Fl_Widget *w, void *data)
    {
    	((CommandInputTextBox *) data)->handleCallbackReturnKey();
    }

    void handleCallbackReturnKey()
    {
//    	printf ("%s\n", (char *) this->value());
    	VmolCommand::getInstance()->executeCommand((string) this->value());
    	VmolGui::getInstance()->refreshGui();
    }

public:
    int handle(int e)
    {
        switch (e)
        {
            case FL_PUSH:
                // RIGHT MOUSE PUSHED? Popup menu on right click
                if ( Fl::event_button() == FL_RIGHT_MOUSE )
                {
                    Fl_Menu_Item rclick_menu[] =
                    {
                        { "Copy",   0, Copy_CB,  (void*)this },
                        { "Paste",  0, Paste_CB, (void*)this },
                        { 0 }
                    };

                    const Fl_Menu_Item *m = rclick_menu->popup(Fl::event_x(), Fl::event_y(), 0, 0, 0);
                    if ( m ) m->do_callback(0, m->user_data());
                    return(1);          // (tells caller we handled this event)
                }
                break;
            case FL_RELEASE:
                // RIGHT MOUSE RELEASED? Mask it from Fl_Input
                if ( Fl::event_button() == FL_RIGHT_MOUSE )
                {
                    return(1);          // (tells caller we handled this event)
                }
                break;
        }

        return(Fl_Input::handle(e));    // let Fl_Input handle all other events
    }

    CommandInputTextBox(int X,int Y,int W,int H,const char*L=0):Fl_Input(X,Y,W,H,L)
    {
    	CommandInputTextBox *in = (CommandInputTextBox*) this;
        in->callback(callbackReturnKey, (void *) this);
        in->when(FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED);
    }
};
*/

class CommandInputTextBox : public Fl_Input
{
    static void Copy_CB(Fl_Widget*, void *userdata);
    static void Paste_CB(Fl_Widget*, void *userdata);
    static void callbackReturnKey(Fl_Widget *w, void *data);
    void handleCallbackReturnKey();

public:
    int handle(int e);
    CommandInputTextBox(int X,int Y,int W,int H,const char*L=0);
};




#endif /* TEXTCOMMANDINPUT_H_ */
