#include "cApp.h"

wxIMPLEMENT_APP(cApp);	// pretty much the 'int main()' of wxWidgets 
	

cApp::cApp() {


}

cApp::~cApp() {


}

bool cApp::OnInit() {

	MAIN_FRAME_1 = new cMain();					// frame 1 = new instance of cMain() (our launcher)
	MAIN_FRAME_1->Show();						// show the main window (cMain())

	return true;
}