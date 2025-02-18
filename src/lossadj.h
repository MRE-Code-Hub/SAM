/*
BSD 3-Clause License

Copyright (c) Alliance for Sustainable Energy, LLC. See also https://github.com/NREL/SAM/blob/develop/LICENSE
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef __adjfac_h
#define __adjfac_h

#include <vector>

#include <wx/panel.h>


#include "object.h"


/* Hourly adjustment factors:
	example SSC variables:

	adjust:factor
	adjust:en_hourly
	adjust:hourly
    adjust:en_timeindex
    adjust:timeindex
	adjust:en_periods
	adjust:periods

    updated for more flexible naming and flattened for better ssc/SAM translation and code generation.
*/

class wxButton;
class wxTextCtrl;
class wxStaticText;
class Case;
class VarValue;

#define EVT_HOURLYFACTORS(i,f) EVT_BUTTON(i,f)

class AFLossAdjustmentCtrl : public wxPanel
{
public:
	AFLossAdjustmentCtrl( wxWindow *parent, int id,
		const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize);

//    void Write(VarValue*);
//    bool Read(VarValue*);
    void Write(Case*,size_t);
    bool Read(Case*, size_t);

	struct FactorData
	{
		float constant; // updated from "factor" to "constant" 6/19/15
        size_t analysis_period;
        size_t mode;
        bool show_mode;
		bool en_hourly;
		std::vector<double> hourly;
        

        bool en_timeindex;
        std::vector<double> timeindex;

		bool en_periods;
		matrix_t<double> periods; // stored as n x 3 matrix: columns: [start hour] [length hour] [factor]
        wxString descriptive_text;
	};

	bool DoEdit();

    void SetDescription(const wxString& s);
    wxString GetDescription();

    void SetMode(const size_t& p) { mMode = p; }
    size_t GetMode() { return mMode; }

    void SetShowMode(const bool& b) { mShowMode = b; };
    bool GetShowMode() { return mShowMode; };

    void SetAnalysisPeriod(const size_t& p)
    {
        mAnalysisPeriod = p;
    }

    void SetDataLabel(const wxString& s)
    {
        mDataLabel = s;
    }
    wxString GetDataLabel()
    {
        return mDataLabel;
    }

    void SetAnnualEnabled(const bool& e) { mAnnualEnabled = e; }
    bool GetAnnualEnabled() { return mAnnualEnabled; }

    void SetWeeklyEnabled(const bool& e) { mWeeklyEnabled = e; }
    bool GetWeeklyEnabled() { return mWeeklyEnabled; }

    void SetName(const wxString& _name) { m_name = _name; }
    wxString GetName() { return m_name; }

private:
	void OnPressed(wxCommandEvent &);
	void UpdateText();
	
	wxButton *m_button;
    wxStaticText* m_label;
    wxString mDataLabel;
	FactorData m_data;
    size_t mAnalysisPeriod;
    size_t mMode;
    bool mShowMode;
    bool mAnnualEnabled;
    bool mWeeklyEnabled;
    wxString m_description;
    wxString m_name;

	DECLARE_EVENT_TABLE();
};

#endif

