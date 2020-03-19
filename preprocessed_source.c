# 1 "SGL.c"
# 1 "c:/program files/tcc/include/math.h" 1
# 13 "c:/program files/tcc/include/math.h"
# 1 "c:/program files/tcc/include/_mingw.h" 1
# 27 "c:/program files/tcc/include/_mingw.h"
# 1 "c:/program files/tcc/include/stddef.h" 1



typedef unsigned long long size_t;
typedef long long ssize_t;
typedef unsigned short wchar_t;
typedef long long ptrdiff_t;
typedef long long intptr_t;
typedef unsigned long long uintptr_t;



typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;



typedef signed long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;



typedef unsigned long long int uint64_t;
# 37 "c:/program files/tcc/include/stddef.h"
void *alloca(size_t size);
# 28 "c:/program files/tcc/include/_mingw.h" 2
# 1 "c:/program files/tcc/include/stdarg.h" 1
# 34 "c:/program files/tcc/include/stdarg.h"
typedef char *va_list;
# 76 "c:/program files/tcc/include/stdarg.h"
typedef va_list __gnuc_va_list;
# 29 "c:/program files/tcc/include/_mingw.h" 2
# 104 "c:/program files/tcc/include/_mingw.h"
typedef long __time32_t;




typedef long long __time64_t;







typedef __time64_t time_t;





typedef wchar_t wctype_t;




typedef unsigned short wint_t;


typedef int errno_t;


typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
typedef struct localeinfo_struct _locale_tstruct,*_locale_t;
# 14 "c:/program files/tcc/include/math.h" 2

struct exception;

#pragma pack(push,8)
# 76 "c:/program files/tcc/include/math.h"
  struct _exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




  struct _complex {
    double x,y;
  };
# 99 "c:/program files/tcc/include/math.h"
  extern double *_imp___HUGE;
# 108 "c:/program files/tcc/include/math.h"
  int  abs(int _X);
  long  labs(long _X);

  double  acos(double _X);
  double  asin(double _X);
  double  atan(double _X);
  double  atan2(double _Y,double _X);


  extern double  _copysign (double _Number,double _Sign);
  extern double  _chgsign (double _X);

  double  cos(double _X);
  double  cosh(double _X);
  double  exp(double _X);
  double  expm1(double _X);
  double  fabs(double _X);
  double  fmod(double _X,double _Y);
  double  log(double _X);
  double  log10(double _X);
  double  pow(double _X,double _Y);
  double  sin(double _X);
  double  sinh(double _X);
  double  tan(double _X);
  double  tanh(double _X);
  double  sqrt(double _X);


  double  atof(const char *_String);
  double  _atof_l(const char *_String,_locale_t _Locale);


  extern double  _cabs(struct _complex _ComplexA);
  double  ceil(double _X);
  double  floor(double _X);
  double  frexp(double _X,int *_Y);
  double  _hypot(double _X,double _Y);
  extern double  _j0(double _X);
  extern double  _j1(double _X);
  extern double  _jn(int _X,double _Y);
  double  ldexp(double _X,int _Y);


  int  _matherr(struct _exception *_Except);

  double  modf(double _X,double *_Y);
  extern double  _y0(double _X);
  extern double  _y1(double _X);
  extern double  _yn(int _X,double _Y);







  float frexpf(float _X,int *_Y);
  float  ldexpf(float _X,int _Y);
  long double  ldexpl(long double _X,int _Y);
  float  acosf(float _X);
  float  asinf(float _X);
   float  atanf(float _X);
   float  atan2f(float _X,float _Y);
   float  cosf(float _X);
   float  sinf(float _X);
   float  tanf(float _X);
   float  coshf(float _X);
   float  sinhf(float _X);
   float  tanhf(float _X);
   float  expf(float _X);
   float  expm1f(float _X);
   float  logf(float _X);
   float  log10f(float _X);
   float  modff(float _X,float *_Y);
   float  powf(float _X,float _Y);
   float  sqrtf(float _X);
   float  ceilf(float _X);
   float  floorf(float _X);
  float  fmodf(float _X,float _Y);
   float  _hypotf(float _X,float _Y);
  float  fabsf(float _X);


   float  _copysignf (float _Number,float _Sign);
   float  _chgsignf (float _X);
   float  _logbf(float _X);
   float  _nextafterf(float _X,float _Y);
   int  _finitef(float _X);
   int  _isnanf(float _X);
   int  _fpclassf(float _X);



  extern __inline__ long double  fabsl (long double x)
  {
    long double res;
    __asm__ ("fabs;" : "=t" (res) : "0" (x));
    return res;
  }


  extern __inline__ long double _chgsignl(long double _Number) { return _chgsign((double)(_Number)); }
  extern __inline__ long double _copysignl(long double _Number,long double _Sign) { return _copysign((double)(_Number),(double)(_Sign)); }
  extern __inline__ float frexpf(float _X,int *_Y) { return ((float)frexp((double)_X,_Y)); }


  extern __inline__ float  fabsf (float x)
  {
    float res;
    __asm__ ("fabs;" : "=t" (res) : "0" (x));
    return res;
  }

  extern __inline__ float  ldexpf (float x, int expn) { return (float) ldexp (x, expn); }
# 280 "c:/program files/tcc/include/math.h"
  double  hypot(double _X,double _Y);
  extern double  j0(double _X);
  extern double  j1(double _X);
  extern double  jn(int _X,double _Y);
  extern double  y0(double _X);
  extern double  y1(double _X);
  extern double  yn(int _X,double _Y);
# 314 "c:/program files/tcc/include/math.h"
  extern int  __fpclassifyf (float);
  extern int  __fpclassify (double);
  extern int  __fpclassifyl (long double);
# 339 "c:/program files/tcc/include/math.h"
  extern int  __signbitf (float);
  extern int  __signbit (double);
  extern int  __signbitl (long double);






  extern double  exp2(double);
  extern float  exp2f(float);
  extern long double  exp2l(long double);



  extern int  ilogb (double);
  extern int  ilogbf (float);
  extern int  ilogbl (long double);

  extern double  log1p(double);
  extern float  log1pf(float);
  extern long double  log1pl(long double);

  extern double  log2 (double);
  extern float  log2f (float);
  extern long double  log2l (long double);

  extern double  logb (double);
  extern float  logbf (float);
  extern long double  logbl (long double);

  extern __inline__ double  logb (double x)
  {
    double res;
    __asm__ ("fxtract\n\t"
      "fstp	%%st" : "=t" (res) : "0" (x));
    return res;
  }

  extern __inline__ float  logbf (float x)
  {
    float res;
    __asm__ ("fxtract\n\t"
      "fstp	%%st" : "=t" (res) : "0" (x));
    return res;
  }

  extern __inline__ long double  logbl (long double x)
  {
    long double res;
    __asm__ ("fxtract\n\t"
      "fstp	%%st" : "=t" (res) : "0" (x));
    return res;
  }

  extern long double  modfl (long double, long double*);


  extern double  scalbn (double, int);
  extern float  scalbnf (float, int);
  extern long double  scalbnl (long double, int);

  extern double  scalbln (double, long);
  extern float  scalblnf (float, long);
  extern long double  scalblnl (long double, long);



  extern double  cbrt (double);
  extern float  cbrtf (float);
  extern long double  cbrtl (long double);

  extern __inline__ float  hypotf (float x, float y)
  { return (float) hypot (x, y);}
  extern long double  hypotl (long double, long double);

  extern long double  powl (long double, long double);
  extern long double  expl(long double);
  extern long double  expm1l(long double);
  extern long double  coshl(long double);
  extern long double  fabsl (long double);
  extern long double  acosl(long double);
  extern long double  asinl(long double);
  extern long double  atanl(long double);
  extern long double  atan2l(long double,long double);
  extern long double  sinhl(long double);
  extern long double  tanhl(long double);


  extern double  erf (double);
  extern float  erff (float);





  extern double  erfc (double);
  extern float  erfcf (float);





  extern double  lgamma (double);
  extern float  lgammaf (float);
  extern long double  lgammal (long double);


  extern double  tgamma (double);
  extern float  tgammaf (float);
  extern long double  tgammal (long double);

  extern long double  ceill (long double);
  extern long double  floorl (long double);
  extern long double  frexpl(long double,int *);
  extern long double  log10l(long double);
  extern long double  logl(long double);
  extern long double  cosl(long double);
  extern long double  sinl(long double);
  extern long double  tanl(long double);
  extern long double sqrtl(long double);


  extern double  nearbyint ( double);
  extern float  nearbyintf (float);
  extern long double  nearbyintl (long double);



  extern __inline__ double  rint (double x)
  {
    double retval;
    __asm__ (
      "fldl    %1\n"
      "frndint   \n"
      "fstl    %0\n" : "=m" (retval) : "m" (x));
    return retval;
  }

  extern __inline__ float  rintf (float x)
  {
    float retval;
    __asm__ (
      "flds    %1\n"
      "frndint   \n"
      "fsts    %0\n" : "=m" (retval) : "m" (x));
    return retval;
  }

  extern __inline__ long double  rintl (long double x)
  {
    long double retval;
    __asm__ (
      "fldt    %1\n"
      "frndint   \n"
      "fstt    %0\n" : "=m" (retval) : "m" (x));
    return retval;
  }


  extern __inline__ long  lrint (double x)
  {
    long retval;
    __asm__ __volatile__                               ("fldl   %1\n"                                    "fistpl %0"  : "=m" (retval) : "m" (x));        return retval;



  }

  extern __inline__ long  lrintf (float x)
  {
    long retval;
    __asm__ __volatile__                               ("flds   %1\n"                                    "fistpl %0"  : "=m" (retval) : "m" (x));        return retval;



  }

  extern __inline__ long  lrintl (long double x)
  {
    long retval;
    __asm__ __volatile__                               ("fldt   %1\n"                                    "fistpl %0"  : "=m" (retval) : "m" (x));        return retval;



  }

  extern __inline__ long long  llrint (double x)
  {
    long long retval;
    __asm__ __volatile__                               ("fldl    %1\n"                                   "fistpll %0"  : "=m" (retval) : "m" (x));       return retval;



  }

  extern __inline__ long long  llrintf (float x)
  {
    long long retval;
    __asm__ __volatile__                               ("flds   %1\n"                                    "fistpll %0"  : "=m" (retval) : "m" (x));       return retval;



  }

  extern __inline__ long long  llrintl (long double x)
  {
    long long retval;
    __asm__ __volatile__                               ("fldt    %1\n"                                   "fistpll %0"  : "=m" (retval) : "m" (x));       return retval;



  }






  extern __inline__ double trunc (double _x)
  {
    double retval;
    unsigned short saved_cw;
    unsigned short tmp_cw;
    __asm__ ("fnstcw %0;" : "=m" (saved_cw));
    tmp_cw = (saved_cw & ~(0x0000 | 0x0400 | 0x0800 | 0x0c00))
	    | 0x0c00;
    __asm__ ("fldcw %0;" : : "m" (tmp_cw));
    __asm__ ("fldl  %1;"
             "frndint;"
             "fstl  %0;" : "=m" (retval)  : "m" (_x));
    __asm__ ("fldcw %0;" : : "m" (saved_cw) );
    return retval;
  }



  extern double  round (double);
  extern float  roundf (float);
  extern long double  roundl (long double);


  extern long  lround (double);
  extern long  lroundf (float);
  extern long  lroundl (long double);

  extern long long  llround (double);
  extern long long  llroundf (float);
  extern long long  llroundl (long double);



  extern double  trunc (double);
  extern float  truncf (float);
  extern long double  truncl (long double);

  extern long double  fmodl (long double, long double);


  extern double  remainder (double, double);
  extern float  remainderf (float, float);
  extern long double  remainderl (long double, long double);


  extern double  remquo(double, double, int *);
  extern float  remquof(float, float, int *);
  extern long double  remquol(long double, long double, int *);


  extern double  copysign (double, double);
  extern float  copysignf (float, float);
  extern long double  copysignl (long double, long double);


  extern double  nan(const char *tagp);
  extern float  nanf(const char *tagp);
  extern long double  nanl(const char *tagp);
# 624 "c:/program files/tcc/include/math.h"
  extern double  nextafter (double, double);
  extern float  nextafterf (float, float);
  extern long double  nextafterl (long double, long double);





  extern double  fdim (double x, double y);
  extern float  fdimf (float x, float y);
  extern long double  fdiml (long double x, long double y);







  extern double  fmax  (double, double);
  extern float  fmaxf (float, float);
  extern long double  fmaxl (long double, long double);


  extern double  fmin (double, double);
  extern float  fminf (float, float);
  extern long double  fminl (long double, long double);



  extern double  fma (double, double, double);
  extern float  fmaf (float, float, float);
  extern long double  fmal (long double, long double, long double);
# 722 "c:/program files/tcc/include/math.h"
#pragma pack(pop)
# 734 "c:/program files/tcc/include/math.h"
# 1 "c:/program files/tcc/include/tcc/tcc_libm.h" 1



# 1 "c:/program files/tcc/include/tcc/../math.h" 1
# 5 "c:/program files/tcc/include/tcc/tcc_libm.h" 2
# 48 "c:/program files/tcc/include/tcc/tcc_libm.h"
extern __inline__ int  __fpclassify (double x) {
  union {double f; uint64_t i;} u = {x};
  int e = u.i>>52 & 0x7ff;
  if (!e) return u.i<<1 ? (0x0400 | 0x4000) : 0x4000;
  if (e==0x7ff) return u.i<<12 ? 0x0100 : (0x0100 | 0x0400);
  return 0x0400;
}

extern __inline__ int  __fpclassifyf (float x) {
  union {float f; uint32_t i;} u = {x};
  int e = u.i>>23 & 0xff;
  if (!e) return u.i<<1 ? (0x0400 | 0x4000) : 0x4000;
  if (e==0xff) return u.i<<9 ? 0x0100 : (0x0100 | 0x0400);
  return 0x0400;
}

extern __inline__ int  __fpclassifyl (long double x) {
  return __fpclassify(x);
}




extern __inline__ int  __signbit (double x) {
  union {double d; uint64_t i;} y = { x };
  return y.i>>63;
}

extern __inline__ int  __signbitf (float x) {
  union {float f; uint32_t i; } y = { x };
  return y.i>>31;
}

extern __inline__ int  __signbitl (long double x) {
  return __signbit(x);
}
# 93 "c:/program files/tcc/include/tcc/tcc_libm.h"
extern __inline__ double  fmin (double x, double y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? x : y) : x < y ? x : y);
}

extern __inline__ float  fminf (float x, float y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? x : y) : x < y ? x : y);
}

extern __inline__ long double  fminl (long double x, long double y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? x : y) : x < y ? x : y);
}






extern __inline__ double  fmax (double x, double y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? y : x) : x < y ? y : x);
}

extern __inline__ float  fmaxf (float x, float y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? y : x) : x < y ? y : x);
}

extern __inline__ long double  fmaxl (long double x, long double y) {
  return (((sizeof (x) == sizeof (float) ? __fpclassifyf (x)	: sizeof (x) == sizeof (double) ? __fpclassify (x) : __fpclassifyl (x)) == 0x0100) ? y : ((sizeof (y) == sizeof (float) ? __fpclassifyf (y)	: sizeof (y) == sizeof (double) ? __fpclassify (y) : __fpclassifyl (y)) == 0x0100) ? x : ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) != (sizeof (y) == sizeof (float) ? __signbitf (y)	: sizeof (y) == sizeof (double) ? __signbit (y)	: __signbitl (y))) ? ((sizeof (x) == sizeof (float) ? __signbitf (x)	: sizeof (x) == sizeof (double) ? __signbit (x)	: __signbitl (x)) ? y : x) : x < y ? y : x);
}
# 138 "c:/program files/tcc/include/tcc/tcc_libm.h"
extern __inline__ double  round (double x) {
  union {double f; uint64_t i;} u = {x};
  int e = u.i >> 52 & 0x7ff;
  double y;

  if (e >= 0x3ff+52)
    return x;
  if (u.i >> 63)
    x = -x;
  if (e < 0x3ff-1) {

    do { if (sizeof(x + 0x1p52) == sizeof(float)) { volatile float __x; __x = (x + 0x1p52); } else if (sizeof(x + 0x1p52) == sizeof(double)) { volatile double __x; __x = (x + 0x1p52); } else { volatile long double __x; __x = (x + 0x1p52); } } while(0);
    return 0*u.f;
  }
  y = (double)(x + 0x1p52) - 0x1p52 - x;
  if (y > 0.5)
    y = y + x - 1;
  else if (y <= -0.5)
    y = y + x + 1;
  else
    y = y + x;
  if (u.i >> 63)
    y = -y;
  return y;
}

extern __inline__ long  lround (double x) {
  return round(x);
}

extern __inline__ long long  llround (double x) {
  return round(x);
}

extern __inline__ float  roundf (float x) {
  return round(x);
}

extern __inline__ long  lroundf (float x) {
  return round(x);
}

extern __inline__ long long  llroundf (float x) {
  return round(x);
}

extern __inline__ long double  roundl (long double x) {
  return round(x);
}

extern __inline__ long  lroundl (long double x) {
  return round(x);
}

extern __inline__ long long  llroundl (long double x) {
  return round(x);
}
# 735 "c:/program files/tcc/include/math.h" 2
# 2 "SGL.c" 2
# 1 "c:/program files/tcc/include/stdio.h" 1
# 11 "c:/program files/tcc/include/stdio.h"
#pragma pack(push,8)
# 24 "c:/program files/tcc/include/stdio.h"
  struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
  };
  typedef struct _iobuf FILE;
# 78 "c:/program files/tcc/include/stdio.h"
  typedef long _off_t;

  typedef long off_t;






  typedef long long _off64_t;

  typedef long long off64_t;





  extern FILE * __iob_func(void);
# 113 "c:/program files/tcc/include/stdio.h"
  typedef long long fpos_t;
# 150 "c:/program files/tcc/include/stdio.h"
  extern int  _filbuf(FILE *_File);
  extern int  _flsbuf(int _Ch,FILE *_File);



  extern FILE * _fsopen(const char *_Filename,const char *_Mode,int _ShFlag);

  void  clearerr(FILE *_File);
  int  fclose(FILE *_File);
  extern int  _fcloseall(void);



  extern FILE * _fdopen(int _FileHandle,const char *_Mode);

  int  feof(FILE *_File);
  int  ferror(FILE *_File);
  int  fflush(FILE *_File);
  int  fgetc(FILE *_File);
  extern int  _fgetchar(void);
  int  fgetpos(FILE *_File ,fpos_t *_Pos);
  char * fgets(char *_Buf,int _MaxCount,FILE *_File);



  extern int  _fileno(FILE *_File);

  extern char * _tempnam(const char *_DirName,const char *_FilePrefix);
  extern int  _flushall(void);
  FILE * fopen(const char *_Filename,const char *_Mode);
  FILE *fopen64(const char *filename,const char *mode);
  int  fprintf(FILE *_File,const char *_Format,...);
  int  fputc(int _Ch,FILE *_File);
  extern int  _fputchar(int _Ch);
  int  fputs(const char *_Str,FILE *_File);
  size_t  fread(void *_DstBuf,size_t _ElementSize,size_t _Count,FILE *_File);
  FILE * freopen(const char *_Filename,const char *_Mode,FILE *_File);
  int  fscanf(FILE *_File,const char *_Format,...);
  int  fsetpos(FILE *_File,const fpos_t *_Pos);
  int  fseek(FILE *_File,long _Offset,int _Origin);
   int fseeko64(FILE* stream, _off64_t offset, int whence);
  long  ftell(FILE *_File);
  _off64_t ftello64(FILE * stream);
  int  _fseeki64(FILE *_File,long long _Offset,int _Origin);
  long long  _ftelli64(FILE *_File);
  size_t  fwrite(const void *_Str,size_t _Size,size_t _Count,FILE *_File);
  int  getc(FILE *_File);
  int  getchar(void);
  extern int  _getmaxstdio(void);
  char * gets(char *_Buffer);
  int  _getw(FILE *_File);


  void  perror(const char *_ErrMsg);

  extern int  _pclose(FILE *_File);
  extern FILE * _popen(const char *_Command,const char *_Mode);




  int  printf(const char *_Format,...);
  int  putc(int _Ch,FILE *_File);
  int  putchar(int _Ch);
  int  puts(const char *_Str);
  extern int  _putw(int _Word,FILE *_File);


  int  remove(const char *_Filename);
  int  rename(const char *_OldFilename,const char *_NewFilename);
  extern int  _unlink(const char *_Filename);

  int  unlink(const char *_Filename);


  void  rewind(FILE *_File);
  extern int  _rmtmp(void);
  int  scanf(const char *_Format,...);
  void  setbuf(FILE *_File,char *_Buffer);
  extern int  _setmaxstdio(int _Max);
  extern unsigned int  _set_output_format(unsigned int _Format);
  extern unsigned int  _get_output_format(void);
  int  setvbuf(FILE *_File,char *_Buf,int _Mode,size_t _Size);
  extern int  _scprintf(const char *_Format,...);
  int  sscanf(const char *_Src,const char *_Format,...);
  extern int  _snscanf(const char *_Src,size_t _MaxCount,const char *_Format,...);
  FILE * tmpfile(void);
  char * tmpnam(char *_Buffer);
  int  ungetc(int _Ch,FILE *_File);
  int  vfprintf(FILE *_File,const char *_Format,va_list _ArgList);
  int  vprintf(const char *_Format,va_list _ArgList);





  extern
  __attribute__((format(gnu_printf, 3, 0))) __attribute__((nonnull (3)))
  int __mingw_vsnprintf(char *_DstBuf,size_t _MaxCount,const char *_Format,va_list _ArgList);
  extern
  __attribute__((format(gnu_printf, 3, 4))) __attribute__((nonnull (3)))
  int __mingw_snprintf(char* s, size_t n, const char*  format, ...);
  int  vsnprintf(char *_DstBuf,size_t _MaxCount,const char *_Format,va_list _ArgList);
  extern int  _snprintf(char *_Dest,size_t _Count,const char *_Format,...);
  extern int  _vsnprintf(char *_Dest,size_t _Count,const char *_Format,va_list _Args);
  int  sprintf(char *_Dest,const char *_Format,...);
  int  vsprintf(char *_Dest,const char *_Format,va_list _Args);

  int  snprintf(char* s, size_t n, const char*  format, ...);
  extern __inline__ int  vsnprintf (char* s, size_t n, const char* format,va_list arg) {
    return _vsnprintf ( s, n, format, arg);
  }
  int  vscanf(const char * Format, va_list argp);
  int  vfscanf (FILE * fp, const char * Format,va_list argp);
  int  vsscanf (const char * _Str,const char * Format,va_list argp);
# 278 "c:/program files/tcc/include/stdio.h"
  extern int  _vscprintf(const char *_Format,va_list _ArgList);
  extern int  _set_printf_count_output(int _Value);
  extern int  _get_printf_count_output(void);
# 291 "c:/program files/tcc/include/stdio.h"
  extern FILE * _wfsopen(const wchar_t *_Filename,const wchar_t *_Mode,int _ShFlag);

  wint_t  fgetwc(FILE *_File);
  extern wint_t  _fgetwchar(void);
  wint_t  fputwc(wchar_t _Ch,FILE *_File);
  extern wint_t  _fputwchar(wchar_t _Ch);
  wint_t  getwc(FILE *_File);
  wint_t  getwchar(void);
  wint_t  putwc(wchar_t _Ch,FILE *_File);
  wint_t  putwchar(wchar_t _Ch);
  wint_t  ungetwc(wint_t _Ch,FILE *_File);
  wchar_t * fgetws(wchar_t *_Dst,int _SizeInWords,FILE *_File);
  int  fputws(const wchar_t *_Str,FILE *_File);
  extern wchar_t * _getws(wchar_t *_String);
  extern int  _putws(const wchar_t *_Str);
  int  fwprintf(FILE *_File,const wchar_t *_Format,...);
  int  wprintf(const wchar_t *_Format,...);
  extern int  _scwprintf(const wchar_t *_Format,...);
  int  vfwprintf(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  int  vwprintf(const wchar_t *_Format,va_list _ArgList);
  extern int  swprintf(wchar_t*, const wchar_t*, ...);
  extern int  vswprintf(wchar_t*, const wchar_t*,va_list);
  extern int  _swprintf_c(wchar_t *_DstBuf,size_t _SizeInWords,const wchar_t *_Format,...);
  extern int  _vswprintf_c(wchar_t *_DstBuf,size_t _SizeInWords,const wchar_t *_Format,va_list _ArgList);
  extern int  _snwprintf(wchar_t *_Dest,size_t _Count,const wchar_t *_Format,...);
  extern int  _vsnwprintf(wchar_t *_Dest,size_t _Count,const wchar_t *_Format,va_list _Args);

  int  snwprintf (wchar_t* s, size_t n, const wchar_t*  format, ...);
  extern __inline__ int  vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, va_list arg) { return _vsnwprintf(s,n,format,arg); }
  int  vwscanf (const wchar_t *, va_list);
  int  vfwscanf (FILE *,const wchar_t *,va_list);
  int  vswscanf (const wchar_t *,const wchar_t *,va_list);

  extern int  _swprintf(wchar_t *_Dest,const wchar_t *_Format,...);
  extern int  _vswprintf(wchar_t *_Dest,const wchar_t *_Format,va_list _Args);


# 1 "c:/program files/tcc/include/vadefs.h" 1
# 329 "c:/program files/tcc/include/stdio.h" 2
# 340 "c:/program files/tcc/include/stdio.h"
  extern wchar_t * _wtempnam(const wchar_t *_Directory,const wchar_t *_FilePrefix);
  extern int  _vscwprintf(const wchar_t *_Format,va_list _ArgList);
  int  fwscanf(FILE *_File,const wchar_t *_Format,...);
  int  swscanf(const wchar_t *_Src,const wchar_t *_Format,...);
  extern int  _snwscanf(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,...);
  int  wscanf(const wchar_t *_Format,...);
  extern FILE * _wfdopen(int _FileHandle ,const wchar_t *_Mode);
  extern FILE * _wfopen(const wchar_t *_Filename,const wchar_t *_Mode);
  extern FILE * _wfreopen(const wchar_t *_Filename,const wchar_t *_Mode,FILE *_OldFile);


  extern void  _wperror(const wchar_t *_ErrMsg);

  extern FILE * _wpopen(const wchar_t *_Command,const wchar_t *_Mode);



  extern int  _wremove(const wchar_t *_Filename);
  extern wchar_t * _wtmpnam(wchar_t *_Buffer);
  extern wint_t  _fgetwc_nolock(FILE *_File);
  extern wint_t  _fputwc_nolock(wchar_t _Ch,FILE *_File);
  extern wint_t  _ungetwc_nolock(wint_t _Ch,FILE *_File);
# 393 "c:/program files/tcc/include/stdio.h"
  extern void  _lock_file(FILE *_File);
  extern void  _unlock_file(FILE *_File);
  extern int  _fclose_nolock(FILE *_File);
  extern int  _fflush_nolock(FILE *_File);
  extern size_t  _fread_nolock(void *_DstBuf,size_t _ElementSize,size_t _Count,FILE *_File);
  extern int  _fseek_nolock(FILE *_File,long _Offset,int _Origin);
  extern long  _ftell_nolock(FILE *_File);
  extern int  _fseeki64_nolock(FILE *_File,long long _Offset,int _Origin);
  extern long long  _ftelli64_nolock(FILE *_File);
  extern size_t  _fwrite_nolock(const void *_DstBuf,size_t _Size,size_t _Count,FILE *_File);
  extern int  _ungetc_nolock(int _Ch,FILE *_File);





  char * tempnam(const char *_Directory,const char *_FilePrefix);
  int  fcloseall(void);
  FILE * fdopen(int _FileHandle,const char *_Format);
  int  fgetchar(void);
  int  fileno(FILE *_File);
  int  flushall(void);
  int  fputchar(int _Ch);
  int  getw(FILE *_File);
  int  putw(int _Ch,FILE *_File);
  int  rmtmp(void);






#pragma pack(pop)

# 1 "c:/program files/tcc/include/sec_api/stdio_s.h" 1
# 9 "c:/program files/tcc/include/sec_api/stdio_s.h"
# 1 "c:/program files/tcc/include/stdio.h" 1
# 10 "c:/program files/tcc/include/sec_api/stdio_s.h" 2
# 19 "c:/program files/tcc/include/sec_api/stdio_s.h"
  extern errno_t  clearerr_s(FILE *_File);
  int  fprintf_s(FILE *_File,const char *_Format,...);
  size_t  fread_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
  extern int  _fscanf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  int  printf_s(const char *_Format,...);
  extern int  _scanf_l(const char *_Format,_locale_t _Locale,...);
  extern int  _scanf_s_l(const char *_Format,_locale_t _Locale,...);
  extern int  _snprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,...);
  extern int  _snprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,...);
  extern int  _vsnprintf_c(char *_DstBuf,size_t _MaxCount,const char *_Format,va_list _ArgList);
  int  sprintf_s(char *_DstBuf,size_t _DstSize,const char *_Format,...);
  extern int  _fscanf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  extern int  _sscanf_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  extern int  _sscanf_s_l(const char *_Src,const char *_Format,_locale_t _Locale,...);
  extern int  _snscanf_s(const char *_Src,size_t _MaxCount,const char *_Format,...);
  extern int  _snscanf_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  extern int  _snscanf_s_l(const char *_Src,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  int  vfprintf_s(FILE *_File,const char *_Format,va_list _ArgList);
  int  vprintf_s(const char *_Format,va_list _ArgList);
  int  vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);
  extern int  _vsnprintf_s(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,va_list _ArgList);
  int  vsprintf_s(char *_DstBuf,size_t _Size,const char *_Format,va_list _ArgList);
  extern int  _fprintf_p(FILE *_File,const char *_Format,...);
  extern int  _printf_p(const char *_Format,...);
  extern int  _sprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,...);
  extern int  _vfprintf_p(FILE *_File,const char *_Format,va_list _ArgList);
  extern int  _vprintf_p(const char *_Format,va_list _ArgList);
  extern int  _vsprintf_p(char *_Dst,size_t _MaxCount,const char *_Format,va_list _ArgList);
  extern int  _scprintf_p(const char *_Format,...);
  extern int  _vscprintf_p(const char *_Format,va_list _ArgList);
  extern int  _printf_l(const char *_Format,_locale_t _Locale,...);
  extern int  _printf_p_l(const char *_Format,_locale_t _Locale,...);
  extern int  _vprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  extern int  _fprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  extern int  _vfprintf_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vfprintf_p_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _sprintf_l(char *_DstBuf,const char *_Format,_locale_t _Locale,...);
  extern int  _sprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  extern int  _vsprintf_l(char *_DstBuf,const char *_Format,_locale_t,va_list _ArgList);
  extern int  _vsprintf_p_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _scprintf_l(const char *_Format,_locale_t _Locale,...);
  extern int  _scprintf_p_l(const char *_Format,_locale_t _Locale,...);
  extern int  _vscprintf_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vscprintf_p_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _printf_s_l(const char *_Format,_locale_t _Locale,...);
  extern int  _vprintf_s_l(const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,...);
  extern int  _vfprintf_s_l(FILE *_File,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _sprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,...);
  extern int  _vsprintf_s_l(char *_DstBuf,size_t _DstSize,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _snprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  extern int  _vsnprintf_s_l(char *_DstBuf,size_t _DstSize,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _snprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  extern int  _snprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,...);
  extern int  _vsnprintf_l(char *_DstBuf,size_t _MaxCount,const char *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vsnprintf_c_l(char *_DstBuf,size_t _MaxCount,const char *,_locale_t _Locale,va_list _ArgList);



  extern wchar_t * _getws_s(wchar_t *_Str,size_t _SizeInWords);
  int  fwprintf_s(FILE *_File,const wchar_t *_Format,...);
  int  wprintf_s(const wchar_t *_Format,...);
  int  vwprintf_s(const wchar_t *_Format,va_list _ArgList);
  int  swprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,...);
  int  vswprintf_s(wchar_t *_Dst,size_t _SizeInWords,const wchar_t *_Format,va_list _ArgList);
  extern int  _snwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,...);
  extern int  _vsnwprintf_s(wchar_t *_DstBuf,size_t _DstSizeInWords,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);
  extern int  _wprintf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vwprintf_s_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vfwprintf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _swprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vswprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _snwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vsnwprintf_s_l(wchar_t *_DstBuf,size_t _DstSize,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fwscanf_s_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _swscanf_s_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _snwscanf_s(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,...);
  extern int  _snwscanf_s_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _wscanf_s_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern errno_t  _wfopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode);
  extern errno_t  _wfreopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode,FILE *_OldFile);
  extern errno_t  _wtmpnam_s(wchar_t *_DstBuf,size_t _SizeInWords);
  extern int  _fwprintf_p(FILE *_File,const wchar_t *_Format,...);
  extern int  _wprintf_p(const wchar_t *_Format,...);
  extern int  _vfwprintf_p(FILE *_File,const wchar_t *_Format,va_list _ArgList);
  extern int  _vwprintf_p(const wchar_t *_Format,va_list _ArgList);
  extern int  _swprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,...);
  extern int  _vswprintf_p(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,va_list _ArgList);
  extern int  _scwprintf_p(const wchar_t *_Format,...);
  extern int  _vscwprintf_p(const wchar_t *_Format,va_list _ArgList);
  extern int  _wprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _wprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _fwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vfwprintf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vfwprintf_p_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _swprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _swprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vswprintf_c_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _vswprintf_p_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _scwprintf_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _scwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vscwprintf_p_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _snwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _vsnwprintf_l(wchar_t *_DstBuf,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  __swprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,...);
  extern int  __vswprintf_l(wchar_t *_Dest,const wchar_t *_Format,_locale_t _Plocinfo,va_list _Args);
  extern int  _vscwprintf_l(const wchar_t *_Format,_locale_t _Locale,va_list _ArgList);
  extern int  _fwscanf_l(FILE *_File,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _swscanf_l(const wchar_t *_Src,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _snwscanf_l(const wchar_t *_Src,size_t _MaxCount,const wchar_t *_Format,_locale_t _Locale,...);
  extern int  _wscanf_l(const wchar_t *_Format,_locale_t _Locale,...);



  extern size_t  _fread_nolock_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
# 428 "c:/program files/tcc/include/stdio.h" 2
# 3 "SGL.c" 2
# 1 "c:/program files/tcc/include/stdlib.h" 1
# 10 "c:/program files/tcc/include/stdlib.h"
# 1 "c:/program files/tcc/include/limits.h" 1
# 11 "c:/program files/tcc/include/stdlib.h" 2

#pragma pack(push,8)
# 32 "c:/program files/tcc/include/stdlib.h"
  typedef int ( *_onexit_t)(void);
# 42 "c:/program files/tcc/include/stdlib.h"
  typedef struct _div_t {
    int quot;
    int rem;
  } div_t;

  typedef struct _ldiv_t {
    long quot;
    long rem;
  } ldiv_t;





#pragma pack(4)
  typedef struct {
    unsigned char ld[10];
  } _LDOUBLE;
#pragma pack()



  typedef struct {
    double x;
  } _CRT_DOUBLE;

  typedef struct {
    float f;
  } _CRT_FLOAT;




  typedef struct {
    long double x;
  } _LONGDOUBLE;



#pragma pack(4)
  typedef struct {
    unsigned char ld12[12];
  } _LDBL12;
#pragma pack()
# 97 "c:/program files/tcc/include/stdlib.h"
  extern int *_imp____mb_cur_max;






  extern int* _imp____mbcur_max;
# 128 "c:/program files/tcc/include/stdlib.h"
  typedef void ( *_purecall_handler)(void);

  extern _purecall_handler  _set_purecall_handler(_purecall_handler _Handler);
  extern _purecall_handler  _get_purecall_handler(void);

  typedef void ( *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
  _invalid_parameter_handler  _set_invalid_parameter_handler(_invalid_parameter_handler _Handler);
  _invalid_parameter_handler  _get_invalid_parameter_handler(void);



  extern extern int * _errno(void);

  errno_t  _set_errno(int _Value);
  errno_t  _get_errno(int *_Value);

  extern unsigned long * __doserrno(void);

  errno_t  _set_doserrno(unsigned long _Value);
  errno_t  _get_doserrno(unsigned long *_Value);




  extern char *_sys_errlist[1];
  extern int _sys_nerr;
# 169 "c:/program files/tcc/include/stdlib.h"
  extern int *_imp____argc;







  extern char ***_imp____argv;







  extern wchar_t ***_imp____wargv;
# 197 "c:/program files/tcc/include/stdlib.h"
  extern char ***_imp___environ;
# 206 "c:/program files/tcc/include/stdlib.h"
  extern wchar_t ***_imp___wenviron;
# 215 "c:/program files/tcc/include/stdlib.h"
  extern char **_imp___pgmptr;
# 224 "c:/program files/tcc/include/stdlib.h"
  extern wchar_t **_imp___wpgmptr;


  errno_t  _get_pgmptr(char **_Value);
  errno_t  _get_wpgmptr(wchar_t **_Value);





  extern int *_imp___fmode;


  extern errno_t  _set_fmode(int _Mode);
  extern errno_t  _get_fmode(int *_PMode);






  extern unsigned int *_imp___osplatform;
# 254 "c:/program files/tcc/include/stdlib.h"
  extern unsigned int *_imp___osver;
# 263 "c:/program files/tcc/include/stdlib.h"
  extern unsigned int *_imp___winver;
# 272 "c:/program files/tcc/include/stdlib.h"
  extern unsigned int *_imp___winmajor;
# 281 "c:/program files/tcc/include/stdlib.h"
  extern unsigned int *_imp___winminor;



  errno_t  _get_osplatform(unsigned int *_Value);
  errno_t  _get_osver(unsigned int *_Value);
  errno_t  _get_winver(unsigned int *_Value);
  errno_t  _get_winmajor(unsigned int *_Value);
  errno_t  _get_winminor(unsigned int *_Value);
# 303 "c:/program files/tcc/include/stdlib.h"
  void   exit(int _Code) ;
  extern void   _exit(int _Code) ;


  void  _Exit(int) ;
  extern __inline__  void   _Exit(int status)
  {  _exit(status); }




  void  __attribute__((noreturn)) abort(void);




  extern unsigned int  _set_abort_behavior(unsigned int _Flags,unsigned int _Mask);
# 328 "c:/program files/tcc/include/stdlib.h"
  long long  _abs64(long long);

  int  atexit(void ( *)(void));





  int  atoi(const char *_Str);
  extern int  _atoi_l(const char *_Str,_locale_t _Locale);
  long  atol(const char *_Str);
  extern long  _atol_l(const char *_Str,_locale_t _Locale);


  void * bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int ( *_PtFuncCompare)(const void *,const void *));
  void  qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int ( *_PtFuncCompare)(const void *,const void *));

  unsigned short  _byteswap_ushort(unsigned short _Short);


  unsigned long long  _byteswap_uint64(unsigned long long _Int64);

  div_t  div(int _Numerator,int _Denominator);
  char * getenv(const char *_VarName);
  extern char * _itoa(int _Value,char *_Dest,int _Radix);

  extern char * _i64toa(long long _Val,char *_DstBuf,int _Radix);
  extern char * _ui64toa(unsigned long long _Val,char *_DstBuf,int _Radix);
  extern long long  _atoi64(const char *_String);
  extern long long  _atoi64_l(const char *_String,_locale_t _Locale);
  extern long long  _strtoi64(const char *_String,char **_EndPtr,int _Radix);
  extern long long  _strtoi64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  extern unsigned long long  _strtoui64(const char *_String,char **_EndPtr,int _Radix);
  extern unsigned long long  _strtoui64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);

  ldiv_t  ldiv(long _Numerator,long _Denominator);
  extern char * _ltoa(long _Value,char *_Dest,int _Radix);
  int  mblen(const char *_Ch,size_t _MaxCount);
  extern int  _mblen_l(const char *_Ch,size_t _MaxCount,_locale_t _Locale);
  extern size_t  _mbstrlen(const char *_Str);
  extern size_t  _mbstrlen_l(const char *_Str,_locale_t _Locale);
  extern size_t  _mbstrnlen(const char *_Str,size_t _MaxCount);
  extern size_t  _mbstrnlen_l(const char *_Str,size_t _MaxCount,_locale_t _Locale);
  int  mbtowc(wchar_t *_DstCh,const char *_SrcCh,size_t _SrcSizeInBytes);
  extern int  _mbtowc_l(wchar_t *_DstCh,const char *_SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale);
  size_t  mbstowcs(wchar_t *_Dest,const char *_Source,size_t _MaxCount);
  extern size_t  _mbstowcs_l(wchar_t *_Dest,const char *_Source,size_t _MaxCount,_locale_t _Locale);
  int  rand(void);
  extern int  _set_error_mode(int _Mode);
  void  srand(unsigned int _Seed);
  double  strtod(const char *_Str,char **_EndPtr);
  float  strtof(const char *nptr, char **endptr);

  float  strtof (const char * __restrict__, char ** __restrict__);
  long double  strtold(const char * __restrict__, char ** __restrict__);

  extern double  _strtod_l(const char *_Str,char **_EndPtr,_locale_t _Locale);
  long  strtol(const char *_Str,char **_EndPtr,int _Radix);
  extern long  _strtol_l(const char *_Str,char **_EndPtr,int _Radix,_locale_t _Locale);
  unsigned long  strtoul(const char *_Str,char **_EndPtr,int _Radix);
  extern unsigned long  _strtoul_l(const char *_Str,char **_EndPtr,int _Radix,_locale_t _Locale);


  int  system(const char *_Command);

  extern char * _ultoa(unsigned long _Value,char *_Dest,int _Radix);
  int  wctomb(char *_MbCh,wchar_t _WCh);
  extern int  _wctomb_l(char *_MbCh,wchar_t _WCh,_locale_t _Locale);
  size_t  wcstombs(char *_Dest,const wchar_t *_Source,size_t _MaxCount);
  extern size_t  _wcstombs_l(char *_Dest,const wchar_t *_Source,size_t _MaxCount,_locale_t _Locale);



  void * calloc(size_t _NumOfElements,size_t _SizeOfElements);
  void  free(void *_Memory);
  void * malloc(size_t _Size);
  void * realloc(void *_Memory,size_t _NewSize);
  extern void * _recalloc(void *_Memory,size_t _Count,size_t _Size);


  extern void * _aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset);
  extern void * _aligned_realloc(void *_Memory,size_t _Size,size_t _Alignment);
  extern void * _aligned_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment);
  extern void * _aligned_offset_realloc(void *_Memory,size_t _Size,size_t _Alignment,size_t _Offset);
  extern void * _aligned_offset_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment,size_t _Offset);





  extern wchar_t * _itow(int _Value,wchar_t *_Dest,int _Radix);
  extern wchar_t * _ltow(long _Value,wchar_t *_Dest,int _Radix);
  extern wchar_t * _ultow(unsigned long _Value,wchar_t *_Dest,int _Radix);
  double  wcstod(const wchar_t *_Str,wchar_t **_EndPtr);
  float  wcstof(const wchar_t *nptr, wchar_t **endptr);

  float  wcstof( const wchar_t * __restrict__, wchar_t ** __restrict__);
  long double  wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);

  extern double  _wcstod_l(const wchar_t *_Str,wchar_t **_EndPtr,_locale_t _Locale);
  long  wcstol(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  extern long  _wcstol_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  unsigned long  wcstoul(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  extern unsigned long  _wcstoul_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  extern wchar_t * _wgetenv(const wchar_t *_VarName);


  extern int  _wsystem(const wchar_t *_Command);

  extern double  _wtof(const wchar_t *_Str);
  extern double  _wtof_l(const wchar_t *_Str,_locale_t _Locale);
  extern int  _wtoi(const wchar_t *_Str);
  extern int  _wtoi_l(const wchar_t *_Str,_locale_t _Locale);
  extern long  _wtol(const wchar_t *_Str);
  extern long  _wtol_l(const wchar_t *_Str,_locale_t _Locale);


  extern wchar_t * _i64tow(long long _Val,wchar_t *_DstBuf,int _Radix);
  extern wchar_t * _ui64tow(unsigned long long _Val,wchar_t *_DstBuf,int _Radix);
  extern long long  _wtoi64(const wchar_t *_Str);
  extern long long  _wtoi64_l(const wchar_t *_Str,_locale_t _Locale);
  extern long long  _wcstoi64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  extern long long  _wcstoi64_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  extern unsigned long long  _wcstoui64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  extern unsigned long long  _wcstoui64_l(const wchar_t *_Str ,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);





  extern char * _fullpath(char *_FullPath,const char *_Path,size_t _SizeInBytes);
  extern char * _ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign);
  extern char * _fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  extern char * _gcvt(double _Val,int _NumOfDigits,char *_DstBuf);
  extern int  _atodbl(_CRT_DOUBLE *_Result,char *_Str);
  extern int  _atoldbl(_LDOUBLE *_Result,char *_Str);
  extern int  _atoflt(_CRT_FLOAT *_Result,char *_Str);
  extern int  _atodbl_l(_CRT_DOUBLE *_Result,char *_Str,_locale_t _Locale);
  extern int  _atoldbl_l(_LDOUBLE *_Result,char *_Str,_locale_t _Locale);
  extern int  _atoflt_l(_CRT_FLOAT *_Result,char *_Str,_locale_t _Locale);
  unsigned long  _lrotl(unsigned long _Val,int _Shift);
  unsigned long  _lrotr(unsigned long _Val,int _Shift);
  extern void  _makepath(char *_Path,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  _onexit_t  _onexit(_onexit_t _Func);





  extern int  _putenv(const char *_EnvString);
  unsigned int  _rotl(unsigned int _Val,int _Shift);

  unsigned long long  _rotl64(unsigned long long _Val,int _Shift);

  unsigned int  _rotr(unsigned int _Val,int _Shift);

  unsigned long long  _rotr64(unsigned long long _Val,int _Shift);

  extern void  _searchenv(const char *_Filename,const char *_EnvVar,char *_ResultPath);
  extern void  _splitpath(const char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext);
  extern void  _swab(char *_Buf1,char *_Buf2,int _SizeInBytes);



  extern wchar_t * _wfullpath(wchar_t *_FullPath,const wchar_t *_Path,size_t _SizeInWords);
  extern void  _wmakepath(wchar_t *_ResultPath,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);




  extern int  _wputenv(const wchar_t *_EnvString);
  extern void  _wsearchenv(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath);
  extern void  _wsplitpath(const wchar_t *_FullPath,wchar_t *_Drive,wchar_t *_Dir,wchar_t *_Filename,wchar_t *_Ext);


  extern void  _beep(unsigned _Frequency,unsigned _Duration) ;

  extern void  _seterrormode(int _Mode) ;
  extern void  _sleep(unsigned long _Duration) ;
# 527 "c:/program files/tcc/include/stdlib.h"
  char * ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign);
  char * fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  char * gcvt(double _Val,int _NumOfDigits,char *_DstBuf);
  char * itoa(int _Val,char *_DstBuf,int _Radix);
  char * ltoa(long _Val,char *_DstBuf,int _Radix);
  int  putenv(const char *_EnvString);
  void  swab(char *_Buf1,char *_Buf2,int _SizeInBytes);
  char * ultoa(unsigned long _Val,char *_Dstbuf,int _Radix);
  _onexit_t  onexit(_onexit_t _Func);





  typedef struct { long long quot, rem; } lldiv_t;

  lldiv_t  lldiv(long long, long long);

  extern __inline__ long long  llabs(long long _j) { return (_j >= 0 ? _j : -_j); }

  long long   strtoll(const char* __restrict__, char** __restrict, int);
  unsigned long long   strtoull(const char* __restrict__, char** __restrict__, int);


  long long   atoll (const char *);


  long long   wtoll (const wchar_t *);
  char * lltoa (long long, char *, int);
  char * ulltoa (unsigned long long , char *, int);
  wchar_t * lltow (long long, wchar_t *, int);
  wchar_t * ulltow (unsigned long long, wchar_t *, int);


  extern __inline__ long long   atoll (const char * _c) { return _atoi64 (_c); }
  extern __inline__ char * lltoa (long long _n, char * _c, int _i) { return _i64toa (_n, _c, _i); }
  extern __inline__ char * ulltoa (unsigned long long _n, char * _c, int _i) { return _ui64toa (_n, _c, _i); }
  extern __inline__ long long   wtoll (const wchar_t * _w) { return _wtoi64 (_w); }
  extern __inline__ wchar_t * lltow (long long _n, wchar_t * _w, int _i) { return _i64tow (_n, _w, _i); }
  extern __inline__ wchar_t * ulltow (unsigned long long _n, wchar_t * _w, int _i) { return _ui64tow (_n, _w, _i); }
# 575 "c:/program files/tcc/include/stdlib.h"
#pragma pack(pop)

# 1 "c:/program files/tcc/include/sec_api/stdlib_s.h" 1
# 9 "c:/program files/tcc/include/sec_api/stdlib_s.h"
# 1 "c:/program files/tcc/include/stdlib.h" 1
# 10 "c:/program files/tcc/include/sec_api/stdlib_s.h" 2







  extern errno_t  _dupenv_s(char **_PBuffer,size_t *_PBufferSizeInBytes,const char *_VarName);
  extern errno_t  _itoa_s(int _Value,char *_DstBuf,size_t _Size,int _Radix);

  extern errno_t  _i64toa_s(long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  extern errno_t  _ui64toa_s(unsigned long long _Val,char *_DstBuf,size_t _Size,int _Radix);

  extern errno_t  _ltoa_s(long _Val,char *_DstBuf,size_t _Size,int _Radix);
  extern errno_t  mbstowcs_s(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount);
  extern errno_t  _mbstowcs_s_l(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount,_locale_t _Locale);
  extern errno_t  _ultoa_s(unsigned long _Val,char *_DstBuf,size_t _Size,int _Radix);
  extern errno_t  _wctomb_s_l(int *_SizeConverted,char *_MbCh,size_t _SizeInBytes,wchar_t _WCh,_locale_t _Locale);
  extern errno_t  wcstombs_s(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes);
  extern errno_t  _wcstombs_s_l(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes,_locale_t _Locale);



  extern errno_t  _itow_s (int _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  extern errno_t  _ltow_s (long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  extern errno_t  _ultow_s (unsigned long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  extern errno_t  _wgetenv_s(size_t *_ReturnSize,wchar_t *_DstBuf,size_t _DstSizeInWords,const wchar_t *_VarName);
  extern errno_t  _wdupenv_s(wchar_t **_Buffer,size_t *_BufferSizeInWords,const wchar_t *_VarName);

  extern errno_t  _i64tow_s(long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  extern errno_t  _ui64tow_s(unsigned long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);




  extern errno_t  _ecvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDights,int *_PtDec,int *_PtSign);
  extern errno_t  _fcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  extern errno_t  _gcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDigits);
  extern errno_t  _makepath_s(char *_PathResult,size_t _Size,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  extern errno_t  _putenv_s(const char *_Name,const char *_Value);
  extern errno_t  _searchenv_s(const char *_Filename,const char *_EnvVar,char *_ResultPath,size_t _SizeInBytes);
  extern errno_t  _splitpath_s(const char *_FullPath,char *_Drive,size_t _DriveSize,char *_Dir,size_t _DirSize,char *_Filename,size_t _FilenameSize,char *_Ext,size_t _ExtSize);



  extern errno_t  _wmakepath_s(wchar_t *_PathResult,size_t _SizeInWords,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);
  extern errno_t  _wputenv_s(const wchar_t *_Name,const wchar_t *_Value);
  extern errno_t  _wsearchenv_s(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath,size_t _SizeInWords);
  extern errno_t  _wsplitpath_s(const wchar_t *_FullPath,wchar_t *_Drive,size_t _DriveSizeInWords,wchar_t *_Dir,size_t _DirSizeInWords,wchar_t *_Filename,size_t _FilenameSizeInWords,wchar_t *_Ext,size_t _ExtSizeInWords);
# 578 "c:/program files/tcc/include/stdlib.h" 2
# 1 "c:/program files/tcc/include/malloc.h" 1
# 11 "c:/program files/tcc/include/malloc.h"
#pragma pack(push,8)
# 46 "c:/program files/tcc/include/malloc.h"
  typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;


  extern unsigned int _amblksiz;
# 76 "c:/program files/tcc/include/malloc.h"
  extern int  _resetstkoflw (void);
  extern unsigned long  _set_malloc_crt_max_wait(unsigned long _NewValue);

  extern void * _expand(void *_Memory,size_t _NewSize);
  extern size_t  _msize(void *_Memory);
# 93 "c:/program files/tcc/include/malloc.h"
  extern size_t  _get_sbh_threshold(void);
  extern int  _set_sbh_threshold(size_t _NewValue);
  extern errno_t  _set_amblksiz(size_t _Value);
  extern errno_t  _get_amblksiz(size_t *_Value);
  extern int  _heapadd(void *_Memory,size_t _Size);
  extern int  _heapchk(void);
  extern int  _heapmin(void);
  extern int  _heapset(unsigned int _Fill);
  extern int  _heapwalk(_HEAPINFO *_EntryInfo);
  extern size_t  _heapused(size_t *_Used,size_t *_Commit);
  extern intptr_t  _get_heap_handle(void);
# 116 "c:/program files/tcc/include/malloc.h"
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + 16;
    }
    return _Ptr;
  }
# 135 "c:/program files/tcc/include/malloc.h"
  static __inline void  _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - 16;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==0xDDDD) {
	free(_Memory);
      }





    }
  }
# 179 "c:/program files/tcc/include/malloc.h"
#pragma pack(pop)
# 579 "c:/program files/tcc/include/stdlib.h" 2
# 4 "SGL.c" 2
# 1 "c:/program files/tcc/include/ctype.h" 1
# 36 "c:/program files/tcc/include/ctype.h"
  extern unsigned short **_imp___pctype;
# 51 "c:/program files/tcc/include/ctype.h"
  extern unsigned short **_imp___wctype;
# 63 "c:/program files/tcc/include/ctype.h"
  extern unsigned short **_imp___pwctype;
# 72 "c:/program files/tcc/include/ctype.h"
  extern const unsigned char __newclmap[];
  extern const unsigned char __newcumap[];
  extern pthreadlocinfo __ptlocinfo;
  extern pthreadmbcinfo __ptmbcinfo;
  extern int __globallocalestatus;
  extern int __locale_changed;
  extern struct threadlocaleinfostruct __initiallocinfo;
  extern _locale_tstruct __initiallocalestructinfo;
  pthreadlocinfo  __updatetlocinfo(void);
  pthreadmbcinfo  __updatetmbcinfo(void);
# 100 "c:/program files/tcc/include/ctype.h"
  extern int  _isctype(int _C,int _Type);
  extern int  _isctype_l(int _C,int _Type,_locale_t _Locale);
  extern int  isalpha(int _C);
  extern int  _isalpha_l(int _C,_locale_t _Locale);
  extern int  isupper(int _C);
  extern int  _isupper_l(int _C,_locale_t _Locale);
  extern int  islower(int _C);
  extern int  _islower_l(int _C,_locale_t _Locale);
  extern int  isdigit(int _C);
  extern int  _isdigit_l(int _C,_locale_t _Locale);
  extern int  isxdigit(int _C);
  extern int  _isxdigit_l(int _C,_locale_t _Locale);
  extern int  isspace(int _C);
  extern int  _isspace_l(int _C,_locale_t _Locale);
  extern int  ispunct(int _C);
  extern int  _ispunct_l(int _C,_locale_t _Locale);
  extern int  isalnum(int _C);
  extern int  _isalnum_l(int _C,_locale_t _Locale);
  extern int  isprint(int _C);
  extern int  _isprint_l(int _C,_locale_t _Locale);
  extern int  isgraph(int _C);
  extern int  _isgraph_l(int _C,_locale_t _Locale);
  extern int  iscntrl(int _C);
  extern int  _iscntrl_l(int _C,_locale_t _Locale);
  extern int  toupper(int _C);
  extern int  tolower(int _C);
  extern int  _tolower(int _C);
  extern int  _tolower_l(int _C,_locale_t _Locale);
  extern int  _toupper(int _C);
  extern int  _toupper_l(int _C,_locale_t _Locale);
  extern int  __isascii(int _C);
  extern int  __toascii(int _C);
  extern int  __iscsymf(int _C);
  extern int  __iscsym(int _C);


int  isblank(int _C);






  int  iswalpha(wint_t _C);
  extern int  _iswalpha_l(wint_t _C,_locale_t _Locale);
  int  iswupper(wint_t _C);
  extern int  _iswupper_l(wint_t _C,_locale_t _Locale);
  int  iswlower(wint_t _C);
  extern int  _iswlower_l(wint_t _C,_locale_t _Locale);
  int  iswdigit(wint_t _C);
  extern int  _iswdigit_l(wint_t _C,_locale_t _Locale);
  int  iswxdigit(wint_t _C);
  extern int  _iswxdigit_l(wint_t _C,_locale_t _Locale);
  int  iswspace(wint_t _C);
  extern int  _iswspace_l(wint_t _C,_locale_t _Locale);
  int  iswpunct(wint_t _C);
  extern int  _iswpunct_l(wint_t _C,_locale_t _Locale);
  int  iswalnum(wint_t _C);
  extern int  _iswalnum_l(wint_t _C,_locale_t _Locale);
  int  iswprint(wint_t _C);
  extern int  _iswprint_l(wint_t _C,_locale_t _Locale);
  int  iswgraph(wint_t _C);
  extern int  _iswgraph_l(wint_t _C,_locale_t _Locale);
  int  iswcntrl(wint_t _C);
  extern int  _iswcntrl_l(wint_t _C,_locale_t _Locale);
  int  iswascii(wint_t _C);
  int  isleadbyte(int _C);
  extern int  _isleadbyte_l(int _C,_locale_t _Locale);
  wint_t  towupper(wint_t _C);
  extern wint_t  _towupper_l(wint_t _C,_locale_t _Locale);
  wint_t  towlower(wint_t _C);
  extern wint_t  _towlower_l(wint_t _C,_locale_t _Locale);
  int  iswctype(wint_t _C,wctype_t _Type);
  extern int  _iswctype_l(wint_t _C,wctype_t _Type,_locale_t _Locale);
  extern int  __iswcsymf(wint_t _C);
  extern int  _iswcsymf_l(wint_t _C,_locale_t _Locale);
  extern int  __iswcsym(wint_t _C);
  extern int  _iswcsym_l(wint_t _C,_locale_t _Locale);
  int  is_wctype(wint_t _C,wctype_t _Type);


int  iswblank(wint_t _C);
# 5 "SGL.c" 2
# 1 "c:/program files/tcc/include/winapi/windows.h" 1
# 62 "c:/program files/tcc/include/winapi/windows.h"
# 1 "c:/program files/tcc/include/excpt.h" 1
# 11 "c:/program files/tcc/include/excpt.h"
#pragma pack(push,8)





  struct _EXCEPTION_POINTERS;
# 42 "c:/program files/tcc/include/excpt.h"
  struct _EXCEPTION_RECORD;
  struct _CONTEXT;
# 53 "c:/program files/tcc/include/excpt.h"
  unsigned long  _exception_code(void);
  void * _exception_info(void);
  int  _abnormal_termination(void);






  typedef void ( * _PHNDLR)(int);

  struct _XCPT_ACTION {
    unsigned long XcptNum;
    int SigNum;
    _PHNDLR XcptAction;
  };

  extern struct _XCPT_ACTION _XcptActTab[];
  extern int _XcptActTabCount;
  extern int _XcptActTabSize;
  extern int _First_FPE_Indx;
  extern int _Num_FPE;

  int  __CppXcptFilter(unsigned long _ExceptionNum,struct _EXCEPTION_POINTERS * _ExceptionPtr);
  int  _XcptFilter(unsigned long _ExceptionNum,struct _EXCEPTION_POINTERS * _ExceptionPtr);





  typedef int (*PEXCEPTION_HANDLER)(struct _EXCEPTION_RECORD*, void*, struct _CONTEXT*, void*);






  typedef struct _EXCEPTION_REGISTRATION {
    struct _EXCEPTION_REGISTRATION *prev;
    int (*handler)(struct _EXCEPTION_RECORD*, void*, struct _CONTEXT*, void*);
  } EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;

  typedef EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION_RECORD;
  typedef PEXCEPTION_REGISTRATION PEXCEPTION_REGISTRATION_RECORD;
# 122 "c:/program files/tcc/include/excpt.h"
#pragma pack(pop)
# 63 "c:/program files/tcc/include/winapi/windows.h" 2



# 1 "c:/program files/tcc/include/winapi/windef.h" 1
# 23 "c:/program files/tcc/include/winapi/windef.h"
  typedef unsigned long ULONG;
  typedef ULONG *PULONG;
  typedef unsigned short USHORT;
  typedef USHORT *PUSHORT;
  typedef unsigned char UCHAR;
  typedef UCHAR *PUCHAR;
  typedef char *PSZ;
# 94 "c:/program files/tcc/include/winapi/windef.h"
  typedef unsigned long DWORD;
  typedef int WINBOOL;

  typedef unsigned char BYTE;
  typedef unsigned short WORD;
  typedef float FLOAT;
  typedef FLOAT *PFLOAT;
  typedef WINBOOL *PBOOL;
  typedef WINBOOL *LPBOOL;
  typedef BYTE *PBYTE;
  typedef BYTE *LPBYTE;
  typedef int *PINT;
  typedef int *LPINT;
  typedef WORD *PWORD;
  typedef WORD *LPWORD;
  typedef long *LPLONG;
  typedef DWORD *PDWORD;
  typedef DWORD *LPDWORD;
  typedef void *LPVOID;


typedef const void *LPCVOID;

  typedef int INT;
  typedef unsigned int UINT;
  typedef unsigned int *PUINT;


# 1 "c:/program files/tcc/include/winapi/winnt.h" 1
# 80 "c:/program files/tcc/include/winapi/winnt.h"
# 1 "c:/program files/tcc/include/winapi/basetsd.h" 1
# 10 "c:/program files/tcc/include/winapi/basetsd.h"
typedef unsigned long long POINTER_64_INT;
# 23 "c:/program files/tcc/include/winapi/basetsd.h"
  typedef signed char INT8,*PINT8;
  typedef signed short INT16,*PINT16;
  typedef signed int INT32,*PINT32;
  typedef signed long long INT64,*PINT64;
  typedef unsigned char UINT8,*PUINT8;
  typedef unsigned short UINT16,*PUINT16;
  typedef unsigned int UINT32,*PUINT32;
  typedef unsigned long long UINT64,*PUINT64;
  typedef signed int LONG32,*PLONG32;
  typedef unsigned int ULONG32,*PULONG32;
  typedef unsigned int DWORD32,*PDWORD32;






  typedef long long INT_PTR,*PINT_PTR;
  typedef unsigned long long UINT_PTR,*PUINT_PTR;
  typedef long long LONG_PTR,*PLONG_PTR;
  typedef unsigned long long ULONG_PTR,*PULONG_PTR;
# 55 "c:/program files/tcc/include/winapi/basetsd.h"
  typedef long long SHANDLE_PTR;
  typedef unsigned long long HANDLE_PTR;
  typedef unsigned int UHALF_PTR,*PUHALF_PTR;
  typedef int HALF_PTR,*PHALF_PTR;

  static __inline unsigned long HandleToULong(const void *h) { return((unsigned long) (ULONG_PTR) h); }
  static __inline long HandleToLong(const void *h) { return((long) (LONG_PTR) h); }
  static __inline void *ULongToHandle(const unsigned long h) { return((void *) (UINT_PTR) h); }
  static __inline void *LongToHandle(const long h) { return((void *) (INT_PTR) h); }
  static __inline unsigned long PtrToUlong(const void *p) { return((unsigned long) (ULONG_PTR) p); }
  static __inline unsigned int PtrToUint(const void *p) { return((unsigned int) (UINT_PTR) p); }
  static __inline unsigned short PtrToUshort(const void *p) { return((unsigned short) (unsigned long) (ULONG_PTR) p); }
  static __inline long PtrToLong(const void *p) { return((long) (LONG_PTR) p); }
  static __inline int PtrToInt(const void *p) { return((int) (INT_PTR) p); }
  static __inline short PtrToShort(const void *p) { return((short) (long) (LONG_PTR) p); }
  static __inline void *IntToPtr(const int i) { return((void *)(INT_PTR)i); }
  static __inline void *UIntToPtr(const unsigned int ui) { return((void *)(UINT_PTR)ui); }
  static __inline void *LongToPtr(const long l) { return((void *)(LONG_PTR)l); }
  static __inline void *ULongToPtr(const unsigned long ul) { return((void *)(ULONG_PTR)ul); }






  static __inline void *Ptr32ToPtr(const void *p) { return (void *)p; }
  static __inline void *Handle32ToHandle(const void *h) { return((void *) h); }
  static __inline void *PtrToPtr32(const void *p) { return((void *) (ULONG_PTR) p); }
# 137 "c:/program files/tcc/include/winapi/basetsd.h"
  typedef ULONG_PTR SIZE_T,*PSIZE_T;
  typedef LONG_PTR SSIZE_T,*PSSIZE_T;
  typedef ULONG_PTR DWORD_PTR,*PDWORD_PTR;
  typedef long long LONG64,*PLONG64;
  typedef unsigned long long ULONG64,*PULONG64;
  typedef unsigned long long DWORD64,*PDWORD64;
  typedef ULONG_PTR KAFFINITY;
  typedef KAFFINITY *PKAFFINITY;
# 81 "c:/program files/tcc/include/winapi/winnt.h" 2
# 140 "c:/program files/tcc/include/winapi/winnt.h"
  typedef void *PVOID;
  typedef void *PVOID64;







  typedef char CHAR;
  typedef short SHORT;
  typedef long LONG;


  typedef wchar_t WCHAR;
  typedef WCHAR *PWCHAR,*LPWCH,*PWCH;
  typedef const WCHAR *LPCWCH,*PCWCH;
  typedef WCHAR *NWPSTR,*LPWSTR,*PWSTR;
  typedef PWSTR *PZPWSTR;
  typedef const PWSTR *PCZPWSTR;
  typedef WCHAR  *LPUWSTR,*PUWSTR;
  typedef const WCHAR *LPCWSTR,*PCWSTR;
  typedef PCWSTR *PZPCWSTR;
  typedef const WCHAR  *LPCUWSTR,*PCUWSTR;
  typedef CHAR *PCHAR,*LPCH,*PCH;
  typedef const CHAR *LPCCH,*PCCH;
  typedef CHAR *NPSTR,*LPSTR,*PSTR;
  typedef PSTR *PZPSTR;
  typedef const PSTR *PCZPSTR;
  typedef const CHAR *LPCSTR,*PCSTR;
  typedef PCSTR *PZPCSTR;
# 189 "c:/program files/tcc/include/winapi/winnt.h"
  typedef char TCHAR,*PTCHAR;
  typedef unsigned char TBYTE ,*PTBYTE;


  typedef LPSTR LPTCH,PTCH;
  typedef LPSTR PTSTR,LPTSTR,PUTSTR,LPUTSTR;
  typedef LPCSTR PCTSTR,LPCTSTR,PCUTSTR,LPCUTSTR;





  typedef SHORT *PSHORT;
  typedef LONG *PLONG;

  typedef void *HANDLE;

  typedef HANDLE *PHANDLE;

  typedef BYTE FCHAR;
  typedef WORD FSHORT;
  typedef DWORD FLONG;



  typedef LONG HRESULT;
# 236 "c:/program files/tcc/include/winapi/winnt.h"
  typedef char CCHAR;


typedef DWORD LCID;

  typedef PDWORD PLCID;


  typedef WORD LANGID;
# 255 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _FLOAT128 {
      long long LowPart;
      long long HighPart;
  } FLOAT128;

  typedef FLOAT128 *PFLOAT128;



  typedef long long LONGLONG;
  typedef unsigned long long ULONGLONG;
# 274 "c:/program files/tcc/include/winapi/winnt.h"
  typedef LONGLONG *PLONGLONG;
  typedef ULONGLONG *PULONGLONG;

  typedef LONGLONG USN;

  typedef union _LARGE_INTEGER {
    struct {
      DWORD LowPart;
      LONG HighPart;
    };
    struct {
      DWORD LowPart;
      LONG HighPart;
    } u;
    LONGLONG QuadPart;
  } LARGE_INTEGER;

  typedef LARGE_INTEGER *PLARGE_INTEGER;

  typedef union _ULARGE_INTEGER {
    struct {
      DWORD LowPart;
      DWORD HighPart;
    };
    struct {
      DWORD LowPart;
      DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
  } ULARGE_INTEGER;

  typedef ULARGE_INTEGER *PULARGE_INTEGER;

  typedef struct _LUID {
    DWORD LowPart;
    LONG HighPart;
  } LUID,*PLUID;


  typedef ULONGLONG DWORDLONG;
  typedef DWORDLONG *PDWORDLONG;
# 346 "c:/program files/tcc/include/winapi/winnt.h"
    unsigned char  _rotl8(unsigned char Value,unsigned char Shift);
    unsigned short  _rotl16(unsigned short Value,unsigned char Shift);
    unsigned char  _rotr8(unsigned char Value,unsigned char Shift);
    unsigned short  _rotr16(unsigned short Value,unsigned char Shift);







    unsigned int  _rotl(unsigned int Value,int Shift);
    unsigned long long  _rotl64(unsigned long long Value,int Shift);
    unsigned int  _rotr(unsigned int Value,int Shift);
    unsigned long long  _rotr64(unsigned long long Value,int Shift);
# 372 "c:/program files/tcc/include/winapi/winnt.h"
  typedef BYTE BOOLEAN;

  typedef BOOLEAN *PBOOLEAN;

  typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
  } LIST_ENTRY,*PLIST_ENTRY,* PRLIST_ENTRY;

  typedef struct _SINGLE_LIST_ENTRY {
    struct _SINGLE_LIST_ENTRY *Next;
  } SINGLE_LIST_ENTRY,*PSINGLE_LIST_ENTRY;

  typedef struct LIST_ENTRY32 {
    DWORD Flink;
    DWORD Blink;
  } LIST_ENTRY32;
  typedef LIST_ENTRY32 *PLIST_ENTRY32;

  typedef struct LIST_ENTRY64 {
    ULONGLONG Flink;
    ULONGLONG Blink;
  } LIST_ENTRY64;
  typedef LIST_ENTRY64 *PLIST_ENTRY64;

# 1 "c:/program files/tcc/include/winapi/guiddef.h" 1







typedef struct _GUID {
  unsigned long Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char Data4[8 ];
} GUID;




typedef GUID UUID;
# 58 "c:/program files/tcc/include/winapi/guiddef.h"
typedef GUID *LPGUID;




typedef const GUID *LPCGUID;





typedef GUID IID;
typedef IID *LPIID;


typedef GUID CLSID;
typedef CLSID *LPCLSID;


typedef GUID FMTID;
typedef FMTID *LPFMTID;
# 127 "c:/program files/tcc/include/winapi/guiddef.h"
# 1 "c:/program files/tcc/include/string.h" 1
# 32 "c:/program files/tcc/include/string.h"
  extern void * _memccpy(void *_Dst,const void *_Src,int _Val,size_t _MaxCount);
   void * memchr(const void *_Buf ,int _Val,size_t _MaxCount);
  extern int  _memicmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  extern int  _memicmp_l(const void *_Buf1,const void *_Buf2,size_t _Size,_locale_t _Locale);
  int  memcmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  void * memcpy(void *_Dst,const void *_Src,size_t _Size);
  void * memset(void *_Dst,int _Val,size_t _Size);

  void * memccpy(void *_Dst,const void *_Src,int _Val,size_t _Size);
  int  memicmp(const void *_Buf1,const void *_Buf2,size_t _Size);


  char * _strset(char *_Str,int _Val);
  char * strcpy(char *_Dest,const char *_Source);
  char * strcat(char *_Dest,const char *_Source);
  int  strcmp(const char *_Str1,const char *_Str2);
  size_t  strlen(const char *_Str);



  void * memmove(void *_Dst,const void *_Src,size_t _Size);
  extern char * _strdup(const char *_Src);
   char * strchr(const char *_Str,int _Val);
  extern int  _stricmp(const char *_Str1,const char *_Str2);
  extern int  _strcmpi(const char *_Str1,const char *_Str2);
  extern int  _stricmp_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  int  strcoll(const char *_Str1,const char *_Str2);
  extern int  _strcoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  extern int  _stricoll(const char *_Str1,const char *_Str2);
  extern int  _stricoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  extern int  _strncoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  extern int  _strncoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  extern int  _strnicoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  extern int  _strnicoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  size_t  strcspn(const char *_Str,const char *_Control);
  extern char * _strerror(const char *_ErrMsg);
  char * strerror(int);
  extern char * _strlwr(char *_String);
  char *strlwr_l(char *_String,_locale_t _Locale);
  char * strncat(char *_Dest,const char *_Source,size_t _Count);
  int  strncmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  extern int  _strnicmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  extern int  _strnicmp_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  char *strncpy(char *_Dest,const char *_Source,size_t _Count);
  extern char * _strnset(char *_Str,int _Val,size_t _MaxCount);
   char * strpbrk(const char *_Str,const char *_Control);
   char * strrchr(const char *_Str,int _Ch);
  extern char * _strrev(char *_Str);
  size_t  strspn(const char *_Str,const char *_Control);
   char * strstr(const char *_Str,const char *_SubStr);
  char * strtok(char *_Str,const char *_Delim);
  extern char * _strupr(char *_String);
  extern char *_strupr_l(char *_String,_locale_t _Locale);
  size_t  strxfrm(char *_Dst,const char *_Src,size_t _MaxCount);
  extern size_t  _strxfrm_l(char *_Dst,const char *_Src,size_t _MaxCount,_locale_t _Locale);


  char * strdup(const char *_Src);
  int  strcmpi(const char *_Str1,const char *_Str2);
  int  stricmp(const char *_Str1,const char *_Str2);
  char * strlwr(char *_Str);
  int  strnicmp(const char *_Str1,const char *_Str,size_t _MaxCount);
  extern __inline__ int  strncasecmp (const char *__sz1, const char *__sz2, size_t __sizeMaxCompare) { return _strnicmp (__sz1, __sz2, __sizeMaxCompare); }
  extern __inline__ int  strcasecmp (const char *__sz1, const char *__sz2) { return _stricmp (__sz1, __sz2); }
  char * strnset(char *_Str,int _Val,size_t _MaxCount);
  char * strrev(char *_Str);
  char * strset(char *_Str,int _Val);
  char * strupr(char *_Str);





  extern wchar_t * _wcsdup(const wchar_t *_Str);
  wchar_t * wcscat(wchar_t *_Dest,const wchar_t *_Source);
   wchar_t * wcschr(const wchar_t *_Str,wchar_t _Ch);
  int  wcscmp(const wchar_t *_Str1,const wchar_t *_Str2);
  wchar_t * wcscpy(wchar_t *_Dest,const wchar_t *_Source);
  size_t  wcscspn(const wchar_t *_Str,const wchar_t *_Control);
  size_t  wcslen(const wchar_t *_Str);
  size_t  wcsnlen(const wchar_t *_Src,size_t _MaxCount);
  wchar_t *wcsncat(wchar_t *_Dest,const wchar_t *_Source,size_t _Count);
  int  wcsncmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  wchar_t *wcsncpy(wchar_t *_Dest,const wchar_t *_Source,size_t _Count);
   wchar_t * wcspbrk(const wchar_t *_Str,const wchar_t *_Control);
   wchar_t * wcsrchr(const wchar_t *_Str,wchar_t _Ch);
  size_t  wcsspn(const wchar_t *_Str,const wchar_t *_Control);
   wchar_t * wcsstr(const wchar_t *_Str,const wchar_t *_SubStr);
  wchar_t * wcstok(wchar_t *_Str,const wchar_t *_Delim);
  extern wchar_t * _wcserror(int _ErrNum);
  extern wchar_t * __wcserror(const wchar_t *_Str);
  extern int  _wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2);
  extern int  _wcsicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  extern int  _wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  extern int  _wcsnicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  extern wchar_t * _wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount);
  extern wchar_t * _wcsrev(wchar_t *_Str);
  extern wchar_t * _wcsset(wchar_t *_Str,wchar_t _Val);
  extern wchar_t * _wcslwr(wchar_t *_String);
  extern wchar_t *_wcslwr_l(wchar_t *_String,_locale_t _Locale);
  extern wchar_t * _wcsupr(wchar_t *_String);
  extern wchar_t *_wcsupr_l(wchar_t *_String,_locale_t _Locale);
  size_t  wcsxfrm(wchar_t *_Dst,const wchar_t *_Src,size_t _MaxCount);
  extern size_t  _wcsxfrm_l(wchar_t *_Dst,const wchar_t *_Src,size_t _MaxCount,_locale_t _Locale);
  int  wcscoll(const wchar_t *_Str1,const wchar_t *_Str2);
  extern int  _wcscoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  extern int  _wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2);
  extern int  _wcsicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  extern int  _wcsncoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  extern int  _wcsncoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  extern int  _wcsnicoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  extern int  _wcsnicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);


  wchar_t * wcsdup(const wchar_t *_Str);

  int  wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2);
  int  wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  wchar_t * wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount);
  wchar_t * wcsrev(wchar_t *_Str);
  wchar_t * wcsset(wchar_t *_Str,wchar_t _Val);
  wchar_t * wcslwr(wchar_t *_Str);
  wchar_t * wcsupr(wchar_t *_Str);
  int  wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2);







# 1 "c:/program files/tcc/include/sec_api/string_s.h" 1
# 9 "c:/program files/tcc/include/sec_api/string_s.h"
# 1 "c:/program files/tcc/include/string.h" 1
# 10 "c:/program files/tcc/include/sec_api/string_s.h" 2







  extern errno_t  _strset_s(char *_Dst,size_t _DstSize,int _Value);
  extern errno_t  _strerror_s(char *_Buf,size_t _SizeInBytes,const char *_ErrMsg);
  extern errno_t  _strlwr_s(char *_Str,size_t _Size);
  extern errno_t  _strlwr_s_l(char *_Str,size_t _Size,_locale_t _Locale);
  extern errno_t  _strnset_s(char *_Str,size_t _Size,int _Val,size_t _MaxCount);
  extern errno_t  _strupr_s(char *_Str,size_t _Size);
  extern errno_t  _strupr_s_l(char *_Str,size_t _Size,_locale_t _Locale);


  extern wchar_t * wcstok_s(wchar_t *_Str,const wchar_t *_Delim,wchar_t **_Context);
  extern errno_t  _wcserror_s(wchar_t *_Buf,size_t _SizeInWords,int _ErrNum);
  extern errno_t  __wcserror_s(wchar_t *_Buffer,size_t _SizeInWords,const wchar_t *_ErrMsg);
  extern errno_t  _wcsnset_s(wchar_t *_Dst,size_t _DstSizeInWords,wchar_t _Val,size_t _MaxCount);
  extern errno_t  _wcsset_s(wchar_t *_Str,size_t _SizeInWords,wchar_t _Val);
  extern errno_t  _wcslwr_s(wchar_t *_Str,size_t _SizeInWords);
  extern errno_t  _wcslwr_s_l(wchar_t *_Str,size_t _SizeInWords,_locale_t _Locale);
  extern errno_t  _wcsupr_s(wchar_t *_Str,size_t _Size);
  extern errno_t  _wcsupr_s_l(wchar_t *_Str,size_t _Size,_locale_t _Locale);
# 164 "c:/program files/tcc/include/string.h" 2
# 128 "c:/program files/tcc/include/winapi/guiddef.h" 2
# 398 "c:/program files/tcc/include/winapi/winnt.h" 2



  typedef struct _OBJECTID {
    GUID Lineage;
    DWORD Uniquifier;
  } OBJECTID;
# 829 "c:/program files/tcc/include/winapi/winnt.h"
  typedef ULONG_PTR KSPIN_LOCK;
  typedef KSPIN_LOCK *PKSPIN_LOCK;
# 853 "c:/program files/tcc/include/winapi/winnt.h"
    extern __inline__ BOOLEAN _bittest(LONG const *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("btl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandcomplement(LONG *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("btcl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN InterlockedBitTestAndComplement(LONG *Base,LONG Bit) {
      int old = 0;
      __asm__ __volatile__("lock ; btcl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Bit));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandset(LONG *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("btsl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandreset(LONG *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("btrl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _interlockedbittestandset(LONG *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("lock ; btsl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _interlockedbittestandreset(LONG *Base,LONG Offset) {
      int old = 0;
      __asm__ __volatile__("lock ; btrl %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittest64(LONG64 const *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("btq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandcomplement64(LONG64 *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("btcq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandset64(LONG64 *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("btsq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _bittestandreset64(LONG64 *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("btrq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _interlockedbittestandset64(LONG64 *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("lock ; btsq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }
    extern __inline__ BOOLEAN _interlockedbittestandreset64(LONG64 *Base,LONG64 Offset) {
      int old = 0;
      __asm__ __volatile__("lock ; btrq %2,%1\n\tsbbl %0,%0 "
	:"=r" (old),"=m" ((*(volatile long long *) Base))
	:"Ir" (Offset));
      return (BOOLEAN) (old!=0);
    }





    extern __inline__ BOOLEAN _BitScanForward(DWORD *Index,DWORD Mask) {
      __asm__ __volatile__("bsfl %1,%0" : "=r" (Mask),"=m" ((*(volatile long *)Index)));
      return Mask!=0;
    }
    extern __inline__ BOOLEAN _BitScanReverse(DWORD *Index,DWORD Mask) {
      __asm__ __volatile__("bsrl %1,%0" : "=r" (Mask),"=m" ((*(volatile long *)Index)));
      return Mask!=0;
    }
    extern __inline__ BOOLEAN _BitScanForward64(DWORD *Index,DWORD64 Mask) {
      __asm__ __volatile__("bsfq %1,%0" : "=r" (Mask),"=m" ((*(volatile long long *)Index)));
      return Mask!=0;
    }
    extern __inline__ BOOLEAN _BitScanReverse64(DWORD *Index,DWORD64 Mask) {
      __asm__ __volatile__("bsrq %1,%0" : "=r" (Mask),"=m" ((*(volatile long long *)Index)));
      return Mask!=0;
    }
# 1010 "c:/program files/tcc/include/winapi/winnt.h"
    extern __inline__ SHORT _InterlockedIncrement16(SHORT volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; addw $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ SHORT _InterlockedDecrement16(SHORT volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; subw $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ SHORT _InterlockedCompareExchange16(SHORT volatile *Destination,SHORT ExChange,SHORT Comperand) {
      SHORT prev;
      __asm__ __volatile__("lock ; cmpxchgw %w1,%2"
	:"=a"(prev)
	:"q"(ExChange), "m"(*Destination), "0"(Comperand)
	: "memory");
      return prev;
    }
    extern __inline__ LONG _InterlockedAnd(LONG volatile *Destination,LONG Value) {
      __asm__ __volatile__("lock ; andl %0,%1"
	: :"r"(Value),"m"(*Destination)
	: "memory");
      return *Destination;
    }
    extern __inline__ LONG _InterlockedOr(LONG volatile *Destination,LONG Value) {
      __asm__ __volatile__("lock ; orl %0,%1"
	: : "r"(Value),"m"(*Destination) : "memory");
      return *Destination;
    }
    extern __inline__ LONG _InterlockedXor(LONG volatile *Destination,LONG Value) {
      __asm__ __volatile__("lock ; xorl %0,%1"
	: : "r"(Value),"m"(*Destination) : "memory");
      return *Destination;
    }

    extern __inline__ LONG64 _InterlockedAnd64(LONG64 volatile *Destination,LONG64 Value) {
      __asm__ __volatile__("lock ; andq %0,%1"
	: : "r"(Value),"m"(*Destination) : "memory");
      return *Destination;
    }
    extern __inline__ LONG64 _InterlockedOr64(LONG64 volatile *Destination,LONG64 Value) {
      __asm__ __volatile__("lock ; orq %0,%1"
	: : "r"(Value),"m"(*Destination) : "memory");
      return *Destination;
    }
    extern __inline__ LONG64 _InterlockedXor64(LONG64 volatile *Destination,LONG64 Value) {
      __asm__ __volatile__("lock ; xorq %0,%1"
	: : "r"(Value),"m"(*Destination) : "memory");
      return *Destination;
    }
    extern __inline__ LONG _InterlockedIncrement(LONG volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; addl $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ LONG _InterlockedDecrement(LONG volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; subl $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ LONG _InterlockedExchange(LONG volatile *Target,LONG Value) {
      __asm__ __volatile("lock ; xchgl %0,%1"
	: "=r"(Value)
	: "m"(*Target),"0"(Value)
	: "memory");
      return Value;
    }
    LONG _InterlockedExchangeAdd(LONG volatile *Addend,LONG Value);


    extern __inline__ LONG _InterlockedAdd(LONG volatile *Addend,LONG Value) { return _InterlockedExchangeAdd(Addend,Value) + Value; }

    extern __inline__ LONG _InterlockedCompareExchange(LONG volatile *Destination,LONG ExChange,LONG Comperand) {
      LONG prev;
      __asm__ __volatile__("lock ; cmpxchgl %1,%2" : "=a" (prev) : "q" (ExChange),"m" (*Destination), "0" (Comperand) : "memory");
      return prev;
    }
    extern __inline__ LONG64 _InterlockedIncrement64(LONG64 volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; addq $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ LONG64 _InterlockedDecrement64(LONG64 volatile *Addend) {
      unsigned char c;
      unsigned char s;
      __asm__ __volatile__(
	"lock ; subq $1,%0; sete %1 ; sets %2"
	:"=m" (*Addend), "=qm" (c), "=qm" (s)
	:"m" (*Addend) : "memory");
      return (c != 0 ? 0 : (s != 0 ? -1 : 1));
    }
    extern __inline__ LONG64 _InterlockedExchange64(LONG64 volatile *Target,LONG64 Value) {
      __asm__ __volatile("lock ; xchgq %0,%1"
	: "=r"(Value)
	: "m"(*Target),"0"(Value)
	: "memory");
      return Value;
    }
    LONG64 _InterlockedExchangeAdd64(LONG64 volatile *Addend,LONG64 Value);


    extern __inline__ LONG64 _InterlockedAdd64(LONG64 volatile *Addend,LONG64 Value) { return _InterlockedExchangeAdd64(Addend,Value) + Value; }


    extern __inline__ LONG64 _InterlockedCompareExchange64(LONG64 volatile *Destination,LONG64 ExChange,LONG64 Comperand) {
      LONG64 prev;
      __asm__ __volatile__("lock ; cmpxchgq %1,%2" : "=a" (prev) : "q" (ExChange),"m" (*Destination), "0" (Comperand) : "memory");
      return prev;
    }
    extern __inline__ PVOID _InterlockedCompareExchangePointer(PVOID volatile *Destination,PVOID ExChange,PVOID Comperand) {
      PVOID prev;
      __asm__ __volatile__("lock ; cmpxchgq %1,%2" : "=a" (prev) : "q" (ExChange),"m" (*Destination), "0" (Comperand) : "memory");
      return prev;
    }
    extern __inline__ PVOID _InterlockedExchangePointer(PVOID volatile *Target,PVOID Value) {
      __asm__ __volatile("lock ; xchgq %0,%1"
	: "=r"(Value)
	: "m"(*Target),"0"(Value)
	: "memory");
      return Value;
    }



    void _ReadWriteBarrier(void);






    void __faststorefence(void);
    void _m_prefetchw(volatile const void *Source);
# 1180 "c:/program files/tcc/include/winapi/winnt.h"
    void __int2c(void);




    unsigned int __getcallerseflags(void);



    DWORD __segmentlimit(DWORD Selector);



    DWORD64 __rdtsc(void);
    void __movsb(PBYTE Destination,BYTE const *Source,SIZE_T Count);
    void __movsw(PWORD Destination,WORD const *Source,SIZE_T Count);
    void __movsd(PDWORD Destination,DWORD const *Source,SIZE_T Count);
    void __movsq(PDWORD64 Destination,DWORD64 const *Source,SIZE_T Count);
    void __stosb(PBYTE Destination,BYTE Value,SIZE_T Count);
    void __stosw(PWORD Destination,WORD Value,SIZE_T Count);
    void __stosd(PDWORD Destination,DWORD Value,SIZE_T Count);
    void __stosq(PDWORD64 Destination,DWORD64 Value,SIZE_T Count);




    LONGLONG __mulh(LONGLONG Multiplier,LONGLONG Multiplicand);
    ULONGLONG __umulh(ULONGLONG Multiplier,ULONGLONG Multiplicand);




    DWORD64 __shiftleft128(DWORD64 LowPart,DWORD64 HighPart,BYTE Shift);
    DWORD64 __shiftright128(DWORD64 LowPart,DWORD64 HighPart,BYTE Shift);



    LONG64 _mul128(LONG64 Multiplier,LONG64 Multiplicand,LONG64 *HighProduct);



    DWORD64 _umul128(DWORD64 Multiplier,DWORD64 Multiplicand,DWORD64 *HighProduct);

    extern __inline__ LONG64 MultiplyExtract128(LONG64 Multiplier,LONG64 Multiplicand,BYTE Shift) {
      LONG64 extractedProduct;
      LONG64 highProduct;
      LONG64 lowProduct;
      lowProduct = _mul128(Multiplier,Multiplicand,&highProduct);
      extractedProduct = (LONG64)__shiftright128((LONG64)lowProduct,(LONG64)highProduct,Shift);
      return extractedProduct;
    }

    extern __inline__ DWORD64 UnsignedMultiplyExtract128(DWORD64 Multiplier,DWORD64 Multiplicand,BYTE Shift) {
      DWORD64 extractedProduct;
      DWORD64 highProduct;
      DWORD64 lowProduct;
      lowProduct = _umul128(Multiplier,Multiplicand,&highProduct);
      extractedProduct = __shiftright128(lowProduct,highProduct,Shift);
      return extractedProduct;
    }

    extern __inline__ BYTE __readgsbyte(DWORD Offset) {
      BYTE ret;
      __asm__ volatile ("movb	%%gs:%1,%0"
	: "=r" (ret) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
      return ret;
    }
    extern __inline__ WORD __readgsword(DWORD Offset) {
      WORD ret;
      __asm__ volatile ("movw	%%gs:%1,%0"
	: "=r" (ret) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
      return ret;
    }
    extern __inline__ DWORD __readgsdword(DWORD Offset) {
      DWORD ret;
      __asm__ volatile ("movl	%%gs:%1,%0"
	: "=r" (ret) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
      return ret;
    }
    extern __inline__ DWORD64 __readgsqword(DWORD Offset) {
      void *ret;
      __asm__ volatile ("movq	%%gs:%1,%0"
	: "=r" (ret) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
      return (DWORD64) ret;
    }
    extern __inline__ void __writegsbyte(DWORD Offset,BYTE Data) {
      __asm__ volatile ("movb	%0,%%gs:%1"
	: "=r" (Data) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
    }
    extern __inline__ void __writegsword(DWORD Offset,WORD Data) {
      __asm__ volatile ("movw	%0,%%gs:%1"
	: "=r" (Data) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
    }
    extern __inline__ void __writegsdword(DWORD Offset,DWORD Data) {
      __asm__ volatile ("movl	%0,%%gs:%1"
	: "=r" (Data) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
    }
    extern __inline__ void __writegsqword(DWORD Offset,DWORD64 Data) {
      __asm__ volatile ("movq	%0,%%gs:%1"
	: "=r" (Data) ,"=m" ((*(volatile long *) (DWORD64) Offset)));
    }
# 1313 "c:/program files/tcc/include/winapi/winnt.h"
  typedef __attribute__((aligned(16))) struct _M128A {
    ULONGLONG Low;
    LONGLONG High;
  } M128A,*PM128A;

  typedef struct _XMM_SAVE_AREA32 {
    WORD ControlWord;
    WORD StatusWord;
    BYTE TagWord;
    BYTE Reserved1;
    WORD ErrorOpcode;
    DWORD ErrorOffset;
    WORD ErrorSelector;
    WORD Reserved2;
    DWORD DataOffset;
    WORD DataSelector;
    WORD Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];
    M128A XmmRegisters[16];
    BYTE Reserved4[96];
  } XMM_SAVE_AREA32,*PXMM_SAVE_AREA32;



  typedef __attribute__((aligned(16))) struct _CONTEXT {
    DWORD64 P1Home;
    DWORD64 P2Home;
    DWORD64 P3Home;
    DWORD64 P4Home;
    DWORD64 P5Home;
    DWORD64 P6Home;
    DWORD ContextFlags;
    DWORD MxCsr;
    WORD SegCs;
    WORD SegDs;
    WORD SegEs;
    WORD SegFs;
    WORD SegGs;
    WORD SegSs;
    DWORD EFlags;
    DWORD64 Dr0;
    DWORD64 Dr1;
    DWORD64 Dr2;
    DWORD64 Dr3;
    DWORD64 Dr6;
    DWORD64 Dr7;
    DWORD64 Rax;
    DWORD64 Rcx;
    DWORD64 Rdx;
    DWORD64 Rbx;
    DWORD64 Rsp;
    DWORD64 Rbp;
    DWORD64 Rsi;
    DWORD64 Rdi;
    DWORD64 R8;
    DWORD64 R9;
    DWORD64 R10;
    DWORD64 R11;
    DWORD64 R12;
    DWORD64 R13;
    DWORD64 R14;
    DWORD64 R15;
    DWORD64 Rip;
    union {
      XMM_SAVE_AREA32 FltSave;
      XMM_SAVE_AREA32 FloatSave;
      struct {
	M128A Header[2];
	M128A Legacy[8];
	M128A Xmm0;
	M128A Xmm1;
	M128A Xmm2;
	M128A Xmm3;
	M128A Xmm4;
	M128A Xmm5;
	M128A Xmm6;
	M128A Xmm7;
	M128A Xmm8;
	M128A Xmm9;
	M128A Xmm10;
	M128A Xmm11;
	M128A Xmm12;
	M128A Xmm13;
	M128A Xmm14;
	M128A Xmm15;
      };
    };
    M128A VectorRegister[26];
    DWORD64 VectorControl;
    DWORD64 DebugControl;
    DWORD64 LastBranchToRip;
    DWORD64 LastBranchFromRip;
    DWORD64 LastExceptionToRip;
    DWORD64 LastExceptionFromRip;
  } CONTEXT,*PCONTEXT;



  typedef struct _RUNTIME_FUNCTION {
    DWORD BeginAddress;
    DWORD EndAddress;
    DWORD UnwindData;
  } RUNTIME_FUNCTION,*PRUNTIME_FUNCTION;

  typedef PRUNTIME_FUNCTION (*PGET_RUNTIME_FUNCTION_CALLBACK)(DWORD64 ControlPc,PVOID Context);
  typedef DWORD (*POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK)(HANDLE Process,PVOID TableAddress,PDWORD Entries,PRUNTIME_FUNCTION *Functions);



  __attribute__((dllimport)) void  RtlRestoreContext (PCONTEXT ContextRecord,struct _EXCEPTION_RECORD *ExceptionRecord);
  __attribute__((dllimport)) BOOLEAN  RtlAddFunctionTable(PRUNTIME_FUNCTION FunctionTable,DWORD EntryCount,DWORD64 BaseAddress);
  __attribute__((dllimport)) BOOLEAN  RtlInstallFunctionTableCallback(DWORD64 TableIdentifier,DWORD64 BaseAddress,DWORD Length,PGET_RUNTIME_FUNCTION_CALLBACK Callback,PVOID Context,PCWSTR OutOfProcessCallbackDll);
  __attribute__((dllimport)) BOOLEAN  RtlDeleteFunctionTable(PRUNTIME_FUNCTION FunctionTable);
# 1584 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _LDT_ENTRY {
      WORD LimitLow;
      WORD BaseLow;
      union {
	struct {
	  BYTE BaseMid;
	  BYTE Flags1;
	  BYTE Flags2;
	  BYTE BaseHi;
	} Bytes;
	struct {
	  DWORD BaseMid : 8;
	  DWORD Type : 5;
	  DWORD Dpl : 2;
	  DWORD Pres : 1;
	  DWORD LimitHi : 4;
	  DWORD Sys : 1;
	  DWORD Reserved_0 : 1;
	  DWORD Default_Big : 1;
	  DWORD Granularity : 1;
	  DWORD BaseHi : 8;
	} Bits;
      } HighWord;
    } LDT_ENTRY,*PLDT_ENTRY;
# 1935 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _EXCEPTION_RECORD {
      DWORD ExceptionCode;
      DWORD ExceptionFlags;
      struct _EXCEPTION_RECORD *ExceptionRecord;
      PVOID ExceptionAddress;
      DWORD NumberParameters;
      ULONG_PTR ExceptionInformation[15];
    } EXCEPTION_RECORD;

    typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

    typedef struct _EXCEPTION_RECORD32 {
      DWORD ExceptionCode;
      DWORD ExceptionFlags;
      DWORD ExceptionRecord;
      DWORD ExceptionAddress;
      DWORD NumberParameters;
      DWORD ExceptionInformation[15];
    } EXCEPTION_RECORD32,*PEXCEPTION_RECORD32;

    typedef struct _EXCEPTION_RECORD64 {
      DWORD ExceptionCode;
      DWORD ExceptionFlags;
      DWORD64 ExceptionRecord;
      DWORD64 ExceptionAddress;
      DWORD NumberParameters;
      DWORD __unusedAlignment;
      DWORD64 ExceptionInformation[15];
    } EXCEPTION_RECORD64,*PEXCEPTION_RECORD64;

    typedef struct _EXCEPTION_POINTERS {
      PEXCEPTION_RECORD ExceptionRecord;
      PCONTEXT ContextRecord;
    } EXCEPTION_POINTERS,*PEXCEPTION_POINTERS;



    typedef int  EXCEPTION_ROUTINE (struct _EXCEPTION_RECORD *ExceptionRecord, PVOID EstablisherFrame, struct _CONTEXT *ContextRecord, PVOID DispatcherContext);


    typedef EXCEPTION_ROUTINE *PEXCEPTION_ROUTINE;






  typedef struct _UNWIND_HISTORY_TABLE_ENTRY {
    ULONG64 ImageBase;
    PRUNTIME_FUNCTION FunctionEntry;
  } UNWIND_HISTORY_TABLE_ENTRY, *PUNWIND_HISTORY_TABLE_ENTRY;





  typedef struct _UNWIND_HISTORY_TABLE {
    ULONG Count;
    UCHAR Search;
    ULONG64 LowAddress;
    ULONG64 HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[12];
  } UNWIND_HISTORY_TABLE, *PUNWIND_HISTORY_TABLE;



  struct _DISPATCHER_CONTEXT;
  typedef struct _DISPATCHER_CONTEXT DISPATCHER_CONTEXT;
  typedef struct _DISPATCHER_CONTEXT *PDISPATCHER_CONTEXT;

  struct _DISPATCHER_CONTEXT {
    ULONG64 ControlPc;
    ULONG64 ImageBase;
    PRUNTIME_FUNCTION FunctionEntry;
    ULONG64 EstablisherFrame;
    ULONG64 TargetIp;
    PCONTEXT ContextRecord;
    PEXCEPTION_ROUTINE LanguageHandler;
    PVOID HandlerData;

    PUNWIND_HISTORY_TABLE HistoryTable;
    ULONG ScopeIndex;
    ULONG Fill0;
  };



  typedef struct _KNONVOLATILE_CONTEXT_POINTERS
  {
    PM128A FloatingContext[16];
    PULONG64 IntegerContext[16];
  } KNONVOLATILE_CONTEXT_POINTERS, *PKNONVOLATILE_CONTEXT_POINTERS;


    typedef PVOID PACCESS_TOKEN;
    typedef PVOID PSECURITY_DESCRIPTOR;
    typedef PVOID PSID;

    typedef DWORD ACCESS_MASK;
    typedef ACCESS_MASK *PACCESS_MASK;
# 2059 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _GENERIC_MAPPING {
      ACCESS_MASK GenericRead;
      ACCESS_MASK GenericWrite;
      ACCESS_MASK GenericExecute;
      ACCESS_MASK GenericAll;
    } GENERIC_MAPPING;
    typedef GENERIC_MAPPING *PGENERIC_MAPPING;

# 1 "c:/program files/tcc/include/winapi/pshpack4.h" 1






#pragma pack(push,4)
# 2068 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _LUID_AND_ATTRIBUTES {
      LUID Luid;
      DWORD Attributes;
    } LUID_AND_ATTRIBUTES,*PLUID_AND_ATTRIBUTES;
    typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[1];
    typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 2077 "c:/program files/tcc/include/winapi/winnt.h" 2



    typedef struct _SID_IDENTIFIER_AUTHORITY {
      BYTE Value[6];
    } SID_IDENTIFIER_AUTHORITY,*PSID_IDENTIFIER_AUTHORITY;




    typedef struct _SID {
      BYTE Revision;
      BYTE SubAuthorityCount;
      SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
      DWORD SubAuthority[1];
    } SID,*PISID;
# 2101 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _SID_NAME_USE {
      SidTypeUser = 1,SidTypeGroup,SidTypeDomain,SidTypeAlias,SidTypeWellKnownGroup,SidTypeDeletedAccount,SidTypeInvalid,SidTypeUnknown,SidTypeComputer
    } SID_NAME_USE,*PSID_NAME_USE;

    typedef struct _SID_AND_ATTRIBUTES {
      PSID Sid;
      DWORD Attributes;
    } SID_AND_ATTRIBUTES,*PSID_AND_ATTRIBUTES;

    typedef SID_AND_ATTRIBUTES SID_AND_ATTRIBUTES_ARRAY[1];
    typedef SID_AND_ATTRIBUTES_ARRAY *PSID_AND_ATTRIBUTES_ARRAY;
# 2239 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum {
      WinNullSid = 0,WinWorldSid = 1,WinLocalSid = 2,WinCreatorOwnerSid = 3,WinCreatorGroupSid = 4,WinCreatorOwnerServerSid = 5,WinCreatorGroupServerSid = 6,WinNtAuthoritySid = 7,WinDialupSid = 8,WinNetworkSid = 9,WinBatchSid = 10,WinInteractiveSid = 11,WinServiceSid = 12,WinAnonymousSid = 13,WinProxySid = 14,WinEnterpriseControllersSid = 15,WinSelfSid = 16,WinAuthenticatedUserSid = 17,WinRestrictedCodeSid = 18,WinTerminalServerSid = 19,WinRemoteLogonIdSid = 20,WinLogonIdsSid = 21,WinLocalSystemSid = 22,WinLocalServiceSid = 23,WinNetworkServiceSid = 24,WinBuiltinDomainSid = 25,WinBuiltinAdministratorsSid = 26,WinBuiltinUsersSid = 27,WinBuiltinGuestsSid = 28,WinBuiltinPowerUsersSid = 29,WinBuiltinAccountOperatorsSid = 30,WinBuiltinSystemOperatorsSid = 31,WinBuiltinPrintOperatorsSid = 32,WinBuiltinBackupOperatorsSid = 33,WinBuiltinReplicatorSid = 34,WinBuiltinPreWindows2000CompatibleAccessSid = 35,WinBuiltinRemoteDesktopUsersSid = 36,WinBuiltinNetworkConfigurationOperatorsSid = 37,WinAccountAdministratorSid = 38,WinAccountGuestSid = 39,WinAccountKrbtgtSid = 40,WinAccountDomainAdminsSid = 41,WinAccountDomainUsersSid = 42,WinAccountDomainGuestsSid = 43,WinAccountComputersSid = 44,WinAccountControllersSid = 45,WinAccountCertAdminsSid = 46,WinAccountSchemaAdminsSid = 47,WinAccountEnterpriseAdminsSid = 48,WinAccountPolicyAdminsSid = 49,WinAccountRasAndIasServersSid = 50,WinNTLMAuthenticationSid = 51,WinDigestAuthenticationSid = 52,WinSChannelAuthenticationSid = 53,WinThisOrganizationSid = 54,WinOtherOrganizationSid = 55,WinBuiltinIncomingForestTrustBuildersSid = 56,WinBuiltinPerfMonitoringUsersSid = 57,WinBuiltinPerfLoggingUsersSid = 58,WinBuiltinAuthorizationAccessSid = 59,WinBuiltinTerminalServerLicenseServersSid = 60,WinBuiltinDCOMUsersSid = 61
    } WELL_KNOWN_SID_TYPE;
# 2269 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _ACL {
      BYTE AclRevision;
      BYTE Sbz1;
      WORD AclSize;
      WORD AceCount;
      WORD Sbz2;
    } ACL;
    typedef ACL *PACL;

    typedef struct _ACE_HEADER {
      BYTE AceType;
      BYTE AceFlags;
      WORD AceSize;
    } ACE_HEADER;
    typedef ACE_HEADER *PACE_HEADER;
# 2327 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _ACCESS_ALLOWED_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;
    } ACCESS_ALLOWED_ACE;

    typedef ACCESS_ALLOWED_ACE *PACCESS_ALLOWED_ACE;

    typedef struct _ACCESS_DENIED_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;
    } ACCESS_DENIED_ACE;
    typedef ACCESS_DENIED_ACE *PACCESS_DENIED_ACE;

    typedef struct _SYSTEM_AUDIT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;
    } SYSTEM_AUDIT_ACE;
    typedef SYSTEM_AUDIT_ACE *PSYSTEM_AUDIT_ACE;

    typedef struct _SYSTEM_ALARM_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;
    } SYSTEM_ALARM_ACE;
    typedef SYSTEM_ALARM_ACE *PSYSTEM_ALARM_ACE;

    typedef struct _ACCESS_ALLOWED_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;
    } ACCESS_ALLOWED_OBJECT_ACE,*PACCESS_ALLOWED_OBJECT_ACE;

    typedef struct _ACCESS_DENIED_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;
    } ACCESS_DENIED_OBJECT_ACE,*PACCESS_DENIED_OBJECT_ACE;

    typedef struct _SYSTEM_AUDIT_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;
    } SYSTEM_AUDIT_OBJECT_ACE,*PSYSTEM_AUDIT_OBJECT_ACE;

    typedef struct _SYSTEM_ALARM_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;
    } SYSTEM_ALARM_OBJECT_ACE,*PSYSTEM_ALARM_OBJECT_ACE;

    typedef struct _ACCESS_ALLOWED_CALLBACK_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;

    } ACCESS_ALLOWED_CALLBACK_ACE,*PACCESS_ALLOWED_CALLBACK_ACE;

    typedef struct _ACCESS_DENIED_CALLBACK_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;

    } ACCESS_DENIED_CALLBACK_ACE,*PACCESS_DENIED_CALLBACK_ACE;

    typedef struct _SYSTEM_AUDIT_CALLBACK_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;

    } SYSTEM_AUDIT_CALLBACK_ACE,*PSYSTEM_AUDIT_CALLBACK_ACE;

    typedef struct _SYSTEM_ALARM_CALLBACK_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD SidStart;

    } SYSTEM_ALARM_CALLBACK_ACE,*PSYSTEM_ALARM_CALLBACK_ACE;

    typedef struct _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;

    } ACCESS_ALLOWED_CALLBACK_OBJECT_ACE,*PACCESS_ALLOWED_CALLBACK_OBJECT_ACE;

    typedef struct _ACCESS_DENIED_CALLBACK_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;

    } ACCESS_DENIED_CALLBACK_OBJECT_ACE,*PACCESS_DENIED_CALLBACK_OBJECT_ACE;

    typedef struct _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;

    } SYSTEM_AUDIT_CALLBACK_OBJECT_ACE,*PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE;

    typedef struct _SYSTEM_ALARM_CALLBACK_OBJECT_ACE {
      ACE_HEADER Header;
      ACCESS_MASK Mask;
      DWORD Flags;
      GUID ObjectType;
      GUID InheritedObjectType;
      DWORD SidStart;

    } SYSTEM_ALARM_CALLBACK_OBJECT_ACE,*PSYSTEM_ALARM_CALLBACK_OBJECT_ACE;




    typedef enum _ACL_INFORMATION_CLASS {
      AclRevisionInformation = 1,AclSizeInformation
    } ACL_INFORMATION_CLASS;

    typedef struct _ACL_REVISION_INFORMATION {
      DWORD AclRevision;
    } ACL_REVISION_INFORMATION;
    typedef ACL_REVISION_INFORMATION *PACL_REVISION_INFORMATION;

    typedef struct _ACL_SIZE_INFORMATION {
      DWORD AceCount;
      DWORD AclBytesInUse;
      DWORD AclBytesFree;
    } ACL_SIZE_INFORMATION;
    typedef ACL_SIZE_INFORMATION *PACL_SIZE_INFORMATION;






    typedef WORD SECURITY_DESCRIPTOR_CONTROL,*PSECURITY_DESCRIPTOR_CONTROL;
# 2501 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _SECURITY_DESCRIPTOR_RELATIVE {
      BYTE Revision;
      BYTE Sbz1;
      SECURITY_DESCRIPTOR_CONTROL Control;
      DWORD Owner;
      DWORD Group;
      DWORD Sacl;
      DWORD Dacl;
    } SECURITY_DESCRIPTOR_RELATIVE,*PISECURITY_DESCRIPTOR_RELATIVE;

    typedef struct _SECURITY_DESCRIPTOR {
      BYTE Revision;
      BYTE Sbz1;
      SECURITY_DESCRIPTOR_CONTROL Control;
      PSID Owner;
      PSID Group;
      PACL Sacl;
      PACL Dacl;

    } SECURITY_DESCRIPTOR,*PISECURITY_DESCRIPTOR;

    typedef struct _OBJECT_TYPE_LIST {
      WORD Level;
      WORD Sbz;
      GUID *ObjectType;
    } OBJECT_TYPE_LIST,*POBJECT_TYPE_LIST;







    typedef enum _AUDIT_EVENT_TYPE {
      AuditEventObjectAccess,AuditEventDirectoryServiceAccess
    } AUDIT_EVENT_TYPE,*PAUDIT_EVENT_TYPE;
# 2552 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _PRIVILEGE_SET {
      DWORD PrivilegeCount;
      DWORD Control;
      LUID_AND_ATTRIBUTES Privilege[1];
    } PRIVILEGE_SET,*PPRIVILEGE_SET;
# 2589 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _SECURITY_IMPERSONATION_LEVEL {
      SecurityAnonymous,SecurityIdentification,SecurityImpersonation,SecurityDelegation
    } SECURITY_IMPERSONATION_LEVEL,*PSECURITY_IMPERSONATION_LEVEL;
# 2616 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _TOKEN_TYPE {
      TokenPrimary = 1,TokenImpersonation
    } TOKEN_TYPE;
    typedef TOKEN_TYPE *PTOKEN_TYPE;

    typedef enum _TOKEN_INFORMATION_CLASS {
      TokenUser = 1,TokenGroups,TokenPrivileges,TokenOwner,TokenPrimaryGroup,TokenDefaultDacl,TokenSource,TokenType,TokenImpersonationLevel,
      TokenStatistics,TokenRestrictedSids,TokenSessionId,TokenGroupsAndPrivileges,TokenSessionReference,TokenSandBoxInert,TokenAuditPolicy,
      TokenOrigin,MaxTokenInfoClass
    } TOKEN_INFORMATION_CLASS,*PTOKEN_INFORMATION_CLASS;

    typedef struct _TOKEN_USER {
      SID_AND_ATTRIBUTES User;
    } TOKEN_USER,*PTOKEN_USER;

    typedef struct _TOKEN_GROUPS {
      DWORD GroupCount;
      SID_AND_ATTRIBUTES Groups[1];
    } TOKEN_GROUPS,*PTOKEN_GROUPS;

    typedef struct _TOKEN_PRIVILEGES {
      DWORD PrivilegeCount;
      LUID_AND_ATTRIBUTES Privileges[1];
    } TOKEN_PRIVILEGES,*PTOKEN_PRIVILEGES;

    typedef struct _TOKEN_OWNER {
      PSID Owner;
    } TOKEN_OWNER,*PTOKEN_OWNER;

    typedef struct _TOKEN_PRIMARY_GROUP {
      PSID PrimaryGroup;
    } TOKEN_PRIMARY_GROUP,*PTOKEN_PRIMARY_GROUP;

    typedef struct _TOKEN_DEFAULT_DACL {
      PACL DefaultDacl;
    } TOKEN_DEFAULT_DACL,*PTOKEN_DEFAULT_DACL;

    typedef struct _TOKEN_GROUPS_AND_PRIVILEGES {
      DWORD SidCount;
      DWORD SidLength;
      PSID_AND_ATTRIBUTES Sids;
      DWORD RestrictedSidCount;
      DWORD RestrictedSidLength;
      PSID_AND_ATTRIBUTES RestrictedSids;
      DWORD PrivilegeCount;
      DWORD PrivilegeLength;
      PLUID_AND_ATTRIBUTES Privileges;
      LUID AuthenticationId;
    } TOKEN_GROUPS_AND_PRIVILEGES,*PTOKEN_GROUPS_AND_PRIVILEGES;
# 2674 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _TOKEN_AUDIT_POLICY_ELEMENT {
      DWORD Category;
      DWORD PolicyMask;
    } TOKEN_AUDIT_POLICY_ELEMENT,*PTOKEN_AUDIT_POLICY_ELEMENT;

    typedef struct _TOKEN_AUDIT_POLICY {
      DWORD PolicyCount;
      TOKEN_AUDIT_POLICY_ELEMENT Policy[1];
    } TOKEN_AUDIT_POLICY,*PTOKEN_AUDIT_POLICY;






    typedef struct _TOKEN_SOURCE {
      CHAR SourceName[8];
      LUID SourceIdentifier;
    } TOKEN_SOURCE,*PTOKEN_SOURCE;

    typedef struct _TOKEN_STATISTICS {
      LUID TokenId;
      LUID AuthenticationId;
      LARGE_INTEGER ExpirationTime;
      TOKEN_TYPE TokenType;
      SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
      DWORD DynamicCharged;
      DWORD DynamicAvailable;
      DWORD GroupCount;
      DWORD PrivilegeCount;
      LUID ModifiedId;
    } TOKEN_STATISTICS,*PTOKEN_STATISTICS;

    typedef struct _TOKEN_CONTROL {
      LUID TokenId;
      LUID AuthenticationId;
      LUID ModifiedId;
      TOKEN_SOURCE TokenSource;
    } TOKEN_CONTROL,*PTOKEN_CONTROL;

    typedef struct _TOKEN_ORIGIN {
      LUID OriginatingLogonSession;
    } TOKEN_ORIGIN,*PTOKEN_ORIGIN;




    typedef BOOLEAN SECURITY_CONTEXT_TRACKING_MODE,*PSECURITY_CONTEXT_TRACKING_MODE;

    typedef struct _SECURITY_QUALITY_OF_SERVICE {
      DWORD Length;
      SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
      SECURITY_CONTEXT_TRACKING_MODE ContextTrackingMode;
      BOOLEAN EffectiveOnly;
    } SECURITY_QUALITY_OF_SERVICE,*PSECURITY_QUALITY_OF_SERVICE;

    typedef struct _SE_IMPERSONATION_STATE {
      PACCESS_TOKEN Token;
      BOOLEAN CopyOnOpen;
      BOOLEAN EffectiveOnly;
      SECURITY_IMPERSONATION_LEVEL Level;
    } SE_IMPERSONATION_STATE,*PSE_IMPERSONATION_STATE;




    typedef DWORD SECURITY_INFORMATION,*PSECURITY_INFORMATION;
# 2791 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _JOB_SET_ARRAY {
      HANDLE JobHandle;
      DWORD MemberLevel;
      DWORD Flags;
    } JOB_SET_ARRAY,*PJOB_SET_ARRAY;






    typedef struct _NT_TIB {
      struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
      PVOID StackBase;
      PVOID StackLimit;
      PVOID SubSystemTib;
      union {
	PVOID FiberData;
	DWORD Version;
      };
      PVOID ArbitraryUserPointer;
      struct _NT_TIB *Self;
    } NT_TIB;
    typedef NT_TIB *PNT_TIB;


    typedef struct _NT_TIB32 {
      DWORD ExceptionList;
      DWORD StackBase;
      DWORD StackLimit;
      DWORD SubSystemTib;
      union {
	DWORD FiberData;
	DWORD Version;
      };
      DWORD ArbitraryUserPointer;
      DWORD Self;
    } NT_TIB32,*PNT_TIB32;

    typedef struct _NT_TIB64 {
      DWORD64 ExceptionList;
      DWORD64 StackBase;
      DWORD64 StackLimit;
      DWORD64 SubSystemTib;
      union {
	DWORD64 FiberData;
	DWORD Version;
      };
      DWORD64 ArbitraryUserPointer;
      DWORD64 Self;
    } NT_TIB64,*PNT_TIB64;
# 2852 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _QUOTA_LIMITS {
      SIZE_T PagedPoolLimit;
      SIZE_T NonPagedPoolLimit;
      SIZE_T MinimumWorkingSetSize;
      SIZE_T MaximumWorkingSetSize;
      SIZE_T PagefileLimit;
      LARGE_INTEGER TimeLimit;
    } QUOTA_LIMITS,*PQUOTA_LIMITS;






    typedef struct _QUOTA_LIMITS_EX {
      SIZE_T PagedPoolLimit;
      SIZE_T NonPagedPoolLimit;
      SIZE_T MinimumWorkingSetSize;
      SIZE_T MaximumWorkingSetSize;
      SIZE_T PagefileLimit;
      LARGE_INTEGER TimeLimit;
      SIZE_T Reserved1;
      SIZE_T Reserved2;
      SIZE_T Reserved3;
      SIZE_T Reserved4;
      DWORD Flags;
      DWORD Reserved5;
    } QUOTA_LIMITS_EX,*PQUOTA_LIMITS_EX;

    typedef struct _IO_COUNTERS {
      ULONGLONG ReadOperationCount;
      ULONGLONG WriteOperationCount;
      ULONGLONG OtherOperationCount;
      ULONGLONG ReadTransferCount;
      ULONGLONG WriteTransferCount;
      ULONGLONG OtherTransferCount;
    } IO_COUNTERS;
    typedef IO_COUNTERS *PIO_COUNTERS;

    typedef struct _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION {
      LARGE_INTEGER TotalUserTime;
      LARGE_INTEGER TotalKernelTime;
      LARGE_INTEGER ThisPeriodTotalUserTime;
      LARGE_INTEGER ThisPeriodTotalKernelTime;
      DWORD TotalPageFaultCount;
      DWORD TotalProcesses;
      DWORD ActiveProcesses;
      DWORD TotalTerminatedProcesses;
    } JOBOBJECT_BASIC_ACCOUNTING_INFORMATION,*PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION;

    typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION {
      LARGE_INTEGER PerProcessUserTimeLimit;
      LARGE_INTEGER PerJobUserTimeLimit;
      DWORD LimitFlags;
      SIZE_T MinimumWorkingSetSize;
      SIZE_T MaximumWorkingSetSize;
      DWORD ActiveProcessLimit;
      ULONG_PTR Affinity;
      DWORD PriorityClass;
      DWORD SchedulingClass;
    } JOBOBJECT_BASIC_LIMIT_INFORMATION,*PJOBOBJECT_BASIC_LIMIT_INFORMATION;

    typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION {
      JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation;
      IO_COUNTERS IoInfo;
      SIZE_T ProcessMemoryLimit;
      SIZE_T JobMemoryLimit;
      SIZE_T PeakProcessMemoryUsed;
      SIZE_T PeakJobMemoryUsed;
    } JOBOBJECT_EXTENDED_LIMIT_INFORMATION,*PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;

    typedef struct _JOBOBJECT_BASIC_PROCESS_ID_LIST {
      DWORD NumberOfAssignedProcesses;
      DWORD NumberOfProcessIdsInList;
      ULONG_PTR ProcessIdList[1];
    } JOBOBJECT_BASIC_PROCESS_ID_LIST,*PJOBOBJECT_BASIC_PROCESS_ID_LIST;

    typedef struct _JOBOBJECT_BASIC_UI_RESTRICTIONS {
      DWORD UIRestrictionsClass;
    } JOBOBJECT_BASIC_UI_RESTRICTIONS,*PJOBOBJECT_BASIC_UI_RESTRICTIONS;

    typedef struct _JOBOBJECT_SECURITY_LIMIT_INFORMATION {
      DWORD SecurityLimitFlags;
      HANDLE JobToken;
      PTOKEN_GROUPS SidsToDisable;
      PTOKEN_PRIVILEGES PrivilegesToDelete;
      PTOKEN_GROUPS RestrictedSids;
    } JOBOBJECT_SECURITY_LIMIT_INFORMATION,*PJOBOBJECT_SECURITY_LIMIT_INFORMATION;

    typedef struct _JOBOBJECT_END_OF_JOB_TIME_INFORMATION {
      DWORD EndOfJobTimeAction;
    } JOBOBJECT_END_OF_JOB_TIME_INFORMATION,*PJOBOBJECT_END_OF_JOB_TIME_INFORMATION;

    typedef struct _JOBOBJECT_ASSOCIATE_COMPLETION_PORT {
      PVOID CompletionKey;
      HANDLE CompletionPort;
    } JOBOBJECT_ASSOCIATE_COMPLETION_PORT,*PJOBOBJECT_ASSOCIATE_COMPLETION_PORT;

    typedef struct _JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION {
      JOBOBJECT_BASIC_ACCOUNTING_INFORMATION BasicInfo;
      IO_COUNTERS IoInfo;
    } JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION,*PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;

    typedef struct _JOBOBJECT_JOBSET_INFORMATION {
      DWORD MemberLevel;
    } JOBOBJECT_JOBSET_INFORMATION,*PJOBOBJECT_JOBSET_INFORMATION;
# 3022 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _JOBOBJECTINFOCLASS {
      JobObjectBasicAccountingInformation = 1,JobObjectBasicLimitInformation,JobObjectBasicProcessIdList,JobObjectBasicUIRestrictions,
      JobObjectSecurityLimitInformation,JobObjectEndOfJobTimeInformation,JobObjectAssociateCompletionPortInformation,
      JobObjectBasicAndIoAccountingInformation,JobObjectExtendedLimitInformation,JobObjectJobSetInformation,MaxJobObjectInfoClass
    } JOBOBJECTINFOCLASS;
# 3046 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP {
      RelationProcessorCore,RelationNumaNode,RelationCache
    } LOGICAL_PROCESSOR_RELATIONSHIP;



    typedef enum _PROCESSOR_CACHE_TYPE {
      CacheUnified,CacheInstruction,CacheData,CacheTrace
    } PROCESSOR_CACHE_TYPE;



    typedef struct _CACHE_DESCRIPTOR {
      BYTE Level;
      BYTE Associativity;
      WORD LineSize;
      DWORD Size;
      PROCESSOR_CACHE_TYPE Type;
    } CACHE_DESCRIPTOR,*PCACHE_DESCRIPTOR;

    typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION {
      ULONG_PTR ProcessorMask;
      LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
      union {
	struct {
	  BYTE Flags;
	} ProcessorCore;
	struct {
	  DWORD NodeNumber;
	} NumaNode;
	CACHE_DESCRIPTOR Cache;
	ULONGLONG Reserved[2];
      };
    } SYSTEM_LOGICAL_PROCESSOR_INFORMATION,*PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;
# 3133 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _MEMORY_BASIC_INFORMATION {
      PVOID BaseAddress;
      PVOID AllocationBase;
      DWORD AllocationProtect;
      SIZE_T RegionSize;
      DWORD State;
      DWORD Protect;
      DWORD Type;
    } MEMORY_BASIC_INFORMATION,*PMEMORY_BASIC_INFORMATION;

    typedef struct _MEMORY_BASIC_INFORMATION32 {
      DWORD BaseAddress;
      DWORD AllocationBase;
      DWORD AllocationProtect;
      DWORD RegionSize;
      DWORD State;
      DWORD Protect;
      DWORD Type;
    } MEMORY_BASIC_INFORMATION32,*PMEMORY_BASIC_INFORMATION32;

    typedef __attribute__((aligned(16))) struct _MEMORY_BASIC_INFORMATION64 {
      ULONGLONG BaseAddress;
      ULONGLONG AllocationBase;
      DWORD AllocationProtect;
      DWORD __alignment1;
      ULONGLONG RegionSize;
      DWORD State;
      DWORD Protect;
      DWORD Type;
      DWORD __alignment2;
    } MEMORY_BASIC_INFORMATION64,*PMEMORY_BASIC_INFORMATION64;
# 3281 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _FILE_NOTIFY_INFORMATION {
      DWORD NextEntryOffset;
      DWORD Action;
      DWORD FileNameLength;
      WCHAR FileName[1];
    } FILE_NOTIFY_INFORMATION,*PFILE_NOTIFY_INFORMATION;

    typedef union _FILE_SEGMENT_ELEMENT {
      PVOID64 Buffer;
      ULONGLONG Alignment;
    }FILE_SEGMENT_ELEMENT,*PFILE_SEGMENT_ELEMENT;

    typedef struct _REPARSE_GUID_DATA_BUFFER {
      DWORD ReparseTag;
      WORD ReparseDataLength;
      WORD Reserved;
      GUID ReparseGuid;
      struct {
	BYTE DataBuffer[1];
      } GenericReparseBuffer;
    } REPARSE_GUID_DATA_BUFFER,*PREPARSE_GUID_DATA_BUFFER;
# 3325 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _SYSTEM_POWER_STATE {
      PowerSystemUnspecified = 0,PowerSystemWorking = 1,PowerSystemSleeping1 = 2,PowerSystemSleeping2 = 3,PowerSystemSleeping3 = 4,PowerSystemHibernate = 5,PowerSystemShutdown = 6,PowerSystemMaximum = 7
    } SYSTEM_POWER_STATE,*PSYSTEM_POWER_STATE;



    typedef enum {
      PowerActionNone = 0,PowerActionReserved,PowerActionSleep,PowerActionHibernate,PowerActionShutdown,PowerActionShutdownReset,PowerActionShutdownOff,PowerActionWarmEject
    } POWER_ACTION,*PPOWER_ACTION;

    typedef enum _DEVICE_POWER_STATE {
      PowerDeviceUnspecified = 0,PowerDeviceD0,PowerDeviceD1,PowerDeviceD2,PowerDeviceD3,PowerDeviceMaximum
    } DEVICE_POWER_STATE,*PDEVICE_POWER_STATE;






    typedef DWORD EXECUTION_STATE;

    typedef enum {
      LT_DONT_CARE,LT_LOWEST_LATENCY
    } LATENCY_TIME;
# 3360 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct CM_Power_Data_s {
      DWORD PD_Size;
      DEVICE_POWER_STATE PD_MostRecentPowerState;
      DWORD PD_Capabilities;
      DWORD PD_D1Latency;
      DWORD PD_D2Latency;
      DWORD PD_D3Latency;
      DEVICE_POWER_STATE PD_PowerStateMapping[7];
      SYSTEM_POWER_STATE PD_DeepestSystemWake;
    } CM_POWER_DATA,*PCM_POWER_DATA;

    typedef enum {
      SystemPowerPolicyAc,SystemPowerPolicyDc,VerifySystemPolicyAc,VerifySystemPolicyDc,SystemPowerCapabilities,SystemBatteryState,SystemPowerStateHandler,ProcessorStateHandler,SystemPowerPolicyCurrent,AdministratorPowerPolicy,SystemReserveHiberFile,ProcessorInformation,SystemPowerInformation,ProcessorStateHandler2,LastWakeTime,LastSleepTime,SystemExecutionState,SystemPowerStateNotifyHandler,ProcessorPowerPolicyAc,ProcessorPowerPolicyDc,VerifyProcessorPowerPolicyAc,VerifyProcessorPowerPolicyDc,ProcessorPowerPolicyCurrent,SystemPowerStateLogging,SystemPowerLoggingEntry
    } POWER_INFORMATION_LEVEL;

    typedef struct {
      DWORD Granularity;
      DWORD Capacity;
    } BATTERY_REPORTING_SCALE,*PBATTERY_REPORTING_SCALE;

    typedef struct {
      POWER_ACTION Action;
      DWORD Flags;
      DWORD EventCode;
    } POWER_ACTION_POLICY,*PPOWER_ACTION_POLICY;
# 3401 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct {
      BOOLEAN Enable;
      BYTE Spare[3];
      DWORD BatteryLevel;
      POWER_ACTION_POLICY PowerPolicy;
      SYSTEM_POWER_STATE MinSystemState;
    } SYSTEM_POWER_LEVEL,*PSYSTEM_POWER_LEVEL;
# 3419 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _SYSTEM_POWER_POLICY {
      DWORD Revision;
      POWER_ACTION_POLICY PowerButton;
      POWER_ACTION_POLICY SleepButton;
      POWER_ACTION_POLICY LidClose;
      SYSTEM_POWER_STATE LidOpenWake;
      DWORD Reserved;
      POWER_ACTION_POLICY Idle;
      DWORD IdleTimeout;
      BYTE IdleSensitivity;
      BYTE DynamicThrottle;
      BYTE Spare2[2];
      SYSTEM_POWER_STATE MinSleep;
      SYSTEM_POWER_STATE MaxSleep;
      SYSTEM_POWER_STATE ReducedLatencySleep;
      DWORD WinLogonFlags;
      DWORD Spare3;
      DWORD DozeS4Timeout;
      DWORD BroadcastCapacityResolution;
      SYSTEM_POWER_LEVEL DischargePolicy[4];
      DWORD VideoTimeout;
      BOOLEAN VideoDimDisplay;
      DWORD VideoReserved[3];
      DWORD SpindownTimeout;
      BOOLEAN OptimizeForPower;
      BYTE FanThrottleTolerance;
      BYTE ForcedThrottle;
      BYTE MinThrottle;
      POWER_ACTION_POLICY OverThrottled;
    } SYSTEM_POWER_POLICY,*PSYSTEM_POWER_POLICY;

    typedef struct _PROCESSOR_POWER_POLICY_INFO {
      DWORD TimeCheck;
      DWORD DemoteLimit;
      DWORD PromoteLimit;
      BYTE DemotePercent;
      BYTE PromotePercent;
      BYTE Spare[2];
      DWORD AllowDemotion:1;
      DWORD AllowPromotion:1;
      DWORD Reserved:30;
    } PROCESSOR_POWER_POLICY_INFO,*PPROCESSOR_POWER_POLICY_INFO;

    typedef struct _PROCESSOR_POWER_POLICY {
      DWORD Revision;
      BYTE DynamicThrottle;
      BYTE Spare[3];
      DWORD DisableCStates:1;
      DWORD Reserved:31;
      DWORD PolicyCount;
      PROCESSOR_POWER_POLICY_INFO Policy[3];
    } PROCESSOR_POWER_POLICY,*PPROCESSOR_POWER_POLICY;

    typedef struct _ADMINISTRATOR_POWER_POLICY {
      SYSTEM_POWER_STATE MinSleep;
      SYSTEM_POWER_STATE MaxSleep;
      DWORD MinVideoTimeout;
      DWORD MaxVideoTimeout;
      DWORD MinSpindownTimeout;
      DWORD MaxSpindownTimeout;
    } ADMINISTRATOR_POWER_POLICY,*PADMINISTRATOR_POWER_POLICY;

    typedef struct {
      BOOLEAN PowerButtonPresent;
      BOOLEAN SleepButtonPresent;
      BOOLEAN LidPresent;
      BOOLEAN SystemS1;
      BOOLEAN SystemS2;
      BOOLEAN SystemS3;
      BOOLEAN SystemS4;
      BOOLEAN SystemS5;
      BOOLEAN HiberFilePresent;
      BOOLEAN FullWake;
      BOOLEAN VideoDimPresent;
      BOOLEAN ApmPresent;
      BOOLEAN UpsPresent;
      BOOLEAN ThermalControl;
      BOOLEAN ProcessorThrottle;
      BYTE ProcessorMinThrottle;
      BYTE ProcessorMaxThrottle;
      BYTE spare2[4];
      BOOLEAN DiskSpinDown;
      BYTE spare3[8];
      BOOLEAN SystemBatteriesPresent;
      BOOLEAN BatteriesAreShortTerm;
      BATTERY_REPORTING_SCALE BatteryScale[3];
      SYSTEM_POWER_STATE AcOnLineWake;
      SYSTEM_POWER_STATE SoftLidWake;
      SYSTEM_POWER_STATE RtcWake;
      SYSTEM_POWER_STATE MinDeviceWakeState;
      SYSTEM_POWER_STATE DefaultLowLatencyWake;
    } SYSTEM_POWER_CAPABILITIES,*PSYSTEM_POWER_CAPABILITIES;

    typedef struct {
      BOOLEAN AcOnLine;
      BOOLEAN BatteryPresent;
      BOOLEAN Charging;
      BOOLEAN Discharging;
      BOOLEAN Spare1[4];
      DWORD MaxCapacity;
      DWORD RemainingCapacity;
      DWORD Rate;
      DWORD EstimatedTime;
      DWORD DefaultAlert1;
      DWORD DefaultAlert2;
    } SYSTEM_BATTERY_STATE,*PSYSTEM_BATTERY_STATE;

# 1 "c:/program files/tcc/include/winapi/pshpack4.h" 1






#pragma pack(push,4)
# 3527 "c:/program files/tcc/include/winapi/winnt.h" 2







# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 3535 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_DOS_HEADER {
      WORD e_magic;
      WORD e_cblp;
      WORD e_cp;
      WORD e_crlc;
      WORD e_cparhdr;
      WORD e_minalloc;
      WORD e_maxalloc;
      WORD e_ss;
      WORD e_sp;
      WORD e_csum;
      WORD e_ip;
      WORD e_cs;
      WORD e_lfarlc;
      WORD e_ovno;
      WORD e_res[4];
      WORD e_oemid;
      WORD e_oeminfo;
      WORD e_res2[10];
      LONG e_lfanew;
    } IMAGE_DOS_HEADER,*PIMAGE_DOS_HEADER;

    typedef struct _IMAGE_OS2_HEADER {
      WORD ne_magic;
      CHAR ne_ver;
      CHAR ne_rev;
      WORD ne_enttab;
      WORD ne_cbenttab;
      LONG ne_crc;
      WORD ne_flags;
      WORD ne_autodata;
      WORD ne_heap;
      WORD ne_stack;
      LONG ne_csip;
      LONG ne_sssp;
      WORD ne_cseg;
      WORD ne_cmod;
      WORD ne_cbnrestab;
      WORD ne_segtab;
      WORD ne_rsrctab;
      WORD ne_restab;
      WORD ne_modtab;
      WORD ne_imptab;
      LONG ne_nrestab;
      WORD ne_cmovent;
      WORD ne_align;
      WORD ne_cres;
      BYTE ne_exetyp;
      BYTE ne_flagsothers;
      WORD ne_pretthunks;
      WORD ne_psegrefbytes;
      WORD ne_swaparea;
      WORD ne_expver;
    } IMAGE_OS2_HEADER,*PIMAGE_OS2_HEADER;

    typedef struct _IMAGE_VXD_HEADER {
      WORD e32_magic;
      BYTE e32_border;
      BYTE e32_worder;
      DWORD e32_level;
      WORD e32_cpu;
      WORD e32_os;
      DWORD e32_ver;
      DWORD e32_mflags;
      DWORD e32_mpages;
      DWORD e32_startobj;
      DWORD e32_eip;
      DWORD e32_stackobj;
      DWORD e32_esp;
      DWORD e32_pagesize;
      DWORD e32_lastpagesize;
      DWORD e32_fixupsize;
      DWORD e32_fixupsum;
      DWORD e32_ldrsize;
      DWORD e32_ldrsum;
      DWORD e32_objtab;
      DWORD e32_objcnt;
      DWORD e32_objmap;
      DWORD e32_itermap;
      DWORD e32_rsrctab;
      DWORD e32_rsrccnt;
      DWORD e32_restab;
      DWORD e32_enttab;
      DWORD e32_dirtab;
      DWORD e32_dircnt;
      DWORD e32_fpagetab;
      DWORD e32_frectab;
      DWORD e32_impmod;
      DWORD e32_impmodcnt;
      DWORD e32_impproc;
      DWORD e32_pagesum;
      DWORD e32_datapage;
      DWORD e32_preload;
      DWORD e32_nrestab;
      DWORD e32_cbnrestab;
      DWORD e32_nressum;
      DWORD e32_autodata;
      DWORD e32_debuginfo;
      DWORD e32_debuglen;
      DWORD e32_instpreload;
      DWORD e32_instdemand;
      DWORD e32_heapsize;
      BYTE e32_res3[12];
      DWORD e32_winresoff;
      DWORD e32_winreslen;
      WORD e32_devid;
      WORD e32_ddkver;
    } IMAGE_VXD_HEADER,*PIMAGE_VXD_HEADER;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 3646 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_FILE_HEADER {
      WORD Machine;
      WORD NumberOfSections;
      DWORD TimeDateStamp;
      DWORD PointerToSymbolTable;
      DWORD NumberOfSymbols;
      WORD SizeOfOptionalHeader;
      WORD Characteristics;
    } IMAGE_FILE_HEADER,*PIMAGE_FILE_HEADER;
# 3705 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_DATA_DIRECTORY {
      DWORD VirtualAddress;
      DWORD Size;
    } IMAGE_DATA_DIRECTORY,*PIMAGE_DATA_DIRECTORY;



    typedef struct _IMAGE_OPTIONAL_HEADER {

      WORD Magic;
      BYTE MajorLinkerVersion;
      BYTE MinorLinkerVersion;
      DWORD SizeOfCode;
      DWORD SizeOfInitializedData;
      DWORD SizeOfUninitializedData;
      DWORD AddressOfEntryPoint;
      DWORD BaseOfCode;
      DWORD BaseOfData;
      DWORD ImageBase;
      DWORD SectionAlignment;
      DWORD FileAlignment;
      WORD MajorOperatingSystemVersion;
      WORD MinorOperatingSystemVersion;
      WORD MajorImageVersion;
      WORD MinorImageVersion;
      WORD MajorSubsystemVersion;
      WORD MinorSubsystemVersion;
      DWORD Win32VersionValue;
      DWORD SizeOfImage;
      DWORD SizeOfHeaders;
      DWORD CheckSum;
      WORD Subsystem;
      WORD DllCharacteristics;
      DWORD SizeOfStackReserve;
      DWORD SizeOfStackCommit;
      DWORD SizeOfHeapReserve;
      DWORD SizeOfHeapCommit;
      DWORD LoaderFlags;
      DWORD NumberOfRvaAndSizes;
      IMAGE_DATA_DIRECTORY DataDirectory[16];
    } IMAGE_OPTIONAL_HEADER32,*PIMAGE_OPTIONAL_HEADER32;

    typedef struct _IMAGE_ROM_OPTIONAL_HEADER {
      WORD Magic;
      BYTE MajorLinkerVersion;
      BYTE MinorLinkerVersion;
      DWORD SizeOfCode;
      DWORD SizeOfInitializedData;
      DWORD SizeOfUninitializedData;
      DWORD AddressOfEntryPoint;
      DWORD BaseOfCode;
      DWORD BaseOfData;
      DWORD BaseOfBss;
      DWORD GprMask;
      DWORD CprMask[4];
      DWORD GpValue;
    } IMAGE_ROM_OPTIONAL_HEADER,*PIMAGE_ROM_OPTIONAL_HEADER;

    typedef struct _IMAGE_OPTIONAL_HEADER64 {
      WORD Magic;
      BYTE MajorLinkerVersion;
      BYTE MinorLinkerVersion;
      DWORD SizeOfCode;
      DWORD SizeOfInitializedData;
      DWORD SizeOfUninitializedData;
      DWORD AddressOfEntryPoint;
      DWORD BaseOfCode;
      ULONGLONG ImageBase;
      DWORD SectionAlignment;
      DWORD FileAlignment;
      WORD MajorOperatingSystemVersion;
      WORD MinorOperatingSystemVersion;
      WORD MajorImageVersion;
      WORD MinorImageVersion;
      WORD MajorSubsystemVersion;
      WORD MinorSubsystemVersion;
      DWORD Win32VersionValue;
      DWORD SizeOfImage;
      DWORD SizeOfHeaders;
      DWORD CheckSum;
      WORD Subsystem;
      WORD DllCharacteristics;
      ULONGLONG SizeOfStackReserve;
      ULONGLONG SizeOfStackCommit;
      ULONGLONG SizeOfHeapReserve;
      ULONGLONG SizeOfHeapCommit;
      DWORD LoaderFlags;
      DWORD NumberOfRvaAndSizes;
      IMAGE_DATA_DIRECTORY DataDirectory[16];
    } IMAGE_OPTIONAL_HEADER64,*PIMAGE_OPTIONAL_HEADER64;
# 3806 "c:/program files/tcc/include/winapi/winnt.h"
    typedef IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER;
    typedef PIMAGE_OPTIONAL_HEADER64 PIMAGE_OPTIONAL_HEADER;
# 3817 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_NT_HEADERS64 {
      DWORD Signature;
      IMAGE_FILE_HEADER FileHeader;
      IMAGE_OPTIONAL_HEADER64 OptionalHeader;
    } IMAGE_NT_HEADERS64,*PIMAGE_NT_HEADERS64;

    typedef struct _IMAGE_NT_HEADERS {
      DWORD Signature;
      IMAGE_FILE_HEADER FileHeader;
      IMAGE_OPTIONAL_HEADER32 OptionalHeader;
    } IMAGE_NT_HEADERS32,*PIMAGE_NT_HEADERS32;

    typedef struct _IMAGE_ROM_HEADERS {
      IMAGE_FILE_HEADER FileHeader;
      IMAGE_ROM_OPTIONAL_HEADER OptionalHeader;
    } IMAGE_ROM_HEADERS,*PIMAGE_ROM_HEADERS;


    typedef IMAGE_NT_HEADERS64 IMAGE_NT_HEADERS;
    typedef PIMAGE_NT_HEADERS64 PIMAGE_NT_HEADERS;
# 3881 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct ANON_OBJECT_HEADER {
      WORD Sig1;
      WORD Sig2;
      WORD Version;
      WORD Machine;
      DWORD TimeDateStamp;
      CLSID ClassID;
      DWORD SizeOfData;
    } ANON_OBJECT_HEADER;



    typedef struct _IMAGE_SECTION_HEADER {
      BYTE Name[8];
      union {
	DWORD PhysicalAddress;
	DWORD VirtualSize;
      } Misc;
      DWORD VirtualAddress;
      DWORD SizeOfRawData;
      DWORD PointerToRawData;
      DWORD PointerToRelocations;
      DWORD PointerToLinenumbers;
      WORD NumberOfRelocations;
      WORD NumberOfLinenumbers;
      DWORD Characteristics;
    } IMAGE_SECTION_HEADER,*PIMAGE_SECTION_HEADER;
# 3956 "c:/program files/tcc/include/winapi/winnt.h"
# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 3957 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_SYMBOL {
      union {
	BYTE ShortName[8];
	struct {
	  DWORD Short;
	  DWORD Long;
	} Name;
	DWORD LongName[2];
      } N;
      DWORD Value;
      SHORT SectionNumber;
      WORD Type;
      BYTE StorageClass;
      BYTE NumberOfAuxSymbols;
    } IMAGE_SYMBOL;
    typedef IMAGE_SYMBOL  *PIMAGE_SYMBOL;
# 4066 "c:/program files/tcc/include/winapi/winnt.h"
    typedef union _IMAGE_AUX_SYMBOL {
      struct {
	DWORD TagIndex;
	union {
	  struct {
	    WORD Linenumber;
	    WORD Size;
	  } LnSz;
	  DWORD TotalSize;
	} Misc;
	union {
	  struct {
	    DWORD PointerToLinenumber;
	    DWORD PointerToNextFunction;
	  } Function;
	  struct {
	    WORD Dimension[4];
	  } Array;
	} FcnAry;
	WORD TvIndex;
      } Sym;
      struct {
	BYTE Name[18];
      } File;
      struct {
	DWORD Length;
	WORD NumberOfRelocations;
	WORD NumberOfLinenumbers;
	DWORD CheckSum;
	SHORT Number;
	BYTE Selection;
      } Section;
    } IMAGE_AUX_SYMBOL;
    typedef IMAGE_AUX_SYMBOL  *PIMAGE_AUX_SYMBOL;



    typedef enum IMAGE_AUX_SYMBOL_TYPE {
      IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF = 1
    } IMAGE_AUX_SYMBOL_TYPE;

# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 4108 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct IMAGE_AUX_SYMBOL_TOKEN_DEF {
      BYTE bAuxType;
      BYTE bReserved;
      DWORD SymbolTableIndex;
      BYTE rgbReserved[12];
    } IMAGE_AUX_SYMBOL_TOKEN_DEF;

    typedef IMAGE_AUX_SYMBOL_TOKEN_DEF  *PIMAGE_AUX_SYMBOL_TOKEN_DEF;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 4119 "c:/program files/tcc/include/winapi/winnt.h" 2
# 4132 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_RELOCATION {
      union {
	DWORD VirtualAddress;
	DWORD RelocCount;
      };
      DWORD SymbolTableIndex;
      WORD Type;
    } IMAGE_RELOCATION;
    typedef IMAGE_RELOCATION  *PIMAGE_RELOCATION;
# 4454 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_LINENUMBER {
      union {
	DWORD SymbolTableIndex;
	DWORD VirtualAddress;
      } Type;
      WORD Linenumber;
    } IMAGE_LINENUMBER;
    typedef IMAGE_LINENUMBER  *PIMAGE_LINENUMBER;



# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 4466 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_BASE_RELOCATION {
      DWORD VirtualAddress;
      DWORD SizeOfBlock;

    } IMAGE_BASE_RELOCATION;
    typedef IMAGE_BASE_RELOCATION  *PIMAGE_BASE_RELOCATION;
# 4493 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_ARCHIVE_MEMBER_HEADER {
      BYTE Name[16];
      BYTE Date[12];
      BYTE UserID[6];
      BYTE GroupID[6];
      BYTE Mode[8];
      BYTE Size[10];
      BYTE EndHeader[2];
    } IMAGE_ARCHIVE_MEMBER_HEADER,*PIMAGE_ARCHIVE_MEMBER_HEADER;



    typedef struct _IMAGE_EXPORT_DIRECTORY {
      DWORD Characteristics;
      DWORD TimeDateStamp;
      WORD MajorVersion;
      WORD MinorVersion;
      DWORD Name;
      DWORD Base;
      DWORD NumberOfFunctions;
      DWORD NumberOfNames;
      DWORD AddressOfFunctions;
      DWORD AddressOfNames;
      DWORD AddressOfNameOrdinals;
    } IMAGE_EXPORT_DIRECTORY,*PIMAGE_EXPORT_DIRECTORY;

    typedef struct _IMAGE_IMPORT_BY_NAME {
      WORD Hint;
      BYTE Name[1];
    } IMAGE_IMPORT_BY_NAME,*PIMAGE_IMPORT_BY_NAME;

# 1 "c:/program files/tcc/include/winapi/pshpack8.h" 1






#pragma pack(push,8)
# 4525 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_THUNK_DATA64 {
      union {
	ULONGLONG ForwarderString;
	ULONGLONG Function;
	ULONGLONG Ordinal;
	ULONGLONG AddressOfData;
      } u1;
    } IMAGE_THUNK_DATA64;
    typedef IMAGE_THUNK_DATA64 *PIMAGE_THUNK_DATA64;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 4537 "c:/program files/tcc/include/winapi/winnt.h" 2

    typedef struct _IMAGE_THUNK_DATA32 {
      union {
	DWORD ForwarderString;
	DWORD Function;
	DWORD Ordinal;
	DWORD AddressOfData;
      } u1;
    } IMAGE_THUNK_DATA32;
    typedef IMAGE_THUNK_DATA32 *PIMAGE_THUNK_DATA32;
# 4555 "c:/program files/tcc/include/winapi/winnt.h"
    typedef void
      ( *PIMAGE_TLS_CALLBACK)(PVOID DllHandle,DWORD Reason,PVOID Reserved);

    typedef struct _IMAGE_TLS_DIRECTORY64 {
      ULONGLONG StartAddressOfRawData;
      ULONGLONG EndAddressOfRawData;
      ULONGLONG AddressOfIndex;
      ULONGLONG AddressOfCallBacks;
      DWORD SizeOfZeroFill;
      DWORD Characteristics;
    } IMAGE_TLS_DIRECTORY64;
    typedef IMAGE_TLS_DIRECTORY64 *PIMAGE_TLS_DIRECTORY64;

    typedef struct _IMAGE_TLS_DIRECTORY32 {
      DWORD StartAddressOfRawData;
      DWORD EndAddressOfRawData;
      DWORD AddressOfIndex;
      DWORD AddressOfCallBacks;
      DWORD SizeOfZeroFill;
      DWORD Characteristics;
    } IMAGE_TLS_DIRECTORY32;
    typedef IMAGE_TLS_DIRECTORY32 *PIMAGE_TLS_DIRECTORY32;




    typedef IMAGE_THUNK_DATA64 IMAGE_THUNK_DATA;
    typedef PIMAGE_THUNK_DATA64 PIMAGE_THUNK_DATA;

    typedef IMAGE_TLS_DIRECTORY64 IMAGE_TLS_DIRECTORY;
    typedef PIMAGE_TLS_DIRECTORY64 PIMAGE_TLS_DIRECTORY;
# 4596 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_IMPORT_DESCRIPTOR {
      union {
	DWORD Characteristics;
	DWORD OriginalFirstThunk;
      };
      DWORD TimeDateStamp;

      DWORD ForwarderChain;
      DWORD Name;
      DWORD FirstThunk;
    } IMAGE_IMPORT_DESCRIPTOR;
    typedef IMAGE_IMPORT_DESCRIPTOR  *PIMAGE_IMPORT_DESCRIPTOR;

    typedef struct _IMAGE_BOUND_IMPORT_DESCRIPTOR {
      DWORD TimeDateStamp;
      WORD OffsetModuleName;
      WORD NumberOfModuleForwarderRefs;
    } IMAGE_BOUND_IMPORT_DESCRIPTOR,*PIMAGE_BOUND_IMPORT_DESCRIPTOR;

    typedef struct _IMAGE_BOUND_FORWARDER_REF {
      DWORD TimeDateStamp;
      WORD OffsetModuleName;
      WORD Reserved;
    } IMAGE_BOUND_FORWARDER_REF,*PIMAGE_BOUND_FORWARDER_REF;

    typedef struct _IMAGE_RESOURCE_DIRECTORY {
      DWORD Characteristics;
      DWORD TimeDateStamp;
      WORD MajorVersion;
      WORD MinorVersion;
      WORD NumberOfNamedEntries;
      WORD NumberOfIdEntries;
    } IMAGE_RESOURCE_DIRECTORY,*PIMAGE_RESOURCE_DIRECTORY;




    typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
      union {
	struct {
	  DWORD NameOffset:31;
	  DWORD NameIsString:1;
	};
	DWORD Name;
	WORD Id;
      };
      union {
	DWORD OffsetToData;
	struct {
	  DWORD OffsetToDirectory:31;
	  DWORD DataIsDirectory:1;
	};
      };
    } IMAGE_RESOURCE_DIRECTORY_ENTRY,*PIMAGE_RESOURCE_DIRECTORY_ENTRY;

    typedef struct _IMAGE_RESOURCE_DIRECTORY_STRING {
      WORD Length;
      CHAR NameString[1];
    } IMAGE_RESOURCE_DIRECTORY_STRING,*PIMAGE_RESOURCE_DIRECTORY_STRING;

    typedef struct _IMAGE_RESOURCE_DIR_STRING_U {
      WORD Length;
      WCHAR NameString[1];
    } IMAGE_RESOURCE_DIR_STRING_U,*PIMAGE_RESOURCE_DIR_STRING_U;

    typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
      DWORD OffsetToData;
      DWORD Size;
      DWORD CodePage;
      DWORD Reserved;
    } IMAGE_RESOURCE_DATA_ENTRY,*PIMAGE_RESOURCE_DATA_ENTRY;

    typedef struct {
      DWORD Size;
      DWORD TimeDateStamp;
      WORD MajorVersion;
      WORD MinorVersion;
      DWORD GlobalFlagsClear;
      DWORD GlobalFlagsSet;
      DWORD CriticalSectionDefaultTimeout;
      DWORD DeCommitFreeBlockThreshold;
      DWORD DeCommitTotalFreeThreshold;
      DWORD LockPrefixTable;
      DWORD MaximumAllocationSize;
      DWORD VirtualMemoryThreshold;
      DWORD ProcessHeapFlags;
      DWORD ProcessAffinityMask;
      WORD CSDVersion;
      WORD Reserved1;
      DWORD EditList;
      DWORD SecurityCookie;
      DWORD SEHandlerTable;
      DWORD SEHandlerCount;
    } IMAGE_LOAD_CONFIG_DIRECTORY32,*PIMAGE_LOAD_CONFIG_DIRECTORY32;

    typedef struct {
      DWORD Size;
      DWORD TimeDateStamp;
      WORD MajorVersion;
      WORD MinorVersion;
      DWORD GlobalFlagsClear;
      DWORD GlobalFlagsSet;
      DWORD CriticalSectionDefaultTimeout;
      ULONGLONG DeCommitFreeBlockThreshold;
      ULONGLONG DeCommitTotalFreeThreshold;
      ULONGLONG LockPrefixTable;
      ULONGLONG MaximumAllocationSize;
      ULONGLONG VirtualMemoryThreshold;
      ULONGLONG ProcessAffinityMask;
      DWORD ProcessHeapFlags;
      WORD CSDVersion;
      WORD Reserved1;
      ULONGLONG EditList;
      ULONGLONG SecurityCookie;
      ULONGLONG SEHandlerTable;
      ULONGLONG SEHandlerCount;
    } IMAGE_LOAD_CONFIG_DIRECTORY64,*PIMAGE_LOAD_CONFIG_DIRECTORY64;


    typedef IMAGE_LOAD_CONFIG_DIRECTORY64 IMAGE_LOAD_CONFIG_DIRECTORY;
    typedef PIMAGE_LOAD_CONFIG_DIRECTORY64 PIMAGE_LOAD_CONFIG_DIRECTORY;





    typedef struct _IMAGE_CE_RUNTIME_FUNCTION_ENTRY {
      DWORD FuncStart;
      DWORD PrologLen : 8;
      DWORD FuncLen : 22;
      DWORD ThirtyTwoBit : 1;
      DWORD ExceptionFlag : 1;
    } IMAGE_CE_RUNTIME_FUNCTION_ENTRY,*PIMAGE_CE_RUNTIME_FUNCTION_ENTRY;

    typedef struct _IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY {
      ULONGLONG BeginAddress;
      ULONGLONG EndAddress;
      ULONGLONG ExceptionHandler;
      ULONGLONG HandlerData;
      ULONGLONG PrologEndAddress;
    } IMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY,*PIMAGE_ALPHA64_RUNTIME_FUNCTION_ENTRY;

    typedef struct _IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY {
      DWORD BeginAddress;
      DWORD EndAddress;
      DWORD ExceptionHandler;
      DWORD HandlerData;
      DWORD PrologEndAddress;
    } IMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY,*PIMAGE_ALPHA_RUNTIME_FUNCTION_ENTRY;

    typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY {
      DWORD BeginAddress;
      DWORD EndAddress;
      DWORD UnwindInfoAddress;
    } _IMAGE_RUNTIME_FUNCTION_ENTRY,*_PIMAGE_RUNTIME_FUNCTION_ENTRY;

    typedef _IMAGE_RUNTIME_FUNCTION_ENTRY IMAGE_IA64_RUNTIME_FUNCTION_ENTRY;
    typedef _PIMAGE_RUNTIME_FUNCTION_ENTRY PIMAGE_IA64_RUNTIME_FUNCTION_ENTRY;

    typedef _IMAGE_RUNTIME_FUNCTION_ENTRY IMAGE_RUNTIME_FUNCTION_ENTRY;
    typedef _PIMAGE_RUNTIME_FUNCTION_ENTRY PIMAGE_RUNTIME_FUNCTION_ENTRY;

    typedef struct _IMAGE_DEBUG_DIRECTORY {
      DWORD Characteristics;
      DWORD TimeDateStamp;
      WORD MajorVersion;
      WORD MinorVersion;
      DWORD Type;
      DWORD SizeOfData;
      DWORD AddressOfRawData;
      DWORD PointerToRawData;
    } IMAGE_DEBUG_DIRECTORY,*PIMAGE_DEBUG_DIRECTORY;
# 4782 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _IMAGE_COFF_SYMBOLS_HEADER {
      DWORD NumberOfSymbols;
      DWORD LvaToFirstSymbol;
      DWORD NumberOfLinenumbers;
      DWORD LvaToFirstLinenumber;
      DWORD RvaToFirstByteOfCode;
      DWORD RvaToLastByteOfCode;
      DWORD RvaToFirstByteOfData;
      DWORD RvaToLastByteOfData;
    } IMAGE_COFF_SYMBOLS_HEADER,*PIMAGE_COFF_SYMBOLS_HEADER;






    typedef struct _FPO_DATA {
      DWORD ulOffStart;
      DWORD cbProcSize;
      DWORD cdwLocals;
      WORD cdwParams;
      WORD cbProlog : 8;
      WORD cbRegs : 3;
      WORD fHasSEH : 1;
      WORD fUseBP : 1;
      WORD reserved : 1;
      WORD cbFrame : 2;
    } FPO_DATA,*PFPO_DATA;




    typedef struct _IMAGE_DEBUG_MISC {
      DWORD DataType;
      DWORD Length;
      BOOLEAN Unicode;
      BYTE Reserved[3];
      BYTE Data[1];
    } IMAGE_DEBUG_MISC,*PIMAGE_DEBUG_MISC;

    typedef struct _IMAGE_FUNCTION_ENTRY {
      DWORD StartingAddress;
      DWORD EndingAddress;
      DWORD EndOfPrologue;
    } IMAGE_FUNCTION_ENTRY,*PIMAGE_FUNCTION_ENTRY;

    typedef struct _IMAGE_FUNCTION_ENTRY64 {
      ULONGLONG StartingAddress;
      ULONGLONG EndingAddress;
      union {
	ULONGLONG EndOfPrologue;
	ULONGLONG UnwindInfoAddress;
      };
    } IMAGE_FUNCTION_ENTRY64,*PIMAGE_FUNCTION_ENTRY64;

    typedef struct _IMAGE_SEPARATE_DEBUG_HEADER {
      WORD Signature;
      WORD Flags;
      WORD Machine;
      WORD Characteristics;
      DWORD TimeDateStamp;
      DWORD CheckSum;
      DWORD ImageBase;
      DWORD SizeOfImage;
      DWORD NumberOfSections;
      DWORD ExportedNamesSize;
      DWORD DebugDirectorySize;
      DWORD SectionAlignment;
      DWORD Reserved[2];
    } IMAGE_SEPARATE_DEBUG_HEADER,*PIMAGE_SEPARATE_DEBUG_HEADER;

    typedef struct _NON_PAGED_DEBUG_INFO {
      WORD Signature;
      WORD Flags;
      DWORD Size;
      WORD Machine;
      WORD Characteristics;
      DWORD TimeDateStamp;
      DWORD CheckSum;
      DWORD SizeOfImage;
      ULONGLONG ImageBase;

    } NON_PAGED_DEBUG_INFO,*PNON_PAGED_DEBUG_INFO;







    typedef struct _ImageArchitectureHeader {
      unsigned int AmaskValue: 1;
      int Adummy1 :7;
      unsigned int AmaskShift: 8;
      int Adummy2 :16;
      DWORD FirstEntryRVA;
    } IMAGE_ARCHITECTURE_HEADER,*PIMAGE_ARCHITECTURE_HEADER;

    typedef struct _ImageArchitectureEntry {
      DWORD FixupInstRVA;
      DWORD NewInst;
    } IMAGE_ARCHITECTURE_ENTRY,*PIMAGE_ARCHITECTURE_ENTRY;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 4886 "c:/program files/tcc/include/winapi/winnt.h" 2



    typedef struct IMPORT_OBJECT_HEADER {
      WORD Sig1;
      WORD Sig2;
      WORD Version;
      WORD Machine;
      DWORD TimeDateStamp;
      DWORD SizeOfData;
      union {
	WORD Ordinal;
	WORD Hint;
      };
      WORD Type : 2;
      WORD NameType : 3;
      WORD Reserved : 11;
    } IMPORT_OBJECT_HEADER;

    typedef enum IMPORT_OBJECT_TYPE {
      IMPORT_OBJECT_CODE = 0,IMPORT_OBJECT_DATA = 1,IMPORT_OBJECT_CONST = 2
    } IMPORT_OBJECT_TYPE;

    typedef enum IMPORT_OBJECT_NAME_TYPE {
      IMPORT_OBJECT_ORDINAL = 0,IMPORT_OBJECT_NAME = 1,IMPORT_OBJECT_NAME_NO_PREFIX = 2,IMPORT_OBJECT_NAME_UNDECORATE = 3
    } IMPORT_OBJECT_NAME_TYPE;



    typedef enum ReplacesCorHdrNumericDefines {
      COMIMAGE_FLAGS_ILONLY =0x00000001,COMIMAGE_FLAGS_32BITREQUIRED =0x00000002,COMIMAGE_FLAGS_IL_LIBRARY =0x00000004,
      COMIMAGE_FLAGS_STRONGNAMESIGNED =0x00000008,COMIMAGE_FLAGS_TRACKDEBUGDATA =0x00010000,COR_VERSION_MAJOR_V2 =2,
      COR_VERSION_MAJOR =COR_VERSION_MAJOR_V2,COR_VERSION_MINOR =0,COR_DELETED_NAME_LENGTH =8,COR_VTABLEGAP_NAME_LENGTH =8,
      NATIVE_TYPE_MAX_CB =1,COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE=0xFF,IMAGE_COR_MIH_METHODRVA =0x01,IMAGE_COR_MIH_EHRVA =0x02,
      IMAGE_COR_MIH_BASICBLOCK =0x08,COR_VTABLE_32BIT =0x01,COR_VTABLE_64BIT =0x02,COR_VTABLE_FROM_UNMANAGED =0x04,
      COR_VTABLE_CALL_MOST_DERIVED =0x10,IMAGE_COR_EATJ_THUNK_SIZE =32,MAX_CLASS_NAME =1024,MAX_PACKAGE_NAME =1024
    } ReplacesCorHdrNumericDefines;

    typedef struct IMAGE_COR20_HEADER {
      DWORD cb;
      WORD MajorRuntimeVersion;
      WORD MinorRuntimeVersion;
      IMAGE_DATA_DIRECTORY MetaData;
      DWORD Flags;
      DWORD EntryPointToken;
      IMAGE_DATA_DIRECTORY Resources;
      IMAGE_DATA_DIRECTORY StrongNameSignature;
      IMAGE_DATA_DIRECTORY CodeManagerTable;
      IMAGE_DATA_DIRECTORY VTableFixups;
      IMAGE_DATA_DIRECTORY ExportAddressTableJumps;
      IMAGE_DATA_DIRECTORY ManagedNativeHeader;
    } IMAGE_COR20_HEADER,*PIMAGE_COR20_HEADER;



    __attribute__((dllimport)) PRUNTIME_FUNCTION  RtlLookupFunctionEntry (DWORD64 ControlPc, PDWORD64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable);
    __attribute__((dllimport)) void  RtlUnwindEx (PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue, PCONTEXT ContextRecord, PUNWIND_HISTORY_TABLE HistoryTable);
# 4951 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _SLIST_ENTRY *PSLIST_ENTRY;
    typedef __attribute__((aligned(16))) struct _SLIST_ENTRY {
      PSLIST_ENTRY Next;
    } SLIST_ENTRY;
# 4964 "c:/program files/tcc/include/winapi/winnt.h"
    typedef __attribute__((aligned(16))) struct _SLIST_HEADER {
      ULONGLONG Alignment;
      ULONGLONG Region;
    } SLIST_HEADER;

    typedef struct _SLIST_HEADER *PSLIST_HEADER;
# 4983 "c:/program files/tcc/include/winapi/winnt.h"
    __attribute__((dllimport)) void  RtlInitializeSListHead(PSLIST_HEADER ListHead);
    __attribute__((dllimport)) PSLIST_ENTRY  RtlFirstEntrySList(const SLIST_HEADER *ListHead);
    __attribute__((dllimport)) PSLIST_ENTRY  RtlInterlockedPopEntrySList(PSLIST_HEADER ListHead);
    __attribute__((dllimport)) PSLIST_ENTRY  RtlInterlockedPushEntrySList(PSLIST_HEADER ListHead,PSLIST_ENTRY ListEntry);
    __attribute__((dllimport)) PSLIST_ENTRY  RtlInterlockedFlushSList(PSLIST_HEADER ListHead);
    __attribute__((dllimport)) WORD  RtlQueryDepthSList(PSLIST_HEADER ListHead);
# 5006 "c:/program files/tcc/include/winapi/winnt.h"
    __attribute__((dllimport)) void  RtlCaptureContext(PCONTEXT ContextRecord);
# 5048 "c:/program files/tcc/include/winapi/winnt.h"
    __attribute__((dllimport)) SIZE_T  RtlCompareMemory(const void *Source1,const void *Source2,SIZE_T Length);







    extern __inline__ PVOID RtlSecureZeroMemory(PVOID ptr,SIZE_T cnt) {
      volatile char *vptr =(volatile char *)ptr;

      __stosb((PBYTE)((DWORD64)vptr),0,cnt);







      return ptr;
    }

    typedef struct _MESSAGE_RESOURCE_ENTRY {
      WORD Length;
      WORD Flags;
      BYTE Text[1];
    } MESSAGE_RESOURCE_ENTRY,*PMESSAGE_RESOURCE_ENTRY;



    typedef struct _MESSAGE_RESOURCE_BLOCK {
      DWORD LowId;
      DWORD HighId;
      DWORD OffsetToEntries;
    } MESSAGE_RESOURCE_BLOCK,*PMESSAGE_RESOURCE_BLOCK;

    typedef struct _MESSAGE_RESOURCE_DATA {
      DWORD NumberOfBlocks;
      MESSAGE_RESOURCE_BLOCK Blocks[1];
    } MESSAGE_RESOURCE_DATA,*PMESSAGE_RESOURCE_DATA;

    typedef struct _OSVERSIONINFOA {
      DWORD dwOSVersionInfoSize;
      DWORD dwMajorVersion;
      DWORD dwMinorVersion;
      DWORD dwBuildNumber;
      DWORD dwPlatformId;
      CHAR szCSDVersion[128];
    } OSVERSIONINFOA,*POSVERSIONINFOA,*LPOSVERSIONINFOA;

    typedef struct _OSVERSIONINFOW {
      DWORD dwOSVersionInfoSize;
      DWORD dwMajorVersion;
      DWORD dwMinorVersion;
      DWORD dwBuildNumber;
      DWORD dwPlatformId;
      WCHAR szCSDVersion[128];
    } OSVERSIONINFOW,*POSVERSIONINFOW,*LPOSVERSIONINFOW,RTL_OSVERSIONINFOW,*PRTL_OSVERSIONINFOW;






    typedef OSVERSIONINFOA OSVERSIONINFO;
    typedef POSVERSIONINFOA POSVERSIONINFO;
    typedef LPOSVERSIONINFOA LPOSVERSIONINFO;


    typedef struct _OSVERSIONINFOEXA {
      DWORD dwOSVersionInfoSize;
      DWORD dwMajorVersion;
      DWORD dwMinorVersion;
      DWORD dwBuildNumber;
      DWORD dwPlatformId;
      CHAR szCSDVersion[128];
      WORD wServicePackMajor;
      WORD wServicePackMinor;
      WORD wSuiteMask;
      BYTE wProductType;
      BYTE wReserved;
    } OSVERSIONINFOEXA,*POSVERSIONINFOEXA,*LPOSVERSIONINFOEXA;

    typedef struct _OSVERSIONINFOEXW {
      DWORD dwOSVersionInfoSize;
      DWORD dwMajorVersion;
      DWORD dwMinorVersion;
      DWORD dwBuildNumber;
      DWORD dwPlatformId;
      WCHAR szCSDVersion[128];
      WORD wServicePackMajor;
      WORD wServicePackMinor;
      WORD wSuiteMask;
      BYTE wProductType;
      BYTE wReserved;
    } OSVERSIONINFOEXW,*POSVERSIONINFOEXW,*LPOSVERSIONINFOEXW,RTL_OSVERSIONINFOEXW,*PRTL_OSVERSIONINFOEXW;





    typedef OSVERSIONINFOEXA OSVERSIONINFOEX;
    typedef POSVERSIONINFOEXA POSVERSIONINFOEX;
    typedef LPOSVERSIONINFOEXA LPOSVERSIONINFOEX;
# 5184 "c:/program files/tcc/include/winapi/winnt.h"
    __attribute__((dllimport)) ULONGLONG  VerSetConditionMask(ULONGLONG ConditionMask,DWORD TypeMask,BYTE Condition);

    typedef struct _RTL_CRITICAL_SECTION_DEBUG {
      WORD Type;
      WORD CreatorBackTraceIndex;
      struct _RTL_CRITICAL_SECTION *CriticalSection;
      LIST_ENTRY ProcessLocksList;
      DWORD EntryCount;
      DWORD ContentionCount;
      DWORD Spare[2];
    } RTL_CRITICAL_SECTION_DEBUG,*PRTL_CRITICAL_SECTION_DEBUG,RTL_RESOURCE_DEBUG,*PRTL_RESOURCE_DEBUG;




    typedef struct _RTL_CRITICAL_SECTION {
      PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
      LONG LockCount;
      LONG RecursionCount;
      HANDLE OwningThread;
      HANDLE LockSemaphore;
      ULONG_PTR SpinCount;
    } RTL_CRITICAL_SECTION,*PRTL_CRITICAL_SECTION;

    typedef void ( *RTL_VERIFIER_DLL_LOAD_CALLBACK) (PWSTR DllName,PVOID DllBase,SIZE_T DllSize,PVOID Reserved);
    typedef void ( *RTL_VERIFIER_DLL_UNLOAD_CALLBACK) (PWSTR DllName,PVOID DllBase,SIZE_T DllSize,PVOID Reserved);
    typedef void ( *RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK)(PVOID AllocationBase,SIZE_T AllocationSize);

    typedef struct _RTL_VERIFIER_THUNK_DESCRIPTOR {
      PCHAR ThunkName;
      PVOID ThunkOldAddress;
      PVOID ThunkNewAddress;
    } RTL_VERIFIER_THUNK_DESCRIPTOR,*PRTL_VERIFIER_THUNK_DESCRIPTOR;

    typedef struct _RTL_VERIFIER_DLL_DESCRIPTOR {
      PWCHAR DllName;
      DWORD DllFlags;
      PVOID DllAddress;
      PRTL_VERIFIER_THUNK_DESCRIPTOR DllThunks;
    } RTL_VERIFIER_DLL_DESCRIPTOR,*PRTL_VERIFIER_DLL_DESCRIPTOR;

    typedef struct _RTL_VERIFIER_PROVIDER_DESCRIPTOR {
      DWORD Length;
      PRTL_VERIFIER_DLL_DESCRIPTOR ProviderDlls;
      RTL_VERIFIER_DLL_LOAD_CALLBACK ProviderDllLoadCallback;
      RTL_VERIFIER_DLL_UNLOAD_CALLBACK ProviderDllUnloadCallback;
      PWSTR VerifierImage;
      DWORD VerifierFlags;
      DWORD VerifierDebug;
      PVOID RtlpGetStackTraceAddress;
      PVOID RtlpDebugPageHeapCreate;
      PVOID RtlpDebugPageHeapDestroy;
      RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK ProviderNtdllHeapFreeCallback;
    } RTL_VERIFIER_PROVIDER_DESCRIPTOR,*PRTL_VERIFIER_PROVIDER_DESCRIPTOR;
# 5344 "c:/program files/tcc/include/winapi/winnt.h"
    void  RtlApplicationVerifierStop(ULONG_PTR Code,PSTR Message,ULONG_PTR Param1,PSTR Description1,ULONG_PTR Param2,PSTR Description2,ULONG_PTR Param3,PSTR Description3,ULONG_PTR Param4,PSTR Description4);

    typedef LONG ( *PVECTORED_EXCEPTION_HANDLER)(struct _EXCEPTION_POINTERS *ExceptionInfo);
# 5355 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _HEAP_INFORMATION_CLASS {
      HeapCompatibilityInformation
    } HEAP_INFORMATION_CLASS;

    __attribute__((dllimport)) DWORD  RtlSetHeapInformation(PVOID HeapHandle,HEAP_INFORMATION_CLASS HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength);
    __attribute__((dllimport)) DWORD  RtlQueryHeapInformation(PVOID HeapHandle,HEAP_INFORMATION_CLASS HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength,PSIZE_T ReturnLength);
    DWORD  RtlMultipleAllocateHeap(PVOID HeapHandle,DWORD Flags,SIZE_T Size,DWORD Count,PVOID *Array);
    DWORD  RtlMultipleFreeHeap(PVOID HeapHandle,DWORD Flags,DWORD Count,PVOID *Array);
# 5375 "c:/program files/tcc/include/winapi/winnt.h"
    typedef void ( *WAITORTIMERCALLBACKFUNC)(PVOID,BOOLEAN);
    typedef void ( *WORKERCALLBACKFUNC)(PVOID);
    typedef void ( *APC_CALLBACK_FUNCTION)(DWORD ,PVOID,PVOID);
    typedef
      void
      ( *PFLS_CALLBACK_FUNCTION)(PVOID lpFlsData);



    typedef enum _ACTIVATION_CONTEXT_INFO_CLASS {
      ActivationContextBasicInformation = 1,ActivationContextDetailedInformation = 2,AssemblyDetailedInformationInActivationContext = 3,FileInformationInAssemblyOfAssemblyInActivationContext = 4,MaxActivationContextInfoClass,AssemblyDetailedInformationInActivationContxt = 3,FileInformationInAssemblyOfAssemblyInActivationContxt = 4
    } ACTIVATION_CONTEXT_INFO_CLASS;



    typedef struct _ACTIVATION_CONTEXT_QUERY_INDEX {
      DWORD ulAssemblyIndex;
      DWORD ulFileIndexInAssembly;
    } ACTIVATION_CONTEXT_QUERY_INDEX,*PACTIVATION_CONTEXT_QUERY_INDEX;

    typedef const struct _ACTIVATION_CONTEXT_QUERY_INDEX *PCACTIVATION_CONTEXT_QUERY_INDEX;






    typedef struct _ASSEMBLY_FILE_DETAILED_INFORMATION {
      DWORD ulFlags;
      DWORD ulFilenameLength;
      DWORD ulPathLength;

      PCWSTR lpFileName;
      PCWSTR lpFilePath;
    } ASSEMBLY_FILE_DETAILED_INFORMATION,*PASSEMBLY_FILE_DETAILED_INFORMATION;
    typedef const ASSEMBLY_FILE_DETAILED_INFORMATION *PCASSEMBLY_FILE_DETAILED_INFORMATION;






    typedef struct _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION {
      DWORD ulFlags;
      DWORD ulEncodedAssemblyIdentityLength;
      DWORD ulManifestPathType;
      DWORD ulManifestPathLength;
      LARGE_INTEGER liManifestLastWriteTime;
      DWORD ulPolicyPathType;
      DWORD ulPolicyPathLength;
      LARGE_INTEGER liPolicyLastWriteTime;
      DWORD ulMetadataSatelliteRosterIndex;
      DWORD ulManifestVersionMajor;
      DWORD ulManifestVersionMinor;
      DWORD ulPolicyVersionMajor;
      DWORD ulPolicyVersionMinor;
      DWORD ulAssemblyDirectoryNameLength;
      PCWSTR lpAssemblyEncodedAssemblyIdentity;
      PCWSTR lpAssemblyManifestPath;
      PCWSTR lpAssemblyPolicyPath;
      PCWSTR lpAssemblyDirectoryName;
      DWORD ulFileCount;
    } ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION,*PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;

    typedef const struct _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION *PCACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;

    typedef struct _ACTIVATION_CONTEXT_DETAILED_INFORMATION {
      DWORD dwFlags;
      DWORD ulFormatVersion;
      DWORD ulAssemblyCount;
      DWORD ulRootManifestPathType;
      DWORD ulRootManifestPathChars;
      DWORD ulRootConfigurationPathType;
      DWORD ulRootConfigurationPathChars;
      DWORD ulAppDirPathType;
      DWORD ulAppDirPathChars;
      PCWSTR lpRootManifestPath;
      PCWSTR lpRootConfigurationPath;
      PCWSTR lpAppDirPath;
    } ACTIVATION_CONTEXT_DETAILED_INFORMATION,*PACTIVATION_CONTEXT_DETAILED_INFORMATION;

    typedef const struct _ACTIVATION_CONTEXT_DETAILED_INFORMATION *PCACTIVATION_CONTEXT_DETAILED_INFORMATION;
# 5482 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _EVENTLOGRECORD {
      DWORD Length;
      DWORD Reserved;
      DWORD RecordNumber;
      DWORD TimeGenerated;
      DWORD TimeWritten;
      DWORD EventID;
      WORD EventType;
      WORD NumStrings;
      WORD EventCategory;
      WORD ReservedFlags;
      DWORD ClosingRecordNumber;
      DWORD StringOffset;
      DWORD UserSidLength;
      DWORD UserSidOffset;
      DWORD DataLength;
      DWORD DataOffset;
    } EVENTLOGRECORD,*PEVENTLOGRECORD;



    typedef struct _EVENTSFORLOGFILE{
      DWORD ulSize;
      WCHAR szLogicalLogFile[256];
      DWORD ulNumRecords;
      EVENTLOGRECORD pEventLogRecords[];
    } EVENTSFORLOGFILE,*PEVENTSFORLOGFILE;

    typedef struct _PACKEDEVENTINFO{
      DWORD ulSize;
      DWORD ulNumEventsForLogFile;
      DWORD ulOffsets[];
    } PACKEDEVENTINFO,*PPACKEDEVENTINFO;
# 5598 "c:/program files/tcc/include/winapi/winnt.h"
    typedef enum _CM_SERVICE_NODE_TYPE {
      DriverType = 0x00000001,FileSystemType = 0x00000002,Win32ServiceOwnProcess = 0x00000010,
      Win32ServiceShareProcess = 0x00000020,AdapterType = 0x00000004,RecognizerType = 0x00000008
    } SERVICE_NODE_TYPE;

    typedef enum _CM_SERVICE_LOAD_TYPE {
      BootLoad = 0x00000000,SystemLoad = 0x00000001,AutoLoad = 0x00000002,DemandLoad = 0x00000003,
      DisableLoad = 0x00000004
    } SERVICE_LOAD_TYPE;

    typedef enum _CM_ERROR_CONTROL_TYPE {
      IgnoreError = 0x00000000,NormalError = 0x00000001,SevereError = 0x00000002,CriticalError = 0x00000003
    } SERVICE_ERROR_TYPE;




    typedef struct _TAPE_ERASE {
      DWORD Type;
      BOOLEAN Immediate;
    } TAPE_ERASE,*PTAPE_ERASE;
# 5627 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _TAPE_PREPARE {
      DWORD Operation;
      BOOLEAN Immediate;
    } TAPE_PREPARE,*PTAPE_PREPARE;






    typedef struct _TAPE_WRITE_MARKS {
      DWORD Type;
      DWORD Count;
      BOOLEAN Immediate;
    } TAPE_WRITE_MARKS,*PTAPE_WRITE_MARKS;





    typedef struct _TAPE_GET_POSITION {
      DWORD Type;
      DWORD Partition;
      LARGE_INTEGER Offset;
    } TAPE_GET_POSITION,*PTAPE_GET_POSITION;
# 5664 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _TAPE_SET_POSITION {
      DWORD Method;
      DWORD Partition;
      LARGE_INTEGER Offset;
      BOOLEAN Immediate;
    } TAPE_SET_POSITION,*PTAPE_SET_POSITION;
# 5743 "c:/program files/tcc/include/winapi/winnt.h"
    typedef struct _TAPE_GET_DRIVE_PARAMETERS {
      BOOLEAN ECC;
      BOOLEAN Compression;
      BOOLEAN DataPadding;
      BOOLEAN ReportSetmarks;
      DWORD DefaultBlockSize;
      DWORD MaximumBlockSize;
      DWORD MinimumBlockSize;
      DWORD MaximumPartitionCount;
      DWORD FeaturesLow;
      DWORD FeaturesHigh;
      DWORD EOTWarningZoneSize;
    } TAPE_GET_DRIVE_PARAMETERS,*PTAPE_GET_DRIVE_PARAMETERS;

    typedef struct _TAPE_SET_DRIVE_PARAMETERS {
      BOOLEAN ECC;
      BOOLEAN Compression;
      BOOLEAN DataPadding;
      BOOLEAN ReportSetmarks;
      DWORD EOTWarningZoneSize;
    } TAPE_SET_DRIVE_PARAMETERS,*PTAPE_SET_DRIVE_PARAMETERS;

    typedef struct _TAPE_GET_MEDIA_PARAMETERS {
      LARGE_INTEGER Capacity;
      LARGE_INTEGER Remaining;
      DWORD BlockSize;
      DWORD PartitionCount;
      BOOLEAN WriteProtected;
    } TAPE_GET_MEDIA_PARAMETERS,*PTAPE_GET_MEDIA_PARAMETERS;

    typedef struct _TAPE_SET_MEDIA_PARAMETERS {
      DWORD BlockSize;
    } TAPE_SET_MEDIA_PARAMETERS,*PTAPE_SET_MEDIA_PARAMETERS;





    typedef struct _TAPE_CREATE_PARTITION {
      DWORD Method;
      DWORD Count;
      DWORD Size;
    } TAPE_CREATE_PARTITION,*PTAPE_CREATE_PARTITION;







    typedef struct _TAPE_WMI_OPERATIONS {
      DWORD Method;
      DWORD DataBufferSize;
      PVOID DataBuffer;
    } TAPE_WMI_OPERATIONS,*PTAPE_WMI_OPERATIONS;

    typedef enum _TAPE_DRIVE_PROBLEM_TYPE {
      TapeDriveProblemNone,TapeDriveReadWriteWarning,TapeDriveReadWriteError,TapeDriveReadWarning,TapeDriveWriteWarning,TapeDriveReadError,TapeDriveWriteError,TapeDriveHardwareError,TapeDriveUnsupportedMedia,TapeDriveScsiConnectionError,TapeDriveTimetoClean,TapeDriveCleanDriveNow,TapeDriveMediaLifeExpired,TapeDriveSnappedTape
    } TAPE_DRIVE_PROBLEM_TYPE;


    extern __inline__ struct _TEB *NtCurrentTeb(void) { return (struct _TEB *)__readgsqword(((LONG)(LONG_PTR)&(((NT_TIB *)0)->Self))); }
    extern __inline__ PVOID GetCurrentFiber(void) { return(PVOID)__readgsqword(((LONG)(LONG_PTR)&(((NT_TIB *)0)->FiberData))); }
    extern __inline__ PVOID GetFiberData(void) {
      return *(PVOID *)GetCurrentFiber();
    }
# 123 "c:/program files/tcc/include/winapi/windef.h" 2




  typedef UINT_PTR WPARAM;
  typedef LONG_PTR LPARAM;
  typedef LONG_PTR LRESULT;
# 151 "c:/program files/tcc/include/winapi/windef.h"
  struct HWND__ { int unused; }; typedef struct HWND__ *HWND;
  struct HHOOK__ { int unused; }; typedef struct HHOOK__ *HHOOK;





  typedef WORD ATOM;

  typedef HANDLE *SPHANDLE;
  typedef HANDLE *LPHANDLE;
  typedef HANDLE HGLOBAL;
  typedef HANDLE HLOCAL;
  typedef HANDLE GLOBALHANDLE;
  typedef HANDLE LOCALHANDLE;

  typedef INT_PTR ( *FARPROC)();
  typedef INT_PTR ( *NEARPROC)();
  typedef INT_PTR ( *PROC)();






  typedef void *HGDIOBJ;

  struct HKEY__ { int unused; }; typedef struct HKEY__ *HKEY;
  typedef HKEY *PHKEY;

  struct HACCEL__ { int unused; }; typedef struct HACCEL__ *HACCEL;
  struct HBITMAP__ { int unused; }; typedef struct HBITMAP__ *HBITMAP;
  struct HBRUSH__ { int unused; }; typedef struct HBRUSH__ *HBRUSH;
  struct HCOLORSPACE__ { int unused; }; typedef struct HCOLORSPACE__ *HCOLORSPACE;
  struct HDC__ { int unused; }; typedef struct HDC__ *HDC;
  struct HGLRC__ { int unused; }; typedef struct HGLRC__ *HGLRC;
  struct HDESK__ { int unused; }; typedef struct HDESK__ *HDESK;
  struct HENHMETAFILE__ { int unused; }; typedef struct HENHMETAFILE__ *HENHMETAFILE;
  struct HFONT__ { int unused; }; typedef struct HFONT__ *HFONT;
  struct HICON__ { int unused; }; typedef struct HICON__ *HICON;
  struct HMENU__ { int unused; }; typedef struct HMENU__ *HMENU;
  struct HMETAFILE__ { int unused; }; typedef struct HMETAFILE__ *HMETAFILE;
  struct HINSTANCE__ { int unused; }; typedef struct HINSTANCE__ *HINSTANCE;
  typedef HINSTANCE HMODULE;
  struct HPALETTE__ { int unused; }; typedef struct HPALETTE__ *HPALETTE;
  struct HPEN__ { int unused; }; typedef struct HPEN__ *HPEN;
  struct HRGN__ { int unused; }; typedef struct HRGN__ *HRGN;
  struct HRSRC__ { int unused; }; typedef struct HRSRC__ *HRSRC;
  struct HSTR__ { int unused; }; typedef struct HSTR__ *HSTR;
  struct HTASK__ { int unused; }; typedef struct HTASK__ *HTASK;
  struct HWINSTA__ { int unused; }; typedef struct HWINSTA__ *HWINSTA;
  struct HKL__ { int unused; }; typedef struct HKL__ *HKL;
  struct HMONITOR__ { int unused; }; typedef struct HMONITOR__ *HMONITOR;
  struct HWINEVENTHOOK__ { int unused; }; typedef struct HWINEVENTHOOK__ *HWINEVENTHOOK;
  struct HUMPD__ { int unused; }; typedef struct HUMPD__ *HUMPD;

  typedef int HFILE;
  typedef HICON HCURSOR;
  typedef DWORD COLORREF;
  typedef DWORD *LPCOLORREF;



  typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
  } RECT,*PRECT,*NPRECT,*LPRECT;

  typedef const RECT *LPCRECT;

  typedef struct _RECTL {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
  } RECTL,*PRECTL,*LPRECTL;

  typedef const RECTL *LPCRECTL;

  typedef struct tagPOINT {
    LONG x;
    LONG y;
  } POINT,*PPOINT,*NPPOINT,*LPPOINT;

  typedef struct _POINTL {
    LONG x;
    LONG y;
  } POINTL,*PPOINTL;

  typedef struct tagSIZE {
    LONG cx;
    LONG cy;
  } SIZE,*PSIZE,*LPSIZE;

  typedef SIZE SIZEL;
  typedef SIZE *PSIZEL,*LPSIZEL;

  typedef struct tagPOINTS {
    SHORT x;
    SHORT y;
  } POINTS,*PPOINTS,*LPPOINTS;

  typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
  } FILETIME,*PFILETIME,*LPFILETIME;
# 67 "c:/program files/tcc/include/winapi/windows.h" 2
# 1 "c:/program files/tcc/include/winapi/winbase.h" 1
# 134 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
      struct {
	DWORD Offset;
	DWORD OffsetHigh;
      };
      PVOID Pointer;
    };
    HANDLE hEvent;
  } OVERLAPPED,*LPOVERLAPPED;

  typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    WINBOOL bInheritHandle;
  } SECURITY_ATTRIBUTES,*PSECURITY_ATTRIBUTES,*LPSECURITY_ATTRIBUTES;

  typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
  } PROCESS_INFORMATION,*PPROCESS_INFORMATION,*LPPROCESS_INFORMATION;
# 168 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
  } SYSTEMTIME,*PSYSTEMTIME,*LPSYSTEMTIME;

  typedef DWORD ( *PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
  typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;
  typedef void ( *PFIBER_START_ROUTINE)(LPVOID lpFiberParameter);
  typedef PFIBER_START_ROUTINE LPFIBER_START_ROUTINE;

  typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
  typedef PRTL_CRITICAL_SECTION PCRITICAL_SECTION;
  typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;
  typedef RTL_CRITICAL_SECTION_DEBUG CRITICAL_SECTION_DEBUG;
  typedef PRTL_CRITICAL_SECTION_DEBUG PCRITICAL_SECTION_DEBUG;
  typedef PRTL_CRITICAL_SECTION_DEBUG LPCRITICAL_SECTION_DEBUG;

  __attribute__((dllimport)) PVOID  EncodePointer(PVOID Ptr);
  __attribute__((dllimport)) PVOID  DecodePointer(PVOID Ptr);
  __attribute__((dllimport)) PVOID  EncodeSystemPointer(PVOID Ptr);
  __attribute__((dllimport)) PVOID  DecodeSystemPointer(PVOID Ptr);




  typedef LPVOID LPLDT_ENTRY;
# 277 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _COMMPROP {
    WORD wPacketLength;
    WORD wPacketVersion;
    DWORD dwServiceMask;
    DWORD dwReserved1;
    DWORD dwMaxTxQueue;
    DWORD dwMaxRxQueue;
    DWORD dwMaxBaud;
    DWORD dwProvSubType;
    DWORD dwProvCapabilities;
    DWORD dwSettableParams;
    DWORD dwSettableBaud;
    WORD wSettableData;
    WORD wSettableStopParity;
    DWORD dwCurrentTxQueue;
    DWORD dwCurrentRxQueue;
    DWORD dwProvSpec1;
    DWORD dwProvSpec2;
    WCHAR wcProvChar[1];
  } COMMPROP,*LPCOMMPROP;



  typedef struct _COMSTAT {
    DWORD fCtsHold : 1;
    DWORD fDsrHold : 1;
    DWORD fRlsdHold : 1;
    DWORD fXoffHold : 1;
    DWORD fXoffSent : 1;
    DWORD fEof : 1;
    DWORD fTxim : 1;
    DWORD fReserved : 25;
    DWORD cbInQue;
    DWORD cbOutQue;
  } COMSTAT,*LPCOMSTAT;
# 322 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _DCB {
    DWORD DCBlength;
    DWORD BaudRate;
    DWORD fBinary: 1;
    DWORD fParity: 1;
    DWORD fOutxCtsFlow:1;
    DWORD fOutxDsrFlow:1;
    DWORD fDtrControl:2;
    DWORD fDsrSensitivity:1;
    DWORD fTXContinueOnXoff: 1;
    DWORD fOutX: 1;
    DWORD fInX: 1;
    DWORD fErrorChar: 1;
    DWORD fNull: 1;
    DWORD fRtsControl:2;
    DWORD fAbortOnError:1;
    DWORD fDummy2:17;
    WORD wReserved;
    WORD XonLim;
    WORD XoffLim;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
    char XonChar;
    char XoffChar;
    char ErrorChar;
    char EofChar;
    char EvtChar;
    WORD wReserved1;
  } DCB,*LPDCB;

  typedef struct _COMMTIMEOUTS {
    DWORD ReadIntervalTimeout;
    DWORD ReadTotalTimeoutMultiplier;
    DWORD ReadTotalTimeoutConstant;
    DWORD WriteTotalTimeoutMultiplier;
    DWORD WriteTotalTimeoutConstant;
  } COMMTIMEOUTS,*LPCOMMTIMEOUTS;

  typedef struct _COMMCONFIG {
    DWORD dwSize;
    WORD wVersion;
    WORD wReserved;
    DCB dcb;
    DWORD dwProviderSubType;
    DWORD dwProviderOffset;
    DWORD dwProviderSize;
    WCHAR wcProviderData[1];
  } COMMCONFIG,*LPCOMMCONFIG;

  typedef struct _SYSTEM_INFO {
    union {
      DWORD dwOemId;
      struct {
	WORD wProcessorArchitecture;
	WORD wReserved;
      };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
  } SYSTEM_INFO,*LPSYSTEM_INFO;
# 420 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _MEMORYSTATUS {
    DWORD dwLength;
    DWORD dwMemoryLoad;
    SIZE_T dwTotalPhys;
    SIZE_T dwAvailPhys;
    SIZE_T dwTotalPageFile;
    SIZE_T dwAvailPageFile;
    SIZE_T dwTotalVirtual;
    SIZE_T dwAvailVirtual;
  } MEMORYSTATUS,*LPMEMORYSTATUS;
# 502 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _EXCEPTION_DEBUG_INFO {
    EXCEPTION_RECORD ExceptionRecord;
    DWORD dwFirstChance;
  } EXCEPTION_DEBUG_INFO,*LPEXCEPTION_DEBUG_INFO;

  typedef struct _CREATE_THREAD_DEBUG_INFO {
    HANDLE hThread;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
  } CREATE_THREAD_DEBUG_INFO,*LPCREATE_THREAD_DEBUG_INFO;

  typedef struct _CREATE_PROCESS_DEBUG_INFO {
    HANDLE hFile;
    HANDLE hProcess;
    HANDLE hThread;
    LPVOID lpBaseOfImage;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpThreadLocalBase;
    LPTHREAD_START_ROUTINE lpStartAddress;
    LPVOID lpImageName;
    WORD fUnicode;
  } CREATE_PROCESS_DEBUG_INFO,*LPCREATE_PROCESS_DEBUG_INFO;

  typedef struct _EXIT_THREAD_DEBUG_INFO {
    DWORD dwExitCode;
  } EXIT_THREAD_DEBUG_INFO,*LPEXIT_THREAD_DEBUG_INFO;

  typedef struct _EXIT_PROCESS_DEBUG_INFO {
    DWORD dwExitCode;
  } EXIT_PROCESS_DEBUG_INFO,*LPEXIT_PROCESS_DEBUG_INFO;

  typedef struct _LOAD_DLL_DEBUG_INFO {
    HANDLE hFile;
    LPVOID lpBaseOfDll;
    DWORD dwDebugInfoFileOffset;
    DWORD nDebugInfoSize;
    LPVOID lpImageName;
    WORD fUnicode;
  } LOAD_DLL_DEBUG_INFO,*LPLOAD_DLL_DEBUG_INFO;

  typedef struct _UNLOAD_DLL_DEBUG_INFO {
    LPVOID lpBaseOfDll;
  } UNLOAD_DLL_DEBUG_INFO,*LPUNLOAD_DLL_DEBUG_INFO;

  typedef struct _OUTPUT_DEBUG_STRING_INFO {
    LPSTR lpDebugStringData;
    WORD fUnicode;
    WORD nDebugStringLength;
  } OUTPUT_DEBUG_STRING_INFO,*LPOUTPUT_DEBUG_STRING_INFO;

  typedef struct _RIP_INFO {
    DWORD dwError;
    DWORD dwType;
  } RIP_INFO,*LPRIP_INFO;

  typedef struct _DEBUG_EVENT {
    DWORD dwDebugEventCode;
    DWORD dwProcessId;
    DWORD dwThreadId;
    union {
      EXCEPTION_DEBUG_INFO Exception;
      CREATE_THREAD_DEBUG_INFO CreateThread;
      CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
      EXIT_THREAD_DEBUG_INFO ExitThread;
      EXIT_PROCESS_DEBUG_INFO ExitProcess;
      LOAD_DLL_DEBUG_INFO LoadDll;
      UNLOAD_DLL_DEBUG_INFO UnloadDll;
      OUTPUT_DEBUG_STRING_INFO DebugString;
      RIP_INFO RipInfo;
    } u;
  } DEBUG_EVENT,*LPDEBUG_EVENT;

  typedef PCONTEXT LPCONTEXT;
  typedef PEXCEPTION_RECORD LPEXCEPTION_RECORD;
  typedef PEXCEPTION_POINTERS LPEXCEPTION_POINTERS;
# 754 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _OFSTRUCT {
    BYTE cBytes;
    BYTE fFixedDisk;
    WORD nErrCode;
    WORD Reserved1;
    WORD Reserved2;
    CHAR szPathName[128];
  } OFSTRUCT,*LPOFSTRUCT,*POFSTRUCT;
# 955 "c:/program files/tcc/include/winapi/winbase.h"
  LONG _InterlockedIncrement(LONG volatile *Addend);
  LONG _InterlockedDecrement(LONG volatile *Addend);
  LONG _InterlockedExchange(LONG volatile *Target,LONG Value);
  LONG _InterlockedExchangeAdd(LONG volatile *Addend,LONG Value);
  LONG _InterlockedCompareExchange(LONG volatile *Destination,LONG ExChange,LONG Comperand);
  PVOID _InterlockedCompareExchangePointer(PVOID volatile *Destination,PVOID Exchange,PVOID Comperand);
  PVOID _InterlockedExchangePointer(PVOID volatile *Target,PVOID Value);
  LONG64 _InterlockedAnd64(LONG64 volatile *Destination,LONG64 Value);
  LONG64 _InterlockedOr64(LONG64 volatile *Destination,LONG64 Value);
  LONG64 _InterlockedXor64(LONG64 volatile *Destination,LONG64 Value);
  LONG64 _InterlockedIncrement64(LONG64 volatile *Addend);
  LONG64 _InterlockedDecrement64(LONG64 volatile *Addend);
  LONG64 _InterlockedExchange64(LONG64 volatile *Target,LONG64 Value);
  LONG64 _InterlockedExchangeAdd64(LONG64 volatile *Addend,LONG64 Value);
  LONG64 _InterlockedCompareExchange64(LONG64 volatile *Destination,LONG64 ExChange,LONG64 Comperand);
# 1062 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) void  InitializeSListHead(PSLIST_HEADER ListHead);
  __attribute__((dllimport)) PSLIST_ENTRY  InterlockedPopEntrySList(PSLIST_HEADER ListHead);
  __attribute__((dllimport)) PSLIST_ENTRY  InterlockedPushEntrySList(PSLIST_HEADER ListHead,PSLIST_ENTRY ListEntry);
  __attribute__((dllimport)) PSLIST_ENTRY  InterlockedFlushSList(PSLIST_HEADER ListHead);
  __attribute__((dllimport)) USHORT  QueryDepthSList(PSLIST_HEADER ListHead);




  __attribute__((dllimport)) WINBOOL  FreeResource(HGLOBAL hResData);
  __attribute__((dllimport)) LPVOID  LockResource(HGLOBAL hResData);






  int  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd);
  __attribute__((dllimport)) WINBOOL  FreeLibrary(HMODULE hLibModule);
  __attribute__((dllimport))  void  FreeLibraryAndExitThread(HMODULE hLibModule,DWORD dwExitCode);
  __attribute__((dllimport)) WINBOOL  DisableThreadLibraryCalls(HMODULE hLibModule);
  __attribute__((dllimport)) FARPROC  GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
  __attribute__((dllimport)) DWORD  GetVersion(void);
  __attribute__((dllimport)) HGLOBAL  GlobalAlloc(UINT uFlags,SIZE_T dwBytes);
  __attribute__((dllimport)) HGLOBAL  GlobalReAlloc(HGLOBAL hMem,SIZE_T dwBytes,UINT uFlags);
  __attribute__((dllimport)) SIZE_T  GlobalSize(HGLOBAL hMem);
  __attribute__((dllimport)) UINT  GlobalFlags(HGLOBAL hMem);
  __attribute__((dllimport)) LPVOID  GlobalLock(HGLOBAL hMem);
  __attribute__((dllimport)) HGLOBAL  GlobalHandle(LPCVOID pMem);
  __attribute__((dllimport)) WINBOOL  GlobalUnlock(HGLOBAL hMem);
  __attribute__((dllimport)) HGLOBAL  GlobalFree(HGLOBAL hMem);
  __attribute__((dllimport)) SIZE_T  GlobalCompact(DWORD dwMinFree);
  __attribute__((dllimport)) void  GlobalFix(HGLOBAL hMem);
  __attribute__((dllimport)) void  GlobalUnfix(HGLOBAL hMem);
  __attribute__((dllimport)) LPVOID  GlobalWire(HGLOBAL hMem);
  __attribute__((dllimport)) WINBOOL  GlobalUnWire(HGLOBAL hMem);
  __attribute__((dllimport)) void  GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer);

  typedef struct _MEMORYSTATUSEX {
    DWORD dwLength;
    DWORD dwMemoryLoad;
    DWORDLONG ullTotalPhys;
    DWORDLONG ullAvailPhys;
    DWORDLONG ullTotalPageFile;
    DWORDLONG ullAvailPageFile;
    DWORDLONG ullTotalVirtual;
    DWORDLONG ullAvailVirtual;
    DWORDLONG ullAvailExtendedVirtual;
  } MEMORYSTATUSEX,*LPMEMORYSTATUSEX;

  __attribute__((dllimport)) WINBOOL  GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer);
  __attribute__((dllimport)) HLOCAL  LocalAlloc(UINT uFlags,SIZE_T uBytes);
  __attribute__((dllimport)) HLOCAL  LocalReAlloc(HLOCAL hMem,SIZE_T uBytes,UINT uFlags);
  __attribute__((dllimport)) LPVOID  LocalLock(HLOCAL hMem);
  __attribute__((dllimport)) HLOCAL  LocalHandle(LPCVOID pMem);
  __attribute__((dllimport)) WINBOOL  LocalUnlock(HLOCAL hMem);
  __attribute__((dllimport)) SIZE_T  LocalSize(HLOCAL hMem);
  __attribute__((dllimport)) UINT  LocalFlags(HLOCAL hMem);
  __attribute__((dllimport)) HLOCAL  LocalFree(HLOCAL hMem);
  __attribute__((dllimport)) SIZE_T  LocalShrink(HLOCAL hMem,UINT cbNewSize);
  __attribute__((dllimport)) SIZE_T  LocalCompact(UINT uMinFree);
  __attribute__((dllimport)) WINBOOL  FlushInstructionCache(HANDLE hProcess,LPCVOID lpBaseAddress,SIZE_T dwSize);
  __attribute__((dllimport)) LPVOID  VirtualAlloc(LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect);
  __attribute__((dllimport)) WINBOOL  VirtualFree(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
  __attribute__((dllimport)) WINBOOL  VirtualProtect(LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);
  __attribute__((dllimport)) SIZE_T  VirtualQuery(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength);
  __attribute__((dllimport)) LPVOID  VirtualAllocEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect);
  __attribute__((dllimport)) UINT  GetWriteWatch(DWORD dwFlags,PVOID lpBaseAddress,SIZE_T dwRegionSize,PVOID *lpAddresses,ULONG_PTR *lpdwCount,PULONG lpdwGranularity);
  __attribute__((dllimport)) UINT  ResetWriteWatch(LPVOID lpBaseAddress,SIZE_T dwRegionSize);
  __attribute__((dllimport)) SIZE_T  GetLargePageMinimum(void);
  __attribute__((dllimport)) UINT  EnumSystemFirmwareTables(DWORD FirmwareTableProviderSignature,PVOID pFirmwareTableEnumBuffer,DWORD BufferSize);
  __attribute__((dllimport)) UINT  GetSystemFirmwareTable(DWORD FirmwareTableProviderSignature,DWORD FirmwareTableID,PVOID pFirmwareTableBuffer,DWORD BufferSize);
  __attribute__((dllimport)) WINBOOL  VirtualFreeEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
  __attribute__((dllimport)) WINBOOL  VirtualProtectEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);
  __attribute__((dllimport)) SIZE_T  VirtualQueryEx(HANDLE hProcess,LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength);
  __attribute__((dllimport)) HANDLE  HeapCreate(DWORD flOptions,SIZE_T dwInitialSize,SIZE_T dwMaximumSize);
  __attribute__((dllimport)) WINBOOL  HeapDestroy(HANDLE hHeap);
  __attribute__((dllimport)) LPVOID  HeapAlloc(HANDLE hHeap,DWORD dwFlags,SIZE_T dwBytes);
  __attribute__((dllimport)) LPVOID  HeapReAlloc(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem,SIZE_T dwBytes);
  __attribute__((dllimport)) WINBOOL  HeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem);
  __attribute__((dllimport)) SIZE_T  HeapSize(HANDLE hHeap,DWORD dwFlags,LPCVOID lpMem);
  __attribute__((dllimport)) WINBOOL  HeapValidate(HANDLE hHeap,DWORD dwFlags,LPCVOID lpMem);
  __attribute__((dllimport)) SIZE_T  HeapCompact(HANDLE hHeap,DWORD dwFlags);
  __attribute__((dllimport)) HANDLE  GetProcessHeap(void);
  __attribute__((dllimport)) DWORD  GetProcessHeaps(DWORD NumberOfHeaps,PHANDLE ProcessHeaps);

  typedef struct _PROCESS_HEAP_ENTRY {
    PVOID lpData;
    DWORD cbData;
    BYTE cbOverhead;
    BYTE iRegionIndex;
    WORD wFlags;
    union {
      struct {
	HANDLE hMem;
	DWORD dwReserved[3];
      } Block;
      struct {
	DWORD dwCommittedSize;
	DWORD dwUnCommittedSize;
	LPVOID lpFirstBlock;
	LPVOID lpLastBlock;
      } Region;
    };
  } PROCESS_HEAP_ENTRY,*LPPROCESS_HEAP_ENTRY,*PPROCESS_HEAP_ENTRY;







  __attribute__((dllimport)) WINBOOL  HeapLock(HANDLE hHeap);
  __attribute__((dllimport)) WINBOOL  HeapUnlock(HANDLE hHeap);
  __attribute__((dllimport)) WINBOOL  HeapWalk(HANDLE hHeap,LPPROCESS_HEAP_ENTRY lpEntry);
  __attribute__((dllimport)) WINBOOL  HeapSetInformation(HANDLE HeapHandle,HEAP_INFORMATION_CLASS HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength);
  __attribute__((dllimport)) WINBOOL  HeapQueryInformation(HANDLE HeapHandle,HEAP_INFORMATION_CLASS HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength,PSIZE_T ReturnLength);
# 1210 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  GetBinaryTypeA(LPCSTR lpApplicationName,LPDWORD lpBinaryType);
  __attribute__((dllimport)) WINBOOL  GetBinaryTypeW(LPCWSTR lpApplicationName,LPDWORD lpBinaryType);
  __attribute__((dllimport)) DWORD  GetShortPathNameA(LPCSTR lpszLongPath,LPSTR lpszShortPath,DWORD cchBuffer);
  __attribute__((dllimport)) DWORD  GetShortPathNameW(LPCWSTR lpszLongPath,LPWSTR lpszShortPath,DWORD cchBuffer);
  __attribute__((dllimport)) DWORD  GetLongPathNameA(LPCSTR lpszShortPath,LPSTR lpszLongPath,DWORD cchBuffer);
  __attribute__((dllimport)) DWORD  GetLongPathNameW(LPCWSTR lpszShortPath,LPWSTR lpszLongPath,DWORD cchBuffer);
  __attribute__((dllimport)) WINBOOL  GetProcessAffinityMask(HANDLE hProcess,PDWORD_PTR lpProcessAffinityMask,PDWORD_PTR lpSystemAffinityMask);
  __attribute__((dllimport)) WINBOOL  SetProcessAffinityMask(HANDLE hProcess,DWORD_PTR dwProcessAffinityMask);
  __attribute__((dllimport)) WINBOOL  GetProcessHandleCount(HANDLE hProcess,PDWORD pdwHandleCount);
  __attribute__((dllimport)) WINBOOL  GetProcessTimes(HANDLE hProcess,LPFILETIME lpCreationTime,LPFILETIME lpExitTime,LPFILETIME lpKernelTime,LPFILETIME lpUserTime);
  __attribute__((dllimport)) WINBOOL  GetProcessIoCounters(HANDLE hProcess,PIO_COUNTERS lpIoCounters);
  __attribute__((dllimport)) WINBOOL  GetProcessWorkingSetSize(HANDLE hProcess,PSIZE_T lpMinimumWorkingSetSize,PSIZE_T lpMaximumWorkingSetSize);
  __attribute__((dllimport)) WINBOOL  GetProcessWorkingSetSizeEx(HANDLE hProcess,PSIZE_T lpMinimumWorkingSetSize,PSIZE_T lpMaximumWorkingSetSize,PDWORD Flags);
  __attribute__((dllimport)) WINBOOL  SetProcessWorkingSetSize(HANDLE hProcess,SIZE_T dwMinimumWorkingSetSize,SIZE_T dwMaximumWorkingSetSize);
  __attribute__((dllimport)) WINBOOL  SetProcessWorkingSetSizeEx(HANDLE hProcess,SIZE_T dwMinimumWorkingSetSize,SIZE_T dwMaximumWorkingSetSize,DWORD Flags);
  __attribute__((dllimport)) HANDLE  OpenProcess(DWORD dwDesiredAccess,WINBOOL bInheritHandle,DWORD dwProcessId);
  __attribute__((dllimport)) HANDLE  GetCurrentProcess(void);
  __attribute__((dllimport)) DWORD  GetCurrentProcessId(void);
  __attribute__((dllimport))  void  ExitProcess(UINT uExitCode);
  __attribute__((dllimport)) WINBOOL  TerminateProcess(HANDLE hProcess,UINT uExitCode);
  __attribute__((dllimport)) WINBOOL  GetExitCodeProcess(HANDLE hProcess,LPDWORD lpExitCode);
  __attribute__((dllimport)) void  FatalExit(int ExitCode);

  __attribute__((dllimport)) LPWCH  GetEnvironmentStringsW(void);
  __attribute__((dllimport)) WINBOOL  SetEnvironmentStringsA(LPCH NewEnvironment);
  __attribute__((dllimport)) WINBOOL  SetEnvironmentStringsW(LPWCH NewEnvironment);
  __attribute__((dllimport)) WINBOOL  FreeEnvironmentStringsA(LPCH);
  __attribute__((dllimport)) WINBOOL  FreeEnvironmentStringsW(LPWCH);
  __attribute__((dllimport)) void  RaiseException(DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,const ULONG_PTR *lpArguments);
  __attribute__((dllimport)) LONG  UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo);

  typedef LONG ( *PTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *ExceptionInfo);
  typedef PTOP_LEVEL_EXCEPTION_FILTER LPTOP_LEVEL_EXCEPTION_FILTER;

  __attribute__((dllimport)) LPTOP_LEVEL_EXCEPTION_FILTER  SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);



  __attribute__((dllimport)) LPVOID  CreateFiber(SIZE_T dwStackSize,LPFIBER_START_ROUTINE lpStartAddress,LPVOID lpParameter);
  __attribute__((dllimport)) LPVOID  CreateFiberEx(SIZE_T dwStackCommitSize,SIZE_T dwStackReserveSize,DWORD dwFlags,LPFIBER_START_ROUTINE lpStartAddress,LPVOID lpParameter);
  __attribute__((dllimport)) void  DeleteFiber(LPVOID lpFiber);
  __attribute__((dllimport)) LPVOID  ConvertThreadToFiber(LPVOID lpParameter);
  __attribute__((dllimport)) LPVOID  ConvertThreadToFiberEx(LPVOID lpParameter,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  ConvertFiberToThread(void);
  __attribute__((dllimport)) void  SwitchToFiber(LPVOID lpFiber);
  __attribute__((dllimport)) WINBOOL  SwitchToThread(void);
  __attribute__((dllimport)) HANDLE  CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId);
  __attribute__((dllimport)) HANDLE  CreateRemoteThread(HANDLE hProcess,LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId);
  __attribute__((dllimport)) HANDLE  GetCurrentThread(void);
  __attribute__((dllimport)) DWORD  GetCurrentThreadId(void);
  __attribute__((dllimport)) WINBOOL  SetThreadStackGuarantee (PULONG StackSizeInBytes);
  __attribute__((dllimport)) DWORD  GetProcessIdOfThread(HANDLE Thread);
  __attribute__((dllimport)) DWORD  GetThreadId(HANDLE Thread);
  __attribute__((dllimport)) DWORD  GetProcessId(HANDLE Process);
  __attribute__((dllimport)) DWORD  GetCurrentProcessorNumber(void);
  __attribute__((dllimport)) DWORD_PTR  SetThreadAffinityMask(HANDLE hThread,DWORD_PTR dwThreadAffinityMask);
  __attribute__((dllimport)) DWORD  SetThreadIdealProcessor(HANDLE hThread,DWORD dwIdealProcessor);
  __attribute__((dllimport)) WINBOOL  SetProcessPriorityBoost(HANDLE hProcess,WINBOOL bDisablePriorityBoost);
  __attribute__((dllimport)) WINBOOL  GetProcessPriorityBoost(HANDLE hProcess,PBOOL pDisablePriorityBoost);
  __attribute__((dllimport)) WINBOOL  RequestWakeupLatency(LATENCY_TIME latency);
  __attribute__((dllimport)) WINBOOL  IsSystemResumeAutomatic(void);
  __attribute__((dllimport)) HANDLE  OpenThread(DWORD dwDesiredAccess,WINBOOL bInheritHandle,DWORD dwThreadId);
  __attribute__((dllimport)) WINBOOL  SetThreadPriority(HANDLE hThread,int nPriority);
  __attribute__((dllimport)) WINBOOL  SetThreadPriorityBoost(HANDLE hThread,WINBOOL bDisablePriorityBoost);
  __attribute__((dllimport)) WINBOOL  GetThreadPriorityBoost(HANDLE hThread,PBOOL pDisablePriorityBoost);
  __attribute__((dllimport)) int  GetThreadPriority(HANDLE hThread);
  __attribute__((dllimport)) WINBOOL  GetThreadTimes(HANDLE hThread,LPFILETIME lpCreationTime,LPFILETIME lpExitTime,LPFILETIME lpKernelTime,LPFILETIME lpUserTime);
  __attribute__((dllimport)) WINBOOL  GetThreadIOPendingFlag(HANDLE hThread,PBOOL lpIOIsPending);
  __attribute__((dllimport))  void  ExitThread(DWORD dwExitCode);
  __attribute__((dllimport)) WINBOOL  TerminateThread(HANDLE hThread,DWORD dwExitCode);
  __attribute__((dllimport)) WINBOOL  GetExitCodeThread(HANDLE hThread,LPDWORD lpExitCode);
  __attribute__((dllimport)) WINBOOL  GetThreadSelectorEntry(HANDLE hThread,DWORD dwSelector,LPLDT_ENTRY lpSelectorEntry);
  __attribute__((dllimport)) EXECUTION_STATE  SetThreadExecutionState(EXECUTION_STATE esFlags);
  __attribute__((dllimport)) DWORD  GetLastError(void);
  __attribute__((dllimport)) void  SetLastError(DWORD dwErrCode);
# 1300 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  GetOverlappedResult(HANDLE hFile,LPOVERLAPPED lpOverlapped,LPDWORD lpNumberOfBytesTransferred,WINBOOL bWait);
  __attribute__((dllimport)) HANDLE  CreateIoCompletionPort(HANDLE FileHandle,HANDLE ExistingCompletionPort,ULONG_PTR CompletionKey,DWORD NumberOfConcurrentThreads);
  __attribute__((dllimport)) WINBOOL  GetQueuedCompletionStatus(HANDLE CompletionPort,LPDWORD lpNumberOfBytesTransferred,PULONG_PTR lpCompletionKey,LPOVERLAPPED *lpOverlapped,DWORD dwMilliseconds);
  __attribute__((dllimport)) WINBOOL  PostQueuedCompletionStatus(HANDLE CompletionPort,DWORD dwNumberOfBytesTransferred,ULONG_PTR dwCompletionKey,LPOVERLAPPED lpOverlapped);






  __attribute__((dllimport)) UINT  SetErrorMode(UINT uMode);
  __attribute__((dllimport)) WINBOOL  ReadProcessMemory(HANDLE hProcess,LPCVOID lpBaseAddress,LPVOID lpBuffer,SIZE_T nSize,SIZE_T *lpNumberOfBytesRead);
  __attribute__((dllimport)) WINBOOL  WriteProcessMemory(HANDLE hProcess,LPVOID lpBaseAddress,LPCVOID lpBuffer,SIZE_T nSize,SIZE_T *lpNumberOfBytesWritten);
  __attribute__((dllimport)) WINBOOL  GetThreadContext(HANDLE hThread,LPCONTEXT lpContext);
  __attribute__((dllimport)) WINBOOL  SetThreadContext(HANDLE hThread,const CONTEXT *lpContext);
  __attribute__((dllimport)) DWORD  SuspendThread(HANDLE hThread);
  __attribute__((dllimport)) DWORD  ResumeThread(HANDLE hThread);

  typedef void ( *PAPCFUNC)(ULONG_PTR dwParam);

  __attribute__((dllimport)) DWORD  QueueUserAPC(PAPCFUNC pfnAPC,HANDLE hThread,ULONG_PTR dwData);
  __attribute__((dllimport)) WINBOOL  IsDebuggerPresent(void);
  __attribute__((dllimport)) WINBOOL  CheckRemoteDebuggerPresent(HANDLE hProcess,PBOOL pbDebuggerPresent);
  __attribute__((dllimport)) void  DebugBreak(void);
  __attribute__((dllimport)) WINBOOL  WaitForDebugEvent(LPDEBUG_EVENT lpDebugEvent,DWORD dwMilliseconds);
  __attribute__((dllimport)) WINBOOL  ContinueDebugEvent(DWORD dwProcessId,DWORD dwThreadId,DWORD dwContinueStatus);
  __attribute__((dllimport)) WINBOOL  DebugActiveProcess(DWORD dwProcessId);
  __attribute__((dllimport)) WINBOOL  DebugActiveProcessStop(DWORD dwProcessId);
  __attribute__((dllimport)) WINBOOL  DebugSetProcessKillOnExit(WINBOOL KillOnExit);
  __attribute__((dllimport)) WINBOOL  DebugBreakProcess(HANDLE Process);
  __attribute__((dllimport)) void  InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
  __attribute__((dllimport)) void  EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
  __attribute__((dllimport)) void  LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
  __attribute__((dllimport)) WINBOOL  InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection,DWORD dwSpinCount);
  __attribute__((dllimport)) DWORD  SetCriticalSectionSpinCount(LPCRITICAL_SECTION lpCriticalSection,DWORD dwSpinCount);
  __attribute__((dllimport)) WINBOOL  TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
  __attribute__((dllimport)) void  DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
  __attribute__((dllimport)) WINBOOL  SetEvent(HANDLE hEvent);
  __attribute__((dllimport)) WINBOOL  ResetEvent(HANDLE hEvent);
  __attribute__((dllimport)) WINBOOL  PulseEvent(HANDLE hEvent);
  __attribute__((dllimport)) WINBOOL  ReleaseSemaphore(HANDLE hSemaphore,LONG lReleaseCount,LPLONG lpPreviousCount);
  __attribute__((dllimport)) WINBOOL  ReleaseMutex(HANDLE hMutex);
  __attribute__((dllimport)) DWORD  WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds);
  __attribute__((dllimport)) DWORD  WaitForMultipleObjects(DWORD nCount,const HANDLE *lpHandles,WINBOOL bWaitAll,DWORD dwMilliseconds);
  __attribute__((dllimport)) void  Sleep(DWORD dwMilliseconds);
  __attribute__((dllimport)) HGLOBAL  LoadResource(HMODULE hModule,HRSRC hResInfo);
  __attribute__((dllimport)) DWORD  SizeofResource(HMODULE hModule,HRSRC hResInfo);
  __attribute__((dllimport)) ATOM  GlobalDeleteAtom(ATOM nAtom);
  __attribute__((dllimport)) WINBOOL  InitAtomTable(DWORD nSize);
  __attribute__((dllimport)) ATOM  DeleteAtom(ATOM nAtom);
  __attribute__((dllimport)) UINT  SetHandleCount(UINT uNumber);
  __attribute__((dllimport)) DWORD  GetLogicalDrives(void);
  __attribute__((dllimport)) WINBOOL  LockFile(HANDLE hFile,DWORD dwFileOffsetLow,DWORD dwFileOffsetHigh,DWORD nNumberOfBytesToLockLow,DWORD nNumberOfBytesToLockHigh);
  __attribute__((dllimport)) WINBOOL  UnlockFile(HANDLE hFile,DWORD dwFileOffsetLow,DWORD dwFileOffsetHigh,DWORD nNumberOfBytesToUnlockLow,DWORD nNumberOfBytesToUnlockHigh);
  __attribute__((dllimport)) WINBOOL  LockFileEx(HANDLE hFile,DWORD dwFlags,DWORD dwReserved,DWORD nNumberOfBytesToLockLow,DWORD nNumberOfBytesToLockHigh,LPOVERLAPPED lpOverlapped);




  __attribute__((dllimport)) WINBOOL  UnlockFileEx(HANDLE hFile,DWORD dwReserved,DWORD nNumberOfBytesToUnlockLow,DWORD nNumberOfBytesToUnlockHigh,LPOVERLAPPED lpOverlapped);

  typedef struct _BY_HANDLE_FILE_INFORMATION {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD dwVolumeSerialNumber;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD nNumberOfLinks;
    DWORD nFileIndexHigh;
    DWORD nFileIndexLow;
  } BY_HANDLE_FILE_INFORMATION,*PBY_HANDLE_FILE_INFORMATION,*LPBY_HANDLE_FILE_INFORMATION;







  __attribute__((dllimport)) WINBOOL  GetFileInformationByHandle(HANDLE hFile,LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
  __attribute__((dllimport)) DWORD  GetFileType(HANDLE hFile);
  __attribute__((dllimport)) DWORD  GetFileSize(HANDLE hFile,LPDWORD lpFileSizeHigh);
  __attribute__((dllimport)) WINBOOL  GetFileSizeEx(HANDLE hFile,PLARGE_INTEGER lpFileSize);
  __attribute__((dllimport)) HANDLE  GetStdHandle(DWORD nStdHandle);
  __attribute__((dllimport)) WINBOOL  SetStdHandle(DWORD nStdHandle,HANDLE hHandle);
  __attribute__((dllimport)) WINBOOL  WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) WINBOOL  ReadFile(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) WINBOOL  FlushFileBuffers(HANDLE hFile);
  __attribute__((dllimport)) WINBOOL  DeviceIoControl(HANDLE hDevice,DWORD dwIoControlCode,LPVOID lpInBuffer,DWORD nInBufferSize,LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesReturned,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) WINBOOL  RequestDeviceWakeup(HANDLE hDevice);
  __attribute__((dllimport)) WINBOOL  CancelDeviceWakeupRequest(HANDLE hDevice);
  __attribute__((dllimport)) WINBOOL  GetDevicePowerState(HANDLE hDevice,WINBOOL *pfOn);
  __attribute__((dllimport)) WINBOOL  SetMessageWaitingIndicator(HANDLE hMsgIndicator,ULONG ulMsgCount);
  __attribute__((dllimport)) WINBOOL  SetEndOfFile(HANDLE hFile);
  __attribute__((dllimport)) DWORD  SetFilePointer(HANDLE hFile,LONG lDistanceToMove,PLONG lpDistanceToMoveHigh,DWORD dwMoveMethod);
  __attribute__((dllimport)) WINBOOL  SetFilePointerEx(HANDLE hFile,LARGE_INTEGER liDistanceToMove,PLARGE_INTEGER lpNewFilePointer,DWORD dwMoveMethod);
  __attribute__((dllimport)) WINBOOL  FindClose(HANDLE hFindFile);
  __attribute__((dllimport)) WINBOOL  GetFileTime(HANDLE hFile,LPFILETIME lpCreationTime,LPFILETIME lpLastAccessTime,LPFILETIME lpLastWriteTime);
  __attribute__((dllimport)) WINBOOL  SetFileTime(HANDLE hFile,const FILETIME *lpCreationTime,const FILETIME *lpLastAccessTime,const FILETIME *lpLastWriteTime);
  __attribute__((dllimport)) WINBOOL  SetFileValidData(HANDLE hFile,LONGLONG ValidDataLength);
  __attribute__((dllimport)) WINBOOL  SetFileShortNameA(HANDLE hFile,LPCSTR lpShortName);
  __attribute__((dllimport)) WINBOOL  SetFileShortNameW(HANDLE hFile,LPCWSTR lpShortName);
  __attribute__((dllimport)) WINBOOL  CloseHandle(HANDLE hObject);
  __attribute__((dllimport)) WINBOOL  DuplicateHandle(HANDLE hSourceProcessHandle,HANDLE hSourceHandle,HANDLE hTargetProcessHandle,LPHANDLE lpTargetHandle,DWORD dwDesiredAccess,WINBOOL bInheritHandle,DWORD dwOptions);
  __attribute__((dllimport)) WINBOOL  GetHandleInformation(HANDLE hObject,LPDWORD lpdwFlags);
  __attribute__((dllimport)) WINBOOL  SetHandleInformation(HANDLE hObject,DWORD dwMask,DWORD dwFlags);






  __attribute__((dllimport)) DWORD  LoadModule(LPCSTR lpModuleName,LPVOID lpParameterBlock);
  __attribute__((dllimport)) UINT  WinExec(LPCSTR lpCmdLine,UINT uCmdShow);
  __attribute__((dllimport)) WINBOOL  ClearCommBreak(HANDLE hFile);
  __attribute__((dllimport)) WINBOOL  ClearCommError(HANDLE hFile,LPDWORD lpErrors,LPCOMSTAT lpStat);
  __attribute__((dllimport)) WINBOOL  SetupComm(HANDLE hFile,DWORD dwInQueue,DWORD dwOutQueue);
  __attribute__((dllimport)) WINBOOL  EscapeCommFunction(HANDLE hFile,DWORD dwFunc);
  __attribute__((dllimport)) WINBOOL  GetCommConfig(HANDLE hCommDev,LPCOMMCONFIG lpCC,LPDWORD lpdwSize);
  __attribute__((dllimport)) WINBOOL  GetCommMask(HANDLE hFile,LPDWORD lpEvtMask);
  __attribute__((dllimport)) WINBOOL  GetCommProperties(HANDLE hFile,LPCOMMPROP lpCommProp);
  __attribute__((dllimport)) WINBOOL  GetCommModemStatus(HANDLE hFile,LPDWORD lpModemStat);
  __attribute__((dllimport)) WINBOOL  GetCommState(HANDLE hFile,LPDCB lpDCB);
  __attribute__((dllimport)) WINBOOL  GetCommTimeouts(HANDLE hFile,LPCOMMTIMEOUTS lpCommTimeouts);
  __attribute__((dllimport)) WINBOOL  PurgeComm(HANDLE hFile,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  SetCommBreak(HANDLE hFile);
  __attribute__((dllimport)) WINBOOL  SetCommConfig(HANDLE hCommDev,LPCOMMCONFIG lpCC,DWORD dwSize);
  __attribute__((dllimport)) WINBOOL  SetCommMask(HANDLE hFile,DWORD dwEvtMask);
  __attribute__((dllimport)) WINBOOL  SetCommState(HANDLE hFile,LPDCB lpDCB);
  __attribute__((dllimport)) WINBOOL  SetCommTimeouts(HANDLE hFile,LPCOMMTIMEOUTS lpCommTimeouts);
  __attribute__((dllimport)) WINBOOL  TransmitCommChar(HANDLE hFile,char cChar);
  __attribute__((dllimport)) WINBOOL  WaitCommEvent(HANDLE hFile,LPDWORD lpEvtMask,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) DWORD  SetTapePosition(HANDLE hDevice,DWORD dwPositionMethod,DWORD dwPartition,DWORD dwOffsetLow,DWORD dwOffsetHigh,WINBOOL bImmediate);
  __attribute__((dllimport)) DWORD  GetTapePosition(HANDLE hDevice,DWORD dwPositionType,LPDWORD lpdwPartition,LPDWORD lpdwOffsetLow,LPDWORD lpdwOffsetHigh);
  __attribute__((dllimport)) DWORD  PrepareTape(HANDLE hDevice,DWORD dwOperation,WINBOOL bImmediate);
  __attribute__((dllimport)) DWORD  EraseTape(HANDLE hDevice,DWORD dwEraseType,WINBOOL bImmediate);
  __attribute__((dllimport)) DWORD  CreateTapePartition(HANDLE hDevice,DWORD dwPartitionMethod,DWORD dwCount,DWORD dwSize);
  __attribute__((dllimport)) DWORD  WriteTapemark(HANDLE hDevice,DWORD dwTapemarkType,DWORD dwTapemarkCount,WINBOOL bImmediate);
  __attribute__((dllimport)) DWORD  GetTapeStatus(HANDLE hDevice);
  __attribute__((dllimport)) DWORD  GetTapeParameters(HANDLE hDevice,DWORD dwOperation,LPDWORD lpdwSize,LPVOID lpTapeInformation);




  __attribute__((dllimport)) DWORD  SetTapeParameters(HANDLE hDevice,DWORD dwOperation,LPVOID lpTapeInformation);




  __attribute__((dllimport)) WINBOOL  Beep(DWORD dwFreq,DWORD dwDuration);
  __attribute__((dllimport)) int  MulDiv(int nNumber,int nNumerator,int nDenominator);
  __attribute__((dllimport)) void  GetSystemTime(LPSYSTEMTIME lpSystemTime);
  __attribute__((dllimport)) void  GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);
  __attribute__((dllimport)) WINBOOL  SetSystemTime(const SYSTEMTIME *lpSystemTime);
  __attribute__((dllimport)) void  GetLocalTime(LPSYSTEMTIME lpSystemTime);
  __attribute__((dllimport)) WINBOOL  SetLocalTime(const SYSTEMTIME *lpSystemTime);
  __attribute__((dllimport)) void  GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
  __attribute__((dllimport)) WINBOOL  SetSystemFileCacheSize(SIZE_T MinimumFileCacheSize,SIZE_T MaximumFileCacheSize,DWORD Flags);
  __attribute__((dllimport)) WINBOOL  GetSystemFileCacheSize(PSIZE_T lpMinimumFileCacheSize,PSIZE_T lpMaximumFileCacheSize,PDWORD lpFlags);
  __attribute__((dllimport)) WINBOOL  GetSystemRegistryQuota(PDWORD pdwQuotaAllowed,PDWORD pdwQuotaUsed);
  WINBOOL  GetSystemTimes(LPFILETIME lpIdleTime,LPFILETIME lpKernelTime,LPFILETIME lpUserTime);
  __attribute__((dllimport)) void  GetNativeSystemInfo(LPSYSTEM_INFO lpSystemInfo);
  __attribute__((dllimport)) WINBOOL  IsProcessorFeaturePresent(DWORD ProcessorFeature);

  typedef struct _TIME_ZONE_INFORMATION {
    LONG Bias;
    WCHAR StandardName[32];
    SYSTEMTIME StandardDate;
    LONG StandardBias;
    WCHAR DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG DaylightBias;
  } TIME_ZONE_INFORMATION,*PTIME_ZONE_INFORMATION,*LPTIME_ZONE_INFORMATION;







  __attribute__((dllimport)) WINBOOL  SystemTimeToTzSpecificLocalTime(LPTIME_ZONE_INFORMATION lpTimeZoneInformation,LPSYSTEMTIME lpUniversalTime,LPSYSTEMTIME lpLocalTime);
  __attribute__((dllimport)) WINBOOL  TzSpecificLocalTimeToSystemTime(LPTIME_ZONE_INFORMATION lpTimeZoneInformation,LPSYSTEMTIME lpLocalTime,LPSYSTEMTIME lpUniversalTime);
  __attribute__((dllimport)) DWORD  GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation);
  __attribute__((dllimport)) WINBOOL  SetTimeZoneInformation(const TIME_ZONE_INFORMATION *lpTimeZoneInformation);
  __attribute__((dllimport)) WINBOOL  SystemTimeToFileTime(const SYSTEMTIME *lpSystemTime,LPFILETIME lpFileTime);
  __attribute__((dllimport)) WINBOOL  FileTimeToLocalFileTime(const FILETIME *lpFileTime,LPFILETIME lpLocalFileTime);
  __attribute__((dllimport)) WINBOOL  LocalFileTimeToFileTime(const FILETIME *lpLocalFileTime,LPFILETIME lpFileTime);
  __attribute__((dllimport)) WINBOOL  FileTimeToSystemTime(const FILETIME *lpFileTime,LPSYSTEMTIME lpSystemTime);
  __attribute__((dllimport)) LONG  CompareFileTime(const FILETIME *lpFileTime1,const FILETIME *lpFileTime2);
  __attribute__((dllimport)) WINBOOL  FileTimeToDosDateTime(const FILETIME *lpFileTime,LPWORD lpFatDate,LPWORD lpFatTime);
  __attribute__((dllimport)) WINBOOL  DosDateTimeToFileTime(WORD wFatDate,WORD wFatTime,LPFILETIME lpFileTime);
  __attribute__((dllimport)) DWORD  GetTickCount(void);
  __attribute__((dllimport)) WINBOOL  SetSystemTimeAdjustment(DWORD dwTimeAdjustment,WINBOOL bTimeAdjustmentDisabled);
  __attribute__((dllimport)) WINBOOL  GetSystemTimeAdjustment(PDWORD lpTimeAdjustment,PDWORD lpTimeIncrement,PBOOL lpTimeAdjustmentDisabled);
  __attribute__((dllimport)) DWORD  FormatMessageA(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,LPSTR lpBuffer,DWORD nSize,va_list *Arguments);
  __attribute__((dllimport)) DWORD  FormatMessageW(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,LPWSTR lpBuffer,DWORD nSize,va_list *Arguments);
# 1518 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  CreatePipe(PHANDLE hReadPipe,PHANDLE hWritePipe,LPSECURITY_ATTRIBUTES lpPipeAttributes,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  ConnectNamedPipe(HANDLE hNamedPipe,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) WINBOOL  DisconnectNamedPipe(HANDLE hNamedPipe);
  __attribute__((dllimport)) WINBOOL  SetNamedPipeHandleState(HANDLE hNamedPipe,LPDWORD lpMode,LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout);
  __attribute__((dllimport)) WINBOOL  GetNamedPipeInfo(HANDLE hNamedPipe,LPDWORD lpFlags,LPDWORD lpOutBufferSize,LPDWORD lpInBufferSize,LPDWORD lpMaxInstances);
  __attribute__((dllimport)) WINBOOL  PeekNamedPipe(HANDLE hNamedPipe,LPVOID lpBuffer,DWORD nBufferSize,LPDWORD lpBytesRead,LPDWORD lpTotalBytesAvail,LPDWORD lpBytesLeftThisMessage);
  __attribute__((dllimport)) WINBOOL  TransactNamedPipe(HANDLE hNamedPipe,LPVOID lpInBuffer,DWORD nInBufferSize,LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) HANDLE  CreateMailslotA(LPCSTR lpName,DWORD nMaxMessageSize,DWORD lReadTimeout,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) HANDLE  CreateMailslotW(LPCWSTR lpName,DWORD nMaxMessageSize,DWORD lReadTimeout,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  GetMailslotInfo(HANDLE hMailslot,LPDWORD lpMaxMessageSize,LPDWORD lpNextSize,LPDWORD lpMessageCount,LPDWORD lpReadTimeout);
  __attribute__((dllimport)) WINBOOL  SetMailslotInfo(HANDLE hMailslot,DWORD lReadTimeout);
  __attribute__((dllimport)) LPVOID  MapViewOfFile(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,SIZE_T dwNumberOfBytesToMap);
  __attribute__((dllimport)) WINBOOL  FlushViewOfFile(LPCVOID lpBaseAddress,SIZE_T dwNumberOfBytesToFlush);
  __attribute__((dllimport)) WINBOOL  UnmapViewOfFile(LPCVOID lpBaseAddress);
  __attribute__((dllimport)) WINBOOL  EncryptFileA(LPCSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  EncryptFileW(LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  DecryptFileA(LPCSTR lpFileName,DWORD dwReserved);
  __attribute__((dllimport)) WINBOOL  DecryptFileW(LPCWSTR lpFileName,DWORD dwReserved);
# 1548 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  FileEncryptionStatusA(LPCSTR lpFileName,LPDWORD lpStatus);
  __attribute__((dllimport)) WINBOOL  FileEncryptionStatusW(LPCWSTR lpFileName,LPDWORD lpStatus);



  typedef DWORD ( *PFE_EXPORT_FUNC)(PBYTE pbData,PVOID pvCallbackContext,ULONG ulLength);
  typedef DWORD ( *PFE_IMPORT_FUNC)(PBYTE pbData,PVOID pvCallbackContext,PULONG ulLength);
# 1578 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) DWORD  OpenEncryptedFileRawA(LPCSTR lpFileName,ULONG ulFlags,PVOID *pvContext);
  __attribute__((dllimport)) DWORD  OpenEncryptedFileRawW(LPCWSTR lpFileName,ULONG ulFlags,PVOID *pvContext);
  __attribute__((dllimport)) DWORD  ReadEncryptedFileRaw(PFE_EXPORT_FUNC pfExportCallback,PVOID pvCallbackContext,PVOID pvContext);
  __attribute__((dllimport)) DWORD  WriteEncryptedFileRaw(PFE_IMPORT_FUNC pfImportCallback,PVOID pvCallbackContext,PVOID pvContext);
  __attribute__((dllimport)) void  CloseEncryptedFileRaw(PVOID pvContext);
  __attribute__((dllimport)) int  lstrcmpA(LPCSTR lpString1,LPCSTR lpString2);
  __attribute__((dllimport)) int  lstrcmpW(LPCWSTR lpString1,LPCWSTR lpString2);
  __attribute__((dllimport)) int  lstrcmpiA(LPCSTR lpString1,LPCSTR lpString2);
  __attribute__((dllimport)) int  lstrcmpiW(LPCWSTR lpString1,LPCWSTR lpString2);
  __attribute__((dllimport)) LPSTR  lstrcpynA(LPSTR lpString1,LPCSTR lpString2,int iMaxLength);
  __attribute__((dllimport)) LPWSTR  lstrcpynW(LPWSTR lpString1,LPCWSTR lpString2,int iMaxLength);
  __attribute__((dllimport)) LPSTR  lstrcpyA(LPSTR lpString1,LPCSTR lpString2);
  __attribute__((dllimport)) LPWSTR  lstrcpyW(LPWSTR lpString1,LPCWSTR lpString2);
  __attribute__((dllimport)) LPSTR  lstrcatA(LPSTR lpString1,LPCSTR lpString2);
  __attribute__((dllimport)) LPWSTR  lstrcatW(LPWSTR lpString1,LPCWSTR lpString2);
  __attribute__((dllimport)) int  lstrlenA(LPCSTR lpString);
  __attribute__((dllimport)) int  lstrlenW(LPCWSTR lpString);
  __attribute__((dllimport)) HFILE  OpenFile(LPCSTR lpFileName,LPOFSTRUCT lpReOpenBuff,UINT uStyle);
  __attribute__((dllimport)) HFILE  _lopen(LPCSTR lpPathName,int iReadWrite);
  __attribute__((dllimport)) HFILE  _lcreat(LPCSTR lpPathName,int iAttribute);
  __attribute__((dllimport)) UINT  _lread(HFILE hFile,LPVOID lpBuffer,UINT uBytes);
  __attribute__((dllimport)) UINT  _lwrite(HFILE hFile,LPCCH lpBuffer,UINT uBytes);
  __attribute__((dllimport)) long  _hread(HFILE hFile,LPVOID lpBuffer,long lBytes);
  __attribute__((dllimport)) long  _hwrite(HFILE hFile,LPCCH lpBuffer,long lBytes);
  __attribute__((dllimport)) HFILE  _lclose(HFILE hFile);
  __attribute__((dllimport)) LONG  _llseek(HFILE hFile,LONG lOffset,int iOrigin);
  __attribute__((dllimport)) WINBOOL  IsTextUnicode(const void *lpv,int iSize,LPINT lpiResult);



  __attribute__((dllimport)) DWORD  FlsAlloc(PFLS_CALLBACK_FUNCTION lpCallback);
  __attribute__((dllimport)) PVOID  FlsGetValue(DWORD dwFlsIndex);
  __attribute__((dllimport)) WINBOOL  FlsSetValue(DWORD dwFlsIndex,PVOID lpFlsData);
  __attribute__((dllimport)) WINBOOL  FlsFree(DWORD dwFlsIndex);



  __attribute__((dllimport)) DWORD  TlsAlloc(void);
  __attribute__((dllimport)) LPVOID  TlsGetValue(DWORD dwTlsIndex);
  __attribute__((dllimport)) WINBOOL  TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue);
  __attribute__((dllimport)) WINBOOL  TlsFree(DWORD dwTlsIndex);

  typedef void ( *LPOVERLAPPED_COMPLETION_ROUTINE)(DWORD dwErrorCode,DWORD dwNumberOfBytesTransfered,LPOVERLAPPED lpOverlapped);

  __attribute__((dllimport)) DWORD  SleepEx(DWORD dwMilliseconds,WINBOOL bAlertable);
  __attribute__((dllimport)) DWORD  WaitForSingleObjectEx(HANDLE hHandle,DWORD dwMilliseconds,WINBOOL bAlertable);
  __attribute__((dllimport)) DWORD  WaitForMultipleObjectsEx(DWORD nCount,const HANDLE *lpHandles,WINBOOL bWaitAll,DWORD dwMilliseconds,WINBOOL bAlertable);
  __attribute__((dllimport)) DWORD  SignalObjectAndWait(HANDLE hObjectToSignal,HANDLE hObjectToWaitOn,DWORD dwMilliseconds,WINBOOL bAlertable);
  __attribute__((dllimport)) WINBOOL  ReadFileEx(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPOVERLAPPED lpOverlapped,LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
  __attribute__((dllimport)) WINBOOL  WriteFileEx(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,LPOVERLAPPED lpOverlapped,LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
  __attribute__((dllimport)) WINBOOL  BackupRead(HANDLE hFile,LPBYTE lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,WINBOOL bAbort,WINBOOL bProcessSecurity,LPVOID *lpContext);
  __attribute__((dllimport)) WINBOOL  BackupSeek(HANDLE hFile,DWORD dwLowBytesToSeek,DWORD dwHighBytesToSeek,LPDWORD lpdwLowByteSeeked,LPDWORD lpdwHighByteSeeked,LPVOID *lpContext);
  __attribute__((dllimport)) WINBOOL  BackupWrite(HANDLE hFile,LPBYTE lpBuffer,DWORD nNumberOfBytesToWrite,LPDWORD lpNumberOfBytesWritten,WINBOOL bAbort,WINBOOL bProcessSecurity,LPVOID *lpContext);

  typedef struct _WIN32_STREAM_ID {
    DWORD dwStreamId;
    DWORD dwStreamAttributes;
    LARGE_INTEGER Size;
    DWORD dwStreamNameSize;
    WCHAR cStreamName[1];
  } WIN32_STREAM_ID,*LPWIN32_STREAM_ID;
# 1657 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  ReadFileScatter(HANDLE hFile,FILE_SEGMENT_ELEMENT aSegmentArray[],DWORD nNumberOfBytesToRead,LPDWORD lpReserved,LPOVERLAPPED lpOverlapped);
  __attribute__((dllimport)) WINBOOL  WriteFileGather(HANDLE hFile,FILE_SEGMENT_ELEMENT aSegmentArray[],DWORD nNumberOfBytesToWrite,LPDWORD lpReserved,LPOVERLAPPED lpOverlapped);
# 1672 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _STARTUPINFOA {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
  } STARTUPINFOA,*LPSTARTUPINFOA;

  typedef struct _STARTUPINFOW {
    DWORD cb;
    LPWSTR lpReserved;
    LPWSTR lpDesktop;
    LPWSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
  } STARTUPINFOW,*LPSTARTUPINFOW;





  typedef STARTUPINFOA STARTUPINFO;
  typedef LPSTARTUPINFOA LPSTARTUPINFO;




  typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    CHAR cFileName[260];
    CHAR cAlternateFileName[14];
  } WIN32_FIND_DATAA,*PWIN32_FIND_DATAA,*LPWIN32_FIND_DATAA;

  typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    WCHAR cFileName[260];
    WCHAR cAlternateFileName[14];
  } WIN32_FIND_DATAW,*PWIN32_FIND_DATAW,*LPWIN32_FIND_DATAW;






  typedef WIN32_FIND_DATAA WIN32_FIND_DATA;
  typedef PWIN32_FIND_DATAA PWIN32_FIND_DATA;
  typedef LPWIN32_FIND_DATAA LPWIN32_FIND_DATA;


  typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
  } WIN32_FILE_ATTRIBUTE_DATA,*LPWIN32_FILE_ATTRIBUTE_DATA;
# 1785 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) HANDLE  CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes,WINBOOL bInitialOwner,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateMutexW(LPSECURITY_ATTRIBUTES lpMutexAttributes,WINBOOL bInitialOwner,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenMutexA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenMutexW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes,WINBOOL bManualReset,WINBOOL bInitialState,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateEventW(LPSECURITY_ATTRIBUTES lpEventAttributes,WINBOOL bManualReset,WINBOOL bInitialState,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenEventA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenEventW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateSemaphoreA(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,LONG lInitialCount,LONG lMaximumCount,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateSemaphoreW(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,LONG lInitialCount,LONG lMaximumCount,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenSemaphoreA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenSemaphoreW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpName);

  typedef void ( *PTIMERAPCROUTINE)(LPVOID lpArgToCompletionRoutine,DWORD dwTimerLowValue,DWORD dwTimerHighValue);
# 1822 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) HANDLE  CreateWaitableTimerA(LPSECURITY_ATTRIBUTES lpTimerAttributes,WINBOOL bManualReset,LPCSTR lpTimerName);
  __attribute__((dllimport)) HANDLE  CreateWaitableTimerW(LPSECURITY_ATTRIBUTES lpTimerAttributes,WINBOOL bManualReset,LPCWSTR lpTimerName);
  __attribute__((dllimport)) HANDLE  OpenWaitableTimerA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpTimerName);
  __attribute__((dllimport)) HANDLE  OpenWaitableTimerW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpTimerName);
  __attribute__((dllimport)) WINBOOL  SetWaitableTimer(HANDLE hTimer,const LARGE_INTEGER *lpDueTime,LONG lPeriod,PTIMERAPCROUTINE pfnCompletionRoutine,LPVOID lpArgToCompletionRoutine,WINBOOL fResume);
  __attribute__((dllimport)) WINBOOL  CancelWaitableTimer(HANDLE hTimer);
  __attribute__((dllimport)) HANDLE  CreateFileMappingA(HANDLE hFile,LPSECURITY_ATTRIBUTES lpFileMappingAttributes,DWORD flProtect,DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateFileMappingW(HANDLE hFile,LPSECURITY_ATTRIBUTES lpFileMappingAttributes,DWORD flProtect,DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenFileMappingA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenFileMappingW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpName);
  __attribute__((dllimport)) DWORD  GetLogicalDriveStringsA(DWORD nBufferLength,LPSTR lpBuffer);
  __attribute__((dllimport)) DWORD  GetLogicalDriveStringsW(DWORD nBufferLength,LPWSTR lpBuffer);

  typedef enum _MEMORY_RESOURCE_NOTIFICATION_TYPE {
    LowMemoryResourceNotification,HighMemoryResourceNotification
  } MEMORY_RESOURCE_NOTIFICATION_TYPE;

  __attribute__((dllimport)) HANDLE  CreateMemoryResourceNotification(MEMORY_RESOURCE_NOTIFICATION_TYPE NotificationType);
  __attribute__((dllimport)) WINBOOL  QueryMemoryResourceNotification(HANDLE ResourceNotificationHandle,PBOOL ResourceState);
  __attribute__((dllimport)) HMODULE  LoadLibraryA(LPCSTR lpLibFileName);
  __attribute__((dllimport)) HMODULE  LoadLibraryW(LPCWSTR lpLibFileName);
  __attribute__((dllimport)) HMODULE  LoadLibraryExA(LPCSTR lpLibFileName,HANDLE hFile,DWORD dwFlags);
  __attribute__((dllimport)) HMODULE  LoadLibraryExW(LPCWSTR lpLibFileName,HANDLE hFile,DWORD dwFlags);
# 1853 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) DWORD  GetModuleFileNameA(HMODULE hModule,LPCH lpFilename,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetModuleFileNameW(HMODULE hModule,LPWCH lpFilename,DWORD nSize);
  __attribute__((dllimport)) HMODULE  GetModuleHandleA(LPCSTR lpModuleName);
  __attribute__((dllimport)) HMODULE  GetModuleHandleW(LPCWSTR lpModuleName);






  typedef WINBOOL ( *PGET_MODULE_HANDLE_EXA)(DWORD dwFlags,LPCSTR lpModuleName,HMODULE *phModule);
  typedef WINBOOL ( *PGET_MODULE_HANDLE_EXW)(DWORD dwFlags,LPCWSTR lpModuleName,HMODULE *phModule);
# 1874 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  GetModuleHandleExA(DWORD dwFlags,LPCSTR lpModuleName,HMODULE *phModule);
  __attribute__((dllimport)) WINBOOL  GetModuleHandleExW(DWORD dwFlags,LPCWSTR lpModuleName,HMODULE *phModule);
# 1908 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  NeedCurrentDirectoryForExePathA(LPCSTR ExeName);
  __attribute__((dllimport)) WINBOOL  NeedCurrentDirectoryForExePathW(LPCWSTR ExeName);
  __attribute__((dllimport)) WINBOOL  CreateProcessA(LPCSTR lpApplicationName,LPSTR lpCommandLine,LPSECURITY_ATTRIBUTES lpProcessAttributes,LPSECURITY_ATTRIBUTES lpThreadAttributes,WINBOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCSTR lpCurrentDirectory,LPSTARTUPINFOA lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);
  __attribute__((dllimport)) WINBOOL  CreateProcessW(LPCWSTR lpApplicationName,LPWSTR lpCommandLine,LPSECURITY_ATTRIBUTES lpProcessAttributes,LPSECURITY_ATTRIBUTES lpThreadAttributes,WINBOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,LPSTARTUPINFOW lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);
  __attribute__((dllimport)) DWORD  AddLocalAlternateComputerNameA(LPCSTR lpDnsFQHostname,ULONG ulFlags);
  __attribute__((dllimport)) DWORD  AddLocalAlternateComputerNameW(LPCWSTR lpDnsFQHostname,ULONG ulFlags);
  __attribute__((dllimport)) WINBOOL  SetProcessShutdownParameters(DWORD dwLevel,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  GetProcessShutdownParameters(LPDWORD lpdwLevel,LPDWORD lpdwFlags);
  __attribute__((dllimport)) DWORD  GetProcessVersion(DWORD ProcessId);
  __attribute__((dllimport)) void  FatalAppExitA(UINT uAction,LPCSTR lpMessageText);
  __attribute__((dllimport)) void  FatalAppExitW(UINT uAction,LPCWSTR lpMessageText);
  __attribute__((dllimport)) void  GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo);
  __attribute__((dllimport)) void  GetStartupInfoW(LPSTARTUPINFOW lpStartupInfo);
  __attribute__((dllimport)) LPSTR  GetCommandLineA(void);
  __attribute__((dllimport)) LPWSTR  GetCommandLineW(void);
  __attribute__((dllimport)) DWORD  GetEnvironmentVariableA(LPCSTR lpName,LPSTR lpBuffer,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetEnvironmentVariableW(LPCWSTR lpName,LPWSTR lpBuffer,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetEnvironmentVariableA(LPCSTR lpName,LPCSTR lpValue);
  __attribute__((dllimport)) WINBOOL  SetEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpValue);
  __attribute__((dllimport)) DWORD  ExpandEnvironmentStringsA(LPCSTR lpSrc,LPSTR lpDst,DWORD nSize);
  __attribute__((dllimport)) DWORD  ExpandEnvironmentStringsW(LPCWSTR lpSrc,LPWSTR lpDst,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetFirmwareEnvironmentVariableA(LPCSTR lpName,LPCSTR lpGuid,PVOID pBuffer,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetFirmwareEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpGuid,PVOID pBuffer,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetFirmwareEnvironmentVariableA(LPCSTR lpName,LPCSTR lpGuid,PVOID pValue,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetFirmwareEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpGuid,PVOID pValue,DWORD nSize);
  __attribute__((dllimport)) void  OutputDebugStringA(LPCSTR lpOutputString);
  __attribute__((dllimport)) void  OutputDebugStringW(LPCWSTR lpOutputString);
  __attribute__((dllimport)) HRSRC  FindResourceA(HMODULE hModule,LPCSTR lpName,LPCSTR lpType);
  __attribute__((dllimport)) HRSRC  FindResourceW(HMODULE hModule,LPCWSTR lpName,LPCWSTR lpType);
  __attribute__((dllimport)) HRSRC  FindResourceExA(HMODULE hModule,LPCSTR lpType,LPCSTR lpName,WORD wLanguage);
  __attribute__((dllimport)) HRSRC  FindResourceExW(HMODULE hModule,LPCWSTR lpType,LPCWSTR lpName,WORD wLanguage);
# 2014 "c:/program files/tcc/include/winapi/winbase.h"
  typedef WINBOOL ( *ENUMRESTYPEPROCA)(HMODULE hModule,LPSTR lpType,LONG_PTR lParam);
  typedef WINBOOL ( *ENUMRESTYPEPROCW)(HMODULE hModule,LPWSTR lpType,LONG_PTR lParam);
  typedef WINBOOL ( *ENUMRESNAMEPROCA)(HMODULE hModule,LPCSTR lpType,LPSTR lpName,LONG_PTR lParam);
  typedef WINBOOL ( *ENUMRESNAMEPROCW)(HMODULE hModule,LPCWSTR lpType,LPWSTR lpName,LONG_PTR lParam);
  typedef WINBOOL ( *ENUMRESLANGPROCA)(HMODULE hModule,LPCSTR lpType,LPCSTR lpName,WORD wLanguage,LONG_PTR lParam);
  typedef WINBOOL ( *ENUMRESLANGPROCW)(HMODULE hModule,LPCWSTR lpType,LPCWSTR lpName,WORD wLanguage,LONG_PTR lParam);

  __attribute__((dllimport)) WINBOOL  EnumResourceTypesA(HMODULE hModule,ENUMRESTYPEPROCA lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) WINBOOL  EnumResourceTypesW(HMODULE hModule,ENUMRESTYPEPROCW lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) WINBOOL  EnumResourceNamesA(HMODULE hModule,LPCSTR lpType,ENUMRESNAMEPROCA lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) WINBOOL  EnumResourceNamesW(HMODULE hModule,LPCWSTR lpType,ENUMRESNAMEPROCW lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) WINBOOL  EnumResourceLanguagesA(HMODULE hModule,LPCSTR lpType,LPCSTR lpName,ENUMRESLANGPROCA lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) WINBOOL  EnumResourceLanguagesW(HMODULE hModule,LPCWSTR lpType,LPCWSTR lpName,ENUMRESLANGPROCW lpEnumFunc,LONG_PTR lParam);
  __attribute__((dllimport)) HANDLE  BeginUpdateResourceA(LPCSTR pFileName,WINBOOL bDeleteExistingResources);
  __attribute__((dllimport)) HANDLE  BeginUpdateResourceW(LPCWSTR pFileName,WINBOOL bDeleteExistingResources);
  __attribute__((dllimport)) WINBOOL  UpdateResourceA(HANDLE hUpdate,LPCSTR lpType,LPCSTR lpName,WORD wLanguage,LPVOID lpData,DWORD cb);
  __attribute__((dllimport)) WINBOOL  UpdateResourceW(HANDLE hUpdate,LPCWSTR lpType,LPCWSTR lpName,WORD wLanguage,LPVOID lpData,DWORD cb);
  __attribute__((dllimport)) WINBOOL  EndUpdateResourceA(HANDLE hUpdate,WINBOOL fDiscard);
  __attribute__((dllimport)) WINBOOL  EndUpdateResourceW(HANDLE hUpdate,WINBOOL fDiscard);
  __attribute__((dllimport)) ATOM  GlobalAddAtomA(LPCSTR lpString);
  __attribute__((dllimport)) ATOM  GlobalAddAtomW(LPCWSTR lpString);
  __attribute__((dllimport)) ATOM  GlobalFindAtomA(LPCSTR lpString);
  __attribute__((dllimport)) ATOM  GlobalFindAtomW(LPCWSTR lpString);
  __attribute__((dllimport)) UINT  GlobalGetAtomNameA(ATOM nAtom,LPSTR lpBuffer,int nSize);
  __attribute__((dllimport)) UINT  GlobalGetAtomNameW(ATOM nAtom,LPWSTR lpBuffer,int nSize);
  __attribute__((dllimport)) ATOM  AddAtomA(LPCSTR lpString);
  __attribute__((dllimport)) ATOM  AddAtomW(LPCWSTR lpString);
  __attribute__((dllimport)) ATOM  FindAtomA(LPCSTR lpString);
  __attribute__((dllimport)) ATOM  FindAtomW(LPCWSTR lpString);
  __attribute__((dllimport)) UINT  GetAtomNameA(ATOM nAtom,LPSTR lpBuffer,int nSize);
  __attribute__((dllimport)) UINT  GetAtomNameW(ATOM nAtom,LPWSTR lpBuffer,int nSize);
  __attribute__((dllimport)) UINT  GetProfileIntA(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault);
  __attribute__((dllimport)) UINT  GetProfileIntW(LPCWSTR lpAppName,LPCWSTR lpKeyName,INT nDefault);
  __attribute__((dllimport)) DWORD  GetProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpDefault,LPWSTR lpReturnedString,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  WriteProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString);
  __attribute__((dllimport)) WINBOOL  WriteProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpString);
  __attribute__((dllimport)) DWORD  GetProfileSectionA(LPCSTR lpAppName,LPSTR lpReturnedString,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetProfileSectionW(LPCWSTR lpAppName,LPWSTR lpReturnedString,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  WriteProfileSectionA(LPCSTR lpAppName,LPCSTR lpString);
  __attribute__((dllimport)) WINBOOL  WriteProfileSectionW(LPCWSTR lpAppName,LPCWSTR lpString);
  __attribute__((dllimport)) UINT  GetPrivateProfileIntA(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault,LPCSTR lpFileName);
  __attribute__((dllimport)) UINT  GetPrivateProfileIntW(LPCWSTR lpAppName,LPCWSTR lpKeyName,INT nDefault,LPCWSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize,LPCSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpDefault,LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString,LPCSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpString,LPCWSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileSectionA(LPCSTR lpAppName,LPSTR lpReturnedString,DWORD nSize,LPCSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileSectionW(LPCWSTR lpAppName,LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileSectionA(LPCSTR lpAppName,LPCSTR lpString,LPCSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileSectionW(LPCWSTR lpAppName,LPCWSTR lpString,LPCWSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileSectionNamesA(LPSTR lpszReturnBuffer,DWORD nSize,LPCSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetPrivateProfileSectionNamesW(LPWSTR lpszReturnBuffer,DWORD nSize,LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  GetPrivateProfileStructA(LPCSTR lpszSection,LPCSTR lpszKey,LPVOID lpStruct,UINT uSizeStruct,LPCSTR szFile);
  __attribute__((dllimport)) WINBOOL  GetPrivateProfileStructW(LPCWSTR lpszSection,LPCWSTR lpszKey,LPVOID lpStruct,UINT uSizeStruct,LPCWSTR szFile);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileStructA(LPCSTR lpszSection,LPCSTR lpszKey,LPVOID lpStruct,UINT uSizeStruct,LPCSTR szFile);
  __attribute__((dllimport)) WINBOOL  WritePrivateProfileStructW(LPCWSTR lpszSection,LPCWSTR lpszKey,LPVOID lpStruct,UINT uSizeStruct,LPCWSTR szFile);
  __attribute__((dllimport)) UINT  GetDriveTypeA(LPCSTR lpRootPathName);
  __attribute__((dllimport)) UINT  GetDriveTypeW(LPCWSTR lpRootPathName);
  __attribute__((dllimport)) UINT  GetSystemDirectoryA(LPSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) UINT  GetSystemDirectoryW(LPWSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) DWORD  GetTempPathA(DWORD nBufferLength,LPSTR lpBuffer);
  __attribute__((dllimport)) DWORD  GetTempPathW(DWORD nBufferLength,LPWSTR lpBuffer);
  __attribute__((dllimport)) UINT  GetTempFileNameA(LPCSTR lpPathName,LPCSTR lpPrefixString,UINT uUnique,LPSTR lpTempFileName);
  __attribute__((dllimport)) UINT  GetTempFileNameW(LPCWSTR lpPathName,LPCWSTR lpPrefixString,UINT uUnique,LPWSTR lpTempFileName);
  __attribute__((dllimport)) UINT  GetWindowsDirectoryA(LPSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) UINT  GetWindowsDirectoryW(LPWSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) UINT  GetSystemWindowsDirectoryA(LPSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) UINT  GetSystemWindowsDirectoryW(LPWSTR lpBuffer,UINT uSize);
# 2091 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) UINT  GetSystemWow64DirectoryA(LPSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) UINT  GetSystemWow64DirectoryW(LPWSTR lpBuffer,UINT uSize);
  __attribute__((dllimport)) BOOLEAN  Wow64EnableWow64FsRedirection(BOOLEAN Wow64FsEnableRedirection);
  __attribute__((dllimport)) WINBOOL  Wow64DisableWow64FsRedirection(PVOID *OldValue);
  __attribute__((dllimport)) WINBOOL  Wow64RevertWow64FsRedirection(PVOID OlValue);

  typedef UINT ( *PGET_SYSTEM_WOW64_DIRECTORY_A)(LPSTR lpBuffer,UINT uSize);
  typedef UINT ( *PGET_SYSTEM_WOW64_DIRECTORY_W)(LPWSTR lpBuffer,UINT uSize);
# 2152 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  SetCurrentDirectoryA(LPCSTR lpPathName);
  __attribute__((dllimport)) WINBOOL  SetCurrentDirectoryW(LPCWSTR lpPathName);
  __attribute__((dllimport)) DWORD  GetCurrentDirectoryA(DWORD nBufferLength,LPSTR lpBuffer);
  __attribute__((dllimport)) DWORD  GetCurrentDirectoryW(DWORD nBufferLength,LPWSTR lpBuffer);
  __attribute__((dllimport)) WINBOOL  SetDllDirectoryA(LPCSTR lpPathName);
  __attribute__((dllimport)) WINBOOL  SetDllDirectoryW(LPCWSTR lpPathName);
  __attribute__((dllimport)) DWORD  GetDllDirectoryA(DWORD nBufferLength,LPSTR lpBuffer);
  __attribute__((dllimport)) DWORD  GetDllDirectoryW(DWORD nBufferLength,LPWSTR lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetDiskFreeSpaceA(LPCSTR lpRootPathName,LPDWORD lpSectorsPerCluster,LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
  __attribute__((dllimport)) WINBOOL  GetDiskFreeSpaceW(LPCWSTR lpRootPathName,LPDWORD lpSectorsPerCluster,LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
  __attribute__((dllimport)) WINBOOL  GetDiskFreeSpaceExA(LPCSTR lpDirectoryName,PULARGE_INTEGER lpFreeBytesAvailableToCaller,PULARGE_INTEGER lpTotalNumberOfBytes,PULARGE_INTEGER lpTotalNumberOfFreeBytes);
  __attribute__((dllimport)) WINBOOL  GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName,PULARGE_INTEGER lpFreeBytesAvailableToCaller,PULARGE_INTEGER lpTotalNumberOfBytes,PULARGE_INTEGER lpTotalNumberOfFreeBytes);
  __attribute__((dllimport)) WINBOOL  CreateDirectoryA(LPCSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  CreateDirectoryW(LPCWSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  CreateDirectoryExA(LPCSTR lpTemplateDirectory,LPCSTR lpNewDirectory,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  CreateDirectoryExW(LPCWSTR lpTemplateDirectory,LPCWSTR lpNewDirectory,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  RemoveDirectoryA(LPCSTR lpPathName);
  __attribute__((dllimport)) WINBOOL  RemoveDirectoryW(LPCWSTR lpPathName);
  __attribute__((dllimport)) DWORD  GetFullPathNameA(LPCSTR lpFileName,DWORD nBufferLength,LPSTR lpBuffer,LPSTR *lpFilePart);
  __attribute__((dllimport)) DWORD  GetFullPathNameW(LPCWSTR lpFileName,DWORD nBufferLength,LPWSTR lpBuffer,LPWSTR *lpFilePart);







  __attribute__((dllimport)) WINBOOL  DefineDosDeviceA(DWORD dwFlags,LPCSTR lpDeviceName,LPCSTR lpTargetPath);
  __attribute__((dllimport)) WINBOOL  DefineDosDeviceW(DWORD dwFlags,LPCWSTR lpDeviceName,LPCWSTR lpTargetPath);
  __attribute__((dllimport)) DWORD  QueryDosDeviceA(LPCSTR lpDeviceName,LPSTR lpTargetPath,DWORD ucchMax);
  __attribute__((dllimport)) DWORD  QueryDosDeviceW(LPCWSTR lpDeviceName,LPWSTR lpTargetPath,DWORD ucchMax);



  __attribute__((dllimport)) HANDLE  CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
  __attribute__((dllimport)) HANDLE  CreateFileW(LPCWSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
  __attribute__((dllimport)) HANDLE  ReOpenFile(HANDLE hOriginalFile,DWORD dwDesiredAccess,DWORD dwShareMode,DWORD dwFlagsAndAttributes);
  __attribute__((dllimport)) WINBOOL  SetFileAttributesA(LPCSTR lpFileName,DWORD dwFileAttributes);
  __attribute__((dllimport)) WINBOOL  SetFileAttributesW(LPCWSTR lpFileName,DWORD dwFileAttributes);
  __attribute__((dllimport)) DWORD  GetFileAttributesA(LPCSTR lpFileName);
  __attribute__((dllimport)) DWORD  GetFileAttributesW(LPCWSTR lpFileName);

  typedef enum _GET_FILEEX_INFO_LEVELS {
    GetFileExInfoStandard,GetFileExMaxInfoLevel
  } GET_FILEEX_INFO_LEVELS;
# 2210 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  GetFileAttributesExA(LPCSTR lpFileName,GET_FILEEX_INFO_LEVELS fInfoLevelId,LPVOID lpFileInformation);
  __attribute__((dllimport)) WINBOOL  GetFileAttributesExW(LPCWSTR lpFileName,GET_FILEEX_INFO_LEVELS fInfoLevelId,LPVOID lpFileInformation);
  __attribute__((dllimport)) DWORD  GetCompressedFileSizeA(LPCSTR lpFileName,LPDWORD lpFileSizeHigh);
  __attribute__((dllimport)) DWORD  GetCompressedFileSizeW(LPCWSTR lpFileName,LPDWORD lpFileSizeHigh);
  __attribute__((dllimport)) WINBOOL  DeleteFileA(LPCSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  DeleteFileW(LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  CheckNameLegalDOS8Dot3A(LPCSTR lpName,LPSTR lpOemName,DWORD OemNameSize,PBOOL pbNameContainsSpaces,PBOOL pbNameLegal);
  __attribute__((dllimport)) WINBOOL  CheckNameLegalDOS8Dot3W(LPCWSTR lpName,LPSTR lpOemName,DWORD OemNameSize,PBOOL pbNameContainsSpaces,PBOOL pbNameLegal);

  typedef enum _FINDEX_INFO_LEVELS {
    FindExInfoStandard,FindExInfoMaxInfoLevel
  } FINDEX_INFO_LEVELS;

  typedef enum _FINDEX_SEARCH_OPS {
    FindExSearchNameMatch,FindExSearchLimitToDirectories,FindExSearchLimitToDevices,FindExSearchMaxSearchOp
  } FINDEX_SEARCH_OPS;
# 2339 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) HANDLE  FindFirstFileExA(LPCSTR lpFileName,FINDEX_INFO_LEVELS fInfoLevelId,LPVOID lpFindFileData,FINDEX_SEARCH_OPS fSearchOp,LPVOID lpSearchFilter,DWORD dwAdditionalFlags);
  __attribute__((dllimport)) HANDLE  FindFirstFileExW(LPCWSTR lpFileName,FINDEX_INFO_LEVELS fInfoLevelId,LPVOID lpFindFileData,FINDEX_SEARCH_OPS fSearchOp,LPVOID lpSearchFilter,DWORD dwAdditionalFlags);
  __attribute__((dllimport)) HANDLE  FindFirstFileA(LPCSTR lpFileName,LPWIN32_FIND_DATAA lpFindFileData);
  __attribute__((dllimport)) HANDLE  FindFirstFileW(LPCWSTR lpFileName,LPWIN32_FIND_DATAW lpFindFileData);
  __attribute__((dllimport)) WINBOOL  FindNextFileA(HANDLE hFindFile,LPWIN32_FIND_DATAA lpFindFileData);
  __attribute__((dllimport)) WINBOOL  FindNextFileW(HANDLE hFindFile,LPWIN32_FIND_DATAW lpFindFileData);
  __attribute__((dllimport)) DWORD  SearchPathA(LPCSTR lpPath,LPCSTR lpFileName,LPCSTR lpExtension,DWORD nBufferLength,LPSTR lpBuffer,LPSTR *lpFilePart);
  __attribute__((dllimport)) DWORD  SearchPathW(LPCWSTR lpPath,LPCWSTR lpFileName,LPCWSTR lpExtension,DWORD nBufferLength,LPWSTR lpBuffer,LPWSTR *lpFilePart);
  __attribute__((dllimport)) WINBOOL  CopyFileA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,WINBOOL bFailIfExists);
  __attribute__((dllimport)) WINBOOL  CopyFileW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,WINBOOL bFailIfExists);

  typedef DWORD ( *LPPROGRESS_ROUTINE)(LARGE_INTEGER TotalFileSize,LARGE_INTEGER TotalBytesTransferred,LARGE_INTEGER StreamSize,LARGE_INTEGER StreamBytesTransferred,DWORD dwStreamNumber,DWORD dwCallbackReason,HANDLE hSourceFile,HANDLE hDestinationFile,LPVOID lpData);

  __attribute__((dllimport)) WINBOOL  CopyFileExA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,LPPROGRESS_ROUTINE lpProgressRoutine,LPVOID lpData,LPBOOL pbCancel,DWORD dwCopyFlags);
  __attribute__((dllimport)) WINBOOL  CopyFileExW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,LPPROGRESS_ROUTINE lpProgressRoutine,LPVOID lpData,LPBOOL pbCancel,DWORD dwCopyFlags);
  __attribute__((dllimport)) WINBOOL  MoveFileA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName);
  __attribute__((dllimport)) WINBOOL  MoveFileW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName);
  __attribute__((dllimport)) WINBOOL  MoveFileExA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  MoveFileExW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  MoveFileWithProgressA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,LPPROGRESS_ROUTINE lpProgressRoutine,LPVOID lpData,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  MoveFileWithProgressW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,LPPROGRESS_ROUTINE lpProgressRoutine,LPVOID lpData,DWORD dwFlags);
# 2368 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  ReplaceFileA(LPCSTR lpReplacedFileName,LPCSTR lpReplacementFileName,LPCSTR lpBackupFileName,DWORD dwReplaceFlags,LPVOID lpExclude,LPVOID lpReserved);
  __attribute__((dllimport)) WINBOOL  ReplaceFileW(LPCWSTR lpReplacedFileName,LPCWSTR lpReplacementFileName,LPCWSTR lpBackupFileName,DWORD dwReplaceFlags,LPVOID lpExclude,LPVOID lpReserved);
  __attribute__((dllimport)) WINBOOL  CreateHardLinkA(LPCSTR lpFileName,LPCSTR lpExistingFileName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  CreateHardLinkW(LPCWSTR lpFileName,LPCWSTR lpExistingFileName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);

  typedef enum _STREAM_INFO_LEVELS {
    FindStreamInfoStandard,FindStreamInfoMaxInfoLevel
  } STREAM_INFO_LEVELS;

  typedef struct _WIN32_FIND_STREAM_DATA {
    LARGE_INTEGER StreamSize;
    WCHAR cStreamName[260 + 36];
  } WIN32_FIND_STREAM_DATA,*PWIN32_FIND_STREAM_DATA;

  HANDLE  FindFirstStreamW(LPCWSTR lpFileName,STREAM_INFO_LEVELS InfoLevel,LPVOID lpFindStreamData,DWORD dwFlags);
  WINBOOL  FindNextStreamW(HANDLE hFindStream,LPVOID lpFindStreamData);
  __attribute__((dllimport)) HANDLE  CreateNamedPipeA(LPCSTR lpName,DWORD dwOpenMode,DWORD dwPipeMode,DWORD nMaxInstances,DWORD nOutBufferSize,DWORD nInBufferSize,DWORD nDefaultTimeOut,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) HANDLE  CreateNamedPipeW(LPCWSTR lpName,DWORD dwOpenMode,DWORD dwPipeMode,DWORD nMaxInstances,DWORD nOutBufferSize,DWORD nInBufferSize,DWORD nDefaultTimeOut,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) WINBOOL  GetNamedPipeHandleStateA(HANDLE hNamedPipe,LPDWORD lpState,LPDWORD lpCurInstances,LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout,LPSTR lpUserName,DWORD nMaxUserNameSize);
  __attribute__((dllimport)) WINBOOL  GetNamedPipeHandleStateW(HANDLE hNamedPipe,LPDWORD lpState,LPDWORD lpCurInstances,LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout,LPWSTR lpUserName,DWORD nMaxUserNameSize);
  __attribute__((dllimport)) WINBOOL  CallNamedPipeA(LPCSTR lpNamedPipeName,LPVOID lpInBuffer,DWORD nInBufferSize,LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,DWORD nTimeOut);
  __attribute__((dllimport)) WINBOOL  CallNamedPipeW(LPCWSTR lpNamedPipeName,LPVOID lpInBuffer,DWORD nInBufferSize,LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,DWORD nTimeOut);
  __attribute__((dllimport)) WINBOOL  WaitNamedPipeA(LPCSTR lpNamedPipeName,DWORD nTimeOut);
  __attribute__((dllimport)) WINBOOL  WaitNamedPipeW(LPCWSTR lpNamedPipeName,DWORD nTimeOut);
  __attribute__((dllimport)) WINBOOL  SetVolumeLabelA(LPCSTR lpRootPathName,LPCSTR lpVolumeName);
  __attribute__((dllimport)) WINBOOL  SetVolumeLabelW(LPCWSTR lpRootPathName,LPCWSTR lpVolumeName);
  __attribute__((dllimport)) void  SetFileApisToOEM(void);
  __attribute__((dllimport)) void  SetFileApisToANSI(void);
  __attribute__((dllimport)) WINBOOL  AreFileApisANSI(void);
  __attribute__((dllimport)) WINBOOL  GetVolumeInformationA(LPCSTR lpRootPathName,LPSTR lpVolumeNameBuffer,DWORD nVolumeNameSize,LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,LPDWORD lpFileSystemFlags,LPSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize);
  __attribute__((dllimport)) WINBOOL  GetVolumeInformationW(LPCWSTR lpRootPathName,LPWSTR lpVolumeNameBuffer,DWORD nVolumeNameSize,LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,LPDWORD lpFileSystemFlags,LPWSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize);
  __attribute__((dllimport)) WINBOOL  CancelIo(HANDLE hFile);
  __attribute__((dllimport)) WINBOOL  ClearEventLogA(HANDLE hEventLog,LPCSTR lpBackupFileName);
  __attribute__((dllimport)) WINBOOL  ClearEventLogW(HANDLE hEventLog,LPCWSTR lpBackupFileName);
  __attribute__((dllimport)) WINBOOL  BackupEventLogA(HANDLE hEventLog,LPCSTR lpBackupFileName);
  __attribute__((dllimport)) WINBOOL  BackupEventLogW(HANDLE hEventLog,LPCWSTR lpBackupFileName);
  __attribute__((dllimport)) WINBOOL  CloseEventLog(HANDLE hEventLog);
  __attribute__((dllimport)) WINBOOL  DeregisterEventSource(HANDLE hEventLog);
  __attribute__((dllimport)) WINBOOL  NotifyChangeEventLog(HANDLE hEventLog,HANDLE hEvent);
  __attribute__((dllimport)) WINBOOL  GetNumberOfEventLogRecords(HANDLE hEventLog,PDWORD NumberOfRecords);
  __attribute__((dllimport)) WINBOOL  GetOldestEventLogRecord(HANDLE hEventLog,PDWORD OldestRecord);
  __attribute__((dllimport)) HANDLE  OpenEventLogA(LPCSTR lpUNCServerName,LPCSTR lpSourceName);
  __attribute__((dllimport)) HANDLE  OpenEventLogW(LPCWSTR lpUNCServerName,LPCWSTR lpSourceName);
  __attribute__((dllimport)) HANDLE  RegisterEventSourceA(LPCSTR lpUNCServerName,LPCSTR lpSourceName);
  __attribute__((dllimport)) HANDLE  RegisterEventSourceW(LPCWSTR lpUNCServerName,LPCWSTR lpSourceName);
  __attribute__((dllimport)) HANDLE  OpenBackupEventLogA(LPCSTR lpUNCServerName,LPCSTR lpFileName);
  __attribute__((dllimport)) HANDLE  OpenBackupEventLogW(LPCWSTR lpUNCServerName,LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  ReadEventLogA(HANDLE hEventLog,DWORD dwReadFlags,DWORD dwRecordOffset,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,DWORD *pnBytesRead,DWORD *pnMinNumberOfBytesNeeded);
  __attribute__((dllimport)) WINBOOL  ReadEventLogW(HANDLE hEventLog,DWORD dwReadFlags,DWORD dwRecordOffset,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,DWORD *pnBytesRead,DWORD *pnMinNumberOfBytesNeeded);
  __attribute__((dllimport)) WINBOOL  ReportEventA(HANDLE hEventLog,WORD wType,WORD wCategory,DWORD dwEventID,PSID lpUserSid,WORD wNumStrings,DWORD dwDataSize,LPCSTR *lpStrings,LPVOID lpRawData);
  __attribute__((dllimport)) WINBOOL  ReportEventW(HANDLE hEventLog,WORD wType,WORD wCategory,DWORD dwEventID,PSID lpUserSid,WORD wNumStrings,DWORD dwDataSize,LPCWSTR *lpStrings,LPVOID lpRawData);



  typedef struct _EVENTLOG_FULL_INFORMATION {
    DWORD dwFull;
  } EVENTLOG_FULL_INFORMATION,*LPEVENTLOG_FULL_INFORMATION;

  __attribute__((dllimport)) WINBOOL  GetEventLogInformation(HANDLE hEventLog,DWORD dwInfoLevel,LPVOID lpBuffer,DWORD cbBufSize,LPDWORD pcbBytesNeeded);
  __attribute__((dllimport)) WINBOOL  DuplicateToken(HANDLE ExistingTokenHandle,SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,PHANDLE DuplicateTokenHandle);
  __attribute__((dllimport)) WINBOOL  GetKernelObjectSecurity(HANDLE Handle,SECURITY_INFORMATION RequestedInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
  __attribute__((dllimport)) WINBOOL  ImpersonateNamedPipeClient(HANDLE hNamedPipe);
  __attribute__((dllimport)) WINBOOL  ImpersonateSelf(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel);
  __attribute__((dllimport)) WINBOOL  RevertToSelf(void);
  __attribute__((dllimport)) WINBOOL  SetThreadToken (PHANDLE Thread,HANDLE Token);
  __attribute__((dllimport)) WINBOOL  AccessCheck(PSECURITY_DESCRIPTOR pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,PGENERIC_MAPPING GenericMapping,PPRIVILEGE_SET PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccess,LPBOOL AccessStatus);
  __attribute__((dllimport)) WINBOOL  AccessCheckByType(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID PrincipalSelfSid,HANDLE ClientToken,DWORD DesiredAccess,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,PPRIVILEGE_SET PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccess,LPBOOL AccessStatus);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeResultList(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID PrincipalSelfSid,HANDLE ClientToken,DWORD DesiredAccess,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,PPRIVILEGE_SET PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccessList,LPDWORD AccessStatusList);
  __attribute__((dllimport)) WINBOOL  OpenProcessToken(HANDLE ProcessHandle,DWORD DesiredAccess,PHANDLE TokenHandle);
  __attribute__((dllimport)) WINBOOL  OpenThreadToken(HANDLE ThreadHandle,DWORD DesiredAccess,WINBOOL OpenAsSelf,PHANDLE TokenHandle);
  __attribute__((dllimport)) WINBOOL  GetTokenInformation(HANDLE TokenHandle,TOKEN_INFORMATION_CLASS TokenInformationClass,LPVOID TokenInformation,DWORD TokenInformationLength,PDWORD ReturnLength);
  __attribute__((dllimport)) WINBOOL  SetTokenInformation(HANDLE TokenHandle,TOKEN_INFORMATION_CLASS TokenInformationClass,LPVOID TokenInformation,DWORD TokenInformationLength);
  __attribute__((dllimport)) WINBOOL  AdjustTokenPrivileges(HANDLE TokenHandle,WINBOOL DisableAllPrivileges,PTOKEN_PRIVILEGES NewState,DWORD BufferLength,PTOKEN_PRIVILEGES PreviousState,PDWORD ReturnLength);
  __attribute__((dllimport)) WINBOOL  AdjustTokenGroups(HANDLE TokenHandle,WINBOOL ResetToDefault,PTOKEN_GROUPS NewState,DWORD BufferLength,PTOKEN_GROUPS PreviousState,PDWORD ReturnLength);
  __attribute__((dllimport)) WINBOOL  PrivilegeCheck(HANDLE ClientToken,PPRIVILEGE_SET RequiredPrivileges,LPBOOL pfResult);
  __attribute__((dllimport)) WINBOOL  AccessCheckAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPSTR ObjectTypeName,LPSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,DWORD DesiredAccess,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPWSTR ObjectTypeName,LPWSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,DWORD DesiredAccess,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPCSTR ObjectTypeName,LPCSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPCWSTR ObjectTypeName,LPCWSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeResultListAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPCSTR ObjectTypeName,LPCSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeResultListAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPCWSTR ObjectTypeName,LPCWSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeResultListAndAuditAlarmByHandleA(LPCSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,LPCSTR ObjectTypeName,LPCSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  AccessCheckByTypeResultListAndAuditAlarmByHandleW(LPCWSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,LPCWSTR ObjectTypeName,LPCWSTR ObjectName,PSECURITY_DESCRIPTOR SecurityDescriptor,PSID PrincipalSelfSid,DWORD DesiredAccess,AUDIT_EVENT_TYPE AuditType,DWORD Flags,POBJECT_TYPE_LIST ObjectTypeList,DWORD ObjectTypeListLength,PGENERIC_MAPPING GenericMapping,WINBOOL ObjectCreation,LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectOpenAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPSTR ObjectTypeName,LPSTR ObjectName,PSECURITY_DESCRIPTOR pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,DWORD GrantedAccess,PPRIVILEGE_SET Privileges,WINBOOL ObjectCreation,WINBOOL AccessGranted,LPBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectOpenAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPWSTR ObjectTypeName,LPWSTR ObjectName,PSECURITY_DESCRIPTOR pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,DWORD GrantedAccess,PPRIVILEGE_SET Privileges,WINBOOL ObjectCreation,WINBOOL AccessGranted,LPBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectPrivilegeAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,DWORD DesiredAccess,PPRIVILEGE_SET Privileges,WINBOOL AccessGranted);
  __attribute__((dllimport)) WINBOOL  ObjectPrivilegeAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,DWORD DesiredAccess,PPRIVILEGE_SET Privileges,WINBOOL AccessGranted);
  __attribute__((dllimport)) WINBOOL  ObjectCloseAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,WINBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectCloseAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,WINBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectDeleteAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,WINBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  ObjectDeleteAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,WINBOOL GenerateOnClose);
  __attribute__((dllimport)) WINBOOL  PrivilegedServiceAuditAlarmA(LPCSTR SubsystemName,LPCSTR ServiceName,HANDLE ClientToken,PPRIVILEGE_SET Privileges,WINBOOL AccessGranted);
  __attribute__((dllimport)) WINBOOL  PrivilegedServiceAuditAlarmW(LPCWSTR SubsystemName,LPCWSTR ServiceName,HANDLE ClientToken,PPRIVILEGE_SET Privileges,WINBOOL AccessGranted);
  __attribute__((dllimport)) WINBOOL  IsWellKnownSid(PSID pSid,WELL_KNOWN_SID_TYPE WellKnownSidType);
  __attribute__((dllimport)) WINBOOL  CreateWellKnownSid(WELL_KNOWN_SID_TYPE WellKnownSidType,PSID DomainSid,PSID pSid,DWORD *cbSid);
  __attribute__((dllimport)) WINBOOL  EqualDomainSid(PSID pSid1,PSID pSid2,WINBOOL *pfEqual);
  __attribute__((dllimport)) WINBOOL  GetWindowsAccountDomainSid(PSID pSid,PSID pDomainSid,DWORD *cbDomainSid);
  __attribute__((dllimport)) WINBOOL  IsValidSid(PSID pSid);
  __attribute__((dllimport)) WINBOOL  EqualSid(PSID pSid1,PSID pSid2);
  __attribute__((dllimport)) WINBOOL  EqualPrefixSid(PSID pSid1,PSID pSid2);
  __attribute__((dllimport)) DWORD  GetSidLengthRequired (UCHAR nSubAuthorityCount);
  __attribute__((dllimport)) WINBOOL  AllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,BYTE nSubAuthorityCount,DWORD nSubAuthority0,DWORD nSubAuthority1,DWORD nSubAuthority2,DWORD nSubAuthority3,DWORD nSubAuthority4,DWORD nSubAuthority5,DWORD nSubAuthority6,DWORD nSubAuthority7,PSID *pSid);
  __attribute__((dllimport)) PVOID  FreeSid(PSID pSid);
  __attribute__((dllimport)) WINBOOL  InitializeSid(PSID Sid,PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,BYTE nSubAuthorityCount);
  __attribute__((dllimport)) PSID_IDENTIFIER_AUTHORITY  GetSidIdentifierAuthority(PSID pSid);
  __attribute__((dllimport)) PDWORD  GetSidSubAuthority(PSID pSid,DWORD nSubAuthority);
  __attribute__((dllimport)) PUCHAR  GetSidSubAuthorityCount(PSID pSid);
  __attribute__((dllimport)) DWORD  GetLengthSid(PSID pSid);
  __attribute__((dllimport)) WINBOOL  CopySid(DWORD nDestinationSidLength,PSID pDestinationSid,PSID pSourceSid);
  __attribute__((dllimport)) WINBOOL  AreAllAccessesGranted(DWORD GrantedAccess,DWORD DesiredAccess);
  __attribute__((dllimport)) WINBOOL  AreAnyAccessesGranted(DWORD GrantedAccess,DWORD DesiredAccess);
  __attribute__((dllimport)) void  MapGenericMask(PDWORD AccessMask,PGENERIC_MAPPING GenericMapping);
  __attribute__((dllimport)) WINBOOL  IsValidAcl(PACL pAcl);
  __attribute__((dllimport)) WINBOOL  InitializeAcl(PACL pAcl,DWORD nAclLength,DWORD dwAclRevision);
  __attribute__((dllimport)) WINBOOL  GetAclInformation(PACL pAcl,LPVOID pAclInformation,DWORD nAclInformationLength,ACL_INFORMATION_CLASS dwAclInformationClass);
  __attribute__((dllimport)) WINBOOL  SetAclInformation(PACL pAcl,LPVOID pAclInformation,DWORD nAclInformationLength,ACL_INFORMATION_CLASS dwAclInformationClass);
  __attribute__((dllimport)) WINBOOL  AddAce(PACL pAcl,DWORD dwAceRevision,DWORD dwStartingAceIndex,LPVOID pAceList,DWORD nAceListLength);
  __attribute__((dllimport)) WINBOOL  DeleteAce(PACL pAcl,DWORD dwAceIndex);
  __attribute__((dllimport)) WINBOOL  GetAce(PACL pAcl,DWORD dwAceIndex,LPVOID *pAce);
  __attribute__((dllimport)) WINBOOL  AddAccessAllowedAce(PACL pAcl,DWORD dwAceRevision,DWORD AccessMask,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAccessAllowedAceEx(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAccessDeniedAce(PACL pAcl,DWORD dwAceRevision,DWORD AccessMask,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAccessDeniedAceEx(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAuditAccessAce(PACL pAcl,DWORD dwAceRevision,DWORD dwAccessMask,PSID pSid,WINBOOL bAuditSuccess,WINBOOL bAuditFailure);
  __attribute__((dllimport)) WINBOOL  AddAuditAccessAceEx(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD dwAccessMask,PSID pSid,WINBOOL bAuditSuccess,WINBOOL bAuditFailure);
  __attribute__((dllimport)) WINBOOL  AddAccessAllowedObjectAce(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,GUID *ObjectTypeGuid,GUID *InheritedObjectTypeGuid,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAccessDeniedObjectAce(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,GUID *ObjectTypeGuid,GUID *InheritedObjectTypeGuid,PSID pSid);
  __attribute__((dllimport)) WINBOOL  AddAuditAccessObjectAce(PACL pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,GUID *ObjectTypeGuid,GUID *InheritedObjectTypeGuid,PSID pSid,WINBOOL bAuditSuccess,WINBOOL bAuditFailure);
  __attribute__((dllimport)) WINBOOL  FindFirstFreeAce(PACL pAcl,LPVOID *pAce);
  __attribute__((dllimport)) WINBOOL  InitializeSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor,DWORD dwRevision);
  __attribute__((dllimport)) WINBOOL  IsValidSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor);
  __attribute__((dllimport)) DWORD  GetSecurityDescriptorLength(PSECURITY_DESCRIPTOR pSecurityDescriptor);
  __attribute__((dllimport)) WINBOOL  GetSecurityDescriptorControl(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSECURITY_DESCRIPTOR_CONTROL pControl,LPDWORD lpdwRevision);
  __attribute__((dllimport)) WINBOOL  SetSecurityDescriptorControl(PSECURITY_DESCRIPTOR pSecurityDescriptor,SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet);
  __attribute__((dllimport)) WINBOOL  SetSecurityDescriptorDacl(PSECURITY_DESCRIPTOR pSecurityDescriptor,WINBOOL bDaclPresent,PACL pDacl,WINBOOL bDaclDefaulted);
  __attribute__((dllimport)) WINBOOL  GetSecurityDescriptorDacl(PSECURITY_DESCRIPTOR pSecurityDescriptor,LPBOOL lpbDaclPresent,PACL *pDacl,LPBOOL lpbDaclDefaulted);
  __attribute__((dllimport)) WINBOOL  SetSecurityDescriptorSacl(PSECURITY_DESCRIPTOR pSecurityDescriptor,WINBOOL bSaclPresent,PACL pSacl,WINBOOL bSaclDefaulted);
  __attribute__((dllimport)) WINBOOL  GetSecurityDescriptorSacl(PSECURITY_DESCRIPTOR pSecurityDescriptor,LPBOOL lpbSaclPresent,PACL *pSacl,LPBOOL lpbSaclDefaulted);
  __attribute__((dllimport)) WINBOOL  SetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID pOwner,WINBOOL bOwnerDefaulted);
  __attribute__((dllimport)) WINBOOL  GetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID *pOwner,LPBOOL lpbOwnerDefaulted);
  __attribute__((dllimport)) WINBOOL  SetSecurityDescriptorGroup(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID pGroup,WINBOOL bGroupDefaulted);
  __attribute__((dllimport)) WINBOOL  GetSecurityDescriptorGroup(PSECURITY_DESCRIPTOR pSecurityDescriptor,PSID *pGroup,LPBOOL lpbGroupDefaulted);
  __attribute__((dllimport)) DWORD  SetSecurityDescriptorRMControl(PSECURITY_DESCRIPTOR SecurityDescriptor,PUCHAR RMControl);
  __attribute__((dllimport)) DWORD  GetSecurityDescriptorRMControl(PSECURITY_DESCRIPTOR SecurityDescriptor,PUCHAR RMControl);
  __attribute__((dllimport)) WINBOOL  CreatePrivateObjectSecurity(PSECURITY_DESCRIPTOR ParentDescriptor,PSECURITY_DESCRIPTOR CreatorDescriptor,PSECURITY_DESCRIPTOR *NewDescriptor,WINBOOL IsDirectoryObject,HANDLE Token,PGENERIC_MAPPING GenericMapping);
  __attribute__((dllimport)) WINBOOL  ConvertToAutoInheritPrivateObjectSecurity(PSECURITY_DESCRIPTOR ParentDescriptor,PSECURITY_DESCRIPTOR CurrentSecurityDescriptor,PSECURITY_DESCRIPTOR *NewSecurityDescriptor,GUID *ObjectType,BOOLEAN IsDirectoryObject,PGENERIC_MAPPING GenericMapping);
  __attribute__((dllimport)) WINBOOL  CreatePrivateObjectSecurityEx(PSECURITY_DESCRIPTOR ParentDescriptor,PSECURITY_DESCRIPTOR CreatorDescriptor,PSECURITY_DESCRIPTOR *NewDescriptor,GUID *ObjectType,WINBOOL IsContainerObject,ULONG AutoInheritFlags,HANDLE Token,PGENERIC_MAPPING GenericMapping);
  __attribute__((dllimport)) WINBOOL  CreatePrivateObjectSecurityWithMultipleInheritance(PSECURITY_DESCRIPTOR ParentDescriptor,PSECURITY_DESCRIPTOR CreatorDescriptor,PSECURITY_DESCRIPTOR *NewDescriptor,GUID **ObjectTypes,ULONG GuidCount,WINBOOL IsContainerObject,ULONG AutoInheritFlags,HANDLE Token,PGENERIC_MAPPING GenericMapping);
  __attribute__((dllimport)) WINBOOL  SetPrivateObjectSecurity (SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR ModificationDescriptor,PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,PGENERIC_MAPPING GenericMapping,HANDLE Token);
  __attribute__((dllimport)) WINBOOL  SetPrivateObjectSecurityEx (SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR ModificationDescriptor,PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,ULONG AutoInheritFlags,PGENERIC_MAPPING GenericMapping,HANDLE Token);
  __attribute__((dllimport)) WINBOOL  GetPrivateObjectSecurity(PSECURITY_DESCRIPTOR ObjectDescriptor,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR ResultantDescriptor,DWORD DescriptorLength,PDWORD ReturnLength);
  __attribute__((dllimport)) WINBOOL  DestroyPrivateObjectSecurity(PSECURITY_DESCRIPTOR *ObjectDescriptor);
  __attribute__((dllimport)) WINBOOL  MakeSelfRelativeSD(PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,LPDWORD lpdwBufferLength);
  __attribute__((dllimport)) WINBOOL  MakeAbsoluteSD(PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,LPDWORD lpdwAbsoluteSecurityDescriptorSize,PACL pDacl,LPDWORD lpdwDaclSize,PACL pSacl,LPDWORD lpdwSaclSize,PSID pOwner,LPDWORD lpdwOwnerSize,PSID pPrimaryGroup,LPDWORD lpdwPrimaryGroupSize);
  __attribute__((dllimport)) WINBOOL  MakeAbsoluteSD2(PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,LPDWORD lpdwBufferSize);
  __attribute__((dllimport)) WINBOOL  SetFileSecurityA(LPCSTR lpFileName,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor);
  __attribute__((dllimport)) WINBOOL  SetFileSecurityW(LPCWSTR lpFileName,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor);
  __attribute__((dllimport)) WINBOOL  GetFileSecurityA(LPCSTR lpFileName,SECURITY_INFORMATION RequestedInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
  __attribute__((dllimport)) WINBOOL  GetFileSecurityW(LPCWSTR lpFileName,SECURITY_INFORMATION RequestedInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
  __attribute__((dllimport)) WINBOOL  SetKernelObjectSecurity(HANDLE Handle,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR SecurityDescriptor);
  __attribute__((dllimport)) HANDLE  FindFirstChangeNotificationA(LPCSTR lpPathName,WINBOOL bWatchSubtree,DWORD dwNotifyFilter);
  __attribute__((dllimport)) HANDLE  FindFirstChangeNotificationW(LPCWSTR lpPathName,WINBOOL bWatchSubtree,DWORD dwNotifyFilter);
  __attribute__((dllimport)) WINBOOL  FindNextChangeNotification(HANDLE hChangeHandle);
  __attribute__((dllimport)) WINBOOL  FindCloseChangeNotification(HANDLE hChangeHandle);
  __attribute__((dllimport)) WINBOOL  ReadDirectoryChangesW(HANDLE hDirectory,LPVOID lpBuffer,DWORD nBufferLength,WINBOOL bWatchSubtree,DWORD dwNotifyFilter,LPDWORD lpBytesReturned,LPOVERLAPPED lpOverlapped,LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
  __attribute__((dllimport)) WINBOOL  VirtualLock(LPVOID lpAddress,SIZE_T dwSize);
  __attribute__((dllimport)) WINBOOL  VirtualUnlock(LPVOID lpAddress,SIZE_T dwSize);
  __attribute__((dllimport)) LPVOID  MapViewOfFileEx(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,SIZE_T dwNumberOfBytesToMap,LPVOID lpBaseAddress);
  __attribute__((dllimport)) WINBOOL  SetPriorityClass(HANDLE hProcess,DWORD dwPriorityClass);
  __attribute__((dllimport)) DWORD  GetPriorityClass(HANDLE hProcess);
  __attribute__((dllimport)) WINBOOL  IsBadReadPtr(const void *lp,UINT_PTR ucb);
  __attribute__((dllimport)) WINBOOL  IsBadWritePtr(LPVOID lp,UINT_PTR ucb);
  __attribute__((dllimport)) WINBOOL  IsBadHugeReadPtr(const void *lp,UINT_PTR ucb);
  __attribute__((dllimport)) WINBOOL  IsBadHugeWritePtr(LPVOID lp,UINT_PTR ucb);
  __attribute__((dllimport)) WINBOOL  IsBadCodePtr(FARPROC lpfn);
  __attribute__((dllimport)) WINBOOL  IsBadStringPtrA(LPCSTR lpsz,UINT_PTR ucchMax);
  __attribute__((dllimport)) WINBOOL  IsBadStringPtrW(LPCWSTR lpsz,UINT_PTR ucchMax);
  __attribute__((dllimport)) WINBOOL  LookupAccountSidA(LPCSTR lpSystemName,PSID Sid,LPSTR Name,LPDWORD cchName,LPSTR ReferencedDomainName,LPDWORD cchReferencedDomainName,PSID_NAME_USE peUse);
  __attribute__((dllimport)) WINBOOL  LookupAccountSidW(LPCWSTR lpSystemName,PSID Sid,LPWSTR Name,LPDWORD cchName,LPWSTR ReferencedDomainName,LPDWORD cchReferencedDomainName,PSID_NAME_USE peUse);
  __attribute__((dllimport)) WINBOOL  LookupAccountNameA(LPCSTR lpSystemName,LPCSTR lpAccountName,PSID Sid,LPDWORD cbSid,LPSTR ReferencedDomainName,LPDWORD cchReferencedDomainName,PSID_NAME_USE peUse);
  __attribute__((dllimport)) WINBOOL  LookupAccountNameW(LPCWSTR lpSystemName,LPCWSTR lpAccountName,PSID Sid,LPDWORD cbSid,LPWSTR ReferencedDomainName,LPDWORD cchReferencedDomainName,PSID_NAME_USE peUse);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeValueA(LPCSTR lpSystemName,LPCSTR lpName,PLUID lpLuid);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeValueW(LPCWSTR lpSystemName,LPCWSTR lpName,PLUID lpLuid);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeNameA(LPCSTR lpSystemName,PLUID lpLuid,LPSTR lpName,LPDWORD cchName);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeNameW(LPCWSTR lpSystemName,PLUID lpLuid,LPWSTR lpName,LPDWORD cchName);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeDisplayNameA(LPCSTR lpSystemName,LPCSTR lpName,LPSTR lpDisplayName,LPDWORD cchDisplayName,LPDWORD lpLanguageId);
  __attribute__((dllimport)) WINBOOL  LookupPrivilegeDisplayNameW(LPCWSTR lpSystemName,LPCWSTR lpName,LPWSTR lpDisplayName,LPDWORD cchDisplayName,LPDWORD lpLanguageId);
  __attribute__((dllimport)) WINBOOL  AllocateLocallyUniqueId(PLUID Luid);
  __attribute__((dllimport)) WINBOOL  BuildCommDCBA(LPCSTR lpDef,LPDCB lpDCB);
  __attribute__((dllimport)) WINBOOL  BuildCommDCBW(LPCWSTR lpDef,LPDCB lpDCB);
  __attribute__((dllimport)) WINBOOL  BuildCommDCBAndTimeoutsA(LPCSTR lpDef,LPDCB lpDCB,LPCOMMTIMEOUTS lpCommTimeouts);
  __attribute__((dllimport)) WINBOOL  BuildCommDCBAndTimeoutsW(LPCWSTR lpDef,LPDCB lpDCB,LPCOMMTIMEOUTS lpCommTimeouts);
  __attribute__((dllimport)) WINBOOL  CommConfigDialogA(LPCSTR lpszName,HWND hWnd,LPCOMMCONFIG lpCC);
  __attribute__((dllimport)) WINBOOL  CommConfigDialogW(LPCWSTR lpszName,HWND hWnd,LPCOMMCONFIG lpCC);
  __attribute__((dllimport)) WINBOOL  GetDefaultCommConfigA(LPCSTR lpszName,LPCOMMCONFIG lpCC,LPDWORD lpdwSize);
  __attribute__((dllimport)) WINBOOL  GetDefaultCommConfigW(LPCWSTR lpszName,LPCOMMCONFIG lpCC,LPDWORD lpdwSize);
  __attribute__((dllimport)) WINBOOL  SetDefaultCommConfigA(LPCSTR lpszName,LPCOMMCONFIG lpCC,DWORD dwSize);
  __attribute__((dllimport)) WINBOOL  SetDefaultCommConfigW(LPCWSTR lpszName,LPCOMMCONFIG lpCC,DWORD dwSize);



  __attribute__((dllimport)) WINBOOL  GetComputerNameA(LPSTR lpBuffer,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  GetComputerNameW(LPWSTR lpBuffer,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetComputerNameA(LPCSTR lpComputerName);
  __attribute__((dllimport)) WINBOOL  SetComputerNameW(LPCWSTR lpComputerName);

  typedef enum _COMPUTER_NAME_FORMAT {
    ComputerNameNetBIOS,ComputerNameDnsHostname,ComputerNameDnsDomain,ComputerNameDnsFullyQualified,ComputerNamePhysicalNetBIOS,ComputerNamePhysicalDnsHostname,ComputerNamePhysicalDnsDomain,ComputerNamePhysicalDnsFullyQualified,ComputerNameMax
  } COMPUTER_NAME_FORMAT;

  __attribute__((dllimport)) WINBOOL  GetComputerNameExA(COMPUTER_NAME_FORMAT NameType,LPSTR lpBuffer,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  GetComputerNameExW(COMPUTER_NAME_FORMAT NameType,LPWSTR lpBuffer,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetComputerNameExA(COMPUTER_NAME_FORMAT NameType,LPCSTR lpBuffer);
  __attribute__((dllimport)) WINBOOL  SetComputerNameExW(COMPUTER_NAME_FORMAT NameType,LPCWSTR lpBuffer);
  __attribute__((dllimport)) WINBOOL  DnsHostnameToComputerNameA(LPCSTR Hostname,LPSTR ComputerName,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  DnsHostnameToComputerNameW(LPCWSTR Hostname,LPWSTR ComputerName,LPDWORD nSize);
  __attribute__((dllimport)) WINBOOL  GetUserNameA(LPSTR lpBuffer,LPDWORD pcbBuffer);
  __attribute__((dllimport)) WINBOOL  GetUserNameW(LPWSTR lpBuffer,LPDWORD pcbBuffer);
# 2610 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  LogonUserA(LPCSTR lpszUsername,LPCSTR lpszDomain,LPCSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,PHANDLE phToken);
  __attribute__((dllimport)) WINBOOL  LogonUserW(LPCWSTR lpszUsername,LPCWSTR lpszDomain,LPCWSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,PHANDLE phToken);
  __attribute__((dllimport)) WINBOOL  LogonUserExA(LPCSTR lpszUsername,LPCSTR lpszDomain,LPCSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,PHANDLE phToken,PSID *ppLogonSid,PVOID *ppProfileBuffer,LPDWORD pdwProfileLength,PQUOTA_LIMITS pQuotaLimits);
  __attribute__((dllimport)) WINBOOL  LogonUserExW(LPCWSTR lpszUsername,LPCWSTR lpszDomain,LPCWSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,PHANDLE phToken,PSID *ppLogonSid,PVOID *ppProfileBuffer,LPDWORD pdwProfileLength,PQUOTA_LIMITS pQuotaLimits);
  __attribute__((dllimport)) WINBOOL  ImpersonateLoggedOnUser(HANDLE hToken);
  __attribute__((dllimport)) WINBOOL  CreateProcessAsUserA(HANDLE hToken,LPCSTR lpApplicationName,LPSTR lpCommandLine,LPSECURITY_ATTRIBUTES lpProcessAttributes,LPSECURITY_ATTRIBUTES lpThreadAttributes,WINBOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCSTR lpCurrentDirectory,LPSTARTUPINFOA lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);
  __attribute__((dllimport)) WINBOOL  CreateProcessAsUserW(HANDLE hToken,LPCWSTR lpApplicationName,LPWSTR lpCommandLine,LPSECURITY_ATTRIBUTES lpProcessAttributes,LPSECURITY_ATTRIBUTES lpThreadAttributes,WINBOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,LPSTARTUPINFOW lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);





  __attribute__((dllimport)) WINBOOL  CreateProcessWithLogonW(LPCWSTR lpUsername,LPCWSTR lpDomain,LPCWSTR lpPassword,DWORD dwLogonFlags,LPCWSTR lpApplicationName,LPWSTR lpCommandLine,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,LPSTARTUPINFOW lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);
  __attribute__((dllimport)) WINBOOL  CreateProcessWithTokenW(HANDLE hToken,DWORD dwLogonFlags,LPCWSTR lpApplicationName,LPWSTR lpCommandLine,DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,LPSTARTUPINFOW lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation);
  __attribute__((dllimport)) WINBOOL  ImpersonateAnonymousToken(HANDLE ThreadHandle);
  __attribute__((dllimport)) WINBOOL  DuplicateTokenEx(HANDLE hExistingToken,DWORD dwDesiredAccess,LPSECURITY_ATTRIBUTES lpTokenAttributes,SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,TOKEN_TYPE TokenType,PHANDLE phNewToken);
  __attribute__((dllimport)) WINBOOL  CreateRestrictedToken(HANDLE ExistingTokenHandle,DWORD Flags,DWORD DisableSidCount,PSID_AND_ATTRIBUTES SidsToDisable,DWORD DeletePrivilegeCount,PLUID_AND_ATTRIBUTES PrivilegesToDelete,DWORD RestrictedSidCount,PSID_AND_ATTRIBUTES SidsToRestrict,PHANDLE NewTokenHandle);
  __attribute__((dllimport)) WINBOOL  IsTokenRestricted(HANDLE TokenHandle);
  __attribute__((dllimport)) WINBOOL  IsTokenUntrusted(HANDLE TokenHandle);
  __attribute__((dllimport)) WINBOOL  CheckTokenMembership(HANDLE TokenHandle,PSID SidToCheck,PBOOL IsMember);

  typedef WAITORTIMERCALLBACKFUNC WAITORTIMERCALLBACK;

  __attribute__((dllimport)) WINBOOL  RegisterWaitForSingleObject(PHANDLE phNewWaitObject,HANDLE hObject,WAITORTIMERCALLBACK Callback,PVOID Context,ULONG dwMilliseconds,ULONG dwFlags);
  __attribute__((dllimport)) HANDLE  RegisterWaitForSingleObjectEx(HANDLE hObject,WAITORTIMERCALLBACK Callback,PVOID Context,ULONG dwMilliseconds,ULONG dwFlags);
  __attribute__((dllimport)) WINBOOL  UnregisterWait(HANDLE WaitHandle);
  __attribute__((dllimport)) WINBOOL  UnregisterWaitEx(HANDLE WaitHandle,HANDLE CompletionEvent);
  __attribute__((dllimport)) WINBOOL  QueueUserWorkItem(LPTHREAD_START_ROUTINE Function,PVOID Context,ULONG Flags);
  __attribute__((dllimport)) WINBOOL  BindIoCompletionCallback(HANDLE FileHandle,LPOVERLAPPED_COMPLETION_ROUTINE Function,ULONG Flags);
  __attribute__((dllimport)) HANDLE  CreateTimerQueue(void);
  __attribute__((dllimport)) WINBOOL  CreateTimerQueueTimer(PHANDLE phNewTimer,HANDLE TimerQueue,WAITORTIMERCALLBACK Callback,PVOID Parameter,DWORD DueTime,DWORD Period,ULONG Flags);
  __attribute__((dllimport)) WINBOOL  ChangeTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer,ULONG DueTime,ULONG Period);
  __attribute__((dllimport)) WINBOOL  DeleteTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer,HANDLE CompletionEvent);
  __attribute__((dllimport)) WINBOOL  DeleteTimerQueueEx(HANDLE TimerQueue,HANDLE CompletionEvent);
  __attribute__((dllimport)) HANDLE  SetTimerQueueTimer(HANDLE TimerQueue,WAITORTIMERCALLBACK Callback,PVOID Parameter,DWORD DueTime,DWORD Period,WINBOOL PreferIo);
  __attribute__((dllimport)) WINBOOL  CancelTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer);
  __attribute__((dllimport)) WINBOOL  DeleteTimerQueue(HANDLE TimerQueue);
# 2657 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct tagHW_PROFILE_INFOA {
    DWORD dwDockInfo;
    CHAR szHwProfileGuid[39];
    CHAR szHwProfileName[80];
  } HW_PROFILE_INFOA,*LPHW_PROFILE_INFOA;

  typedef struct tagHW_PROFILE_INFOW {
    DWORD dwDockInfo;
    WCHAR szHwProfileGuid[39];
    WCHAR szHwProfileName[80];
  } HW_PROFILE_INFOW,*LPHW_PROFILE_INFOW;





  typedef HW_PROFILE_INFOA HW_PROFILE_INFO;
  typedef LPHW_PROFILE_INFOA LPHW_PROFILE_INFO;
# 2687 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  GetCurrentHwProfileA (LPHW_PROFILE_INFOA lpHwProfileInfo);
  __attribute__((dllimport)) WINBOOL  GetCurrentHwProfileW (LPHW_PROFILE_INFOW lpHwProfileInfo);
  __attribute__((dllimport)) WINBOOL  QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
  __attribute__((dllimport)) WINBOOL  QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
  __attribute__((dllimport)) WINBOOL  GetVersionExA(LPOSVERSIONINFOA lpVersionInformation);
  __attribute__((dllimport)) WINBOOL  GetVersionExW(LPOSVERSIONINFOW lpVersionInformation);
  __attribute__((dllimport)) WINBOOL  VerifyVersionInfoA(LPOSVERSIONINFOEXA lpVersionInformation,DWORD dwTypeMask,DWORDLONG dwlConditionMask);
  __attribute__((dllimport)) WINBOOL  VerifyVersionInfoW(LPOSVERSIONINFOEXW lpVersionInformation,DWORD dwTypeMask,DWORDLONG dwlConditionMask);

# 1 "c:/program files/tcc/include/winapi/winerror.h" 1
# 2697 "c:/program files/tcc/include/winapi/winbase.h" 2
# 2719 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct _SYSTEM_POWER_STATUS {
    BYTE ACLineStatus;
    BYTE BatteryFlag;
    BYTE BatteryLifePercent;
    BYTE Reserved1;
    DWORD BatteryLifeTime;
    DWORD BatteryFullLifeTime;
  } SYSTEM_POWER_STATUS,*LPSYSTEM_POWER_STATUS;
# 2754 "c:/program files/tcc/include/winapi/winbase.h"
  WINBOOL  GetSystemPowerStatus(LPSYSTEM_POWER_STATUS lpSystemPowerStatus);
  WINBOOL  SetSystemPowerState(WINBOOL fSuspend,WINBOOL fForce);
  __attribute__((dllimport)) WINBOOL  AllocateUserPhysicalPages(HANDLE hProcess,PULONG_PTR NumberOfPages,PULONG_PTR PageArray);
  __attribute__((dllimport)) WINBOOL  FreeUserPhysicalPages(HANDLE hProcess,PULONG_PTR NumberOfPages,PULONG_PTR PageArray);
  __attribute__((dllimport)) WINBOOL  MapUserPhysicalPages(PVOID VirtualAddress,ULONG_PTR NumberOfPages,PULONG_PTR PageArray);
  __attribute__((dllimport)) WINBOOL  MapUserPhysicalPagesScatter(PVOID *VirtualAddresses,ULONG_PTR NumberOfPages,PULONG_PTR PageArray);
  __attribute__((dllimport)) HANDLE  CreateJobObjectA(LPSECURITY_ATTRIBUTES lpJobAttributes,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  CreateJobObjectW(LPSECURITY_ATTRIBUTES lpJobAttributes,LPCWSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenJobObjectA(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCSTR lpName);
  __attribute__((dllimport)) HANDLE  OpenJobObjectW(DWORD dwDesiredAccess,WINBOOL bInheritHandle,LPCWSTR lpName);
  __attribute__((dllimport)) WINBOOL  AssignProcessToJobObject(HANDLE hJob,HANDLE hProcess);
  __attribute__((dllimport)) WINBOOL  TerminateJobObject(HANDLE hJob,UINT uExitCode);
  __attribute__((dllimport)) WINBOOL  QueryInformationJobObject(HANDLE hJob,JOBOBJECTINFOCLASS JobObjectInformationClass,LPVOID lpJobObjectInformation,DWORD cbJobObjectInformationLength,LPDWORD lpReturnLength);
  __attribute__((dllimport)) WINBOOL  SetInformationJobObject(HANDLE hJob,JOBOBJECTINFOCLASS JobObjectInformationClass,LPVOID lpJobObjectInformation,DWORD cbJobObjectInformationLength);
  __attribute__((dllimport)) WINBOOL  IsProcessInJob(HANDLE ProcessHandle,HANDLE JobHandle,PBOOL Result);
  __attribute__((dllimport)) WINBOOL  CreateJobSet(ULONG NumJob,PJOB_SET_ARRAY UserJobSet,ULONG Flags);
  __attribute__((dllimport)) PVOID  AddVectoredExceptionHandler (ULONG First,PVECTORED_EXCEPTION_HANDLER Handler);
  __attribute__((dllimport)) ULONG  RemoveVectoredExceptionHandler(PVOID Handle);
  __attribute__((dllimport)) PVOID  AddVectoredContinueHandler (ULONG First,PVECTORED_EXCEPTION_HANDLER Handler);
  __attribute__((dllimport)) ULONG  RemoveVectoredContinueHandler(PVOID Handle);
  __attribute__((dllimport)) HANDLE  FindFirstVolumeA(LPSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) HANDLE  FindFirstVolumeW(LPWSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindNextVolumeA(HANDLE hFindVolume,LPSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindNextVolumeW(HANDLE hFindVolume,LPWSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindVolumeClose(HANDLE hFindVolume);
  __attribute__((dllimport)) HANDLE  FindFirstVolumeMountPointA(LPCSTR lpszRootPathName,LPSTR lpszVolumeMountPoint,DWORD cchBufferLength);
  __attribute__((dllimport)) HANDLE  FindFirstVolumeMountPointW(LPCWSTR lpszRootPathName,LPWSTR lpszVolumeMountPoint,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindNextVolumeMountPointA(HANDLE hFindVolumeMountPoint,LPSTR lpszVolumeMountPoint,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindNextVolumeMountPointW(HANDLE hFindVolumeMountPoint,LPWSTR lpszVolumeMountPoint,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  FindVolumeMountPointClose(HANDLE hFindVolumeMountPoint);
  __attribute__((dllimport)) WINBOOL  SetVolumeMountPointA(LPCSTR lpszVolumeMountPoint,LPCSTR lpszVolumeName);
  __attribute__((dllimport)) WINBOOL  SetVolumeMountPointW(LPCWSTR lpszVolumeMountPoint,LPCWSTR lpszVolumeName);
  __attribute__((dllimport)) WINBOOL  DeleteVolumeMountPointA(LPCSTR lpszVolumeMountPoint);
  __attribute__((dllimport)) WINBOOL  DeleteVolumeMountPointW(LPCWSTR lpszVolumeMountPoint);
  __attribute__((dllimport)) WINBOOL  GetVolumeNameForVolumeMountPointA(LPCSTR lpszVolumeMountPoint,LPSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  GetVolumeNameForVolumeMountPointW(LPCWSTR lpszVolumeMountPoint,LPWSTR lpszVolumeName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  GetVolumePathNameA(LPCSTR lpszFileName,LPSTR lpszVolumePathName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  GetVolumePathNameW(LPCWSTR lpszFileName,LPWSTR lpszVolumePathName,DWORD cchBufferLength);
  __attribute__((dllimport)) WINBOOL  GetVolumePathNamesForVolumeNameA(LPCSTR lpszVolumeName,LPCH lpszVolumePathNames,DWORD cchBufferLength,PDWORD lpcchReturnLength);
  __attribute__((dllimport)) WINBOOL  GetVolumePathNamesForVolumeNameW(LPCWSTR lpszVolumeName,LPWCH lpszVolumePathNames,DWORD cchBufferLength,PDWORD lpcchReturnLength);
# 2804 "c:/program files/tcc/include/winapi/winbase.h"
  typedef struct tagACTCTXA {
    ULONG cbSize;
    DWORD dwFlags;
    LPCSTR lpSource;
    USHORT wProcessorArchitecture;
    LANGID wLangId;
    LPCSTR lpAssemblyDirectory;
    LPCSTR lpResourceName;
    LPCSTR lpApplicationName;
    HMODULE hModule;
  } ACTCTXA,*PACTCTXA;

  typedef struct tagACTCTXW {
    ULONG cbSize;
    DWORD dwFlags;
    LPCWSTR lpSource;
    USHORT wProcessorArchitecture;
    LANGID wLangId;
    LPCWSTR lpAssemblyDirectory;
    LPCWSTR lpResourceName;
    LPCWSTR lpApplicationName;
    HMODULE hModule;
  } ACTCTXW,*PACTCTXW;

  typedef const ACTCTXA *PCACTCTXA;
  typedef const ACTCTXW *PCACTCTXW;






  typedef ACTCTXA ACTCTX;
  typedef PACTCTXA PACTCTX;
  typedef PCACTCTXA PCACTCTX;
# 2847 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) HANDLE  CreateActCtxA(PCACTCTXA pActCtx);
  __attribute__((dllimport)) HANDLE  CreateActCtxW(PCACTCTXW pActCtx);
  __attribute__((dllimport)) void  AddRefActCtx(HANDLE hActCtx);
  __attribute__((dllimport)) void  ReleaseActCtx(HANDLE hActCtx);
  __attribute__((dllimport)) WINBOOL  ZombifyActCtx(HANDLE hActCtx);
  __attribute__((dllimport)) WINBOOL  ActivateActCtx(HANDLE hActCtx,ULONG_PTR *lpCookie);



  __attribute__((dllimport)) WINBOOL  DeactivateActCtx(DWORD dwFlags,ULONG_PTR ulCookie);
  __attribute__((dllimport)) WINBOOL  GetCurrentActCtx(HANDLE *lphActCtx);

  typedef struct tagACTCTX_SECTION_KEYED_DATA_2600 {
    ULONG cbSize;
    ULONG ulDataFormatVersion;
    PVOID lpData;
    ULONG ulLength;
    PVOID lpSectionGlobalData;
    ULONG ulSectionGlobalDataLength;
    PVOID lpSectionBase;
    ULONG ulSectionTotalLength;
    HANDLE hActCtx;
    ULONG ulAssemblyRosterIndex;
  } ACTCTX_SECTION_KEYED_DATA_2600,*PACTCTX_SECTION_KEYED_DATA_2600;

  typedef const ACTCTX_SECTION_KEYED_DATA_2600 *PCACTCTX_SECTION_KEYED_DATA_2600;

  typedef struct tagACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA {
    PVOID lpInformation;
    PVOID lpSectionBase;
    ULONG ulSectionLength;
    PVOID lpSectionGlobalDataBase;
    ULONG ulSectionGlobalDataLength;
  } ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA,*PACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA;

  typedef const ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA *PCACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA;

  typedef struct tagACTCTX_SECTION_KEYED_DATA {
    ULONG cbSize;
    ULONG ulDataFormatVersion;
    PVOID lpData;
    ULONG ulLength;
    PVOID lpSectionGlobalData;
    ULONG ulSectionGlobalDataLength;
    PVOID lpSectionBase;
    ULONG ulSectionTotalLength;
    HANDLE hActCtx;
    ULONG ulAssemblyRosterIndex;

    ULONG ulFlags;
    ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA AssemblyMetadata;
  } ACTCTX_SECTION_KEYED_DATA,*PACTCTX_SECTION_KEYED_DATA;

  typedef const ACTCTX_SECTION_KEYED_DATA *PCACTCTX_SECTION_KEYED_DATA;
# 2912 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  FindActCtxSectionStringA(DWORD dwFlags,const GUID *lpExtensionGuid,ULONG ulSectionId,LPCSTR lpStringToFind,PACTCTX_SECTION_KEYED_DATA ReturnedData);
  __attribute__((dllimport)) WINBOOL  FindActCtxSectionStringW(DWORD dwFlags,const GUID *lpExtensionGuid,ULONG ulSectionId,LPCWSTR lpStringToFind,PACTCTX_SECTION_KEYED_DATA ReturnedData);
  __attribute__((dllimport)) WINBOOL  FindActCtxSectionGuid(DWORD dwFlags,const GUID *lpExtensionGuid,ULONG ulSectionId,const GUID *lpGuidToFind,PACTCTX_SECTION_KEYED_DATA ReturnedData);




  typedef struct _ACTIVATION_CONTEXT_BASIC_INFORMATION {
    HANDLE hActCtx;
    DWORD dwFlags;
  } ACTIVATION_CONTEXT_BASIC_INFORMATION,*PACTIVATION_CONTEXT_BASIC_INFORMATION;

  typedef const struct _ACTIVATION_CONTEXT_BASIC_INFORMATION *PCACTIVATION_CONTEXT_BASIC_INFORMATION;
# 2935 "c:/program files/tcc/include/winapi/winbase.h"
  __attribute__((dllimport)) WINBOOL  QueryActCtxW(DWORD dwFlags,HANDLE hActCtx,PVOID pvSubInstance,ULONG ulInfoClass,PVOID pvBuffer,SIZE_T cbBuffer,SIZE_T *pcbWrittenOrRequired);

  typedef WINBOOL ( *PQUERYACTCTXW_FUNC)(DWORD dwFlags,HANDLE hActCtx,PVOID pvSubInstance,ULONG ulInfoClass,PVOID pvBuffer,SIZE_T cbBuffer,SIZE_T *pcbWrittenOrRequired);

  __attribute__((dllimport)) WINBOOL  ProcessIdToSessionId(DWORD dwProcessId,DWORD *pSessionId);
  __attribute__((dllimport)) DWORD  WTSGetActiveConsoleSessionId();
  __attribute__((dllimport)) WINBOOL  IsWow64Process(HANDLE hProcess,PBOOL Wow64Process);
  __attribute__((dllimport)) WINBOOL  GetLogicalProcessorInformation(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer,PDWORD ReturnedLength);
  __attribute__((dllimport)) WINBOOL  GetNumaHighestNodeNumber(PULONG HighestNodeNumber);
  __attribute__((dllimport)) WINBOOL  GetNumaProcessorNode(UCHAR Processor,PUCHAR NodeNumber);
  __attribute__((dllimport)) WINBOOL  GetNumaNodeProcessorMask(UCHAR Node,PULONGLONG ProcessorMask);
  __attribute__((dllimport)) WINBOOL  GetNumaAvailableMemoryNode(UCHAR Node,PULONGLONG AvailableBytes);
# 68 "c:/program files/tcc/include/winapi/windows.h" 2
# 1 "c:/program files/tcc/include/winapi/wingdi.h" 1
# 208 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _DRAWPATRECT {
    POINT ptPosition;
    POINT ptSize;
    WORD wStyle;
    WORD wPattern;
  } DRAWPATRECT,*PDRAWPATRECT;
# 309 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _PSINJECTDATA {
    DWORD DataBytes;
    WORD InjectionPoint;
    WORD PageNumber;
  } PSINJECTDATA,*PPSINJECTDATA;
# 363 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _PSFEATURE_OUTPUT {
    WINBOOL bPageIndependent;
    WINBOOL bSetPageDevice;
  } PSFEATURE_OUTPUT,*PPSFEATURE_OUTPUT;

  typedef struct _PSFEATURE_CUSTPAPER {
    LONG lOrientation;
    LONG lWidth;
    LONG lHeight;
    LONG lWidthOffset;
    LONG lHeightOffset;
  } PSFEATURE_CUSTPAPER,*PPSFEATURE_CUSTPAPER;
# 418 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagXFORM {
    FLOAT eM11;
    FLOAT eM12;
    FLOAT eM21;
    FLOAT eM22;
    FLOAT eDx;
    FLOAT eDy;
  } XFORM,*PXFORM,*LPXFORM;

  typedef struct tagBITMAP {
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitsPixel;
    LPVOID bmBits;
  } BITMAP,*PBITMAP,*NPBITMAP,*LPBITMAP;

# 1 "c:/program files/tcc/include/winapi/pshpack1.h" 1






#pragma pack(push,1)
# 438 "c:/program files/tcc/include/winapi/wingdi.h" 2
  typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
  } RGBTRIPLE;
# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 444 "c:/program files/tcc/include/winapi/wingdi.h" 2

  typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
  } RGBQUAD;
  typedef RGBQUAD *LPRGBQUAD;
# 461 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef LONG LCSCSTYPE;


  typedef LONG LCSGAMUTMATCH;
# 488 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef long FXPT16DOT16,*LPFXPT16DOT16;
  typedef long FXPT2DOT30,*LPFXPT2DOT30;

  typedef struct tagCIEXYZ {
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
  } CIEXYZ;
  typedef CIEXYZ *LPCIEXYZ;

  typedef struct tagICEXYZTRIPLE {
    CIEXYZ ciexyzRed;
    CIEXYZ ciexyzGreen;
    CIEXYZ ciexyzBlue;
  } CIEXYZTRIPLE;

  typedef CIEXYZTRIPLE *LPCIEXYZTRIPLE;

  typedef struct tagLOGCOLORSPACEA {
    DWORD lcsSignature;
    DWORD lcsVersion;
    DWORD lcsSize;
    LCSCSTYPE lcsCSType;
    LCSGAMUTMATCH lcsIntent;
    CIEXYZTRIPLE lcsEndpoints;
    DWORD lcsGammaRed;
    DWORD lcsGammaGreen;
    DWORD lcsGammaBlue;
    CHAR lcsFilename[260];
  } LOGCOLORSPACEA,*LPLOGCOLORSPACEA;

  typedef struct tagLOGCOLORSPACEW {
    DWORD lcsSignature;
    DWORD lcsVersion;
    DWORD lcsSize;
    LCSCSTYPE lcsCSType;
    LCSGAMUTMATCH lcsIntent;
    CIEXYZTRIPLE lcsEndpoints;
    DWORD lcsGammaRed;
    DWORD lcsGammaGreen;
    DWORD lcsGammaBlue;
    WCHAR lcsFilename[260];
  } LOGCOLORSPACEW,*LPLOGCOLORSPACEW;





  typedef LOGCOLORSPACEA LOGCOLORSPACE;
  typedef LPLOGCOLORSPACEA LPLOGCOLORSPACE;


  typedef struct tagBITMAPCOREHEADER {
    DWORD bcSize;
    WORD bcWidth;
    WORD bcHeight;
    WORD bcPlanes;
    WORD bcBitCount;
  } BITMAPCOREHEADER,*LPBITMAPCOREHEADER,*PBITMAPCOREHEADER;

  typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
  } BITMAPINFOHEADER,*LPBITMAPINFOHEADER,*PBITMAPINFOHEADER;

  typedef struct {
    DWORD bV4Size;
    LONG bV4Width;
    LONG bV4Height;
    WORD bV4Planes;
    WORD bV4BitCount;
    DWORD bV4V4Compression;
    DWORD bV4SizeImage;
    LONG bV4XPelsPerMeter;
    LONG bV4YPelsPerMeter;
    DWORD bV4ClrUsed;
    DWORD bV4ClrImportant;
    DWORD bV4RedMask;
    DWORD bV4GreenMask;
    DWORD bV4BlueMask;
    DWORD bV4AlphaMask;
    DWORD bV4CSType;
    CIEXYZTRIPLE bV4Endpoints;
    DWORD bV4GammaRed;
    DWORD bV4GammaGreen;
    DWORD bV4GammaBlue;
  } BITMAPV4HEADER,*LPBITMAPV4HEADER,*PBITMAPV4HEADER;

  typedef struct {
    DWORD bV5Size;
    LONG bV5Width;
    LONG bV5Height;
    WORD bV5Planes;
    WORD bV5BitCount;
    DWORD bV5Compression;
    DWORD bV5SizeImage;
    LONG bV5XPelsPerMeter;
    LONG bV5YPelsPerMeter;
    DWORD bV5ClrUsed;
    DWORD bV5ClrImportant;
    DWORD bV5RedMask;
    DWORD bV5GreenMask;
    DWORD bV5BlueMask;
    DWORD bV5AlphaMask;
    DWORD bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    DWORD bV5GammaRed;
    DWORD bV5GammaGreen;
    DWORD bV5GammaBlue;
    DWORD bV5Intent;
    DWORD bV5ProfileData;
    DWORD bV5ProfileSize;
    DWORD bV5Reserved;
  } BITMAPV5HEADER,*LPBITMAPV5HEADER,*PBITMAPV5HEADER;
# 622 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
  } BITMAPINFO,*LPBITMAPINFO,*PBITMAPINFO;

  typedef struct tagBITMAPCOREINFO {
    BITMAPCOREHEADER bmciHeader;
    RGBTRIPLE bmciColors[1];
  } BITMAPCOREINFO,*LPBITMAPCOREINFO,*PBITMAPCOREINFO;

# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 633 "c:/program files/tcc/include/winapi/wingdi.h" 2
  typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
  } BITMAPFILEHEADER,*LPBITMAPFILEHEADER,*PBITMAPFILEHEADER;
# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 641 "c:/program files/tcc/include/winapi/wingdi.h" 2




  typedef struct tagFONTSIGNATURE {
    DWORD fsUsb[4];
    DWORD fsCsb[2];
  } FONTSIGNATURE,*PFONTSIGNATURE,*LPFONTSIGNATURE;

  typedef struct tagCHARSETINFO {
    UINT ciCharset;
    UINT ciACP;
    FONTSIGNATURE fs;
  } CHARSETINFO,*PCHARSETINFO,*NPCHARSETINFO,*LPCHARSETINFO;






  typedef struct tagLOCALESIGNATURE {
    DWORD lsUsb[4];
    DWORD lsCsbDefault[2];
    DWORD lsCsbSupported[2];
  } LOCALESIGNATURE,*PLOCALESIGNATURE,*LPLOCALESIGNATURE;




  typedef struct tagHANDLETABLE {
    HGDIOBJ objectHandle[1];
  } HANDLETABLE,*PHANDLETABLE,*LPHANDLETABLE;

  typedef struct tagMETARECORD {
    DWORD rdSize;
    WORD rdFunction;
    WORD rdParm[1];
  } METARECORD;
  typedef struct tagMETARECORD  *PMETARECORD;
  typedef struct tagMETARECORD  *LPMETARECORD;

  typedef struct tagMETAFILEPICT {
    LONG mm;
    LONG xExt;
    LONG yExt;
    HMETAFILE hMF;
  } METAFILEPICT,*LPMETAFILEPICT;

# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 690 "c:/program files/tcc/include/winapi/wingdi.h" 2
  typedef struct tagMETAHEADER {
    WORD mtType;
    WORD mtHeaderSize;
    WORD mtVersion;
    DWORD mtSize;
    WORD mtNoObjects;
    DWORD mtMaxRecord;
    WORD mtNoParameters;
  } METAHEADER;
  typedef struct tagMETAHEADER  *PMETAHEADER;
  typedef struct tagMETAHEADER  *LPMETAHEADER;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 703 "c:/program files/tcc/include/winapi/wingdi.h" 2

  typedef struct tagENHMETARECORD {
    DWORD iType;
    DWORD nSize;
    DWORD dParm[1];
  } ENHMETARECORD,*PENHMETARECORD,*LPENHMETARECORD;

  typedef struct tagENHMETAHEADER {
    DWORD iType;
    DWORD nSize;
    RECTL rclBounds;
    RECTL rclFrame;
    DWORD dSignature;
    DWORD nVersion;
    DWORD nBytes;
    DWORD nRecords;
    WORD nHandles;
    WORD sReserved;
    DWORD nDescription;
    DWORD offDescription;
    DWORD nPalEntries;
    SIZEL szlDevice;
    SIZEL szlMillimeters;
    DWORD cbPixelFormat;
    DWORD offPixelFormat;
    DWORD bOpenGL;
    SIZEL szlMicrometers;
  } ENHMETAHEADER,*PENHMETAHEADER,*LPENHMETAHEADER;
# 742 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef BYTE BCHAR;




  typedef struct tagTEXTMETRICA {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    BYTE tmFirstChar;
    BYTE tmLastChar;
    BYTE tmDefaultChar;
    BYTE tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
  } TEXTMETRICA,*PTEXTMETRICA,*NPTEXTMETRICA,*LPTEXTMETRICA;

  typedef struct tagTEXTMETRICW {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    WCHAR tmFirstChar;
    WCHAR tmLastChar;
    WCHAR tmDefaultChar;
    WCHAR tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
  } TEXTMETRICW,*PTEXTMETRICW,*NPTEXTMETRICW,*LPTEXTMETRICW;






  typedef TEXTMETRICA TEXTMETRIC;
  typedef PTEXTMETRICA PTEXTMETRIC;
  typedef NPTEXTMETRICA NPTEXTMETRIC;
  typedef LPTEXTMETRICA LPTEXTMETRIC;
# 816 "c:/program files/tcc/include/winapi/wingdi.h"
# 1 "c:/program files/tcc/include/winapi/pshpack4.h" 1






#pragma pack(push,4)
# 817 "c:/program files/tcc/include/winapi/wingdi.h" 2
  typedef struct tagNEWTEXTMETRICA {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    BYTE tmFirstChar;
    BYTE tmLastChar;
    BYTE tmDefaultChar;
    BYTE tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
    DWORD ntmFlags;
    UINT ntmSizeEM;
    UINT ntmCellHeight;
    UINT ntmAvgWidth;
  } NEWTEXTMETRICA,*PNEWTEXTMETRICA,*NPNEWTEXTMETRICA,*LPNEWTEXTMETRICA;

  typedef struct tagNEWTEXTMETRICW {
    LONG tmHeight;
    LONG tmAscent;
    LONG tmDescent;
    LONG tmInternalLeading;
    LONG tmExternalLeading;
    LONG tmAveCharWidth;
    LONG tmMaxCharWidth;
    LONG tmWeight;
    LONG tmOverhang;
    LONG tmDigitizedAspectX;
    LONG tmDigitizedAspectY;
    WCHAR tmFirstChar;
    WCHAR tmLastChar;
    WCHAR tmDefaultChar;
    WCHAR tmBreakChar;
    BYTE tmItalic;
    BYTE tmUnderlined;
    BYTE tmStruckOut;
    BYTE tmPitchAndFamily;
    BYTE tmCharSet;
    DWORD ntmFlags;
    UINT ntmSizeEM;
    UINT ntmCellHeight;
    UINT ntmAvgWidth;
  } NEWTEXTMETRICW,*PNEWTEXTMETRICW,*NPNEWTEXTMETRICW,*LPNEWTEXTMETRICW;






  typedef NEWTEXTMETRICA NEWTEXTMETRIC;
  typedef PNEWTEXTMETRICA PNEWTEXTMETRIC;
  typedef NPNEWTEXTMETRICA NPNEWTEXTMETRIC;
  typedef LPNEWTEXTMETRICA LPNEWTEXTMETRIC;

# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 882 "c:/program files/tcc/include/winapi/wingdi.h" 2

  typedef struct tagNEWTEXTMETRICEXA {
    NEWTEXTMETRICA ntmTm;
    FONTSIGNATURE ntmFontSig;
  } NEWTEXTMETRICEXA;

  typedef struct tagNEWTEXTMETRICEXW {
    NEWTEXTMETRICW ntmTm;
    FONTSIGNATURE ntmFontSig;
  } NEWTEXTMETRICEXW;



  typedef NEWTEXTMETRICEXA NEWTEXTMETRICEX;



  typedef struct tagPELARRAY {
    LONG paXCount;
    LONG paYCount;
    LONG paXExt;
    LONG paYExt;
    BYTE paRGBs;
  } PELARRAY,*PPELARRAY,*NPPELARRAY,*LPPELARRAY;

  typedef struct tagLOGBRUSH {
    UINT lbStyle;
    COLORREF lbColor;
    ULONG_PTR lbHatch;
  } LOGBRUSH,*PLOGBRUSH,*NPLOGBRUSH,*LPLOGBRUSH;

  typedef struct tagLOGBRUSH32 {
    UINT lbStyle;
    COLORREF lbColor;
    ULONG lbHatch;
  } LOGBRUSH32,*PLOGBRUSH32,*NPLOGBRUSH32,*LPLOGBRUSH32;

  typedef LOGBRUSH PATTERN;
  typedef PATTERN *PPATTERN;
  typedef PATTERN *NPPATTERN;
  typedef PATTERN *LPPATTERN;

  typedef struct tagLOGPEN {
    UINT lopnStyle;
    POINT lopnWidth;
    COLORREF lopnColor;
  } LOGPEN,*PLOGPEN,*NPLOGPEN,*LPLOGPEN;

  typedef struct tagEXTLOGPEN {
    DWORD elpPenStyle;
    DWORD elpWidth;
    UINT elpBrushStyle;
    COLORREF elpColor;
    ULONG_PTR elpHatch;
    DWORD elpNumEntries;
    DWORD elpStyleEntry[1];
  } EXTLOGPEN,*PEXTLOGPEN,*NPEXTLOGPEN,*LPEXTLOGPEN;



  typedef struct tagPALETTEENTRY {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
  } PALETTEENTRY,*PPALETTEENTRY,*LPPALETTEENTRY;





  typedef struct tagLOGPALETTE {
    WORD palVersion;
    WORD palNumEntries;
    PALETTEENTRY palPalEntry[1];
  } LOGPALETTE,*PLOGPALETTE,*NPLOGPALETTE,*LPLOGPALETTE;




  typedef struct tagLOGFONTA {
    LONG lfHeight;
    LONG lfWidth;
    LONG lfEscapement;
    LONG lfOrientation;
    LONG lfWeight;
    BYTE lfItalic;
    BYTE lfUnderline;
    BYTE lfStrikeOut;
    BYTE lfCharSet;
    BYTE lfOutPrecision;
    BYTE lfClipPrecision;
    BYTE lfQuality;
    BYTE lfPitchAndFamily;
    CHAR lfFaceName[32];
  } LOGFONTA,*PLOGFONTA,*NPLOGFONTA,*LPLOGFONTA;

  typedef struct tagLOGFONTW {
    LONG lfHeight;
    LONG lfWidth;
    LONG lfEscapement;
    LONG lfOrientation;
    LONG lfWeight;
    BYTE lfItalic;
    BYTE lfUnderline;
    BYTE lfStrikeOut;
    BYTE lfCharSet;
    BYTE lfOutPrecision;
    BYTE lfClipPrecision;
    BYTE lfQuality;
    BYTE lfPitchAndFamily;
    WCHAR lfFaceName[32];
  } LOGFONTW,*PLOGFONTW,*NPLOGFONTW,*LPLOGFONTW;






  typedef LOGFONTA LOGFONT;
  typedef PLOGFONTA PLOGFONT;
  typedef NPLOGFONTA NPLOGFONT;
  typedef LPLOGFONTA LPLOGFONT;




  typedef struct tagENUMLOGFONTA {
    LOGFONTA elfLogFont;
    BYTE elfFullName[64];
    BYTE elfStyle[32];
  } ENUMLOGFONTA,*LPENUMLOGFONTA;

  typedef struct tagENUMLOGFONTW {
    LOGFONTW elfLogFont;
    WCHAR elfFullName[64];
    WCHAR elfStyle[32];
  } ENUMLOGFONTW,*LPENUMLOGFONTW;




  typedef ENUMLOGFONTA ENUMLOGFONT;
  typedef LPENUMLOGFONTA LPENUMLOGFONT;


  typedef struct tagENUMLOGFONTEXA {
    LOGFONTA elfLogFont;
    BYTE elfFullName[64];
    BYTE elfStyle[32];
    BYTE elfScript[32];
  } ENUMLOGFONTEXA,*LPENUMLOGFONTEXA;

  typedef struct tagENUMLOGFONTEXW {
    LOGFONTW elfLogFont;
    WCHAR elfFullName[64];
    WCHAR elfStyle[32];
    WCHAR elfScript[32];
  } ENUMLOGFONTEXW,*LPENUMLOGFONTEXW;




  typedef ENUMLOGFONTEXA ENUMLOGFONTEX;
  typedef LPENUMLOGFONTEXA LPENUMLOGFONTEX;
# 1164 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagPANOSE {
    BYTE bFamilyType;
    BYTE bSerifStyle;
    BYTE bWeight;
    BYTE bProportion;
    BYTE bContrast;
    BYTE bStrokeVariation;
    BYTE bArmStyle;
    BYTE bLetterform;
    BYTE bMidline;
    BYTE bXHeight;
  } PANOSE,*LPPANOSE;
# 1285 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagEXTLOGFONTA {
    LOGFONTA elfLogFont;
    BYTE elfFullName[64];
    BYTE elfStyle[32];
    DWORD elfVersion;
    DWORD elfStyleSize;
    DWORD elfMatch;
    DWORD elfReserved;
    BYTE elfVendorId[4];
    DWORD elfCulture;
    PANOSE elfPanose;
  } EXTLOGFONTA,*PEXTLOGFONTA,*NPEXTLOGFONTA,*LPEXTLOGFONTA;

  typedef struct tagEXTLOGFONTW {
    LOGFONTW elfLogFont;
    WCHAR elfFullName[64];
    WCHAR elfStyle[32];
    DWORD elfVersion;
    DWORD elfStyleSize;
    DWORD elfMatch;
    DWORD elfReserved;
    BYTE elfVendorId[4];
    DWORD elfCulture;
    PANOSE elfPanose;
  } EXTLOGFONTW,*PEXTLOGFONTW,*NPEXTLOGFONTW,*LPEXTLOGFONTW;






  typedef EXTLOGFONTA EXTLOGFONT;
  typedef PEXTLOGFONTA PEXTLOGFONT;
  typedef NPEXTLOGFONTA NPEXTLOGFONT;
  typedef LPEXTLOGFONTA LPEXTLOGFONT;
# 1606 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _devicemodeA {
    BYTE dmDeviceName[32];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    union {
      struct {
        short dmOrientation;
        short dmPaperSize;
        short dmPaperLength;
        short dmPaperWidth;
        short dmScale;
        short dmCopies;
        short dmDefaultSource;
        short dmPrintQuality;
      };
      struct {
        POINTL dmPosition;
        DWORD dmDisplayOrientation;
        DWORD dmDisplayFixedOutput;
      };
    };
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    BYTE dmFormName[32];
    WORD dmLogPixels;
    DWORD dmBitsPerPel;
    DWORD dmPelsWidth;
    DWORD dmPelsHeight;
    union {
      DWORD dmDisplayFlags;
      DWORD dmNup;
    };
    DWORD dmDisplayFrequency;
    DWORD dmICMMethod;
    DWORD dmICMIntent;
    DWORD dmMediaType;
    DWORD dmDitherType;
    DWORD dmReserved1;
    DWORD dmReserved2;
    DWORD dmPanningWidth;
    DWORD dmPanningHeight;
  } DEVMODEA,*PDEVMODEA,*NPDEVMODEA,*LPDEVMODEA;

  typedef struct _devicemodeW {
    WCHAR dmDeviceName[32];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    union {
      struct {
        short dmOrientation;
        short dmPaperSize;
        short dmPaperLength;
        short dmPaperWidth;
        short dmScale;
        short dmCopies;
        short dmDefaultSource;
        short dmPrintQuality;
      };
      struct {
        POINTL dmPosition;
        DWORD dmDisplayOrientation;
        DWORD dmDisplayFixedOutput;
      };
    };
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    WCHAR dmFormName[32];
    WORD dmLogPixels;
    DWORD dmBitsPerPel;
    DWORD dmPelsWidth;
    DWORD dmPelsHeight;
    union {
      DWORD dmDisplayFlags;
      DWORD dmNup;
    };
    DWORD dmDisplayFrequency;
    DWORD dmICMMethod;
    DWORD dmICMIntent;
    DWORD dmMediaType;
    DWORD dmDitherType;
    DWORD dmReserved1;
    DWORD dmReserved2;
    DWORD dmPanningWidth;
    DWORD dmPanningHeight;
  } DEVMODEW,*PDEVMODEW,*NPDEVMODEW,*LPDEVMODEW;






  typedef DEVMODEA DEVMODE;
  typedef PDEVMODEA PDEVMODE;
  typedef NPDEVMODEA NPDEVMODE;
  typedef LPDEVMODEA LPDEVMODE;
# 1961 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _DISPLAY_DEVICEA {
    DWORD cb;
    CHAR DeviceName[32];
    CHAR DeviceString[128];
    DWORD StateFlags;
    CHAR DeviceID[128];
    CHAR DeviceKey[128];
  } DISPLAY_DEVICEA,*PDISPLAY_DEVICEA,*LPDISPLAY_DEVICEA;
  typedef struct _DISPLAY_DEVICEW {
    DWORD cb;
    WCHAR DeviceName[32];
    WCHAR DeviceString[128];
    DWORD StateFlags;
    WCHAR DeviceID[128];
    WCHAR DeviceKey[128];
  } DISPLAY_DEVICEW,*PDISPLAY_DEVICEW,*LPDISPLAY_DEVICEW;





  typedef DISPLAY_DEVICEA DISPLAY_DEVICE;
  typedef PDISPLAY_DEVICEA PDISPLAY_DEVICE;
  typedef LPDISPLAY_DEVICEA LPDISPLAY_DEVICE;
# 2002 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct _RGNDATAHEADER {
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT rcBound;
  } RGNDATAHEADER,*PRGNDATAHEADER;

  typedef struct _RGNDATA {
    RGNDATAHEADER rdh;
    char Buffer[1];
  } RGNDATA,*PRGNDATA,*NPRGNDATA,*LPRGNDATA;



  typedef struct _ABC {
    int abcA;
    UINT abcB;
    int abcC;
  } ABC,*PABC,*NPABC,*LPABC;

  typedef struct _ABCFLOAT {
    FLOAT abcfA;
    FLOAT abcfB;
    FLOAT abcfC;
  } ABCFLOAT,*PABCFLOAT,*NPABCFLOAT,*LPABCFLOAT;



  typedef struct _OUTLINETEXTMETRICA {
    UINT otmSize;
    TEXTMETRICA otmTextMetrics;
    BYTE otmFiller;
    PANOSE otmPanoseNumber;
    UINT otmfsSelection;
    UINT otmfsType;
    int otmsCharSlopeRise;
    int otmsCharSlopeRun;
    int otmItalicAngle;
    UINT otmEMSquare;
    int otmAscent;
    int otmDescent;
    UINT otmLineGap;
    UINT otmsCapEmHeight;
    UINT otmsXHeight;
    RECT otmrcFontBox;
    int otmMacAscent;
    int otmMacDescent;
    UINT otmMacLineGap;
    UINT otmusMinimumPPEM;
    POINT otmptSubscriptSize;
    POINT otmptSubscriptOffset;
    POINT otmptSuperscriptSize;
    POINT otmptSuperscriptOffset;
    UINT otmsStrikeoutSize;
    int otmsStrikeoutPosition;
    int otmsUnderscoreSize;
    int otmsUnderscorePosition;
    PSTR otmpFamilyName;
    PSTR otmpFaceName;
    PSTR otmpStyleName;
    PSTR otmpFullName;
  } OUTLINETEXTMETRICA,*POUTLINETEXTMETRICA,*NPOUTLINETEXTMETRICA,*LPOUTLINETEXTMETRICA;

  typedef struct _OUTLINETEXTMETRICW {
    UINT otmSize;
    TEXTMETRICW otmTextMetrics;
    BYTE otmFiller;
    PANOSE otmPanoseNumber;
    UINT otmfsSelection;
    UINT otmfsType;
    int otmsCharSlopeRise;
    int otmsCharSlopeRun;
    int otmItalicAngle;
    UINT otmEMSquare;
    int otmAscent;
    int otmDescent;
    UINT otmLineGap;
    UINT otmsCapEmHeight;
    UINT otmsXHeight;
    RECT otmrcFontBox;
    int otmMacAscent;
    int otmMacDescent;
    UINT otmMacLineGap;
    UINT otmusMinimumPPEM;
    POINT otmptSubscriptSize;
    POINT otmptSubscriptOffset;
    POINT otmptSuperscriptSize;
    POINT otmptSuperscriptOffset;
    UINT otmsStrikeoutSize;
    int otmsStrikeoutPosition;
    int otmsUnderscoreSize;
    int otmsUnderscorePosition;
    PSTR otmpFamilyName;
    PSTR otmpFaceName;
    PSTR otmpStyleName;
    PSTR otmpFullName;
  } OUTLINETEXTMETRICW,*POUTLINETEXTMETRICW,*NPOUTLINETEXTMETRICW,*LPOUTLINETEXTMETRICW;






  typedef OUTLINETEXTMETRICA OUTLINETEXTMETRIC;
  typedef POUTLINETEXTMETRICA POUTLINETEXTMETRIC;
  typedef NPOUTLINETEXTMETRICA NPOUTLINETEXTMETRIC;
  typedef LPOUTLINETEXTMETRICA LPOUTLINETEXTMETRIC;



  typedef struct tagPOLYTEXTA {
    int x;
    int y;
    UINT n;
    LPCSTR lpstr;
    UINT uiFlags;
    RECT rcl;
    int *pdx;
  } POLYTEXTA,*PPOLYTEXTA,*NPPOLYTEXTA,*LPPOLYTEXTA;

  typedef struct tagPOLYTEXTW {
    int x;
    int y;
    UINT n;
    LPCWSTR lpstr;
    UINT uiFlags;
    RECT rcl;
    int *pdx;
  } POLYTEXTW,*PPOLYTEXTW,*NPPOLYTEXTW,*LPPOLYTEXTW;






  typedef POLYTEXTA POLYTEXT;
  typedef PPOLYTEXTA PPOLYTEXT;
  typedef NPPOLYTEXTA NPPOLYTEXT;
  typedef LPPOLYTEXTA LPPOLYTEXT;


  typedef struct _FIXED {
    WORD fract;
    short value;
  } FIXED;

  typedef struct _MAT2 {
    FIXED eM11;
    FIXED eM12;
    FIXED eM21;
    FIXED eM22;
  } MAT2,*LPMAT2;

  typedef struct _GLYPHMETRICS {
    UINT gmBlackBoxX;
    UINT gmBlackBoxY;
    POINT gmptGlyphOrigin;
    short gmCellIncX;
    short gmCellIncY;
  } GLYPHMETRICS,*LPGLYPHMETRICS;
# 2181 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagPOINTFX {
    FIXED x;
    FIXED y;
  } POINTFX,*LPPOINTFX;

  typedef struct tagTTPOLYCURVE {
    WORD wType;
    WORD cpfx;
    POINTFX apfx[1];
  } TTPOLYCURVE,*LPTTPOLYCURVE;

  typedef struct tagTTPOLYGONHEADER {
    DWORD cb;
    DWORD dwType;
    POINTFX pfxStart;
  } TTPOLYGONHEADER,*LPTTPOLYGONHEADER;
# 2239 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagGCP_RESULTSA {
    DWORD lStructSize;
    LPSTR lpOutString;
    UINT *lpOrder;
    int *lpDx;
    int *lpCaretPos;
    LPSTR lpClass;
    LPWSTR lpGlyphs;
    UINT nGlyphs;
    int nMaxFit;
  } GCP_RESULTSA,*LPGCP_RESULTSA;
  typedef struct tagGCP_RESULTSW {
    DWORD lStructSize;
    LPWSTR lpOutString;
    UINT *lpOrder;
    int *lpDx;
    int *lpCaretPos;
    LPSTR lpClass;
    LPWSTR lpGlyphs;
    UINT nGlyphs;
    int nMaxFit;
  } GCP_RESULTSW,*LPGCP_RESULTSW;




  typedef GCP_RESULTSA GCP_RESULTS;
  typedef LPGCP_RESULTSA LPGCP_RESULTS;


  typedef struct _RASTERIZER_STATUS {
    short nSize;
    short wFlags;
    short nLanguageID;
  } RASTERIZER_STATUS,*LPRASTERIZER_STATUS;




  typedef struct tagPIXELFORMATDESCRIPTOR {
    WORD nSize;
    WORD nVersion;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE cColorBits;
    BYTE cRedBits;
    BYTE cRedShift;
    BYTE cGreenBits;
    BYTE cGreenShift;
    BYTE cBlueBits;
    BYTE cBlueShift;
    BYTE cAlphaBits;
    BYTE cAlphaShift;
    BYTE cAccumBits;
    BYTE cAccumRedBits;
    BYTE cAccumGreenBits;
    BYTE cAccumBlueBits;
    BYTE cAccumAlphaBits;
    BYTE cDepthBits;
    BYTE cStencilBits;
    BYTE cAuxBuffers;
    BYTE iLayerType;
    BYTE bReserved;
    DWORD dwLayerMask;
    DWORD dwVisibleMask;
    DWORD dwDamageMask;
  } PIXELFORMATDESCRIPTOR,*PPIXELFORMATDESCRIPTOR,*LPPIXELFORMATDESCRIPTOR;
# 2334 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef int ( *OLDFONTENUMPROCA)(const LOGFONTA *,const TEXTMETRICA *,DWORD,LPARAM);
  typedef int ( *OLDFONTENUMPROCW)(const LOGFONTW *,const TEXTMETRICW *,DWORD,LPARAM);
# 2351 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef OLDFONTENUMPROCA FONTENUMPROCA;
  typedef OLDFONTENUMPROCW FONTENUMPROCW;



  typedef FONTENUMPROCA FONTENUMPROC;


  typedef int ( *GOBJENUMPROC)(LPVOID,LPARAM);
  typedef void ( *LINEDDAPROC)(int,int,LPARAM);
# 2382 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) int  AddFontResourceA(LPCSTR);
  __attribute__((dllimport)) int  AddFontResourceW(LPCWSTR);
  __attribute__((dllimport)) WINBOOL  AnimatePalette(HPALETTE hPal,UINT iStartIndex,UINT cEntries,const PALETTEENTRY *ppe);
  __attribute__((dllimport)) WINBOOL  Arc(HDC hdc,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
  __attribute__((dllimport)) WINBOOL  BitBlt(HDC hdc,int x,int y,int cx,int cy,HDC hdcSrc,int x1,int y1,DWORD rop);
  __attribute__((dllimport)) WINBOOL  CancelDC(HDC hdc);
  __attribute__((dllimport)) WINBOOL  Chord(HDC hdc,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
  __attribute__((dllimport)) int  ChoosePixelFormat(HDC hdc,const PIXELFORMATDESCRIPTOR *ppfd);
  __attribute__((dllimport)) HMETAFILE  CloseMetaFile(HDC hdc);
  __attribute__((dllimport)) int  CombineRgn(HRGN hrgnDst,HRGN hrgnSrc1,HRGN hrgnSrc2,int iMode);
  __attribute__((dllimport)) HMETAFILE  CopyMetaFileA(HMETAFILE,LPCSTR);
  __attribute__((dllimport)) HMETAFILE  CopyMetaFileW(HMETAFILE,LPCWSTR);
  __attribute__((dllimport)) HBITMAP  CreateBitmap(int nWidth,int nHeight,UINT nPlanes,UINT nBitCount,const void *lpBits);
  __attribute__((dllimport)) HBITMAP  CreateBitmapIndirect(const BITMAP *pbm);
  __attribute__((dllimport)) HBRUSH  CreateBrushIndirect(const LOGBRUSH *plbrush);
  __attribute__((dllimport)) HBITMAP  CreateCompatibleBitmap(HDC hdc,int cx,int cy);
  __attribute__((dllimport)) HBITMAP  CreateDiscardableBitmap(HDC hdc,int cx,int cy);
  __attribute__((dllimport)) HDC  CreateCompatibleDC(HDC hdc);
  __attribute__((dllimport)) HDC  CreateDCA(LPCSTR pwszDriver,LPCSTR pwszDevice,LPCSTR pszPort,const DEVMODEA *pdm);
  __attribute__((dllimport)) HDC  CreateDCW(LPCWSTR pwszDriver,LPCWSTR pwszDevice,LPCWSTR pszPort,const DEVMODEW *pdm);
  __attribute__((dllimport)) HBITMAP  CreateDIBitmap(HDC hdc,const BITMAPINFOHEADER *pbmih,DWORD flInit,const void *pjBits,const BITMAPINFO *pbmi,UINT iUsage);
  __attribute__((dllimport)) HBRUSH  CreateDIBPatternBrush(HGLOBAL h,UINT iUsage);
  __attribute__((dllimport)) HBRUSH  CreateDIBPatternBrushPt(const void *lpPackedDIB,UINT iUsage);
  __attribute__((dllimport)) HRGN  CreateEllipticRgn(int x1,int y1,int x2,int y2);
  __attribute__((dllimport)) HRGN  CreateEllipticRgnIndirect(const RECT *lprect);
  __attribute__((dllimport)) HFONT  CreateFontIndirectA(const LOGFONTA *lplf);
  __attribute__((dllimport)) HFONT  CreateFontIndirectW(const LOGFONTW *lplf);
  __attribute__((dllimport)) HFONT  CreateFontA(int cHeight,int cWidth,int cEscapement,int cOrientation,int cWeight,DWORD bItalic,DWORD bUnderline,DWORD bStrikeOut,DWORD iCharSet,DWORD iOutPrecision,DWORD iClipPrecision,DWORD iQuality,DWORD iPitchAndFamily,LPCSTR pszFaceName);
  __attribute__((dllimport)) HFONT  CreateFontW(int cHeight,int cWidth,int cEscapement,int cOrientation,int cWeight,DWORD bItalic,DWORD bUnderline,DWORD bStrikeOut,DWORD iCharSet,DWORD iOutPrecision,DWORD iClipPrecision,DWORD iQuality,DWORD iPitchAndFamily,LPCWSTR pszFaceName);
  __attribute__((dllimport)) HBRUSH  CreateHatchBrush(int iHatch,COLORREF color);
  __attribute__((dllimport)) HDC  CreateICA(LPCSTR pszDriver,LPCSTR pszDevice,LPCSTR pszPort,const DEVMODEA *pdm);
  __attribute__((dllimport)) HDC  CreateICW(LPCWSTR pszDriver,LPCWSTR pszDevice,LPCWSTR pszPort,const DEVMODEW *pdm);
  __attribute__((dllimport)) HDC  CreateMetaFileA(LPCSTR pszFile);
  __attribute__((dllimport)) HDC  CreateMetaFileW(LPCWSTR pszFile);
  __attribute__((dllimport)) HPALETTE  CreatePalette(const LOGPALETTE *plpal);
  __attribute__((dllimport)) HPEN  CreatePen(int iStyle,int cWidth,COLORREF color);
  __attribute__((dllimport)) HPEN  CreatePenIndirect(const LOGPEN *plpen);
  __attribute__((dllimport)) HRGN  CreatePolyPolygonRgn(const POINT *pptl,const INT *pc,int cPoly,int iMode);
  __attribute__((dllimport)) HBRUSH  CreatePatternBrush(HBITMAP hbm);
  __attribute__((dllimport)) HRGN  CreateRectRgn(int x1,int y1,int x2,int y2);
  __attribute__((dllimport)) HRGN  CreateRectRgnIndirect(const RECT *lprect);
  __attribute__((dllimport)) HRGN  CreateRoundRectRgn(int x1,int y1,int x2,int y2,int w,int h);
  __attribute__((dllimport)) WINBOOL  CreateScalableFontResourceA(DWORD fdwHidden,LPCSTR lpszFont,LPCSTR lpszFile,LPCSTR lpszPath);
  __attribute__((dllimport)) WINBOOL  CreateScalableFontResourceW(DWORD fdwHidden,LPCWSTR lpszFont,LPCWSTR lpszFile,LPCWSTR lpszPath);
  __attribute__((dllimport)) HBRUSH  CreateSolidBrush(COLORREF color);
  __attribute__((dllimport)) WINBOOL  DeleteDC(HDC hdc);
  __attribute__((dllimport)) WINBOOL  DeleteMetaFile(HMETAFILE hmf);
  __attribute__((dllimport)) WINBOOL  DeleteObject(HGDIOBJ ho);
  __attribute__((dllimport)) int  DescribePixelFormat(HDC hdc,int iPixelFormat,UINT nBytes,LPPIXELFORMATDESCRIPTOR ppfd);

  typedef UINT ( *LPFNDEVMODE)(HWND,HMODULE,LPDEVMODE,LPSTR,LPSTR,LPDEVMODE,LPSTR,UINT);
  typedef DWORD ( *LPFNDEVCAPS)(LPSTR,LPSTR,UINT,LPSTR,LPDEVMODE);
# 2525 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) int  DeviceCapabilitiesA(LPCSTR pDevice,LPCSTR pPort,WORD fwCapability,LPSTR pOutput,const DEVMODEA *pDevMode);
  __attribute__((dllimport)) int  DeviceCapabilitiesW(LPCWSTR pDevice,LPCWSTR pPort,WORD fwCapability,LPWSTR pOutput,const DEVMODEW *pDevMode);
  __attribute__((dllimport)) int  DrawEscape(HDC hdc,int iEscape,int cjIn,LPCSTR lpIn);
  __attribute__((dllimport)) WINBOOL  Ellipse(HDC hdc,int left,int top,int right,int bottom);
  __attribute__((dllimport)) int  EnumFontFamiliesExA(HDC hdc,LPLOGFONTA lpLogfont,FONTENUMPROCA lpProc,LPARAM lParam,DWORD dwFlags);
  __attribute__((dllimport)) int  EnumFontFamiliesExW(HDC hdc,LPLOGFONTW lpLogfont,FONTENUMPROCW lpProc,LPARAM lParam,DWORD dwFlags);
  __attribute__((dllimport)) int  EnumFontFamiliesA(HDC hdc,LPCSTR lpLogfont,FONTENUMPROCA lpProc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumFontFamiliesW(HDC hdc,LPCWSTR lpLogfont,FONTENUMPROCW lpProc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumFontsA(HDC hdc,LPCSTR lpLogfont,FONTENUMPROCA lpProc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumFontsW(HDC hdc,LPCWSTR lpLogfont,FONTENUMPROCW lpProc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumObjects(HDC hdc,int nType,GOBJENUMPROC lpFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  EqualRgn(HRGN hrgn1,HRGN hrgn2);
  __attribute__((dllimport)) int  Escape(HDC hdc,int iEscape,int cjIn,LPCSTR pvIn,LPVOID pvOut);
  __attribute__((dllimport)) int  ExtEscape(HDC hdc,int iEscape,int cjInput,LPCSTR lpInData,int cjOutput,LPSTR lpOutData);
  __attribute__((dllimport)) int  ExcludeClipRect(HDC hdc,int left,int top,int right,int bottom);
  __attribute__((dllimport)) HRGN  ExtCreateRegion(const XFORM *lpx,DWORD nCount,const RGNDATA *lpData);
  __attribute__((dllimport)) WINBOOL  ExtFloodFill(HDC hdc,int x,int y,COLORREF color,UINT type);
  __attribute__((dllimport)) WINBOOL  FillRgn(HDC hdc,HRGN hrgn,HBRUSH hbr);
  __attribute__((dllimport)) WINBOOL  FloodFill(HDC hdc,int x,int y,COLORREF color);
  __attribute__((dllimport)) WINBOOL  FrameRgn(HDC hdc,HRGN hrgn,HBRUSH hbr,int w,int h);
  __attribute__((dllimport)) int  GetROP2(HDC hdc);
  __attribute__((dllimport)) WINBOOL  GetAspectRatioFilterEx(HDC hdc,LPSIZE lpsize);
  __attribute__((dllimport)) COLORREF  GetBkColor(HDC hdc);
  __attribute__((dllimport)) COLORREF  GetDCBrushColor(HDC hdc);
  __attribute__((dllimport)) COLORREF  GetDCPenColor(HDC hdc);
  __attribute__((dllimport)) int  GetBkMode(HDC hdc);
  __attribute__((dllimport)) LONG  GetBitmapBits(HBITMAP hbit,LONG cb,LPVOID lpvBits);
  __attribute__((dllimport)) WINBOOL  GetBitmapDimensionEx(HBITMAP hbit,LPSIZE lpsize);
  __attribute__((dllimport)) UINT  GetBoundsRect(HDC hdc,LPRECT lprect,UINT flags);
  __attribute__((dllimport)) WINBOOL  GetBrushOrgEx(HDC hdc,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  GetCharWidthA(HDC hdc,UINT iFirst,UINT iLast,LPINT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharWidthW(HDC hdc,UINT iFirst,UINT iLast,LPINT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharWidth32A(HDC hdc,UINT iFirst,UINT iLast,LPINT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharWidth32W(HDC hdc,UINT iFirst,UINT iLast,LPINT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharWidthFloatA(HDC hdc,UINT iFirst,UINT iLast,PFLOAT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharWidthFloatW(HDC hdc,UINT iFirst,UINT iLast,PFLOAT lpBuffer);
  __attribute__((dllimport)) WINBOOL  GetCharABCWidthsA(HDC hdc,UINT wFirst,UINT wLast,LPABC lpABC);
  __attribute__((dllimport)) WINBOOL  GetCharABCWidthsW(HDC hdc,UINT wFirst,UINT wLast,LPABC lpABC);
  __attribute__((dllimport)) WINBOOL  GetCharABCWidthsFloatA(HDC hdc,UINT iFirst,UINT iLast,LPABCFLOAT lpABC);
  __attribute__((dllimport)) WINBOOL  GetCharABCWidthsFloatW(HDC hdc,UINT iFirst,UINT iLast,LPABCFLOAT lpABC);
  __attribute__((dllimport)) int  GetClipBox(HDC hdc,LPRECT lprect);
  __attribute__((dllimport)) int  GetClipRgn(HDC hdc,HRGN hrgn);
  __attribute__((dllimport)) int  GetMetaRgn(HDC hdc,HRGN hrgn);
  __attribute__((dllimport)) HGDIOBJ  GetCurrentObject(HDC hdc,UINT type);
  __attribute__((dllimport)) WINBOOL  GetCurrentPositionEx(HDC hdc,LPPOINT lppt);
  __attribute__((dllimport)) int  GetDeviceCaps(HDC hdc,int index);
  __attribute__((dllimport)) int  GetDIBits(HDC hdc,HBITMAP hbm,UINT start,UINT cLines,LPVOID lpvBits,LPBITMAPINFO lpbmi,UINT usage);
  __attribute__((dllimport)) DWORD  GetFontData (HDC hdc,DWORD dwTable,DWORD dwOffset,PVOID pvBuffer,DWORD cjBuffer);
  __attribute__((dllimport)) DWORD  GetGlyphOutlineA(HDC hdc,UINT uChar,UINT fuFormat,LPGLYPHMETRICS lpgm,DWORD cjBuffer,LPVOID pvBuffer,const MAT2 *lpmat2);
  __attribute__((dllimport)) DWORD  GetGlyphOutlineW(HDC hdc,UINT uChar,UINT fuFormat,LPGLYPHMETRICS lpgm,DWORD cjBuffer,LPVOID pvBuffer,const MAT2 *lpmat2);
  __attribute__((dllimport)) int  GetGraphicsMode(HDC hdc);
  __attribute__((dllimport)) int  GetMapMode(HDC hdc);
  __attribute__((dllimport)) UINT  GetMetaFileBitsEx(HMETAFILE hMF,UINT cbBuffer,LPVOID lpData);
  __attribute__((dllimport)) HMETAFILE  GetMetaFileA(LPCSTR lpName);
  __attribute__((dllimport)) HMETAFILE  GetMetaFileW(LPCWSTR lpName);
  __attribute__((dllimport)) COLORREF  GetNearestColor(HDC hdc,COLORREF color);
  __attribute__((dllimport)) UINT  GetNearestPaletteIndex(HPALETTE h,COLORREF color);
  __attribute__((dllimport)) DWORD  GetObjectType(HGDIOBJ h);
# 2591 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) UINT  GetOutlineTextMetricsA(HDC hdc,UINT cjCopy,LPOUTLINETEXTMETRICA potm);
  __attribute__((dllimport)) UINT  GetOutlineTextMetricsW(HDC hdc,UINT cjCopy,LPOUTLINETEXTMETRICW potm);
# 2607 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) UINT  GetPaletteEntries(HPALETTE hpal,UINT iStart,UINT cEntries,LPPALETTEENTRY pPalEntries);
  __attribute__((dllimport)) COLORREF  GetPixel(HDC hdc,int x,int y);
  __attribute__((dllimport)) int  GetPixelFormat(HDC hdc);
  __attribute__((dllimport)) int  GetPolyFillMode(HDC hdc);
  __attribute__((dllimport)) WINBOOL  GetRasterizerCaps(LPRASTERIZER_STATUS lpraststat,UINT cjBytes);
  __attribute__((dllimport)) int  GetRandomRgn (HDC hdc,HRGN hrgn,INT i);
  __attribute__((dllimport)) DWORD  GetRegionData(HRGN hrgn,DWORD nCount,LPRGNDATA lpRgnData);
  __attribute__((dllimport)) int  GetRgnBox(HRGN hrgn,LPRECT lprc);
  __attribute__((dllimport)) HGDIOBJ  GetStockObject(int i);
  __attribute__((dllimport)) int  GetStretchBltMode(HDC hdc);
  __attribute__((dllimport)) UINT  GetSystemPaletteEntries(HDC hdc,UINT iStart,UINT cEntries,LPPALETTEENTRY pPalEntries);
  __attribute__((dllimport)) UINT  GetSystemPaletteUse(HDC hdc);
  __attribute__((dllimport)) int  GetTextCharacterExtra(HDC hdc);
  __attribute__((dllimport)) UINT  GetTextAlign(HDC hdc);
  __attribute__((dllimport)) COLORREF  GetTextColor(HDC hdc);
  __attribute__((dllimport)) WINBOOL  GetTextExtentPointA(HDC hdc,LPCSTR lpString,int c,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  GetTextExtentPointW(HDC hdc,LPCWSTR lpString,int c,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  GetTextExtentPoint32A(HDC hdc,LPCSTR lpString,int c,LPSIZE psizl);
  __attribute__((dllimport)) WINBOOL  GetTextExtentPoint32W(HDC hdc,LPCWSTR lpString,int c,LPSIZE psizl);
  __attribute__((dllimport)) WINBOOL  GetTextExtentExPointA(HDC hdc,LPCSTR lpszString,int cchString,int nMaxExtent,LPINT lpnFit,LPINT lpnDx,LPSIZE lpSize);
  __attribute__((dllimport)) WINBOOL  GetTextExtentExPointW(HDC hdc,LPCWSTR lpszString,int cchString,int nMaxExtent,LPINT lpnFit,LPINT lpnDx,LPSIZE lpSize);
  __attribute__((dllimport)) int  GetTextCharset(HDC hdc);
  __attribute__((dllimport)) int  GetTextCharsetInfo(HDC hdc,LPFONTSIGNATURE lpSig,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  TranslateCharsetInfo(DWORD *lpSrc,LPCHARSETINFO lpCs,DWORD dwFlags);
  __attribute__((dllimport)) DWORD  GetFontLanguageInfo(HDC hdc);
  __attribute__((dllimport)) DWORD  GetCharacterPlacementA(HDC hdc,LPCSTR lpString,int nCount,int nMexExtent,LPGCP_RESULTSA lpResults,DWORD dwFlags);
  __attribute__((dllimport)) DWORD  GetCharacterPlacementW(HDC hdc,LPCWSTR lpString,int nCount,int nMexExtent,LPGCP_RESULTSW lpResults,DWORD dwFlags);

  typedef struct tagWCRANGE {
    WCHAR wcLow;
    USHORT cGlyphs;
  } WCRANGE,*PWCRANGE,*LPWCRANGE;

  typedef struct tagGLYPHSET {
    DWORD cbThis;
    DWORD flAccel;
    DWORD cGlyphsSupported;
    DWORD cRanges;
    WCRANGE ranges[1];
  } GLYPHSET,*PGLYPHSET,*LPGLYPHSET;
# 2658 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) DWORD  GetFontUnicodeRanges(HDC hdc,LPGLYPHSET lpgs);
  __attribute__((dllimport)) DWORD  GetGlyphIndicesA(HDC hdc,LPCSTR lpstr,int c,LPWORD pgi,DWORD fl);
  __attribute__((dllimport)) DWORD  GetGlyphIndicesW(HDC hdc,LPCWSTR lpstr,int c,LPWORD pgi,DWORD fl);
  __attribute__((dllimport)) WINBOOL  GetTextExtentPointI(HDC hdc,LPWORD pgiIn,int cgi,LPSIZE psize);
  __attribute__((dllimport)) WINBOOL  GetTextExtentExPointI (HDC hdc,LPWORD lpwszString,int cwchString,int nMaxExtent,LPINT lpnFit,LPINT lpnDx,LPSIZE lpSize);
  __attribute__((dllimport)) WINBOOL  GetCharWidthI(HDC hdc,UINT giFirst,UINT cgi,LPWORD pgi,LPINT piWidths);
  __attribute__((dllimport)) WINBOOL  GetCharABCWidthsI(HDC hdc,UINT giFirst,UINT cgi,LPWORD pgi,LPABC pabc);





  typedef struct tagDESIGNVECTOR {
    DWORD dvReserved;
    DWORD dvNumAxes;
    LONG dvValues[16];
  } DESIGNVECTOR,*PDESIGNVECTOR,*LPDESIGNVECTOR;
# 2684 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) int  AddFontResourceExA(LPCSTR name,DWORD fl,PVOID res);
  __attribute__((dllimport)) int  AddFontResourceExW(LPCWSTR name,DWORD fl,PVOID res);
  __attribute__((dllimport)) WINBOOL  RemoveFontResourceExA(LPCSTR name,DWORD fl,PVOID pdv);
  __attribute__((dllimport)) WINBOOL  RemoveFontResourceExW(LPCWSTR name,DWORD fl,PVOID pdv);
  __attribute__((dllimport)) HANDLE  AddFontMemResourceEx(PVOID pFileView,DWORD cjSize,PVOID pvResrved,DWORD *pNumFonts);
  __attribute__((dllimport)) WINBOOL  RemoveFontMemResourceEx(HANDLE h);






  typedef struct tagAXISINFOA {
    LONG axMinValue;
    LONG axMaxValue;
    BYTE axAxisName[16];
  } AXISINFOA,*PAXISINFOA,*LPAXISINFOA;

  typedef struct tagAXISINFOW {
    LONG axMinValue;
    LONG axMaxValue;
    WCHAR axAxisName[16];
  } AXISINFOW,*PAXISINFOW,*LPAXISINFOW;





  typedef AXISINFOA AXISINFO;
  typedef PAXISINFOA PAXISINFO;
  typedef LPAXISINFOA LPAXISINFO;


  typedef struct tagAXESLISTA {
    DWORD axlReserved;
    DWORD axlNumAxes;
    AXISINFOA axlAxisInfo[16];
  } AXESLISTA,*PAXESLISTA,*LPAXESLISTA;

  typedef struct tagAXESLISTW {
    DWORD axlReserved;
    DWORD axlNumAxes;
    AXISINFOW axlAxisInfo[16];
  } AXESLISTW,*PAXESLISTW,*LPAXESLISTW;





  typedef AXESLISTA AXESLIST;
  typedef PAXESLISTA PAXESLIST;
  typedef LPAXESLISTA LPAXESLIST;


  typedef struct tagENUMLOGFONTEXDVA {
    ENUMLOGFONTEXA elfEnumLogfontEx;
    DESIGNVECTOR elfDesignVector;
  } ENUMLOGFONTEXDVA,*PENUMLOGFONTEXDVA,*LPENUMLOGFONTEXDVA;

  typedef struct tagENUMLOGFONTEXDVW {
    ENUMLOGFONTEXW elfEnumLogfontEx;
    DESIGNVECTOR elfDesignVector;
  } ENUMLOGFONTEXDVW,*PENUMLOGFONTEXDVW,*LPENUMLOGFONTEXDVW;





  typedef ENUMLOGFONTEXDVA ENUMLOGFONTEXDV;
  typedef PENUMLOGFONTEXDVA PENUMLOGFONTEXDV;
  typedef LPENUMLOGFONTEXDVA LPENUMLOGFONTEXDV;
# 2763 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) HFONT  CreateFontIndirectExA(const ENUMLOGFONTEXDVA *);
  __attribute__((dllimport)) HFONT  CreateFontIndirectExW(const ENUMLOGFONTEXDVW *);


  typedef struct tagENUMTEXTMETRICA {
    NEWTEXTMETRICEXA etmNewTextMetricEx;
    AXESLISTA etmAxesList;
  } ENUMTEXTMETRICA,*PENUMTEXTMETRICA,*LPENUMTEXTMETRICA;
  typedef struct tagENUMTEXTMETRICW
  {
    NEWTEXTMETRICEXW etmNewTextMetricEx;
    AXESLISTW etmAxesList;
  } ENUMTEXTMETRICW,*PENUMTEXTMETRICW,*LPENUMTEXTMETRICW;





  typedef ENUMTEXTMETRICA ENUMTEXTMETRIC;
  typedef PENUMTEXTMETRICA PENUMTEXTMETRIC;
  typedef LPENUMTEXTMETRICA LPENUMTEXTMETRIC;
# 2795 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  GetViewportExtEx(HDC hdc,LPSIZE lpsize);
  __attribute__((dllimport)) WINBOOL  GetViewportOrgEx(HDC hdc,LPPOINT lppoint);
  __attribute__((dllimport)) WINBOOL  GetWindowExtEx(HDC hdc,LPSIZE lpsize);
  __attribute__((dllimport)) WINBOOL  GetWindowOrgEx(HDC hdc,LPPOINT lppoint);
  __attribute__((dllimport)) int  IntersectClipRect(HDC hdc,int left,int top,int right,int bottom);
  __attribute__((dllimport)) WINBOOL  InvertRgn(HDC hdc,HRGN hrgn);
  __attribute__((dllimport)) WINBOOL  LineDDA(int xStart,int yStart,int xEnd,int yEnd,LINEDDAPROC lpProc,LPARAM data);
  __attribute__((dllimport)) WINBOOL  LineTo(HDC hdc,int x,int y);
  __attribute__((dllimport)) WINBOOL  MaskBlt(HDC hdcDest,int xDest,int yDest,int width,int height,HDC hdcSrc,int xSrc,int ySrc,HBITMAP hbmMask,int xMask,int yMask,DWORD rop);
  __attribute__((dllimport)) WINBOOL  PlgBlt(HDC hdcDest,const POINT *lpPoint,HDC hdcSrc,int xSrc,int ySrc,int width,int height,HBITMAP hbmMask,int xMask,int yMask);
  __attribute__((dllimport)) int  OffsetClipRgn(HDC hdc,int x,int y);
  __attribute__((dllimport)) int  OffsetRgn(HRGN hrgn,int x,int y);
  __attribute__((dllimport)) WINBOOL  PatBlt(HDC hdc,int x,int y,int w,int h,DWORD rop);
  __attribute__((dllimport)) WINBOOL  Pie(HDC hdc,int left,int top,int right,int bottom,int xr1,int yr1,int xr2,int yr2);
  __attribute__((dllimport)) WINBOOL  PlayMetaFile(HDC hdc,HMETAFILE hmf);
  __attribute__((dllimport)) WINBOOL  PaintRgn(HDC hdc,HRGN hrgn);
  __attribute__((dllimport)) WINBOOL  PolyPolygon(HDC hdc,const POINT *apt,const INT *asz,int csz);
  __attribute__((dllimport)) WINBOOL  PtInRegion(HRGN hrgn,int x,int y);
  __attribute__((dllimport)) WINBOOL  PtVisible(HDC hdc,int x,int y);
  __attribute__((dllimport)) WINBOOL  RectInRegion(HRGN hrgn,const RECT *lprect);
  __attribute__((dllimport)) WINBOOL  RectVisible(HDC hdc,const RECT *lprect);
  __attribute__((dllimport)) WINBOOL  Rectangle(HDC hdc,int left,int top,int right,int bottom);
  __attribute__((dllimport)) WINBOOL  RestoreDC(HDC hdc,int nSavedDC);
  __attribute__((dllimport)) HDC  ResetDCA(HDC hdc,const DEVMODEA *lpdm);
  __attribute__((dllimport)) HDC  ResetDCW(HDC hdc,const DEVMODEW *lpdm);
  __attribute__((dllimport)) UINT  RealizePalette(HDC hdc);
  __attribute__((dllimport)) WINBOOL  RemoveFontResourceA(LPCSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  RemoveFontResourceW(LPCWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  RoundRect(HDC hdc,int left,int top,int right,int bottom,int width,int height);
  __attribute__((dllimport)) WINBOOL  ResizePalette(HPALETTE hpal,UINT n);
  __attribute__((dllimport)) int  SaveDC(HDC hdc);
  __attribute__((dllimport)) int  SelectClipRgn(HDC hdc,HRGN hrgn);
  __attribute__((dllimport)) int  ExtSelectClipRgn(HDC hdc,HRGN hrgn,int mode);
  __attribute__((dllimport)) int  SetMetaRgn(HDC hdc);
  __attribute__((dllimport)) HGDIOBJ  SelectObject(HDC hdc,HGDIOBJ h);
  __attribute__((dllimport)) HPALETTE  SelectPalette(HDC hdc,HPALETTE hPal,WINBOOL bForceBkgd);
  __attribute__((dllimport)) COLORREF  SetBkColor(HDC hdc,COLORREF color);
  __attribute__((dllimport)) COLORREF  SetDCBrushColor(HDC hdc,COLORREF color);
  __attribute__((dllimport)) COLORREF  SetDCPenColor(HDC hdc,COLORREF color);
  __attribute__((dllimport)) int  SetBkMode(HDC hdc,int mode);
  __attribute__((dllimport)) LONG  SetBitmapBits(HBITMAP hbm,DWORD cb,const void *pvBits);
  __attribute__((dllimport)) UINT  SetBoundsRect(HDC hdc,const RECT *lprect,UINT flags);
  __attribute__((dllimport)) int  SetDIBits(HDC hdc,HBITMAP hbm,UINT start,UINT cLines,const void *lpBits,const BITMAPINFO *lpbmi,UINT ColorUse);
  __attribute__((dllimport)) int  SetDIBitsToDevice(HDC hdc,int xDest,int yDest,DWORD w,DWORD h,int xSrc,int ySrc,UINT StartScan,UINT cLines,const void *lpvBits,const BITMAPINFO *lpbmi,UINT ColorUse);
  __attribute__((dllimport)) DWORD  SetMapperFlags(HDC hdc,DWORD flags);
  __attribute__((dllimport)) int  SetGraphicsMode(HDC hdc,int iMode);
  __attribute__((dllimport)) int  SetMapMode(HDC hdc,int iMode);
  __attribute__((dllimport)) DWORD  SetLayout(HDC hdc,DWORD l);
  __attribute__((dllimport)) DWORD  GetLayout(HDC hdc);
  __attribute__((dllimport)) HMETAFILE  SetMetaFileBitsEx(UINT cbBuffer,const BYTE *lpData);
  __attribute__((dllimport)) UINT  SetPaletteEntries(HPALETTE hpal,UINT iStart,UINT cEntries,const PALETTEENTRY *pPalEntries);
  __attribute__((dllimport)) COLORREF  SetPixel(HDC hdc,int x,int y,COLORREF color);
  __attribute__((dllimport)) WINBOOL  SetPixelV(HDC hdc,int x,int y,COLORREF color);
  __attribute__((dllimport)) WINBOOL  SetPixelFormat(HDC hdc,int format,const PIXELFORMATDESCRIPTOR *ppfd);
  __attribute__((dllimport)) int  SetPolyFillMode(HDC hdc,int mode);
  __attribute__((dllimport)) WINBOOL  StretchBlt(HDC hdcDest,int xDest,int yDest,int wDest,int hDest,HDC hdcSrc,int xSrc,int ySrc,int wSrc,int hSrc,DWORD rop);
  __attribute__((dllimport)) WINBOOL  SetRectRgn(HRGN hrgn,int left,int top,int right,int bottom);
  __attribute__((dllimport)) int  StretchDIBits(HDC hdc,int xDest,int yDest,int DestWidth,int DestHeight,int xSrc,int ySrc,int SrcWidth,int SrcHeight,const void *lpBits,const BITMAPINFO *lpbmi,UINT iUsage,DWORD rop);
  __attribute__((dllimport)) int  SetROP2(HDC hdc,int rop2);
  __attribute__((dllimport)) int  SetStretchBltMode(HDC hdc,int mode);
  __attribute__((dllimport)) UINT  SetSystemPaletteUse(HDC hdc,UINT use);
  __attribute__((dllimport)) int  SetTextCharacterExtra(HDC hdc,int extra);
  __attribute__((dllimport)) COLORREF  SetTextColor(HDC hdc,COLORREF color);
  __attribute__((dllimport)) UINT  SetTextAlign(HDC hdc,UINT align);
  __attribute__((dllimport)) WINBOOL  SetTextJustification(HDC hdc,int extra,int count);
  __attribute__((dllimport)) WINBOOL  UpdateColors(HDC hdc);

  typedef USHORT COLOR16;

  typedef struct _TRIVERTEX {
    LONG x;
    LONG y;
    COLOR16 Red;
    COLOR16 Green;
    COLOR16 Blue;
    COLOR16 Alpha;
  } TRIVERTEX,*PTRIVERTEX,*LPTRIVERTEX;

  typedef struct _GRADIENT_TRIANGLE {
    ULONG Vertex1;
    ULONG Vertex2;
    ULONG Vertex3;
  } GRADIENT_TRIANGLE,*PGRADIENT_TRIANGLE,*LPGRADIENT_TRIANGLE;

  typedef struct _GRADIENT_RECT {
    ULONG UpperLeft;
    ULONG LowerRight;
  } GRADIENT_RECT,*PGRADIENT_RECT,*LPGRADIENT_RECT;

  typedef struct _BLENDFUNCTION {
    BYTE BlendOp;
    BYTE BlendFlags;
    BYTE SourceConstantAlpha;
    BYTE AlphaFormat;
  } BLENDFUNCTION,*PBLENDFUNCTION;




  __attribute__((dllimport)) WINBOOL  AlphaBlend(HDC hdcDest,int xoriginDest,int yoriginDest,int wDest,int hDest,HDC hdcSrc,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,BLENDFUNCTION ftn);
  __attribute__((dllimport)) WINBOOL  TransparentBlt(HDC hdcDest,int xoriginDest,int yoriginDest,int wDest,int hDest,HDC hdcSrc,int xoriginSrc,int yoriginSrc,int wSrc,int hSrc,UINT crTransparent);






  __attribute__((dllimport)) WINBOOL  GradientFill(HDC hdc,PTRIVERTEX pVertex,ULONG nVertex,PVOID pMesh,ULONG nMesh,ULONG ulMode);
# 2918 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  PlayMetaFileRecord(HDC hdc,LPHANDLETABLE lpHandleTable,LPMETARECORD lpMR,UINT noObjs);

  typedef int ( *MFENUMPROC)(HDC hdc,HANDLETABLE *lpht,METARECORD *lpMR,int nObj,LPARAM param);

  __attribute__((dllimport)) WINBOOL  EnumMetaFile(HDC hdc,HMETAFILE hmf,MFENUMPROC proc,LPARAM param);

  typedef int ( *ENHMFENUMPROC)(HDC hdc,HANDLETABLE *lpht,const ENHMETARECORD *lpmr,int hHandles,LPARAM data);

  __attribute__((dllimport)) HENHMETAFILE  CloseEnhMetaFile(HDC hdc);
  __attribute__((dllimport)) HENHMETAFILE  CopyEnhMetaFileA(HENHMETAFILE hEnh,LPCSTR lpFileName);
  __attribute__((dllimport)) HENHMETAFILE  CopyEnhMetaFileW(HENHMETAFILE hEnh,LPCWSTR lpFileName);
  __attribute__((dllimport)) HDC  CreateEnhMetaFileA(HDC hdc,LPCSTR lpFilename,const RECT *lprc,LPCSTR lpDesc);
  __attribute__((dllimport)) HDC  CreateEnhMetaFileW(HDC hdc,LPCWSTR lpFilename,const RECT *lprc,LPCWSTR lpDesc);
  __attribute__((dllimport)) WINBOOL  DeleteEnhMetaFile(HENHMETAFILE hmf);
  __attribute__((dllimport)) WINBOOL  EnumEnhMetaFile(HDC hdc,HENHMETAFILE hmf,ENHMFENUMPROC proc,LPVOID param,const RECT *lpRect);
  __attribute__((dllimport)) HENHMETAFILE  GetEnhMetaFileA(LPCSTR lpName);
  __attribute__((dllimport)) HENHMETAFILE  GetEnhMetaFileW(LPCWSTR lpName);
  __attribute__((dllimport)) UINT  GetEnhMetaFileBits(HENHMETAFILE hEMF,UINT nSize,LPBYTE lpData);
  __attribute__((dllimport)) UINT  GetEnhMetaFileDescriptionA(HENHMETAFILE hemf,UINT cchBuffer,LPSTR lpDescription);
  __attribute__((dllimport)) UINT  GetEnhMetaFileDescriptionW(HENHMETAFILE hemf,UINT cchBuffer,LPWSTR lpDescription);
  __attribute__((dllimport)) UINT  GetEnhMetaFileHeader(HENHMETAFILE hemf,UINT nSize,LPENHMETAHEADER lpEnhMetaHeader);
  __attribute__((dllimport)) UINT  GetEnhMetaFilePaletteEntries(HENHMETAFILE hemf,UINT nNumEntries,LPPALETTEENTRY lpPaletteEntries);
  __attribute__((dllimport)) UINT  GetEnhMetaFilePixelFormat(HENHMETAFILE hemf,UINT cbBuffer,PIXELFORMATDESCRIPTOR *ppfd);
  __attribute__((dllimport)) UINT  GetWinMetaFileBits(HENHMETAFILE hemf,UINT cbData16,LPBYTE pData16,INT iMapMode,HDC hdcRef);
  __attribute__((dllimport)) WINBOOL  PlayEnhMetaFile(HDC hdc,HENHMETAFILE hmf,const RECT *lprect);
  __attribute__((dllimport)) WINBOOL  PlayEnhMetaFileRecord(HDC hdc,LPHANDLETABLE pht,const ENHMETARECORD *pmr,UINT cht);
  __attribute__((dllimport)) HENHMETAFILE  SetEnhMetaFileBits(UINT nSize,const BYTE *pb);
  __attribute__((dllimport)) HENHMETAFILE  SetWinMetaFileBits(UINT nSize,const BYTE *lpMeta16Data,HDC hdcRef,const METAFILEPICT *lpMFP);
  __attribute__((dllimport)) WINBOOL  GdiComment(HDC hdc,UINT nSize,const BYTE *lpData);
# 2956 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  GetTextMetricsA(HDC hdc,LPTEXTMETRICA lptm);
  __attribute__((dllimport)) WINBOOL  GetTextMetricsW(HDC hdc,LPTEXTMETRICW lptm);


  typedef struct tagDIBSECTION {
    BITMAP dsBm;
    BITMAPINFOHEADER dsBmih;
    DWORD dsBitfields[3];
    HANDLE dshSection;
    DWORD dsOffset;
  } DIBSECTION,*LPDIBSECTION,*PDIBSECTION;

  __attribute__((dllimport)) WINBOOL  AngleArc(HDC hdc,int x,int y,DWORD r,FLOAT StartAngle,FLOAT SweepAngle);
  __attribute__((dllimport)) WINBOOL  PolyPolyline(HDC hdc,const POINT *apt,const DWORD *asz,DWORD csz);
  __attribute__((dllimport)) WINBOOL  GetWorldTransform(HDC hdc,LPXFORM lpxf);
  __attribute__((dllimport)) WINBOOL  SetWorldTransform(HDC hdc,const XFORM *lpxf);
  __attribute__((dllimport)) WINBOOL  ModifyWorldTransform(HDC hdc,const XFORM *lpxf,DWORD mode);
  __attribute__((dllimport)) WINBOOL  CombineTransform(LPXFORM lpxfOut,const XFORM *lpxf1,const XFORM *lpxf2);
  __attribute__((dllimport)) HBITMAP  CreateDIBSection(HDC hdc,const BITMAPINFO *lpbmi,UINT usage,void **ppvBits,HANDLE hSection,DWORD offset);
  __attribute__((dllimport)) UINT  GetDIBColorTable(HDC hdc,UINT iStart,UINT cEntries,RGBQUAD *prgbq);
  __attribute__((dllimport)) UINT  SetDIBColorTable(HDC hdc,UINT iStart,UINT cEntries,const RGBQUAD *prgbq);
# 3008 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagCOLORADJUSTMENT {
    WORD caSize;
    WORD caFlags;
    WORD caIlluminantIndex;
    WORD caRedGamma;
    WORD caGreenGamma;
    WORD caBlueGamma;
    WORD caReferenceBlack;
    WORD caReferenceWhite;
    SHORT caContrast;
    SHORT caBrightness;
    SHORT caColorfulness;
    SHORT caRedGreenTint;
  } COLORADJUSTMENT,*PCOLORADJUSTMENT,*LPCOLORADJUSTMENT;

  __attribute__((dllimport)) WINBOOL  SetColorAdjustment(HDC hdc,const COLORADJUSTMENT *lpca);
  __attribute__((dllimport)) WINBOOL  GetColorAdjustment(HDC hdc,LPCOLORADJUSTMENT lpca);
  __attribute__((dllimport)) HPALETTE  CreateHalftonePalette(HDC hdc);

  typedef WINBOOL ( *ABORTPROC)(HDC,int);

  typedef struct _DOCINFOA {
    int cbSize;
    LPCSTR lpszDocName;
    LPCSTR lpszOutput;
    LPCSTR lpszDatatype;
    DWORD fwType;
  } DOCINFOA,*LPDOCINFOA;

  typedef struct _DOCINFOW {
    int cbSize;
    LPCWSTR lpszDocName;
    LPCWSTR lpszOutput;
    LPCWSTR lpszDatatype;
    DWORD fwType;
  } DOCINFOW,*LPDOCINFOW;





  typedef DOCINFOA DOCINFO;
  typedef LPDOCINFOA LPDOCINFO;
# 3072 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) int  StartDocA(HDC hdc,const DOCINFOA *lpdi);
  __attribute__((dllimport)) int  StartDocW(HDC hdc,const DOCINFOW *lpdi);
  __attribute__((dllimport)) int  EndDoc(HDC hdc);
  __attribute__((dllimport)) int  StartPage(HDC hdc);
  __attribute__((dllimport)) int  EndPage(HDC hdc);
  __attribute__((dllimport)) int  AbortDoc(HDC hdc);
  __attribute__((dllimport)) int  SetAbortProc(HDC hdc,ABORTPROC proc);
  __attribute__((dllimport)) WINBOOL  AbortPath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  ArcTo(HDC hdc,int left,int top,int right,int bottom,int xr1,int yr1,int xr2,int yr2);
  __attribute__((dllimport)) WINBOOL  BeginPath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  CloseFigure(HDC hdc);
  __attribute__((dllimport)) WINBOOL  EndPath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  FillPath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  FlattenPath(HDC hdc);
  __attribute__((dllimport)) int  GetPath(HDC hdc,LPPOINT apt,LPBYTE aj,int cpt);
  __attribute__((dllimport)) HRGN  PathToRegion(HDC hdc);
  __attribute__((dllimport)) WINBOOL  PolyDraw(HDC hdc,const POINT *apt,const BYTE *aj,int cpt);
  __attribute__((dllimport)) WINBOOL  SelectClipPath(HDC hdc,int mode);
  __attribute__((dllimport)) int  SetArcDirection(HDC hdc,int dir);
  __attribute__((dllimport)) WINBOOL  SetMiterLimit(HDC hdc,FLOAT limit,PFLOAT old);
  __attribute__((dllimport)) WINBOOL  StrokeAndFillPath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  StrokePath(HDC hdc);
  __attribute__((dllimport)) WINBOOL  WidenPath(HDC hdc);
  __attribute__((dllimport)) HPEN  ExtCreatePen(DWORD iPenStyle,DWORD cWidth,const LOGBRUSH *plbrush,DWORD cStyle,const DWORD *pstyle);
  __attribute__((dllimport)) WINBOOL  GetMiterLimit(HDC hdc,PFLOAT plimit);
  __attribute__((dllimport)) int  GetArcDirection(HDC hdc);
  __attribute__((dllimport)) int  GetObjectA(HANDLE h,int c,LPVOID pv);
  __attribute__((dllimport)) int  GetObjectW(HANDLE h,int c,LPVOID pv);
  __attribute__((dllimport)) WINBOOL  MoveToEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  TextOutA(HDC hdc,int x,int y,LPCSTR lpString,int c);
  __attribute__((dllimport)) WINBOOL  TextOutW(HDC hdc,int x,int y,LPCWSTR lpString,int c);
  __attribute__((dllimport)) WINBOOL  ExtTextOutA(HDC hdc,int x,int y,UINT options,const RECT *lprect,LPCSTR lpString,UINT c,const INT *lpDx);
  __attribute__((dllimport)) WINBOOL  ExtTextOutW(HDC hdc,int x,int y,UINT options,const RECT *lprect,LPCWSTR lpString,UINT c,const INT *lpDx);
  __attribute__((dllimport)) WINBOOL  PolyTextOutA(HDC hdc,const POLYTEXTA *ppt,int nstrings);
  __attribute__((dllimport)) WINBOOL  PolyTextOutW(HDC hdc,const POLYTEXTW *ppt,int nstrings);
  __attribute__((dllimport)) HRGN  CreatePolygonRgn(const POINT *pptl,int cPoint,int iMode);
  __attribute__((dllimport)) WINBOOL  DPtoLP(HDC hdc,LPPOINT lppt,int c);
  __attribute__((dllimport)) WINBOOL  LPtoDP(HDC hdc,LPPOINT lppt,int c);
  __attribute__((dllimport)) WINBOOL  Polygon(HDC hdc,const POINT *apt,int cpt);
  __attribute__((dllimport)) WINBOOL  Polyline(HDC hdc,const POINT *apt,int cpt);
  __attribute__((dllimport)) WINBOOL  PolyBezier(HDC hdc,const POINT *apt,DWORD cpt);
  __attribute__((dllimport)) WINBOOL  PolyBezierTo(HDC hdc,const POINT *apt,DWORD cpt);
  __attribute__((dllimport)) WINBOOL  PolylineTo(HDC hdc,const POINT *apt,DWORD cpt);
  __attribute__((dllimport)) WINBOOL  SetViewportExtEx(HDC hdc,int x,int y,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  SetViewportOrgEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  SetWindowExtEx(HDC hdc,int x,int y,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  SetWindowOrgEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  OffsetViewportOrgEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  OffsetWindowOrgEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  ScaleViewportExtEx(HDC hdc,int xn,int dx,int yn,int yd,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  ScaleWindowExtEx(HDC hdc,int xn,int xd,int yn,int yd,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  SetBitmapDimensionEx(HBITMAP hbm,int w,int h,LPSIZE lpsz);
  __attribute__((dllimport)) WINBOOL  SetBrushOrgEx(HDC hdc,int x,int y,LPPOINT lppt);
  __attribute__((dllimport)) int  GetTextFaceA(HDC hdc,int c,LPSTR lpName);
  __attribute__((dllimport)) int  GetTextFaceW(HDC hdc,int c,LPWSTR lpName);



  typedef struct tagKERNINGPAIR {
    WORD wFirst;
    WORD wSecond;
    int iKernAmount;
  } KERNINGPAIR,*LPKERNINGPAIR;







  __attribute__((dllimport)) DWORD  GetKerningPairsA(HDC hdc,DWORD nPairs,LPKERNINGPAIR lpKernPair);
  __attribute__((dllimport)) DWORD  GetKerningPairsW(HDC hdc,DWORD nPairs,LPKERNINGPAIR lpKernPair);
  __attribute__((dllimport)) WINBOOL  GetDCOrgEx(HDC hdc,LPPOINT lppt);
  __attribute__((dllimport)) WINBOOL  FixBrushOrgEx(HDC hdc,int x,int y,LPPOINT ptl);
  __attribute__((dllimport)) WINBOOL  UnrealizeObject(HGDIOBJ h);
  __attribute__((dllimport)) WINBOOL  GdiFlush();
  __attribute__((dllimport)) DWORD  GdiSetBatchLimit(DWORD dw);
  __attribute__((dllimport)) DWORD  GdiGetBatchLimit();






  typedef int ( *ICMENUMPROCA)(LPSTR,LPARAM);
  typedef int ( *ICMENUMPROCW)(LPWSTR,LPARAM);
# 3177 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) int  SetICMMode(HDC hdc,int mode);
  __attribute__((dllimport)) WINBOOL  CheckColorsInGamut(HDC hdc,LPVOID lpRGBTriple,LPVOID dlpBuffer,DWORD nCount);
  __attribute__((dllimport)) HCOLORSPACE  GetColorSpace(HDC hdc);
  __attribute__((dllimport)) WINBOOL  GetLogColorSpaceA(HCOLORSPACE hColorSpace,LPLOGCOLORSPACEA lpBuffer,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  GetLogColorSpaceW(HCOLORSPACE hColorSpace,LPLOGCOLORSPACEW lpBuffer,DWORD nSize);
  __attribute__((dllimport)) HCOLORSPACE  CreateColorSpaceA(LPLOGCOLORSPACEA lplcs);
  __attribute__((dllimport)) HCOLORSPACE  CreateColorSpaceW(LPLOGCOLORSPACEW lplcs);
  __attribute__((dllimport)) HCOLORSPACE  SetColorSpace(HDC hdc,HCOLORSPACE hcs);
  __attribute__((dllimport)) WINBOOL  DeleteColorSpace(HCOLORSPACE hcs);
  __attribute__((dllimport)) WINBOOL  GetICMProfileA(HDC hdc,LPDWORD pBufSize,LPSTR pszFilename);
  __attribute__((dllimport)) WINBOOL  GetICMProfileW(HDC hdc,LPDWORD pBufSize,LPWSTR pszFilename);
  __attribute__((dllimport)) WINBOOL  SetICMProfileA(HDC hdc,LPSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  SetICMProfileW(HDC hdc,LPWSTR lpFileName);
  __attribute__((dllimport)) WINBOOL  GetDeviceGammaRamp(HDC hdc,LPVOID lpRamp);
  __attribute__((dllimport)) WINBOOL  SetDeviceGammaRamp(HDC hdc,LPVOID lpRamp);
  __attribute__((dllimport)) WINBOOL  ColorMatchToTarget(HDC hdc,HDC hdcTarget,DWORD action);
  __attribute__((dllimport)) int  EnumICMProfilesA(HDC hdc,ICMENUMPROCA proc,LPARAM param);
  __attribute__((dllimport)) int  EnumICMProfilesW(HDC hdc,ICMENUMPROCW proc,LPARAM param);
  __attribute__((dllimport)) WINBOOL  UpdateICMRegKeyA(DWORD reserved,LPSTR lpszCMID,LPSTR lpszFileName,UINT command);
  __attribute__((dllimport)) WINBOOL  UpdateICMRegKeyW(DWORD reserved,LPWSTR lpszCMID,LPWSTR lpszFileName,UINT command);
  __attribute__((dllimport)) WINBOOL  ColorCorrectPalette(HDC hdc,HPALETTE hPal,DWORD deFirst,DWORD num);
# 3332 "c:/program files/tcc/include/winapi/wingdi.h"
  typedef struct tagEMR {
    DWORD iType;
    DWORD nSize;
  } EMR,*PEMR;

  typedef struct tagEMRTEXT {
    POINTL ptlReference;
    DWORD nChars;
    DWORD offString;
    DWORD fOptions;
    RECTL rcl;
    DWORD offDx;
  } EMRTEXT,*PEMRTEXT;

  typedef struct tagABORTPATH {
    EMR emr;
  } EMRABORTPATH,*PEMRABORTPATH,EMRBEGINPATH,*PEMRBEGINPATH,EMRENDPATH,*PEMRENDPATH,EMRCLOSEFIGURE,*PEMRCLOSEFIGURE,EMRFLATTENPATH,*PEMRFLATTENPATH,EMRWIDENPATH,*PEMRWIDENPATH,EMRSETMETARGN,*PEMRSETMETARGN,EMRSAVEDC,*PEMRSAVEDC,EMRREALIZEPALETTE,*PEMRREALIZEPALETTE;

  typedef struct tagEMRSELECTCLIPPATH {
    EMR emr;
    DWORD iMode;
  } EMRSELECTCLIPPATH,*PEMRSELECTCLIPPATH,EMRSETBKMODE,*PEMRSETBKMODE,EMRSETMAPMODE,*PEMRSETMAPMODE,EMRSETLAYOUT,*PEMRSETLAYOUT,
    EMRSETPOLYFILLMODE,*PEMRSETPOLYFILLMODE,EMRSETROP2,*PEMRSETROP2,EMRSETSTRETCHBLTMODE,*PEMRSETSTRETCHBLTMODE,EMRSETICMMODE,
    *PEMRSETICMMODE,EMRSETTEXTALIGN,*PEMRSETTEXTALIGN;

  typedef struct tagEMRSETMITERLIMIT {
    EMR emr;
    FLOAT eMiterLimit;
  } EMRSETMITERLIMIT,*PEMRSETMITERLIMIT;

  typedef struct tagEMRRESTOREDC {
    EMR emr;
    LONG iRelative;
  } EMRRESTOREDC,*PEMRRESTOREDC;

  typedef struct tagEMRSETARCDIRECTION {
    EMR emr;
    DWORD iArcDirection;

  } EMRSETARCDIRECTION,*PEMRSETARCDIRECTION;

  typedef struct tagEMRSETMAPPERFLAGS {
    EMR emr;
    DWORD dwFlags;
  } EMRSETMAPPERFLAGS,*PEMRSETMAPPERFLAGS;

  typedef struct tagEMRSETTEXTCOLOR {
    EMR emr;
    COLORREF crColor;
  } EMRSETBKCOLOR,*PEMRSETBKCOLOR,EMRSETTEXTCOLOR,*PEMRSETTEXTCOLOR;

  typedef struct tagEMRSELECTOBJECT {
    EMR emr;
    DWORD ihObject;
  } EMRSELECTOBJECT,*PEMRSELECTOBJECT,EMRDELETEOBJECT,*PEMRDELETEOBJECT;

  typedef struct tagEMRSELECTPALETTE {
    EMR emr;
    DWORD ihPal;
  } EMRSELECTPALETTE,*PEMRSELECTPALETTE;

  typedef struct tagEMRRESIZEPALETTE {
    EMR emr;
    DWORD ihPal;
    DWORD cEntries;
  } EMRRESIZEPALETTE,*PEMRRESIZEPALETTE;

  typedef struct tagEMRSETPALETTEENTRIES {
    EMR emr;
    DWORD ihPal;
    DWORD iStart;
    DWORD cEntries;
    PALETTEENTRY aPalEntries[1];
  } EMRSETPALETTEENTRIES,*PEMRSETPALETTEENTRIES;

  typedef struct tagEMRSETCOLORADJUSTMENT {
    EMR emr;
    COLORADJUSTMENT ColorAdjustment;
  } EMRSETCOLORADJUSTMENT,*PEMRSETCOLORADJUSTMENT;

  typedef struct tagEMRGDICOMMENT {
    EMR emr;
    DWORD cbData;
    BYTE Data[1];
  } EMRGDICOMMENT,*PEMRGDICOMMENT;

  typedef struct tagEMREOF {
    EMR emr;
    DWORD nPalEntries;
    DWORD offPalEntries;
    DWORD nSizeLast;
  } EMREOF,*PEMREOF;

  typedef struct tagEMRLINETO {
    EMR emr;
    POINTL ptl;
  } EMRLINETO,*PEMRLINETO,EMRMOVETOEX,*PEMRMOVETOEX;

  typedef struct tagEMROFFSETCLIPRGN {
    EMR emr;
    POINTL ptlOffset;
  } EMROFFSETCLIPRGN,*PEMROFFSETCLIPRGN;

  typedef struct tagEMRFILLPATH {
    EMR emr;
    RECTL rclBounds;
  } EMRFILLPATH,*PEMRFILLPATH,EMRSTROKEANDFILLPATH,*PEMRSTROKEANDFILLPATH,EMRSTROKEPATH,*PEMRSTROKEPATH;

  typedef struct tagEMREXCLUDECLIPRECT {
    EMR emr;
    RECTL rclClip;
  } EMREXCLUDECLIPRECT,*PEMREXCLUDECLIPRECT,EMRINTERSECTCLIPRECT,*PEMRINTERSECTCLIPRECT;

  typedef struct tagEMRSETVIEWPORTORGEX {
    EMR emr;
    POINTL ptlOrigin;
  } EMRSETVIEWPORTORGEX,*PEMRSETVIEWPORTORGEX,EMRSETWINDOWORGEX,*PEMRSETWINDOWORGEX,EMRSETBRUSHORGEX,*PEMRSETBRUSHORGEX;

  typedef struct tagEMRSETVIEWPORTEXTEX {
    EMR emr;
    SIZEL szlExtent;
  } EMRSETVIEWPORTEXTEX,*PEMRSETVIEWPORTEXTEX,EMRSETWINDOWEXTEX,*PEMRSETWINDOWEXTEX;

  typedef struct tagEMRSCALEVIEWPORTEXTEX {
    EMR emr;
    LONG xNum;
    LONG xDenom;
    LONG yNum;
    LONG yDenom;
  } EMRSCALEVIEWPORTEXTEX,*PEMRSCALEVIEWPORTEXTEX,EMRSCALEWINDOWEXTEX,*PEMRSCALEWINDOWEXTEX;

  typedef struct tagEMRSETWORLDTRANSFORM {
    EMR emr;
    XFORM xform;
  } EMRSETWORLDTRANSFORM,*PEMRSETWORLDTRANSFORM;

  typedef struct tagEMRMODIFYWORLDTRANSFORM {
    EMR emr;
    XFORM xform;
    DWORD iMode;
  } EMRMODIFYWORLDTRANSFORM,*PEMRMODIFYWORLDTRANSFORM;

  typedef struct tagEMRSETPIXELV {
    EMR emr;
    POINTL ptlPixel;
    COLORREF crColor;
  } EMRSETPIXELV,*PEMRSETPIXELV;

  typedef struct tagEMREXTFLOODFILL {
    EMR emr;
    POINTL ptlStart;
    COLORREF crColor;
    DWORD iMode;
  } EMREXTFLOODFILL,*PEMREXTFLOODFILL;

  typedef struct tagEMRELLIPSE {
    EMR emr;
    RECTL rclBox;
  } EMRELLIPSE,*PEMRELLIPSE,EMRRECTANGLE,*PEMRRECTANGLE;

  typedef struct tagEMRROUNDRECT {
    EMR emr;
    RECTL rclBox;
    SIZEL szlCorner;
  } EMRROUNDRECT,*PEMRROUNDRECT;

  typedef struct tagEMRARC {
    EMR emr;
    RECTL rclBox;
    POINTL ptlStart;
    POINTL ptlEnd;
  } EMRARC,*PEMRARC,EMRARCTO,*PEMRARCTO,EMRCHORD,*PEMRCHORD,EMRPIE,*PEMRPIE;

  typedef struct tagEMRANGLEARC {
    EMR emr;
    POINTL ptlCenter;
    DWORD nRadius;
    FLOAT eStartAngle;
    FLOAT eSweepAngle;
  } EMRANGLEARC,*PEMRANGLEARC;

  typedef struct tagEMRPOLYLINE {
    EMR emr;
    RECTL rclBounds;
    DWORD cptl;
    POINTL aptl[1];
  } EMRPOLYLINE,*PEMRPOLYLINE,EMRPOLYBEZIER,*PEMRPOLYBEZIER,EMRPOLYGON,*PEMRPOLYGON,EMRPOLYBEZIERTO,*PEMRPOLYBEZIERTO,EMRPOLYLINETO,*PEMRPOLYLINETO;

  typedef struct tagEMRPOLYLINE16 {
    EMR emr;
    RECTL rclBounds;
    DWORD cpts;
    POINTS apts[1];
  } EMRPOLYLINE16,*PEMRPOLYLINE16,EMRPOLYBEZIER16,*PEMRPOLYBEZIER16,EMRPOLYGON16,*PEMRPOLYGON16,EMRPOLYBEZIERTO16,*PEMRPOLYBEZIERTO16,EMRPOLYLINETO16,*PEMRPOLYLINETO16;

  typedef struct tagEMRPOLYDRAW {
    EMR emr;
    RECTL rclBounds;
    DWORD cptl;
    POINTL aptl[1];
    BYTE abTypes[1];
  } EMRPOLYDRAW,*PEMRPOLYDRAW;

  typedef struct tagEMRPOLYDRAW16 {
    EMR emr;
    RECTL rclBounds;
    DWORD cpts;
    POINTS apts[1];
    BYTE abTypes[1];
  } EMRPOLYDRAW16,*PEMRPOLYDRAW16;

  typedef struct tagEMRPOLYPOLYLINE {
    EMR emr;
    RECTL rclBounds;
    DWORD nPolys;
    DWORD cptl;
    DWORD aPolyCounts[1];
    POINTL aptl[1];
  } EMRPOLYPOLYLINE,*PEMRPOLYPOLYLINE,EMRPOLYPOLYGON,*PEMRPOLYPOLYGON;

  typedef struct tagEMRPOLYPOLYLINE16 {
    EMR emr;
    RECTL rclBounds;
    DWORD nPolys;
    DWORD cpts;
    DWORD aPolyCounts[1];
    POINTS apts[1];
  } EMRPOLYPOLYLINE16,*PEMRPOLYPOLYLINE16,EMRPOLYPOLYGON16,*PEMRPOLYPOLYGON16;

  typedef struct tagEMRINVERTRGN {
    EMR emr;
    RECTL rclBounds;
    DWORD cbRgnData;
    BYTE RgnData[1];
  } EMRINVERTRGN,*PEMRINVERTRGN,EMRPAINTRGN,*PEMRPAINTRGN;

  typedef struct tagEMRFILLRGN {
    EMR emr;
    RECTL rclBounds;
    DWORD cbRgnData;
    DWORD ihBrush;
    BYTE RgnData[1];
  } EMRFILLRGN,*PEMRFILLRGN;

  typedef struct tagEMRFRAMERGN {
    EMR emr;
    RECTL rclBounds;
    DWORD cbRgnData;
    DWORD ihBrush;
    SIZEL szlStroke;
    BYTE RgnData[1];
  } EMRFRAMERGN,*PEMRFRAMERGN;

  typedef struct tagEMREXTSELECTCLIPRGN {
    EMR emr;
    DWORD cbRgnData;
    DWORD iMode;
    BYTE RgnData[1];
  } EMREXTSELECTCLIPRGN,*PEMREXTSELECTCLIPRGN;

  typedef struct tagEMREXTTEXTOUTA {
    EMR emr;
    RECTL rclBounds;
    DWORD iGraphicsMode;
    FLOAT exScale;
    FLOAT eyScale;
    EMRTEXT emrtext;
  } EMREXTTEXTOUTA,*PEMREXTTEXTOUTA,EMREXTTEXTOUTW,*PEMREXTTEXTOUTW;

  typedef struct tagEMRPOLYTEXTOUTA {
    EMR emr;
    RECTL rclBounds;
    DWORD iGraphicsMode;
    FLOAT exScale;
    FLOAT eyScale;
    LONG cStrings;
    EMRTEXT aemrtext[1];
  } EMRPOLYTEXTOUTA,*PEMRPOLYTEXTOUTA,EMRPOLYTEXTOUTW,*PEMRPOLYTEXTOUTW;

  typedef struct tagEMRBITBLT {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG cxDest;
    LONG cyDest;
    DWORD dwRop;
    LONG xSrc;
    LONG ySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
  } EMRBITBLT,*PEMRBITBLT;

  typedef struct tagEMRSTRETCHBLT {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG cxDest;
    LONG cyDest;
    DWORD dwRop;
    LONG xSrc;
    LONG ySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    LONG cxSrc;
    LONG cySrc;
  } EMRSTRETCHBLT,*PEMRSTRETCHBLT;

  typedef struct tagEMRMASKBLT {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG cxDest;
    LONG cyDest;
    DWORD dwRop;
    LONG xSrc;
    LONG ySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    LONG xMask;
    LONG yMask;
    DWORD iUsageMask;
    DWORD offBmiMask;
    DWORD cbBmiMask;
    DWORD offBitsMask;
    DWORD cbBitsMask;
  } EMRMASKBLT,*PEMRMASKBLT;

  typedef struct tagEMRPLGBLT {
    EMR emr;
    RECTL rclBounds;
    POINTL aptlDest[3];
    LONG xSrc;
    LONG ySrc;
    LONG cxSrc;
    LONG cySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    LONG xMask;
    LONG yMask;
    DWORD iUsageMask;
    DWORD offBmiMask;
    DWORD cbBmiMask;
    DWORD offBitsMask;
    DWORD cbBitsMask;
  } EMRPLGBLT,*PEMRPLGBLT;

  typedef struct tagEMRSETDIBITSTODEVICE {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG xSrc;
    LONG ySrc;
    LONG cxSrc;
    LONG cySrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    DWORD iUsageSrc;
    DWORD iStartScan;
    DWORD cScans;
  } EMRSETDIBITSTODEVICE,*PEMRSETDIBITSTODEVICE;

  typedef struct tagEMRSTRETCHDIBITS {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG xSrc;
    LONG ySrc;
    LONG cxSrc;
    LONG cySrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    DWORD iUsageSrc;
    DWORD dwRop;
    LONG cxDest;
    LONG cyDest;
  } EMRSTRETCHDIBITS,*PEMRSTRETCHDIBITS;

  typedef struct tagEMREXTCREATEFONTINDIRECTW {
    EMR emr;
    DWORD ihFont;
    EXTLOGFONTW elfw;
  } EMREXTCREATEFONTINDIRECTW,*PEMREXTCREATEFONTINDIRECTW;

  typedef struct tagEMRCREATEPALETTE {
    EMR emr;
    DWORD ihPal;
    LOGPALETTE lgpl;
  } EMRCREATEPALETTE,*PEMRCREATEPALETTE;

  typedef struct tagEMRCREATEPEN {
    EMR emr;
    DWORD ihPen;
    LOGPEN lopn;
  } EMRCREATEPEN,*PEMRCREATEPEN;

  typedef struct tagEMREXTCREATEPEN {
    EMR emr;
    DWORD ihPen;
    DWORD offBmi;
    DWORD cbBmi;
    DWORD offBits;
    DWORD cbBits;
    EXTLOGPEN elp;
  } EMREXTCREATEPEN,*PEMREXTCREATEPEN;

  typedef struct tagEMRCREATEBRUSHINDIRECT {
    EMR emr;
    DWORD ihBrush;
    LOGBRUSH32 lb;
  } EMRCREATEBRUSHINDIRECT,*PEMRCREATEBRUSHINDIRECT;

  typedef struct tagEMRCREATEMONOBRUSH {
    EMR emr;
    DWORD ihBrush;
    DWORD iUsage;
    DWORD offBmi;
    DWORD cbBmi;
    DWORD offBits;
    DWORD cbBits;
  } EMRCREATEMONOBRUSH,*PEMRCREATEMONOBRUSH;

  typedef struct tagEMRCREATEDIBPATTERNBRUSHPT {
    EMR emr;
    DWORD ihBrush;
    DWORD iUsage;
    DWORD offBmi;
    DWORD cbBmi;
    DWORD offBits;
    DWORD cbBits;
  } EMRCREATEDIBPATTERNBRUSHPT,*PEMRCREATEDIBPATTERNBRUSHPT;

  typedef struct tagEMRFORMAT {
    DWORD dSignature;
    DWORD nVersion;
    DWORD cbData;
    DWORD offData;
  } EMRFORMAT,*PEMRFORMAT;

  typedef struct tagEMRGLSRECORD {
    EMR emr;
    DWORD cbData;
    BYTE Data[1];
  } EMRGLSRECORD,*PEMRGLSRECORD;

  typedef struct tagEMRGLSBOUNDEDRECORD {
    EMR emr;
    RECTL rclBounds;
    DWORD cbData;
    BYTE Data[1];
  } EMRGLSBOUNDEDRECORD,*PEMRGLSBOUNDEDRECORD;

  typedef struct tagEMRPIXELFORMAT {
    EMR emr;
    PIXELFORMATDESCRIPTOR pfd;
  } EMRPIXELFORMAT,*PEMRPIXELFORMAT;

  typedef struct tagEMRCREATECOLORSPACE {
    EMR emr;
    DWORD ihCS;
    LOGCOLORSPACEA lcs;
  } EMRCREATECOLORSPACE,*PEMRCREATECOLORSPACE;

  typedef struct tagEMRSETCOLORSPACE {
    EMR emr;
    DWORD ihCS;
  } EMRSETCOLORSPACE,*PEMRSETCOLORSPACE,EMRSELECTCOLORSPACE,*PEMRSELECTCOLORSPACE,EMRDELETECOLORSPACE,*PEMRDELETECOLORSPACE;

  typedef struct tagEMREXTESCAPE {
    EMR emr;
    INT iEscape;
    INT cbEscData;
    BYTE EscData[1];
  } EMREXTESCAPE,*PEMREXTESCAPE,EMRDRAWESCAPE,*PEMRDRAWESCAPE;

  typedef struct tagEMRNAMEDESCAPE {
    EMR emr;
    INT iEscape;
    INT cbDriver;
    INT cbEscData;
    BYTE EscData[1];
  } EMRNAMEDESCAPE,*PEMRNAMEDESCAPE;



  typedef struct tagEMRSETICMPROFILE {
    EMR emr;
    DWORD dwFlags;
    DWORD cbName;
    DWORD cbData;
    BYTE Data[1];
  } EMRSETICMPROFILE,*PEMRSETICMPROFILE,EMRSETICMPROFILEA,*PEMRSETICMPROFILEA,EMRSETICMPROFILEW,*PEMRSETICMPROFILEW;



  typedef struct tagEMRCREATECOLORSPACEW {
    EMR emr;
    DWORD ihCS;
    LOGCOLORSPACEW lcs;
    DWORD dwFlags;
    DWORD cbData;
    BYTE Data[1];
  } EMRCREATECOLORSPACEW,*PEMRCREATECOLORSPACEW;



  typedef struct tagCOLORMATCHTOTARGET {
    EMR emr;
    DWORD dwAction;
    DWORD dwFlags;
    DWORD cbName;
    DWORD cbData;
    BYTE Data[1];
  } EMRCOLORMATCHTOTARGET,*PEMRCOLORMATCHTOTARGET;

  typedef struct tagCOLORCORRECTPALETTE {
    EMR emr;
    DWORD ihPalette;
    DWORD nFirstEntry;
    DWORD nPalEntries;
    DWORD nReserved;
  } EMRCOLORCORRECTPALETTE,*PEMRCOLORCORRECTPALETTE;

  typedef struct tagEMRALPHABLEND {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG cxDest;
    LONG cyDest;
    DWORD dwRop;
    LONG xSrc;
    LONG ySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    LONG cxSrc;
    LONG cySrc;
  } EMRALPHABLEND,*PEMRALPHABLEND;

  typedef struct tagEMRGRADIENTFILL {
    EMR emr;
    RECTL rclBounds;
    DWORD nVer;
    DWORD nTri;
    ULONG ulMode;
    TRIVERTEX Ver[1];
  } EMRGRADIENTFILL,*PEMRGRADIENTFILL;

  typedef struct tagEMRTRANSPARENTBLT {
    EMR emr;
    RECTL rclBounds;
    LONG xDest;
    LONG yDest;
    LONG cxDest;
    LONG cyDest;
    DWORD dwRop;
    LONG xSrc;
    LONG ySrc;
    XFORM xformSrc;
    COLORREF crBkColorSrc;
    DWORD iUsageSrc;
    DWORD offBmiSrc;
    DWORD cbBmiSrc;
    DWORD offBitsSrc;
    DWORD cbBitsSrc;
    LONG cxSrc;
    LONG cySrc;
  } EMRTRANSPARENTBLT,*PEMRTRANSPARENTBLT;
# 3950 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  wglCopyContext(HGLRC,HGLRC,UINT);
  __attribute__((dllimport)) HGLRC  wglCreateContext(HDC);
  __attribute__((dllimport)) HGLRC  wglCreateLayerContext(HDC,int);
  __attribute__((dllimport)) WINBOOL  wglDeleteContext(HGLRC);
  __attribute__((dllimport)) HGLRC  wglGetCurrentContext(void);
  __attribute__((dllimport)) HDC  wglGetCurrentDC(void);
  __attribute__((dllimport)) PROC  wglGetProcAddress(LPCSTR);
  __attribute__((dllimport)) WINBOOL  wglMakeCurrent(HDC,HGLRC);
  __attribute__((dllimport)) WINBOOL  wglShareLists(HGLRC,HGLRC);
  __attribute__((dllimport)) WINBOOL  wglUseFontBitmapsA(HDC,DWORD,DWORD,DWORD);
  __attribute__((dllimport)) WINBOOL  wglUseFontBitmapsW(HDC,DWORD,DWORD,DWORD);
  __attribute__((dllimport)) WINBOOL  SwapBuffers(HDC);

  typedef struct _POINTFLOAT {
    FLOAT x;
    FLOAT y;
  } POINTFLOAT,*PPOINTFLOAT;

  typedef struct _GLYPHMETRICSFLOAT {
    FLOAT gmfBlackBoxX;
    FLOAT gmfBlackBoxY;
    POINTFLOAT gmfptGlyphOrigin;
    FLOAT gmfCellIncX;
    FLOAT gmfCellIncY;
  } GLYPHMETRICSFLOAT,*PGLYPHMETRICSFLOAT,*LPGLYPHMETRICSFLOAT;
# 3985 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  wglUseFontOutlinesA(HDC,DWORD,DWORD,DWORD,FLOAT,FLOAT,int,LPGLYPHMETRICSFLOAT);
  __attribute__((dllimport)) WINBOOL  wglUseFontOutlinesW(HDC,DWORD,DWORD,DWORD,FLOAT,FLOAT,int,LPGLYPHMETRICSFLOAT);

  typedef struct tagLAYERPLANEDESCRIPTOR {
    WORD nSize;
    WORD nVersion;
    DWORD dwFlags;
    BYTE iPixelType;
    BYTE cColorBits;
    BYTE cRedBits;
    BYTE cRedShift;
    BYTE cGreenBits;
    BYTE cGreenShift;
    BYTE cBlueBits;
    BYTE cBlueShift;
    BYTE cAlphaBits;
    BYTE cAlphaShift;
    BYTE cAccumBits;
    BYTE cAccumRedBits;
    BYTE cAccumGreenBits;
    BYTE cAccumBlueBits;
    BYTE cAccumAlphaBits;
    BYTE cDepthBits;
    BYTE cStencilBits;
    BYTE cAuxBuffers;
    BYTE iLayerPlane;
    BYTE bReserved;
    COLORREF crTransparent;
  } LAYERPLANEDESCRIPTOR,*PLAYERPLANEDESCRIPTOR,*LPLAYERPLANEDESCRIPTOR;
# 4061 "c:/program files/tcc/include/winapi/wingdi.h"
  __attribute__((dllimport)) WINBOOL  wglDescribeLayerPlane(HDC,int,int,UINT,LPLAYERPLANEDESCRIPTOR);
  __attribute__((dllimport)) int  wglSetLayerPaletteEntries(HDC,int,int,int,const COLORREF *);
  __attribute__((dllimport)) int  wglGetLayerPaletteEntries(HDC,int,int,int,COLORREF *);
  __attribute__((dllimport)) WINBOOL  wglRealizeLayerPalette(HDC,int,WINBOOL);
  __attribute__((dllimport)) WINBOOL  wglSwapLayerBuffers(HDC,UINT);

  typedef struct _WGLSWAP {
    HDC hdc;
    UINT uiFlags;
  } WGLSWAP,*PWGLSWAP,*LPWGLSWAP;



  __attribute__((dllimport)) DWORD  wglSwapMultipleBuffers(UINT,const WGLSWAP *);
# 69 "c:/program files/tcc/include/winapi/windows.h" 2
# 1 "c:/program files/tcc/include/winapi/winuser.h" 1
# 22 "c:/program files/tcc/include/winapi/winuser.h"
  typedef HANDLE HDWP;
  typedef void MENUTEMPLATEA;
  typedef void MENUTEMPLATEW;
  typedef PVOID LPMENUTEMPLATEA;
  typedef PVOID LPMENUTEMPLATEW;





  typedef MENUTEMPLATEA MENUTEMPLATE;
  typedef LPMENUTEMPLATEA LPMENUTEMPLATE;


  typedef LRESULT ( *WNDPROC)(HWND,UINT,WPARAM,LPARAM);
  typedef INT_PTR ( *DLGPROC)(HWND,UINT,WPARAM,LPARAM);
  typedef void ( *TIMERPROC)(HWND,UINT,UINT_PTR,DWORD);
  typedef WINBOOL ( *GRAYSTRINGPROC)(HDC,LPARAM,int);
  typedef WINBOOL ( *WNDENUMPROC)(HWND,LPARAM);
  typedef LRESULT ( *HOOKPROC)(int code,WPARAM wParam,LPARAM lParam);
  typedef void ( *SENDASYNCPROC)(HWND,UINT,ULONG_PTR,LRESULT);
  typedef WINBOOL ( *PROPENUMPROCA)(HWND,LPCSTR,HANDLE);
  typedef WINBOOL ( *PROPENUMPROCW)(HWND,LPCWSTR,HANDLE);
  typedef WINBOOL ( *PROPENUMPROCEXA)(HWND,LPSTR,HANDLE,ULONG_PTR);
  typedef WINBOOL ( *PROPENUMPROCEXW)(HWND,LPWSTR,HANDLE,ULONG_PTR);
  typedef int ( *EDITWORDBREAKPROCA)(LPSTR lpch,int ichCurrent,int cch,int code);
  typedef int ( *EDITWORDBREAKPROCW)(LPWSTR lpch,int ichCurrent,int cch,int code);
  typedef WINBOOL ( *DRAWSTATEPROC)(HDC hdc,LPARAM lData,WPARAM wData,int cx,int cy);






  typedef PROPENUMPROCA PROPENUMPROC;
  typedef PROPENUMPROCEXA PROPENUMPROCEX;
  typedef EDITWORDBREAKPROCA EDITWORDBREAKPROC;


  typedef WINBOOL ( *NAMEENUMPROCA)(LPSTR,LPARAM);
  typedef WINBOOL ( *NAMEENUMPROCW)(LPWSTR,LPARAM);
  typedef NAMEENUMPROCA WINSTAENUMPROCA;
  typedef NAMEENUMPROCA DESKTOPENUMPROCA;
  typedef NAMEENUMPROCW WINSTAENUMPROCW;
  typedef NAMEENUMPROCW DESKTOPENUMPROCW;





  typedef WINSTAENUMPROCA WINSTAENUMPROC;
  typedef DESKTOPENUMPROCA DESKTOPENUMPROC;
# 134 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  wvsprintfA(LPSTR,LPCSTR,va_list arglist);
  __attribute__((dllimport)) int  wvsprintfW(LPWSTR,LPCWSTR,va_list arglist);
  __attribute__((dllimport)) int  wsprintfA(LPSTR,LPCSTR,...);
  __attribute__((dllimport)) int  wsprintfW(LPWSTR,LPCWSTR,...);
# 420 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagCBT_CREATEWNDA {
    struct tagCREATESTRUCTA *lpcs;
    HWND hwndInsertAfter;
  } CBT_CREATEWNDA,*LPCBT_CREATEWNDA;

  typedef struct tagCBT_CREATEWNDW {
    struct tagCREATESTRUCTW *lpcs;
    HWND hwndInsertAfter;
  } CBT_CREATEWNDW,*LPCBT_CREATEWNDW;




  typedef CBT_CREATEWNDA CBT_CREATEWND;
  typedef LPCBT_CREATEWNDA LPCBT_CREATEWND;


  typedef struct tagCBTACTIVATESTRUCT
  {
    WINBOOL fMouse;
    HWND hWndActive;
  } CBTACTIVATESTRUCT,*LPCBTACTIVATESTRUCT;

  typedef struct tagWTSSESSION_NOTIFICATION {
    DWORD cbSize;
    DWORD dwSessionId;

  } WTSSESSION_NOTIFICATION,*PWTSSESSION_NOTIFICATION;
# 554 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct {
    HWND hwnd;
    RECT rc;
  } SHELLHOOKINFO,*LPSHELLHOOKINFO;

  typedef struct tagEVENTMSG {
    UINT message;
    UINT paramL;
    UINT paramH;
    DWORD time;
    HWND hwnd;
  } EVENTMSG,*PEVENTMSGMSG,*NPEVENTMSGMSG,*LPEVENTMSGMSG;

  typedef struct tagEVENTMSG *PEVENTMSG,*NPEVENTMSG,*LPEVENTMSG;

  typedef struct tagCWPSTRUCT {
    LPARAM lParam;
    WPARAM wParam;
    UINT message;
    HWND hwnd;
  } CWPSTRUCT,*PCWPSTRUCT,*NPCWPSTRUCT,*LPCWPSTRUCT;

  typedef struct tagCWPRETSTRUCT {
    LRESULT lResult;
    LPARAM lParam;
    WPARAM wParam;
    UINT message;
    HWND hwnd;
  } CWPRETSTRUCT,*PCWPRETSTRUCT,*NPCWPRETSTRUCT,*LPCWPRETSTRUCT;
# 591 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagKBDLLHOOKSTRUCT {
    DWORD vkCode;
    DWORD scanCode;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
  } KBDLLHOOKSTRUCT,*LPKBDLLHOOKSTRUCT,*PKBDLLHOOKSTRUCT;

  typedef struct tagMSLLHOOKSTRUCT {
    POINT pt;
    DWORD mouseData;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
  } MSLLHOOKSTRUCT,*LPMSLLHOOKSTRUCT,*PMSLLHOOKSTRUCT;

  typedef struct tagDEBUGHOOKINFO {
    DWORD idThread;
    DWORD idThreadInstaller;
    LPARAM lParam;
    WPARAM wParam;
    int code;
  } DEBUGHOOKINFO,*PDEBUGHOOKINFO,*NPDEBUGHOOKINFO,*LPDEBUGHOOKINFO;

  typedef struct tagMOUSEHOOKSTRUCT {
    POINT pt;
    HWND hwnd;
    UINT wHitTestCode;
    ULONG_PTR dwExtraInfo;
  } MOUSEHOOKSTRUCT,*LPMOUSEHOOKSTRUCT,*PMOUSEHOOKSTRUCT;






  typedef struct tagMOUSEHOOKSTRUCTEX {
    MOUSEHOOKSTRUCT _unnamed;
    DWORD mouseData;
  } MOUSEHOOKSTRUCTEX,*LPMOUSEHOOKSTRUCTEX,*PMOUSEHOOKSTRUCTEX;


  typedef struct tagHARDWAREHOOKSTRUCT {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
  } HARDWAREHOOKSTRUCT,*LPHARDWAREHOOKSTRUCT,*PHARDWAREHOOKSTRUCT;
# 667 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HKL  LoadKeyboardLayoutA(LPCSTR pwszKLID,UINT Flags);
  __attribute__((dllimport)) HKL  LoadKeyboardLayoutW(LPCWSTR pwszKLID,UINT Flags);
  __attribute__((dllimport)) HKL  ActivateKeyboardLayout(HKL hkl,UINT Flags);
  __attribute__((dllimport)) int  ToUnicodeEx(UINT wVirtKey,UINT wScanCode,const BYTE *lpKeyState,LPWSTR pwszBuff,int cchBuff,UINT wFlags,HKL dwhkl);
  __attribute__((dllimport)) WINBOOL  UnloadKeyboardLayout(HKL hkl);
  __attribute__((dllimport)) WINBOOL  GetKeyboardLayoutNameA(LPSTR pwszKLID);
  __attribute__((dllimport)) WINBOOL  GetKeyboardLayoutNameW(LPWSTR pwszKLID);
  __attribute__((dllimport)) int  GetKeyboardLayoutList(int nBuff,HKL *lpList);
  __attribute__((dllimport)) HKL  GetKeyboardLayout(DWORD idThread);

  typedef struct tagMOUSEMOVEPOINT {
    int x;
    int y;
    DWORD time;
    ULONG_PTR dwExtraInfo;
  } MOUSEMOVEPOINT,*PMOUSEMOVEPOINT,*LPMOUSEMOVEPOINT;




  __attribute__((dllimport)) int  GetMouseMovePointsEx(UINT cbSize,LPMOUSEMOVEPOINT lppt,LPMOUSEMOVEPOINT lpptBuf,int nBufPoints,DWORD resolution);
# 711 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HDESK  CreateDesktopA(LPCSTR lpszDesktop,LPCSTR lpszDevice,LPDEVMODEA pDevmode,DWORD dwFlags,ACCESS_MASK dwDesiredAccess,LPSECURITY_ATTRIBUTES lpsa);
  __attribute__((dllimport)) HDESK  CreateDesktopW(LPCWSTR lpszDesktop,LPCWSTR lpszDevice,LPDEVMODEW pDevmode,DWORD dwFlags,ACCESS_MASK dwDesiredAccess,LPSECURITY_ATTRIBUTES lpsa);
# 724 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HDESK  OpenDesktopA(LPCSTR lpszDesktop,DWORD dwFlags,WINBOOL fInherit,ACCESS_MASK dwDesiredAccess);
  __attribute__((dllimport)) HDESK  OpenDesktopW(LPCWSTR lpszDesktop,DWORD dwFlags,WINBOOL fInherit,ACCESS_MASK dwDesiredAccess);
  __attribute__((dllimport)) HDESK  OpenInputDesktop(DWORD dwFlags,WINBOOL fInherit,ACCESS_MASK dwDesiredAccess);
  __attribute__((dllimport)) WINBOOL  EnumDesktopsA(HWINSTA hwinsta,DESKTOPENUMPROCA lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  EnumDesktopsW(HWINSTA hwinsta,DESKTOPENUMPROCW lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  EnumDesktopWindows(HDESK hDesktop,WNDENUMPROC lpfn,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  SwitchDesktop(HDESK hDesktop);
  __attribute__((dllimport)) WINBOOL  SetThreadDesktop(HDESK hDesktop);
  __attribute__((dllimport)) WINBOOL  CloseDesktop(HDESK hDesktop);
  __attribute__((dllimport)) HDESK  GetThreadDesktop(DWORD dwThreadId);
# 762 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HWINSTA  CreateWindowStationA(LPCSTR lpwinsta,DWORD dwFlags,ACCESS_MASK dwDesiredAccess,LPSECURITY_ATTRIBUTES lpsa);
  __attribute__((dllimport)) HWINSTA  CreateWindowStationW(LPCWSTR lpwinsta,DWORD dwFlags,ACCESS_MASK dwDesiredAccess,LPSECURITY_ATTRIBUTES lpsa);
  __attribute__((dllimport)) HWINSTA  OpenWindowStationA(LPCSTR lpszWinSta,WINBOOL fInherit,ACCESS_MASK dwDesiredAccess);
  __attribute__((dllimport)) HWINSTA  OpenWindowStationW(LPCWSTR lpszWinSta,WINBOOL fInherit,ACCESS_MASK dwDesiredAccess);
  __attribute__((dllimport)) WINBOOL  EnumWindowStationsA(WINSTAENUMPROCA lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  EnumWindowStationsW(WINSTAENUMPROCW lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  CloseWindowStation(HWINSTA hWinSta);
  __attribute__((dllimport)) WINBOOL  SetProcessWindowStation(HWINSTA hWinSta);
  __attribute__((dllimport)) HWINSTA  GetProcessWindowStation(void);



  __attribute__((dllimport)) WINBOOL  SetUserObjectSecurity(HANDLE hObj,PSECURITY_INFORMATION pSIRequested,PSECURITY_DESCRIPTOR pSID);
  __attribute__((dllimport)) WINBOOL  GetUserObjectSecurity(HANDLE hObj,PSECURITY_INFORMATION pSIRequested,PSECURITY_DESCRIPTOR pSID,DWORD nLength,LPDWORD lpnLengthNeeded);






  typedef struct tagUSEROBJECTFLAGS {
    WINBOOL fInherit;
    WINBOOL fReserved;
    DWORD dwFlags;
  } USEROBJECTFLAGS,*PUSEROBJECTFLAGS;
# 796 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetUserObjectInformationA(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength,LPDWORD lpnLengthNeeded);
  __attribute__((dllimport)) WINBOOL  GetUserObjectInformationW(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength,LPDWORD lpnLengthNeeded);
  __attribute__((dllimport)) WINBOOL  SetUserObjectInformationA(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength);
  __attribute__((dllimport)) WINBOOL  SetUserObjectInformationW(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength);


  typedef struct tagWNDCLASSEXA {
    UINT cbSize;
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
    HICON hIconSm;
  } WNDCLASSEXA,*PWNDCLASSEXA,*NPWNDCLASSEXA,*LPWNDCLASSEXA;

  typedef struct tagWNDCLASSEXW {
    UINT cbSize;
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCWSTR lpszMenuName;
    LPCWSTR lpszClassName;

    HICON hIconSm;
  } WNDCLASSEXW,*PWNDCLASSEXW,*NPWNDCLASSEXW,*LPWNDCLASSEXW;







  typedef WNDCLASSEXA WNDCLASSEX;
  typedef PWNDCLASSEXA PWNDCLASSEX;
  typedef NPWNDCLASSEXA NPWNDCLASSEX;
  typedef LPWNDCLASSEXA LPWNDCLASSEX;


  typedef struct tagWNDCLASSA {
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
  } WNDCLASSA,*PWNDCLASSA,*NPWNDCLASSA,*LPWNDCLASSA;

  typedef struct tagWNDCLASSW {
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCWSTR lpszMenuName;
    LPCWSTR lpszClassName;
  } WNDCLASSW,*PWNDCLASSW,*NPWNDCLASSW,*LPWNDCLASSW;







  typedef WNDCLASSA WNDCLASS;
  typedef PWNDCLASSA PWNDCLASS;
  typedef NPWNDCLASSA NPWNDCLASS;
  typedef LPWNDCLASSA LPWNDCLASS;


  __attribute__((dllimport)) WINBOOL  IsHungAppWindow(HWND hwnd);
  __attribute__((dllimport)) void  DisableProcessWindowsGhosting(void);


  typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
  } MSG,*PMSG,*NPMSG,*LPMSG;
# 1004 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMINMAXINFO {
    POINT ptReserved;
    POINT ptMaxSize;
    POINT ptMaxPosition;
    POINT ptMinTrackSize;
    POINT ptMaxTrackSize;
  } MINMAXINFO,*PMINMAXINFO,*LPMINMAXINFO;
# 1046 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagCOPYDATASTRUCT {
    ULONG_PTR dwData;
    DWORD cbData;
    PVOID lpData;
  } COPYDATASTRUCT,*PCOPYDATASTRUCT;

  typedef struct tagMDINEXTMENU {
    HMENU hmenuIn;
    HMENU hmenuNext;
    HWND hwndNext;
  } MDINEXTMENU,*PMDINEXTMENU,*LPMDINEXTMENU;
# 1354 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) UINT  RegisterWindowMessageA(LPCSTR lpString);
  __attribute__((dllimport)) UINT  RegisterWindowMessageW(LPCWSTR lpString);
# 1369 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagWINDOWPOS {
    HWND hwnd;
    HWND hwndInsertAfter;
    int x;
    int y;
    int cx;
    int cy;
    UINT flags;
  } WINDOWPOS,*LPWINDOWPOS,*PWINDOWPOS;

  typedef struct tagNCCALCSIZE_PARAMS {
    RECT rgrc[3];
    PWINDOWPOS lppos;
  } NCCALCSIZE_PARAMS,*LPNCCALCSIZE_PARAMS;
# 1414 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagTRACKMOUSEEVENT {
    DWORD cbSize;
    DWORD dwFlags;
    HWND hwndTrack;
    DWORD dwHoverTime;
  } TRACKMOUSEEVENT,*LPTRACKMOUSEEVENT;

  __attribute__((dllimport)) WINBOOL  TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack);
# 1542 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DrawEdge(HDC hdc,LPRECT qrc,UINT edge,UINT grfFlags);
# 1586 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DrawFrameControl(HDC,LPRECT,UINT,UINT);
# 1596 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DrawCaption(HWND hwnd,HDC hdc,const RECT *lprect,UINT flags);




  __attribute__((dllimport)) WINBOOL  DrawAnimatedRects(HWND hwnd,int idAni,const RECT *lprcFrom,const RECT *lprcTo);
# 1643 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagACCEL {
    BYTE fVirt;
    WORD key;
    WORD cmd;
  } ACCEL,*LPACCEL;

  typedef struct tagPAINTSTRUCT {
    HDC hdc;
    WINBOOL fErase;
    RECT rcPaint;
    WINBOOL fRestore;
    WINBOOL fIncUpdate;
    BYTE rgbReserved[32];
  } PAINTSTRUCT,*PPAINTSTRUCT,*NPPAINTSTRUCT,*LPPAINTSTRUCT;

  typedef struct tagCREATESTRUCTA {
    LPVOID lpCreateParams;
    HINSTANCE hInstance;
    HMENU hMenu;
    HWND hwndParent;
    int cy;
    int cx;
    int y;
    int x;
    LONG style;
    LPCSTR lpszName;
    LPCSTR lpszClass;
    DWORD dwExStyle;
  } CREATESTRUCTA,*LPCREATESTRUCTA;

  typedef struct tagCREATESTRUCTW {
    LPVOID lpCreateParams;
    HINSTANCE hInstance;
    HMENU hMenu;
    HWND hwndParent;
    int cy;
    int cx;
    int y;
    int x;
    LONG style;
    LPCWSTR lpszName;
    LPCWSTR lpszClass;
    DWORD dwExStyle;
  } CREATESTRUCTW,*LPCREATESTRUCTW;





  typedef CREATESTRUCTA CREATESTRUCT;
  typedef LPCREATESTRUCTA LPCREATESTRUCT;


  typedef struct tagWINDOWPLACEMENT {
    UINT length;
    UINT flags;
    UINT showCmd;
    POINT ptMinPosition;
    POINT ptMaxPosition;
    RECT rcNormalPosition;
  } WINDOWPLACEMENT;
  typedef WINDOWPLACEMENT *PWINDOWPLACEMENT,*LPWINDOWPLACEMENT;





  typedef struct tagNMHDR {
    HWND hwndFrom;
    UINT_PTR idFrom;
    UINT code;
  } NMHDR;

  typedef NMHDR *LPNMHDR;

  typedef struct tagSTYLESTRUCT {
    DWORD styleOld;
    DWORD styleNew;
  } STYLESTRUCT,*LPSTYLESTRUCT;
# 1745 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMEASUREITEMSTRUCT {
    UINT CtlType;
    UINT CtlID;
    UINT itemID;
    UINT itemWidth;
    UINT itemHeight;
    ULONG_PTR itemData;
  } MEASUREITEMSTRUCT,*PMEASUREITEMSTRUCT,*LPMEASUREITEMSTRUCT;

  typedef struct tagDRAWITEMSTRUCT {
    UINT CtlType;
    UINT CtlID;
    UINT itemID;
    UINT itemAction;
    UINT itemState;
    HWND hwndItem;
    HDC hDC;
    RECT rcItem;
    ULONG_PTR itemData;
  } DRAWITEMSTRUCT,*PDRAWITEMSTRUCT,*LPDRAWITEMSTRUCT;

  typedef struct tagDELETEITEMSTRUCT {
    UINT CtlType;
    UINT CtlID;
    UINT itemID;
    HWND hwndItem;
    ULONG_PTR itemData;
  } DELETEITEMSTRUCT,*PDELETEITEMSTRUCT,*LPDELETEITEMSTRUCT;

  typedef struct tagCOMPAREITEMSTRUCT {
    UINT CtlType;
    UINT CtlID;
    HWND hwndItem;
    UINT itemID1;
    ULONG_PTR itemData1;
    UINT itemID2;
    ULONG_PTR itemData2;
    DWORD dwLocaleId;
  } COMPAREITEMSTRUCT,*PCOMPAREITEMSTRUCT,*LPCOMPAREITEMSTRUCT;
# 1796 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetMessageA(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
  __attribute__((dllimport)) WINBOOL  GetMessageW(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
  __attribute__((dllimport)) WINBOOL  TranslateMessage(const MSG *lpMsg);
  __attribute__((dllimport)) LRESULT  DispatchMessageA(const MSG *lpMsg);
  __attribute__((dllimport)) LRESULT  DispatchMessageW(const MSG *lpMsg);
  __attribute__((dllimport)) WINBOOL  SetMessageQueue(int cMessagesMax);
  __attribute__((dllimport)) WINBOOL  PeekMessageA(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
  __attribute__((dllimport)) WINBOOL  PeekMessageW(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
# 1814 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  RegisterHotKey(HWND hWnd,int id,UINT fsModifiers,UINT vk);
  __attribute__((dllimport)) WINBOOL  UnregisterHotKey(HWND hWnd,int id);
# 1857 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  ExitWindowsEx(UINT uFlags,DWORD dwReason);
  __attribute__((dllimport)) WINBOOL  SwapMouseButton(WINBOOL fSwap);
  __attribute__((dllimport)) DWORD  GetMessagePos(void);
  __attribute__((dllimport)) LONG  GetMessageTime(void);
  __attribute__((dllimport)) LPARAM  GetMessageExtraInfo(void);
  __attribute__((dllimport)) WINBOOL  IsWow64Message(void);
  __attribute__((dllimport)) LPARAM  SetMessageExtraInfo(LPARAM lParam);
  __attribute__((dllimport)) LRESULT  SendMessageA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  SendMessageW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  SendMessageTimeoutA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,UINT fuFlags,UINT uTimeout,PDWORD_PTR lpdwResult);
  __attribute__((dllimport)) LRESULT  SendMessageTimeoutW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,UINT fuFlags,UINT uTimeout,PDWORD_PTR lpdwResult);
  __attribute__((dllimport)) WINBOOL  SendNotifyMessageA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  SendNotifyMessageW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  SendMessageCallbackA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,SENDASYNCPROC lpResultCallBack,ULONG_PTR dwData);
  __attribute__((dllimport)) WINBOOL  SendMessageCallbackW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,SENDASYNCPROC lpResultCallBack,ULONG_PTR dwData);

  typedef struct {
    UINT cbSize;
    HDESK hdesk;
    HWND hwnd;
    LUID luid;
  } BSMINFO,*PBSMINFO;
# 1888 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) long  BroadcastSystemMessageExA(DWORD flags,LPDWORD lpInfo,UINT Msg,WPARAM wParam,LPARAM lParam,PBSMINFO pbsmInfo);
  __attribute__((dllimport)) long  BroadcastSystemMessageExW(DWORD flags,LPDWORD lpInfo,UINT Msg,WPARAM wParam,LPARAM lParam,PBSMINFO pbsmInfo);
  __attribute__((dllimport)) long  BroadcastSystemMessageA(DWORD flags,LPDWORD lpInfo,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) long  BroadcastSystemMessageW(DWORD flags,LPDWORD lpInfo,UINT Msg,WPARAM wParam,LPARAM lParam);
# 1914 "c:/program files/tcc/include/winapi/winuser.h"
  typedef PVOID HDEVNOTIFY;
  typedef HDEVNOTIFY *PHDEVNOTIFY;
# 1947 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HDEVNOTIFY  RegisterDeviceNotificationA(HANDLE hRecipient,LPVOID NotificationFilter,DWORD Flags);
  __attribute__((dllimport)) HDEVNOTIFY  RegisterDeviceNotificationW(HANDLE hRecipient,LPVOID NotificationFilter,DWORD Flags);
  __attribute__((dllimport)) WINBOOL  UnregisterDeviceNotification(HDEVNOTIFY Handle);
  __attribute__((dllimport)) WINBOOL  PostMessageA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  PostMessageW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  PostThreadMessageA(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  PostThreadMessageW(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam);






  __attribute__((dllimport)) WINBOOL  AttachThreadInput(DWORD idAttach,DWORD idAttachTo,WINBOOL fAttach);
  __attribute__((dllimport)) WINBOOL  ReplyMessage(LRESULT lResult);
  __attribute__((dllimport)) WINBOOL  WaitMessage(void);
  __attribute__((dllimport)) DWORD  WaitForInputIdle(HANDLE hProcess,DWORD dwMilliseconds);
  __attribute__((dllimport)) LRESULT  DefWindowProcA(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  DefWindowProcW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) void  PostQuitMessage(int nExitCode);
  __attribute__((dllimport)) LRESULT  CallWindowProcA(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  CallWindowProcW(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  InSendMessage(void);
  __attribute__((dllimport)) DWORD  InSendMessageEx(LPVOID lpReserved);







  __attribute__((dllimport)) UINT  GetDoubleClickTime(void);
  __attribute__((dllimport)) WINBOOL  SetDoubleClickTime(UINT);
  __attribute__((dllimport)) ATOM  RegisterClassA(const WNDCLASSA *lpWndClass);
  __attribute__((dllimport)) ATOM  RegisterClassW(const WNDCLASSW *lpWndClass);
  __attribute__((dllimport)) WINBOOL  UnregisterClassA(LPCSTR lpClassName,HINSTANCE hInstance);
  __attribute__((dllimport)) WINBOOL  UnregisterClassW(LPCWSTR lpClassName,HINSTANCE hInstance);
  __attribute__((dllimport)) WINBOOL  GetClassInfoA(HINSTANCE hInstance,LPCSTR lpClassName,LPWNDCLASSA lpWndClass);
  __attribute__((dllimport)) WINBOOL  GetClassInfoW(HINSTANCE hInstance,LPCWSTR lpClassName,LPWNDCLASSW lpWndClass);
  __attribute__((dllimport)) ATOM  RegisterClassExA(const WNDCLASSEXA *);
  __attribute__((dllimport)) ATOM  RegisterClassExW(const WNDCLASSEXW *);
  __attribute__((dllimport)) WINBOOL  GetClassInfoExA(HINSTANCE hInstance,LPCSTR lpszClass,LPWNDCLASSEXA lpwcx);
  __attribute__((dllimport)) WINBOOL  GetClassInfoExW(HINSTANCE hInstance,LPCWSTR lpszClass,LPWNDCLASSEXW lpwcx);





  typedef BOOLEAN ( *PREGISTERCLASSNAMEW)(LPCWSTR);
# 2005 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HWND  CreateWindowExA(DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);
  __attribute__((dllimport)) HWND  CreateWindowExW(DWORD dwExStyle,LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);


  __attribute__((dllimport)) WINBOOL  IsWindow(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  IsMenu(HMENU hMenu);
  __attribute__((dllimport)) WINBOOL  IsChild(HWND hWndParent,HWND hWnd);
  __attribute__((dllimport)) WINBOOL  DestroyWindow(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  ShowWindow(HWND hWnd,int nCmdShow);
  __attribute__((dllimport)) WINBOOL  AnimateWindow(HWND hWnd,DWORD dwTime,DWORD dwFlags);


  __attribute__((dllimport)) WINBOOL  UpdateLayeredWindow(HWND hWnd,HDC hdcDst,POINT *pptDst,SIZE *psize,HDC hdcSrc,POINT *pptSrc,COLORREF crKey,BLENDFUNCTION *pblend,DWORD dwFlags);

  typedef struct tagUPDATELAYEREDWINDOWINFO {
    DWORD cbSize;
    HDC hdcDst;
    POINT const *pptDst;
    SIZE const *psize;
    HDC hdcSrc;
    POINT const *pptSrc;
    COLORREF crKey;
    BLENDFUNCTION const *pblend;
    DWORD dwFlags;
    RECT const *prcDirty;
  } UPDATELAYEREDWINDOWINFO,*PUPDATELAYEREDWINDOWINFO;

  __attribute__((dllimport)) WINBOOL  UpdateLayeredWindowIndirect(HWND hWnd,UPDATELAYEREDWINDOWINFO const *pULWInfo);
  __attribute__((dllimport)) WINBOOL  GetLayeredWindowAttributes(HWND hwnd,COLORREF *pcrKey,BYTE *pbAlpha,DWORD *pdwFlags);



  __attribute__((dllimport)) WINBOOL  PrintWindow(HWND hwnd,HDC hdcBlt,UINT nFlags);
  __attribute__((dllimport)) WINBOOL  SetLayeredWindowAttributes(HWND hwnd,COLORREF crKey,BYTE bAlpha,DWORD dwFlags);
# 2049 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  ShowWindowAsync(HWND hWnd,int nCmdShow);
  __attribute__((dllimport)) WINBOOL  FlashWindow(HWND hWnd,WINBOOL bInvert);

  typedef struct {
    UINT cbSize;
    HWND hwnd;
    DWORD dwFlags;
    UINT uCount;
    DWORD dwTimeout;
  } FLASHWINFO,*PFLASHWINFO;

  __attribute__((dllimport)) WINBOOL  FlashWindowEx(PFLASHWINFO pfwi);
# 2069 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  ShowOwnedPopups(HWND hWnd,WINBOOL fShow);
  __attribute__((dllimport)) WINBOOL  OpenIcon(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  CloseWindow(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  MoveWindow(HWND hWnd,int X,int Y,int nWidth,int nHeight,WINBOOL bRepaint);
  __attribute__((dllimport)) WINBOOL  SetWindowPos(HWND hWnd,HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  GetWindowPlacement(HWND hWnd,WINDOWPLACEMENT *lpwndpl);
  __attribute__((dllimport)) WINBOOL  SetWindowPlacement(HWND hWnd,const WINDOWPLACEMENT *lpwndpl);


  __attribute__((dllimport)) HDWP  BeginDeferWindowPos(int nNumWindows);
  __attribute__((dllimport)) HDWP  DeferWindowPos(HDWP hWinPosInfo,HWND hWnd,HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  EndDeferWindowPos(HDWP hWinPosInfo);


  __attribute__((dllimport)) WINBOOL  IsWindowVisible(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  IsIconic(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  AnyPopup(void);
  __attribute__((dllimport)) WINBOOL  BringWindowToTop(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  IsZoomed(HWND hWnd);
# 2113 "c:/program files/tcc/include/winapi/winuser.h"
# 1 "c:/program files/tcc/include/winapi/pshpack2.h" 1






#pragma pack(push,2)
# 2114 "c:/program files/tcc/include/winapi/winuser.h" 2

  typedef struct {
    DWORD style;
    DWORD dwExtendedStyle;
    WORD cdit;
    short x;
    short y;
    short cx;
    short cy;
  } DLGTEMPLATE;

  typedef DLGTEMPLATE *LPDLGTEMPLATEA;
  typedef DLGTEMPLATE *LPDLGTEMPLATEW;




  typedef LPDLGTEMPLATEA LPDLGTEMPLATE;


  typedef const DLGTEMPLATE *LPCDLGTEMPLATEA;
  typedef const DLGTEMPLATE *LPCDLGTEMPLATEW;




  typedef LPCDLGTEMPLATEA LPCDLGTEMPLATE;


  typedef struct {
    DWORD style;
    DWORD dwExtendedStyle;
    short x;
    short y;
    short cx;
    short cy;
    WORD id;
  } DLGITEMTEMPLATE;

  typedef DLGITEMTEMPLATE *PDLGITEMTEMPLATEA;
  typedef DLGITEMTEMPLATE *PDLGITEMTEMPLATEW;




  typedef PDLGITEMTEMPLATEA PDLGITEMTEMPLATE;


  typedef DLGITEMTEMPLATE *LPDLGITEMTEMPLATEA;
  typedef DLGITEMTEMPLATE *LPDLGITEMTEMPLATEW;




  typedef LPDLGITEMTEMPLATEA LPDLGITEMTEMPLATE;


# 1 "c:/program files/tcc/include/winapi/poppack.h" 1






#pragma pack(pop)
# 2172 "c:/program files/tcc/include/winapi/winuser.h" 2
# 2201 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HWND  CreateDialogParamA(HINSTANCE hInstance,LPCSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) HWND  CreateDialogParamW(HINSTANCE hInstance,LPCWSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) HWND  CreateDialogIndirectParamA(HINSTANCE hInstance,LPCDLGTEMPLATEA lpTemplate,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) HWND  CreateDialogIndirectParamW(HINSTANCE hInstance,LPCDLGTEMPLATEW lpTemplate,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);




  __attribute__((dllimport)) INT_PTR  DialogBoxParamA(HINSTANCE hInstance,LPCSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) INT_PTR  DialogBoxParamW(HINSTANCE hInstance,LPCWSTR lpTemplateName,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) INT_PTR  DialogBoxIndirectParamA(HINSTANCE hInstance,LPCDLGTEMPLATEA hDialogTemplate,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);
  __attribute__((dllimport)) INT_PTR  DialogBoxIndirectParamW(HINSTANCE hInstance,LPCDLGTEMPLATEW hDialogTemplate,HWND hWndParent,DLGPROC lpDialogFunc,LPARAM dwInitParam);




  __attribute__((dllimport)) WINBOOL  EndDialog(HWND hDlg,INT_PTR nResult);
  __attribute__((dllimport)) HWND  GetDlgItem(HWND hDlg,int nIDDlgItem);
  __attribute__((dllimport)) WINBOOL  SetDlgItemInt(HWND hDlg,int nIDDlgItem,UINT uValue,WINBOOL bSigned);
  __attribute__((dllimport)) UINT  GetDlgItemInt(HWND hDlg,int nIDDlgItem,WINBOOL *lpTranslated,WINBOOL bSigned);
  __attribute__((dllimport)) WINBOOL  SetDlgItemTextA(HWND hDlg,int nIDDlgItem,LPCSTR lpString);
  __attribute__((dllimport)) WINBOOL  SetDlgItemTextW(HWND hDlg,int nIDDlgItem,LPCWSTR lpString);
  __attribute__((dllimport)) UINT  GetDlgItemTextA(HWND hDlg,int nIDDlgItem,LPSTR lpString,int cchMax);
  __attribute__((dllimport)) UINT  GetDlgItemTextW(HWND hDlg,int nIDDlgItem,LPWSTR lpString,int cchMax);
  __attribute__((dllimport)) WINBOOL  CheckDlgButton(HWND hDlg,int nIDButton,UINT uCheck);
  __attribute__((dllimport)) WINBOOL  CheckRadioButton(HWND hDlg,int nIDFirstButton,int nIDLastButton,int nIDCheckButton);
  __attribute__((dllimport)) UINT  IsDlgButtonChecked(HWND hDlg,int nIDButton);
  __attribute__((dllimport)) LRESULT  SendDlgItemMessageA(HWND hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  SendDlgItemMessageW(HWND hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) HWND  GetNextDlgGroupItem(HWND hDlg,HWND hCtl,WINBOOL bPrevious);
  __attribute__((dllimport)) HWND  GetNextDlgTabItem(HWND hDlg,HWND hCtl,WINBOOL bPrevious);
  __attribute__((dllimport)) int  GetDlgCtrlID(HWND hWnd);
  __attribute__((dllimport)) long  GetDialogBaseUnits(void);
  __attribute__((dllimport)) LRESULT  DefDlgProcA(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  DefDlgProcW(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);
# 2248 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  CallMsgFilterA(LPMSG lpMsg,int nCode);
  __attribute__((dllimport)) WINBOOL  CallMsgFilterW(LPMSG lpMsg,int nCode);
# 2262 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  OpenClipboard(HWND hWndNewOwner);
  __attribute__((dllimport)) WINBOOL  CloseClipboard(void);
  __attribute__((dllimport)) DWORD  GetClipboardSequenceNumber(void);
  __attribute__((dllimport)) HWND  GetClipboardOwner(void);
  __attribute__((dllimport)) HWND  SetClipboardViewer(HWND hWndNewViewer);
  __attribute__((dllimport)) HWND  GetClipboardViewer(void);
  __attribute__((dllimport)) WINBOOL  ChangeClipboardChain(HWND hWndRemove,HWND hWndNewNext);
  __attribute__((dllimport)) HANDLE  SetClipboardData(UINT uFormat,HANDLE hMem);
  __attribute__((dllimport)) HANDLE  GetClipboardData(UINT uFormat);
  __attribute__((dllimport)) UINT  RegisterClipboardFormatA(LPCSTR lpszFormat);
  __attribute__((dllimport)) UINT  RegisterClipboardFormatW(LPCWSTR lpszFormat);
  __attribute__((dllimport)) int  CountClipboardFormats(void);
  __attribute__((dllimport)) UINT  EnumClipboardFormats(UINT format);
  __attribute__((dllimport)) int  GetClipboardFormatNameA(UINT format,LPSTR lpszFormatName,int cchMaxCount);
  __attribute__((dllimport)) int  GetClipboardFormatNameW(UINT format,LPWSTR lpszFormatName,int cchMaxCount);
  __attribute__((dllimport)) WINBOOL  EmptyClipboard(void);
  __attribute__((dllimport)) WINBOOL  IsClipboardFormatAvailable(UINT format);
  __attribute__((dllimport)) int  GetPriorityClipboardFormat(UINT *paFormatPriorityList,int cFormats);
  __attribute__((dllimport)) HWND  GetOpenClipboardWindow(void);
# 2307 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  CharToOemA(LPCSTR lpszSrc,LPSTR lpszDst);
  __attribute__((dllimport)) WINBOOL  CharToOemW(LPCWSTR lpszSrc,LPSTR lpszDst);
  __attribute__((dllimport)) WINBOOL  OemToCharA(LPCSTR lpszSrc,LPSTR lpszDst);
  __attribute__((dllimport)) WINBOOL  OemToCharW(LPCSTR lpszSrc,LPWSTR lpszDst);
  __attribute__((dllimport)) WINBOOL  CharToOemBuffA(LPCSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
  __attribute__((dllimport)) WINBOOL  CharToOemBuffW(LPCWSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
  __attribute__((dllimport)) WINBOOL  OemToCharBuffA(LPCSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
  __attribute__((dllimport)) WINBOOL  OemToCharBuffW(LPCSTR lpszSrc,LPWSTR lpszDst,DWORD cchDstLength);
  __attribute__((dllimport)) LPSTR  CharUpperA(LPSTR lpsz);
  __attribute__((dllimport)) LPWSTR  CharUpperW(LPWSTR lpsz);
  __attribute__((dllimport)) DWORD  CharUpperBuffA(LPSTR lpsz,DWORD cchLength);
  __attribute__((dllimport)) DWORD  CharUpperBuffW(LPWSTR lpsz,DWORD cchLength);
  __attribute__((dllimport)) LPSTR  CharLowerA(LPSTR lpsz);
  __attribute__((dllimport)) LPWSTR  CharLowerW(LPWSTR lpsz);
  __attribute__((dllimport)) DWORD  CharLowerBuffA(LPSTR lpsz,DWORD cchLength);
  __attribute__((dllimport)) DWORD  CharLowerBuffW(LPWSTR lpsz,DWORD cchLength);
  __attribute__((dllimport)) LPSTR  CharNextA(LPCSTR lpsz);
  __attribute__((dllimport)) LPWSTR  CharNextW(LPCWSTR lpsz);
  __attribute__((dllimport)) LPSTR  CharPrevA(LPCSTR lpszStart,LPCSTR lpszCurrent);
  __attribute__((dllimport)) LPWSTR  CharPrevW(LPCWSTR lpszStart,LPCWSTR lpszCurrent);
  __attribute__((dllimport)) LPSTR  CharNextExA(WORD CodePage,LPCSTR lpCurrentChar,DWORD dwFlags);
  __attribute__((dllimport)) LPSTR  CharPrevExA(WORD CodePage,LPCSTR lpStart,LPCSTR lpCurrentChar,DWORD dwFlags);
# 2355 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  IsCharAlphaA(CHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharAlphaW(WCHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharAlphaNumericA(CHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharAlphaNumericW(WCHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharUpperA(CHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharUpperW(WCHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharLowerA(CHAR ch);
  __attribute__((dllimport)) WINBOOL  IsCharLowerW(WCHAR ch);
# 2375 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HWND  SetFocus(HWND hWnd);
  __attribute__((dllimport)) HWND  GetActiveWindow(void);
  __attribute__((dllimport)) HWND  GetFocus(void);
  __attribute__((dllimport)) UINT  GetKBCodePage(void);
  __attribute__((dllimport)) SHORT  GetKeyState(int nVirtKey);
  __attribute__((dllimport)) SHORT  GetAsyncKeyState(int vKey);
  __attribute__((dllimport)) WINBOOL  GetKeyboardState(PBYTE lpKeyState);
  __attribute__((dllimport)) WINBOOL  SetKeyboardState(LPBYTE lpKeyState);
  __attribute__((dllimport)) int  GetKeyNameTextA(LONG lParam,LPSTR lpString,int cchSize);
  __attribute__((dllimport)) int  GetKeyNameTextW(LONG lParam,LPWSTR lpString,int cchSize);
  __attribute__((dllimport)) int  GetKeyboardType(int nTypeFlag);
  __attribute__((dllimport)) int  ToAscii(UINT uVirtKey,UINT uScanCode,const BYTE *lpKeyState,LPWORD lpChar,UINT uFlags);
  __attribute__((dllimport)) int  ToAsciiEx(UINT uVirtKey,UINT uScanCode,const BYTE *lpKeyState,LPWORD lpChar,UINT uFlags,HKL dwhkl);
  __attribute__((dllimport)) int  ToUnicode(UINT wVirtKey,UINT wScanCode,const BYTE *lpKeyState,LPWSTR pwszBuff,int cchBuff,UINT wFlags);
  __attribute__((dllimport)) DWORD  OemKeyScan(WORD wOemChar);
  __attribute__((dllimport)) SHORT  VkKeyScanA(CHAR ch);
  __attribute__((dllimport)) SHORT  VkKeyScanW(WCHAR ch);
  __attribute__((dllimport)) SHORT  VkKeyScanExA(CHAR ch,HKL dwhkl);
  __attribute__((dllimport)) SHORT  VkKeyScanExW(WCHAR ch,HKL dwhkl);






  __attribute__((dllimport)) void  keybd_event(BYTE bVk,BYTE bScan,DWORD dwFlags,ULONG_PTR dwExtraInfo);
# 2415 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) void  mouse_event(DWORD dwFlags,DWORD dx,DWORD dy,DWORD dwData,ULONG_PTR dwExtraInfo);

  typedef struct tagMOUSEINPUT {
    LONG dx;
    LONG dy;
    DWORD mouseData;
    DWORD dwFlags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
  } MOUSEINPUT,*PMOUSEINPUT,*LPMOUSEINPUT;

  typedef struct tagKEYBDINPUT {
    WORD wVk;
    WORD wScan;
    DWORD dwFlags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
  } KEYBDINPUT,*PKEYBDINPUT,*LPKEYBDINPUT;

  typedef struct tagHARDWAREINPUT {
    DWORD uMsg;
    WORD wParamL;
    WORD wParamH;
  } HARDWAREINPUT,*PHARDWAREINPUT,*LPHARDWAREINPUT;





  typedef struct tagINPUT {
    DWORD type;
    union {
      MOUSEINPUT mi;
      KEYBDINPUT ki;
      HARDWAREINPUT hi;
    };
  } INPUT,*PINPUT,*LPINPUT;

  __attribute__((dllimport)) UINT  SendInput(UINT cInputs,LPINPUT pInputs,int cbSize);

  typedef struct tagLASTINPUTINFO {
    UINT cbSize;
    DWORD dwTime;
  } LASTINPUTINFO,*PLASTINPUTINFO;
# 2468 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetLastInputInfo(PLASTINPUTINFO plii);
  __attribute__((dllimport)) UINT  MapVirtualKeyA(UINT uCode,UINT uMapType);
  __attribute__((dllimport)) UINT  MapVirtualKeyW(UINT uCode,UINT uMapType);
  __attribute__((dllimport)) UINT  MapVirtualKeyExA(UINT uCode,UINT uMapType,HKL dwhkl);
  __attribute__((dllimport)) UINT  MapVirtualKeyExW(UINT uCode,UINT uMapType,HKL dwhkl);
  __attribute__((dllimport)) WINBOOL  GetInputState(void);
  __attribute__((dllimport)) DWORD  GetQueueStatus(UINT flags);
  __attribute__((dllimport)) HWND  GetCapture(void);
  __attribute__((dllimport)) HWND  SetCapture(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  ReleaseCapture(void);
  __attribute__((dllimport)) DWORD  MsgWaitForMultipleObjects(DWORD nCount,const HANDLE *pHandles,WINBOOL fWaitAll,DWORD dwMilliseconds,DWORD dwWakeMask);
  __attribute__((dllimport)) DWORD  MsgWaitForMultipleObjectsEx(DWORD nCount,const HANDLE *pHandles,DWORD dwMilliseconds,DWORD dwWakeMask,DWORD dwFlags);
# 2513 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) UINT_PTR  SetTimer(HWND hWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc);
  __attribute__((dllimport)) WINBOOL  KillTimer(HWND hWnd,UINT_PTR uIDEvent);
  __attribute__((dllimport)) WINBOOL  IsWindowUnicode(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  EnableWindow(HWND hWnd,WINBOOL bEnable);
  __attribute__((dllimport)) WINBOOL  IsWindowEnabled(HWND hWnd);
  __attribute__((dllimport)) HACCEL  LoadAcceleratorsA(HINSTANCE hInstance,LPCSTR lpTableName);
  __attribute__((dllimport)) HACCEL  LoadAcceleratorsW(HINSTANCE hInstance,LPCWSTR lpTableName);
  __attribute__((dllimport)) HACCEL  CreateAcceleratorTableA(LPACCEL paccel,int cAccel);
  __attribute__((dllimport)) HACCEL  CreateAcceleratorTableW(LPACCEL paccel,int cAccel);
  __attribute__((dllimport)) WINBOOL  DestroyAcceleratorTable(HACCEL hAccel);
  __attribute__((dllimport)) int  CopyAcceleratorTableA(HACCEL hAccelSrc,LPACCEL lpAccelDst,int cAccelEntries);
  __attribute__((dllimport)) int  CopyAcceleratorTableW(HACCEL hAccelSrc,LPACCEL lpAccelDst,int cAccelEntries);
# 2534 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  TranslateAcceleratorA(HWND hWnd,HACCEL hAccTable,LPMSG lpMsg);
  __attribute__((dllimport)) int  TranslateAcceleratorW(HWND hWnd,HACCEL hAccTable,LPMSG lpMsg);
# 2638 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  GetSystemMetrics(int nIndex);
# 2661 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HMENU  LoadMenuA(HINSTANCE hInstance,LPCSTR lpMenuName);
  __attribute__((dllimport)) HMENU  LoadMenuW(HINSTANCE hInstance,LPCWSTR lpMenuName);
  __attribute__((dllimport)) HMENU  LoadMenuIndirectA(const MENUTEMPLATEA *lpMenuTemplate);
  __attribute__((dllimport)) HMENU  LoadMenuIndirectW(const MENUTEMPLATEW *lpMenuTemplate);
  __attribute__((dllimport)) HMENU  GetMenu(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  SetMenu(HWND hWnd,HMENU hMenu);
  __attribute__((dllimport)) WINBOOL  ChangeMenuA(HMENU hMenu,UINT cmd,LPCSTR lpszNewItem,UINT cmdInsert,UINT flags);
  __attribute__((dllimport)) WINBOOL  ChangeMenuW(HMENU hMenu,UINT cmd,LPCWSTR lpszNewItem,UINT cmdInsert,UINT flags);
  __attribute__((dllimport)) WINBOOL  HiliteMenuItem(HWND hWnd,HMENU hMenu,UINT uIDHiliteItem,UINT uHilite);
  __attribute__((dllimport)) int  GetMenuStringA(HMENU hMenu,UINT uIDItem,LPSTR lpString,int cchMax,UINT flags);
  __attribute__((dllimport)) int  GetMenuStringW(HMENU hMenu,UINT uIDItem,LPWSTR lpString,int cchMax,UINT flags);
  __attribute__((dllimport)) UINT  GetMenuState(HMENU hMenu,UINT uId,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  DrawMenuBar(HWND hWnd);



  __attribute__((dllimport)) HMENU  GetSystemMenu(HWND hWnd,WINBOOL bRevert);
  __attribute__((dllimport)) HMENU  CreateMenu(void);
  __attribute__((dllimport)) HMENU  CreatePopupMenu(void);
  __attribute__((dllimport)) WINBOOL  DestroyMenu(HMENU hMenu);
  __attribute__((dllimport)) DWORD  CheckMenuItem(HMENU hMenu,UINT uIDCheckItem,UINT uCheck);
  __attribute__((dllimport)) WINBOOL  EnableMenuItem(HMENU hMenu,UINT uIDEnableItem,UINT uEnable);
  __attribute__((dllimport)) HMENU  GetSubMenu(HMENU hMenu,int nPos);
  __attribute__((dllimport)) UINT  GetMenuItemID(HMENU hMenu,int nPos);
  __attribute__((dllimport)) int  GetMenuItemCount(HMENU hMenu);
  __attribute__((dllimport)) WINBOOL  InsertMenuA(HMENU hMenu,UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  InsertMenuW(HMENU hMenu,UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCWSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  AppendMenuA(HMENU hMenu,UINT uFlags,UINT_PTR uIDNewItem,LPCSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  AppendMenuW(HMENU hMenu,UINT uFlags,UINT_PTR uIDNewItem,LPCWSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  ModifyMenuA(HMENU hMnu,UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  ModifyMenuW(HMENU hMnu,UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCWSTR lpNewItem);
  __attribute__((dllimport)) WINBOOL  RemoveMenu(HMENU hMenu,UINT uPosition,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  DeleteMenu(HMENU hMenu,UINT uPosition,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  SetMenuItemBitmaps(HMENU hMenu,UINT uPosition,UINT uFlags,HBITMAP hBitmapUnchecked,HBITMAP hBitmapChecked);
  __attribute__((dllimport)) LONG  GetMenuCheckMarkDimensions(void);
  __attribute__((dllimport)) WINBOOL  TrackPopupMenu(HMENU hMenu,UINT uFlags,int x,int y,int nReserved,HWND hWnd,const RECT *prcRect);






  typedef struct tagTPMPARAMS {
    UINT cbSize;
    RECT rcExclude;
  } TPMPARAMS;

  typedef TPMPARAMS *LPTPMPARAMS;

  __attribute__((dllimport)) WINBOOL  TrackPopupMenuEx(HMENU,UINT,int,int,HWND,LPTPMPARAMS);
# 2726 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMENUINFO {
    DWORD cbSize;
    DWORD fMask;
    DWORD dwStyle;
    UINT cyMax;
    HBRUSH hbrBack;
    DWORD dwContextHelpID;
    ULONG_PTR dwMenuData;
  } MENUINFO,*LPMENUINFO;

  typedef MENUINFO const *LPCMENUINFO;

  __attribute__((dllimport)) WINBOOL  GetMenuInfo(HMENU,LPMENUINFO);
  __attribute__((dllimport)) WINBOOL  SetMenuInfo(HMENU,LPCMENUINFO);
  __attribute__((dllimport)) WINBOOL  EndMenu(void);




  typedef struct tagMENUGETOBJECTINFO {
    DWORD dwFlags;
    UINT uPos;
    HMENU hmenu;
    PVOID riid;
    PVOID pvObj;
  } MENUGETOBJECTINFO,*PMENUGETOBJECTINFO;
# 2782 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMENUITEMINFOA {
    UINT cbSize;
    UINT fMask;
    UINT fType;
    UINT fState;
    UINT wID;
    HMENU hSubMenu;
    HBITMAP hbmpChecked;
    HBITMAP hbmpUnchecked;
    ULONG_PTR dwItemData;
    LPSTR dwTypeData;
    UINT cch;
    HBITMAP hbmpItem;
  } MENUITEMINFOA,*LPMENUITEMINFOA;

  typedef struct tagMENUITEMINFOW {
    UINT cbSize;
    UINT fMask;
    UINT fType;
    UINT fState;
    UINT wID;
    HMENU hSubMenu;
    HBITMAP hbmpChecked;
    HBITMAP hbmpUnchecked;
    ULONG_PTR dwItemData;
    LPWSTR dwTypeData;
    UINT cch;
    HBITMAP hbmpItem;
  } MENUITEMINFOW,*LPMENUITEMINFOW;





  typedef MENUITEMINFOA MENUITEMINFO;
  typedef LPMENUITEMINFOA LPMENUITEMINFO;

  typedef MENUITEMINFOA const *LPCMENUITEMINFOA;
  typedef MENUITEMINFOW const *LPCMENUITEMINFOW;



  typedef LPCMENUITEMINFOA LPCMENUITEMINFO;
# 2837 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  InsertMenuItemA(HMENU hmenu,UINT item,WINBOOL fByPosition,LPCMENUITEMINFOA lpmi);
  __attribute__((dllimport)) WINBOOL  InsertMenuItemW(HMENU hmenu,UINT item,WINBOOL fByPosition,LPCMENUITEMINFOW lpmi);
  __attribute__((dllimport)) WINBOOL  GetMenuItemInfoA(HMENU hmenu,UINT item,WINBOOL fByPosition,LPMENUITEMINFOA lpmii);
  __attribute__((dllimport)) WINBOOL  GetMenuItemInfoW(HMENU hmenu,UINT item,WINBOOL fByPosition,LPMENUITEMINFOW lpmii);
  __attribute__((dllimport)) WINBOOL  SetMenuItemInfoA(HMENU hmenu,UINT item,WINBOOL fByPositon,LPCMENUITEMINFOA lpmii);
  __attribute__((dllimport)) WINBOOL  SetMenuItemInfoW(HMENU hmenu,UINT item,WINBOOL fByPositon,LPCMENUITEMINFOW lpmii);




  __attribute__((dllimport)) UINT  GetMenuDefaultItem(HMENU hMenu,UINT fByPos,UINT gmdiFlags);
  __attribute__((dllimport)) WINBOOL  SetMenuDefaultItem(HMENU hMenu,UINT uItem,UINT fByPos);
  __attribute__((dllimport)) WINBOOL  GetMenuItemRect(HWND hWnd,HMENU hMenu,UINT uItem,LPRECT lprcItem);
  __attribute__((dllimport)) int  MenuItemFromPoint(HWND hWnd,HMENU hMenu,POINT ptScreen);
# 2874 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagDROPSTRUCT {
    HWND hwndSource;
    HWND hwndSink;
    DWORD wFmt;
    ULONG_PTR dwData;
    POINT ptDrop;
    DWORD dwControlData;
  } DROPSTRUCT,*PDROPSTRUCT,*LPDROPSTRUCT;
# 2893 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) DWORD  DragObject(HWND hwndParent,HWND hwndFrom,UINT fmt,ULONG_PTR data,HCURSOR hcur);
  __attribute__((dllimport)) WINBOOL  DragDetect(HWND hwnd,POINT pt);
  __attribute__((dllimport)) WINBOOL  DrawIcon(HDC hDC,int X,int Y,HICON hIcon);
# 2925 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagDRAWTEXTPARAMS {
    UINT cbSize;
    int iTabLength;
    int iLeftMargin;
    int iRightMargin;
    UINT uiLengthDrawn;
  } DRAWTEXTPARAMS,*LPDRAWTEXTPARAMS;
# 2941 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  DrawTextA(HDC hdc,LPCSTR lpchText,int cchText,LPRECT lprc,UINT format);
  __attribute__((dllimport)) int  DrawTextW(HDC hdc,LPCWSTR lpchText,int cchText,LPRECT lprc,UINT format);
  __attribute__((dllimport)) int  DrawTextExA(HDC hdc,LPSTR lpchText,int cchText,LPRECT lprc,UINT format,LPDRAWTEXTPARAMS lpdtp);
  __attribute__((dllimport)) int  DrawTextExW(HDC hdc,LPWSTR lpchText,int cchText,LPRECT lprc,UINT format,LPDRAWTEXTPARAMS lpdtp);
# 2959 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GrayStringA(HDC hDC,HBRUSH hBrush,GRAYSTRINGPROC lpOutputFunc,LPARAM lpData,int nCount,int X,int Y,int nWidth,int nHeight);
  __attribute__((dllimport)) WINBOOL  GrayStringW(HDC hDC,HBRUSH hBrush,GRAYSTRINGPROC lpOutputFunc,LPARAM lpData,int nCount,int X,int Y,int nWidth,int nHeight);
# 2976 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DrawStateA(HDC hdc,HBRUSH hbrFore,DRAWSTATEPROC qfnCallBack,LPARAM lData,WPARAM wData,int x,int y,int cx,int cy,UINT uFlags);
  __attribute__((dllimport)) WINBOOL  DrawStateW(HDC hdc,HBRUSH hbrFore,DRAWSTATEPROC qfnCallBack,LPARAM lData,WPARAM wData,int x,int y,int cx,int cy,UINT uFlags);
  __attribute__((dllimport)) LONG  TabbedTextOutA(HDC hdc,int x,int y,LPCSTR lpString,int chCount,int nTabPositions,const INT *lpnTabStopPositions,int nTabOrigin);
  __attribute__((dllimport)) LONG  TabbedTextOutW(HDC hdc,int x,int y,LPCWSTR lpString,int chCount,int nTabPositions,const INT *lpnTabStopPositions,int nTabOrigin);
  __attribute__((dllimport)) DWORD  GetTabbedTextExtentA(HDC hdc,LPCSTR lpString,int chCount,int nTabPositions,const INT *lpnTabStopPositions);
  __attribute__((dllimport)) DWORD  GetTabbedTextExtentW(HDC hdc,LPCWSTR lpString,int chCount,int nTabPositions,const INT *lpnTabStopPositions);
  __attribute__((dllimport)) WINBOOL  UpdateWindow(HWND hWnd);
  __attribute__((dllimport)) HWND  SetActiveWindow(HWND hWnd);
  __attribute__((dllimport)) HWND  GetForegroundWindow(void);
  __attribute__((dllimport)) WINBOOL  PaintDesktop(HDC hdc);
  __attribute__((dllimport)) void  SwitchToThisWindow(HWND hwnd,WINBOOL fUnknown);
  __attribute__((dllimport)) WINBOOL  SetForegroundWindow(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  AllowSetForegroundWindow(DWORD dwProcessId);



  __attribute__((dllimport)) WINBOOL  LockSetForegroundWindow(UINT uLockCode);




  __attribute__((dllimport)) HWND  WindowFromDC(HDC hDC);
  __attribute__((dllimport)) HDC  GetDC(HWND hWnd);
  __attribute__((dllimport)) HDC  GetDCEx(HWND hWnd,HRGN hrgnClip,DWORD flags);
# 3015 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HDC  GetWindowDC(HWND hWnd);
  __attribute__((dllimport)) int  ReleaseDC(HWND hWnd,HDC hDC);
  __attribute__((dllimport)) HDC  BeginPaint(HWND hWnd,LPPAINTSTRUCT lpPaint);
  __attribute__((dllimport)) WINBOOL  EndPaint(HWND hWnd,const PAINTSTRUCT *lpPaint);
  __attribute__((dllimport)) WINBOOL  GetUpdateRect(HWND hWnd,LPRECT lpRect,WINBOOL bErase);
  __attribute__((dllimport)) int  GetUpdateRgn(HWND hWnd,HRGN hRgn,WINBOOL bErase);
  __attribute__((dllimport)) int  SetWindowRgn(HWND hWnd,HRGN hRgn,WINBOOL bRedraw);
  __attribute__((dllimport)) int  GetWindowRgn(HWND hWnd,HRGN hRgn);
  __attribute__((dllimport)) int  GetWindowRgnBox(HWND hWnd,LPRECT lprc);
  __attribute__((dllimport)) int  ExcludeUpdateRgn(HDC hDC,HWND hWnd);
  __attribute__((dllimport)) WINBOOL  InvalidateRect(HWND hWnd,const RECT *lpRect,WINBOOL bErase);
  __attribute__((dllimport)) WINBOOL  ValidateRect(HWND hWnd,const RECT *lpRect);
  __attribute__((dllimport)) WINBOOL  InvalidateRgn(HWND hWnd,HRGN hRgn,WINBOOL bErase);
  __attribute__((dllimport)) WINBOOL  ValidateRgn(HWND hWnd,HRGN hRgn);
  __attribute__((dllimport)) WINBOOL  RedrawWindow(HWND hWnd,const RECT *lprcUpdate,HRGN hrgnUpdate,UINT flags);
# 3048 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  LockWindowUpdate(HWND hWndLock);
  __attribute__((dllimport)) WINBOOL  ScrollWindow(HWND hWnd,int XAmount,int YAmount,const RECT *lpRect,const RECT *lpClipRect);
  __attribute__((dllimport)) WINBOOL  ScrollDC(HDC hDC,int dx,int dy,const RECT *lprcScroll,const RECT *lprcClip,HRGN hrgnUpdate,LPRECT lprcUpdate);
  __attribute__((dllimport)) int  ScrollWindowEx(HWND hWnd,int dx,int dy,const RECT *prcScroll,const RECT *prcClip,HRGN hrgnUpdate,LPRECT prcUpdate,UINT flags);







  __attribute__((dllimport)) int  SetScrollPos(HWND hWnd,int nBar,int nPos,WINBOOL bRedraw);
  __attribute__((dllimport)) int  GetScrollPos(HWND hWnd,int nBar);
  __attribute__((dllimport)) WINBOOL  SetScrollRange(HWND hWnd,int nBar,int nMinPos,int nMaxPos,WINBOOL bRedraw);
  __attribute__((dllimport)) WINBOOL  GetScrollRange(HWND hWnd,int nBar,LPINT lpMinPos,LPINT lpMaxPos);
  __attribute__((dllimport)) WINBOOL  ShowScrollBar(HWND hWnd,int wBar,WINBOOL bShow);
  __attribute__((dllimport)) WINBOOL  EnableScrollBar(HWND hWnd,UINT wSBflags,UINT wArrows);
# 3099 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  SetPropA(HWND hWnd,LPCSTR lpString,HANDLE hData);
  __attribute__((dllimport)) WINBOOL  SetPropW(HWND hWnd,LPCWSTR lpString,HANDLE hData);
  __attribute__((dllimport)) HANDLE  GetPropA(HWND hWnd,LPCSTR lpString);
  __attribute__((dllimport)) HANDLE  GetPropW(HWND hWnd,LPCWSTR lpString);
  __attribute__((dllimport)) HANDLE  RemovePropA(HWND hWnd,LPCSTR lpString);
  __attribute__((dllimport)) HANDLE  RemovePropW(HWND hWnd,LPCWSTR lpString);
  __attribute__((dllimport)) int  EnumPropsExA(HWND hWnd,PROPENUMPROCEXA lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumPropsExW(HWND hWnd,PROPENUMPROCEXW lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) int  EnumPropsA(HWND hWnd,PROPENUMPROCA lpEnumFunc);
  __attribute__((dllimport)) int  EnumPropsW(HWND hWnd,PROPENUMPROCW lpEnumFunc);
  __attribute__((dllimport)) WINBOOL  SetWindowTextA(HWND hWnd,LPCSTR lpString);
  __attribute__((dllimport)) WINBOOL  SetWindowTextW(HWND hWnd,LPCWSTR lpString);
  __attribute__((dllimport)) int  GetWindowTextA(HWND hWnd,LPSTR lpString,int nMaxCount);
  __attribute__((dllimport)) int  GetWindowTextW(HWND hWnd,LPWSTR lpString,int nMaxCount);
  __attribute__((dllimport)) int  GetWindowTextLengthA(HWND hWnd);
  __attribute__((dllimport)) int  GetWindowTextLengthW(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  GetClientRect(HWND hWnd,LPRECT lpRect);
  __attribute__((dllimport)) WINBOOL  GetWindowRect(HWND hWnd,LPRECT lpRect);
  __attribute__((dllimport)) WINBOOL  AdjustWindowRect(LPRECT lpRect,DWORD dwStyle,WINBOOL bMenu);
  __attribute__((dllimport)) WINBOOL  AdjustWindowRectEx(LPRECT lpRect,DWORD dwStyle,WINBOOL bMenu,DWORD dwExStyle);




  typedef struct tagHELPINFO {
    UINT cbSize;
    int iContextType;
    int iCtrlId;
    HANDLE hItemHandle;
    DWORD_PTR dwContextId;
    POINT MousePos;
  } HELPINFO,*LPHELPINFO;

  __attribute__((dllimport)) WINBOOL  SetWindowContextHelpId(HWND,DWORD);
  __attribute__((dllimport)) DWORD  GetWindowContextHelpId(HWND);
  __attribute__((dllimport)) WINBOOL  SetMenuContextHelpId(HMENU,DWORD);
  __attribute__((dllimport)) DWORD  GetMenuContextHelpId(HMENU);
# 3185 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  MessageBoxA(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
  __attribute__((dllimport)) int  MessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType);
  __attribute__((dllimport)) int  MessageBoxExA(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType,WORD wLanguageId);
  __attribute__((dllimport)) int  MessageBoxExW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType,WORD wLanguageId);

  typedef void ( *MSGBOXCALLBACK)(LPHELPINFO lpHelpInfo);

  typedef struct tagMSGBOXPARAMSA {
    UINT cbSize;
    HWND hwndOwner;
    HINSTANCE hInstance;
    LPCSTR lpszText;
    LPCSTR lpszCaption;
    DWORD dwStyle;
    LPCSTR lpszIcon;
    DWORD_PTR dwContextHelpId;
    MSGBOXCALLBACK lpfnMsgBoxCallback;
    DWORD dwLanguageId;
  } MSGBOXPARAMSA,*PMSGBOXPARAMSA,*LPMSGBOXPARAMSA;

  typedef struct tagMSGBOXPARAMSW {
    UINT cbSize;
    HWND hwndOwner;
    HINSTANCE hInstance;
    LPCWSTR lpszText;
    LPCWSTR lpszCaption;
    DWORD dwStyle;
    LPCWSTR lpszIcon;
    DWORD_PTR dwContextHelpId;
    MSGBOXCALLBACK lpfnMsgBoxCallback;
    DWORD dwLanguageId;
  } MSGBOXPARAMSW,*PMSGBOXPARAMSW,*LPMSGBOXPARAMSW;






  typedef MSGBOXPARAMSA MSGBOXPARAMS;
  typedef PMSGBOXPARAMSA PMSGBOXPARAMS;
  typedef LPMSGBOXPARAMSA LPMSGBOXPARAMS;
# 3234 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  MessageBoxIndirectA(const MSGBOXPARAMSA *lpmbp);
  __attribute__((dllimport)) int  MessageBoxIndirectW(const MSGBOXPARAMSW *lpmbp);
  __attribute__((dllimport)) WINBOOL  MessageBeep(UINT uType);


  __attribute__((dllimport)) int  ShowCursor(WINBOOL bShow);
  __attribute__((dllimport)) WINBOOL  SetCursorPos(int X,int Y);
  __attribute__((dllimport)) HCURSOR  SetCursor(HCURSOR hCursor);
  __attribute__((dllimport)) WINBOOL  GetCursorPos(LPPOINT lpPoint);
  __attribute__((dllimport)) WINBOOL  ClipCursor(const RECT *lpRect);
  __attribute__((dllimport)) WINBOOL  GetClipCursor(LPRECT lpRect);
  __attribute__((dllimport)) HCURSOR  GetCursor(void);
  __attribute__((dllimport)) WINBOOL  CreateCaret(HWND hWnd,HBITMAP hBitmap,int nWidth,int nHeight);
  __attribute__((dllimport)) UINT  GetCaretBlinkTime(void);
  __attribute__((dllimport)) WINBOOL  SetCaretBlinkTime(UINT uMSeconds);
  __attribute__((dllimport)) WINBOOL  DestroyCaret(void);
  __attribute__((dllimport)) WINBOOL  HideCaret(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  ShowCaret(HWND hWnd);
  __attribute__((dllimport)) WINBOOL  SetCaretPos(int X,int Y);
  __attribute__((dllimport)) WINBOOL  GetCaretPos(LPPOINT lpPoint);
  __attribute__((dllimport)) WINBOOL  ClientToScreen(HWND hWnd,LPPOINT lpPoint);
  __attribute__((dllimport)) WINBOOL  ScreenToClient(HWND hWnd,LPPOINT lpPoint);
  __attribute__((dllimport)) int  MapWindowPoints(HWND hWndFrom,HWND hWndTo,LPPOINT lpPoints,UINT cPoints);
  __attribute__((dllimport)) HWND  WindowFromPoint(POINT Point);
  __attribute__((dllimport)) HWND  ChildWindowFromPoint(HWND hWndParent,POINT Point);






  __attribute__((dllimport)) HWND  ChildWindowFromPointEx(HWND hwnd,POINT pt,UINT flags);
# 3318 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) DWORD  GetSysColor(int nIndex);
  __attribute__((dllimport)) HBRUSH  GetSysColorBrush(int nIndex);
  __attribute__((dllimport)) WINBOOL  SetSysColors(int cElements,const INT *lpaElements,const COLORREF *lpaRgbValues);


  __attribute__((dllimport)) WINBOOL  DrawFocusRect(HDC hDC,const RECT *lprc);
  __attribute__((dllimport)) int  FillRect(HDC hDC,const RECT *lprc,HBRUSH hbr);
  __attribute__((dllimport)) int  FrameRect(HDC hDC,const RECT *lprc,HBRUSH hbr);
  __attribute__((dllimport)) WINBOOL  InvertRect(HDC hDC,const RECT *lprc);
  __attribute__((dllimport)) WINBOOL  SetRect(LPRECT lprc,int xLeft,int yTop,int xRight,int yBottom);
  __attribute__((dllimport)) WINBOOL  SetRectEmpty(LPRECT lprc);
  __attribute__((dllimport)) WINBOOL  CopyRect(LPRECT lprcDst,const RECT *lprcSrc);
  __attribute__((dllimport)) WINBOOL  InflateRect(LPRECT lprc,int dx,int dy);
  __attribute__((dllimport)) WINBOOL  IntersectRect(LPRECT lprcDst,const RECT *lprcSrc1,const RECT *lprcSrc2);
  __attribute__((dllimport)) WINBOOL  UnionRect(LPRECT lprcDst,const RECT *lprcSrc1,const RECT *lprcSrc2);
  __attribute__((dllimport)) WINBOOL  SubtractRect(LPRECT lprcDst,const RECT *lprcSrc1,const RECT *lprcSrc2);
  __attribute__((dllimport)) WINBOOL  OffsetRect(LPRECT lprc,int dx,int dy);
  __attribute__((dllimport)) WINBOOL  IsRectEmpty(const RECT *lprc);
  __attribute__((dllimport)) WINBOOL  EqualRect(const RECT *lprc1,const RECT *lprc2);
  __attribute__((dllimport)) WINBOOL  PtInRect(const RECT *lprc,POINT pt);
# 3349 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WORD  GetWindowWord(HWND hWnd,int nIndex);
  __attribute__((dllimport)) WORD  SetWindowWord(HWND hWnd,int nIndex,WORD wNewWord);
  __attribute__((dllimport)) LONG  GetWindowLongA(HWND hWnd,int nIndex);
  __attribute__((dllimport)) LONG  GetWindowLongW(HWND hWnd,int nIndex);
  __attribute__((dllimport)) LONG  SetWindowLongA(HWND hWnd,int nIndex,LONG dwNewLong);
  __attribute__((dllimport)) LONG  SetWindowLongW(HWND hWnd,int nIndex,LONG dwNewLong);
# 3366 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) LONG_PTR  GetWindowLongPtrA(HWND hWnd,int nIndex);
  __attribute__((dllimport)) LONG_PTR  GetWindowLongPtrW(HWND hWnd,int nIndex);
  __attribute__((dllimport)) LONG_PTR  SetWindowLongPtrA(HWND hWnd,int nIndex,LONG_PTR dwNewLong);
  __attribute__((dllimport)) LONG_PTR  SetWindowLongPtrW(HWND hWnd,int nIndex,LONG_PTR dwNewLong);
# 3394 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WORD  GetClassWord(HWND hWnd,int nIndex);
  __attribute__((dllimport)) WORD  SetClassWord(HWND hWnd,int nIndex,WORD wNewWord);
  __attribute__((dllimport)) DWORD  GetClassLongA(HWND hWnd,int nIndex);
  __attribute__((dllimport)) DWORD  GetClassLongW(HWND hWnd,int nIndex);
  __attribute__((dllimport)) DWORD  SetClassLongA(HWND hWnd,int nIndex,LONG dwNewLong);
  __attribute__((dllimport)) DWORD  SetClassLongW(HWND hWnd,int nIndex,LONG dwNewLong);
# 3411 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) ULONG_PTR  GetClassLongPtrA(HWND hWnd,int nIndex);
  __attribute__((dllimport)) ULONG_PTR  GetClassLongPtrW(HWND hWnd,int nIndex);
  __attribute__((dllimport)) ULONG_PTR  SetClassLongPtrA(HWND hWnd,int nIndex,LONG_PTR dwNewLong);
  __attribute__((dllimport)) ULONG_PTR  SetClassLongPtrW(HWND hWnd,int nIndex,LONG_PTR dwNewLong);
# 3441 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetProcessDefaultLayout(DWORD *pdwDefaultLayout);
  __attribute__((dllimport)) WINBOOL  SetProcessDefaultLayout(DWORD dwDefaultLayout);
  __attribute__((dllimport)) HWND  GetDesktopWindow(void);
  __attribute__((dllimport)) HWND  GetParent(HWND hWnd);
  __attribute__((dllimport)) HWND  SetParent(HWND hWndChild,HWND hWndNewParent);
  __attribute__((dllimport)) WINBOOL  EnumChildWindows(HWND hWndParent,WNDENUMPROC lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) HWND  FindWindowA(LPCSTR lpClassName,LPCSTR lpWindowName);
  __attribute__((dllimport)) HWND  FindWindowW(LPCWSTR lpClassName,LPCWSTR lpWindowName);
  __attribute__((dllimport)) HWND  FindWindowExA(HWND hWndParent,HWND hWndChildAfter,LPCSTR lpszClass,LPCSTR lpszWindow);
  __attribute__((dllimport)) HWND  FindWindowExW(HWND hWndParent,HWND hWndChildAfter,LPCWSTR lpszClass,LPCWSTR lpszWindow);
  __attribute__((dllimport)) HWND  GetShellWindow(void);
  __attribute__((dllimport)) WINBOOL  RegisterShellHookWindow(HWND hwnd);
  __attribute__((dllimport)) WINBOOL  DeregisterShellHookWindow(HWND hwnd);
  __attribute__((dllimport)) WINBOOL  EnumWindows(WNDENUMPROC lpEnumFunc,LPARAM lParam);
  __attribute__((dllimport)) WINBOOL  EnumThreadWindows(DWORD dwThreadId,WNDENUMPROC lpfn,LPARAM lParam);



  __attribute__((dllimport)) int  GetClassNameA(HWND hWnd,LPSTR lpClassName,int nMaxCount);
  __attribute__((dllimport)) int  GetClassNameW(HWND hWnd,LPWSTR lpClassName,int nMaxCount);
  __attribute__((dllimport)) HWND  GetTopWindow(HWND hWnd);





  __attribute__((dllimport)) DWORD  GetWindowThreadProcessId(HWND hWnd,LPDWORD lpdwProcessId);
  __attribute__((dllimport)) WINBOOL  IsGUIThread(WINBOOL bConvert);



  __attribute__((dllimport)) HWND  GetLastActivePopup(HWND hWnd);
# 3483 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HWND  GetWindow(HWND hWnd,UINT uCmd);
# 3495 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HHOOK  SetWindowsHookA(int nFilterType,HOOKPROC pfnFilterProc);
  __attribute__((dllimport)) HHOOK  SetWindowsHookW(int nFilterType,HOOKPROC pfnFilterProc);
  __attribute__((dllimport)) WINBOOL  UnhookWindowsHook(int nCode,HOOKPROC pfnFilterProc);
  __attribute__((dllimport)) HHOOK  SetWindowsHookExA(int idHook,HOOKPROC lpfn,HINSTANCE hmod,DWORD dwThreadId);
  __attribute__((dllimport)) HHOOK  SetWindowsHookExW(int idHook,HOOKPROC lpfn,HINSTANCE hmod,DWORD dwThreadId);
  __attribute__((dllimport)) WINBOOL  UnhookWindowsHookEx(HHOOK hhk);
  __attribute__((dllimport)) LRESULT  CallNextHookEx(HHOOK hhk,int nCode,WPARAM wParam,LPARAM lParam);
# 3555 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  CheckMenuRadioItem(HMENU hmenu,UINT first,UINT last,UINT check,UINT flags);

  typedef struct {
    WORD versionNumber;
    WORD offset;
  } MENUITEMTEMPLATEHEADER,*PMENUITEMTEMPLATEHEADER;

  typedef struct {
    WORD mtOption;
    WORD mtID;
    WCHAR mtString[1];
  } MENUITEMTEMPLATE,*PMENUITEMTEMPLATE;
# 3606 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HBITMAP  LoadBitmapA(HINSTANCE hInstance,LPCSTR lpBitmapName);
  __attribute__((dllimport)) HBITMAP  LoadBitmapW(HINSTANCE hInstance,LPCWSTR lpBitmapName);
  __attribute__((dllimport)) HCURSOR  LoadCursorA(HINSTANCE hInstance,LPCSTR lpCursorName);
  __attribute__((dllimport)) HCURSOR  LoadCursorW(HINSTANCE hInstance,LPCWSTR lpCursorName);
  __attribute__((dllimport)) HCURSOR  LoadCursorFromFileA(LPCSTR lpFileName);
  __attribute__((dllimport)) HCURSOR  LoadCursorFromFileW(LPCWSTR lpFileName);
  __attribute__((dllimport)) HCURSOR  CreateCursor(HINSTANCE hInst,int xHotSpot,int yHotSpot,int nWidth,int nHeight,const void *pvANDPlane,const void *pvXORPlane);
  __attribute__((dllimport)) WINBOOL  DestroyCursor(HCURSOR hCursor);
# 3634 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  SetSystemCursor(HCURSOR hcur,DWORD id);

  typedef struct _ICONINFO {
    WINBOOL fIcon;
    DWORD xHotspot;
    DWORD yHotspot;
    HBITMAP hbmMask;
    HBITMAP hbmColor;
  } ICONINFO;
  typedef ICONINFO *PICONINFO;
# 3653 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HICON  LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName);
  __attribute__((dllimport)) HICON  LoadIconW(HINSTANCE hInstance,LPCWSTR lpIconName);
  __attribute__((dllimport)) UINT  PrivateExtractIconsA(LPCSTR szFileName,int nIconIndex,int cxIcon,int cyIcon,HICON *phicon,UINT *piconid,UINT nIcons,UINT flags);
  __attribute__((dllimport)) UINT  PrivateExtractIconsW(LPCWSTR szFileName,int nIconIndex,int cxIcon,int cyIcon,HICON *phicon,UINT *piconid,UINT nIcons,UINT flags);
  __attribute__((dllimport)) HICON  CreateIcon(HINSTANCE hInstance,int nWidth,int nHeight,BYTE cPlanes,BYTE cBitsPixel,const BYTE *lpbANDbits,const BYTE *lpbXORbits);
  __attribute__((dllimport)) WINBOOL  DestroyIcon(HICON hIcon);
  __attribute__((dllimport)) int  LookupIconIdFromDirectory(PBYTE presbits,WINBOOL fIcon);
  __attribute__((dllimport)) int  LookupIconIdFromDirectoryEx(PBYTE presbits,WINBOOL fIcon,int cxDesired,int cyDesired,UINT Flags);
  __attribute__((dllimport)) HICON  CreateIconFromResource(PBYTE presbits,DWORD dwResSize,WINBOOL fIcon,DWORD dwVer);
  __attribute__((dllimport)) HICON  CreateIconFromResourceEx(PBYTE presbits,DWORD dwResSize,WINBOOL fIcon,DWORD dwVer,int cxDesired,int cyDesired,UINT Flags);

  typedef struct tagCURSORSHAPE {
    int xHotSpot;
    int yHotSpot;
    int cx;
    int cy;
    int cbWidth;
    BYTE Planes;
    BYTE BitsPixel;
  } CURSORSHAPE,*LPCURSORSHAPE;
# 3699 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HANDLE  LoadImageA(HINSTANCE hInst,LPCSTR name,UINT type,int cx,int cy,UINT fuLoad);
  __attribute__((dllimport)) HANDLE  LoadImageW(HINSTANCE hInst,LPCWSTR name,UINT type,int cx,int cy,UINT fuLoad);
  __attribute__((dllimport)) HANDLE  CopyImage(HANDLE h,UINT type,int cx,int cy,UINT flags);
# 3710 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DrawIconEx(HDC hdc,int xLeft,int yTop,HICON hIcon,int cxWidth,int cyWidth,UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw,UINT diFlags);
  __attribute__((dllimport)) HICON  CreateIconIndirect(PICONINFO piconinfo);
  __attribute__((dllimport)) HICON  CopyIcon(HICON hIcon);
  __attribute__((dllimport)) WINBOOL  GetIconInfo(HICON hIcon,PICONINFO piconinfo);
# 3815 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) int  LoadStringA(HINSTANCE hInstance,UINT uID,LPSTR lpBuffer,int cchBufferMax);
  __attribute__((dllimport)) int  LoadStringW(HINSTANCE hInstance,UINT uID,LPWSTR lpBuffer,int cchBufferMax);
# 4048 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  IsDialogMessageA(HWND hDlg,LPMSG lpMsg);
  __attribute__((dllimport)) WINBOOL  IsDialogMessageW(HWND hDlg,LPMSG lpMsg);
# 4064 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  MapDialogRect(HWND hDlg,LPRECT lpRect);
  __attribute__((dllimport)) int  DlgDirListA(HWND hDlg,LPSTR lpPathSpec,int nIDListBox,int nIDStaticPath,UINT uFileType);
  __attribute__((dllimport)) int  DlgDirListW(HWND hDlg,LPWSTR lpPathSpec,int nIDListBox,int nIDStaticPath,UINT uFileType);
# 4079 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  DlgDirSelectExA(HWND hwndDlg,LPSTR lpString,int chCount,int idListBox);
  __attribute__((dllimport)) WINBOOL  DlgDirSelectExW(HWND hwndDlg,LPWSTR lpString,int chCount,int idListBox);
  __attribute__((dllimport)) int  DlgDirListComboBoxA(HWND hDlg,LPSTR lpPathSpec,int nIDComboBox,int nIDStaticPath,UINT uFiletype);
  __attribute__((dllimport)) int  DlgDirListComboBoxW(HWND hDlg,LPWSTR lpPathSpec,int nIDComboBox,int nIDStaticPath,UINT uFiletype);
  __attribute__((dllimport)) WINBOOL  DlgDirSelectComboBoxExA(HWND hwndDlg,LPSTR lpString,int cchOut,int idComboBox);
  __attribute__((dllimport)) WINBOOL  DlgDirSelectComboBoxExW(HWND hwndDlg,LPWSTR lpString,int cchOut,int idComboBox);
# 4317 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagSCROLLINFO {
    UINT cbSize;
    UINT fMask;
    int nMin;
    int nMax;
    UINT nPage;
    int nPos;
    int nTrackPos;
  } SCROLLINFO,*LPSCROLLINFO;
  typedef SCROLLINFO const *LPCSCROLLINFO;

  __attribute__((dllimport)) int  SetScrollInfo(HWND hwnd,int nBar,LPCSCROLLINFO lpsi,WINBOOL redraw);
  __attribute__((dllimport)) WINBOOL  GetScrollInfo(HWND hwnd,int nBar,LPSCROLLINFO lpsi);
# 4342 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMDICREATESTRUCTA {
    LPCSTR szClass;
    LPCSTR szTitle;
    HANDLE hOwner;
    int x;
    int y;
    int cx;
    int cy;
    DWORD style;
    LPARAM lParam;
  } MDICREATESTRUCTA,*LPMDICREATESTRUCTA;

  typedef struct tagMDICREATESTRUCTW {
    LPCWSTR szClass;
    LPCWSTR szTitle;
    HANDLE hOwner;
    int x;
    int y;
    int cx;
    int cy;
    DWORD style;
    LPARAM lParam;
  } MDICREATESTRUCTW,*LPMDICREATESTRUCTW;





  typedef MDICREATESTRUCTA MDICREATESTRUCT;
  typedef LPMDICREATESTRUCTA LPMDICREATESTRUCT;


  typedef struct tagCLIENTCREATESTRUCT {
    HANDLE hWindowMenu;
    UINT idFirstChild;
  } CLIENTCREATESTRUCT,*LPCLIENTCREATESTRUCT;
# 4389 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) LRESULT  DefFrameProcA(HWND hWnd,HWND hWndMDIClient,UINT uMsg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  DefFrameProcW(HWND hWnd,HWND hWndMDIClient,UINT uMsg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  DefMDIChildProcA(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
  __attribute__((dllimport)) LRESULT  DefMDIChildProcW(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);


  __attribute__((dllimport)) WINBOOL  TranslateMDISysAccel(HWND hWndClient,LPMSG lpMsg);


  __attribute__((dllimport)) UINT  ArrangeIconicWindows(HWND hWnd);
  __attribute__((dllimport)) HWND  CreateMDIWindowA(LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HINSTANCE hInstance,LPARAM lParam);
  __attribute__((dllimport)) HWND  CreateMDIWindowW(LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int X,int Y,int nWidth,int nHeight,HWND hWndParent,HINSTANCE hInstance,LPARAM lParam);
  __attribute__((dllimport)) WORD  TileWindows(HWND hwndParent,UINT wHow,const RECT *lpRect,UINT cKids,const HWND *lpKids);
  __attribute__((dllimport)) WORD  CascadeWindows(HWND hwndParent,UINT wHow,const RECT *lpRect,UINT cKids,const HWND *lpKids);





  typedef DWORD HELPPOLY;
  typedef struct tagMULTIKEYHELPA {
    DWORD mkSize;
    CHAR mkKeylist;
    CHAR szKeyphrase[1];
  } MULTIKEYHELPA,*PMULTIKEYHELPA,*LPMULTIKEYHELPA;

  typedef struct tagMULTIKEYHELPW {
    DWORD mkSize;
    WCHAR mkKeylist;
    WCHAR szKeyphrase[1];
  } MULTIKEYHELPW,*PMULTIKEYHELPW,*LPMULTIKEYHELPW;






  typedef MULTIKEYHELPA MULTIKEYHELP;
  typedef PMULTIKEYHELPA PMULTIKEYHELP;
  typedef LPMULTIKEYHELPA LPMULTIKEYHELP;


  typedef struct tagHELPWININFOA {
    int wStructSize;
    int x;
    int y;
    int dx;
    int dy;
    int wMax;
    CHAR rgchMember[2];
  } HELPWININFOA,*PHELPWININFOA,*LPHELPWININFOA;

  typedef struct tagHELPWININFOW {
    int wStructSize;
    int x;
    int y;
    int dx;
    int dy;
    int wMax;
    WCHAR rgchMember[2];
  } HELPWININFOW,*PHELPWININFOW,*LPHELPWININFOW;






  typedef HELPWININFOA HELPWININFO;
  typedef PHELPWININFOA PHELPWININFO;
  typedef LPHELPWININFOA LPHELPWININFO;
# 4497 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  WinHelpA(HWND hWndMain,LPCSTR lpszHelp,UINT uCommand,ULONG_PTR dwData);
  __attribute__((dllimport)) WINBOOL  WinHelpW(HWND hWndMain,LPCWSTR lpszHelp,UINT uCommand,ULONG_PTR dwData);





  __attribute__((dllimport)) DWORD  GetGuiResources(HANDLE hProcess,DWORD uiFlags);
# 4697 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagNONCLIENTMETRICSA {
    UINT cbSize;
    int iBorderWidth;
    int iScrollWidth;
    int iScrollHeight;
    int iCaptionWidth;
    int iCaptionHeight;
    LOGFONTA lfCaptionFont;
    int iSmCaptionWidth;
    int iSmCaptionHeight;
    LOGFONTA lfSmCaptionFont;
    int iMenuWidth;
    int iMenuHeight;
    LOGFONTA lfMenuFont;
    LOGFONTA lfStatusFont;
    LOGFONTA lfMessageFont;
  } NONCLIENTMETRICSA,*PNONCLIENTMETRICSA,*LPNONCLIENTMETRICSA;

  typedef struct tagNONCLIENTMETRICSW {
    UINT cbSize;
    int iBorderWidth;
    int iScrollWidth;
    int iScrollHeight;
    int iCaptionWidth;
    int iCaptionHeight;
    LOGFONTW lfCaptionFont;
    int iSmCaptionWidth;
    int iSmCaptionHeight;
    LOGFONTW lfSmCaptionFont;
    int iMenuWidth;
    int iMenuHeight;
    LOGFONTW lfMenuFont;
    LOGFONTW lfStatusFont;
    LOGFONTW lfMessageFont;
  } NONCLIENTMETRICSW,*PNONCLIENTMETRICSW,*LPNONCLIENTMETRICSW;






  typedef NONCLIENTMETRICSA NONCLIENTMETRICS;
  typedef PNONCLIENTMETRICSA PNONCLIENTMETRICS;
  typedef LPNONCLIENTMETRICSA LPNONCLIENTMETRICS;
# 4759 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMINIMIZEDMETRICS {
    UINT cbSize;
    int iWidth;
    int iHorzGap;
    int iVertGap;
    int iArrange;
  } MINIMIZEDMETRICS,*PMINIMIZEDMETRICS,*LPMINIMIZEDMETRICS;



  typedef struct tagICONMETRICSA {
    UINT cbSize;
    int iHorzSpacing;
    int iVertSpacing;
    int iTitleWrap;
    LOGFONTA lfFont;
  } ICONMETRICSA,*PICONMETRICSA,*LPICONMETRICSA;

  typedef struct tagICONMETRICSW {
    UINT cbSize;
    int iHorzSpacing;
    int iVertSpacing;
    int iTitleWrap;
    LOGFONTW lfFont;
  } ICONMETRICSW,*PICONMETRICSW,*LPICONMETRICSW;






  typedef ICONMETRICSA ICONMETRICS;
  typedef PICONMETRICSA PICONMETRICS;
  typedef LPICONMETRICSA LPICONMETRICS;




  typedef struct tagANIMATIONINFO {
    UINT cbSize;
    int iMinAnimate;
  } ANIMATIONINFO,*LPANIMATIONINFO;

  typedef struct tagSERIALKEYSA {
    UINT cbSize;
    DWORD dwFlags;
    LPSTR lpszActivePort;
    LPSTR lpszPort;
    UINT iBaudRate;
    UINT iPortState;
    UINT iActive;
  } SERIALKEYSA,*LPSERIALKEYSA;

  typedef struct tagSERIALKEYSW {
    UINT cbSize;
    DWORD dwFlags;
    LPWSTR lpszActivePort;
    LPWSTR lpszPort;
    UINT iBaudRate;
    UINT iPortState;
    UINT iActive;
  } SERIALKEYSW,*LPSERIALKEYSW;





  typedef SERIALKEYSA SERIALKEYS;
  typedef LPSERIALKEYSA LPSERIALKEYS;






  typedef struct tagHIGHCONTRASTA {
    UINT cbSize;
    DWORD dwFlags;
    LPSTR lpszDefaultScheme;
  } HIGHCONTRASTA,*LPHIGHCONTRASTA;

  typedef struct tagHIGHCONTRASTW {
    UINT cbSize;
    DWORD dwFlags;
    LPWSTR lpszDefaultScheme;
  } HIGHCONTRASTW,*LPHIGHCONTRASTW;





  typedef HIGHCONTRASTA HIGHCONTRAST;
  typedef LPHIGHCONTRASTA LPHIGHCONTRAST;
# 4901 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) LONG  ChangeDisplaySettingsA(LPDEVMODEA lpDevMode,DWORD dwFlags);
  __attribute__((dllimport)) LONG  ChangeDisplaySettingsW(LPDEVMODEW lpDevMode,DWORD dwFlags);
  __attribute__((dllimport)) LONG  ChangeDisplaySettingsExA(LPCSTR lpszDeviceName,LPDEVMODEA lpDevMode,HWND hwnd,DWORD dwflags,LPVOID lParam);
  __attribute__((dllimport)) LONG  ChangeDisplaySettingsExW(LPCWSTR lpszDeviceName,LPDEVMODEW lpDevMode,HWND hwnd,DWORD dwflags,LPVOID lParam);




  __attribute__((dllimport)) WINBOOL  EnumDisplaySettingsA(LPCSTR lpszDeviceName,DWORD iModeNum,LPDEVMODEA lpDevMode);
  __attribute__((dllimport)) WINBOOL  EnumDisplaySettingsW(LPCWSTR lpszDeviceName,DWORD iModeNum,LPDEVMODEW lpDevMode);
  __attribute__((dllimport)) WINBOOL  EnumDisplaySettingsExA(LPCSTR lpszDeviceName,DWORD iModeNum,LPDEVMODEA lpDevMode,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  EnumDisplaySettingsExW(LPCWSTR lpszDeviceName,DWORD iModeNum,LPDEVMODEW lpDevMode,DWORD dwFlags);



  __attribute__((dllimport)) WINBOOL  EnumDisplayDevicesA(LPCSTR lpDevice,DWORD iDevNum,PDISPLAY_DEVICEA lpDisplayDevice,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  EnumDisplayDevicesW(LPCWSTR lpDevice,DWORD iDevNum,PDISPLAY_DEVICEW lpDisplayDevice,DWORD dwFlags);
# 4927 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  SystemParametersInfoA(UINT uiAction,UINT uiParam,PVOID pvParam,UINT fWinIni);
  __attribute__((dllimport)) WINBOOL  SystemParametersInfoW(UINT uiAction,UINT uiParam,PVOID pvParam,UINT fWinIni);


  typedef struct tagFILTERKEYS {
    UINT cbSize;
    DWORD dwFlags;
    DWORD iWaitMSec;
    DWORD iDelayMSec;
    DWORD iRepeatMSec;
    DWORD iBounceMSec;
  } FILTERKEYS,*LPFILTERKEYS;
# 4948 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagSTICKYKEYS {
    UINT cbSize;
    DWORD dwFlags;
  } STICKYKEYS,*LPSTICKYKEYS;
# 4979 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMOUSEKEYS {
    UINT cbSize;
    DWORD dwFlags;
    DWORD iMaxSpeed;
    DWORD iTimeToMaxSpeed;
    DWORD iCtrlSpeed;
    DWORD dwReserved1;
    DWORD dwReserved2;
  } MOUSEKEYS,*LPMOUSEKEYS;
# 5003 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagACCESSTIMEOUT {
    UINT cbSize;
    DWORD dwFlags;
    DWORD iTimeOutMSec;
  } ACCESSTIMEOUT,*LPACCESSTIMEOUT;
# 5026 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagSOUNDSENTRYA {
    UINT cbSize;
    DWORD dwFlags;
    DWORD iFSTextEffect;
    DWORD iFSTextEffectMSec;
    DWORD iFSTextEffectColorBits;
    DWORD iFSGrafEffect;
    DWORD iFSGrafEffectMSec;
    DWORD iFSGrafEffectColor;
    DWORD iWindowsEffect;
    DWORD iWindowsEffectMSec;
    LPSTR lpszWindowsEffectDLL;
    DWORD iWindowsEffectOrdinal;
  } SOUNDSENTRYA,*LPSOUNDSENTRYA;

  typedef struct tagSOUNDSENTRYW {
    UINT cbSize;
    DWORD dwFlags;
    DWORD iFSTextEffect;
    DWORD iFSTextEffectMSec;
    DWORD iFSTextEffectColorBits;
    DWORD iFSGrafEffect;
    DWORD iFSGrafEffectMSec;
    DWORD iFSGrafEffectColor;
    DWORD iWindowsEffect;
    DWORD iWindowsEffectMSec;
    LPWSTR lpszWindowsEffectDLL;
    DWORD iWindowsEffectOrdinal;
  } SOUNDSENTRYW,*LPSOUNDSENTRYW;





  typedef SOUNDSENTRYA SOUNDSENTRY;
  typedef LPSOUNDSENTRYA LPSOUNDSENTRY;






  typedef struct tagTOGGLEKEYS {
    UINT cbSize;
    DWORD dwFlags;
  } TOGGLEKEYS,*LPTOGGLEKEYS;
# 5080 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) void  SetDebugErrorLevel(DWORD dwLevel);





  __attribute__((dllimport)) void  SetLastErrorEx(DWORD dwErrCode,DWORD dwType);
  __attribute__((dllimport)) int  InternalGetWindowText(HWND hWnd,LPWSTR pString,int cchMaxCount);
# 5097 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) HMONITOR  MonitorFromPoint(POINT pt,DWORD dwFlags);
  __attribute__((dllimport)) HMONITOR  MonitorFromRect(LPCRECT lprc,DWORD dwFlags);
  __attribute__((dllimport)) HMONITOR  MonitorFromWindow(HWND hwnd,DWORD dwFlags);







  typedef struct tagMONITORINFO {
    DWORD cbSize;
    RECT rcMonitor;
    RECT rcWork;
    DWORD dwFlags;
  } MONITORINFO,*LPMONITORINFO;
# 5131 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagMONITORINFOEXA {
    MONITORINFO mi;
    CHAR szDevice[32];
  } MONITORINFOEXA,*LPMONITORINFOEXA;

  typedef struct tagMONITORINFOEXW {
    MONITORINFO mi;
    WCHAR szDevice[32];
  } MONITORINFOEXW,*LPMONITORINFOEXW;




  typedef MONITORINFOEXA MONITORINFOEX;
  typedef LPMONITORINFOEXA LPMONITORINFOEX;
# 5155 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetMonitorInfoA(HMONITOR hMonitor,LPMONITORINFO lpmi);
  __attribute__((dllimport)) WINBOOL  GetMonitorInfoW(HMONITOR hMonitor,LPMONITORINFO lpmi);

  typedef WINBOOL ( *MONITORENUMPROC)(HMONITOR,HDC,LPRECT,LPARAM);

  __attribute__((dllimport)) WINBOOL  EnumDisplayMonitors(HDC hdc,LPCRECT lprcClip,MONITORENUMPROC lpfnEnum,LPARAM dwData);


  __attribute__((dllimport)) void  NotifyWinEvent(DWORD event,HWND hwnd,LONG idObject,LONG idChild);

  typedef void ( *WINEVENTPROC)(HWINEVENTHOOK hWinEventHook,DWORD event,HWND hwnd,LONG idObject,LONG idChild,DWORD idEventThread,DWORD dwmsEventTime);

  __attribute__((dllimport)) HWINEVENTHOOK  SetWinEventHook(DWORD eventMin,DWORD eventMax,HMODULE hmodWinEventProc,WINEVENTPROC pfnWinEventProc,DWORD idProcess,DWORD idThread,DWORD dwFlags);
  __attribute__((dllimport)) WINBOOL  IsWinEventHookInstalled(DWORD event);






  __attribute__((dllimport)) WINBOOL  UnhookWinEvent(HWINEVENTHOOK hWinEventHook);
# 5285 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagGUITHREADINFO {
    DWORD cbSize;
    DWORD flags;
    HWND hwndActive;
    HWND hwndFocus;
    HWND hwndCapture;
    HWND hwndMenuOwner;
    HWND hwndMoveSize;
    HWND hwndCaret;
    RECT rcCaret;
  } GUITHREADINFO,*PGUITHREADINFO,*LPGUITHREADINFO;
# 5310 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  GetGUIThreadInfo(DWORD idThread,PGUITHREADINFO pgui);
  __attribute__((dllimport)) UINT  GetWindowModuleFileNameA(HWND hwnd,LPSTR pszFileName,UINT cchFileNameMax);
  __attribute__((dllimport)) UINT  GetWindowModuleFileNameW(HWND hwnd,LPWSTR pszFileName,UINT cchFileNameMax);
# 5352 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagCURSORINFO {
    DWORD cbSize;
    DWORD flags;
    HCURSOR hCursor;
    POINT ptScreenPos;
  } CURSORINFO,*PCURSORINFO,*LPCURSORINFO;



  __attribute__((dllimport)) WINBOOL  GetCursorInfo(PCURSORINFO pci);

  typedef struct tagWINDOWINFO {
    DWORD cbSize;
    RECT rcWindow;
    RECT rcClient;
    DWORD dwStyle;
    DWORD dwExStyle;
    DWORD dwWindowStatus;
    UINT cxWindowBorders;
    UINT cyWindowBorders;
    ATOM atomWindowType;
    WORD wCreatorVersion;
  } WINDOWINFO,*PWINDOWINFO,*LPWINDOWINFO;



  __attribute__((dllimport)) WINBOOL  GetWindowInfo(HWND hwnd,PWINDOWINFO pwi);

  typedef struct tagTITLEBARINFO {
    DWORD cbSize;
    RECT rcTitleBar;
    DWORD rgstate[5 + 1];
  } TITLEBARINFO,*PTITLEBARINFO,*LPTITLEBARINFO;

  __attribute__((dllimport)) WINBOOL  GetTitleBarInfo(HWND hwnd,PTITLEBARINFO pti);

  typedef struct tagMENUBARINFO {
    DWORD cbSize;
    RECT rcBar;
    HMENU hMenu;
    HWND hwndMenu;
    WINBOOL fBarFocused:1;
    WINBOOL fFocused:1;
  } MENUBARINFO,*PMENUBARINFO,*LPMENUBARINFO;

  __attribute__((dllimport)) WINBOOL  GetMenuBarInfo(HWND hwnd,LONG idObject,LONG idItem,PMENUBARINFO pmbi);

  typedef struct tagSCROLLBARINFO {
    DWORD cbSize;
    RECT rcScrollBar;
    int dxyLineButton;
    int xyThumbTop;
    int xyThumbBottom;
    int reserved;
    DWORD rgstate[5 + 1];
  } SCROLLBARINFO,*PSCROLLBARINFO,*LPSCROLLBARINFO;

  __attribute__((dllimport)) WINBOOL  GetScrollBarInfo(HWND hwnd,LONG idObject,PSCROLLBARINFO psbi);

  typedef struct tagCOMBOBOXINFO {
    DWORD cbSize;
    RECT rcItem;
    RECT rcButton;
    DWORD stateButton;
    HWND hwndCombo;
    HWND hwndItem;
    HWND hwndList;
  } COMBOBOXINFO,*PCOMBOBOXINFO,*LPCOMBOBOXINFO;

  __attribute__((dllimport)) WINBOOL  GetComboBoxInfo(HWND hwndCombo,PCOMBOBOXINFO pcbi);





  __attribute__((dllimport)) HWND  GetAncestor(HWND hwnd,UINT gaFlags);
  __attribute__((dllimport)) HWND  RealChildWindowFromPoint(HWND hwndParent,POINT ptParentClientCoords);
  __attribute__((dllimport)) UINT  RealGetWindowClassA(HWND hwnd,LPSTR ptszClassName,UINT cchClassNameMax);
  __attribute__((dllimport)) UINT  RealGetWindowClassW(HWND hwnd,LPWSTR ptszClassName,UINT cchClassNameMax);






  typedef struct tagALTTABINFO {
    DWORD cbSize;
    int cItems;
    int cColumns;
    int cRows;
    int iColFocus;
    int iRowFocus;
    int cxItem;
    int cyItem;
    POINT ptStart;
  } ALTTABINFO,*PALTTABINFO,*LPALTTABINFO;







  __attribute__((dllimport)) WINBOOL  GetAltTabInfoA(HWND hwnd,int iItem,PALTTABINFO pati,LPSTR pszItemText,UINT cchItemText);
  __attribute__((dllimport)) WINBOOL  GetAltTabInfoW(HWND hwnd,int iItem,PALTTABINFO pati,LPWSTR pszItemText,UINT cchItemText);
  __attribute__((dllimport)) DWORD  GetListBoxInfo(HWND hwnd);


  __attribute__((dllimport)) WINBOOL  LockWorkStation(void);
  __attribute__((dllimport)) WINBOOL  UserHandleGrantAccess(HANDLE hUserHandle,HANDLE hJob,WINBOOL bGrant);

  struct HRAWINPUT__ { int unused; }; typedef struct HRAWINPUT__ *HRAWINPUT;






  typedef struct tagRAWINPUTHEADER {
    DWORD dwType;
    DWORD dwSize;
    HANDLE hDevice;
    WPARAM wParam;
  } RAWINPUTHEADER,*PRAWINPUTHEADER,*LPRAWINPUTHEADER;





  typedef struct tagRAWMOUSE {
    USHORT usFlags;
    union {
      ULONG ulButtons;
      struct {
	USHORT usButtonFlags;
	USHORT usButtonData;
      };
    };
    ULONG ulRawButtons;
    LONG lLastX;
    LONG lLastY;
    ULONG ulExtraInformation;
  } RAWMOUSE,*PRAWMOUSE,*LPRAWMOUSE;
# 5522 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagRAWKEYBOARD {
    USHORT MakeCode;
    USHORT Flags;
    USHORT Reserved;
    USHORT VKey;
    UINT Message;
    ULONG ExtraInformation;
  } RAWKEYBOARD,*PRAWKEYBOARD,*LPRAWKEYBOARD;
# 5540 "c:/program files/tcc/include/winapi/winuser.h"
  typedef struct tagRAWHID {
    DWORD dwSizeHid;
    DWORD dwCount;
    BYTE bRawData[1];
  } RAWHID,*PRAWHID,*LPRAWHID;

  typedef struct tagRAWINPUT {
    RAWINPUTHEADER header;
    union {
      RAWMOUSE mouse;
      RAWKEYBOARD keyboard;
      RAWHID hid;
    } data;
  } RAWINPUT,*PRAWINPUT,*LPRAWINPUT;
# 5566 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) UINT  GetRawInputData(HRAWINPUT hRawInput,UINT uiCommand,LPVOID pData,PUINT pcbSize,UINT cbSizeHeader);





  typedef struct tagRID_DEVICE_INFO_MOUSE {
    DWORD dwId;
    DWORD dwNumberOfButtons;
    DWORD dwSampleRate;
  } RID_DEVICE_INFO_MOUSE,*PRID_DEVICE_INFO_MOUSE;

  typedef struct tagRID_DEVICE_INFO_KEYBOARD {
    DWORD dwType;
    DWORD dwSubType;
    DWORD dwKeyboardMode;
    DWORD dwNumberOfFunctionKeys;
    DWORD dwNumberOfIndicators;
    DWORD dwNumberOfKeysTotal;
  } RID_DEVICE_INFO_KEYBOARD,*PRID_DEVICE_INFO_KEYBOARD;

  typedef struct tagRID_DEVICE_INFO_HID {
    DWORD dwVendorId;
    DWORD dwProductId;
    DWORD dwVersionNumber;
    USHORT usUsagePage;
    USHORT usUsage;
  } RID_DEVICE_INFO_HID,*PRID_DEVICE_INFO_HID;

  typedef struct tagRID_DEVICE_INFO {
    DWORD cbSize;
    DWORD dwType;
    union {
      RID_DEVICE_INFO_MOUSE mouse;
      RID_DEVICE_INFO_KEYBOARD keyboard;
      RID_DEVICE_INFO_HID hid;
    };
  } RID_DEVICE_INFO,*PRID_DEVICE_INFO,*LPRID_DEVICE_INFO;







  __attribute__((dllimport)) UINT  GetRawInputDeviceInfoA(HANDLE hDevice,UINT uiCommand,LPVOID pData,PUINT pcbSize);
  __attribute__((dllimport)) UINT  GetRawInputDeviceInfoW(HANDLE hDevice,UINT uiCommand,LPVOID pData,PUINT pcbSize);
  __attribute__((dllimport)) UINT  GetRawInputBuffer(PRAWINPUT pData,PUINT pcbSize,UINT cbSizeHeader);

  typedef struct tagRAWINPUTDEVICE {
    USHORT usUsagePage;
    USHORT usUsage;
    DWORD dwFlags;
    HWND hwndTarget;
  } RAWINPUTDEVICE,*PRAWINPUTDEVICE,*LPRAWINPUTDEVICE;

  typedef const RAWINPUTDEVICE *PCRAWINPUTDEVICE;
# 5635 "c:/program files/tcc/include/winapi/winuser.h"
  __attribute__((dllimport)) WINBOOL  RegisterRawInputDevices(PCRAWINPUTDEVICE pRawInputDevices,UINT uiNumDevices,UINT cbSize);
  __attribute__((dllimport)) UINT  GetRegisteredRawInputDevices(PRAWINPUTDEVICE pRawInputDevices,PUINT puiNumDevices,UINT cbSize);

  typedef struct tagRAWINPUTDEVICELIST {
    HANDLE hDevice;
    DWORD dwType;
  } RAWINPUTDEVICELIST,*PRAWINPUTDEVICELIST;

  __attribute__((dllimport)) UINT  GetRawInputDeviceList(PRAWINPUTDEVICELIST pRawInputDeviceList,PUINT puiNumDevices,UINT cbSize);
  __attribute__((dllimport)) LRESULT  DefRawInputProc(PRAWINPUT *paRawInput,INT nInput,UINT cbSizeHeader);
# 70 "c:/program files/tcc/include/winapi/windows.h" 2

# 1 "c:/program files/tcc/include/winapi/wincon.h" 1
# 13 "c:/program files/tcc/include/winapi/wincon.h"
  typedef struct _COORD {
    SHORT X;
    SHORT Y;
  } COORD,*PCOORD;

  typedef struct _SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
  } SMALL_RECT,*PSMALL_RECT;

  typedef struct _KEY_EVENT_RECORD {
    WINBOOL bKeyDown;
    WORD wRepeatCount;
    WORD wVirtualKeyCode;
    WORD wVirtualScanCode;
    union {
      WCHAR UnicodeChar;
      CHAR AsciiChar;
    } uChar;
    DWORD dwControlKeyState;
  } KEY_EVENT_RECORD,*PKEY_EVENT_RECORD;
# 54 "c:/program files/tcc/include/winapi/wincon.h"
  typedef struct _MOUSE_EVENT_RECORD {
    COORD dwMousePosition;
    DWORD dwButtonState;
    DWORD dwControlKeyState;
    DWORD dwEventFlags;
  } MOUSE_EVENT_RECORD,*PMOUSE_EVENT_RECORD;
# 71 "c:/program files/tcc/include/winapi/wincon.h"
  typedef struct _WINDOW_BUFFER_SIZE_RECORD {
    COORD dwSize;
  } WINDOW_BUFFER_SIZE_RECORD,*PWINDOW_BUFFER_SIZE_RECORD;

  typedef struct _MENU_EVENT_RECORD {
    UINT dwCommandId;
  } MENU_EVENT_RECORD,*PMENU_EVENT_RECORD;

  typedef struct _FOCUS_EVENT_RECORD {
    WINBOOL bSetFocus;
  } FOCUS_EVENT_RECORD,*PFOCUS_EVENT_RECORD;

  typedef struct _INPUT_RECORD {
    WORD EventType;
    union {
      KEY_EVENT_RECORD KeyEvent;
      MOUSE_EVENT_RECORD MouseEvent;
      WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
      MENU_EVENT_RECORD MenuEvent;
      FOCUS_EVENT_RECORD FocusEvent;
    } Event;
  } INPUT_RECORD,*PINPUT_RECORD;







  typedef struct _CHAR_INFO {
    union {
      WCHAR UnicodeChar;
      CHAR AsciiChar;
    } Char;
    WORD Attributes;
  } CHAR_INFO,*PCHAR_INFO;
# 126 "c:/program files/tcc/include/winapi/wincon.h"
  typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD dwSize;
    COORD dwCursorPosition;
    WORD wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
  } CONSOLE_SCREEN_BUFFER_INFO,*PCONSOLE_SCREEN_BUFFER_INFO;

  typedef struct _CONSOLE_CURSOR_INFO {
    DWORD dwSize;
    WINBOOL bVisible;
  } CONSOLE_CURSOR_INFO,*PCONSOLE_CURSOR_INFO;

  typedef struct _CONSOLE_FONT_INFO {
    DWORD nFont;
    COORD dwFontSize;
  } CONSOLE_FONT_INFO,*PCONSOLE_FONT_INFO;

  typedef struct _CONSOLE_SELECTION_INFO {
    DWORD dwFlags;
    COORD dwSelectionAnchor;
    SMALL_RECT srSelection;
  } CONSOLE_SELECTION_INFO,*PCONSOLE_SELECTION_INFO;







  typedef WINBOOL ( *PHANDLER_ROUTINE)(DWORD CtrlType);
# 216 "c:/program files/tcc/include/winapi/wincon.h"
  __attribute__((dllimport)) WINBOOL  PeekConsoleInputA(HANDLE hConsoleInput,PINPUT_RECORD lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
  __attribute__((dllimport)) WINBOOL  PeekConsoleInputW(HANDLE hConsoleInput,PINPUT_RECORD lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
  __attribute__((dllimport)) WINBOOL  ReadConsoleInputA(HANDLE hConsoleInput,PINPUT_RECORD lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
  __attribute__((dllimport)) WINBOOL  ReadConsoleInputW(HANDLE hConsoleInput,PINPUT_RECORD lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
  __attribute__((dllimport)) WINBOOL  WriteConsoleInputA(HANDLE hConsoleInput,const INPUT_RECORD *lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsWritten);
  __attribute__((dllimport)) WINBOOL  WriteConsoleInputW(HANDLE hConsoleInput,const INPUT_RECORD *lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsWritten);
  __attribute__((dllimport)) WINBOOL  ReadConsoleOutputA(HANDLE hConsoleOutput,PCHAR_INFO lpBuffer,COORD dwBufferSize,COORD dwBufferCoord,PSMALL_RECT lpReadRegion);
  __attribute__((dllimport)) WINBOOL  ReadConsoleOutputW(HANDLE hConsoleOutput,PCHAR_INFO lpBuffer,COORD dwBufferSize,COORD dwBufferCoord,PSMALL_RECT lpReadRegion);
  __attribute__((dllimport)) WINBOOL  WriteConsoleOutputA(HANDLE hConsoleOutput,const CHAR_INFO *lpBuffer,COORD dwBufferSize,COORD dwBufferCoord,PSMALL_RECT lpWriteRegion);
  __attribute__((dllimport)) WINBOOL  WriteConsoleOutputW(HANDLE hConsoleOutput,const CHAR_INFO *lpBuffer,COORD dwBufferSize,COORD dwBufferCoord,PSMALL_RECT lpWriteRegion);
  __attribute__((dllimport)) WINBOOL  ReadConsoleOutputCharacterA(HANDLE hConsoleOutput,LPSTR lpCharacter,DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfCharsRead);
  __attribute__((dllimport)) WINBOOL  ReadConsoleOutputCharacterW(HANDLE hConsoleOutput,LPWSTR lpCharacter,DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfCharsRead);
  __attribute__((dllimport)) WINBOOL  ReadConsoleOutputAttribute(HANDLE hConsoleOutput,LPWORD lpAttribute,DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfAttrsRead);
  __attribute__((dllimport)) WINBOOL  WriteConsoleOutputCharacterA(HANDLE hConsoleOutput,LPCSTR lpCharacter,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
  __attribute__((dllimport)) WINBOOL  WriteConsoleOutputCharacterW(HANDLE hConsoleOutput,LPCWSTR lpCharacter,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
  __attribute__((dllimport)) WINBOOL  WriteConsoleOutputAttribute(HANDLE hConsoleOutput,const WORD *lpAttribute,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfAttrsWritten);
  __attribute__((dllimport)) WINBOOL  FillConsoleOutputCharacterA(HANDLE hConsoleOutput,CHAR cCharacter,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
  __attribute__((dllimport)) WINBOOL  FillConsoleOutputCharacterW(HANDLE hConsoleOutput,WCHAR cCharacter,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
  __attribute__((dllimport)) WINBOOL  FillConsoleOutputAttribute(HANDLE hConsoleOutput,WORD wAttribute,DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfAttrsWritten);
  __attribute__((dllimport)) WINBOOL  GetConsoleMode(HANDLE hConsoleHandle,LPDWORD lpMode);
  __attribute__((dllimport)) WINBOOL  GetNumberOfConsoleInputEvents(HANDLE hConsoleInput,LPDWORD lpNumberOfEvents);
  __attribute__((dllimport)) WINBOOL  GetConsoleScreenBufferInfo(HANDLE hConsoleOutput,PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);
  __attribute__((dllimport)) COORD  GetLargestConsoleWindowSize(HANDLE hConsoleOutput);
  __attribute__((dllimport)) WINBOOL  GetConsoleCursorInfo(HANDLE hConsoleOutput,PCONSOLE_CURSOR_INFO lpConsoleCursorInfo);
  __attribute__((dllimport)) WINBOOL  GetCurrentConsoleFont(HANDLE hConsoleOutput,WINBOOL bMaximumWindow,PCONSOLE_FONT_INFO lpConsoleCurrentFont);
  __attribute__((dllimport)) COORD  GetConsoleFontSize(HANDLE hConsoleOutput,DWORD nFont);
  __attribute__((dllimport)) WINBOOL  GetConsoleSelectionInfo(PCONSOLE_SELECTION_INFO lpConsoleSelectionInfo);
  __attribute__((dllimport)) WINBOOL  GetNumberOfConsoleMouseButtons(LPDWORD lpNumberOfMouseButtons);
  __attribute__((dllimport)) WINBOOL  SetConsoleMode(HANDLE hConsoleHandle,DWORD dwMode);
  __attribute__((dllimport)) WINBOOL  SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput);
  __attribute__((dllimport)) WINBOOL  FlushConsoleInputBuffer(HANDLE hConsoleInput);
  __attribute__((dllimport)) WINBOOL  SetConsoleScreenBufferSize(HANDLE hConsoleOutput,COORD dwSize);
  __attribute__((dllimport)) WINBOOL  SetConsoleCursorPosition(HANDLE hConsoleOutput,COORD dwCursorPosition);
  __attribute__((dllimport)) WINBOOL  SetConsoleCursorInfo(HANDLE hConsoleOutput,const CONSOLE_CURSOR_INFO *lpConsoleCursorInfo);
  __attribute__((dllimport)) WINBOOL  ScrollConsoleScreenBufferA(HANDLE hConsoleOutput,const SMALL_RECT *lpScrollRectangle,const SMALL_RECT *lpClipRectangle,COORD dwDestinationOrigin,const CHAR_INFO *lpFill);
  __attribute__((dllimport)) WINBOOL  ScrollConsoleScreenBufferW(HANDLE hConsoleOutput,const SMALL_RECT *lpScrollRectangle,const SMALL_RECT *lpClipRectangle,COORD dwDestinationOrigin,const CHAR_INFO *lpFill);
  __attribute__((dllimport)) WINBOOL  SetConsoleWindowInfo(HANDLE hConsoleOutput,WINBOOL bAbsolute,const SMALL_RECT *lpConsoleWindow);
  __attribute__((dllimport)) WINBOOL  SetConsoleTextAttribute(HANDLE hConsoleOutput,WORD wAttributes);
  __attribute__((dllimport)) WINBOOL  SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine,WINBOOL Add);
  __attribute__((dllimport)) WINBOOL  GenerateConsoleCtrlEvent(DWORD dwCtrlEvent,DWORD dwProcessGroupId);
  __attribute__((dllimport)) WINBOOL  AllocConsole(void);
  __attribute__((dllimport)) WINBOOL  FreeConsole(void);
  __attribute__((dllimport)) WINBOOL  AttachConsole(DWORD dwProcessId);



  __attribute__((dllimport)) DWORD  GetConsoleTitleA(LPSTR lpConsoleTitle,DWORD nSize);
  __attribute__((dllimport)) DWORD  GetConsoleTitleW(LPWSTR lpConsoleTitle,DWORD nSize);
  __attribute__((dllimport)) WINBOOL  SetConsoleTitleA(LPCSTR lpConsoleTitle);
  __attribute__((dllimport)) WINBOOL  SetConsoleTitleW(LPCWSTR lpConsoleTitle);
  __attribute__((dllimport)) WINBOOL  ReadConsoleA(HANDLE hConsoleInput,LPVOID lpBuffer,DWORD nNumberOfCharsToRead,LPDWORD lpNumberOfCharsRead,LPVOID lpReserved);
  __attribute__((dllimport)) WINBOOL  ReadConsoleW(HANDLE hConsoleInput,LPVOID lpBuffer,DWORD nNumberOfCharsToRead,LPDWORD lpNumberOfCharsRead,LPVOID lpReserved);
  __attribute__((dllimport)) WINBOOL  WriteConsoleA(HANDLE hConsoleOutput,const void *lpBuffer,DWORD nNumberOfCharsToWrite,LPDWORD lpNumberOfCharsWritten,LPVOID lpReserved);
  __attribute__((dllimport)) WINBOOL  WriteConsoleW(HANDLE hConsoleOutput,const void *lpBuffer,DWORD nNumberOfCharsToWrite,LPDWORD lpNumberOfCharsWritten,LPVOID lpReserved);



  __attribute__((dllimport)) HANDLE  CreateConsoleScreenBuffer(DWORD dwDesiredAccess,DWORD dwShareMode,const SECURITY_ATTRIBUTES *lpSecurityAttributes,DWORD dwFlags,LPVOID lpScreenBufferData);
  __attribute__((dllimport)) UINT  GetConsoleCP(void);
  __attribute__((dllimport)) WINBOOL  SetConsoleCP(UINT wCodePageID);
  __attribute__((dllimport)) UINT  GetConsoleOutputCP(void);
  __attribute__((dllimport)) WINBOOL  SetConsoleOutputCP(UINT wCodePageID);




  __attribute__((dllimport)) WINBOOL  GetConsoleDisplayMode(LPDWORD lpModeFlags);
  __attribute__((dllimport)) HWND  GetConsoleWindow(void);
  __attribute__((dllimport)) DWORD  GetConsoleProcessList(LPDWORD lpdwProcessList,DWORD dwProcessCount);
  __attribute__((dllimport)) WINBOOL  AddConsoleAliasA(LPSTR Source,LPSTR Target,LPSTR ExeName);
  __attribute__((dllimport)) WINBOOL  AddConsoleAliasW(LPWSTR Source,LPWSTR Target,LPWSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasA(LPSTR Source,LPSTR TargetBuffer,DWORD TargetBufferLength,LPSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasW(LPWSTR Source,LPWSTR TargetBuffer,DWORD TargetBufferLength,LPWSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasesLengthA(LPSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasesLengthW(LPWSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasExesLengthA(void);
  __attribute__((dllimport)) DWORD  GetConsoleAliasExesLengthW(void);
  __attribute__((dllimport)) DWORD  GetConsoleAliasesA(LPSTR AliasBuffer,DWORD AliasBufferLength,LPSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasesW(LPWSTR AliasBuffer,DWORD AliasBufferLength,LPWSTR ExeName);
  __attribute__((dllimport)) DWORD  GetConsoleAliasExesA(LPSTR ExeNameBuffer,DWORD ExeNameBufferLength);
  __attribute__((dllimport)) DWORD  GetConsoleAliasExesW(LPWSTR ExeNameBuffer,DWORD ExeNameBufferLength);
# 72 "c:/program files/tcc/include/winapi/windows.h" 2
# 1 "c:/program files/tcc/include/winapi/winver.h" 1
# 110 "c:/program files/tcc/include/winapi/winver.h"
  typedef struct tagVS_FIXEDFILEINFO
  {
    DWORD dwSignature;
    DWORD dwStrucVersion;
    DWORD dwFileVersionMS;
    DWORD dwFileVersionLS;
    DWORD dwProductVersionMS;
    DWORD dwProductVersionLS;
    DWORD dwFileFlagsMask;
    DWORD dwFileFlags;
    DWORD dwFileOS;
    DWORD dwFileType;
    DWORD dwFileSubtype;
    DWORD dwFileDateMS;
    DWORD dwFileDateLS;
  } VS_FIXEDFILEINFO;
# 143 "c:/program files/tcc/include/winapi/winver.h"
  DWORD  VerFindFileA(DWORD uFlags,LPSTR szFileName,LPSTR szWinDir,LPSTR szAppDir,LPSTR szCurDir,PUINT lpuCurDirLen,LPSTR szDestDir,PUINT lpuDestDirLen);
  DWORD  VerFindFileW(DWORD uFlags,LPWSTR szFileName,LPWSTR szWinDir,LPWSTR szAppDir,LPWSTR szCurDir,PUINT lpuCurDirLen,LPWSTR szDestDir,PUINT lpuDestDirLen);
  DWORD  VerInstallFileA(DWORD uFlags,LPSTR szSrcFileName,LPSTR szDestFileName,LPSTR szSrcDir,LPSTR szDestDir,LPSTR szCurDir,LPSTR szTmpFile,PUINT lpuTmpFileLen);
  DWORD  VerInstallFileW(DWORD uFlags,LPWSTR szSrcFileName,LPWSTR szDestFileName,LPWSTR szSrcDir,LPWSTR szDestDir,LPWSTR szCurDir,LPWSTR szTmpFile,PUINT lpuTmpFileLen);
  DWORD  GetFileVersionInfoSizeA(LPCSTR lptstrFilename,LPDWORD lpdwHandle);
  DWORD  GetFileVersionInfoSizeW(LPCWSTR lptstrFilename,LPDWORD lpdwHandle);
  WINBOOL  GetFileVersionInfoA(LPCSTR lptstrFilename,DWORD dwHandle,DWORD dwLen,LPVOID lpData);
  WINBOOL  GetFileVersionInfoW(LPCWSTR lptstrFilename,DWORD dwHandle,DWORD dwLen,LPVOID lpData);
  DWORD  VerLanguageNameA(DWORD wLang,LPSTR szLang,DWORD nSize);
  DWORD  VerLanguageNameW(DWORD wLang,LPWSTR szLang,DWORD nSize);
  WINBOOL  VerQueryValueA(const LPVOID pBlock,LPSTR lpSubBlock,LPVOID *lplpBuffer,PUINT puLen);
  WINBOOL  VerQueryValueW(const LPVOID pBlock,LPWSTR lpSubBlock,LPVOID *lplpBuffer,PUINT puLen);
# 73 "c:/program files/tcc/include/winapi/windows.h" 2
# 1 "c:/program files/tcc/include/winapi/winreg.h" 1
# 32 "c:/program files/tcc/include/winapi/winreg.h"
  typedef ACCESS_MASK REGSAM;
# 50 "c:/program files/tcc/include/winapi/winreg.h"
  struct val_context {
    int valuelen;
    LPVOID value_context;
    LPVOID val_buff_ptr;
  };

  typedef struct val_context *PVALCONTEXT;

  typedef struct pvalueA {
    LPSTR pv_valuename;
    int pv_valuelen;
    LPVOID pv_value_context;
    DWORD pv_type;
  }PVALUEA,*PPVALUEA;

  typedef struct pvalueW {
    LPWSTR pv_valuename;
    int pv_valuelen;
    LPVOID pv_value_context;
    DWORD pv_type;
  }PVALUEW,*PPVALUEW;





  typedef PVALUEA PVALUE;
  typedef PPVALUEA PPVALUE;


  typedef DWORD  QUERYHANDLER(LPVOID keycontext,PVALCONTEXT val_list,DWORD num_vals,LPVOID outputbuffer,DWORD *total_outlen,DWORD input_blen);

  typedef QUERYHANDLER *PQUERYHANDLER;

  typedef struct provider_info {
    PQUERYHANDLER pi_R0_1val;
    PQUERYHANDLER pi_R0_allvals;
    PQUERYHANDLER pi_R3_1val;
    PQUERYHANDLER pi_R3_allvals;
    DWORD pi_flags;
    LPVOID pi_key_context;
  } REG_PROVIDER;

  typedef struct provider_info *PPROVIDER;

  typedef struct value_entA {
    LPSTR ve_valuename;
    DWORD ve_valuelen;
    DWORD_PTR ve_valueptr;
    DWORD ve_type;
  } VALENTA,*PVALENTA;

  typedef struct value_entW {
    LPWSTR ve_valuename;
    DWORD ve_valuelen;
    DWORD_PTR ve_valueptr;
    DWORD ve_type;
  } VALENTW,*PVALENTW;





  typedef VALENTA VALENT;
  typedef PVALENTA PVALENT;
# 176 "c:/program files/tcc/include/winapi/winreg.h"
  __attribute__((dllimport)) LONG  RegCloseKey(HKEY hKey);
  __attribute__((dllimport)) LONG  RegOverridePredefKey(HKEY hKey,HKEY hNewHKey);
  __attribute__((dllimport)) LONG  RegOpenUserClassesRoot(HANDLE hToken,DWORD dwOptions,REGSAM samDesired,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegOpenCurrentUser(REGSAM samDesired,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegDisablePredefinedCache();
  __attribute__((dllimport)) LONG  RegConnectRegistryA(LPCSTR lpMachineName,HKEY hKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegConnectRegistryW(LPCWSTR lpMachineName,HKEY hKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegConnectRegistryExA(LPCSTR lpMachineName,HKEY hKey,ULONG Flags,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegConnectRegistryExW(LPCWSTR lpMachineName,HKEY hKey,ULONG Flags,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegCreateKeyA(HKEY hKey,LPCSTR lpSubKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegCreateKeyW(HKEY hKey,LPCWSTR lpSubKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegCreateKeyExA(HKEY hKey,LPCSTR lpSubKey,DWORD Reserved,LPSTR lpClass,DWORD dwOptions,REGSAM samDesired,LPSECURITY_ATTRIBUTES lpSecurityAttributes,PHKEY phkResult,LPDWORD lpdwDisposition);
  __attribute__((dllimport)) LONG  RegCreateKeyExW(HKEY hKey,LPCWSTR lpSubKey,DWORD Reserved,LPWSTR lpClass,DWORD dwOptions,REGSAM samDesired,LPSECURITY_ATTRIBUTES lpSecurityAttributes,PHKEY phkResult,LPDWORD lpdwDisposition);
  __attribute__((dllimport)) LONG  RegDeleteKeyA(HKEY hKey,LPCSTR lpSubKey);
  __attribute__((dllimport)) LONG  RegDeleteKeyW(HKEY hKey,LPCWSTR lpSubKey);
  __attribute__((dllimport)) LONG  RegDeleteKeyExA(HKEY hKey,LPCSTR lpSubKey,REGSAM samDesired,DWORD Reserved);
  __attribute__((dllimport)) LONG  RegDeleteKeyExW(HKEY hKey,LPCWSTR lpSubKey,REGSAM samDesired,DWORD Reserved);
  __attribute__((dllimport)) LONG  RegDisableReflectionKey(HKEY hBase);
  __attribute__((dllimport)) LONG  RegEnableReflectionKey(HKEY hBase);
  __attribute__((dllimport)) LONG  RegQueryReflectionKey(HKEY hBase,WINBOOL *bIsReflectionDisabled);
  __attribute__((dllimport)) LONG  RegDeleteValueA(HKEY hKey,LPCSTR lpValueName);
  __attribute__((dllimport)) LONG  RegDeleteValueW(HKEY hKey,LPCWSTR lpValueName);
  __attribute__((dllimport)) LONG  RegEnumKeyA(HKEY hKey,DWORD dwIndex,LPSTR lpName,DWORD cchName);
  __attribute__((dllimport)) LONG  RegEnumKeyW(HKEY hKey,DWORD dwIndex,LPWSTR lpName,DWORD cchName);
  __attribute__((dllimport)) LONG  RegEnumKeyExA(HKEY hKey,DWORD dwIndex,LPSTR lpName,LPDWORD lpcchName,LPDWORD lpReserved,LPSTR lpClass,LPDWORD lpcchClass,PFILETIME lpftLastWriteTime);
  __attribute__((dllimport)) LONG  RegEnumKeyExW(HKEY hKey,DWORD dwIndex,LPWSTR lpName,LPDWORD lpcchName,LPDWORD lpReserved,LPWSTR lpClass,LPDWORD lpcchClass,PFILETIME lpftLastWriteTime);
  __attribute__((dllimport)) LONG  RegEnumValueA(HKEY hKey,DWORD dwIndex,LPSTR lpValueName,LPDWORD lpcchValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
  __attribute__((dllimport)) LONG  RegEnumValueW(HKEY hKey,DWORD dwIndex,LPWSTR lpValueName,LPDWORD lpcchValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
  __attribute__((dllimport)) LONG  RegFlushKey(HKEY hKey);
  __attribute__((dllimport)) LONG  RegGetKeySecurity(HKEY hKey,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor,LPDWORD lpcbSecurityDescriptor);
  __attribute__((dllimport)) LONG  RegLoadKeyA(HKEY hKey,LPCSTR lpSubKey,LPCSTR lpFile);
  __attribute__((dllimport)) LONG  RegLoadKeyW(HKEY hKey,LPCWSTR lpSubKey,LPCWSTR lpFile);
  __attribute__((dllimport)) LONG  RegNotifyChangeKeyValue(HKEY hKey,WINBOOL bWatchSubtree,DWORD dwNotifyFilter,HANDLE hEvent,WINBOOL fAsynchronous);
  __attribute__((dllimport)) LONG  RegOpenKeyA(HKEY hKey,LPCSTR lpSubKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegOpenKeyW(HKEY hKey,LPCWSTR lpSubKey,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegOpenKeyExA(HKEY hKey,LPCSTR lpSubKey,DWORD ulOptions,REGSAM samDesired,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegOpenKeyExW(HKEY hKey,LPCWSTR lpSubKey,DWORD ulOptions,REGSAM samDesired,PHKEY phkResult);
  __attribute__((dllimport)) LONG  RegQueryInfoKeyA(HKEY hKey,LPSTR lpClass,LPDWORD lpcchClass,LPDWORD lpReserved,LPDWORD lpcSubKeys,LPDWORD lpcbMaxSubKeyLen,LPDWORD lpcbMaxClassLen,LPDWORD lpcValues,LPDWORD lpcbMaxValueNameLen,LPDWORD lpcbMaxValueLen,LPDWORD lpcbSecurityDescriptor,PFILETIME lpftLastWriteTime);
  __attribute__((dllimport)) LONG  RegQueryInfoKeyW(HKEY hKey,LPWSTR lpClass,LPDWORD lpcchClass,LPDWORD lpReserved,LPDWORD lpcSubKeys,LPDWORD lpcbMaxSubKeyLen,LPDWORD lpcbMaxClassLen,LPDWORD lpcValues,LPDWORD lpcbMaxValueNameLen,LPDWORD lpcbMaxValueLen,LPDWORD lpcbSecurityDescriptor,PFILETIME lpftLastWriteTime);
  __attribute__((dllimport)) LONG  RegQueryValueA(HKEY hKey,LPCSTR lpSubKey,LPSTR lpData,PLONG lpcbData);
  __attribute__((dllimport)) LONG  RegQueryValueW(HKEY hKey,LPCWSTR lpSubKey,LPWSTR lpData,PLONG lpcbData);
  __attribute__((dllimport)) LONG  RegQueryMultipleValuesA(HKEY hKey,PVALENTA val_list,DWORD num_vals,LPSTR lpValueBuf,LPDWORD ldwTotsize);
  __attribute__((dllimport)) LONG  RegQueryMultipleValuesW(HKEY hKey,PVALENTW val_list,DWORD num_vals,LPWSTR lpValueBuf,LPDWORD ldwTotsize);
  __attribute__((dllimport)) LONG  RegQueryValueExA(HKEY hKey,LPCSTR lpValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
  __attribute__((dllimport)) LONG  RegQueryValueExW(HKEY hKey,LPCWSTR lpValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
  __attribute__((dllimport)) LONG  RegReplaceKeyA(HKEY hKey,LPCSTR lpSubKey,LPCSTR lpNewFile,LPCSTR lpOldFile);
  __attribute__((dllimport)) LONG  RegReplaceKeyW(HKEY hKey,LPCWSTR lpSubKey,LPCWSTR lpNewFile,LPCWSTR lpOldFile);
  __attribute__((dllimport)) LONG  RegRestoreKeyA(HKEY hKey,LPCSTR lpFile,DWORD dwFlags);
  __attribute__((dllimport)) LONG  RegRestoreKeyW(HKEY hKey,LPCWSTR lpFile,DWORD dwFlags);
  __attribute__((dllimport)) LONG  RegSaveKeyA(HKEY hKey,LPCSTR lpFile,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) LONG  RegSaveKeyW(HKEY hKey,LPCWSTR lpFile,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
  __attribute__((dllimport)) LONG  RegSetKeySecurity(HKEY hKey,SECURITY_INFORMATION SecurityInformation,PSECURITY_DESCRIPTOR pSecurityDescriptor);
  __attribute__((dllimport)) LONG  RegSetValueA(HKEY hKey,LPCSTR lpSubKey,DWORD dwType,LPCSTR lpData,DWORD cbData);
  __attribute__((dllimport)) LONG  RegSetValueW(HKEY hKey,LPCWSTR lpSubKey,DWORD dwType,LPCWSTR lpData,DWORD cbData);
  __attribute__((dllimport)) LONG  RegSetValueExA(HKEY hKey,LPCSTR lpValueName,DWORD Reserved,DWORD dwType,const BYTE *lpData,DWORD cbData);
  __attribute__((dllimport)) LONG  RegSetValueExW(HKEY hKey,LPCWSTR lpValueName,DWORD Reserved,DWORD dwType,const BYTE *lpData,DWORD cbData);
  __attribute__((dllimport)) LONG  RegUnLoadKeyA(HKEY hKey,LPCSTR lpSubKey);
  __attribute__((dllimport)) LONG  RegUnLoadKeyW(HKEY hKey,LPCWSTR lpSubKey);
  __attribute__((dllimport)) LONG  RegGetValueA(HKEY hkey,LPCSTR lpSubKey,LPCSTR lpValue,DWORD dwFlags,LPDWORD pdwType,PVOID pvData,LPDWORD pcbData);
  __attribute__((dllimport)) LONG  RegGetValueW(HKEY hkey,LPCWSTR lpSubKey,LPCWSTR lpValue,DWORD dwFlags,LPDWORD pdwType,PVOID pvData,LPDWORD pcbData);
  __attribute__((dllimport)) WINBOOL  InitiateSystemShutdownA(LPSTR lpMachineName,LPSTR lpMessage,DWORD dwTimeout,WINBOOL bForceAppsClosed,WINBOOL bRebootAfterShutdown);
  __attribute__((dllimport)) WINBOOL  InitiateSystemShutdownW(LPWSTR lpMachineName,LPWSTR lpMessage,DWORD dwTimeout,WINBOOL bForceAppsClosed,WINBOOL bRebootAfterShutdown);
  __attribute__((dllimport)) WINBOOL  AbortSystemShutdownA(LPSTR lpMachineName);
  __attribute__((dllimport)) WINBOOL  AbortSystemShutdownW(LPWSTR lpMachineName);
# 263 "c:/program files/tcc/include/winapi/winreg.h"
  __attribute__((dllimport)) WINBOOL  InitiateSystemShutdownExA(LPSTR lpMachineName,LPSTR lpMessage,DWORD dwTimeout,WINBOOL bForceAppsClosed,WINBOOL bRebootAfterShutdown,DWORD dwReason);
  __attribute__((dllimport)) WINBOOL  InitiateSystemShutdownExW(LPWSTR lpMachineName,LPWSTR lpMessage,DWORD dwTimeout,WINBOOL bForceAppsClosed,WINBOOL bRebootAfterShutdown,DWORD dwReason);
  __attribute__((dllimport)) LONG  RegSaveKeyExA(HKEY hKey,LPCSTR lpFile,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD Flags);
  __attribute__((dllimport)) LONG  RegSaveKeyExW(HKEY hKey,LPCWSTR lpFile,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD Flags);
  __attribute__((dllimport)) LONG  Wow64Win32ApiEntry (DWORD dwFuncNumber,DWORD dwFlag,DWORD dwRes);
# 74 "c:/program files/tcc/include/winapi/windows.h" 2
# 6 "SGL.c" 2
# 30 "SGL.c"
typedef struct
{
	int length;
	char* characters;
} string;

typedef struct
{
	float x, y;
} v2;

typedef struct
{
	float x, y, z;
} v3;

typedef struct
{
	float x, y, z, w;
} v4;

typedef struct
{
	int parent;
	v3
		position,
		rotation,
		scale;
} Transform;

typedef struct
{
	float
		frame, value,
		left_handle_x, left_handle_y,
		right_handle_x, right_handle_y;
} KeyFrame;

typedef struct
{
	float
		m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44;
} m4x4;

typedef struct
{
	int transform_index;
	float radius;
	char active;
} Hitbox;

typedef struct
{
	v3 a, b, c;
	unsigned int color;
	float brightness;
} Triangle;

typedef struct
{
	v3* vertices;
	int* indices;
	int vertices_length;
	int indices_length;
} Mesh;

typedef struct
{
	int entity_ID;
	int selected_character;
	char defeated;
	int stock;
	float current_health;
	v2 velocity;
	char grounded;
	Hitbox* attackboxes;
	Hitbox* defendboxes;
} Player;


typedef struct
{
	int width, height;
	unsigned int* pixels;
} Bitmap;


float GetMin(float a, float b, float c);
float GetMax(float a, float b, float c);


unsigned int Darker(unsigned int color);
void Fill(unsigned int color);
void FillTriangle(unsigned int color, int x1, int y1, int x2, int y2, int x3, int y3);
void FillTriangle_VertexColors(v2 a, v2 b, v2 c, unsigned int a_color, unsigned int b_color, unsigned int c_color);
void FillFlatBottom(unsigned int color, int bottom, int left, int right, int top, int middle);
void FillFlatTop(unsigned int color, int top, int left, int right, int bottom, int middle);
void DrawHorizontalSegment(unsigned int color, int y, int x1, int x2);
void PutPixel(unsigned int color, int x, int y);
void PutPixel_ByIndex(unsigned int color, int i);
void DrawHorizontal(unsigned int color, int y);
void DrawString(string s, int x, int y);

Transform InvertTransform(Transform t);
v3 NegateVector(v3 v);
m4x4 Concatenate(m4x4 a, m4x4 b);
m4x4 GetMatrix(Transform t);
m4x4 WorldSpaceMatrix(int index, Transform hierarchy[]);
v3 Transform_v3(m4x4 m, v3 v);
v4 TransformVector4(m4x4 m, v4 v);
m4x4 Transpose(m4x4 m);
m4x4 Translation(float x, float y, float z);
m4x4 Rotation(float x, float y, float z);
m4x4 Scale(float x, float y, float z);
v3 v3_Add(v3 a, v3 b);
v3 v3_Subtract(v3 a, v3 b);
v3 v3_CrossProduct(v3 a, v3 b);
v3 v3_Normalized(v3 v);
float v3_Magnitude(v3 v);
v3 v3_Scale(v3 v, float s);
float v3_DotProduct(v3 a, v3 b);
void DrawLine(unsigned int color, float x1, float y1, float x2, float y2);
void DrawRectangle(unsigned int color, float x, float y, float width, float height);
void DrawSplashScreen(float frames_per_second);
void Flatten();


v2 Lerp_v2(v2 a, v2 b, float t);
float Lerp_Float(float a, float b, float t);
void AnimateProperty(KeyFrame curve[], float frame, float* property);
float Sample(KeyFrame a, KeyFrame b, float frame);


char Intersect(Transform a, Transform b);


v3 GetCentroid(Triangle t);


char Less(Triangle a, Triangle b);
void SwapTriangles(Triangle triangles[], int a, int b);
void SortByDepth(Triangle a[], int length);
void QuickSort(Triangle a[], int lo, int hi);
int Partition(Triangle a[], int lo, int hi);


v3 CameraToClipToScreen(v3 v);


void InitViewport(float field_of_view, int width, int height, unsigned int _pixels[]);
void RunMeshDemo(float delta_time, float frames_per_second);
void Render(Mesh mesh, unsigned int body_poly_colors[], Transform camera, char fill_toggle);
void PrintMesh(Mesh mesh);



Mesh LoadMesh(char* path);
void LoadFontSet();

unsigned int Darker(unsigned int color)
{
	unsigned int r = (color & 0xFFFF0000 ^ 0xFF000000) >> 17 << 16;
	unsigned int g = (color & (0xFF00FF00 ^ 0xFF000000)) >> 9 << 8;
	unsigned int b = (color & 0xFF0000FF ^ 0xFF000000) >> 1;
	return 0xFF000000 | r | g | b;
}

__attribute__((dllexport)) Transform InvertTransform(Transform t)
{
	t.position = NegateVector(t.position);
	t.rotation = NegateVector(t.rotation);
	t.scale.x = 1 / t.scale.x;
	t.scale.y = 1 / t.scale.y;
	t.scale.z = 1 / t.scale.z;
	return t;
}

v3 NegateVector(v3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
}

__attribute__((dllexport)) m4x4 Concatenate(m4x4 a, m4x4 b)
{
	m4x4 result;
	result.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
	result.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
	result.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
	result.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;
	result.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
	result.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
	result.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
	result.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;
	result.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
	result.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
	result.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
	result.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;
	result.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
	result.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
	result.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
	result.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
	return result;
}

m4x4 GetMatrix(Transform t)
{
	m4x4 result = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	result = Concatenate(result, Scale(t.scale.x, t.scale.y, t.scale.z));
	result = Concatenate(result, Rotation(t.rotation.x, t.rotation.y, t.rotation.z));
	result = Concatenate(result, Translation(t.position.x, t.position.y, t.position.z));
	return result;
}

__attribute__((dllexport)) m4x4 WorldSpaceMatrix(int index, Transform hierarchy[])
{
	Transform t = hierarchy[index];
	m4x4 m = GetMatrix(t);
	while (t.parent != -1)
	{
		m = Concatenate(m, GetMatrix(hierarchy[t.parent]));
		t = hierarchy[t.parent];
	}

	return m;
}

__attribute__((dllexport)) v3 Transform_v3(m4x4 m, v3 v)
{
	v3 result =
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43,
	};

	return result;
}

v4 Transform_Vector4(m4x4 m, v4 v)
{
	v4 result =
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41 * v.w,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42 * v.w,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43 * v.w,
		m.m14 * v.x + m.m24 * v.y + m.m34 * v.z + m.m44 * v.w,
	};

	return result;
}

m4x4 Transpose(m4x4 m)
{
	m4x4 transposed = { m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44 };
	return transposed;
}

m4x4 Translation(float x, float y, float z)
{
	m4x4 translation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 };
	return translation;
}

m4x4 Scale(float x, float y, float z)
{
	m4x4 scale = { x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 };
	return scale;
}

m4x4 Rotation(float x, float y, float z)
{
	m4x4 rotation;

	rotation.m11 = (float)(cos(y) * cos(z) - sin(y) * sin(x) * sin(z));
	rotation.m12 = (float)(cos(y) * sin(z) + sin(y) * sin(x) * cos(z));
	rotation.m13 = (float)(-sin(y) * cos(x));
	rotation.m14 = 0;
	rotation.m21 = (float)(-sin(z) * cos(x));
	rotation.m22 = (float)(cos(z) * cos(x));
	rotation.m23 = (float)(sin(x));
	rotation.m24 = 0;
	rotation.m31 = (float)(sin(y) * cos(z) + cos(y) * sin(x) * sin(z));
	rotation.m32 = (float)(sin(z) * sin(y) - cos(y) * sin(x) * cos(z));
	rotation.m33 = (float)(cos(y) * cos(x));
	rotation.m34 = 0;
	rotation.m41 = 0;
	rotation.m42 = 0;
	rotation.m43 = 0;
	rotation.m44 = 1;

	return rotation;
}

__attribute__((dllexport)) m4x4 Perspective(float near_plane, float far_plane, float field_of_view, float width, float height)
{
	float aspect_ratio = height / width;
	float zoom = (float)(1 / tan(field_of_view / 2));
	float q = far_plane / (far_plane - near_plane);

	m4x4 result =
	{
		aspect_ratio * zoom, 0, 0, 0,
		0, -zoom, 0, 0,
		0, 0, q, near_plane * q,
		0, 0, 1, 0
	};

	return result;
}

v3 v3_Add(v3 a, v3 b)
{
	v3 v;
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return v;
}

v3 v3_Subtract(v3 a, v3 b)
{
	v3 v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return v;
}

v3 CrossProduct(v3 a, v3 b)
{
	v3 result =
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};

	return result;
}

v3 v3_Normalized(v3 v)
{
	return v3_Scale(v, v3_Magnitude(v));
}

float v3_Magnitude(v3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

v3 v3_Scale(v3 v, float s)
{
	v3 result = { v.x / s, v.y / s, v.z / s };
	return result;
}

float v3_DotProduct(v3 a, v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }


v2 Lerp_v2(v2 a, v2 b, float t)
{
	v2 v;
	v.x = a.x + (t * (b.x - a.x));
	v.y = a.y + (t * (b.y - a.y));
	return v;
}

float Lerp_Float(float a, float b, float t)
{
	return a + t * (b - a);
}


void AnimateProperty(KeyFrame curve[], float frame, float* property)
{
	size_t n = sizeof(curve) / sizeof(curve[0]);
	for (int i = 0; i < n - 1; i++)
	{
		KeyFrame a = curve[i];
		KeyFrame b = curve[i + 1];
		if (frame >= a.frame && frame <= b.frame)
		{
			*property = Sample(a, b, frame);
			return;
		}
	}
}

float Sample(KeyFrame a, KeyFrame b, float frame)
{
	float t = (frame - a.frame) / (b.frame - a.frame);

	v2 c1 = { a.frame, a.value };
	v2 c2 = { a.frame + a.right_handle_x, a.value + a.right_handle_y };
	v2 c3 = { b.frame + b.left_handle_x, b.value + b.left_handle_y };
	v2 c4 = { b.frame, b.value };
	v2 d = Lerp_v2(c1, c2, t);
	v2 e = Lerp_v2(c2, c3, t);
	v2 f = Lerp_v2(c3, c4, t);
	v2 g = Lerp_v2(d, e, t);
	v2 h = Lerp_v2(e, f, t);
	v2 i = Lerp_v2(g, h, t);

	return i.y;
}


char Intersect(Transform a, Transform b)
{
	float ax_half = a.scale.x / 2;
	float ay_half = a.scale.y / 2;
	float by_half = b.scale.y / 2;
	float bx_half = b.scale.x / 2;

	float a_right = a.position.x + ax_half;
	float a_left = a.position.x - ax_half;
	float a_top = a.position.y + ay_half;
	float a_bottom = a.position.y - ay_half;
	float b_right = b.position.x + bx_half;
	float b_left = b.position.x - bx_half;
	float b_top = b.position.y + by_half;
	float b_bottom = b.position.y - by_half;

	return a_right > b_left && a_left < b_right && a_top > b_bottom && a_bottom < b_top;
}


v3 GetCentroid(Triangle t)
{
	v3 v = v3_Add(v3_Add(t.a, t.b), t.c);
	v.x /= 3;
	v.y /= 3;
	v.z /= 3;
	return v;
}


char Less(Triangle a, Triangle b)
{
	v3 a_centroid = GetCentroid(a);
	v3 b_centroid = GetCentroid(b);

	return a_centroid.z < b_centroid.z;
}

void SwapTriangles(Triangle triangles[], int a, int b)
{
	Triangle temp = triangles[a];
	triangles[a] = triangles[b];
	triangles[b] = temp;
}

void SortByDepth(Triangle a[], int length)
{
	QuickSort(a, 0, length - 1);
}

void QuickSort(Triangle a[], int lo, int hi)
{
	if (hi <= lo) return;
	int j = Partition(a, lo, hi);
	QuickSort(a, lo, j - 1);
	QuickSort(a, j + 1, hi);
}

int Partition(Triangle a[], int lo, int hi)
{
	int i = lo;
	int j = hi + 1;
	Triangle v = a[lo];
	while (1)
	{
		while (Less(a[++i], v))
		{
			if (i == hi) break;
		}

		while (Less(v, a[--j]))
		{
			if (j == lo) break;
		}

		if (i >= j) break;

		SwapTriangles(a, i, j);
	}

	SwapTriangles(a, lo, j);

	return j;
}




float light_rotation = 0;
m4x4 camera_to_clip;
int WIDTH, HEIGHT;
unsigned int* pixels;

Mesh mesh;
Transform cube_transform;
Transform mesh_demo_camera;


typedef struct
{
	char splash_screen_started;
	char splash_screen_ended;
	float splash_screen_time;
	float splash_screen_alpha;
	Bitmap logo;
} SplashScreen;

SplashScreen splash;

void Init_SplashScreen()
{
	splash.splash_screen_started = 0;
	splash.splash_screen_ended = 0;
	splash.splash_screen_time = 0;
	splash.splash_screen_alpha = 0;
}

void DrawSplashScreen(float frames_per_second)
{
	memcpy(pixels, splash.logo.pixels, WIDTH * HEIGHT * 4);

	int pixel_count = WIDTH * HEIGHT;

	for (int i = 0; i < pixel_count; i += 4)
	{
		if (pixels[i] != 0xFF000000)
		{
			unsigned int red_channel = (unsigned int)((pixels[i] & 0xFF0000) * splash.splash_screen_alpha) & 0xFF0000;
			pixels[i] = 0xFF000000 | red_channel;
		}

		if (pixels[i + 1] != 0xFF000000)
		{
			unsigned int red_channel = (unsigned int)((pixels[i + 1] & 0xFF0000) * splash.splash_screen_alpha) & 0xFF0000;
			pixels[i + 1] = 0xFF000000 | red_channel;
		}

		if (pixels[i + 2] != 0xFF000000)
		{
			unsigned int red_channel = (unsigned int)((pixels[i + 2] & 0xFF0000) * splash.splash_screen_alpha) & 0xFF0000;
			pixels[i + 2] = 0xFF000000 | red_channel;
		}

		if (pixels[i + 3] != 0xFF000000)
		{
			unsigned int red_channel = (unsigned int)((pixels[i + 3] & 0xFF0000) * splash.splash_screen_alpha) & 0xFF0000;
			pixels[i + 3] = 0xFF000000 | red_channel;
		}
	}

	char result[50];
	sprintf(result, "FPS: %.3f", frames_per_second);
	string message = { strlen(result), result };
	DrawString(message, 0, 0);
}

__attribute__((dllexport)) char UpdateSplashScreen(float delta_time, float frames_per_second)
{
	if (splash.splash_screen_time > 10)
	{
		if (!splash.splash_screen_ended)
		{

			splash.splash_screen_ended = 1;
		}
		else
		{
			splash.splash_screen_time = 0;
			splash.splash_screen_ended = 0;
			splash.splash_screen_started = 0;
		}
	}

	if (!splash.splash_screen_started)
	{


		splash.splash_screen_started = 1;
	}

	DrawSplashScreen(frames_per_second);

	splash.splash_screen_time += delta_time;
	if (splash.splash_screen_time > 2 && splash.splash_screen_time < 7 && splash.splash_screen_alpha < 1)
	{
		splash.splash_screen_alpha += delta_time / 5;
		if (splash.splash_screen_alpha > 1)
			splash.splash_screen_alpha = 1;
	}

	if (splash.splash_screen_time > 8)
		splash.splash_screen_alpha -= delta_time;

	if (splash.splash_screen_alpha < 0)
		splash.splash_screen_alpha = 0;

	return splash.splash_screen_ended;;
}




Bitmap GetMyFunImage()
{
	FILE* file_pointer = fopen("P:/Assets/viking_studios_logo", "r");
	int width = 1920, height = 1080;
	unsigned int* pixels = malloc(sizeof(unsigned int) * width * height);
	fread(pixels, 4, 1920 * 1080, file_pointer);
	splash.logo.width = width;
	splash.logo.height = height;
	splash.logo.pixels = pixels;
	printf("This is here to remind that the image is being loaded more than once and that needs to be corrected at some point\n");
	fclose(file_pointer);
}

__attribute__((dllexport)) void InitViewport(float field_of_view, int width, int height, unsigned int _pixels[])
{
	WIDTH = width;
	HEIGHT = height;
	camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
	pixels = &_pixels[0];

	GetMyFunImage();
}

__attribute__((dllexport)) void InitMeshDemo()
{
	LoadFontSet();
	mesh = LoadMesh("P:/Assets/teapot.obj");
	v3 forward_10 = { 0, 0, 10 };
	v3 backward_30 = { 0, 0, -30 };
	v3 zero = { 0, 0, 0 };
	v3 one = { 1, 1, 1 };
	cube_transform.position = forward_10;
	cube_transform.rotation = zero;
	cube_transform.scale = one;
	mesh_demo_camera.position = backward_30;
	mesh_demo_camera.rotation = zero;
	mesh_demo_camera.scale = one;
}


__attribute__((dllexport)) void RunMeshDemo(float delta_time, float frames_per_second)
{

	{
		cube_transform.rotation.y += 6.28318530717958f / 16 * delta_time;
	}

	Fill(0xFF000000);

	size_t triangle_count = mesh.indices_length / 3;
	Triangle* triangles = malloc(triangle_count * sizeof(Triangle));


	{
		int i;
		for (i = 0; i < triangle_count; i++)
		{
			triangles[i].a = mesh.vertices[mesh.indices[i * 3 + 0]];
			triangles[i].b = mesh.vertices[mesh.indices[i * 3 + 1]];
			triangles[i].c = mesh.vertices[mesh.indices[i * 3 + 2]];
		}
	}


	{

		m4x4 object_to_world = GetMatrix(cube_transform);


		Transform inverted_camera = InvertTransform(mesh_demo_camera);
		m4x4 world_to_camera = GetMatrix(inverted_camera);
		m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

		int i;
		for (i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];


			{
				t.a = Transform_v3(object_to_camera, t.a);
				t.b = Transform_v3(object_to_camera, t.b);
				t.c = Transform_v3(object_to_camera, t.c);
			}

			triangles[i] = t;
		}


		{
			size_t remaining_count = triangle_count;
			for (int i = 0; i < triangle_count; i++)
			{
			label:
				if (i == remaining_count)
					break;
				Triangle t = triangles[i];
				v3 a = v3_Subtract(t.b, t.a);
				v3 b = v3_Subtract(t.c, t.a);
				v3 normal = v3_Normalized(CrossProduct(a, b));

				v3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, mesh_demo_camera.position));

				if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
				{
					SwapTriangles(triangles, i, remaining_count - 1);
					remaining_count--;
					goto label;
				}
				else
				{
					v3 backward = { 0,0,-1 };
					float dot = v3_DotProduct(normal, Transform_v3(Rotation(0, light_rotation, 0), backward));

					if (dot < 0)
						dot = 0;

					if (!((sizeof (dot) == sizeof (float) ? __fpclassifyf (dot)	: sizeof (dot) == sizeof (double) ? __fpclassify (dot) : __fpclassifyl (dot)) == 0x0100))
					{
						t.brightness = (unsigned char)(dot * 255);
						triangles[i] = t;
					}
				}
			}

			triangle_count = remaining_count;
			triangles = realloc(triangles, triangle_count * sizeof(Triangle));
		}

		for (int i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];
			t.a = CameraToClipToScreen(t.a);
			t.b = CameraToClipToScreen(t.b);
			t.c = CameraToClipToScreen(t.c);
			triangles[i] = t;
		}
	}


	{
		SortByDepth(triangles, triangle_count);
	}


	{
		for (int i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];
			unsigned int color = triangles[i].brightness;
			color = 0xFF000000 | (color << 16) | (color << 8) | color;
			FillTriangle(color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
		}
	}

	free(triangles);

	char result[50];
	sprintf(result, "%.3f", frames_per_second);
	char foo[50];
	strcpy(foo, "FPS: ");

	strcat(foo, result);
	string moopa = { strlen(foo), foo };
	DrawString(moopa, 16, 16);
}

void FillTriangle(unsigned int color, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (y1 == y2 && y2 == y3)
		return;


	{
		int temp;
		if (y1 > y2)
		{
			temp = y1;
			y1 = y2;
			y2 = temp;
			temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if (y1 > y3)
		{
			temp = y1;
			y1 = y3;
			y3 = temp;
			temp = x1;
			x1 = x3;
			x3 = temp;
		}
		if (y2 > y3)
		{
			temp = y2;
			y2 = y3;
			y3 = temp;
			temp = x2;
			x2 = x3;
			x3 = temp;
		}
	}

	int split = (int)(x1 + ((y2 - y1) / (float)(y3 - y1)) * (x3 - x1));

	if (x2 < split)
	{
		FillFlatBottom(color, y2, x2, split, y1, x1);
		FillFlatTop(color, y2, x2, split, y3, x3);
	}
	else
	{
		FillFlatBottom(color, y2, split, x2, y1, x1);
		FillFlatTop(color, y2, split, x2, y3, x3);
	}
}


void FillFlatBottom(unsigned int color, int bottom, int left, int right, int top, int middle)
{
	float dy = bottom - top;

	float inverted_slope1 = (middle - left) / dy;
	float inverted_slope2 = (middle - right) / dy;

	float l = left;
	float r = right;

	for (int scanline = bottom; scanline >= top; scanline--)
	{
		DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
		l += inverted_slope1;
		r += inverted_slope2;
	}
}


void FillFlatTop(unsigned int color, int top, int left, int right, int bottom, int middle)
{
	float dy = bottom - top;

	float inverted_slope1 = (middle - left) / dy;
	float inverted_slope2 = (middle - right) / dy;

	float l = left;
	float r = right;
	for (int scanline = top; scanline <= bottom; scanline++)
	{
		DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
		l += inverted_slope1;
		r += inverted_slope2;
	}
}

void DrawHorizontalSegment(unsigned int color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel(color, x, y);
	}
}

void PutPixel(unsigned int color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[y * WIDTH + x] = color;
}

void PutPixel_ByIndex(unsigned int color, int i)
{
	if (i >= 0 && i < WIDTH * HEIGHT)
		pixels[i] = color;
}

v3 CameraToClipToScreen(v3 v)
{
	v4 v_4 = { v.x, v.y, v.z, 1 };
	v_4 = Transform_Vector4(camera_to_clip, v_4);

	v.x = v_4.x;
	v.y = v_4.y;
	v.z = v_4.z;
	if (v_4.w != 0)
	{
		v.x /= v_4.w;
		v.y /= v_4.w;
		v.z /= v_4.w;
	}


	v.x++;
	v.y++;


	v.x *= WIDTH / 2;
	v.y *= HEIGHT / 2;

	return v;
}

unsigned int LerpColor(unsigned int a, unsigned int b, float t);

void FillVerticalGradient(unsigned int color1, unsigned int color2)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		unsigned int color = LerpColor(color1, color2, y / (float)HEIGHT);
		for (int x = 0; x < WIDTH; x++)
		{
			pixels[y * WIDTH + x] = color;
		}
	}
}

unsigned int LerpColor(unsigned int a, unsigned int b, float t)
{

	unsigned int a_a = (0xFF000000 & a) >> 24;
	unsigned int a_r = (0x00FF0000 & a) >> 16;
	unsigned int a_g = (0x0000FF00 & a) >> 8;
	unsigned int a_b = (0x000000FF & a);
	unsigned int b_a = (0xFF000000 & b) >> 24;
	unsigned int b_r = (0x00FF0000 & b) >> 16;
	unsigned int b_g = (0x0000FF00 & b) >> 8;
	unsigned int b_b = (0x000000FF & b);


	unsigned int l_a = (unsigned int)(((float)a_a) + (t * ((float)b_a - (float)a_a)));
	unsigned int l_r = (unsigned int)(((float)a_r) + (t * ((float)b_r - (float)a_r)));
	unsigned int l_g = (unsigned int)(((float)a_g) + (t * ((float)b_g - (float)a_g)));
	unsigned int l_b = (unsigned int)(((float)a_b) + (t * ((float)b_b - (float)a_b)));



	l_a <<= 24;
	l_r <<= 16;
	l_g <<= 8;



	unsigned int l = l_a | l_r | l_g | l_b;
	return l;
}

unsigned int BlendColor(unsigned int s, unsigned int d)
{
	unsigned int sA = (s & 0xFF000000) >> 24;
	unsigned int sR = (s & 0x00FF0000) >> 16;
	unsigned int sG = (s & 0x0000FF00) >> 8;
	unsigned int sB = (s & 0x000000FF);

	unsigned int dA = (d & 0xFF000000) >> 24;
	unsigned int dR = (d & 0x00FF0000) >> 16;
	unsigned int dG = (d & 0x0000FF00) >> 8;
	unsigned int dB = (d & 0x000000FF);

	float _sA = (sA / 255.0f);
	float _sR = (sR / 255.0f);
	float _sG = (sG / 255.0f);
	float _sB = (sB / 255.0f);
	float _dA = (dA / 255.0f);
	float _dR = (dR / 255.0f);
	float _dG = (dG / 255.0f);
	float _dB = (dB / 255.0f);

	unsigned int rA = (unsigned int)(((_sA * _sA) + (_dA * (1.0f - _sA))) * 255.0f);
	unsigned int rR = (unsigned int)(((_sR * _sA) + (_dR * (1.0f - _sA))) * 255.0f);
	unsigned int rG = (unsigned int)(((_sG * _sA) + (_dG * (1.0f - _sA))) * 255.0f);
	unsigned int rB = (unsigned int)(((_sB * _sA) + (_dB * (1.0f - _sA))) * 255.0f);

	rA <<= 24;
	rR <<= 16;
	rG <<= 8;

	unsigned int result = rA | rR | rG | rB;

	return result;
}

void Fill(unsigned int color)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] = color;
	}
}

__attribute__((dllexport)) Mesh LoadMesh(char* path)
{
	FILE* fp = fopen(path, "r");
	int line_number = 0;

	int vertex_count = 0;
	int index_count = 0;

	while (1)
	{
		char str[500];
		char* line = fgets(str, 500, fp);
		if (feof(fp))
			break;
		char* token = strtok(line, " ");
		char* ptr;
		switch (*token)
		{
		case 'v':
			vertex_count++;
			break;
		case 'f':
			index_count += 3;
			break;
		default:
			break;
		}
	}

	rewind(fp);

	Mesh return_mesh;
	v3* vertices = malloc(sizeof(v3) * vertex_count);
	int* indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_length = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_length = index_count;

	int vertex = 0;
	int index = 0;

	while (1)
	{
		char str[500];
		char* line = fgets(str, 500, fp);
		if (feof(fp))
			break;
		line_number++;
		char* token = strtok(line, " ");
		char* ptr;
		switch (*token)
		{
		case 'v':
			token = strtok(((void*)0), " ");
			float x = (float)strtod(token, &ptr);
			token = strtok(((void*)0), " ");
			float y = (float)strtod(token, &ptr);
			token = strtok(((void*)0), " ");
			float z = (float)strtod(token, &ptr);
			v3 v = { x, y, z };
			return_mesh.vertices[vertex++] = v;
			break;
		case 'f':
			token = strtok(((void*)0), " ");
			int a = (int)strtol(token, &ptr, 10);
			token = strtok(((void*)0), " ");
			int b = (int)strtol(token, &ptr, 10);
			token = strtok(((void*)0), " ");
			int c = (int)strtol(token, &ptr, 10);
			return_mesh.indices[index++] = a - 1;
			return_mesh.indices[index++] = b - 1;
			return_mesh.indices[index++] = c - 1;
			break;
		case '\n':

			break;
		default:

			break;
		}
	}

	fclose(fp);
	return return_mesh;
}

void DrawHorizontal(unsigned int color, int y)
{
	for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
		PutPixel_ByIndex(color, i);
}

void DrawLine(unsigned int color, float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	if (fabs(dx) >= fabs(dy))
	{
		if (x1 > x2)
		{
			float temp = y1;
			y1 = y2;
			y2 = temp;
			temp = x1;
			x1 = x2;
			x2 = temp;
		}
		for (float x = x1; x <= x2; x++)
		{
			float y = (y1 + dy * (x - x1) / dx);
			PutPixel(color, (int)x, (int)y);
		}
	}
	else
	{
		if (y1 > y2)
		{
			float temp = y1;
			y1 = y2;
			y2 = temp;
			temp = x1;
			x1 = x2;
			x2 = temp;
		}
		for (float y = y1; y <= y2; y++)
		{
			float x = (x1 + dx * (y - y1) / dy);
			PutPixel(color, (int)x, (int)y);
		}
	}
}

void DrawRectangle(unsigned int color, float x, float y, float width, float height)
{
	DrawLine(color, x, y, x + width, y);
	DrawLine(color, x, y, x, y + height);
	DrawLine(color, x + width, y, x + width, y + height);
	DrawLine(color, x, y + height, x + width, y + height);
}

void Flatten()
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] |= 0xFF000000;
	}
}

FillRectangle_Blend(unsigned int color, int x, int y, int width, int height)
{
	for (int _x = 0; _x < width; _x++)
	{
		for (int _y = 0; _y < height; _y++)
		{
			PutPixel(BlendColor(color, pixels[(y + _y) * WIDTH + (x + _x)]), _x + x, _y + y);
		}
	}
}

void  DrawHorizontal_Blend(unsigned int color, int y)
{
	for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
		PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
}

void DrawVertical_Blend(unsigned int color, int x)
{
	for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
	{
		PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
	}
}

void DrawVertical(unsigned int color, int x)
{
	for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
	{
		pixels[i] = color;
	}
}

void DrawGrid_ScreenSpace(int unit_size)
{
	for (int x = 0; x < WIDTH; x += unit_size)
	{
		DrawVertical(0xFF00FF00, x);
	}

	for (int y = 0; y < HEIGHT; y += unit_size)
	{
		DrawHorizontal(0xFF00FF00, y);
	}
}

void DrawVerticalSegment(unsigned int color, int x, int y1, int y2)
{
	for (int i = x + (y1 * WIDTH); i <= x + (y2 * WIDTH); i += WIDTH)
		PutPixel_ByIndex(color, i);
}

FillRectangle(unsigned int color, float x, float y, float width, float height)
{
	for (float _x = 0; _x <= width; _x++)
	{
		for (float _y = 0; _y <= height; _y++)
		{
			PutPixel(color, (int)(_x + x), (int)(_y + y));
		}
	}
}

void Draw_Circle(unsigned int color, float x, float y, float radius, float stroke)
{
	int x_min = (int)(x - radius - stroke / 2);
	int x_max = (int)roundf(x + radius + stroke / 2);
	int y_min = (int)(y - radius - stroke / 2);
	int y_max = (int)roundf(y + radius + stroke / 2);

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			float dx = _x - x;
			float dy = _y - y;

			float distance_squared = (float)(dx * dx + dy * dy);
			float distance = (float)sqrt(distance_squared);
			char distance_equals_radius_within_delta = distance <= radius + stroke / 2 && distance >= radius - stroke / 2;

			if (distance_equals_radius_within_delta)
				PutPixel(color, _x, _y);
		}
	}
}

void FillCircle(unsigned int color, float x, float y, float radius)
{
	int x_min = (int)roundf(x - radius);
	int x_max = (int)roundf(x + radius);
	int y_min = (int)roundf(y - radius);
	int y_max = (int)roundf(y + radius);

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			float dx = _x - x;
			float dy = _y - y;

			char distance_less_than_radius = dx * dx + dy * dy <= radius * radius;

			if (distance_less_than_radius)
				PutPixel(color, _x, _y);
		}
	}
}

void Blend_Circle(unsigned int color, float x, float y, float radius)
{
	int x_min = (int)roundf(x - radius);
	int x_max = (int)roundf(x + radius);
	int y_min = (int)roundf(y - radius);
	int y_max = (int)roundf(y + radius);

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			float dx = _x - x;
			float dy = _y - y;

			char distance_less_than_radius = dx * dx + dy * dy <= radius * radius;

			if (distance_less_than_radius)
			{
				int index = _y * WIDTH + _x;

				if (index >= 0 && index < (WIDTH * HEIGHT))
					PutPixel(BlendColor(color, pixels[_y * WIDTH + _x]), _x, _y);
			}
		}
	}
}

__attribute__((dllexport)) void Render(Mesh mesh, unsigned int* body_poly_colors, Transform camera, char fill_toggle)
{
	Fill(0xFF000000);


	{
		size_t triangle_count = mesh.indices_length / 3;
		Triangle* triangles = malloc(triangle_count * sizeof(Triangle));


		{
			int i;
			for (i = 0; i < triangle_count; i++)
			{
				triangles[i].a = mesh.vertices[mesh.indices[i * 3 + 0]];
				triangles[i].b = mesh.vertices[mesh.indices[i * 3 + 1]];
				triangles[i].c = mesh.vertices[mesh.indices[i * 3 + 2]];
				triangles[i].color = body_poly_colors[i];
			}
		}


		{

			m4x4 object_to_world = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};


			m4x4 world_to_camera = GetMatrix(InvertTransform(camera));

			m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangles[i];


				{
					t.a = Transform_v3(object_to_camera, t.a);
					t.b = Transform_v3(object_to_camera, t.b);
					t.c = Transform_v3(object_to_camera, t.c);
				}

				triangles[i] = t;
			}


			{
				size_t remaining_count = triangle_count;
				for (int i = 0; i < triangle_count; i++)
				{
				label:
					if (i == remaining_count)
						break;
					Triangle t = triangles[i];
					v3 a = v3_Subtract(t.b, t.a);
					v3 b = v3_Subtract(t.c, t.a);
					v3 normal = v3_Normalized(CrossProduct(a, b));

					v3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

					if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
					{
						SwapTriangles(triangles, i, remaining_count - 1);
						remaining_count--;
						goto label;
					}
					else
					{
						v3 backward = { 0,0,-1 };
						float dot = v3_DotProduct(normal, Transform_v3(Rotation(0, light_rotation, 0), backward));

						if (dot < 0)
							dot = 0;

						if (!((sizeof (dot) == sizeof (float) ? __fpclassifyf (dot)	: sizeof (dot) == sizeof (double) ? __fpclassify (dot) : __fpclassifyl (dot)) == 0x0100))
						{
							t.brightness = (unsigned char)(dot * 255);
							triangles[i] = t;
						}

						float light = t.brightness / 255.0f;

						unsigned int r = ((t.color & 0xFFFF0000) ^ 0xFF000000) >> 16;
						unsigned int g = ((t.color & 0xFF00FF00) ^ 0xFF000000) >> 8;
						unsigned int b = (t.color & 0xFF0000FF) ^ 0xFF000000;

						r = (unsigned int)(r * light);
						g = (unsigned int)(g * light);
						b = (unsigned int)(b * light);

						t.color = r << 16 | g << 8 | b | 0xFF000000;
						triangles[i] = t;
					}
				}

				triangle_count = remaining_count;
				triangles = realloc(triangles, triangle_count * sizeof(Triangle));
			}

			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangles[i];
				t.a = CameraToClipToScreen(t.a);
				t.b = CameraToClipToScreen(t.b);
				t.c = CameraToClipToScreen(t.c);
				triangles[i] = t;
			}
		}


		{
			SortByDepth(triangles, triangle_count);
		}


		{
			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangles[i];
				v2 a = { t.a.x, t.a.y };
				v2 b = { t.b.x, t.b.y };
				v2 c = { t.c.x, t.c.y };

				if (fill_toggle)
					FillTriangle_VertexColors(a, b, c, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF);
				else
					FillTriangle(t.color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
			}
		}

		free(triangles);
	}
}

float GetMin(float a, float b, float c)
{
	float r = (a < b) ? a : b;
	return (r < c) ? r : c;
}

float GetMax(float a, float b, float c)
{
	float r = (a > b) ? a : b;
	return (r > c) ? r : c;
}

v3 ToBarycentricSpace(float v_x, float v_y, v2 a, v2 b, v2 c)
{
	float b1, b2, b3;
	float denom = (a.y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - a.x);

	b1 = ((v_y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - v_x)) / denom;
	b2 = ((v_y - a.y) * (c.x - a.x) + (c.y - a.y) * (a.x - v_x)) / denom;
	b3 = ((v_y - b.y) * (a.x - b.x) + (a.y - b.y) * (b.x - v_x)) / denom;

	v3 result = { b1, b2, b3 };
	return result;
}

void FillTriangle_VertexColors(v2 a, v2 b, v2 c, unsigned int a_color, unsigned int b_color, unsigned int c_color)
{
	int x_min = (int)GetMin(a.x, b.x, c.x);
	int y_min = (int)GetMin(a.y, b.y, c.y);
	int x_max = (int)roundf(GetMax(a.x, b.x, c.x));
	int y_max = (int)roundf(GetMax(a.y, b.y, c.y));


	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			v3 v = ToBarycentricSpace(_x, _y, a, b, c);
			char in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if (in_triangle)
			{
				unsigned int d_color = LerpColor(c_color, a_color, v.x);
				unsigned int e_color = LerpColor(a_color, b_color, v.y);
				unsigned int f_color = LerpColor(e_color, d_color, v.z);
				PutPixel(f_color, _x, _y);
			}
		}
	}
}

enum Keys
{
	Keys_Tab = 9,
	Keys_Space = 32,
	Keys_Left = 37, Keys_Up, Keys_Right, Keys_Down,
	Keys_Delete = 46,
	Keys_A = 65, Keys_B, Keys_C, Keys_D, Keys_E, Keys_F, Keys_G, Keys_H, Keys_I, Keys_J, Keys_K, Keys_L, Keys_M, Keys_N, Keys_O, Keys_P, Keys_Q, Keys_R, Keys_S, Keys_T, Keys_U, Keys_V, Keys_W, Keys_X, Keys_Y, Keys_Z,
	Keys_F4 = 115,
	Keys_NumPad0 = 96, Keys_NumPad1, Keys_NumPad2, Keys_NumPad3, Keys_NumPad4, Keys_NumPad5, Keys_NumPad6, Keys_NumPad7, Keys_NumPad8, Keys_NumPad9,
};

enum Buttons
{
	LEFT,
	RIGHT,
	DOWN,
	JUMP,
	PUNCH
};


char keys_down[256];
char keys_stale[256];
char keyboard_state[256];

enum Keys control_mappings[4][5] =
{
	{Keys_A,       Keys_D ,       Keys_S,		 Keys_W,	   Keys_Q },
	{Keys_J,       Keys_L,        Keys_K,        Keys_I,       Keys_U },
	{Keys_Left,    Keys_Right,    Keys_Down,     Keys_Up,      Keys_Delete },
	{Keys_NumPad4, Keys_NumPad6,  Keys_NumPad5,  Keys_NumPad8, Keys_NumPad7 }
};

__attribute__((dllexport)) char KeyDownFresh(enum Keys key)
{
	return keys_down[key] && !keys_stale[key];
}

__attribute__((dllexport)) char KeyDown(enum Keys key)
{
	return keys_down[key];
}

char ButtonDown(int player, enum Buttons action)
{
	return KeyDown(control_mappings[player][action]);
}

char ButtonDownFresh(int player, enum Buttons action)
{
	return KeyDownFresh(control_mappings[player][action]);
}

__attribute__((dllexport)) void PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keys_stale[i] = keys_down[i];

	GetKeyboardState(keyboard_state);

	for (int i = 0; i < 256; i++)
		keys_down[i] = keyboard_state[i] & 128;

	for (int i = 0; i < 256; i++)
	{
		if (!keys_down[i])
			keys_stale[i] = 0;
	}
}

typedef struct
{
	int bone1, bone2, bone3, bone4;
} Weight_Index;

typedef struct
{
	Mesh mesh;
	int body_poly_colors_length;
	unsigned int* body_poly_colors;
	int skeleton_length;
	Transform* skeleton;
	int bind_matrices_length;
	m4x4* bind_matrices;
	int weights_length;
	v4* weights;
	int weight_indices_length;
	Weight_Index* weight_indices;

	int morph_weights_length;
	float* morph_weights;
	v3 transformed_vertices_length;
	v3* transformed_vertices;
	Transform camera;

	char has_a_face;
	char animate_face;
	int facial_index_offset;
	char fill_toggle;

	float frame;
	float animation_length;
	float rotation_y;
	char animation_play;
	char rotation_play;
	char view_debug;
	char view_fps;
	float facial_time;
} SkinnedMeshDemo;

SkinnedMeshDemo skinned_demo;
# 1632 "SGL.c"
void SetWeights()
{
# 1667 "SGL.c"
}

unsigned int* LoadPolygonColors(char* path)
{
	FILE* file_pointer = fopen(path, "r");

	int color_count = 0;
	while (1)
	{
		fgetc(file_pointer);
		fgetc(file_pointer);
		fgetc(file_pointer);
		fgetc(file_pointer);

		if (feof(file_pointer))
			break;

		color_count++;
	}

	rewind(file_pointer);
	unsigned int* colors = malloc(4 * color_count);

	for (int i = 0; i < color_count; i++)
	{
		int r = fgetc(file_pointer);
		int g = fgetc(file_pointer);
		int b = fgetc(file_pointer);
		int a = fgetc(file_pointer);
		colors[i] = (a << 24) | (b << 16) | (g << 8) | r;
	}

	fclose(file_pointer);
	return colors;
}

__attribute__((dllexport)) void SkinnedMeshDemo_Init()
{
	Transform camera = { 0, { 0, 0, -50 }, { 0, 0, 0 }, { 1, 1, 1 } };
	skinned_demo.camera = camera;
	skinned_demo.mesh = LoadMesh("P:/Assets/skin_translated.obj");
# 1759 "SGL.c"
	int triangle_count = skinned_demo.mesh.indices_length / 3;


	skinned_demo.body_poly_colors = malloc(triangle_count * sizeof(unsigned int));


	for (int i = 0; i < triangle_count; i++)
	{
		skinned_demo.body_poly_colors[i] = 0xFFFF0000;
	}

	skinned_demo.body_poly_colors = LoadPolygonColors("P:/Assets/skin_poly_colors");

	skinned_demo.body_poly_colors_length = triangle_count;

	SetWeights();
# 1800 "SGL.c"
}

void SkinnedMeshDemo_Input(float delta_time)
{
	float delta = 5 * delta_time;
	if (KeyDownFresh(Keys_Y))
		skinned_demo.view_fps = !skinned_demo.view_fps;

	if (KeyDownFresh(Keys_G))
		skinned_demo.view_debug = !skinned_demo.view_debug;
	if (KeyDown(Keys_W))
		skinned_demo.camera.position.y -= delta;
	if (KeyDown(Keys_S))
		skinned_demo.camera.position.y += delta;
	if (KeyDown(Keys_A))
		skinned_demo.camera.position.x += delta;
	if (KeyDown(Keys_D))
		skinned_demo.camera.position.x -= delta;

	if (KeyDown(Keys_Up))
		skinned_demo.camera.position.z += delta * 10;
	else if (KeyDown(Keys_Down))
		skinned_demo.camera.position.z -= delta * 10;

	if (KeyDownFresh(Keys_T))
	{
		skinned_demo.animation_play = !skinned_demo.animation_play;
	}

	if (KeyDownFresh(Keys_Q))
	{
		skinned_demo.animate_face = !skinned_demo.animate_face;
	}

	if (KeyDownFresh(Keys_F))
	{
		skinned_demo.has_a_face = !skinned_demo.has_a_face;

	}

	if (KeyDownFresh(Keys_R))
	{
		skinned_demo.rotation_play = !skinned_demo.rotation_play;
	}

	if (KeyDownFresh(Keys_Space))
		skinned_demo.fill_toggle = !skinned_demo.fill_toggle;
}

__attribute__((dllexport)) void SkinnedMeshDemo_Update(float delta_time)
{
	SkinnedMeshDemo_Input(delta_time);


	{
		if (skinned_demo.rotation_play)
		{
			skinned_demo.rotation_y += delta_time;

		}

		if (skinned_demo.animation_play)
		{

			{
# 1877 "SGL.c"
			}
		}

		m4x4 skeleton_matrices[skinned_demo.skeleton_length];


		{
			for (int i = 0; i < skinned_demo.skeleton_length; i++)
			{
				skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton);
			}
		}
# 1952 "SGL.c"
	}
# 1963 "SGL.c"
	Render(skinned_demo.mesh, skinned_demo.body_poly_colors, skinned_demo.camera, skinned_demo.fill_toggle);
}

typedef struct
{
	int transform_index;
	char property_tag;
	int keyframes_length;
	KeyFrame* keyframes;
} AnimationCurve;

typedef struct
{
	char looped;
	int curves_length;
	AnimationCurve* curves;
	int** defendbox_keys;
	char** defendbox_values;
	int** attackbox_keys;
	char** attackbox_values;
} Animation;

typedef struct
{
	float current_frame;
	Animation current_animation;
} Animator;



typedef struct
{
	char view_debug;


	Transform camera;
	float field_of_view;
	Transform* transforms;
	Player players[4];
	Animator animators[4];
	unsigned int player_colors[4];
	Transform blocks[30];


	int winner;
	char game_over;
	float initial_time;
	float time_remaining;
	float max_health;


	float gravity;


} GameplayState;


__attribute__((dllexport)) void UpdateGameplay()
{
# 2601 "SGL.c"
}

void GameplayState_Init()
{
# 2633 "SGL.c"
}

void ResetGame()
{
# 2709 "SGL.c"
}
# 2728 "SGL.c"
void PrintMesh(Mesh mesh)
{
	printf("indices:\n");
	for (int i = 0; i < mesh.indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
	}

	printf("vertices:\n");
	for (int i = 0; i < mesh.vertices_length; i++)
	{
		printf("{ %+f, %+f, %+f }\n", mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
	}
}

typedef struct
{
	char
		row1,
		row2,
		row3,
		row4,
		row5,
		row6,
		row7,
		row8;
} CharSprite;

char char_dict[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', '.', ':', ',', '_', '[', ']', '-', };

CharSprite font_set[44];

__attribute__((dllexport)) void FillSprites(CharSprite* sprites, int count)
{
	for (int i = 0; i < count; i++)
	{
		font_set[i] = sprites[i];
	}
}

void DrawCharacter(CharSprite sprite, int x, int y)
{
	char* p = &sprite.row1;
	for (int row = 0; row < 8; row++, p++)
	{
		for (int col = 0; col < 8; col++)
		{
			char pixel_active = ((*p << col) & 0b10000000) == 0b10000000;
			if (pixel_active)
				PutPixel(0xFFFFFFFF, col + x, row + y);
		}
	}
}

void DrawString(string s, int x, int y)
{
	for (int i = 0; i < s.length; i++)
	{
		char a = tolower(s.characters[i]);
		for (int o = 0; o < 44; o++)
		{
			if (a == char_dict[o])
			{
				DrawCharacter(font_set[o], x + i * 9, y);

			}

		}
	}
}
# 3499 "SGL.c"
typedef enum
{
	SplashScreenState,
	MeshDemo,
	SkinnedMesh,
	Gameplay,
} GameStates;

struct Game
{

	int WIDTH;
	int HEIGHT;
# 3523 "SGL.c"
	float previous_time;
	float delta_time;
	float time_since_last_frame;
	float time_scale;
	float time_scale;
	float frames_per_second;
	float time_since_timing_recalculated;
	char fixed_framerate;
	int frames_since_last_second;
	GameStates current_game_state;
}

__attribute__((dllexport)) void InitEverything()
{
	SkinnedMeshDemo_Init();
	InitMeshDemo();
	GameplayState_Init();
}
# 3759 "SGL.c"
void LoadFontSet()
{
	FILE* file_pointer = fopen("P:/Assets/font_set", "r");
	fread(font_set, 8, 44, file_pointer);
	fclose(file_pointer);
}

int main()
{
	printf("Here we go!");
	return 0;
}
# 1 "<stdin>"
