#pragma once
#ifdef MODEA

int openDlgOptions(int* iArr, double* dArr); // decl Options.lib
namespace InpOptions{
static const int LaysCntReserv = 20; 
// offset in iArr;
static const int Dirs = 0;                    // 0
static const int NormDir = Dirs + 16 * 4 * 4; // 256

static const int LaysSzUpY = NormDir + 1;     // 257
static const int LaysSzUpX = LaysSzUpY + 1;   // 258
static const int LaysSzDn = LaysSzUpX + 1;    // 259

static const int SeedRnd = LaysSzDn + 1;      // 260
static const int LaysCnt = SeedRnd + 1;       // 261
static const int Restart = LaysCnt + 1;       // 262
static const int AMasks = Restart + 1;        // 263
              // next = AMasks + 16, add before AMasks !!!

// offset in dArr;
static const int kFillRnd = 0;                // 0
static const int kSigmaY = kFillRnd + 1;      // 1
static const int kSigmaX = kSigmaY + 1;       // 2
static const int kInertion = kSigmaX + 1;     // 3
static const int kBorder = kInertion + 1;     // 4
static const int kLays = kBorder + 1;         // 5
             //  next = kLays + LaysCntReserv, add before kLays !!!
//return
}; // *************************************************************
#endif  // MODEA
