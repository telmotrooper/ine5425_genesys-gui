// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file ../GenesysParser.h
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_GENESYSPARSER_H_INCLUDED
# define YY_YY_GENESYSPARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 9 "bisonparser.yy" // lalr1.cc:377

#include <string>
#include <cmath>
#include "obj_t.h"
#include "../Util.h"
//
// include to Plugin header files should be specified by plugins themselves
//
#include "../Variable.h"
#include "../Queue.h"
#include "../Formula.h"
#include "../Resource.h"
#include "../Set.h"
class genesyspp_driver;


#line 61 "../GenesysParser.h" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 138 "../GenesysParser.h" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class genesyspp_parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // NUMD
      // NUMH
      // CTEZERO
      // oLE
      // oGE
      // oEQ
      // oNE
      // oAND
      // oOR
      // oNOT
      // fSIN
      // fCOS
      // fROUND
      // fMOD
      // fTRUNC
      // fFRAC
      // fEXPO
      // fNORM
      // fUNIF
      // fWEIB
      // fLOGN
      // fGAMM
      // fERLA
      // fTRIA
      // fBETA
      // fDISC
      // fTNOW
      // fTFIN
      // cIF
      // cELSE
      // cFOR
      // cTO
      // cDO
      // ATRIB
      // ILLEGAL
      // RESOURCE
      // fNR
      // fMR
      // fIRF
      // fRESSEIZES
      // fSTATE
      // fSETSUM
      // QUEUE
      // fNQ
      // fFIRSTINQ
      // fLASTINQ
      // fSAQUE
      // fAQUE
      // SET
      // fNUMSET
      // CSTAT
      // fTAVG
      // VARI
      // FORM
      // input
      // programa
      // expressao
      // numero
      // aritmetica
      // relacional
      // comando
      // comandoIF
      // comandoFOR
      // funcao
      // funcaoKernel
      // funcaoTrig
      // funcaoArit
      // funcaoProb
      // funcaoUser
      // listaparm
      // illegal
      // atributo
      // atribuicao
      // variavel
      // formula
      // funcaoPlugin
      char dummy1[sizeof(obj_t)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        NUMD = 258,
        NUMH = 259,
        CTEZERO = 260,
        oLE = 261,
        oGE = 262,
        oEQ = 263,
        oNE = 264,
        oAND = 265,
        oOR = 266,
        oNOT = 267,
        fSIN = 268,
        fCOS = 269,
        fROUND = 270,
        fMOD = 271,
        fTRUNC = 272,
        fFRAC = 273,
        fEXPO = 274,
        fNORM = 275,
        fUNIF = 276,
        fWEIB = 277,
        fLOGN = 278,
        fGAMM = 279,
        fERLA = 280,
        fTRIA = 281,
        fBETA = 282,
        fDISC = 283,
        fTNOW = 284,
        fTFIN = 285,
        cIF = 286,
        cELSE = 287,
        cFOR = 288,
        cTO = 289,
        cDO = 290,
        ATRIB = 291,
        ILLEGAL = 292,
        RESOURCE = 293,
        fNR = 294,
        fMR = 295,
        fIRF = 296,
        fRESSEIZES = 297,
        fSTATE = 298,
        fSETSUM = 299,
        QUEUE = 300,
        fNQ = 301,
        fFIRSTINQ = 302,
        fLASTINQ = 303,
        fSAQUE = 304,
        fAQUE = 305,
        SET = 306,
        fNUMSET = 307,
        CSTAT = 308,
        fTAVG = 309,
        VARI = 310,
        FORM = 311,
        LPAREN = 312,
        RPAREN = 313,
        PLUS = 314,
        MINUS = 315,
        STAR = 316,
        POWER = 317,
        SLASH = 318,
        LESS = 319,
        GREATER = 320,
        ASSIGN = 321,
        COMMA = 322,
        NEG = 323
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const obj_t v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_NUMD (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_NUMH (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_CTEZERO (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oLE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oGE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oEQ (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oNE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oAND (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oOR (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_oNOT (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fSIN (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fCOS (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fROUND (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fMOD (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fTRUNC (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fFRAC (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fEXPO (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fNORM (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fUNIF (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fWEIB (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fLOGN (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fGAMM (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fERLA (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fTRIA (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fBETA (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fDISC (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fTNOW (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fTFIN (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_cIF (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_cELSE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_cFOR (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_cTO (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_cDO (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_ATRIB (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_ILLEGAL (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_RESOURCE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fNR (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fMR (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fIRF (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fRESSEIZES (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fSTATE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fSETSUM (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_QUEUE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fNQ (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fFIRSTINQ (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fLASTINQ (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fSAQUE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fAQUE (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_SET (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fNUMSET (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_CSTAT (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_fTAVG (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_VARI (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_FORM (const obj_t& v, const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_STAR (const location_type& l);

    static inline
    symbol_type
    make_POWER (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_LESS (const location_type& l);

    static inline
    symbol_type
    make_GREATER (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_NEG (const location_type& l);


    /// Build a parser object.
    genesyspp_parser (genesyspp_driver& driver_yyarg);
    virtual ~genesyspp_parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    genesyspp_parser (const genesyspp_parser&);
    genesyspp_parser& operator= (const genesyspp_parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1074,     ///< Last index in yytable_.
      yynnts_ = 23,  ///< Number of nonterminal symbols.
      yyfinal_ = 6, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 73  ///< Number of tokens.
    };


    // User arguments.
    genesyspp_driver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
  genesyspp_parser::token_number_type
  genesyspp_parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      69,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    70,    71,    72
    };
    const unsigned int user_token_number_max_ = 326;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  genesyspp_parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  genesyspp_parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  genesyspp_parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 3: // NUMD
      case 4: // NUMH
      case 5: // CTEZERO
      case 6: // oLE
      case 7: // oGE
      case 8: // oEQ
      case 9: // oNE
      case 10: // oAND
      case 11: // oOR
      case 12: // oNOT
      case 13: // fSIN
      case 14: // fCOS
      case 15: // fROUND
      case 16: // fMOD
      case 17: // fTRUNC
      case 18: // fFRAC
      case 19: // fEXPO
      case 20: // fNORM
      case 21: // fUNIF
      case 22: // fWEIB
      case 23: // fLOGN
      case 24: // fGAMM
      case 25: // fERLA
      case 26: // fTRIA
      case 27: // fBETA
      case 28: // fDISC
      case 29: // fTNOW
      case 30: // fTFIN
      case 31: // cIF
      case 32: // cELSE
      case 33: // cFOR
      case 34: // cTO
      case 35: // cDO
      case 36: // ATRIB
      case 37: // ILLEGAL
      case 38: // RESOURCE
      case 39: // fNR
      case 40: // fMR
      case 41: // fIRF
      case 42: // fRESSEIZES
      case 43: // fSTATE
      case 44: // fSETSUM
      case 45: // QUEUE
      case 46: // fNQ
      case 47: // fFIRSTINQ
      case 48: // fLASTINQ
      case 49: // fSAQUE
      case 50: // fAQUE
      case 51: // SET
      case 52: // fNUMSET
      case 53: // CSTAT
      case 54: // fTAVG
      case 55: // VARI
      case 56: // FORM
      case 74: // input
      case 75: // programa
      case 76: // expressao
      case 77: // numero
      case 78: // aritmetica
      case 79: // relacional
      case 80: // comando
      case 81: // comandoIF
      case 82: // comandoFOR
      case 83: // funcao
      case 84: // funcaoKernel
      case 85: // funcaoTrig
      case 86: // funcaoArit
      case 87: // funcaoProb
      case 88: // funcaoUser
      case 89: // listaparm
      case 90: // illegal
      case 91: // atributo
      case 92: // atribuicao
      case 93: // variavel
      case 94: // formula
      case 95: // funcaoPlugin
        value.copy< obj_t > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  genesyspp_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 3: // NUMD
      case 4: // NUMH
      case 5: // CTEZERO
      case 6: // oLE
      case 7: // oGE
      case 8: // oEQ
      case 9: // oNE
      case 10: // oAND
      case 11: // oOR
      case 12: // oNOT
      case 13: // fSIN
      case 14: // fCOS
      case 15: // fROUND
      case 16: // fMOD
      case 17: // fTRUNC
      case 18: // fFRAC
      case 19: // fEXPO
      case 20: // fNORM
      case 21: // fUNIF
      case 22: // fWEIB
      case 23: // fLOGN
      case 24: // fGAMM
      case 25: // fERLA
      case 26: // fTRIA
      case 27: // fBETA
      case 28: // fDISC
      case 29: // fTNOW
      case 30: // fTFIN
      case 31: // cIF
      case 32: // cELSE
      case 33: // cFOR
      case 34: // cTO
      case 35: // cDO
      case 36: // ATRIB
      case 37: // ILLEGAL
      case 38: // RESOURCE
      case 39: // fNR
      case 40: // fMR
      case 41: // fIRF
      case 42: // fRESSEIZES
      case 43: // fSTATE
      case 44: // fSETSUM
      case 45: // QUEUE
      case 46: // fNQ
      case 47: // fFIRSTINQ
      case 48: // fLASTINQ
      case 49: // fSAQUE
      case 50: // fAQUE
      case 51: // SET
      case 52: // fNUMSET
      case 53: // CSTAT
      case 54: // fTAVG
      case 55: // VARI
      case 56: // FORM
      case 74: // input
      case 75: // programa
      case 76: // expressao
      case 77: // numero
      case 78: // aritmetica
      case 79: // relacional
      case 80: // comando
      case 81: // comandoIF
      case 82: // comandoFOR
      case 83: // funcao
      case 84: // funcaoKernel
      case 85: // funcaoTrig
      case 86: // funcaoArit
      case 87: // funcaoProb
      case 88: // funcaoUser
      case 89: // listaparm
      case 90: // illegal
      case 91: // atributo
      case 92: // atribuicao
      case 93: // variavel
      case 94: // formula
      case 95: // funcaoPlugin
        value.copy< obj_t > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  genesyspp_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  genesyspp_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const obj_t v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  genesyspp_parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  genesyspp_parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 3: // NUMD
      case 4: // NUMH
      case 5: // CTEZERO
      case 6: // oLE
      case 7: // oGE
      case 8: // oEQ
      case 9: // oNE
      case 10: // oAND
      case 11: // oOR
      case 12: // oNOT
      case 13: // fSIN
      case 14: // fCOS
      case 15: // fROUND
      case 16: // fMOD
      case 17: // fTRUNC
      case 18: // fFRAC
      case 19: // fEXPO
      case 20: // fNORM
      case 21: // fUNIF
      case 22: // fWEIB
      case 23: // fLOGN
      case 24: // fGAMM
      case 25: // fERLA
      case 26: // fTRIA
      case 27: // fBETA
      case 28: // fDISC
      case 29: // fTNOW
      case 30: // fTFIN
      case 31: // cIF
      case 32: // cELSE
      case 33: // cFOR
      case 34: // cTO
      case 35: // cDO
      case 36: // ATRIB
      case 37: // ILLEGAL
      case 38: // RESOURCE
      case 39: // fNR
      case 40: // fMR
      case 41: // fIRF
      case 42: // fRESSEIZES
      case 43: // fSTATE
      case 44: // fSETSUM
      case 45: // QUEUE
      case 46: // fNQ
      case 47: // fFIRSTINQ
      case 48: // fLASTINQ
      case 49: // fSAQUE
      case 50: // fAQUE
      case 51: // SET
      case 52: // fNUMSET
      case 53: // CSTAT
      case 54: // fTAVG
      case 55: // VARI
      case 56: // FORM
      case 74: // input
      case 75: // programa
      case 76: // expressao
      case 77: // numero
      case 78: // aritmetica
      case 79: // relacional
      case 80: // comando
      case 81: // comandoIF
      case 82: // comandoFOR
      case 83: // funcao
      case 84: // funcaoKernel
      case 85: // funcaoTrig
      case 86: // funcaoArit
      case 87: // funcaoProb
      case 88: // funcaoUser
      case 89: // listaparm
      case 90: // illegal
      case 91: // atributo
      case 92: // atribuicao
      case 93: // variavel
      case 94: // formula
      case 95: // funcaoPlugin
        value.template destroy< obj_t > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  genesyspp_parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  genesyspp_parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 3: // NUMD
      case 4: // NUMH
      case 5: // CTEZERO
      case 6: // oLE
      case 7: // oGE
      case 8: // oEQ
      case 9: // oNE
      case 10: // oAND
      case 11: // oOR
      case 12: // oNOT
      case 13: // fSIN
      case 14: // fCOS
      case 15: // fROUND
      case 16: // fMOD
      case 17: // fTRUNC
      case 18: // fFRAC
      case 19: // fEXPO
      case 20: // fNORM
      case 21: // fUNIF
      case 22: // fWEIB
      case 23: // fLOGN
      case 24: // fGAMM
      case 25: // fERLA
      case 26: // fTRIA
      case 27: // fBETA
      case 28: // fDISC
      case 29: // fTNOW
      case 30: // fTFIN
      case 31: // cIF
      case 32: // cELSE
      case 33: // cFOR
      case 34: // cTO
      case 35: // cDO
      case 36: // ATRIB
      case 37: // ILLEGAL
      case 38: // RESOURCE
      case 39: // fNR
      case 40: // fMR
      case 41: // fIRF
      case 42: // fRESSEIZES
      case 43: // fSTATE
      case 44: // fSETSUM
      case 45: // QUEUE
      case 46: // fNQ
      case 47: // fFIRSTINQ
      case 48: // fLASTINQ
      case 49: // fSAQUE
      case 50: // fAQUE
      case 51: // SET
      case 52: // fNUMSET
      case 53: // CSTAT
      case 54: // fTAVG
      case 55: // VARI
      case 56: // FORM
      case 74: // input
      case 75: // programa
      case 76: // expressao
      case 77: // numero
      case 78: // aritmetica
      case 79: // relacional
      case 80: // comando
      case 81: // comandoIF
      case 82: // comandoFOR
      case 83: // funcao
      case 84: // funcaoKernel
      case 85: // funcaoTrig
      case 86: // funcaoArit
      case 87: // funcaoProb
      case 88: // funcaoUser
      case 89: // listaparm
      case 90: // illegal
      case 91: // atributo
      case 92: // atribuicao
      case 93: // variavel
      case 94: // formula
      case 95: // funcaoPlugin
        value.move< obj_t > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  genesyspp_parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  genesyspp_parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  genesyspp_parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  genesyspp_parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  genesyspp_parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  genesyspp_parser::by_type::type_get () const
  {
    return type;
  }

  inline
  genesyspp_parser::token_type
  genesyspp_parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    10,
     324,   325,   326
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  genesyspp_parser::symbol_type
  genesyspp_parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_NUMD (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::NUMD, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_NUMH (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::NUMH, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_CTEZERO (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::CTEZERO, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oLE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oLE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oGE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oGE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oEQ (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oEQ, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oNE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oNE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oAND (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oAND, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oOR (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oOR, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_oNOT (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::oNOT, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fSIN (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fSIN, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fCOS (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fCOS, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fROUND (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fROUND, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fMOD (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fMOD, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fTRUNC (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fTRUNC, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fFRAC (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fFRAC, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fEXPO (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fEXPO, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fNORM (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fNORM, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fUNIF (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fUNIF, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fWEIB (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fWEIB, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fLOGN (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fLOGN, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fGAMM (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fGAMM, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fERLA (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fERLA, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fTRIA (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fTRIA, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fBETA (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fBETA, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fDISC (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fDISC, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fTNOW (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fTNOW, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fTFIN (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fTFIN, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_cIF (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::cIF, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_cELSE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::cELSE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_cFOR (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::cFOR, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_cTO (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::cTO, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_cDO (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::cDO, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_ATRIB (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::ATRIB, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_ILLEGAL (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::ILLEGAL, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_RESOURCE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::RESOURCE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fNR (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fNR, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fMR (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fMR, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fIRF (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fIRF, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fRESSEIZES (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fRESSEIZES, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fSTATE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fSTATE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fSETSUM (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fSETSUM, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_QUEUE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::QUEUE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fNQ (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fNQ, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fFIRSTINQ (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fFIRSTINQ, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fLASTINQ (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fLASTINQ, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fSAQUE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fSAQUE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fAQUE (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fAQUE, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_SET (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::SET, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fNUMSET (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fNUMSET, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_CSTAT (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::CSTAT, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_fTAVG (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::fTAVG, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_VARI (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::VARI, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_FORM (const obj_t& v, const location_type& l)
  {
    return symbol_type (token::FORM, v, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::LPAREN, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::RPAREN, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::PLUS, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::MINUS, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_STAR (const location_type& l)
  {
    return symbol_type (token::STAR, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_POWER (const location_type& l)
  {
    return symbol_type (token::POWER, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::SLASH, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_LESS (const location_type& l)
  {
    return symbol_type (token::LESS, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_GREATER (const location_type& l)
  {
    return symbol_type (token::GREATER, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::ASSIGN, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  genesyspp_parser::symbol_type
  genesyspp_parser::make_NEG (const location_type& l)
  {
    return symbol_type (token::NEG, l);
  }



} // yy
#line 2015 "../GenesysParser.h" // lalr1.cc:377




#endif // !YY_YY_GENESYSPARSER_H_INCLUDED
