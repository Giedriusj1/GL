inline double findnoise2(double x,double y)

{

  int n=(int)x+(int)y*57;

  n=(n<<13)^n;

  int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;

  return 1.0-((double)nn/1073741824.0);

}
