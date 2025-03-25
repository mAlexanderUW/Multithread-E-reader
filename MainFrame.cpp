#include "MainFrame.h"
#include <wx/generic/statbmpg.h>

enum IDs
{
	NEXTBUTTON_ID = 2,
	QUITBUTTON_ID = 3,
};


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	createControls();
	createSizers();
	bindEvents();
	createThreads();
}

void MainFrame::createControls()
{
	wxInitAllImageHandlers();
	SetIcon(wxIcon(wxT("BOOK_ICON")));

	wxFont titleFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxWANTS_CHARS);
	panel->SetFont(mainFont);
	

	titleText = new wxStaticText(panel, wxID_ANY, "Moby Dick");
	titleText->SetFont(titleFont);

	bookText = new wxStaticText(panel, wxID_ANY, 
		"This isn't viable as an E-Reader as it only has a next function. \nThis is more to demostrate having a read and write thread with the next \nbutton being a secondary mutex that serves to act like an event that\nunlocks a thread.");

	nextButton = new wxButton(panel, NEXTBUTTON_ID, "Next (Unlock)",
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	quitButton = new wxButton(panel, QUITBUTTON_ID, "Quit", 
		wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	
}
void MainFrame::createSizers()
{
	mainSizer = new wxBoxSizer(wxVERTICAL);
	horzSizer = new wxBoxSizer(wxHORIZONTAL);
	vertLeftSizer = new wxBoxSizer(wxVERTICAL);
	vertRightSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->Add(titleText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	mainSizer->Add(bookText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	horzSizer-> Add(vertLeftSizer, wxSizerFlags().Expand().Proportion(1));
	vertLeftSizer->Add(quitButton, wxSizerFlags().Left());

	horzSizer->Add(vertRightSizer, wxSizerFlags().Expand().Proportion(1));
	vertRightSizer->Add(nextButton, wxSizerFlags().Right());

	mainSizer->Add(horzSizer, wxSizerFlags().Expand().Proportion(1));

	outerBorder = new wxGridSizer(1);
	outerBorder->Add(mainSizer, wxSizerFlags().Border(wxALL, 25));

	panel->SetSizer(outerBorder);
	outerBorder->SetSizeHints(this);
}

void MainFrame::bindEvents()
{
	quitButton->Bind(wxEVT_BUTTON, &MainFrame::QuitButtonClicked, this);
	quitButton->Bind(wxEVT_TEXT_ENTER, &MainFrame::QuitButtonClicked, this);
	nextButton->Bind(wxEVT_BUTTON, &MainFrame::NextButtonClicked, this);
	nextButton->Bind(wxEVT_TEXT_ENTER, &MainFrame::NextButtonClicked, this);
}
void MainFrame::createThreads()
{
	std::thread readThread(&Threads::thread1, &T);
	std::thread writeThread(&Threads::thread2, &T);

	readThread.join();
	writeThread.join();
}

void MainFrame::NextButtonClicked(wxCommandEvent& evt)
{
	bookText->SetLabel(T.getSharedTxt());
	T.releaseEvent();
	outerBorder->SetSizeHints(this);
}
void MainFrame::QuitButtonClicked(wxCommandEvent& evt)
{
	Close(true);
}
