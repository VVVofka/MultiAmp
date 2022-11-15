#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    


#ifndef NORMAL_TO_AREA
#define NORMAL_TO_AREA(POS, WIDTH) (float(2 * (POS) + 1) / (WIDTH) - 1.f)
#endif    
