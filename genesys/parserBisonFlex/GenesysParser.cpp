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
#line 35 "bisonparser.yy" // lalr1.cc:413

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
      case 5: // ATRIB
      case 6: // VARI
      case 7: // FORM
      case 8: // QUEUE
      case 9: // RES
      case 10: // fTFIN
      case 11: // fNR
      case 12: // fMR
      case 13: // fIRF
      case 14: // fRESSEIZES
      case 15: // fSTATE
      case 16: // fNQ
      case 17: // fFIRSTINQ
      case 18: // fLASTINQ
      case 19: // oLE
      case 20: // oGE
      case 21: // oEQ
      case 22: // oNE
      case 23: // oAND
      case 24: // oOR
      case 25: // oNOT
      case 26: // fSIN
      case 27: // fCOS
      case 28: // fAINT
      case 29: // fMOD
      case 30: // fINT
      case 31: // fFRAC
      case 32: // fEXPO
      case 33: // fNORM
      case 34: // fUNIF
      case 35: // fWEIB
      case 36: // fLOGN
      case 37: // fGAMM
      case 38: // fERLA
      case 39: // fTRIA
      case 40: // fBETA
      case 41: // fDISC
      case 42: // fTNOW
      case 43: // cIF
      case 44: // cELSE
      case 45: // cFOR
      case 46: // cTO
      case 47: // cDO
      case 48: // ILLEGAL
      case 66: // input
      case 67: // programa
      case 68: // expressao
      case 69: // numero
      case 70: // aritmetica
      case 71: // relacional
      case 72: // comando
      case 73: // comandoIF
      case 74: // comandoFOR
      case 75: // funcao
      case 76: // atributo
      case 77: // atribuicao
      case 78: // variavel
      case 79: // formula
      case 80: // funcaoTrig
      case 81: // funcaoArit
      case 82: // funcaoProb
      case 83: // funcaoStrc
      case 84: // funcaoUser
      case 85: // listaparm
      case 86: // illegal
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
      case 5: // ATRIB
      case 6: // VARI
      case 7: // FORM
      case 8: // QUEUE
      case 9: // RES
      case 10: // fTFIN
      case 11: // fNR
      case 12: // fMR
      case 13: // fIRF
      case 14: // fRESSEIZES
      case 15: // fSTATE
      case 16: // fNQ
      case 17: // fFIRSTINQ
      case 18: // fLASTINQ
      case 19: // oLE
      case 20: // oGE
      case 21: // oEQ
      case 22: // oNE
      case 23: // oAND
      case 24: // oOR
      case 25: // oNOT
      case 26: // fSIN
      case 27: // fCOS
      case 28: // fAINT
      case 29: // fMOD
      case 30: // fINT
      case 31: // fFRAC
      case 32: // fEXPO
      case 33: // fNORM
      case 34: // fUNIF
      case 35: // fWEIB
      case 36: // fLOGN
      case 37: // fGAMM
      case 38: // fERLA
      case 39: // fTRIA
      case 40: // fBETA
      case 41: // fDISC
      case 42: // fTNOW
      case 43: // cIF
      case 44: // cELSE
      case 45: // cFOR
      case 46: // cTO
      case 47: // cDO
      case 48: // ILLEGAL
      case 66: // input
      case 67: // programa
      case 68: // expressao
      case 69: // numero
      case 70: // aritmetica
      case 71: // relacional
      case 72: // comando
      case 73: // comandoIF
      case 74: // comandoFOR
      case 75: // funcao
      case 76: // atributo
      case 77: // atribuicao
      case 78: // variavel
      case 79: // formula
      case 80: // funcaoTrig
      case 81: // funcaoArit
      case 82: // funcaoProb
      case 83: // funcaoStrc
      case 84: // funcaoUser
      case 85: // listaparm
      case 86: // illegal
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
    #line 28 "bisonparser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver.getFile();
}

#line 558 "../GenesysParser.cpp" // lalr1.cc:741

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
      case 5: // ATRIB
      case 6: // VARI
      case 7: // FORM
      case 8: // QUEUE
      case 9: // RES
      case 10: // fTFIN
      case 11: // fNR
      case 12: // fMR
      case 13: // fIRF
      case 14: // fRESSEIZES
      case 15: // fSTATE
      case 16: // fNQ
      case 17: // fFIRSTINQ
      case 18: // fLASTINQ
      case 19: // oLE
      case 20: // oGE
      case 21: // oEQ
      case 22: // oNE
      case 23: // oAND
      case 24: // oOR
      case 25: // oNOT
      case 26: // fSIN
      case 27: // fCOS
      case 28: // fAINT
      case 29: // fMOD
      case 30: // fINT
      case 31: // fFRAC
      case 32: // fEXPO
      case 33: // fNORM
      case 34: // fUNIF
      case 35: // fWEIB
      case 36: // fLOGN
      case 37: // fGAMM
      case 38: // fERLA
      case 39: // fTRIA
      case 40: // fBETA
      case 41: // fDISC
      case 42: // fTNOW
      case 43: // cIF
      case 44: // cELSE
      case 45: // cFOR
      case 46: // cTO
      case 47: // cDO
      case 48: // ILLEGAL
      case 66: // input
      case 67: // programa
      case 68: // expressao
      case 69: // numero
      case 70: // aritmetica
      case 71: // relacional
      case 72: // comando
      case 73: // comandoIF
      case 74: // comandoFOR
      case 75: // funcao
      case 76: // atributo
      case 77: // atribuicao
      case 78: // variavel
      case 79: // formula
      case 80: // funcaoTrig
      case 81: // funcaoArit
      case 82: // funcaoProb
      case 83: // funcaoStrc
      case 84: // funcaoUser
      case 85: // listaparm
      case 86: // illegal
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
#line 142 "bisonparser.yy" // lalr1.cc:859
    {YYACCEPT;}
#line 738 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 143 "bisonparser.yy" // lalr1.cc:859
    { driver.setResult(yystack_[0].value.as< obj_t > ().valor);}
#line 744 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 145 "bisonparser.yy" // lalr1.cc:859
    { yyerrok; }
#line 750 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 148 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 756 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 151 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 762 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 152 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 768 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 153 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor;}
#line 774 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 154 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 780 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 155 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 786 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 156 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 792 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 157 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 798 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 158 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 804 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 159 "bisonparser.yy" // lalr1.cc:859
    {}
#line 810 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 162 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 816 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 163 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor;}
#line 822 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 166 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor + yystack_[0].value.as< obj_t > ().valor;}
#line 828 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 167 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor - yystack_[0].value.as< obj_t > ().valor;}
#line 834 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 168 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor / yystack_[0].value.as< obj_t > ().valor;}
#line 840 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 169 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor * yystack_[0].value.as< obj_t > ().valor;}
#line 846 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 170 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = pow(yystack_[2].value.as< obj_t > ().valor,yystack_[0].value.as< obj_t > ().valor);}
#line 852 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 171 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = -yystack_[0].value.as< obj_t > ().valor;}
#line 858 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 174 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[2].value.as< obj_t > ().valor && (int) yystack_[0].value.as< obj_t > ().valor;}
#line 864 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 175 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[2].value.as< obj_t > ().valor || (int) yystack_[0].value.as< obj_t > ().valor;}
#line 870 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 176 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor < yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 876 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 177 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor <= yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 882 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 178 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor > yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 888 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 179 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor >= yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 894 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 180 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor == yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 900 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 181 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor != yystack_[0].value.as< obj_t > ().valor ? 1 : 0;}
#line 906 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 188 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[4].value.as< obj_t > ().valor != 0 ? yystack_[2].value.as< obj_t > ().valor : yystack_[0].value.as< obj_t > ().valor;}
#line 912 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 189 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = yystack_[2].value.as< obj_t > ().valor != 0 ? yystack_[0].value.as< obj_t > ().valor : 0;}
#line 918 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 192 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = 0; }
#line 924 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 193 "bisonparser.yy" // lalr1.cc:859
    {yylhs.value.as< obj_t > ().valor = 0; }
#line 930 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 196 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 936 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 197 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 942 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 198 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 948 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 199 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 954 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 200 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 960 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 205 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 966 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 209 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 972 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 210 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[0].value.as< obj_t > ().valor; }
#line 978 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 213 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[0].value.as< obj_t > ().id)))->getValue();}
#line 984 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 214 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[3].value.as< obj_t > ().id)))->getValue(std::to_string(yystack_[1].value.as< obj_t > ().valor));}
#line 990 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 215 "bisonparser.yy" // lalr1.cc:859
    { std::string index(std::to_string(yystack_[3].value.as< obj_t > ().valor)); index.append(","); index.append(std::to_string(yystack_[1].value.as< obj_t > ().valor)); yylhs.value.as< obj_t > ().valor = ((Variable*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), yystack_[5].value.as< obj_t > ().id)))->getValue(index);}
#line 996 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 219 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Formula*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Formula>(), yystack_[0].value.as< obj_t > ().id)))->getValue();}
#line 1002 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 222 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = sin(yystack_[1].value.as< obj_t > ().valor); }
#line 1008 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 223 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = cos(yystack_[1].value.as< obj_t > ().valor); }
#line 1014 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 226 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[1].value.as< obj_t > ().valor;}
#line 1020 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 227 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor - (int) yystack_[1].value.as< obj_t > ().valor;}
#line 1026 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 228 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[1].value.as< obj_t > ().valor;}
#line 1032 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 229 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = (int) yystack_[3].value.as< obj_t > ().valor % (int) yystack_[1].value.as< obj_t > ().valor; }
#line 1038 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 232 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleExponential(yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Exponencial";}
#line 1044 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 233 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleNormal(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Normal"; }
#line 1050 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 234 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleUniform(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Unificada"; }
#line 1056 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 235 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleWeibull(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Weibull"; }
#line 1062 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 236 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleLogNormal(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "LOGNormal"; }
#line 1068 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 237 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleGamma(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Gamma"; }
#line 1074 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 238 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleErlang(yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Erlang"; }
#line 1080 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 239 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleTriangular(yystack_[5].value.as< obj_t > ().valor,yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Triangular"; }
#line 1086 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 240 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getProbs()->sampleBeta(yystack_[7].value.as< obj_t > ().valor,yystack_[5].value.as< obj_t > ().valor,yystack_[3].value.as< obj_t > ().valor,yystack_[1].value.as< obj_t > ().valor); yylhs.value.as< obj_t > ().tipo = "Beta"; }
#line 1092 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 244 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->size();}
#line 1098 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 245 "bisonparser.yy" // lalr1.cc:859
    {/*For now does nothing because need acces to list of QUEUE, or at least the last element*/ }
#line 1104 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 246 "bisonparser.yy" // lalr1.cc:859
    { if (((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->size() > 0){
                                                                    //id da 1a entidade da fila, talvez pegar nome
                                                                    yylhs.value.as< obj_t > ().valor = ((Queue*)(driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), yystack_[1].value.as< obj_t > ().id)))->first()->getEntity()->getId();
                                                                  }else{
                                                                    yylhs.value.as< obj_t > ().valor = 0;
                                                                  }
                                                                }
#line 1116 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 253 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getCapacity();}
#line 1122 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 254 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getNumberBusy();}
#line 1128 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 255 "bisonparser.yy" // lalr1.cc:859
    { /*For now does nothing because needs get Seizes, check with teacher*/}
#line 1134 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 256 "bisonparser.yy" // lalr1.cc:859
    {  switch(((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getResourceState()){
                                                                    case Resource::ResourceState::IDLE:
                                                                      yylhs.value.as< obj_t > ().valor = -1;
                                                                      break;
                                                                    case Resource::ResourceState::BUSY:
                                                                      yylhs.value.as< obj_t > ().valor = -2;
                                                                      break;
                                                                    case Resource::ResourceState::FAILED:
                                                                      yylhs.value.as< obj_t > ().valor = -4;
                                                                      break;
                                                                    case Resource::ResourceState::INACTIVE:
                                                                      yylhs.value.as< obj_t > ().valor = -3;
                                                                    default:
                                                                      yylhs.value.as< obj_t > ().valor = -5;
                                                                      break;
                                                                  }
                                                                }
#line 1156 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 274 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = ((Resource*)driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), yystack_[1].value.as< obj_t > ().id))->getResourceState() == Resource::ResourceState::FAILED ? 1 : 0; }
#line 1162 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 275 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getModel()->getSimulation()->getSimulatedTime();}
#line 1168 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 276 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = driver.getModel()->getInfos()->getReplicationLength();}
#line 1174 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 280 "bisonparser.yy" // lalr1.cc:859
    { yylhs.value.as< obj_t > ().valor = yystack_[1].value.as< obj_t > ().valor; }
#line 1180 "../GenesysParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 288 "bisonparser.yy" // lalr1.cc:859
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
#line 1201 "../GenesysParser.cpp" // lalr1.cc:859
    break;


#line 1205 "../GenesysParser.cpp" // lalr1.cc:859
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


  const signed char genesyspp_parser::yypact_ninf_ = -71;

  const signed char genesyspp_parser::yytable_ninf_ = -3;

  const short int
  genesyspp_parser::yypact_[] =
  {
     185,   -46,   -71,   247,   -71,   -71,   -71,   -71,   -71,   -71,
     -45,   -71,   -71,   -33,   -31,   -30,   -28,   -27,   -26,   -25,
     -24,   -23,   -22,   -21,    -3,    -2,    -1,     0,     1,    16,
      23,    24,    25,    26,    27,    28,    29,   -71,    36,     4,
     309,   309,   -71,    37,   -71,   995,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     309,    78,    79,    80,    81,    82,    86,    87,    88,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   -71,    39,    49,   119,
      51,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,    47,    58,    68,    69,    70,
      71,    74,    75,    85,   601,   640,   648,   343,   656,   664,
     703,   355,   364,   405,   414,   423,   464,   473,   482,   523,
     -48,   711,   309,   309,   -71,   719,   -47,   -47,   -47,   -47,
     187,   187,   -41,   -41,    51,   995,    51,   -47,   -47,   309,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   309,   -71,   -71,   -71,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   -71,   309,   309,   758,   770,
     -71,    60,   778,   817,   825,   833,   841,   880,   888,   532,
     541,   995,   582,   902,   309,   309,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   309,   309,   309,   309,   928,   941,
     949,   591,   995,   995,     4,     4,   -71,   309,    89,   -71,
      90,   -71,   988,   309,   309,   -71,   995,   995
  };

  const unsigned char
  genesyspp_parser::yydefact_[] =
  {
       0,     0,    80,     0,     5,     6,     1,    17,    18,    12,
      47,    50,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,     3,     0,     4,     7,    15,     8,     9,    16,
      33,    34,    11,    13,    14,    40,    39,    41,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,     0,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     0,    28,    30,    31,    32,
      25,    26,    19,    20,    22,    23,    21,    27,    29,     0,
      48,    71,    70,    74,    72,    73,    67,    69,    68,    51,
      52,    53,     0,    55,    54,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,     0,     0,     0,     0,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     0,    36,     0,     0,    49,    56,    58,    59,
      60,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,     0,    78,    35,     0,     0,    64,     0,     0,    38,
       0,    37,     0,     0,     0,    65,    45,    46
  };

  const signed char
  genesyspp_parser::yypgoto_[] =
  {
     -71,   -71,   -71,   -40,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   105,   -70,   -36,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71
  };

  const short int
  genesyspp_parser::yydefgoto_[] =
  {
      -1,     3,    44,    45,    46,    47,    48,    49,    50,    51,
      52,   218,   219,    53,    54,    55,    56,    57,    58,    59,
     130,     4
  };

  const short int
  genesyspp_parser::yytable_[] =
  {
      89,    90,   175,    88,    98,    99,   100,   101,   102,    86,
      10,   176,   100,   101,   102,     5,    61,    60,    62,    63,
     105,    64,    65,    66,    67,    68,    69,    70,    71,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   131,    72,    73,    74,    75,
      76,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,    77,    92,    93,    94,    95,
      96,    97,    78,    79,    80,    81,    82,    83,    84,    92,
      93,    94,    95,    96,    97,    85,    91,   106,   107,   108,
     109,   110,   178,   179,   111,   112,   113,   132,    98,    99,
     100,   101,   102,   103,   104,   101,   149,   133,   151,   181,
     150,    98,    99,   100,   101,   102,   103,   104,   152,   153,
     154,   155,   182,   196,   156,   157,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   158,   192,   193,    92,    93,
      94,    95,    96,    97,    87,   221,     0,   223,   224,     0,
       0,     0,     0,     0,   208,   209,     0,     0,     0,     0,
       0,     0,     0,     0,   210,   211,   212,   213,     0,   134,
      98,    99,   100,   101,   102,   103,   104,   222,   220,   220,
       0,     0,     0,   226,   227,    -2,     1,     0,    -2,    -2,
      -2,    -2,    -2,     0,     0,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,     0,     0,    92,    93,    94,    95,
       0,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,     0,
      -2,     0,     0,     2,    -2,     0,     0,    -2,    98,    99,
     100,   101,   102,   103,   104,     0,    -2,     6,     0,    -2,
       7,     8,     9,    10,    11,     0,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     0,    39,     0,     0,     0,    40,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,    43,     7,     8,     9,    10,    11,     0,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     0,    39,     0,     0,     0,    40,     0,
       0,    41,    92,    93,    94,    95,    96,    97,     0,     0,
       0,     0,     0,    43,    92,    93,    94,    95,    96,    97,
       0,     0,     0,    92,    93,    94,    95,    96,    97,     0,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   103,
     104,     0,   162,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,     0,   166,    98,    99,   100,   101,   102,
     103,   104,     0,   167,    92,    93,    94,    95,    96,    97,
       0,     0,     0,    92,    93,    94,    95,    96,    97,     0,
       0,     0,    92,    93,    94,    95,    96,    97,     0,     0,
       0,     0,     0,     0,     0,     0,    98,    99,   100,   101,
     102,   103,   104,     0,   168,    98,    99,   100,   101,   102,
     103,   104,     0,   169,    98,    99,   100,   101,   102,   103,
     104,     0,   170,    92,    93,    94,    95,    96,    97,     0,
       0,     0,    92,    93,    94,    95,    96,    97,     0,     0,
       0,    92,    93,    94,    95,    96,    97,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    99,   100,   101,   102,
     103,   104,     0,   171,    98,    99,   100,   101,   102,   103,
     104,     0,   172,    98,    99,   100,   101,   102,   103,   104,
       0,   173,    92,    93,    94,    95,    96,    97,     0,     0,
       0,    92,    93,    94,    95,    96,    97,     0,     0,     0,
      92,    93,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    98,    99,   100,   101,   102,   103,
     104,     0,   174,    98,    99,   100,   101,   102,   103,   104,
       0,   204,    98,    99,   100,   101,   102,   103,   104,     0,
     205,    92,    93,    94,    95,    96,    97,     0,     0,     0,
      92,    93,    94,    95,    96,    97,     0,     0,     0,     0,
      92,    93,    94,    95,    96,    97,     0,     0,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103,   104,
       0,   206,    98,    99,   100,   101,   102,   103,   104,     0,
     217,   159,    98,    99,   100,   101,   102,   103,   104,    92,
      93,    94,    95,    96,    97,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,    92,    93,    94,    95,    96,
      97,     0,     0,    92,    93,    94,    95,    96,    97,     0,
     160,    98,    99,   100,   101,   102,   103,   104,   161,    98,
      99,   100,   101,   102,   103,   104,   163,    98,    99,   100,
     101,   102,   103,   104,   164,    98,    99,   100,   101,   102,
     103,   104,    92,    93,    94,    95,    96,    97,     0,     0,
      92,    93,    94,    95,    96,    97,     0,     0,    92,    93,
      94,    95,    96,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,    98,    99,   100,   101,   102,   103,
     104,   177,    98,    99,   100,   101,   102,   103,   104,   180,
      98,    99,   100,   101,   102,   103,   104,    92,    93,    94,
      95,    96,    97,     0,     0,     0,     0,     0,     0,    92,
      93,    94,    95,    96,    97,     0,     0,    92,    93,    94,
      95,    96,    97,     0,   194,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   195,     0,     0,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   197,    98,
      99,   100,   101,   102,   103,   104,    92,    93,    94,    95,
      96,    97,     0,     0,    92,    93,    94,    95,    96,    97,
       0,     0,    92,    93,    94,    95,    96,    97,     0,     0,
      92,    93,    94,    95,    96,    97,     0,   198,    98,    99,
     100,   101,   102,   103,   104,   199,    98,    99,   100,   101,
     102,   103,   104,   200,    98,    99,   100,   101,   102,   103,
     104,   201,    98,    99,   100,   101,   102,   103,   104,    92,
      93,    94,    95,    96,    97,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,     0,     0,     0,     0,     0,
       0,    92,    93,    94,    95,    96,    97,     0,     0,     0,
     202,    98,    99,   100,   101,   102,   103,   104,   203,    98,
      99,   100,   101,   102,   103,   104,   207,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      92,    93,    94,    95,    96,    97,     0,     0,    92,    93,
      94,    95,    96,    97,     0,   214,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,     0,     0,   215,     0,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   216,
      98,    99,   100,   101,   102,   103,   104,    92,    93,    94,
      95,    96,    97,     0,    92,    93,    94,    95,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   225,    98,
      99,   100,   101,   102,   103,   104,    98,    99,   100,   101,
     102,   103,   104
  };

  const short int
  genesyspp_parser::yycheck_[] =
  {
      40,    41,    50,    39,    51,    52,    53,    54,    55,     5,
       6,    59,    53,    54,    55,    61,    49,    62,    49,    49,
      60,    49,    49,    49,    49,    49,    49,    49,    49,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    49,    49,    49,    49,
      49,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,    49,    19,    20,    21,    22,
      23,    24,    49,    49,    49,    49,    49,    49,    49,    19,
      20,    21,    22,    23,    24,    49,    49,     9,     9,     9,
       9,     9,   132,   133,     8,     8,     8,    58,    51,    52,
      53,    54,    55,    56,    57,    54,    59,    58,    50,   149,
      63,    51,    52,    53,    54,    55,    56,    57,    50,    50,
      50,    50,   162,    63,    50,    50,   166,   167,   168,   169,
     170,   171,   172,   173,   174,    50,   176,   177,    19,    20,
      21,    22,    23,    24,    39,   215,    -1,    58,    58,    -1,
      -1,    -1,    -1,    -1,   194,   195,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   204,   205,   206,   207,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,   217,   214,   215,
      -1,    -1,    -1,   223,   224,     0,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    19,    20,    21,    22,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    -1,    -1,    48,    49,    -1,    -1,    52,    51,    52,
      53,    54,    55,    56,    57,    -1,    61,     0,    -1,    64,
       3,     4,     5,     6,     7,    -1,    -1,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    64,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    49,    -1,
      -1,    52,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    64,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    50,    51,    52,    53,    54,    55,    56,    57,    19,
      20,    21,    22,    23,    24,    -1,    -1,    19,    20,    21,
      22,    23,    24,    -1,    -1,    19,    20,    21,    22,    23,
      24,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    50,    51,
      52,    53,    54,    55,    56,    57,    50,    51,    52,    53,
      54,    55,    56,    57,    50,    51,    52,    53,    54,    55,
      56,    57,    19,    20,    21,    22,    23,    24,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    -1,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    50,    51,    52,    53,    54,    55,    56,    57,    50,
      51,    52,    53,    54,    55,    56,    57,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    -1,    -1,    19,    20,    21,
      22,    23,    24,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    50,    51,
      52,    53,    54,    55,    56,    57,    19,    20,    21,    22,
      23,    24,    -1,    -1,    19,    20,    21,    22,    23,    24,
      -1,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    50,    51,    52,    53,    54,
      55,    56,    57,    50,    51,    52,    53,    54,    55,    56,
      57,    50,    51,    52,    53,    54,    55,    56,    57,    19,
      20,    21,    22,    23,    24,    -1,    -1,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    50,    51,
      52,    53,    54,    55,    56,    57,    44,    19,    20,    21,
      22,    23,    24,    51,    52,    53,    54,    55,    56,    57,
      19,    20,    21,    22,    23,    24,    -1,    -1,    19,    20,
      21,    22,    23,    24,    -1,    47,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    47,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    50,
      51,    52,    53,    54,    55,    56,    57,    19,    20,    21,
      22,    23,    24,    -1,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    51,    52,    53,    54,
      55,    56,    57
  };

  const unsigned char
  genesyspp_parser::yystos_[] =
  {
       0,     1,    48,    66,    86,    61,     0,     3,     4,     5,
       6,     7,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    45,
      49,    52,    61,    64,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    78,    79,    80,    81,    82,    83,    84,
      62,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,     5,    76,    78,    68,
      68,    49,    19,    20,    21,    22,    23,    24,    51,    52,
      53,    54,    55,    56,    57,    68,     9,     9,     9,     9,
       9,     8,     8,     8,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      85,    68,    58,    58,    50,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    59,
      63,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    59,    50,    50,    50,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    50,    59,    50,    68,    68,
      50,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    46,    46,    63,    50,    50,    50,
      50,    50,    50,    50,    59,    59,    59,    44,    68,    68,
      68,    68,    68,    68,    47,    47,    50,    59,    76,    77,
      78,    77,    68,    58,    58,    50,    68,    68
  };

  const unsigned char
  genesyspp_parser::yyr1_[] =
  {
       0,    65,    66,    66,    66,    66,    66,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    69,    69,    70,
      70,    70,    70,    70,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    76,    77,    77,    78,    78,    78,
      79,    80,    80,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    84,    85,    85,
      86
  };

  const unsigned char
  genesyspp_parser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     1,     2,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     7,     5,     8,     8,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     4,     6,
       1,     4,     4,     4,     4,     4,     6,     4,     6,     6,
       6,     6,     6,     6,     8,    10,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     1,     1,     4,     5,     3,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const genesyspp_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "NUMD", "NUMH", "ATRIB",
  "VARI", "FORM", "QUEUE", "RES", "fTFIN", "fNR", "fMR", "fIRF",
  "fRESSEIZES", "fSTATE", "fNQ", "fFIRSTINQ", "fLASTINQ", "oLE", "oGE",
  "oEQ", "oNE", "oAND", "oOR", "oNOT", "fSIN", "fCOS", "fAINT", "fMOD",
  "fINT", "fFRAC", "fEXPO", "fNORM", "fUNIF", "fWEIB", "fLOGN", "fGAMM",
  "fERLA", "fTRIA", "fBETA", "fDISC", "fTNOW", "cIF", "cELSE", "cFOR",
  "cTO", "cDO", "ILLEGAL", "\"(\"", "\")\"", "\"+\"", "\"-\"", "\"*\"",
  "\"^\"", "\"/\"", "\"<\"", "\">\"", "\"=\"", "\",\"", "NEG", "'\\n'",
  "\"[\"", "\"]\"", "\"USER\"", "$accept", "input", "programa",
  "expressao", "numero", "aritmetica", "relacional", "comando",
  "comandoIF", "comandoFOR", "funcao", "atributo", "atribuicao",
  "variavel", "formula", "funcaoTrig", "funcaoArit", "funcaoProb",
  "funcaoStrc", "funcaoUser", "listaparm", "illegal", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  genesyspp_parser::yyrline_[] =
  {
       0,   141,   141,   142,   143,   144,   145,   148,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   162,   163,   166,
     167,   168,   169,   170,   171,   174,   175,   176,   177,   178,
     179,   180,   181,   184,   185,   188,   189,   192,   193,   196,
     197,   198,   199,   200,   205,   209,   210,   213,   214,   215,
     219,   222,   223,   226,   227,   228,   229,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   244,   245,   246,
     253,   254,   255,   256,   274,   275,   276,   280,   284,   285,
     288
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
#line 1883 "../GenesysParser.cpp" // lalr1.cc:1167
#line 306 "bisonparser.yy" // lalr1.cc:1168

void
yy::genesyspp_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
