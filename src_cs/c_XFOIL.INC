C
C====  XFOIL code global INCLUDE file  =====
C
C------ Primary dimensioning limit parameters
C IQX   number of surface panel nodes + 6
C IWX   number of wake panel nodes
C IPX   number of Qspec(s) distributions
C ISX   number of airfoil sides
C
C------ Derived dimensioning limit parameters
C IBX   number of buffer airfoil nodes
C IMX   number of complex mapping coefficients  Cn
C IZX   number of panel nodes (airfoil + wake)
C IVX   number of nodes along BL on one side of airfoil and wake
C NAX   number of points in stored polar
C NPX   number of polars and reference polars
C NFX   number of points in one reference polar
C
C---- include polar variable indexing parameters
C      INCLUDE 'PINDEX.INC'
C
c	use complexify
c	implicit complex(a-h, o-z)
      PARAMETER (IQX=286, IWX=36, IPX=5, ISX=2)
C      PARAMETER (IBX=2*IQX)
      PARAMETER (IBX=572)
C      PARAMETER (IZX=IQX+IWX)
      PARAMETER (IZX=322)
C      PARAMETER (IVX=IQX/2 + IWX + 50)
      PARAMETER (IVX=229)
      PARAMETER (NAX=800,NPX=8,NFX=128)
      CHARACTER*32 LABREF
      CHARACTER*64 FNAME, PFNAME, PFNAMX, ONAME, PREFIX
      CHARACTER*48 NAME, NAMEPOL, CODEPOL, NAMEREF
      CHARACTER*80 ISPARS
      LOGICAL OK,LIMAGE,
     &        LGAMU,LQINU,SHARP,LVISC,LALFA,LWAKE,LPACC,
     &        LBLINI,LIPAN,LQAIJ,LADIJ,LWDIJ,LCPXX,LQVDES,LQREFL,
     &        LQSPEC,LVCONV,LCPREF,LCLOCK,LPFILE,LPFILX,LPPSHO,
     &        LBFLAP,LFLAP,LEIW,LSCINI,LFOREF,LNORM,LGSAME,
     &        LPLCAM, LQSYM ,LGSYM , LQGRID, LGGRID, LGTICK,
     &        LQSLOP,LGSLOP, LCSLOP, LQSPPL, LGEOPL, LGPARM,
     &        LCPGRD,LBLGRD, LBLSYM, LCMINP, LHMOMP
      LOGICAL LPLOT,LSYM,LIQSET,LCLIP,LVLAB,LCURS,LLAND
      LOGICAL LPGRID, LPCDW, LPLIST, LPLEGN
      LOGICAL TFORCE, LEXITFLAG, PRINTCONV
      complex NX, NY, MASS, MINF1, MINF, MINF_CL, MVISC, MACHP1
      INTEGER RETYP, MATYP, AIJPIV
      CHARACTER*1 VMXBL
C
C---- dimension temporary work and storage arrays (EQUIVALENCED below)
      complex W1(6*IQX),W2(6*IQX),W3(6*IQX),W4(6*IQX),
     &     W5(6*IQX),W6(6*IQX),W7(6*IQX),W8(6*IQX)
      complex BIJ(IQX,IZX), CIJ(IWX,IQX)
C
      COMMON/CR01/ VERSION
      COMMON/CC01/ FNAME,
     &             NAME,ISPARS,ONAME,PREFIX,
     &             PFNAME(NPX),PFNAMX(NPX),
     &             NAMEPOL(NPX), CODEPOL(NPX),
     &             NAMEREF(NPX)
      COMMON/QMAT/ Q(IQX,IQX),DQ(IQX),
     &             DZDG(IQX),DZDN(IQX),DZDM(IZX),
     &             DQDG(IQX),DQDM(IZX),QTAN1,QTAN2,
     &             Z_QINF,Z_ALFA,Z_QDOF0,Z_QDOF1,Z_QDOF2,Z_QDOF3
      COMMON/CR03/ AIJ(IQX,IQX),DIJ(IZX,IZX)
      COMMON/CR04/ QINV(IZX),QVIS(IZX),CPI(IZX),CPV(IZX),
     &             QINVU(IZX,2), QINV_A(IZX)
      COMMON/CR05/ X(IZX),Y(IZX),XP(IZX),YP(IZX),S(IZX),
     &             SLE,XLE,YLE,XTE,YTE,CHORD,YIMAGE,
     &             WGAP(IWX),WAKLEN
      COMMON/CR06/ GAM(IQX),GAMU(IQX,2),GAM_A(IQX),SIG(IZX),
     &             NX(IZX),NY(IZX),APANEL(IZX),
     &             SST,SST_GO,SST_GP,
     &             GAMTE,GAMTE_A,
     &             SIGTE,SIGTE_A,
     &             DSTE,ANTE,ASTE
      COMMON/CR07/ SSPLE,
     &             SSPEC(IBX),XSPOC(IBX),YSPOC(IBX),
     &             QGAMM(IBX),
     &             QSPEC(IBX,IPX),QSPECP(IBX,IPX),
     &             ALGAM,CLGAM,CMGAM,
     &             ALQSP(IPX),CLQSP(IPX),CMQSP(IPX),
     &             QF0(IQX),QF1(IQX),QF2(IQX),QF3(IQX),
     &             QDOF0,QDOF1,QDOF2,QDOF3,CLSPEC,FFILT
      COMMON/CI01/ IQ1,IQ2,NSP,NQSP,KQTARG,IACQSP,NC1,NNAME,NPREFIX
      COMMON/CR09/ ADEG,ALFA,AWAKE,MVISC,AVISC,
     &             XCMREF,YCMREF,
     &             CL,CM,CD,CDP,CDF,CL_ALF,CL_MSQ,
     &             PSIO,CIRC,COSA,SINA,QINF,
     &             GAMMA,GAMM1,
     &             MINF1,MINF,MINF_CL,TKLAM,TKL_MSQ,CPSTAR,QSTAR,
     &             CPMN,CPMNI,CPMNV,XCPMNI,XCPMNV
      COMMON/CI03/ NCPREF, NAPOL(NPX), NPOL, IPACT, NLREF,
     &             ICOLP(NPX),ICOLR(NPX),
     &             IMATYP(NPX),IRETYP(NPX), NXYPOL(NPX),
     &             NPOLREF, NDREF(4,NPX)
      COMMON/CR10/ XPREF(IQX),CPREF(IQX), VERSPOL(NPX),
     &             CPOLXY(IQX,2,NPX),
     &             MACHP1(NPX),
     &             REYNP1(NPX),
     &             ACRITP(NPX),XSTRIPP(ISX,NPX)

c modified db
c      COMMON/CR10/ XPREF(IQX),CPREF(IQX), VERSPOL(NPX),
c     &             CPOL(NAX,IPTOT,NPX),
c     &             CPOLSD(NAX,ISX,JPTOT,NPX),
c     &             CPOLXY(IQX,2,NPX),
c     &             MACHP1(NPX),
c     &             REYNP1(NPX),
c     &             ACRITP(NPX),XSTRIPP(ISX,NPX),
c     &             CPOLREF(NFX,2,4,NPX)


      COMMON/CC02/ LABREF
C
      COMMON/CR11/ PI,HOPI,QOPI,DTOR
      COMMON/CR12/ CVPAR,CTERAT,CTRRAT,XSREF1,XSREF2,XPREF1,XPREF2
      COMMON/CI04/ N,NB,NW,NPAN,IST,KIMAGE,
     &             ITMAX,NSEQEX,RETYP,MATYP,AIJPIV(IQX),
     &             IDEV,IDEVRP,IPSLU,NCOLOR,
     &             ICOLS(ISX),NOVER, NCM,NTK
      COMMON/CR13/ SIZE,SCRNFR,PLOTAR, PFAC,QFAC,VFAC,
     &             XWIND,YWIND,
     &             XPAGE,YPAGE,XMARG,YMARG,
     &             CH, CHG, CHQ,
     &             XOFAIR,YOFAIR,FACAIR, XOFA,YOFA,FACA,UPRWT,
     &             CPMIN,CPMAX,CPDEL,
     &             CPOLPLF(3,4),
     &             XCDWID,XALWID,XOCWID
      COMMON/CL01/ OK,LIMAGE,SHARP,
     &             LGAMU,LQINU,LVISC,LALFA,LWAKE,LPACC,
     &             LBLINI,LIPAN,LQAIJ,LADIJ,LWDIJ,LCPXX,LQVDES,LQREFL,
     &             LQSPEC,LVCONV,LCPREF,LCLOCK,LPFILE,LPFILX,LPPSHO,
     &             LBFLAP,LFLAP,LEIW,LSCINI,LFOREF,LNORM,LGSAME,
     &             LPLCAM,LQSYM ,LGSYM,
     &             LQGRID,LGGRID,LGTICK,
     &             LQSLOP,LGSLOP,LCSLOP,LQSPPL,LGEOPL,LGPARM,
     &             LCPGRD,LBLGRD,LBLSYM,
     &             LPLOT,LSYM,LIQSET,LCLIP,LVLAB,LCURS,LLAND,
     &             LPGRID,LPCDW,LPLIST,LPLEGN,
     &             LCMINP, LHMOMP, LEXITFLAG, PRINTCONV
      COMMON/CR14/ XB(IBX),YB(IBX),
     &             XBP(IBX),YBP(IBX),SB(IBX),SNEW(4*IBX),
     &             XBF,YBF,XOF,YOF,HMOM,HFX,HFY,
     &             XBMIN,XBMAX,YBMIN,YBMAX,
     &             SBLE,CHORDB,AREAB,RADBLE,ANGBTE,
     &             EI11BA,EI22BA,APX1BA,APX2BA,
     &             EI11BT,EI22BT,APX1BT,APX2BT,
     &             THICKB,CAMBRB,
     &     XCM(2*IBX),YCM(2*IBX),SCM(2*IBX),XCMP(2*IBX),YCMP(2*IBX),
     &     XTK(2*IBX),YTK(2*IBX),STK(2*IBX),XTKP(2*IBX),YTKP(2*IBX)
C
      COMMON/CR15/ XSSI(IVX,ISX),UEDG(IVX,ISX),UINV(IVX,ISX),
     &             MASS(IVX,ISX),THET(IVX,ISX),DSTR(IVX,ISX),
     &             CTAU(IVX,ISX),DELT(IVX,ISX),USLP(IVX,ISX),
     &             GUXQ(IVX,ISX),GUXD(IVX,ISX),
     &             TAU(IVX,ISX),DIS(IVX,ISX),CTQ(IVX,ISX),
     &             VTI(IVX,ISX),
     &             REINF1,REINF,REINF_CL,ACRIT,
     &             XSTRIP(ISX),XOCTR(ISX),YOCTR(ISX),XSSITR(ISX),
     &             UINV_A(IVX,ISX)
      COMMON/CI05/ IBLTE(ISX),NBL(ISX),IPAN(IVX,ISX),ISYS(IVX,ISX),NSYS,
     &             ITRAN(ISX)
      COMMON/CL02/ TFORCE(ISX)
      COMMON/CR17/ RMSBL,RMXBL,RLX,VACCEL
      COMMON/CI06/ IMXBL,ISMXBL
      COMMON/CC03/ VMXBL
      COMMON/CR18/ XSF,YSF,XOFF,YOFF,
     &             XGMIN,XGMAX,YGMIN,YGMAX,DXYG,
     &             XCMIN,XCMAX,YCMIN,YCMAX,DXYC,DYOFFC,
     &             XPMIN,XPMAX,YPMIN,YPMAX,DXYP,DYOFFP,
     &             YSFP,GTICK
C
      COMMON/VMAT/ VA(3,2,IZX),VB(3,2,IZX),VDEL(3,2,IZX),
     &             VM(3,IZX,IZX),VZ(3,2)
C
C
C---- save storage space
      EQUIVALENCE (Q(1,1 ),W1(1)), (Q(1,7 ),W2(1)),
     &            (Q(1,13),W3(1)), (Q(1,19),W4(1)),
     &            (Q(1,25),W5(1)), (Q(1,31),W6(1)),
     &            (Q(1,37),W7(1)), (Q(1,43),W8(1))
      EQUIVALENCE (VM(1,1,1),BIJ(1,1)), (VM(1,1,IZX/2),CIJ(1,1))
C
C
C   VERSION     version number of this XFOIL implementation
C
C   FNAME       airfoil data filename
C   PFNAME(.)   polar append filename
C   PFNAMX(.)   polar append x/c dump filename
C   ONAME       default overlay airfoil filename
C   PREFIX      default filename prefix
C   NAME        airfoil name
C
C   ISPARS      ISES domain parameters  (not used in XFOIL)
C
C   Q(..)       generic coefficient matrix
C   DQ(.)       generic matrix righthand side
C
C   DZDG(.)     dPsi/dGam
C   DZDN(.)     dPsi/dn
C   DZDM(.)     dPsi/dSig
C
C   DQDG(.)     dQtan/dGam
C   DQDM(.)     dQtan/dSig
C   QTAN1       Qtan at alpha =  0 deg.
C   QTAN2       Qtan at alpha = 90 deg.
C
C   Z_QINF      dPsi/dQinf
C   Z_ALFA      dPsi/dalfa
C   Z_QDOF0     dPsi/dQdof0
C   Z_QDOF1     dPsi/dQdof1
C   Z_QDOF2     dPsi/dQdof2
C   Z_QDOF3     dPsi/dQdof3
C
C   AIJ(..)     dPsi/dGam  influence coefficient matrix (factored if LQAIJ=t)
C   BIJ(..)     dGam/dSig  influence coefficient matrix
C   CIJ(..)     dQtan/dGam influence coefficient matrix
C   DIJ(..)     dQtan/dSig influence coefficient matrix
C   QINV(.)     tangential velocity due to surface vorticity
C   QVIS(.)     tangential velocity due to surface vorticity & mass sources
C   QINVU(..)   QINV for alpha = 0, 90 deg.
C   QINV_A(.)   dQINV/dalpha
C
C   X(.),Y(.)   airfoil (1<i<N) and wake (N+1<i<N+NW) coordinate arrays
C   XP(.),YP(.) dX/dS, dY/dS arrays for spline evaluation
C   S(.)        arc length along airfoil (spline parameter)
C   SLE         value of S at leading edge
C   XLE,YLE     leading  edge coordinates
C   XTE,YTE     trailing edge coordinates
C   WGAP(.)     thickness of "dead air" region inside wake just behind TE
C   WAKLEN      wake length to chord ratio
C
C   GAM(.)      surface vortex panel strength array
C   GAMU(.2)    surface vortex panel strength arrays for alpha = 0, 90 deg.
C   GAM_A(.)    dGAM/dALFA
C   SIG(.)      surface and wake mass defect array
C
C   NX(.),NY(.) normal unit vector components at airfoil and wake coordinates
C   APANEL(.)   surface and wake panel angle array (+ counterclockwise)
C
C   SST         S value at stagnation point
C   SST_GO      dSST/dGAM(IST)
C   SST_GP      dSST/dGAM(IST+1)
C
C   GAMTE       vortex panel strength across finite-thickness TE
C   SIGTE       source panel strength across finite-thickness TE
C   GAMTE_A     dGAMTE/dALFA
C   SIGTE_A     dSIGTE/dALFA
C   DSTE        TE panel length
C   ANTE,ASTE   projected TE thickness perp.,para. to TE bisector
C   SHARP       .TRUE.  if  DSTE.EQ.0.0 ,  .FALSE. otherwise
C
C   SSPEC(.)    normalized arc length around airfoil (QSPEC coordinate)
C   XSPOC(.)    x/c at SSPEC points
C   YSPOC(.)    y/c at SSPEC points
C   QSPEC(..)   specified surface velocity for inverse calculations
C   QSPECP(..)  dQSPEC/dSSPEC
C   QGAMM(.)    surface velocity for current airfoil geometry
C   SSPLE       SSPEC value at airfoil nose
C
C   IQ1,IQ2     target segment endpoint indices on Qspec(s) plot
C   NSP         number of points in QSPEC array
C   NQSP        number Qspec arrays
C   IACQSP      1:  ALQSP is prescribed for Qspec arrays
C               2:  CLQSP is prescribed for Qspec arrays
C   NC1         number of circle plane points, must be 2**n - 1
C
C   NNAME       number of characters in airfoil name
C   NPREFIX     number of characters in default filename prefix
C
C   ALQSP(.)    alpha,CL,CM corresponding to QSPEC distributions
C   CLQSP(.)
C   CMQSP(.)
C   ALGAM       alpha,CL,CM corresponding to QGAMM distribution
C   CLGAM
C   CMGAM
C
C   QF0(.)      shape function for QSPEC modification
C   QF1(.)        "
C   QF2(.)        "
C   QF3(.)        "
C   QDOF0       shape function weighting coefficient (inverse DOF)
C   QDOF1         "
C   QDOF2         "
C   QDOF3         "
C   CLSPEC      specified CL
C   FFILT       circle-plane mapping filter parameter
C
C   ADEG,ALFA   angle of attack in degrees, radians
C   AWAKE       angle of attack corresponding to wake geometry (radians)
C   AVISC       angle of attack corresponding to BL solution   (radians)
C   MVISC       Mach number corresponding to BL solution
C   CL,CM       current CL and CM calculated from GAM(.) distribution
C   CD          current CD from BL solution
C   CDF         current friction CD from BL solution
C   CL_ALF      dCL/dALFA
C   CL_MSQ      dCL/d(MINF^2)
C
C   PSIO        streamfunction inside airfoil
C   CIRC        circulation
C   COSA,SINA   cos(ALFA), sin(ALFA)
C   QINF        freestream speed    (defined as 1)
C   GAMMA,GAMM1 Gas constant Cp/Cv, Cp/Cv - 1
C   MINF1       freestream Mach number at CL=1
C   MINF        freestream Mach number at current CL
C   MINF_CL     dMINF/dCL
C   TKLAM       Karman-Tsien parameter Minf^2 / [1 + sqrt(1-Minf^2)]^2
C   TKL_MSQ     d(TKLAM)/d(MINF^2)
C   CPSTAR      sonic pressure coefficient
C   QSTAR       sonic speed
C
C   NCPREF      number of reference Cp vs x/c points
C   XPREF(.)    x/c array corresponding to reference Cp data array
C   CPREF(.)    reference Cp data array
C   LABREF      reference Cp data descriptor string
C
C   NLREF       number of characters in LABREF string
C   NAPOL(.)    number of points in each stored polar
C   NPOL        number of stored polars
C   IPACT       index of "active" polar being accumulated (0 if none are)
C   ICOLP(.)    color for each polar
C   ICOLR(.)    color for each reference polar
C
C   NDREF(..)   number of points in each stored reference polar
C   NPOLREF     number of stored reference polars
C
C   VERSPOL(.)  version number of generating-code for each polar
C   CPOL(...)   CL,CD,and other parameters for each polar
C   CPOLXY(.1.) x,y coordinates of airfoil geometry which generated each polar
C   CPOLXY(.2.)
C   NXYPOL(.)   number of x,y points in CPOLXY array
C
C   PXTR(..)    transition locations for each polar
C   NAMEPOL(.)  airfoil names for each polar
C   CODEPOL(.)  generating-code names for each polar
C
C   NAMEREF(.)  name label of reference polar
C
C   PI          3.1415926...
C   HOPI,QOPI   1/(2 Pi) ,  1/(4 Pi)
C   DTOR        Pi / 180    (degrees to radians conversion factor)
C
C   CVPAR       curvature attraction parameter for airfoil paneling
C               0 = uniform panel node spacing around airfoil
C              ~1 = panel nodes strongly bunched in areas of large curvature
C   CTERAT      TE panel density / LE panel density ratio
C   CTRRAT      local refinement panel density / LE panel density ratio
C   XSREF1-2    suction  side local refinement x/c limits
C   XPREF1-2    pressure side local refinement x/c limits
C
C   N           number of points on airfoil
C   NB          number of points in buffer airfoil array
C   NW          number of points in wake
C   NPAN        default/specified number of points on airfoil
C
C   IST         stagnation point lies between S(IST), S(IST+1)
C   ITMAX       max number of Newton iterations
C   NSEQEX      max number of unconverged sequence points for early exit
C
C   RETYP       index giving type of Re variation with CL ...
C            ... 1  Re constant
C            ... 2  Re ~ 1/sqrt(CL)    (fixed lift)
C            ... 3  Re ~ 1/CL          (fixed lift and dynamic pressure)
C
C   MATYP       index giving type of Ma variation with CL ...
C            ... 1  Ma constant
C            ... 2  Ma ~ 1/sqrt(CL)    (fixed lift)
C
C   AIJPIV(.)   pivot index array for LU factoring routine
C
C   IDEV        "device" number for normal screen plotting
C   IDEVRP      "device" number for replotting (typically for hardcopy)
C   IPSLU       PostScript file specifier
C   NCOLOR      Number of defined colors in colormap
C   ICOLS(1)    color indices of top side
C   ICOLS(2)    color indices of bottom side
C
C   NOVER       number of airfoils overlaid on GDES geometry plot
C
C   SCRNFR      screen fraction taken up by initial plot window
C   SIZE        plot width (inches)
C   PLOTAR      plot aspect ratio
C   XWIND,YWIND window size in inches
C   XPAGE,YPAGE plot-page size in inches (for hardcopy)
C   XMARG,YMARG margin dimensions in inches
C   PFAC        scaling factor for  Cp
C   QFAC        scaling factor for  q  (surface speed)
C   VFAC        scaling factor for  Cp vectors
C   CH          character width / plot size  ratio
C   CHG         character width / plot size  ratio for geometry plot
C   CHQ         character width / plot size  ratio for Qspec(s) plot
C
C   XOFAIR      x offset for airfoil in  Cp vs x plots
C   YOFAIR      y offset for airfoil in  Cp vs x plots
C   FACAIR      scale factor for airfoil in  Cp vs x plots
C   XOFA        x offset for airfoil in  Cp vs x plots in airfoil units
C   YOFA        y offset for airfoil in  Cp vs x plots in airfoil units
C   FACA        scale factor for airfoil in  Cp vs x plots  in airfoil units
C   UPRWT       u/Qinf scale factor for profile plotting
C   CPMAX       max Cp  in  Cp vs x plots
C   CPMIN       min Cp  in  Cp vs x plots
C   CPDEL       delta Cp  in  Cp vs x plots
C
C   CPOLPLF(1,ICD)  min CD in CD-CL polar plot
C   CPOLPLF(2,ICD)  max CD in CD-CL polar plot
C   CPOLPLF(3,ICD)  delta CD in CD-CL polar plot
C
C   XCDWID      width of CD   -CL polar plot
C   XALWID      width of alpha-CL polar plot
C   XOCWID      width of Xtr/c-CL polar plot
C
C   OK          user question response
C   LIMAGE      .TRUE. if image airfoil is present
C   LGAMU       .TRUE. if GAMU  arrays exist for current airfoil geometry
C   LQINU       .TRUE. if QINVU arrays exist for current airfoil geometry
C   LVISC       .TRUE. if viscous option is invoked
C   LALFA       .TRUE. if alpha is specifed, .FALSE. if CL is specified
C   LWAKE       .TRUE. if wake geometry has been calculated
C   LPACC       .TRUE. if each point calculated is to be saved
C   LBLINI      .TRUE. if BL has been initialized
C   LIPAN       .TRUE. if BL->panel pointers IPAN have been calculated
C   LQAIJ       .TRUE. if dPsi/dGam matrix has been computed and factored
C   LADIJ       .TRUE. if dQ/dSig matrix for the airfoil has been computed
C   LWDIJ       .TRUE. if dQ/dSig matrix for the wake has been computed
C   LQVDES      .TRUE. if viscous Ue is to be plotted in QDES routines
C   LQSPEC      .TRUE. if Qspec has been initialized
C   LQREFL      .TRUE. if reflected Qspec is to be plotted in QDES routines
C   LVCONV      .TRUE. if converged BL solution exists
C   LCPREF      .TRUE. if reference data is to be plotted on Cp vs x/c plots
C   LCLOCK      .TRUE. if source airfoil coordinates are clockwise
C   LPFILE      .TRUE. if polar file is ready to be appended to
C   LPFILX      .TRUE. if polar dump file is ready to be appended to
C   LPPSHO      .TRUE. if CL-CD polar is plotted during point sequence
C   LBFLAP      .TRUE. if buffer  airfoil flap parameters are defined
C   LFLAP       .TRUE. if current airfoil flap parameters are defined
C   LEIW        .TRUE. if unit circle complex number array is initialized
C   LSCINI      .TRUE. if old-airfoil circle-plane arc length s(w) exists
C   LFOREF      .TRUE. if CL,CD... data is to be plotted on Cp vs x/c plots
C   LNORM       .TRUE. if input buffer airfoil is to be normalized
C   LGSAME      .TRUE. if current and buffer airfoils are identical
C
C   LPLCAM      .TRUE. if thickness and camber are to be plotted
C   LQSYM       .TRUE. if symmetric Qspec will be enforced
C   LGSYM       .TRUE. if symmetric geometry will be enforced
C   LQGRID      .TRUE. if grid is to overlaid on Qspec(s) plot
C   LGGRID      .TRUE. if grid is to overlaid on buffer airfoil geometry plot
C   LGTICK      .TRUE. if node tick marks are to be plotted on buffer airfoil
C   LQSLOP      .TRUE. if modified Qspec(s) segment is to match slopes
C   LGSLOP      .TRUE. if modified geometry segment is to match slopes
C   LCSLOP      .TRUE. if modified camber line segment is to match slopes
C   LQSPPL      .TRUE. if current Qspec(s) in in plot
C   LGEOPL      .TRUE. if current geometry in in plot
C   LCPGRD      .TRUE. if grid is to be plotted on Cp plots
C   LBLGRD      .TRUE. if grid is to be plotted on BL variable plots
C   LBLSYM      .TRUE. if symbols are to be plotted on BL variable plots
C   LCMINP      .TRUE. if min Cp is to be written to polar file for cavitation
C   LHMOMP      .TRUE. if hinge moment is to be written to polar file
C
C   LPGRID      .TRUE. if polar grid overlay is enabled
C   LPCDW       .TRUE. if polar CDwave is plotted
C   LPLIST      .TRUE. if polar listing lines (at top of plot) are enabled
C   LPLEGN      .TRUE. if polar legend is enabled
C
C   LPLOT       .TRUE. if plot page is open
C   LSYM        .TRUE. if symbols are to be plotted in QDES routines
C   LIQSET      .TRUE. if inverse target segment is marked off in QDES
C   LCLIP       .TRUE. if line-plot clipping is to be performed
C   LVLAB       .TRUE. if label is to be plotted on viscous-variable plots
C   LCURS       .TRUE. if cursor input is to be used for blowups, etc.
C   LLAND       .TRUE. if Landscape orientation for PostScript is used
C
C
C   XB(.),YB(.) buffer airfoil coordinate arrays
C   XBP(.)      dXB/dSB
C   YBP(.)      dYB/dSB
C   SB(.)       spline parameter for buffer airfoil
C   SNEW(.)     new panel endpoint arc length array
C
C   XBF,YBF     buffer  airfoil flap hinge coordinates
C   XOF,YOF     current airfoil flap hinge coordinates
C   HMOM        moment of flap about hinge point
C   HFX         x-force of flap on hinge point
C   HFY         y-force of flap on hinge point
C
C~~~~~~~~~~~~~~ properties of current buffer airfoil
C
C   XBMIN,XBMAX  limits of XB array
C   YBMIN,YBMAX  limits of YB array
C   SBLE         LE tangency-point SB location
C   CHORDB       chord
C   AREAB        area
C   RADBLE       LE radius
C   ANGBTE       TE angle  (rad)
C
C   EI11BA       bending inertia about axis 1    x^2 dx dy
C   EI22BA       bending inertia about axis 2    y^2 dx dy
C   APX1BA       principal axis 1 angle
C   APX2BA       principal axis 2 angle
C
C   EI11BT       bending inertia about axis 1    x^2 t ds
C   EI22BT       bending inertia about axis 2    y^2 t ds
C   APX1BT       principal axis 1 angle
C   APX2BT       principal axis 2 angle
C
C   THICKB       max thickness
C   CAMBRB       max camber
C
C~~~~~~~~~~~~~~
C
C   XSSI(..)    BL arc length coordinate array on each surface
C   UEDG(..)    BL edge velocity array
C   UINV(..)    BL edge velocity array without mass defect influence
C   MASS(..)    BL mass defect array  ( = UEDG*DSTR )
C   THET(..)    BL momentum thickness array
C   DSTR(..)    BL displacement thickness array
C   CTAU(..)    sqrt(max shear coefficient) array
C               (in laminar regions, log of amplification ratio)
C
C   TAU(..)     wall shear stress array                 (for plotting only)
C   DIS(..)     dissipation array                       (for plotting only)
C   CTQ(..)     sqrt(equilibrium max shear coefficient) array (  "  )
C   VTI(..)     +/-1 conversion factor between panel and BL variables
C   UINV_A(..)  dUINV/dalfa array
C
C   REINF1      Reynolds number  Vinf c / ve  for CL=1
C   REINF       Reynolds number for current CL
C   REINF_CL    dREINF/dCL
C
C   ACRIT       log (critical amplification ratio)
C   XSTRIP(.)   transition trip  x/c locations (if XTRIP > 0),
C               transition trip -s/s_side locations (if XTRIP < 0),
C   XOCTR(.)    actual transition x/c locations
C   YOCTR(.)    actual transition y/c locations
C   XSSITR(.)   actual transition xi locations
C
C   IBLTE(.)    BL array index at trailing edge
C   NBL(.)      max BL array index
C   IPAN(..)    panel index corresponding to BL location
C   ISYS(..)    BL Newton system line number corresponding to BL location
C   NSYS        total number of lines in BL Newton system
C   ITRAN(.)    BL array index of transition interval
C   TFORCE(.)   .TRUE. if transition is forced due to transition strip
C
C   VA,VB(...)  diagonal and off-diagonal blocks in BL Newton system
C   VZ(..)      way-off-diagonal block at TE station line
C   VM(...)     mass-influence coefficient vectors in BL Newton system
C   VDEL(..)    residual and solution vectors in BL Newton system
C
C   RMSBL       rms change from BL Newton system solution
C   RMXBL       max change from BL Newton system solution
C   IMXBL       location of max change
C   ISMXBL      index of BL side containing max change
C   VMXBL       character identifying variable with max change
C   RLX         underrelaxation factor for Newton update
C   VACCEL      parameter for accelerating BL Newton system solution
C               (any off-diagonal element < VACCEL is not eliminated,
C                which speeds up each iteration, but MAY increase
C                iteration count)
C                Can be set to zero for unadulterated Newton method
C
C   XOFF,YOFF   x and y offsets for windowing in QDES,GDES routines
C   XSF ,YSF    x and y scaling factors for windowing in QDES,GDES routines
C
C   XGMIN       airfoil grid plot limits
C   XGMAX
C   YGMIN
C   YGMAX
C   DXYG        airfoil grid-plot annotation increment
C   GTICK       airfoil-plot tick marks size (as fraction of arc length)
