
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <thread>

static const char* const dog_frames[] =
{
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"           _a,                \n"
"          _1=3,      a_/      \n"
"         _CvZcs    _J<%3,     \n"
"        _CvXXz)Lsa_VidX>X     \n"
"       clvXXXXaa%|1aXSXz)6    \n"
"      J<oXXXXXXXSoXXXXXXs*,   \n"
"    _Tl%#mmmZe+)YXXX>+XXXs3/  \n"
"   JswXonWWWmwaaaXX#owmmmo%[  \n"
"  _edXZvQWWWm#ZZXZU*!?$WmZ>(  \n"
"  ]1SXh3WWWQWm##X#X>::3WWE=[  \n"
"  \"z3X#oXWWWQWm2Y1X=:=dW#1j' \n"
"   4>3X#BWWWWQWQwwaasw#U1u'   \n"
"    !a*1mWWWQWWWWWBYeYSc3     \n"
"     \"su#mQWQWQQWQh3mo%v{[   \n"
"      cn#WWWQWQWQWWw3YXSi[    \n"
"      cXZBWQWQWQWQQWmgaa%9/   \n"
"      enZWWWQWQWWQWWQWmXXss   \n"
"      o3S#WWQWWQWQWQWWWZXX%[  \n"
"      ]>XZQWWQWQWQWWWQW#XXi[  \n"
"       o{XZWWWB$QWQWQW#XX1u'  \n"
"       \"z3XX#WmvQWWQW$#X2v'  \n"
"        ]c3XX#WcYTS1ijZXe3    \n"
"         -c{ZXm1P??4vmZX<[    \n"
"          E<ZZZn'  J]#Xld     \n"
"         ]1mmYo[   k3meu'     \n"
"         \"wow\"     k*17     \n",
//////////////////////////////////
"                              \n"
"          J!9/      _,a       \n"
"         J(uc3     _Ca%L      \n"
"        _1vXSiLaa JCvSo)[     \n"
"        CvXXXas>l3luoXXs3,    \n"
"    JXL)voXXXXX2X2X2XXXX%3,   \n"
"   ]nZ><oXme+SXoX1**nXXXX>3   \n"
"   Evm>3mQm6adXXos=amZ#mm6i[  \n"
"   CnX%3WWWX??X#ZZ##ZmWWmZ=L  \n"
"   CnX6vWWm=.:3ZZZ##mQWWWE<[  \n"
"   kvZ#mmBWi::3S2SXmWWWQW(j'  \n"
"   5IXZ#WWBpsi>vaqmWBWWZ1u'   \n"
"   '{ISXWWWWWmWWQWQWYvlc3     \n"
"     4>X#WWWWQQWWQWW{#oz)6    \n"
"      cn#WQQWWWQWQWW)WXo|L    \n"
"      c3#WWWWQWQWQWWmv*1|$    \n"
"      ev#WWWQWQWQWWQWWmZs3    \n"
"      ovXWWWQWQWQWQWWWQXXiL   \n"
"      ))Z#WWQWQWWQWWQWWXXi[   \n"
"      ]>XZWQWQWQWQWQWWWXXi[   \n"
"       z3XWWWQWWQWQWWWZSir    \n"
"       ]>3XWWWWWWUVV$#Xej     \n"
"        k)Z#2nwwar''zXX(7     \n"
"        kiXZs[      ={o|[     \n"
"        EiX(7       )<Xi[     \n"
"        )v2v'       =vm<f     \n"
"        ]%mP        ]>17      \n"
"         ''          ??       \n"
"                              \n"
"                              \n",
//////////////////////////////////
"                              \n"
"                              \n"
"          as,      _VY,       \n"
"         Jl>3,     Ei%),      \n"
"        JluXc3, aaJ|oZs3,     \n"
"       _kiXXXvdY1IivXXX>d     \n"
"       JvXXXXXSoXXXoSXXX%V/   \n"
"  _a/ JiXXZ1<SXXX++|XZZXX>3   \n"
"  Eu3J<dmmQoudZZoawqZ#Qmmo%L  \n"
"  k3o><mmWWZ!?X#Z#ZmmWWWBZcd  \n"
"  ]vXz=$BWm>..v#ZZ##WWWWWZc(  \n"
"   eSXc)$WQc::{211XmBWWW#Zi[  \n"
"   {vXX;3W#massawmQWWQWmZ1j   \n"
"   'pIXXXXmmWWWWQQWWWWW#o<[   \n"
"    '[IXXXWWWWWQWQWQWWX#2|[   \n"
"      !%TX#WWWQWQWWWW&3#e=[   \n"
"       k)X#WWQWQWB1wwwXZ(=d   \n"
"       CnXWWWWQWQh3VVY*lv%3   \n"
"      ]lX#WWWQWQWWQgmmQ#S>d   \n"
"      )<ZmmWWWQWQWWWWWWXXid   \n"
"      k{Z#WQQWQWQWQWWWWXX|[   \n"
"      5)ZWBWWQWQWQWQWQ#X2v'   \n"
"      ]>XXWWQWQWQWWWWWX2i7    \n"
"       o{X#WVTYYYTVWW#X(7     \n"
"       ]|SXXlP?!!!'a3XSi[     \n"
"       _cnX2{[     ]iZX<[     \n"
"       'z3Xe7      ?i#e]      \n"
"        k32v'       v#C7      \n"
"        ]%m'        war'      \n"
"                              \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                   _Y?,       \n"
"         _G*L     _Eic],      \n"
"        _S)h%8    J|dXs*,     \n"
"        J=ZXo%H#Y*|vSXXs3,    \n"
"       J1uXXXXouuXX2XXXX%*6   \n"
"      _1uXXXYXX2XX**XXXZXo)L  \n"
"      hvXm#c=dXXe=<vd#mWmmz)[ \n"
" _aa  evmWmmZZZZZZ#Z#mWWW#o>d \n"
"]SovYLc3mWW}~+3ZUZ##mQWmQmXid \n"
"'{2XXa>+$Qmc..vXZXZ#WWWWWm2v' \n"
"  !u3XXs*$Wp;==*lumWWWWWBZ|7  \n"
"    {ISSau##mgmmQWWWWWWW#Z>[  \n"
"     !a{XXWBWWWWWWWWWQ#UXX>[  \n"
"       {)Z#WWQWQWWQQWWkvZX|[  \n"
"       ]vXWWWQWQWQWWWW1de<|[  \n"
"       EvXWWWWQWQWQWWSvX|u|[  \n"
"      JidmWWWQWQWQWW1wX<uX|[  \n"
"      evXWWWWQWQWQWC31wmXX<[  \n"
"      cXZmWWWQWQWWQWQWWZXej   \n"
"      c2ZBWWQWQWQWQWWWWXXi7   \n"
"      cSXWWWWQWQWQWQWW#X(j    \n"
"      5>SZWBUTVYTTHWW#Xev'    \n"
"       5>SXC{F'!''{o9XX>(     \n"
"       ](vXC{[     4%BX|[     \n"
"       ]<mXe3       id2{'     \n"
"       kvmZl(      ]vmej      \n"
"       5%Yn7       'a1o'      \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                    a         \n"
"                   E|3,       \n"
"         _Jt,     J(dc),      \n"
"        _D<a*6   _E{XXo)a     \n"
"        ]|dXo%LJY*iuXXoaIL,   \n"
"        k<XSXooauSXoSXXXX%?6  \n"
"       JloXXXSXSXX!*3XXmmXa*f \n"
"      _CnX#p;iZZ2i=vu#mBWmXc3 \n"
"      ]|XmmmmXZZZX###mWWWWZc3 \n"
"      ]>dWWD^=+X#Z#ZmWWWWm#k3 \n"
"    aaJ>3WW#;;=3XZ3#WWWWWWB17 \n"
"  JSaaaa=VWma;;|lswmWWWWWWEn/ \n"
"  'd1SXXo%3$WqmmmQWWWWWWWmo%L \n"
"    !av*XXXmmmWWQWQWWQWWQmZc3 \n"
"      ''u*XmWQQWQWQWQWWWSZXe3 \n"
"     a,sZ(vmWWWQWQWWQWWEnZXe3 \n"
"    ]io%BdUWWQWQWQWQWWEnXXX1d \n"
"    ]%*{XXmWWWQWQWQWBYqXXX|<[ \n"
"     !cnXmWWQWQWQWW1om#21i>j  \n"
"      c3X#WWWQWQWQQwwwouo2i'  \n"
"      {{X#WWWWQWWWWWWW#XXiP   \n"
"      'cSX#WXWWWQQWQWWXo=3/   \n"
"       5%{Z#h{WWW8UVYYSXXI[   \n"
"        4iX#Enuow~^'4zvX2v[   \n"
"       _1uZXv'      Jnm2n?    \n"
"       ]uvnu'       avnr'     \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                   __a        \n"
"                   Cs)L       \n"
"         _5?L     JiXo>L      \n"
"        _Cno%3, as1{XXo%L     \n"
"        ]=XXo%3Y<ssnXXXovYs   \n"
"       _CvXXXZX2XXSoSXXXZo%L  \n"
"       Ev2XX!YXXX*+|nX#mmmo%L \n"
"      ](oZmm>uXXXaawX#mWWmXsd \n"
"      )<XmW#ZYYUZXZ#ZmWWWWZ(d \n"
"      J=mWWE::=3ZZ#ZmQWWWm#i7 \n"
"  JSoov>{QWm>::3X2YXQWWWWW2d[ \n"
" 'aYXXZX%?W#w>=%bwmmWWWWWWhI[ \n"
"  ''{aISSauZ##mQWWWWWWWWWmZc3 \n"
"      !o%BX#WWQQWWWWWQWQW#ZC3 \n"
"        'a{XWWWWQWQWQWWWCXXe3 \n"
"     _J??lvmWWWQWQWQWQW1uUX13 \n"
"    ]1v(vdmWWWWQWQWWWDsuXX(i3 \n"
"    'a+vXXmWWWQWQWWYnymX1iui7 \n"
"     )<XXXWWWWQWQWWoXYYnwZej  \n"
"     ]>SXX#WWQWQWQWQWWWB#ev'  \n"
"      {%HZ#B$WWQWWQWWW#Yiu'   \n"
"       5>SXXcXWWWWWWW#Xc3     \n"
"        5|XXzvwwuwouaIZe)[    \n"
"        J<Xm}d     alwX(j     \n"
"       _1wZ*u'    _lm#1w'     \n"
"       'v1o'      'wna7       \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                    %_        \n"
"          c_/      J<%|       \n"
"         J{a3a    ]cdS%b      \n"
"        ]|uXaI6_a_TiX2o%L     \n"
"       _kiXXXoooiaoXSXXovL/   \n"
"       EvdXXXXXXXXZo2XoZov3,  \n"
"      JiXXXZ=<XXX*+<{XZ#Zm%b/ \n"
" asa  euXmWWqdZZXooomXmWmmov[ \n"
"]vqodLz3mQWZ'+{#XU#Z#mWWW#X{[ \n"
" 4d#mv+)QWWk;:<XXXZ##WWWWmen[ \n"
"  'zVZo>3WWp;::*Y1nmWWWWBBi7  \n"
"   'w2Xo%Y$mmawwwmQWWWWWWe)[  \n"
"     5%HXmmmWWWWQWWWWWW#XX<[  \n"
"      !c3ZWWWWWQWWQWQWCXXe=[  \n"
"       4<ZWWWWQWQWQWW@sdX<%[  \n"
"       Ei#WWWQWQWQWDYsdS<oI[  \n"
"      ](dZWWQWQWQWQcYYnamX{[  \n"
"      )<XmWWQWQWWQWmmWWW#2]   \n"
"      k)#WWWWQWQWQWQWWWW#e3   \n"
"      k)Z$WWQWQWQWWQQWWmZ<7   \n"
"      5>X#WWQWQWWQQWWWW#}j    \n"
"       :%8#WVVVVVV$WWQ#X<[    \n"
"        k{ZC>''!'!{z$W#zv[    \n"
"        :vXes      ]%#81{[    \n"
"        k3Xc7       cdX(j     \n"
"        k3Zv'      _vmeu'     \n"
"        kvw'       'v1w'      \n",
//////////////////////////////////
"                  a_/         \n"
"        JV,      Ji%3/        \n"
"       J1o%b    _CnXc3/       \n"
"      _(dXovLas,V{XX2cs       \n"
"      JvX2XooosuanXXXS%V,     \n"
"     ]soXXXXZSSXXS2XXXXa?a    \n"
" _VVaCdXmz=nXX2}-|nX#Z#Xa3/   \n"
" ]nq%{XmBmwXZXXoowZmBWW#XI[   \n"
" 'zXm%bWWe^+3ZZZ#m#QWWW#Xs[   \n"
"  ]v#o2$m>::vXZZZ#mWWWWmXv[   \n"
"   e3mod#a;:+Y*nXmWWWWWms3    \n"
"   4%HXX#UqwwwmmQQWWQWW#o)[   \n"
"    !z1XSXmmWQWQWWQWWW#Xo<[   \n"
"     'o3X#WWQWQWQQWWW#vXe=6   \n"
"      '{I#WWQWQWQWVTV1uZ(|d   \n"
"       Cu#WWWWQWWWz$WW21i%3   \n"
"      ]iX#WWQWQWQWmwoowwSc3   \n"
"      u)ZWWWWQWQWQQWQQW#Xe]   \n"
"      k]ZWWWWQWWQWWWWWQ#X(j   \n"
"      k)#mWWWQWQWQWQQWWXSi7   \n"
"      ]>X#WWQWQWQWQWWW#Xev[   \n"
"      'o)##WW#W8W#WWWWZ2i7    \n"
"       'c3dEvw{wwwwuY#2<P     \n"
"        cvZe;      ]{Z2)'     \n"
"       _c3X17      ]{ZX)/     \n"
"        k32n       ]}mo)f     \n"
"        :In[       ]IU1q      \n"
"         ?'         '{7'      \n"
"                              \n"
"                              \n",
//////////////////////////////////
"                              \n"
"         aYL                  \n"
"        J(a%[     _J?L        \n"
"       J1uXn3,   _DsX%L       \n"
"      _CuoXX>*YtaSvSXo)[      \n"
"     _CoXXXXXSovvoXXXXaX/     \n"
"    _SvXXXX221XXXXX1XXX%$     \n"
"    J|3mmmXe|;{XXXc=dZZXIL    \n"
"   ]iX3BWW#ZZqZXUZZ##WQXsd    \n"
"   )vXv$WWmm#ZZZ#}=-]WW#id    \n"
"   5{Xo3WWWW#XZZXs;:]QWZim    \n"
"   )<X#oXWWWmmvvl=;=mW#(][    \n"
"   'cnXWWWQWQWWmmmmmXXsun[    \n"
"    4%8ZWWWWWQWQQWWmoZXXv[    \n"
"     -z{#WWWWQWWQWDYY$ZX%L    \n"
"      ]|X#WWWWQWQWh3maIXsd    \n"
"      )<XWBWQQWQWWQaYSXXlm    \n"
"      )<ZWBQWWQWWQWQma}iv$    \n"
"      u)#WWWWQWQWQWWWWmXo3,   \n"
"      kvXmWWQWQWQWQWQWWXXi[   \n"
"      k)XWWWWQWQWQWQWWWXoi[   \n"
"      ))Z#WWQWQWQWWQWQ#XX{[   \n"
"      'c3XWWWW#W#W#WWW&X1u    \n"
"       'cn#W&v^'''{%W#Xev'    \n"
"        k{Z#ed     h3ZS>(     \n"
"        kvX#1P     5{Zo<[     \n"
"        k]mC7      ]}mZv'     \n"
"        :v1w'      '%Q17      \n"
"        )'?         !w7       \n"
"                              \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"          _a                  \n"
"         _C|X                 \n"
"        a(uXi,     aYY,       \n"
"       a(uXXs3a   Jluo3,      \n"
"      J1uXXXovl?VUvdXX%b      \n"
"    _E<oX2XSXXXXnXZXXXo3,     \n"
"   _Ev2SXXXo*!3XSX1*3XXz3     \n"
"   ]iSn2Xmmma<vXXZoad#mSIL    \n"
"   ]>|uZdQQQZZZXZZYYXWmXcd    \n"
"   ]suZSWWWB#Z#Z#(::]WWmid    \n"
"   ]iXmz#WWW#Z1XX(::3mWZi[    \n"
"   ]%HXmdWWWWmwoai>smmD+d'    \n"
"    pvXZWmWWWQQQWWW#ZSs%3     \n"
"     4c1#BWWQWWWWWW#YYoo3/    \n"
"      )|XBWWQWQQWQWzqo)X>U/   \n"
"      )|XQWWQWQWQWWm3WoXiIL   \n"
"      )|XmWWQWWQWQWQp?S}{v3   \n"
"      )|XWWWQWQWQWQWWmmoXov[  \n"
"      ]|X#WWWQWQWQWWWQWmXXv[  \n"
"      'cSX$WQWWQWWWQWWW#S1{'  \n"
"       4%BX#WWQWQWQWWQW#Xlj   \n"
"        !v{XX#D$WQWWWW#X2<[   \n"
"         'z1XXh}TTYSz3XX(j    \n"
"          'oiXZsF!' k3ZXiP    \n"
"           E{S17   JnWX}j     \n"
"          ]id1r'  _1m#}v'     \n"
"           pw!     :Paw'      \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"          _                   \n"
"        _Jl?/                 \n"
"        J<Xcs     _JYs        \n"
"      _E<dXoIa   _Evd%[       \n"
"     _EvXXXXsI!YU1aXSz]/      \n"
"    J1voXXXSXXouoqXX2X%L      \n"
"   J1I11ZXoX1XX2XX1XXXo3,     \n"
"  _C<o#hmmh|;+SXXo;vXmXcd     \n"
"  EidZSnQW#XqSXXZ#XmmBme{[    \n"
" ]sdX}qWWWmZZZXZZ~=)WBmz3[    \n"
" ]z3XaWWWmWZXZUXo;;=mmW(d,    \n"
"  kIS#WWWWWQmav*|:=vW#1v'     \n"
"   p{XWBWWWWWWmmpso3X({waa    \n"
"   'z3XWWWWQWQQQk3W>3e+*s%3,  \n"
"    ]%3#WWWWQWWWmv#od1{a)Xs[  \n"
"     kv#WWWQWQWQWp3S*ioXs%y[  \n"
"     !vXWWWWQWWWWWmmmmXSXi7   \n"
"     ]%8ZWWQWWQQWQWWWQ#2S>L   \n"
"      {vXX#WWWWWQWQWQ#1nXiP   \n"
"       4%*8X$#2$WWWWD{wS1v'   \n"
"        ''w%BX#aYYYna<Z2<P    \n"
"           CvSS}j??_1mZ(j     \n"
"          Jvm2iw' _Cm#1u'     \n"
"          5anw'   )aXa7       \n",
//////////////////////////////////
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"                              \n"
"         _,a                  \n"
"        _Ca%[      _a/        \n"
"       _CvXss     _Cs3/       \n"
"      ]1uXXo)Ls, J1uZ%b       \n"
"     JludXXXos>IYvoXXo][      \n"
"   _E<vXXXXSXXXoXXZXXXvX      \n"
"   E+iiIXmX1*1XXXX|3XXX%L     \n"
"  J(iX#smW#a>=dXXpsu#mSz3     \n"
"  2<dZvmWWZZZZXXZYYXmmme{[    \n"
"  k3XlmWWWWZ#ZZ#C;::$Wmzv'    \n"
"  zIXqdBWWmmZXXXe=:<mmBiq     \n"
"  4%BX$WQWWWmwaui=<w#V|w'     \n"
"   4%I#WWWWQWQWQmnv}Sa%L      \n"
"    #iZWWWQWQWQWWcdmvni*YYs   \n"
"    ]<XmWWWWQWQWQm%B#Sc=Is)/  \n"
"    ]>X#WWQWQWWQWWmw%}<os|<[  \n"
"    'zvXWWWWQWQWWQQWQg2XX|r'  \n"
"     ]>XZQWQWWWQWQWWWWZX2|[   \n"
"      {%BXWBWWVQWQWQWD1X2{[   \n"
"       4%YXXWXa*QWBU!<XX1v'   \n"
"        ':%*1XXc<vsv=dXe<7    \n"
"          ]c<X2(j 4[wq2|w     \n"
"          JvmZlv' 4>#Xi7'     \n"
"          :msw7'  'asw'       \n"
};


int main()
{
  uint8_t frame_num = 0;

  setbuf(stdout, NULL);

  constexpr std::size_t NUM_FRAMES = sizeof(dog_frames) / sizeof(char*);
  while(true)
  {
    std::system("clear");
    printf("%s", dog_frames[(frame_num++) % NUM_FRAMES]);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

