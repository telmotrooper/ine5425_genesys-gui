%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <locale>
# include <list>
# include "Genesys++-driver.h"
# include "GenesysParser.h"
# include "obj_t.h"
# include "../Util.h"
# include "../List.h"
# include "../Variable.h"
# include "../Queue.h"
# include "../Formula.h" 
# include "../Resource.h"
# include "../ModelElement.h"
# include "../Attribute.h"


// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch noinput

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

I     ~[A-Za-z]+
DD     [0-9]+([eE][-]?[0-9]+)?
RR     [0-9]+[.][0-9]+([eE][-]?[0-9]+)?
L      [A-Za-z0-9_.]+

%%

%{
  // Code run each time yylex is called.
  loc.step ();
%}


[0][xX][aA-fF0-9]+  {
						//Hexadecimal number
            //Will not fail because of regex
            //std::string text("Found Hexadecimal: ");
            //text += yytext;
            //driver.getModel()->getTraceManager()->trace(Util::TraceLevel::mostDetailed, text);
            return yy::genesyspp_parser::make_NUMH(obj_t(atof(yytext), std::string("Hexadecimal")),loc);
					}

{RR}  {
       //Float number
       //Will not fail because of regex
       //std::string text("Found Float: ");
       //text += yytext;
       //driver.getModel()->getTraceManager()->trace(Util::TraceLevel::mostDetailed, text);
       return yy::genesyspp_parser::make_NUMD(obj_t(atof(yytext),std::string("Float")), loc);
     }

{DD}  {
       //Decimal number
       //Will not fail because of regex
       //std::string text("Found Decimal: ");
       //text += yytext;
       //driver.getModel()->getTraceManager()->trace(Util::TraceLevel::mostDetailed, text);
       return yy::genesyspp_parser::make_NUMD(obj_t(atof(yytext),std::string("Decimal")), loc);
      }

[<][=]   { return (yy::genesyspp_parser::make_oLE(obj_t(0, std::string(yytext)), loc));}
[>][=]   { return (yy::genesyspp_parser::make_oGE(obj_t(0, std::string(yytext)), loc));}
[=][=]   { return (yy::genesyspp_parser::make_oEQ(obj_t(0, std::string(yytext)), loc));}
[<][>]   { return (yy::genesyspp_parser::make_oNE(obj_t(0, std::string(yytext)), loc));}

[tT][rR][uU][eE]      {return yy::genesyspp_parser::make_NUMD(obj_t(1, std::string(yytext)), loc);}
[fF][aA][lL][sS][eE]  {return yy::genesyspp_parser::make_NUMD(obj_t(0, std::string(yytext)), loc);}

[iI][fF]              {return yy::genesyspp_parser::make_cIF(obj_t(0, std::string(yytext)), loc);}
[eE][lL][sS][eE]      {return yy::genesyspp_parser::make_cELSE(obj_t(0, std::string(yytext)), loc);}
[fF][oO][rR]          {return yy::genesyspp_parser::make_cFOR(obj_t(0, std::string(yytext)), loc);}
[tT][oO]              {return yy::genesyspp_parser::make_cTO(obj_t(0, std::string(yytext)), loc);}
[dD][oO]              {return yy::genesyspp_parser::make_cDO(obj_t(0, std::string(yytext)), loc);}

[aA][nN][dD]    {return yy::genesyspp_parser::make_oAND(obj_t(0, std::string(yytext)), loc);}
[oO][rR]        {return yy::genesyspp_parser::make_oOR(obj_t(0, std::string(yytext)), loc);}
[nN][oO][tT]    {return yy::genesyspp_parser::make_oNOT(obj_t(0, std::string(yytext)), loc);}

[sS][iI][nN]      {return yy::genesyspp_parser::make_fSIN(obj_t(0, std::string(yytext)), loc);}
[cC][oO][sS]      {return yy::genesyspp_parser::make_fCOS(obj_t(0, std::string(yytext)), loc);}

[aA][iI][nN][tT]  {return yy::genesyspp_parser::make_fAINT(obj_t(0, std::string(yytext)), loc);}
[fF][rR][aA][cC]  {return yy::genesyspp_parser::make_fFRAC(obj_t(0, std::string(yytext)), loc);}
[mM][oO][dD]      {return yy::genesyspp_parser::make_fMOD(obj_t(0, std::string(yytext)), loc);}
[iI][nN][tT]      {return yy::genesyspp_parser::make_fINT(obj_t(0, std::string(yytext)), loc);}

[eE][xX][pP][oO]  {return yy::genesyspp_parser::make_fEXPO(obj_t(0, std::string(yytext)), loc);}
[nN][oO][rR][mM]  {return yy::genesyspp_parser::make_fNORM(obj_t(0, std::string(yytext)), loc);}
[uU][nN][iI][fF]  {return yy::genesyspp_parser::make_fUNIF(obj_t(0, std::string(yytext)), loc);}
[wW][eE][iI][bB]  {return yy::genesyspp_parser::make_fWEIB(obj_t(0, std::string(yytext)), loc);}
[lL][oO][gG][nN]  {return yy::genesyspp_parser::make_fLOGN(obj_t(0, std::string(yytext)), loc);}
[gG][aA][mM][mM]  {return yy::genesyspp_parser::make_fGAMM(obj_t(0, std::string(yytext)), loc);}
[eE][rR][lL][aA]  {return yy::genesyspp_parser::make_fERLA(obj_t(0, std::string(yytext)), loc);}
[tT][rR][iI][aA]  {return yy::genesyspp_parser::make_fTRIA(obj_t(0, std::string(yytext)), loc);}
[bB][eE][tT][aA]  {return yy::genesyspp_parser::make_fBETA(obj_t(0, std::string(yytext)), loc);}
[dD][iI][sS][cC]  {return yy::genesyspp_parser::make_fDISC(obj_t(0, std::string(yytext)), loc);}

[tT][nN][oO][wW]  {return yy::genesyspp_parser::make_fTNOW(obj_t(0, std::string(yytext)), loc);}
[tT][fF][iI][nN]  {return yy::genesyspp_parser::make_fTFIN(obj_t(0, std::string(yytext)), loc);}

[nN][rR]                             {return yy::genesyspp_parser::make_fNR(obj_t(0, std::string(yytext)), loc);}
[mM][rR]                             {return yy::genesyspp_parser::make_fMR(obj_t(0, std::string(yytext)), loc);}
[iI][rR][fF]                         {return yy::genesyspp_parser::make_fIRF(obj_t(0, std::string(yytext)), loc);}
[sS][tT][aA][tT][eE]                 {return yy::genesyspp_parser::make_fSTATE(obj_t(0, std::string(yytext)), loc);}
[rR][eE][sS][sS][eE][iI][zZ][eE][sS] {return yy::genesyspp_parser::make_fRESSEIZES(obj_t(0, std::string(yytext)), loc);}

[iI][dD][lL][eE][_][rR][eE][sS]                 {return yy::genesyspp_parser::make_NUMD(obj_t(-1, std::string(yytext)), loc);}
[bB][uU][sS][yY][_][rR][eE][sS]                 {return yy::genesyspp_parser::make_NUMD(obj_t(-2, std::string(yytext)), loc);}
[iI][nN][aA][cC][tT][iI][vV][eE][_][rR][eE][sS] {return yy::genesyspp_parser::make_NUMD(obj_t(-3, std::string(yytext)), loc);}
[fF][aA][iI][lL][eE][dD][_][rR][eE][sS]         {return yy::genesyspp_parser::make_NUMD(obj_t(-4, std::string(yytext)), loc);}

[nN][qQ]                             {return yy::genesyspp_parser::make_fNQ(obj_t(0, std::string(yytext)), loc);}
[lL][aA][sS][tT][iI][nN][qQ]         {return yy::genesyspp_parser::make_fLASTINQ(obj_t(0, std::string(yytext)), loc);}
[fF][iI][rR][sS][tT][iI][nN][qQ]     {return yy::genesyspp_parser::make_fFIRSTINQ(obj_t(0, std::string(yytext)), loc);}

[(] {return yy::genesyspp_parser::make_LPAREN(loc);}
[)] {return yy::genesyspp_parser::make_RPAREN(loc);}

[+] {return yy::genesyspp_parser::make_PLUS(loc);}
[-] {return yy::genesyspp_parser::make_MINUS(loc);}
[*] {return yy::genesyspp_parser::make_STAR(loc);}
[/] {return yy::genesyspp_parser::make_SLASH(loc);}

[<] {return yy::genesyspp_parser::make_LESS(loc);}
[>] {return yy::genesyspp_parser::make_GREATER(loc);}

[=] {return yy::genesyspp_parser::make_ASSIGN(loc);}

[,] {return yy::genesyspp_parser::make_COMMA(loc);}

[ \t\n]        ;


{L}   {
        // check if it is an ATTRIBUTE
        int rank = driver.getModel()->getElementManager()->getRankOf(Util::TypeOf<Attribute>(), std::string(yytext));
        if (rank>=0) {
            double attributeValue = 0.0;
            if (driver.getModel()->getSimulation()->getCurrentEntity() != nullptr) {
                try {
                    // it could crach because there may be no current entity, if the parse is running before simulation and therefore there is no CurrentEntity
                    attributeValue = driver.getModel()->getSimulation()->getCurrentEntity()->getAttributeValue(std::string(yytext));
                } catch(...) {
                }
            }
            return yy::genesyspp_parser::make_ATRIB(obj_t(attributeValue, Util::TypeOf<Attribute>(), -1),loc);
        }
        
        ModelElement* element; 
        // check VARIABLE
        element = driver.getModel()->getElementManager()->getElement(Util::TypeOf<Variable>(), std::string(yytext));
        if (element != nullptr) { // it is a variable
            Variable* var = static_cast<Variable*>(element);
            double variableValue = var->getValue();
            return yy::genesyspp_parser::make_VARI(obj_t(variableValue, Util::TypeOf<Variable>(), var->getId()),loc);
        }
        
        // check FORMULA
        element = driver.getModel()->getElementManager()->getElement(Util::TypeOf<Formula>(), std::string(yytext));
        if (element != nullptr) { // it is a FORMULA
            Formula* form = static_cast<Formula*>(element);
            double formulaValue = form->getValue();
            return yy::genesyspp_parser::make_FORM(obj_t(formulaValue, Util::TypeOf<Formula>(), form->getId()),loc);
        }
        
        // check QUEUE
        element = driver.getModel()->getElementManager()->getElement(Util::TypeOf<Queue>(), std::string(yytext));
        if (element != nullptr) { 
            return yy::genesyspp_parser::make_QUEUE(obj_t(0, Util::TypeOf<Variable>(), element->getId()),loc);
        }
        
        // check RESOURCE
        element = driver.getModel()->getElementManager()->getElement(Util::TypeOf<Resource>(), std::string(yytext));
        if (element != nullptr) { 
            return yy::genesyspp_parser::make_RES(obj_t(0, Util::TypeOf<Resource>(), element->getId()),loc);
        }

        /*
        //iterates through the model Elements and returns its id and the matching token
        std::list<std::string>* listaDisponiveis = driver.getModel()->getElementManager()->getElementTypenames();
        for(std::list<std::string>::iterator it = listaDisponiveis->begin(); it != listaDisponiveis->end(); ++it){
	    List<ModelElement*>* listaAtual = driver.getModel()->getElementManager()->getElements(*it);
	    for(std::list<ModelElement*>::iterator it2 = listaAtual->getList()->begin(); it2 != listaAtual->getList()->end(); ++it2){
		if((*it2)->getName() == std::string(yytext)){//case sensitive names
		    if (*it == Util::TypeOf<Variable>()){
			return yy::genesyspp_parser::make_VARI(obj_t(0, Util::TypeOf<Variable>(), (*it2)->getId()),loc);
		    }
		    if (*it == Util::TypeOf<Queue>()){
			return yy::genesyspp_parser::make_QUEUE(obj_t(0, Util::TypeOf<Queue>(), (*it2)->getId()),loc);
		    }
		    if (*it == Util::TypeOf<Resource>()){
			return yy::genesyspp_parser::make_RES(obj_t(0, Util::TypeOf<Resource>(), (*it2)->getId()),loc);
		    }
		}
	    }
        }
        */
        //Case not found retturns a illegal token
        return yy::genesyspp_parser::make_ILLEGAL(obj_t(0, std::string("Illegal")), loc);
      }

.       {return yy::genesyspp_parser::make_ILLEGAL(obj_t(1, std::string("Illegal")), loc);}

<<EOF>> {return yy::genesyspp_parser::make_END(loc);}


%%

void
genesyspp_driver::scan_begin_file ()
{
  //yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}

void genesyspp_driver::scan_begin_str ()
{
  //yy_flex_debug = trace_scanning;
  if(!str_to_parse.empty()){    
    yy_scan_string (str_to_parse.c_str()); //maybe throw exception on else
  }else{
    std::string str("0");
    yy_scan_string (str.c_str()); //maybe throw exception on else
  }
}



void
genesyspp_driver::scan_end_file ()
{
  fclose (yyin);
}

void
genesyspp_driver::scan_end_str ()
{
  yy_delete_buffer(YY_CURRENT_BUFFER);
}
