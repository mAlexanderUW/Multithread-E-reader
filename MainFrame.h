#pragma once
#include <wx/wx.h>
#include <wx/generic/statbmpg.h>
#include "Threads.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void createControls();
	void createSizers();
	void bindEvents();
	void createThreads();
	void NextButtonClicked(wxCommandEvent& evt);
	void QuitButtonClicked(wxCommandEvent& evt);

	wxPanel* panel;
	wxStaticText* titleText;
	wxStaticText* bookText;
	wxButton* nextButton;
	wxButton* quitButton;

	wxBoxSizer* mainSizer;
	wxBoxSizer* horzSizer;
	wxBoxSizer* vertLeftSizer;
	wxBoxSizer* vertRightSizer;
	wxGridSizer* outerBorder;

	Threads T;

};

