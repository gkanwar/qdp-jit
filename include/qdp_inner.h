// -*- C++ -*-
// $Id: qdp_inner.h,v 1.2 2003-08-14 03:47:03 edwards Exp $

/*! \file
 * \brief Inner grid
 */


QDP_BEGIN_NAMESPACE(QDP);

//-------------------------------------------------------------------------------------
/*! \addtogroup iscalar Inner grid scalar
 * \ingroup fiberbundle
 *
 * Inner grid scalar means sites are the slowest varying index. There can
 * still be an Outer grid.
 *
 * @{
 */

//! Scalar inner lattice
/*! All inner lattices are of IScalar or ILattice type */
template<class T> class IScalar
{
public:
  IScalar() {}
  ~IScalar() {}

  //---------------------------------------------------------
  //! construct dest = const
  IScalar(const typename WordType<T>::Type_t& rhs) : F(rhs) {}

  //! construct dest = rhs
  template<class T1>
  IScalar(const IScalar<T1>& rhs) : F(rhs.elem()) {}

  //! construct dest = rhs
  template<class T1>
  IScalar(const T1& rhs) : F(rhs) {}

  //---------------------------------------------------------
#if 0
  //! dest = const
  /*! Fill with an integer constant. Will be promoted to underlying word type */
  inline
  IScalar& operator=(const typename WordType<T>::Type_t& rhs)
    {
      elem() = rhs;
      return *this;
    }
#endif

  //! IScalar = IScalar
  /*! Set equal to another IScalar */
  template<class T1>
  inline
  IScalar& operator=(const IScalar<T1>& rhs) 
    {
      elem() = rhs.elem();
      return *this;
    }

  //! IScalar += IScalar
  template<class T1>
  inline
  IScalar& operator+=(const IScalar<T1>& rhs) 
    {
      elem() += rhs.elem();
      return *this;
    }

  //! IScalar -= IScalar
  template<class T1>
  inline
  IScalar& operator-=(const IScalar<T1>& rhs) 
    {
      elem() -= rhs.elem();
      return *this;
    }

  //! IScalar *= IScalar
  template<class T1>
  inline
  IScalar& operator*=(const IScalar<T1>& rhs) 
    {
      elem() *= rhs.elem();
      return *this;
    }

  //! IScalar /= IScalar
  template<class T1>
  inline
  IScalar& operator/=(const IScalar<T1>& rhs) 
    {
      elem() /= rhs.elem();
      return *this;
    }

  //! IScalar %= IScalar
  template<class T1>
  inline
  IScalar& operator%=(const IScalar<T1>& rhs) 
    {
      elem() %= rhs.elem();
      return *this;
    }

  //! IScalar |= IScalar
  template<class T1>
  inline
  IScalar& operator|=(const IScalar<T1>& rhs) 
    {
      elem() |= rhs.elem();
      return *this;
    }

  //! IScalar &= IScalar
  template<class T1>
  inline
  IScalar& operator&=(const IScalar<T1>& rhs) 
    {
      elem() &= rhs.elem();
      return *this;
    }

  //! IScalar ^= IScalar
  template<class T1>
  inline
  IScalar& operator^=(const IScalar<T1>& rhs) 
    {
      elem() ^= rhs.elem();
      return *this;
    }

  //! IScalar <<= IScalar
  template<class T1>
  inline
  IScalar& operator<<=(const IScalar<T1>& rhs) 
    {
      elem() <<= rhs.elem();
      return *this;
    }

  //! IScalar >>= IScalar
  template<class T1>
  inline
  IScalar& operator>>=(const IScalar<T1>& rhs) 
    {
      elem() >>= rhs.elem();
      return *this;
    }

  //! Deep copies here
  IScalar(const IScalar& a): F(a.F) {/* fprintf(stderr,"copy IScalar\n"); */}

public:
  T& elem() {return F;}
  const T& elem() const {return F;}

private:
  T F;
};


 
// Input
//! Ascii input
template<class T>
inline
istream& operator>>(istream& s, IScalar<T>& d)
{
  s >> d.elem();
  return s;
}

//! Ascii output
template<class T> 
inline  
ostream& operator<<(ostream& s, const IScalar<T>& d)
{
  return s << d.elem();
}


//! Text input
template<class T>
inline
TextReader& operator>>(TextReader& s, IScalar<T>& d)
{
  return s >> d.elem();
}

//! Text output
template<class T> 
inline  
TextWriter& operator<<(TextWriter& s, const IScalar<T>& d)
{
  return s << d.elem();
}


//! Namelist output
template<class T>
inline
NmlWriter& operator<<(NmlWriter& s, const IScalar<T>& d)
{
  return s << d.elem();
}

//! XML output
template<class T>
inline
XMLWriter& operator<<(XMLWriter& xml, const IScalar<T>& d)
{
  return xml << d.elem();
}

//! XML input
template<class T>
inline
void read(XMLReader& xml, const string& path, IScalar<T>& d)
{
  read(xml, path, d.elem());
}


/*! @} */  // end of group iscalar




//-------------------------------------------------------------------------------------
//! Inner lattice class
/*!
 * Lattice class for vector like architectures. 
 * Also mixed mode super-scalar architectures with vector extensions
 *
 * @{
 */
template<class T, int N> class ILattice
{
public:
  ILattice() {}
  ~ILattice() {}

  //---------------------------------------------------------
  //! construct dest = const
  ILattice(const typename WordType<T>::Type_t& rhs)
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs;
    }

  //! construct dest = rhs
  template<class T1>
  ILattice(const ILattice<T1,N>& rhs)
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs.elem(i);
    }

  //! construct dest = rhs
  template<class T1>
  ILattice(const T1& rhs)
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs;
    }

  //---------------------------------------------------------
#if 0
  //! dest = const
  /*! Fill with an integer constant. Will be promoted to underlying word type */
  inline
  ILattice& operator=(const typename WordType<T>::Type_t& rhs)
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs;

      return *this;
    }
#endif

  //---------------------------------------------------------
  //! ILattice = IScalar
  /*! Set equal to an IScalar */
  template<class T1>
  inline
  ILattice& operator=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs.elem();

      return *this;
    }

  //! ILattice += IScalar
  template<class T1>
  inline
  ILattice& operator+=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) += rhs.elem();

      return *this;
    }

  //! ILattice -= IScalar
  template<class T1>
  inline
  ILattice& operator-=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) -= rhs.elem();

      return *this;
    }

  //! ILattice *= IScalar
  template<class T1>
  inline
  ILattice& operator*=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) *= rhs.elem();

      return *this;
    }

  //! ILattice /= IScalar
  template<class T1>
  inline
  ILattice& operator/=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) /= rhs.elem();

      return *this;
    }

  //! ILattice %= IScalar
  template<class T1>
  inline
  ILattice& operator%=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) %= rhs.elem();

      return *this;
    }

  //! ILattice |= IScalar
  template<class T1>
  inline
  ILattice& operator|=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) |= rhs.elem();

      return *this;
    }

  //! ILattice &= IScalar
  template<class T1>
  inline
  ILattice& operator&=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) &= rhs.elem();

      return *this;
    }

  //! ILattice ^= IScalar
  template<class T1>
  inline
  ILattice& operator^=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) ^= rhs.elem();

      return *this;
    }

  //! ILattice <<= IScalar
  template<class T1>
  inline
  ILattice& operator<<=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) <<= rhs.elem();

      return *this;
    }

  //! ILattice >>= IScalar
  template<class T1>
  inline
  ILattice& operator>>=(const IScalar<T1>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) >>= rhs.elem();

      return *this;
    }

  //---------------------------------------------------------
  //! ILattice = ILattice
  /*! Set equal to another ILattice */
  template<class T1>
  inline
  ILattice& operator=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) = rhs.elem(i);

      return *this;
    }

  //! ILattice += ILattice
  template<class T1>
  inline
  ILattice& operator+=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) += rhs.elem(i);

      return *this;
    }

  //! ILattice -= ILattice
  template<class T1>
  inline
  ILattice& operator-=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) -= rhs.elem(i);

      return *this;
    }

  //! ILattice *= ILattice
  template<class T1>
  inline
  ILattice& operator*=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) *= rhs.elem(i);

      return *this;
    }

  //! ILattice /= ILattice
  template<class T1>
  inline
  ILattice& operator/=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) /= rhs.elem(i);

      return *this;
    }

  //! ILattice %= ILattice
  template<class T1>
  inline
  ILattice& operator%=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) %= rhs.elem(i);

      return *this;
    }

  //! ILattice |= ILattice
  template<class T1>
  inline
  ILattice& operator|=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) |= rhs.elem(i);

      return *this;
    }

  //! ILattice &= ILattice
  template<class T1>
  inline
  ILattice& operator&=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) &= rhs.elem(i);

      return *this;
    }

  //! ILattice ^= ILattice
  template<class T1>
  inline
  ILattice& operator^=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) ^= rhs.elem(i);

      return *this;
    }

  //! ILattice <<= ILattice
  template<class T1>
  inline
  ILattice& operator<<=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) <<= rhs.elem(i);

      return *this;
    }

  //! ILattice >>= ILattice
  template<class T1>
  inline
  ILattice& operator>>=(const ILattice<T1,N>& rhs) 
    {
      for(int i=0; i < N; ++i)
	elem(i) >>= rhs.elem(i);

      return *this;
    }

#if 0
  // NOTE: intentially avoid defining a copy constructor - let the compiler
  // generate one via the bit copy mechanism. This effectively achieves
  // the first form of the if below (QDP_USE_ARRAY_INITIALIZER) without having
  // to use that syntax which is not strictly legal in C++.
#endif

  //! Deep copy constructor
#if defined(QDP_USE_ARRAY_INITIALIZER)
  ILattice(const ILattice& a) : F(a.F) {}
#else
  /*! This is a copy form - legal but not necessarily efficient */
  ILattice(const ILattice& a)
    {
      // fprintf(stderr,"copy ILattice\n");
      for(int i=0; i < N; ++i)
	F[i] = a.F[i];
    }
#endif

public:
  T& elem(int i) {return F[i];}
  const T& elem(int i) const {return F[i];}

private:
  /*! For now a fixed representation */
  T F[N];

} QDP_ALIGN8;   // possibly force alignment


#if 0
// NOT IMPLEMENTED YET 

//! Stream output
template<class T, int N>
inline
ostream& operator<<(ostream& s, const ILattice<T,N>& d)
{
  for(int i=0; i < N; ++i)
    s << d.elem(i) << "\n";
  return s;
}

//! Text input
template<class T, int N>
inline
TextReader& operator>>(TextReader& s, ILattice<T,N>& d)
{
  for(int i=0; i < N; ++i)
    s >> d.elem(i);
  return s;
}

//! Text output
template<class T, int N> 
inline  
TextWriter& operator<<(TextWriter& s, const ILattice<T,N>& d)
{
  for(int i=0; i < N; ++i)
    s << d.elem(i) << "\n";
  return s;
}


//! Namelist output
template<class T, int N>
inline
NmlWriter& operator<<(NmlWriter& nml, const ILattice<T,N>& d)
{
  nml.get() << "[ ";
  nml << d.real();
  nml.get() << " , ";
  nml << d.imag();
  nml.get() << " ]";

  return nml;
}

//! XML output
template<class T, int N>
inline
XMLWriter& operator<<(XMLWriter& xml, const ILattice<T,N>& d)
{
  xml.openTag("re");
  xml << d.real();
  xml.closeTag();
  xml.openTag("im");
  xml << d.imag();
  xml.closeTag();

  return xml;
}

//! XML input
template<class T, int N>
inline
void read(XMLReader& xml, const string& path, ILattice<T,N>& d)
{
  std::ostringstream error_message;
  
  // XPath for the real part 
  string path_real = xpath + "/re";
	
  // XPath for the imaginary part.
  string path_imag = xpath + "/im";
	
  // Try and recursively get the real part
  try { 
    read(xml, path_real, result.real());
  }
  catch(const string &e) {
    error_message << "XPath Query: " << xpath << " Error: "
		  << "Failed to match real part of RComplex Object with self constructed path: " << path_real;
    
    throw error_message.str();
  }
	
  // Try and recursively get the imaginary part
  try {
    read(xml, path_real, result.imag());
  }
  catch(const string &e) {
    error_message << "XPath Query: " << xpath <<" Error:"
		  <<"Failed to match imaginary part of RComplex Object with self constructed path: " << path_imag;
    
    throw error_message.str();
  }
}
#endif  // NOT IMPLEMENTED


/*! @} */   // end of group ilattice


//-----------------------------------------------------------------------------
// Traits classes to support operations of simple scalars (floating constants, 
// etc.) on QDPTypes
//-----------------------------------------------------------------------------

template<class T>
struct WordType<IScalar<T> > 
{
  typedef typename WordType<T>::Type_t  Type_t;
};

template<class T, int N>
struct WordType<ILattice<T,N> > 
{
  typedef typename WordType<T>::Type_t  Type_t;
};


// Internally used scalars
template<class T>
struct InternalScalar<IScalar<T> > {
  typedef IScalar<typename InternalScalar<T>::Type_t>  Type_t;
};

template<class T, int N>
struct InternalScalar<ILattice<T,N> > {
  typedef IScalar<typename InternalScalar<T>::Type_t>  Type_t;
};


// Internally used real scalars
template<class T>
struct RealScalar<IScalar<T> > {
  typedef IScalar<typename RealScalar<T>::Type_t>  Type_t;
};

template<class T, int N>
struct RealScalar<ILattice<T,N> > {
  typedef IScalar<typename RealScalar<T>::Type_t>  Type_t;
};



//-----------------------------------------------------------------------------
// Traits classes to support return types
//-----------------------------------------------------------------------------

// Default unary(IScalar) -> IScalar
template<class T1, class Op>
struct UnaryReturn<IScalar<T1>, Op> {
  typedef IScalar<typename UnaryReturn<T1, Op>::Type_t>  Type_t;
};

// Default unary(ILattice) -> ILattice
template<class T1, int N, class Op>
struct UnaryReturn<ILattice<T1,N>, Op> {
  typedef ILattice<typename UnaryReturn<T1, Op>::Type_t, N>  Type_t;
};

// Default binary(IScalar,IScalar) -> IScalar
template<class T1, class T2, class Op>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, Op> {
  typedef IScalar<typename BinaryReturn<T1, T2, Op>::Type_t>  Type_t;
};

// Currently, the only trinary operator is ``where'', so return 
// based on T2 and T3
// Default trinary(IScalar,IScalar,IScalar) -> IScalar
template<class T1, class T2, class T3, class Op>
struct TrinaryReturn<IScalar<T1>, IScalar<T2>, IScalar<T3>, Op> {
  typedef IScalar<typename BinaryReturn<T2, T3, Op>::Type_t>  Type_t;
};

// Default binary(ILattice,ILattice) -> ILattice
template<class T1, class T2, int N, class Op>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, Op> {
  typedef ILattice<typename BinaryReturn<T1, T2, Op>::Type_t, N>  Type_t;
};

// Default binary(IScalar,ILattice) -> ILattice
template<class T1, class T2, int N, class Op>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, Op> {
  typedef ILattice<typename BinaryReturn<T1, T2, Op>::Type_t, N>  Type_t;
};

// Default binary(ILattice,IScalar) -> ILattice
template<class T1, class T2, int N, class Op>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, Op> {
  typedef ILattice<typename BinaryReturn<T1, T2, Op>::Type_t, N>  Type_t;
};


// Currently, the only trinary operator is ``where'', so return 
// based on T2 and T3

// Default trinary(ILattice,ILattice,ILattice) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<ILattice<T1,N>, ILattice<T2,N>, ILattice<T3,N>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};


// Default trinary(ILattice,IScalar,ILattice) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<ILattice<T1,N>, IScalar<T2>, ILattice<T3,N>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};

// Default trinary(ILattice,ILattice,IScalar) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<ILattice<T1,N>, ILattice<T2,N>, IScalar<T3>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};

// Default trinary(IScalar,ILattice,ILattice) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<IScalar<T1>, ILattice<T2,N>, ILattice<T3,N>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};


// Default trinary(IScalar,IScalar,ILattice) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<IScalar<T1>, IScalar<T2>, ILattice<T3,N>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};

// Default trinary(OSscalar,ILattice,IScalar) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<IScalar<T1>, ILattice<T2,N>, IScalar<T3>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};

// Default trinary(ILattice,IScalar,IScalar) -> ILattice
template<class T1, class T2, class T3, int N, class Op>
struct TrinaryReturn<ILattice<T1,N>, IScalar<T2>, IScalar<T3>, Op> {
  typedef ILattice<typename BinaryReturn<T2, T3, Op>::Type_t, N>  Type_t;
};




// Specific IScalar cases
// Global operations
template<class T>
struct UnaryReturn<IScalar<T>, FnSum > {
  typedef IScalar<typename UnaryReturn<T, FnSum>::Type_t>  Type_t;
};

template<class T>
struct UnaryReturn<IScalar<T>, FnSumMulti > {
  typedef IScalar<typename UnaryReturn<T, FnSumMulti>::Type_t>  Type_t;
};


// Gamma algebra
template<int N, int m, class T2, class OpGammaConstMultiply>
struct BinaryReturn<GammaConst<N,m>, IScalar<T2>, OpGammaConstMultiply> {
  typedef IScalar<typename UnaryReturn<T2, OpUnaryPlus>::Type_t>  Type_t;
};

template<class T2, int N, int m, class OpMultiplyGammaConst>
struct BinaryReturn<IScalar<T2>, GammaConst<N,m>, OpMultiplyGammaConst> {
  typedef IScalar<typename UnaryReturn<T2, OpUnaryPlus>::Type_t>  Type_t;
};

template<class T2, int N, class OpGammaTypeMultiply>
struct BinaryReturn<GammaType<N>, IScalar<T2>, OpGammaTypeMultiply> {
  typedef IScalar<typename UnaryReturn<T2, OpUnaryPlus>::Type_t>  Type_t;
};

template<class T2, int N, class OpMultiplyGammaType>
struct BinaryReturn<IScalar<T2>, GammaType<N>, OpMultiplyGammaType> {
  typedef IScalar<typename UnaryReturn<T2, OpUnaryPlus>::Type_t>  Type_t;
};



// Local operations

#if 0
template<class T1, class T2>
struct UnaryReturn<IScalar<T2>, OpCast<T1> > {
  typedef IScalar<typename UnaryReturn<T, OpCast>::Type_t>  Type_t;
//  typedef T1 Type_t;
};
#endif
 

template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpAddAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpAddAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpSubtractAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpSubtractAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpMultiplyAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpMultiplyAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpDivideAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpDivideAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpModAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpModAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseOrAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpBitwiseOrAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseAndAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpBitwiseAndAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseXorAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpBitwiseXorAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpLeftShiftAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpLeftShiftAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpRightShiftAssign > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpRightShiftAssign>::Type_t>  &Type_t;
};
 
template<class T1, class T2, class T3>
struct TrinaryReturn<IScalar<T1>, IScalar<T2>, IScalar<T3>, FnColorContract> {
  typedef IScalar<typename TrinaryReturn<T1, T2, T3, FnColorContract>::Type_t>  Type_t;
};

// Specific ILattice cases
// Global operations
template<class T, int N>
struct UnaryReturn<ILattice<T,N>, FnSum > {
  typedef IScalar<typename UnaryReturn<T, FnSum>::Type_t>  Type_t;
};

template<class T, int N>
struct UnaryReturn<ILattice<T,N>, FnSumMulti > {
  typedef multi1d<IScalar<typename UnaryReturn<T, FnSumMulti>::Type_t> >  Type_t;
};

template<class T, int N>
struct UnaryReturn<ILattice<T,N>, FnNorm2 > {
  typedef IScalar<typename UnaryReturn<T, FnNorm2>::Type_t>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, FnInnerProduct > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProduct>::Type_t>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, FnInnerProductReal > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProductReal>::Type_t>  Type_t;
};

template<class T, int N>
struct UnaryReturn<ILattice<T,N>, FnLocalNorm2 > {
  typedef ILattice<typename UnaryReturn<T, FnLocalNorm2>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, FnLocalInnerProduct > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProduct>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, FnLocalInnerProductReal > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProductReal>::Type_t, N>  Type_t;
};


// Gamma algebra
template<int M, int m, class T2, class OpGammaConstMultiply>
struct BinaryReturn<GammaConst<M,m>, ILattice<T2,N>, OpGammaConstMultiply> {
  typedef ILattice<typename UnaryReturn<T2, OpUnaryPlus>::Type_t, N>  Type_t;
};

template<class T2, int M, int m, class OpMultiplyGammaConst>
struct BinaryReturn<ILattice<T2,N>, GammaConst<M,m>, OpMultiplyGammaConst> {
  typedef ILattice<typename UnaryReturn<T2, OpUnaryPlus>::Type_t, N>  Type_t;
};

template<int M, class T2, int N, class OpGammaTypeMultiply>
struct BinaryReturn<GammaType<M>, ILattice<T2,N>, OpGammaTypeMultiply> {
  typedef ILattice<typename UnaryReturn<T2, OpUnaryPlus>::Type_t, N>  Type_t;
};

template<class T2, int N, int M, class OpMultiplyGammaType>
struct BinaryReturn<ILattice<T2,N>, GammaType<M>, OpMultiplyGammaType> {
  typedef ILattice<typename UnaryReturn<T2, OpUnaryPlus>::Type_t, N>  Type_t;
};



// Local operations
template<class T, int N>
struct UnaryReturn<ILattice<T,N>, OpNot > {
  typedef ILattice<typename UnaryReturn<T, OpNot>::Type_t, N>  Type_t;
};


#if 0
template<class T1, class T2, int N>
struct UnaryReturn<ILattice<T2,N>, OpCast<T1> > {
  typedef ILattice<typename UnaryReturn<T, OpCast>::Type_t, N>  Type_t;
//  typedef T1 Type_t;
};
#endif

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpLT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpLE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpGT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpGE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpEQ > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpEQ>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpNE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpNE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpAnd > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpAnd>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpOr > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpOr>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpLeftShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLeftShift>::Type_t, N>  Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpRightShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpRightShift>::Type_t, N>  Type_t;
};
 

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpAddAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpAddAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpSubtractAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpSubtractAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpMultiplyAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpMultiplyAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpDivideAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpDivideAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpModAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpModAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpBitwiseOrAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseOrAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpBitwiseAndAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseAndAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpBitwiseXorAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseXorAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpLeftShiftAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLeftShiftAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, ILattice<T2,N>, OpRightShiftAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpRightShiftAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, class T3, int N>
struct TrinaryReturn<ILattice<T1,N>, ILattice<T2,N>, ILattice<T3,N>, FnColorContract> {
  typedef ILattice<typename TrinaryReturn<T1, T2, T3, FnColorContract>::Type_t, N>  Type_t;
};


// Mixed ILattice & IScalar cases
// Global operations
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, FnInnerProduct > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProduct>::Type_t>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, FnInnerProductReal > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProductReal>::Type_t>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, FnInnerProduct > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProduct>::Type_t>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, FnInnerProductReal > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProductReal>::Type_t>  Type_t;
};


template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, FnLocalInnerProduct > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProduct>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, FnLocalInnerProductReal > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProductReal>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, FnLocalInnerProduct > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProduct>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, FnLocalInnerProductReal > {
  typedef ILattice<typename BinaryReturn<T1, T2, FnLocalInnerProductReal>::Type_t, N>  Type_t;
};


// Local operations
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpLT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpLE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpGT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpGE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpEQ > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpEQ>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpNE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpNE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpAnd > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpAnd>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpOr > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpOr>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpLeftShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLeftShift>::Type_t, N>  Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpRightShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpRightShift>::Type_t, N>  Type_t;
};
 

template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpAddAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpAddAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpSubtractAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpSubtractAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpMultiplyAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpMultiplyAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpDivideAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpDivideAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpModAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpModAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpBitwiseOrAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseOrAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpBitwiseAndAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseAndAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpBitwiseXorAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpBitwiseXorAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpLeftShiftAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLeftShiftAssign>::Type_t, N>  &Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<ILattice<T1,N>, IScalar<T2>, OpRightShiftAssign > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpRightShiftAssign>::Type_t, N>  &Type_t;
};
 

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpLT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpLE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpGT > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGT>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpGE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpGE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpEQ > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpEQ>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpNE > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpNE>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpAnd > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpAnd>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpOr > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpOr>::Type_t, N>  Type_t;
};

template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpLeftShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpLeftShift>::Type_t, N>  Type_t;
};
 
template<class T1, class T2, int N>
struct BinaryReturn<IScalar<T1>, ILattice<T2,N>, OpRightShift > {
  typedef ILattice<typename BinaryReturn<T1, T2, OpRightShift>::Type_t, N>  Type_t;
};
 



//-----------------------------------------------------------------------------
// Scalar Operations
//-----------------------------------------------------------------------------

/*! \addtogroup iscalar */
/*! @{ */

// Inner grid scalar
template<class T>
struct UnaryReturn<IScalar<T>, OpNot > {
  typedef IScalar<typename UnaryReturn<T, OpNot>::Type_t>  Type_t;
};

template<class T1>
inline typename UnaryReturn<IScalar<T1>, OpNot>::Type_t
operator!(const IScalar<T1>& l)
{
  return ! l.elem();
}


template<class T1>
inline typename UnaryReturn<IScalar<T1>, OpUnaryPlus>::Type_t
operator+(const IScalar<T1>& l)
{
  return +l.elem();
}


template<class T1>
inline typename UnaryReturn<IScalar<T1>, OpUnaryMinus>::Type_t
operator-(const IScalar<T1>& l)
{
  return -l.elem();
}


template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpAdd>::Type_t
operator+(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem()+r.elem();
}


template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpSubtract>::Type_t
operator-(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() - r.elem();
}


template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpMultiply>::Type_t
operator*(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() * r.elem();
}

// Optimized  adj(IScalar)*IScalar
template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpAdjMultiply>::Type_t
adjMultiply(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return transpose(l.elem()) * r.elem();
}

// Optimized  IScalar*adj(IScalar)
template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpMultiplyAdj>::Type_t
multiplyAdj(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() * transpose(r.elem());
}

// Optimized  adj(IScalar)*adj(IScalar)
template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpAdjMultiplyAdj>::Type_t
adjMultiplyAdj(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return transpose(l.elem()) * transpose(r.elem());
}


template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpDivide>::Type_t
operator/(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() / r.elem();
}



template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpLeftShift > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpLeftShift>::Type_t>  Type_t;
};
 

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpLeftShift>::Type_t
operator<<(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() << r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpRightShift > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpRightShift>::Type_t>  Type_t;
};
 

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpRightShift>::Type_t
operator>>(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() >> r.elem();
}


template<class T1, class T2 >
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpMod>::Type_t
operator%(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() % r.elem();
}

template<class T1, class T2 >
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseXor>::Type_t
operator^(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() ^ r.elem();
}

template<class T1, class T2 >
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseAnd>::Type_t
operator&(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() & r.elem();
}

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpBitwiseOr>::Type_t
operator|(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() | r.elem();
}



// Comparisons
template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpLT > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpLT>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpLT>::Type_t
operator<(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() < r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpLE > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpLE>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpLE>::Type_t
operator<=(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() <= r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpGT > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpGT>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpGT>::Type_t
operator>(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() > r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpGE > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpGE>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpGE>::Type_t
operator>=(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() >= r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpEQ > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpEQ>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpEQ>::Type_t
operator==(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() == r.elem();
}


template<class T1, class T2 >
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpNE > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpNE>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpNE>::Type_t
operator!=(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() != r.elem();
}


template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpAnd > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpAnd>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpAnd>::Type_t
operator&&(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() && r.elem();
}


template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, OpOr > {
  typedef IScalar<typename BinaryReturn<T1, T2, OpOr>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, OpOr>::Type_t
operator||(const IScalar<T1>& l, const IScalar<T2>& r)
{
  return l.elem() || r.elem();
}



//-----------------------------------------------------------------------------
// Functions

// Adjoint
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnAdjoint>::Type_t
adj(const IScalar<T1>& s1)
{
  return transpose(s1.elem()); // The complex nature has been eaten here
}


// Conjugate
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnConjugate>::Type_t
conj(const IScalar<T1>& s1)
{
  return s1.elem();  // The complex nature has been eaten here
}


// Transpose
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnTranspose>::Type_t
transpose(const IScalar<T1>& s1)
{
  return transpose(s1.elem());
}



// TRACE
// trace = Trace(source1)
template<class T>
struct UnaryReturn<IScalar<T>, FnTrace > {
  typedef IScalar<typename UnaryReturn<T, FnTrace>::Type_t>  Type_t;
};

template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnTrace>::Type_t
trace(const IScalar<T1>& s1)
{
  return trace(s1.elem());
}


// trace = Re(Trace(source1))
template<class T>
struct UnaryReturn<IScalar<T>, FnRealTrace > {
  typedef IScalar<typename UnaryReturn<T, FnRealTrace>::Type_t>  Type_t;
};

template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnRealTrace>::Type_t
trace_real(const IScalar<T1>& s1)
{
  return trace_real(s1.elem());
}


// trace = Im(Trace(source1))
template<class T>
struct UnaryReturn<IScalar<T>, FnImagTrace > {
  typedef IScalar<typename UnaryReturn<T, FnImagTrace>::Type_t>  Type_t;
};

template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnImagTrace>::Type_t
trace_imag(const IScalar<T1>& s1)
{
  return trace_imag(s1.elem());
}


// IScalar = Re(IScalar)  [identity]
template<class T>
inline typename UnaryReturn<IScalar<T>, FnReal>::Type_t
real(const IScalar<T>& s1)
{
  return s1.elem();
}


// IScalar = Im(IScalar) [this is zero]
template<class T>
inline typename UnaryReturn<IScalar<T>, FnImag>::Type_t
imag(const IScalar<T>& s1)
{
  zero_rep(d.elem());
}


// ArcCos
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnArcCos>::Type_t
acos(const IScalar<T1>& s1)
{
  return acos(s1.elem());
}

// ArcSin
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnArcSin>::Type_t
asin(const IScalar<T1>& s1)
{
  return asin(s1.elem());
}

// ArcTan
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnArcTan>::Type_t
atan(const IScalar<T1>& s1)
{
  return atan(s1.elem());
}

// Cos
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnCos>::Type_t
cos(const IScalar<T1>& s1)
{
  return cos(s1.elem());
}

// Exp
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnExp>::Type_t
exp(const IScalar<T1>& s1)
{
  return exp(s1.elem());
}

// Fabs
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnFabs>::Type_t
fabs(const IScalar<T1>& s1)
{
  return fabs(s1.elem());
}

// Log
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnLog>::Type_t
log(const IScalar<T1>& s1)
{
  return log(s1.elem());
}

// Sin
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnSin>::Type_t
sin(const IScalar<T1>& s1)
{
  return sin(s1.elem());
}

// Sqrt
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnSqrt>::Type_t
sqrt(const IScalar<T1>& s1)
{
  return sqrt(s1.elem());
}

// Tan
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnTan>::Type_t
tan(const IScalar<T1>& s1)
{
  return tan(s1.elem());
}

//! IScalar<T> = pow(IScalar<T> , IScalar<T>)
template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, FnPow>::Type_t
pow(const IScalar<T1>& s1, const IScalar<T2>& s2)
{
  return pow(s1.elem(), s2.elem());
}

//! IScalar<T> = atan2(IScalar<T> , IScalar<T>)
template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, FnArcTan2>::Type_t
atan2(const IScalar<T1>& s1, const IScalar<T2>& s2)
{
  return atan2(s1.elem(), s2.elem());
}



//! dest [float type] = source [seed type]
template<class T1>
inline typename UnaryReturn<IScalar<T1>, FnSeedToFloat>::Type_t
seedToFloat(const IScalar<T1>& s1)
{
  return seedToFloat(s1.elem());
}

//! Extract color vector components 
/*! Generically, this is an identity operation. Defined differently under color */
template<class T>
inline typename UnaryReturn<IScalar<T>, FnPeekColorVector>::Type_t
peekColor(const IScalar<T>& l, int row)
{
  return peekColor(l.elem(),row);
}

//! Extract color matrix components 
/*! Generically, this is an identity operation. Defined differently under color */
template<class T>
inline typename UnaryReturn<IScalar<T>, FnPeekColorMatrix>::Type_t
peekColor(const IScalar<T>& l, int row, int col)
{
  return peekColor(l.elem(),row,col);
}

//! Extract spin vector components 
/*! Generically, this is an identity operation. Defined differently under spin */
template<class T>
inline typename UnaryReturn<IScalar<T>, FnPeekSpinVector>::Type_t
peekSpin(const IScalar<T>& l, int row)
{
  return peekSpin(l.elem(),row);
}

//! Extract spin matrix components 
/*! Generically, this is an identity operation. Defined differently under spin */
template<class T>
inline typename UnaryReturn<IScalar<T>, FnPeekSpinMatrix>::Type_t
peekSpin(const IScalar<T>& l, int row, int col)
{
  return peekSpin(l.elem(),row,col);
}


//-----------------------------------------------------------------------------
//! QDP Int to int primitive in conversion routine
template<class T> 
inline int 
toInt(const IScalar<T>& s) 
{
  return toInt(s.elem());
}

//! QDP Real to float primitive in conversion routine
template<class T> 
inline float
toFloat(const IScalar<T>& s) 
{
  return toFloat(s.elem());
}

//! QDP Double to double primitive in conversion routine
template<class T> 
inline double
toDouble(const IScalar<T>& s) 
{
  return toDouble(s.elem());
}

//! QDP Boolean to bool primitive in conversion routine
template<class T> 
inline bool
toBool(const IScalar<T>& s) 
{
  return toBool(s.elem());
}


//------------------------------------------
//! dest = (mask) ? s1 : dest
template<class T, class T1> 
inline
void copymask(IScalar<T>& d, const IScalar<T1>& mask, const IScalar<T>& s1) 
{
  copymask(d.elem(),mask.elem(),s1.elem());
}

//! dest [float type] = source [int type]
template<class T, class T1>
inline
void cast_rep(T& d, const IScalar<T1>& s1)
{
  cast_rep(d, s1.elem());
}


//! dest [float type] = source [int type]
template<class T, class T1>
inline
void recast_rep(IScalar<T>& d, const IScalar<T1>& s1)
{
  cast_rep(d.elem(), s1.elem());
}


//------------------------------------------
// InnerProduct (norm-seq) global sum = sum(tr(adj(s1)*s1))
template<class T>
struct UnaryReturn<IScalar<T>, FnNorm2 > {
  typedef IScalar<typename UnaryReturn<T, FnNorm2>::Type_t>  Type_t;
};

template<class T>
struct UnaryReturn<IScalar<T>, FnLocalNorm2 > {
  typedef IScalar<typename UnaryReturn<T, FnLocalNorm2>::Type_t>  Type_t;
};

template<class T>
inline typename UnaryReturn<IScalar<T>, FnLocalNorm2>::Type_t
localNorm2(const IScalar<T>& s1)
{
  return localNorm2(s1.elem());
}



//! IScalar<T> = InnerProduct(adj(IScalar<T1>)*IScalar<T2>)
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, FnInnerProduct > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProduct>::Type_t>  Type_t;
};

template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, FnLocalInnerProduct > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnLocalInnerProduct>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, FnLocalInnerProduct>::Type_t
localInnerProduct(const IScalar<T1>& s1, const IScalar<T2>& s2)
{
  return localInnerProduct(s1.elem(), s2.elem());
}


//! IScalar<T> = InnerProductReal(adj(PMatrix<T1>)*PMatrix<T1>)
template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, FnInnerProductReal > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnInnerProductReal>::Type_t>  Type_t;
};

template<class T1, class T2>
struct BinaryReturn<IScalar<T1>, IScalar<T2>, FnLocalInnerProductReal > {
  typedef IScalar<typename BinaryReturn<T1, T2, FnLocalInnerProductReal>::Type_t>  Type_t;
};

template<class T1, class T2>
inline typename BinaryReturn<IScalar<T1>, IScalar<T2>, FnLocalInnerProductReal>::Type_t
localInnerProductReal(const IScalar<T1>& s1, const IScalar<T2>& s2)
{
  return localInnerProductReal(s1.elem(), s2.elem());
}


//! IScalar<T> = where(IScalar, IScalar, IScalar)
/*!
 * Where is the ? operation
 * returns  (a) ? b : c;
 */
template<class T1, class T2, class T3>
inline typename BinaryReturn<IScalar<T2>, IScalar<T3>, FnWhere>::Type_t
where(const IScalar<T1>& a, const IScalar<T2>& b, const IScalar<T3>& c)
{
  return where(a.elem(), b.elem(), c.elem());
}



//-----------------------------------------------------------------------------
// Broadcast operations
//! dest = 0
template<class T> 
inline
void zero_rep(IScalar<T>& dest) 
{
  zero_rep(dest.elem());
}


//-----------------------------------------------------------------------------
// Random numbers
//! dest  = random  
template<class T, class T1, class T2>
inline void
fill_random(IScalar<T>& d, T1& seed, T2& skewed_seed, const T1& seed_mult)
{
  fill_random(d.elem(), seed, skewed_seed, seed_mult);
}


//! dest  = gaussian  
template<class T>
inline void
fill_gaussian(IScalar<T>& d, IScalar<T>& r1, IScalar<T>& r2)
{
  fill_gaussian(d.elem(), r1.elem(), r2.elem());
}


/*! @} */  // end of group iscalar

QDP_END_NAMESPACE();
