//---------------------------------------------------------------------------
#include <windows.h>
#include <vcl.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#pragma hdrstop

#include "UFuzzy.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VaClasses"
#pragma link "VaComm"
#pragma resource "*.dfm"

TFmFuzzy *FmFuzzy;

//---------------------------------------------------------------------

std::vector <float> tip_cheap(4561);
std::vector <float> tip_average(4561);
std::vector <float> tip_gorgeous(4561);
std::vector <float> tip(4561);

float x=0;
float y=0;
float posicao_do_grafico = 0;
float posicao_do_grafico_distancia = 0;
float posicao_do_grafico_temperatura = 0;

// Vari�veis Fuzzy.
float fiTemperatura = 0;
float fiDistancia    = 0;
float foTip     = 0;
float fop_rule1 = 0;
float fop_rule2 = 0;
float fop_rule3 = 0;

// Vari�veis de auxilio ao c�lculo da centr�ide.
float sum = 0;
float total_area = 0;
float velocidade = 0;

// Entradas para o sistema.
float temperatura = 23;
float distancia = 0;
int speedBefore = 0;
int first = 0;
//---------------------------------------------------------------------

// Fun��o Triangular
float trimf(float x, float a, float b, float c)
{
	float ua = 0;

	if (x <= a)
		ua = 0;
	else if ((a < x) && (x <= b))
		ua = ((x - a) / (b - a));
	else if ((b < x) && (x <= c))
		ua = ((x - c) / (b - c));
	else if (x > c)
		ua = 0;

	return(ua);
}

//---------------------------------------------------------------------

// Fun��o Trapezoidal
float trapmf(float x, float a, float b, float c, float d)
{
	float ua = 0;

	if (x <= a)
		ua = 0;
	else if ((a < x) && (x <= b))
		ua = ((x - a) / (b - a));
	else if ((b <= x) && (x <= c))
		ua = 1;
	else if ((c < x) && (x <= d))
		ua = ((d - x) / (d - c));
	else if (x > d)
		ua = 0;

	return(ua);
}

//---------------------------------------------------------------------

float min_val(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

//---------------------------------------------------------------------

float max_val(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}


//---------------------------------------------------------------------------

void Fuzzy()
{

	// 1� regra - If temperatura is poor or distancia is rancid, tip is cheap
	if ((temperatura >= 23 && temperatura <= 27) || (distancia >= 0 && distancia <= 25))
	{
		// Fuzzificar as entradas.
		fiTemperatura = trapmf(temperatura, 22, 23, 24, 27);
		fiDistancia    = trapmf(distancia,-1, 0, 5, 15);

		// Aplica��o dos operadores Fuzzy.
		fop_rule1 = max_val(fiTemperatura,fiDistancia);
		// Aplica��o do M�todo de Implica��o (valores m�nimos).
		x=0;
		y=0;
		for (int a=0; a<=4560; a++)
		{
			y = trimf(x,0,760,1520);

			if (y >= fop_rule1)
			{
				tip_cheap.at(a) = fop_rule1;
			}
			else
			{
				tip_cheap.at(a) = y;
			}

			x=x+1;
		}
	}




	// 2.1� regra - If temperatura is good, tip is average
	if (temperatura >= 24 && temperatura <= 32)
	{
		// Fuzzificar as entradas.
		fiTemperatura = trimf(temperatura, 24, 28, 32);

		// Aplica��o dos operadores Fuzzy.
		fop_rule2 = max_val(fiTemperatura,0);

		 // Aplica��o do M�todo de Implica��o (valores m�nimos).
		x=0;
		y=0;
		for (int a=0; a<=4560; a++)
		{
			y = trimf(x,1520,2280,3040);

			if (y >= fop_rule2)
			{
				tip_average.at(a) = fop_rule2;
			}
			else
			{
				tip_average.at(a) = y;
			}

			x=x+1;
		}
	}



	// 3.1� regra - If temperatura is excellent or distancia is delicious, tip is generous
	if ((temperatura >= 29 && temperatura <= 33) || (distancia >= 25 && distancia <= 50))
	{
		// Fuzzificar as entradas.
		fiTemperatura = trapmf(temperatura,29, 32, 33, 34);
		fiDistancia    = trapmf(distancia,35, 45, 50, 51);

		// Aplica��o dos operadores Fuzzy.
		fop_rule3 = max_val(fiTemperatura,fiDistancia);

		// Aplica��o do M�todo de Implica��o (valores m�nimos).
		x=0;
		y=0;
		for (int a=0; a<=4560; a++)
		{
			y = trimf(x,3040,3800,4560);

			if (y >= fop_rule3)
			{
				tip_gorgeous.at(a) = fop_rule3;
			}
			else
			{
				tip_gorgeous.at(a) = y;
			}

			x=x+1;
		}
	}




	// Aplica��o do M�todo de Agrega��o.
	for (int a=0; a<=4560; a++)
	{
		if (a >= 0 && a <= 1520)
		{
			tip.at(a) = tip_cheap.at(a);
		}

		if (a >= 1520 && a <= 3040)
		{
			tip.at(a) = tip_average.at(a);
		}

		if (a > 3040 && a <= 4560)
		{
			tip.at(a) = tip_gorgeous.at(a);
		}
	}


	// Implica��o dos antecedentes pelo consequente.
	x = 0;
	total_area = 0;
	sum = 0;
	for (int a=0; a<=4560; a++)
	{
		total_area = total_area + tip.at(a);
		sum = sum + (x * tip.at(a));

		x=x+1;
	}

	// C�lculo da Centr�ide.
	velocidade = sum/total_area;
	FmFuzzy->Label1->Caption = FloatToStrF(velocidade,ffFixed,10,0);
	posicao_do_grafico = velocidade;



	for (int a=0; a<=4560; a++)
	{
		FmFuzzy->Chart4->Series[0]->YValues->Value[a] = tip.at(a);
	}

	FmFuzzy->Chart3->Refresh();
	FmFuzzy->Chart4->Refresh();
}


//---------------------------------------------------------------------------

__fastcall TFmFuzzy::TFmFuzzy(TComponent* Owner)
	: TForm(Owner)
{




}
//---------------------------------------------------------------------------
void __fastcall TFmFuzzy::FormCreate(TObject *Sender)
{
	// Expande o gr�fico para comportar a quantidade de amostras contidas em max_tela.
	for (unsigned int a = 0; a <= 10; a++)
	{
		Chart1->Series[0]->AddY(0);
		Chart1->Series[1]->AddY(0);
		Chart1->Series[2]->AddY(0);
	}
	for (unsigned int a = 0; a <= 50; a++)
	{
		Chart2->Series[0]->AddY(0);
		Chart2->Series[1]->AddY(0);
	}
	for (unsigned int a = 0; a <= 4560; a++)
	{
		Chart3->Series[0]->AddY(0);
		Chart3->Series[1]->AddY(0);
		Chart3->Series[2]->AddY(0);
		Chart4->Series[0]->AddY(0);
	}

	// Atualiza o chart.
	Chart1->Refresh();
	Chart2->Refresh();
	Chart3->Refresh();
	Chart4->Refresh();


	x = 23; // Inicializa x em 21 para corresponder ao in�cio do seu eixo X
	for (int a = 0; a <= 10; a++) { // Itera do valor inicial at� 10 passos � frente
		// Calcula os valores de pertin�ncia com base em 'x'
		// As fun��es abaixo devem ser ajustadas para refletir as curvas da sua imagem
		Chart1->Series[0]->AddXY(x, trapmf(x, 22, 23, 24, 27)); // Substitua pelos par�metros corretos
		Chart1->Series[1]->AddXY(x, trimf(x, 24, 28, 32));      // Substitua pelos par�metros corretos
		Chart1->Series[2]->AddXY(x, trapmf(x, 29, 32, 33, 34)); // Substitua pelos par�metros corretos

		x++; // Incrementa x a cada itera��o para mover ao longo do eixo X
	}



	x = 0;
	for (int a = 0; a <= 50; a++) {
		Chart2->Series[0]->YValues->Value[a] = trapmf(x, -1, 0, 5, 15);
		Chart2->Series[1]->YValues->Value[a] = trapmf(x, 35, 45, 50, 51);
		x=x+1;
	}

	x=0;
	for (int a=0; a<=4560; a++)
	{
		Chart3->Series[0]->YValues->Value[a] = trimf(x,0,760,1520);
		Chart3->Series[1]->YValues->Value[a] = trimf(x,1520,2280,3040);
		Chart3->Series[2]->YValues->Value[a] = trimf(x,3040,3800,4560);
		x=x+1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFmFuzzy::tbTemperaturaChange(TObject *Sender)
{
	temperatura = tbTemperatura->Position ;
	posicao_do_grafico_temperatura = tbTemperatura->Position ;
	Label5->Caption = (static_cast<int>(posicao_do_grafico_temperatura));


	Chart1->Refresh();

	Fuzzy();
}
//---------------------------------------------------------------------------
void __fastcall TFmFuzzy::tbDistanciaChange(TObject *Sender)
{
	tbDistancia->Position = ((tbDistancia->Position) / 5) * 5;
	distancia = tbDistancia->Position;
	posicao_do_grafico_distancia = tbDistancia->Position;
	Label6->Caption = tbDistancia->Position;

	Chart2->Refresh();

	Fuzzy();
}
//---------------------------------------------------------------------------
void __fastcall TFmFuzzy::Chart4AfterDraw(TObject *Sender)
{
	double xi, xf, yi, yf;

	xi=Chart4->BottomAxis->CalcPosValue(posicao_do_grafico);
	yi=Chart4->LeftAxis->CalcPosValue(Chart4->LeftAxis->Minimum)+5;
	xf=Chart4->BottomAxis->CalcPosValue(posicao_do_grafico)+1;
	yf=Chart4->LeftAxis->CalcPosValue(Chart4->LeftAxis->Maximum)-5;
	Chart4->Canvas->Pen->Style=psSolid;
	Chart4->Canvas->Pen->Color=clBlack;
	Chart4->Canvas->Rectangle(xi,yi,xf,yf);
}
//---------------------------------------------------------------------------
void __fastcall TFmFuzzy::Chart1AfterDraw(TObject *Sender)
{
	double xi, xf, yi, yf;

	xi=Chart1->BottomAxis->CalcPosValue(posicao_do_grafico_temperatura);
	yi=Chart1->LeftAxis->CalcPosValue(Chart1->LeftAxis->Minimum)+5;
	xf=Chart1->BottomAxis->CalcPosValue(posicao_do_grafico_temperatura)+1;
	yf=Chart1->LeftAxis->CalcPosValue(Chart1->LeftAxis->Maximum)-5;
	Chart1->Canvas->Pen->Style=psSolid;
	Chart1->Canvas->Pen->Color=clBlack;
	Chart1->Canvas->Rectangle(xi,yi,xf,yf);
}
//---------------------------------------------------------------------------

void __fastcall TFmFuzzy::Chart2AfterDraw(TObject *Sender)
{
	double xi, xf, yi, yf;

	xi=Chart2->BottomAxis->CalcPosValue(posicao_do_grafico_distancia);
	yi=Chart2->LeftAxis->CalcPosValue(Chart2->LeftAxis->Minimum)+5;
	xf=Chart2->BottomAxis->CalcPosValue(posicao_do_grafico_distancia)+1;
	yf=Chart2->LeftAxis->CalcPosValue(Chart2->LeftAxis->Maximum)-5;
	Chart2->Canvas->Pen->Style=psSolid;
	Chart2->Canvas->Pen->Color=clBlack;
	Chart2->Canvas->Rectangle(xi,yi,xf,yf);
}
//---------------------------------------------------------------------------

void __fastcall TFmFuzzy::Chart3AfterDraw(TObject *Sender)
{
	double xi, xf, yi, yf;

	xi=Chart3->BottomAxis->CalcPosValue(posicao_do_grafico);
	yi=Chart3->LeftAxis->CalcPosValue(Chart3->LeftAxis->Minimum)+5;
	xf=Chart3->BottomAxis->CalcPosValue(posicao_do_grafico)+1;
	yf=Chart3->LeftAxis->CalcPosValue(Chart3->LeftAxis->Maximum)-5;
	Chart3->Canvas->Pen->Style=psSolid;
	Chart3->Canvas->Pen->Color=clBlack;
	Chart3->Canvas->Rectangle(xi,yi,xf,yf);
}
//---------------------------------------------------------------------------


// PORTA SERIAL ---------------------------------------------------------

void __fastcall TFmFuzzy::VaComm1RxChar(TObject *Sender, int Count)
{
	if (CheckBox1->Checked == false) {
	CheckBox1->Font->Style = CheckBox1->Font->Style >> fsBold;

	Label16->Caption = "Dados Recebidos";
	first = 0;

	char *buffer = new char[Count+1];
	memset(buffer, 0, Count+1); // Limpa o buffer
	VaComm1->ReadBuf(buffer, Count); // L� os dados recebidos
	AnsiString data(buffer, Count); // Cria uma AnsiString com os dados recebidos
	Memo1->Lines->Add(data); // Adicione os dados recebidos ao TMemo
	delete [] buffer; // Libera o buffer

    	AnsiString strDistance, strTemperature;
	int indexD = data.Pos("D");
	int indexT = data.Pos("T");
	if (indexD > 0 && indexT > indexD) {
		strDistance = data.SubString(indexD + 1, indexT - indexD - 1);
		strTemperature = data.SubString(indexT + 1, data.Length() - indexT);
		// Converta e use os valores de dist�ncia e temperatura como necess�rio
		// Exemplo: Convertendo para float e exibindo no Memo1
		float distance = atof(strDistance.c_str());
		float temperature = atof(strTemperature.c_str());


	distancia = distance;
	posicao_do_grafico_distancia = distancia;
	Label7->Caption = FloatToStrF(distancia,ffFixed,10,2);

	temperatura = temperature;
	posicao_do_grafico_temperatura = temperatura;
	Label8->Caption = FloatToStrF(temperatura,ffFixed,10,2);


	Chart1->Refresh();
	Chart2->Refresh();

	Fuzzy();

	VaComm1->WriteText(velocidade/14.9);   } }

	else{
		if (first == 0) {
		   Memo1->Clear();
		   first = first + 1;
		}

		CheckBox1->Font->Style = CheckBox1->Font->Style << fsBold;
		Label16->Caption = "Dados Enviados";
		Fuzzy();

		if (int(velocidade/14.91) == speedBefore)  {

			Fuzzy();       }

		else{
        VaComm1->WriteText(int(velocidade/14.91));
		Memo1->Lines->Add(int(velocidade/14.91));

		speedBefore = int(velocidade/14.91);


		}


   }
}





void __fastcall TFmFuzzy::Image1Click(TObject *Sender)
{
ShellExecute(0, L"open", L"https://www.unoesc.edu.br/", NULL, NULL, SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------



void __fastcall TFmFuzzy::Image2Click(TObject *Sender)
{
ShellExecute(0, L"open", L"https://www.instagram.com/lapc_unoesc/", NULL, NULL, SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

