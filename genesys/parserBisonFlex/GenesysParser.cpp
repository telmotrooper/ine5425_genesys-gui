// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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


// First part of user declarations.

#line 37 "../GenesysParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GenesysParser.h"

// User implementation prologue.

#line 51 "../GenesysParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 39 "bisonparser.yy" // lalr1.cc:413

# include "Genesys++-driver.h"


#line 58 "../GenesysParser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 144 "../GenesysParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  genesyspp_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  genesyspp_parser::genesyspp_parser (genesyspp_driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  genesyspp_parser::~genesyspp_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  genesyspp_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  genesyspp_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  genesyspp_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  genesyspp_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  genesyspp_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  genesyspp_parser::symbol_number_type
  genesyspp_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  genesyspp_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  genesyspp_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
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
        value.move< obj_t > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  genesyspp_parser::stack_symbol_type&
  genesyspp_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
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
        value.copy< obj_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  genesyspp_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  genesyspp_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  genesyspp_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  genesyspp_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  genesyspp_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  genesyspp_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  genesyspp_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  genesyspp_parser::debug_level_type
  genesyspp_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  genesyspp_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline genesyspp_parser::state_type
  genesyspp_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  genesyspp_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  genesyspp_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  genesyspp_parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 32 "bisonparser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver.getFile();
}

#line 576 "../GenesysParser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
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
        yylhs.value.build< obj_t > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 192 "bisonparser.yy" // lalr1.cc:859
    {YYACCEPT;}
#line 765 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 193 "bisonparser.yy" // lalr1.cc:859
    { driver.setResult(yystack_[0].value.as< obj_t > ().valor);}
#line 771 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 195 "bisonparser.yy" // lalr1.cc:859
    { yyerrok; }
#line 777 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 198 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 783 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 201 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 789 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 202 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 795 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 203 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 801 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 204 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 807 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 205 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 813 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 206 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor;}
#line 819 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 207 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 825 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 209 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 831 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 211 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 837 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 214 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 843 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 215 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 849 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 218 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor + yystack_[0].value.as< obj_t > ().valor;}
#line 855 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 219 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor - yystack_[0].value.as< obj_t > ().valor;}
#line 861 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 220 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor / yystack_[0].value.as< obj_t > ().valor;}
#line 867 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 221 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor * yystack_[0].value.as< obj_t > ().valor;}
#line 873 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 222 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = pow(yystack_[2].value.as< obj_t > ().valor,yystack_[0].value.as< obj_t > ().valor);}
#line 879 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 223 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = -yystack_[0].value.as< obj_t > ().valor;}
#line 885 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 226 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[2].value.as< obj_t > ().valor && (int) yystack_[0].value.as< obj_t > ().valor;}
#line 891 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 227 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[2].value.as< obj_t > ().valor || (int) yystack_[0].value.as< obj_t > ().valor;}
#line 897 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 228 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor < yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 903 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 229 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor <= yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 909 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 230 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor > yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 915 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 231 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor >= yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 921 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 232 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor == yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 927 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 233 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor != yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 933 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 240 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[4].value.as< obj_t > ().valor != 0 ? yystack_[2].value.as< obj_t > ().valor : yystack_[0].value.as< obj_t > ().valor;}
#line 939 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 241 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor != 0 ? yystack_[0].value.as< obj_t > ().valor : 0;}
#line 945 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 244 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = 0; }
#line 951 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 245 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = 0; }
#line 957 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 248 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 963 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 249 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 969 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 250 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 975 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 251 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 981 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 252 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 987 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 253 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 993 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 256 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getModel()->getSimulation()->getSimulatedTime();}
#line 999 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 257 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getModel()->getInfos()->getReplicationLength();}
#line 1005 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 260 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = sin(yystack_[1].value.as< obj_t > ().valor); }
#line 1011 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 261 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = cos(yystack_[1].value.as< obj_t > ().valor); }
#line 1017 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 264 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = round(yystack_[1].value.as< obj_t > ().valor);}
#line 1023 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 265 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor - (int) yystack_[1].value.as< obj_t > ().valor;}
#line 1029 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 266 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = trunc(yystack_[1].value.as< obj_t > ().valor);}
#line 1035 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 267 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[3].value.as< obj_t > ().valor % (int) yystack_[1].value.as< obj_t > ().valor; }
#line 1041 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 270 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleExponential(yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Exponencial";}
#line 1047 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 271 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleNormal(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Normal"; }
#line 1053 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 272 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleUniform(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Unificada"; }
#line 1059 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 273 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleWeibull(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Weibull"; }
#line 1065 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 274 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleLogNormal(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "LOGNormal"; }
#line 1071 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 275 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleGamma(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Gamma"; }
#line 1077 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 276 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleErlang(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Erlang"; }
#line 1083 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 277 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleTriangular(yystack_[5].value.as< obj_t > ().valor,yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Triangular"; }
#line 1089 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 278 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleBeta(yystack_[7].value.as< obj_t > ().valor,yystack_[5].value.as< obj_t > ().valor,yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Beta"; }
#line 1095 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 284 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor; }
#line 1101 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 292 "bisonparser.yy" // lalr1.cc:859
    {
				  driver.setResult(-1);
				  if(driver.getThrowsException()){
				    if(yystack_[0].value.as< obj_t > ().valor == 0){
				      throw std::string("Literal nao encontrado");
				    }else if(yystack_[0].value.as< obj_t > ().valor == 1){
				      throw std::string("Caracter invalido encontrado");
				    }
				  }else{
				    if(yystack_[0].value.as< obj_t > ().valor == 0){
				      driver.setErrorMessage(std::string("Literal nao encontrado"));
				    }else if(yystack_[0].value.as< obj_t > ().valor == 1){
				      driver.setErrorMessage(std::string("Caracter invalido encontrado"));
				    }
				  }
				}
#line 1122 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 312 "bisonparser.yy" // lalr1.cc:859
    {  double attributeValue = 0.0;
			    if (driver.getModel()->getSimulation()->getCurrentEntity() != nullptr) {
				try {
				    // it could crach because there may be no current entity, if the parse is running before simulation and therefore there is no CurrentEntity
				    attributeValue = driver.getModel()->getSimulation()->getCurrentEntity()->getAttributeValue(yystack_[0].value.as< obj_t > ().valor);
				} catch(...) {
				}
			    }
			    yylhs.value.as< obj_t > ().valor = attributeValue; 
			}
#line 1137 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 325 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 1143 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 326 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 1149 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 329 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[0].value.as< obj_t > ().id)))->getValue();}
#line 1155 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 330 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[3].value.as< obj_t > ().id)))->getValue(std::to_string(yystack_[1].value.as< obj_t > ().valor));}
#line 1161 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 331 "bisonparser.yy" // lalr1.cc:859
    { std::string index(std::to_string(yystack_[3].value.as< obj_t > ().valor)); index.append(","); index.append(std::to_string(yystack_[1].value.as< obj_t > ().valor)); yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[5].value.as< obj_t > ().id)))->getValue(index);}
#line 1167 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 335 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Formula*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Formula>(), yystack_[0].value.as< obj_t > ().id)))->getValue();}
#line 1173 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 339 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = 0; }
#line 1179 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 344 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->size();}
#line 1185 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 345 "bisonparser.yy" // lalr1.cc:859
    {/*For now does nothing because need acces to list of QUEUE, or at least the last element*/ }
#line 1191 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 346 "bisonparser.yy" // lalr1.cc:859
    { if (((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->size() > 0){
                                                            //id da 1a entidade da fila, talvez pegar nome
                                                            yylhs.value.as< obj_t > ().valor = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->first()->getEntity()->getId();
                                                          }else{
                                                            yylhs.value.as< obj_t > ().valor = 0;
                                                          }
                                                        }
#line 1203 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 353 "bisonparser.yy" // lalr1.cc:859
    {   
				 Util::identification queueID = yystack_[3].value.as< obj_t > ().id;
				 Util::identification attrID = yystack_[1].value.as< obj_t > ().id;
				 double sum = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[3].value.as< obj_t > ().id)))->sumAttributesFromWaiting(attrID);
				  yylhs.value.as< obj_t > ().valor = sum;
				}
#line 1214 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 359 "bisonparser.yy" // lalr1.cc:859
    {
				 Util::identification queueID = yystack_[5].value.as< obj_t > ().id;
				 Util::identification attrID = yystack_[1].value.as< obj_t > ().id;
				 double value = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[5].value.as< obj_t > ().id)))->getAttributeFromWaitingRank(yystack_[3].value.as< obj_t > ().valor-1, attrID); // rank starts on 0 in genesys
				  yylhs.value.as< obj_t > ().valor = value;
				}
#line 1225 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 369 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getCapacity();}
#line 1231 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 370 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getNumberBusy();}
#line 1237 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 371 "bisonparser.yy" // lalr1.cc:859
    { /*For now does nothing because needs get Seizes, check with teacher*/}
#line 1243 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 372 "bisonparser.yy" // lalr1.cc:859
    {  yylhs.value.as< obj_t > ().valor = static_cast<int>(((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getResourceState());
							}
#line 1250 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 375 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getResourceState() == Resource::ResourceState::FAILED ? 1 : 0; }
#line 1256 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 376 "bisonparser.yy" // lalr1.cc:859
    {   unsigned int count=0;
							    Resource* res;
							    List<ModelElement*>* setList = ((Set*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Set>(),yystack_[1].value.as< obj_t > ().id))->getElementSet(); 
							    for (std::list<ModelElement*>::iterator it = setList->getList()->begin(); it!=setList->getList()->end(); it++) {
								res = dynamic_cast<Resource*>(*it);
								if (res != nullptr) {
								    if (res->getResourceState()==Resource::ResourceState::BUSY) {
									count++;
								    }
								}
							    }
							    yylhs.value.as< obj_t > ().valor = count; 
							}
#line 1274 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 393 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Set*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Set>(),yystack_[1].value.as< obj_t > ().id))->getElementSet()->size(); }
#line 1280 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 399 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = 0; }
#line 1286 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 400 "bisonparser.yy" // lalr1.cc:859
    {
					    StatisticsCollector* cstat = ((StatisticsCollector*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<StatisticsCollector>(), yystack_[1].value.as< obj_t > ().id)));
					    double value = cstat->getStatistics()->average();
					    yylhs.value.as< obj_t > ().valor = value;
					}
#line 1296 "../GenesysParser.cpp" // lalr1.cc:859
    break;


#line 1300 "../GenesysParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  genesyspp_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  genesyspp_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char genesyspp_parser::yypact_ninf_ = -83;

  const signed char genesyspp_parser::yytable_ninf_ = -3;

  const short int
  genesyspp_parser::yypact_[] =
  {
     216,   -63,   -83,   274,   -83,   -83,   -83,   -83,   -83,   -83,
     -45,   -39,   -38,    -9,    -8,    -7,    -6,    -5,    -4,    -3,
      -2,    -1,     1,     2,    24,    25,   -83,   -83,    26,   -35,
     -83,    27,    28,    29,    30,    31,    32,    33,    34,    37,
      45,    47,    48,   -83,    49,   -58,   -83,   332,   332,   -83,
      50,   -83,  1009,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,    51,    52,    77,    78,
      81,    82,    83,    71,    79,    80,    84,    94,    97,    72,
      74,   332,   621,    66,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   629,   637,
     645,   387,   705,   713,   721,   397,   406,   415,   424,   433,
     495,   504,   513,   522,   -53,   729,   332,   332,    85,    86,
      87,    88,    89,    90,    91,    92,    93,   102,   104,    95,
      96,    36,   -83,   737,   -52,   -52,   -52,   -52,    15,    15,
     -46,   -46,    66,  1009,    66,   -52,   -52,   -83,   -83,   -83,
     332,   -83,   -83,   -83,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   -83,   332,   332,   797,   804,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   116,   152,   -83,
     -83,   332,   -83,   -83,   812,   826,   834,   842,   872,   902,
     910,   531,   540,  1009,   602,   917,   332,   332,    98,   107,
     103,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   332,   332,
     332,   332,   948,   979,   -83,   122,   -83,   933,   611,  1009,
    1009,   -35,   -35,   101,   -83,   332,   110,   -83,   111,   -83,
     -83,   993,   332,   332,   -83,  1009,  1009
  };

  const unsigned char
  genesyspp_parser::yydefact_[] =
  {
       0,     0,    66,     0,     5,     6,     1,    17,    18,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,    46,     0,     0,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,    70,    73,     0,     0,     3,
       0,     4,     7,     8,    11,    12,    10,    33,    34,     9,
      42,    40,    39,    41,    44,    14,    15,    16,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,    28,    30,    31,    32,    25,    26,
      19,    20,    22,    23,    21,    27,    29,    47,    48,    49,
       0,    51,    50,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,     0,     0,     0,     0,    81,    80,
      84,    82,    83,    85,    75,    77,    76,     0,     0,    86,
      88,     0,    71,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,    36,     0,     0,     0,     0,
       0,    52,    54,    55,    56,    57,    58,    59,     0,     0,
       0,     0,     0,     0,    78,     0,    72,     0,     0,    64,
      35,     0,     0,     0,    60,     0,     0,    38,     0,    37,
      79,     0,     0,     0,    61,    68,    69
  };

  const signed char
  genesyspp_parser::yypgoto_[] =
  {
     -83,   -83,   -83,   -44,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -29,   -82,
     -27,   -83,   -83
  };

  const short int
  genesyspp_parser::yydefgoto_[] =
  {
      -1,     3,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,   134,     4,    65,   247,
      66,    67,    68
  };

  const short int
  genesyspp_parser::yytable_[] =
  {
      86,    30,    87,   102,   103,   183,     5,   111,   112,   113,
     114,   115,    69,   101,   184,   113,   114,   115,    70,    71,
      45,   105,   106,   107,   108,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   135,   105,   106,   107,   108,   109,   110,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   151,    81,    82,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   111,   112,   113,   114,   115,   116,
     117,    83,    84,    85,    88,    89,    90,    91,    92,    93,
      94,    95,   186,   187,    96,   111,   112,   113,   114,   115,
     116,   117,    97,   201,    98,    99,   100,   104,   202,   105,
     106,   107,   108,   109,   110,   138,   139,   136,   137,   140,
     141,   142,   143,   149,   144,   145,   204,   150,   114,   146,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   147,
     214,   215,   148,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   218,   199,   200,   219,   234,   220,   243,   250,
     249,     0,   111,   112,   113,   114,   115,   116,   117,   197,
       0,   198,   232,   233,   235,   236,   252,   253,     0,     0,
       0,     0,     0,     0,   237,   238,   239,   240,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,     0,     0,     0,     0,     0,   255,   256,
       0,     0,   246,   246,   248,   248,    -2,     1,     0,    -2,
      -2,    -2,     0,     0,     0,     0,     0,     0,     0,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,     0,    -2,
       0,     0,    -2,     2,     0,    -2,    -2,    -2,    -2,    -2,
      -2,     0,    -2,    -2,    -2,    -2,    -2,     0,    -2,    -2,
      -2,    -2,    -2,    -2,     6,     0,    -2,     7,     8,     9,
       0,     0,     0,     0,     0,    -2,    -2,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,    29,     0,     0,
      30,     0,     0,    31,    32,    33,    34,    35,    36,     0,
      37,    38,    39,    40,    41,     0,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     7,     8,     9,     0,     0,
       0,     0,     0,    49,    50,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,    29,     0,     0,    30,     0,
       0,    31,    32,    33,    34,    35,    36,     0,    37,    38,
      39,    40,    41,     0,    42,    43,    44,    45,    46,    47,
       0,     0,    48,   105,   106,   107,   108,   109,   110,     0,
       0,     0,    50,   105,   106,   107,   108,   109,   110,     0,
       0,     0,   105,   106,   107,   108,   109,   110,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     105,   106,   107,   108,   109,   110,     0,     0,     0,   105,
     106,   107,   108,   109,   110,     0,   111,   112,   113,   114,
     115,   116,   117,     0,   170,     0,   111,   112,   113,   114,
     115,   116,   117,     0,   174,   111,   112,   113,   114,   115,
     116,   117,     0,   175,   111,   112,   113,   114,   115,   116,
     117,     0,   176,   111,   112,   113,   114,   115,   116,   117,
       0,   177,   111,   112,   113,   114,   115,   116,   117,     0,
     178,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     105,   106,   107,   108,   109,   110,     0,     0,     0,   105,
     106,   107,   108,   109,   110,     0,     0,     0,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,     0,   105,   106,   107,   108,
     109,   110,     0,     0,   111,   112,   113,   114,   115,   116,
     117,     0,   179,   111,   112,   113,   114,   115,   116,   117,
       0,   180,   111,   112,   113,   114,   115,   116,   117,     0,
     181,   111,   112,   113,   114,   115,   116,   117,     0,   182,
     111,   112,   113,   114,   115,   116,   117,     0,   228,   111,
     112,   113,   114,   115,   116,   117,     0,   229,   105,   106,
     107,   108,   109,   110,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   105,   106,   107,   108,   109,   110,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,   111,   112,   113,   114,   115,   116,   117,     0,   230,
     111,   112,   113,   114,   115,   116,   117,     0,   245,   152,
     111,   112,   113,   114,   115,   116,   117,   167,   111,   112,
     113,   114,   115,   116,   117,   168,   111,   112,   113,   114,
     115,   116,   117,   169,   111,   112,   113,   114,   115,   116,
     117,   105,   106,   107,   108,   109,   110,     0,     0,   105,
     106,   107,   108,   109,   110,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,   105,   106,   107,   108,   109,
     110,     0,     0,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   111,   112,   113,   114,   115,   116,
     117,   172,   111,   112,   113,   114,   115,   116,   117,   173,
     111,   112,   113,   114,   115,   116,   117,   185,   111,   112,
     113,   114,   115,   116,   117,   203,   111,   112,   113,   114,
     115,   116,   117,   105,   106,   107,   108,   109,   110,     0,
     105,   106,   107,   108,   109,   110,     0,     0,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,   216,   105,   106,   107,   108,   109,   110,   217,     0,
     105,   106,   107,   108,   109,   110,     0,     0,   105,   106,
     107,   108,   109,   110,     0,     0,   111,   112,   113,   114,
     115,   116,   117,   111,   112,   113,   114,   115,   116,   117,
     221,   111,   112,   113,   114,   115,   116,   117,   105,   106,
     107,   108,   109,   110,   222,   111,   112,   113,   114,   115,
     116,   117,   223,   111,   112,   113,   114,   115,   116,   117,
     224,   111,   112,   113,   114,   115,   116,   117,   105,   106,
     107,   108,   109,   110,     0,     0,   105,   106,   107,   108,
     109,   110,     0,   105,   106,   107,   108,   109,   110,     0,
     225,   111,   112,   113,   114,   115,   116,   117,     0,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,   231,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     226,   111,   112,   113,   114,   115,   116,   117,   227,   111,
     112,   113,   114,   115,   116,   117,   111,   112,   113,   114,
     115,   116,   117,   241,     0,   105,   106,   107,   108,   109,
     110,   244,   111,   112,   113,   114,   115,   116,   117,   105,
     106,   107,   108,   109,   110,     0,     0,   111,   112,   113,
     114,   115,   116,   117,   242,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,     0,
       0,   254,   111,   112,   113,   114,   115,   116,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,   115,   116,   117
  };

  const short int
  genesyspp_parser::yycheck_[] =
  {
      29,    36,    29,    47,    48,    58,    69,    59,    60,    61,
      62,    63,    57,    71,    67,    61,    62,    63,    57,    57,
      55,     6,     7,     8,     9,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     6,     7,     8,     9,    10,    11,    57,    57,
      57,    57,    57,    57,    57,    57,    57,   101,    57,    57,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    59,    60,    61,    62,    63,    64,
      65,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,   136,   137,    57,    59,    60,    61,    62,    63,
      64,    65,    57,    67,    57,    57,    57,    57,    72,     6,
       7,     8,     9,    10,    11,    38,    38,    66,    66,    38,
      38,    38,    51,    51,    45,    45,   170,    53,    62,    45,
     174,   175,   176,   177,   178,   179,   180,   181,   182,    45,
     184,   185,    45,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    36,    58,    58,     3,    58,   201,    36,    58,
     242,    -1,    59,    60,    61,    62,    63,    64,    65,    67,
      -1,    67,   216,   217,    67,    72,    66,    66,    -1,    -1,
      -1,    -1,    -1,    -1,   228,   229,   230,   231,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   245,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,
      -1,    -1,   241,   242,   241,   242,     0,     1,    -1,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    -1,    46,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,     0,    -1,    60,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    69,    70,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      36,    -1,    -1,    39,    40,    41,    42,    43,    44,    -1,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    -1,    -1,    60,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    69,    70,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,
      -1,    39,    40,    41,    42,    43,    44,    -1,    46,    47,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,    57,
      -1,    -1,    60,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    70,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,     6,
       7,     8,     9,    10,    11,    -1,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    -1,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    59,    60,    61,    62,    63,
      64,    65,    -1,    67,    59,    60,    61,    62,    63,    64,
      65,    -1,    67,    59,    60,    61,    62,    63,    64,    65,
      -1,    67,    59,    60,    61,    62,    63,    64,    65,    -1,
      67,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    11,    -1,    -1,    59,    60,    61,    62,    63,    64,
      65,    -1,    67,    59,    60,    61,    62,    63,    64,    65,
      -1,    67,    59,    60,    61,    62,    63,    64,    65,    -1,
      67,    59,    60,    61,    62,    63,    64,    65,    -1,    67,
      59,    60,    61,    62,    63,    64,    65,    -1,    67,    59,
      60,    61,    62,    63,    64,    65,    -1,    67,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    11,    -1,    -1,     6,     7,     8,     9,    10,
      11,    -1,    -1,     6,     7,     8,     9,    10,    11,    -1,
      -1,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    65,    -1,    67,
      59,    60,    61,    62,    63,    64,    65,    -1,    67,    58,
      59,    60,    61,    62,    63,    64,    65,    58,    59,    60,
      61,    62,    63,    64,    65,    58,    59,    60,    61,    62,
      63,    64,    65,    58,    59,    60,    61,    62,    63,    64,
      65,     6,     7,     8,     9,    10,    11,    -1,    -1,     6,
       7,     8,     9,    10,    11,    -1,    -1,     6,     7,     8,
       9,    10,    11,    -1,    -1,     6,     7,     8,     9,    10,
      11,    -1,    -1,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    64,
      65,    58,    59,    60,    61,    62,    63,    64,    65,    58,
      59,    60,    61,    62,    63,    64,    65,    58,    59,    60,
      61,    62,    63,    64,    65,    58,    59,    60,    61,    62,
      63,    64,    65,     6,     7,     8,     9,    10,    11,    -1,
       6,     7,     8,     9,    10,    11,    -1,    -1,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,     6,     7,     8,     9,    10,    11,    34,    -1,
       6,     7,     8,     9,    10,    11,    -1,    -1,     6,     7,
       8,     9,    10,    11,    -1,    -1,    59,    60,    61,    62,
      63,    64,    65,    59,    60,    61,    62,    63,    64,    65,
      58,    59,    60,    61,    62,    63,    64,    65,     6,     7,
       8,     9,    10,    11,    58,    59,    60,    61,    62,    63,
      64,    65,    58,    59,    60,    61,    62,    63,    64,    65,
      58,    59,    60,    61,    62,    63,    64,    65,     6,     7,
       8,     9,    10,    11,    -1,    -1,     6,     7,     8,     9,
      10,    11,    -1,     6,     7,     8,     9,    10,    11,    -1,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,    11,
      58,    59,    60,    61,    62,    63,    64,    65,    58,    59,
      60,    61,    62,    63,    64,    65,    59,    60,    61,    62,
      63,    64,    65,    35,    -1,     6,     7,     8,     9,    10,
      11,    58,    59,    60,    61,    62,    63,    64,    65,     6,
       7,     8,     9,    10,    11,    -1,    -1,    59,    60,    61,
      62,    63,    64,    65,    35,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    65
  };

  const unsigned char
  genesyspp_parser::yystos_[] =
  {
       0,     1,    37,    74,    90,    69,     0,     3,     4,     5,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    33,
      36,    39,    40,    41,    42,    43,    44,    46,    47,    48,
      49,    50,    52,    53,    54,    55,    56,    57,    60,    69,
      70,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    91,    93,    94,    95,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    91,    93,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    71,    76,    76,    57,     6,     7,     8,     9,    10,
      11,    59,    60,    61,    62,    63,    64,    65,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    89,    76,    66,    66,    38,    38,
      38,    38,    38,    51,    45,    45,    45,    45,    45,    51,
      53,    76,    58,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    58,    58,    58,
      67,    58,    58,    58,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    58,    67,    58,    76,    76,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    67,    67,    58,
      58,    67,    72,    58,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    34,    34,    36,     3,
      76,    58,    58,    58,    58,    58,    58,    58,    67,    67,
      67,    32,    76,    76,    58,    67,    72,    76,    76,    76,
      76,    35,    35,    36,    58,    67,    91,    92,    93,    92,
      58,    76,    66,    66,    58,    76,    76
  };

  const unsigned char
  genesyspp_parser::yyr1_[] =
  {
       0,    73,    74,    74,    74,    74,    74,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    89,    89,    90,    91,    92,    92,
      93,    93,    93,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95
  };

  const unsigned char
  genesyspp_parser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     7,     5,     8,     8,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     4,
       4,     4,     6,     4,     6,     6,     6,     6,     6,     6,
       8,    10,     4,     4,     5,     3,     1,     1,     3,     3,
       1,     4,     6,     1,     1,     4,     4,     4,     6,     8,
       4,     4,     4,     4,     4,     4,     4,     1,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const genesyspp_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "NUMD", "NUMH", "CTEZERO",
  "oLE", "oGE", "oEQ", "oNE", "oAND", "oOR", "oNOT", "fSIN", "fCOS",
  "fROUND", "fMOD", "fTRUNC", "fFRAC", "fEXPO", "fNORM", "fUNIF", "fWEIB",
  "fLOGN", "fGAMM", "fERLA", "fTRIA", "fBETA", "fDISC", "fTNOW", "fTFIN",
  "cIF", "cELSE", "cFOR", "cTO", "cDO", "ATRIB", "ILLEGAL", "RESOURCE",
  "fNR", "fMR", "fIRF", "fRESSEIZES", "fSTATE", "fSETSUM", "QUEUE", "fNQ",
  "fFIRSTINQ", "fLASTINQ", "fSAQUE", "fAQUE", "SET", "fNUMSET", "CSTAT",
  "fTAVG", "VARI", "FORM", "\"(\"", "\")\"", "\"+\"", "\"-\"", "\"*\"",
  "\"^\"", "\"/\"", "\"<\"", "\">\"", "\"=\"", "\",\"", "NEG", "'\\n'",
  "\"USER\"", "\"[\"", "\"]\"", "$accept", "input", "programa",
  "expressao", "numero", "aritmetica", "relacional", "comando",
  "comandoIF", "comandoFOR", "funcao", "funcaoKernel", "funcaoTrig",
  "funcaoArit", "funcaoProb", "funcaoUser", "listaparm", "illegal",
  "atributo", "atribuicao", "variavel", "formula", "funcaoPlugin", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  genesyspp_parser::yyrline_[] =
  {
       0,   191,   191,   192,   193,   194,   195,   198,   201,   202,
     203,   204,   205,   206,   207,   209,   211,   214,   215,   218,
     219,   220,   221,   222,   223,   226,   227,   228,   229,   230,
     231,   232,   233,   236,   237,   240,   241,   244,   245,   248,
     249,   250,   251,   252,   253,   256,   257,   260,   261,   264,
     265,   266,   267,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   284,   288,   289,   292,   312,   325,   326,
     329,   330,   331,   335,   339,   344,   345,   346,   353,   359,
     369,   370,   371,   372,   375,   376,   393,   399,   400
  };

  // Print the state stack on the debug stream.
  void
  genesyspp_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  genesyspp_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1992 "../GenesysParser.cpp" // lalr1.cc:1167
#line 414 "bisonparser.yy" // lalr1.cc:1168

void
yy::genesyspp_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
