class C {
  bit V = true;
}

def X : C;
def Y : C {
  let V = false;
  string Greeting = "Hello!";
}

class FPFormat <bits<3> val> {
  bits<3> Value = val;
}

def NotFP      : FPFormat<0>;
def ZeroArgFP  : FPFormat<1>;
def OneArgFP   : FPFormat<2>;
def OneArgFPRW : FPFormat<3>;
def TwoArgFP   : FPFormat<4>;
def CompareFP  : FPFormat<5>;
def CondMovFP  : FPFormat<6>;
def SpecialFP  : FPFormat<7>;



multiclass Foo <int Bar> {
  def : FPFormat<Bar>;
}

foreach i = 0...5 in
  def Foo#i;
  
