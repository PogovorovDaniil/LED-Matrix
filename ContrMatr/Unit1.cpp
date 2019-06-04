// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
String str;
// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (OpenDialog1->Execute() == True)
	{
		Image1->Picture->LoadFromFile(OpenDialog1->FileName);
		Image2->Picture->LoadFromFile(OpenDialog1->FileName);

		Image1->Picture->Bitmap->Canvas->StretchDraw(Rect(0, 0, 12, 12),Image2->Picture->Bitmap);
		Image1->Picture->Bitmap->SetSize(12, 12);

		TColor Color;
		int R,G,B;
		str = "";

		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				Color = Image1->Picture->Bitmap->Canvas->Pixels[i][j];

				R = GetRValue(Color);
				G = GetGValue(Color);
				B = GetBValue(Color);
				str += IntToStr(R) + " " + IntToStr(G) + " " + IntToStr(B);
			}
		}
	}
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	IdHTTP1->Get(Edit1->Text + "?str="+str);
}
// ---------------------------------------------------------------------------