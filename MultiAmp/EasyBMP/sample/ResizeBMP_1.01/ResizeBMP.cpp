/**************************************************************
*                                                             *
*  EasyBMP Cross-Platform Windows Bitmap Library Code Sample  * 
*                                                             *
*  Author: Paul Macklin                                       *
*   email: macklin01@users.sourceforge.net                    *
*     WWW: http://easybmp.sourceforge.net                     *
*                                                             *
*    file: ResizeBMP.cpp                                      *
*    date: 2-6-2006                                           *
* version: 1.00                                               *
*                                                             *
*   License: GPL v 2                                          *
* Copyright: 2005-2006 by the EasyBMP Project                 *
*                                                             *
* description: Code sample for EasyBMP library that resizes   *
*              any BMP to be either a specified width         *
*              height, or percentage of original size         *
*                                                             *
**************************************************************/

#include "EasyBMP.h"

using namespace std;

// use bilinear interpolation to get the desired pixel from the old image

RGBApixel GetPixel( BMP &Old , int i, int M , int j , int N )
{
 RGBApixel Output;
 double s = (i+0.0)*(Old.TellWidth()-1.0)/(M-1.0);
 double t = (j+0.0)*(Old.TellHeight()-1.0)/(N-1.0);
 
 // stability fixes for the weird case where Old is 1x1 
 if( Old.TellWidth() == 1 )
 { s = 0.0; }
 if( Old.TellHeight() == 1 )
 { t = 0.0; }
 
 // safety
 if( s < 1e-12 ){ s = 0.0; }
 if( s > Old.TellWidth() -1.0-1e-12 ){ s = Old.TellWidth()-1.0; }
 if( t < 1e-12 ){ t = 0.0; }
 if( t > Old.TellHeight() -1.0-1e-12 ){ t = Old.TellHeight()-1.0; }
 
 int I = (int) floor( s ); double ThetaS = s - I;
 int J = (int) floor( t ); double ThetaT = t - J;
 
 BYTE Upper;
 BYTE Lower;
 
 // special case: right edge

 if( I == Old.TellWidth()-1 )
 {
  if( J == Old.TellHeight()-1 )
  {
   Output.Red = Old(I,J)->Red;
   Output.Green = Old(I,J)->Green;
   Output.Blue = Old(I,J)->Blue;
   Output.Alpha = Old(I,J)->Alpha;
   return Output;
  }
  Output.Red = (BYTE) ( (1.0-ThetaT)*( Old(I,J)->Red + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Red + 0.0 ) );  
  Output.Green = (BYTE) ( (1.0-ThetaT)*( Old(I,J)->Green + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Green + 0.0 ) );  
  Output.Blue = (BYTE) ( (1.0-ThetaT)*( Old(I,J)->Blue + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Blue + 0.0 ) );  
  Output.Alpha = (BYTE) ( (1.0-ThetaT)*( Old(I,J)->Alpha + 0.0 )
                 +  ThetaT*( Old(I,J+1)->Alpha + 0.0 ) );  
  return Output;  
 }
 
 // special case: top edge
 
 if( J == Old.TellHeight()-1 )
 {
  if( I == Old.TellWidth()-1 )
  {
   Output.Red = Old(I,J)->Red;
   Output.Green = Old(I,J)->Green;
   Output.Blue = Old(I,J)->Blue;
   Output.Alpha = Old(I,J)->Alpha;
   return Output;
  }
  Output.Red = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Red + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Red + 0.0 ) );  
  Output.Green = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Green + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Green + 0.0 ) );  
  Output.Blue = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Blue + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Blue + 0.0 ) );  
  Output.Alpha = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Alpha + 0.0 )
                 +  ThetaS*( Old(I+1,J)->Alpha + 0.0 ) );  
  return Output; 
 }
 
 // interpolate red

 Upper = (BYTE) ( (1.0-ThetaS)*( Old(I,J+1)->Red + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Red + 0.0 ) );
 Lower = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Red + 0.0 )
       +  ThetaS*( Old(I+1,J)->Red + 0.0 ) );

 Output.Red = (BYTE) (  (1.0-ThetaT)*( Lower + 0.0 )
                + ThetaT*( Upper + 0.0 ) );
		
 // interpolate green
 
 Upper = (BYTE) ( (1.0-ThetaS)*( Old(I,J+1)->Green + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Green + 0.0 ) );
 Lower = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Green + 0.0 )
       +  ThetaS*( Old(I+1,J)->Green + 0.0 ) );
 Output.Green = (BYTE) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );
 
 // interpolate blue
 
 Upper = (BYTE) ( (1.0-ThetaS)*( Old(I,J+1)->Blue + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Blue + 0.0 ) );
 Lower = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Blue + 0.0 )
       +  ThetaS*( Old(I+1,J)->Blue + 0.0 ) );
 Output.Blue = (BYTE) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );

 // interpolate alpha
 
 Upper = (BYTE) ( (1.0-ThetaS)*( Old(I,J+1)->Alpha + 0.0 )
       +  ThetaS*( Old(I+1,J+1)->Alpha + 0.0 ) );
 Lower = (BYTE) ( (1.0-ThetaS)*( Old(I,J)->Alpha + 0.0 )
       +  ThetaS*( Old(I+1,J)->Alpha + 0.0 ) );
 Output.Alpha = (BYTE) (  (1.0-ThetaT)*( Lower + 0.0 )
                  + ThetaT*( Upper + 0.0 ) );
                  
 return Output;
}

int main( int argc, char* argv[] )
{
 char* DATE = "February 8";
 char* YEAR = "2006";
 char* AUTHOR = "Paul Macklin";
 char* LICENSE = "GPL v. 2";
 char* GROUP = "the EasyBMP Project";
 char* CONTACT = "http://easybmp.sourceforge.net";
 
 // determine if the user asked for help
 bool HelpMode = false;
 if( argc > 1 )
 {
  char HelpTemp [1025];
  strcpy( HelpTemp , argv[1] );
  if( HelpTemp[0] == '-' && HelpTemp[1] == '-' && 
      HelpTemp[2] == 'h' && HelpTemp[3] == 'e' &&
      HelpTemp[4] == 'l' && HelpTemp[5] == 'p' )
  { HelpMode = true; }
 }
 
 if( argc == 2 )
 {
  if( *(argv[1]+0) == '-' )
  { HelpMode = true; }
 }
 
 // if the user asked for help or is confused, spit out help info
 if( argc <= 1 || HelpMode )
 {
  cout << "\nResizeBMP usage:" << endl << endl
       << "To resize a BMP file to a percentage p of its original size:" << endl << endl
       << "          ResizeBMP -p <percentage> <file1> <file2> ..." << endl << endl
       << "To resize a BMP file to desired width:" << endl << endl
       << "          ResizeBMP -w <new width> <file1> <file2> ..." << endl << endl
       << "To resize a BMP file to desired height:" << endl << endl
       << "          ResizeBMP -h <new height> <file1> <file2> ..." << endl << endl
       << "To resize a BMP file in interactive mode:" << endl << endl
       << "          ResizeBMP <file1> <file2> ..." << endl << endl
       << "The program will append 'Resized' to the filename just before the '.bmp'" << endl
       << "Output will be a 24-bit file, unless the original was 32-bits." << endl << endl
       << "This gives this help information:" << endl
       << "          ResizeBMP --help" << endl << endl
       << " Created on " << DATE << ", " << YEAR << " by " << AUTHOR << "." << endl
       << " Uses the EasyBMP library, Version " << _EasyBMP_Version_ << "." << endl
       << " Licensed under " << LICENSE << " by " << GROUP << "." << endl
       << " Copyright (c) " << YEAR << " " << GROUP << endl
       << " Contact: " << CONTACT << endl << endl;
  return 1;
 }
 // spit out copyright / license information
 cout  << "\n Created on " << DATE << ", " << YEAR << " by " << AUTHOR << "." << endl
       << " Uses the EasyBMP library, Version " << _EasyBMP_Version_ << "." << endl
       << " Licensed under " << LICENSE << " by " << GROUP << "." << endl
       << " Copyright (c) " << YEAR << " " << GROUP << endl
       << " Contact: " << CONTACT << endl << endl;
       
 // figure out the mode of operation:
 bool WidthMode = false;
 bool HeightMode = false;
 bool PercentageMode = false;
 bool InteractiveMode = false;
 
 int StartingArgument = 3;
 
 int Percentage = 0;
 int NewWidth = 0;
 int NewHeight = 0;
 char ArgTemp [2049];
 strcpy( ArgTemp , argv[1] );
 
 if( ArgTemp[0] == '-' && ArgTemp[1] == 'w' )
 { WidthMode = true; NewWidth = (int) strtod( argv[2] , NULL ); }
 if( ArgTemp[0] == '-' && ArgTemp[1] == 'h' )
 { HeightMode = true; NewHeight = (int) strtod( argv[2] , NULL ); }
 if( ArgTemp[0] == '-' && ArgTemp[1] == 'p' )
 { PercentageMode = true; Percentage = (int) strtod( argv[2] , NULL ); }
 if( ArgTemp[0] != '-' )
 { InteractiveMode = true; StartingArgument = 1;}
 
 if( InteractiveMode )
 {
  cout << "\nEntering interactive mode ..." << endl << endl;
  cout << "Enter one of the following:" << endl
       << "p <desired percentage of original size>" << endl
       << "w <desired width>" << endl
       << "h <desired height>" << endl << endl;
  char InputString [2049];
  bool done = false;
  cin.get( InputString, 2048 );
  if( InputString[0] == 'p' )
  { PercentageMode = true; done = true;}
  if( InputString[0] == 'w' )
  { WidthMode = true; done = true;}
  if( InputString[0] == 'h' )
  { HeightMode = true; done = true;}
  if( !done )
  {
   cout << endl << "**Error** Follow the directions!" << endl << endl;
   return 1;
  }
  // extract the settings values
  
  InputString[0] = ' ';
  if( PercentageMode )
  { Percentage = (int) strtod( InputString , NULL ); }
  if( WidthMode )
  { NewWidth = (int) strtod( InputString , NULL ); }
  if( HeightMode )
  { NewHeight = (int) strtod( InputString , NULL ); }
 }

 int k;
 for( k=StartingArgument ; k < argc ; k++ )
 {
  BMFH bmfh = GetBMFH( argv[k] );
  // if it isn't a BMP file, don't do anything!
  BMIH bmih = GetBMIH( argv[k] );
  int i,j;
  
  if( bmfh.bfType == 19778 )
  {
   cout << "Processing file " << argv[k] << " ..." << endl;
   BMP ImageIn;
   ImageIn.ReadFromFile( argv[k] );
  
   if( PercentageMode )
   {
    NewWidth = (int) ( ImageIn.TellWidth() * Percentage / 100.0 );
    NewHeight = (int) ( ImageIn.TellHeight() * Percentage / 100.0 );
   } // end percentage mode
   if( WidthMode )
   {
    NewHeight = (int) (  ( NewWidth*ImageIn.TellHeight() + 0.0 )/( ImageIn.TellWidth() + 0.0 ) );
   } // end width mode
   if( HeightMode )
   {
    NewWidth = (int) (  ( NewHeight*ImageIn.TellWidth() + 0.0 )/( ImageIn.TellHeight() + 0.0 ) );
   } // end height mode
   
   BMP ImageOut;
   ImageOut.SetSize( NewWidth, NewHeight );
   
   if( ImageIn.TellBitDepth() == 32 )
   { ImageOut.SetBitDepth( 32 ); }
   else
   { ImageOut.SetBitDepth( 24 ); }
    
   for( j=0 ; j <ImageOut.TellHeight() ; j++)
   {
    for( i=0 ; i < ImageOut.TellWidth() ; i++)
    {
     RGBApixel Temp = GetPixel( ImageIn , i , ImageOut.TellWidth() , j , ImageOut.TellHeight() );  
     *ImageOut(i,j) = Temp;
    }
   }
   
   // determine the output filename  
   char OutputName [2049];
   strcpy( OutputName , argv[k] );
   int Length = strlen(OutputName);
   OutputName[Length-4] = 'R';
   OutputName[Length-3] = 'e';
   OutputName[Length-2] = 's';
   OutputName[Length-1] = 'i';
   OutputName[Length]   = 'z';
   OutputName[Length+1] = 'e';
   OutputName[Length+2] = 'd';
   OutputName[Length+3] = '\0';
   strcat( OutputName , ".bmp");   
   
   cout << "\tSaving to " << OutputName << " ..." << endl;
   
   ImageOut.WriteToFile( OutputName );   
  }
  else
  {
   cout << "Skipping file " << argv[k] 
        << " (not a bmp, or unsupported format) ..." << endl;
  }
 
 }
 
 return 0;
}
