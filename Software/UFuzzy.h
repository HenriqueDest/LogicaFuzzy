//---------------------------------------------------------------------------

#ifndef UFuzzyH
#define UFuzzyH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "VaClasses.hpp"
#include "VaComm.hpp"
#include <System.SysUtils.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include<windows.h>
//---------------------------------------------------------------------------
class TFmFuzzy : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TChart *Chart2;
	TLineSeries *Series5;
	TChart *Chart3;
	TLineSeries *Series7;
	TLineSeries *Series8;
	TTrackBar *tbTemperatura;
	TTrackBar *tbDistancia;
	TChart *Chart4;
	TLineSeries *Series6;
	TLineSeries *Series4;
	TLineSeries *LineSeries3;
	TStatusBar *StatusBar1;
	TChart *Chart1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TVaComm *VaComm1;
	TLabel *Label7;
	TLabel *Label8;
	TCheckBox *CheckBox1;
	TMemo *Memo1;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TImage *Image1;
	TLineSeries *Series1;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TImage *Image2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tbTemperaturaChange(TObject *Sender);
	void __fastcall tbDistanciaChange(TObject *Sender);
	void __fastcall Chart4AfterDraw(TObject *Sender);
	void __fastcall Chart1AfterDraw(TObject *Sender);
	void __fastcall Chart2AfterDraw(TObject *Sender);
	void __fastcall Chart3AfterDraw(TObject *Sender);
	void __fastcall VaComm1RxChar(TObject *Sender, int Count);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFmFuzzy(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmFuzzy *FmFuzzy;
//---------------------------------------------------------------------------
#endif
