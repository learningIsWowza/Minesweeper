#pragma once
 
#include "wx/wx.h"

/*
    Fundamentally, this Parent window is respsonible for distrubuting the events!
    wxWdigets has tools that handles events for us (holy frick thank goodness!!)
*/

class cMain : public wxFrame{


public:
    cMain();
    ~cMain();

public:
    int MAIN_FIELD_WIDTH = 10;
    int MAIN_FIELD_HEIGHT = 10;
    wxButton** MAIN_BUTTON_ARRAY;
    /*
        vars for minesweeper
    */
    int* MINE_FIELD  = nullptr;
    bool bFIRST_CLICK = true;


    void OnButtonClicked(wxCommandEvent& evt);


    /*
        this macro declares we need events handles, and enables the event handlers
    */
    wxDECLARE_EVENT_TABLE();
};

