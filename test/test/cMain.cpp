#include "cMain.h"
/*
	the main window (used as the launcher)
	we inherit from the wxFrame class 
*/

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

/*
	main constructer
*/
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper with c++	Kyle Kato Jan 26 2020 20:33", wxPoint(30,30), wxSize(800, 600)) {
	/*
		intialize our button array with new instances of wxButton
		intialize the wxGridSizer for the button array
	*/
	MAIN_BUTTON_ARRAY = new wxButton* [MAIN_FIELD_WIDTH * MAIN_FIELD_HEIGHT];
	wxGridSizer* MAIN_GRID = new wxGridSizer(MAIN_FIELD_WIDTH, MAIN_FIELD_HEIGHT, 0, 0);
	
	/*
		array for mines
	*/
	MINE_FIELD = new int[MAIN_FIELD_WIDTH * MAIN_FIELD_HEIGHT];

	/*
		create new font so text is more visible than the defaults
	*/
	wxFont NEW_FONT(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < MAIN_FIELD_WIDTH; x++) {
		for (int y = 0; y < MAIN_FIELD_HEIGHT; y++) {
			/*
				using (y * width + x), we turn a 2d array into a 1d system for the arrray of buttons
				create a new button, main is still parent window, and give unique ID based on position
				within the arrray
			*/
			MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x] = new wxButton(this, 10000 + (y * MAIN_FIELD_WIDTH + x));
			
			/*
				set each instance of button to have our new font
			*/
			MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->SetFont(NEW_FONT);

			/*
				we are telling the grid to occupy the avaialble space, and expand as necessary
			*/
			MAIN_GRID->Add(MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x], 1, wxEXPAND | wxALL);	
			
			/*
				bind all buttons to a specific funtion (OnButtonClicked)
			*/
			MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			/*
				default value of the mines
			*/
			MINE_FIELD[y * MAIN_FIELD_WIDTH + x] = 0;
		}
	}
	/*
		now we tell the parent window which sizer to use
	*/
	this->SetSizer(MAIN_GRID);
	MAIN_GRID->Layout();
}
/*
	destructor
*/
cMain::~cMain() {
	/*
		delete the array the holds the buttons, not the buttons or the sizers themselves
	*/
	delete[]MAIN_BUTTON_ARRAY;
}


void cMain::OnButtonClicked(wxCommandEvent& evt) {
	/*
		because we specified a unique ID for each button, we can now seek out the ID from 
		the array and determine which button was pressed using its x&y coordinates
	*/
	int x = (evt.GetId() - 10000) % MAIN_FIELD_WIDTH;
	int y = (evt.GetId() - 10000) / MAIN_FIELD_WIDTH;
	
	if (bFIRST_CLICK) {
		int NUM_MINES = 30;

		while (NUM_MINES) {
			int RAND_X = rand() % MAIN_FIELD_WIDTH;
			int RAND_Y = rand() % MAIN_FIELD_HEIGHT;

			/*
				check to makes sure cell isn't already occupied by another mine
				and check that cell isn't the first button clicked otherwise
				game would end istantly, so if location is valide => place mine.
			*/
			if (MINE_FIELD[RAND_Y * MAIN_FIELD_WIDTH + RAND_X] == 0 && RAND_X != x && RAND_Y != y) {
				MINE_FIELD[RAND_Y * MAIN_FIELD_WIDTH + RAND_X] = -1;
				NUM_MINES--;
			}

		}
		bFIRST_CLICK = false;
	}

	/*
		disable button, prevents any further events i.e presses
	*/
	MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->Enable(false);
	/*
		check if player hit a mine
	*/
	if (MINE_FIELD[y * MAIN_FIELD_WIDTH + x] == -1) {
		wxMessageBox("GAMEOVER >:(\nClick to restart");
		bFIRST_CLICK = true;
		for (int x = 0; x < MAIN_FIELD_WIDTH; x++) {
			for (int y = 0; y < MAIN_FIELD_HEIGHT; y++) {
				MINE_FIELD[y * MAIN_FIELD_WIDTH + x] = 0;
				MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->SetLabel("");
				MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->Enable(true);
			}
		}
	}
	else {
		/*
			count neighbouring mines 
		*/
		int MINE_COUNT = 0;
		for(int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + 1 >= 0 && x + i < MAIN_FIELD_WIDTH && y + j >= 0 && y + j < MAIN_FIELD_HEIGHT) {
					if (MINE_FIELD[y + j * MAIN_FIELD_WIDTH + (x + i)] == -1) {
						MINE_COUNT++;
					}
				}
			}
		}
		if (MINE_COUNT > 0) {
			MAIN_BUTTON_ARRAY[y * MAIN_FIELD_WIDTH + x]->SetLabel(std::to_string(MINE_COUNT));
		}
	}
	evt.Skip();
}